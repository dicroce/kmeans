
#ifndef __distance_h
#define __distance_h

#include <cmath>
#include <ctgmath>

#include "type_traits.h"
#include "zip.h"

template<typename iter>
void add_vec( iter outFirst, iter outLast, iter first1, iter first2 )
{
    zip( []( iter out, iter a, iter b ) {
            *out = *a + *b;
         },
         outFirst,
         outLast,
         first1,
         first2 );
}

template<typename iter>
iter_value_type<iter> sum_of_squares( iter first1, iter last1, iter first2, iter last2, iter_value_type<iter> init )
{
    iter_value_type<iter> result = init;

    zip( [&result]( iter a,
                    iter b ) {
             result += std::pow( std::abs( *a - *b ), 2.0 );
         },
         first1,
         last1,
         first2 );

    return result;
}

template<typename iter>
iter_value_type<iter> euclidean_distance( iter first1, iter last1, iter first2, iter last2, iter_value_type<iter> init )
{
    return std::sqrt( sum_of_squares( first1, last1, first2, last2, init ) );
}

#endif
