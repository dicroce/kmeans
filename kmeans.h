
#ifndef __kmeans_h
#define __kmeans_h

#include <stdexcept>

#include "distance.h"

template<typename T>
class kmeans
{
    using iter = typename std::vector<T>::iterator;

private:
    struct _center
    {
        std::vector<T> data;
        std::vector<std::pair<iter,iter>> members;
    };

public:
    kmeans( size_t numPoints = 20 ) :
        _data(),
        _centers(),
        _numPoints( numPoints )
    {
        _data.reserve( _numPoints );
    }

    virtual ~kmeans() noexcept {}

    void add_center( unsigned int n = 1 )
    {
        for( unsigned int i = 0; i < n; ++i )
            _centers.push_back( _center() );
    }

    std::vector<std::vector<T>> get_centers()
    {
        std::vector<std::vector<T>> centers;
        for( auto c : _centers )
            centers.push_back( c.data );
        return centers;
    }

    void add_data_point( iter first, iter last )
    {
        _data.push_back( std::make_pair( first, last ) );
    }

    void clear()
    {
        _centers.clear();
        _data.clear();
        _data.reserve( _numPoints );
    }

    bool cluster()
    {
        if( _centers.size() < 1 )
            throw std::runtime_error( "You need at lease one cluster center." );

        if( _data.size() < _centers.size() )
            throw std::runtime_error( "You need more data than cluster centers." );

        if( _centers.front().data.empty() )
            _initialize_centers();

        for( auto i = _data.begin(), iend = _data.end(); i != iend; ++i )
        {
            auto closestCenter = _centers.end();
            T leastDistance;

            for( auto ii = _centers.begin(), iiend = _centers.end(); ii != iiend; ++ii )
            {
                T d = euclidean_distance( i->first, i->second, ii->data.begin(), ii->data.end(), 0 );
                if( closestCenter == _centers.end() || d < leastDistance )
                {
                    closestCenter = ii;
                    leastDistance = d;
                }
            }

            closestCenter->members.push_back( *i );
        }

        T maxMoveDistance = 0;

        // refine our clusters
        for( auto &c : _centers )
        {
            auto oldCenterData = c.data;

            for( auto i = c.data.begin(), iend = c.data.end(); i != iend; ++i )
            {
                size_t index = i - c.data.begin();

                T sum = 0;
                for( auto m : c.members )
                    sum += *(m.first + index);
                *i = sum / c.members.size();
            }

            T d = euclidean_distance( oldCenterData.begin(), oldCenterData.end(), c.data.begin(), c.data.end(), 0.0 );
            if( d > maxMoveDistance )
                maxMoveDistance = d;
        }
        return (maxMoveDistance>1.0);
    }

private:
    void _initialize_centers()
    {
        auto i = _data.begin();

        for( auto &c : _centers )
        {
            c.data.clear();
            c.members.clear();
            std::copy( i->first, i->second, back_inserter(c.data) );
            ++i;
        }
    }

    std::vector<std::pair<iter,iter>> _data;
    std::vector<struct _center> _centers;
    size_t _numPoints;
};

#endif

