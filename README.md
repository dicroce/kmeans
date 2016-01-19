# kmeans

Super simple kmeans clustering implementation.

Use it like this:

```c++
#include "kmeans.h"

int main( int argc, char* argv[] )
{
    kmeans<double> km;
    
    std::vector<float> row1 = { 1, 2 };
    std::vector<float> row2 = { 3, 4 };
    
    // Data points are added to kmeans via a pair of iterators. kmeans
    // class does not copy or own your data, so you must make sure it
    // exists for the duration you are using the class.
    km.add_data_point( row1.begin(), row1.end() );
    km.add_data_point( row2.begin(), row2.end() );
    
    // How many cluster centers do you expect?
    km.add_center( 2 );
    
    // kmeans returns false when cluster centers stabilize...
    while( km.cluster() );
    
    // Retrieve centers like this:
    auto centers = km.get_centers();
    for( auto c : centers )
      cout << c[0] << " " << c[1] << endl;

    return 0;
}
```

kmeans is header only and only depends on the STL, but the build here compiles a demo application that uses opengl. If you have trouble compiling (standard cmake stuff) just take kmeans.h, type_traits.h, zip.h, distance.h. You could probably even put it all in one .h file if you'd like.
