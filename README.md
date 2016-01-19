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
