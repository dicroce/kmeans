
#ifndef __zip_h
#define __zip_h

//
// zip functionality

template<typename iter>
void _zip_inc_iters(iter& iterator)
{
    ++iterator;
}

template<typename iter, typename...iters>
void _zip_inc_iters(iter& iterator, iters&...iterators)
{
    ++iterator;
    _zip_inc_iters(iterators...);
}

// Call callable f with values between begin and end and corresponding values from
// variadic arguments:
//
//    vector<int> v1{1,2,3};
//    vector<float> v2{3.0,2.0,1.5};
//    vector<string> v3{"foo","bar","baz"};
//
//    zip( []( int a, float b, string c ) {
//             // do stuff...
//         } ),
//         v1.begin(),
//         v2.end(),
//         v3.begin() );

template<typename func, typename iter, typename...iters>
func zip(func f, iter begin, iter end, iters...iterators)
{
    for(;begin != end; ++begin, _zip_inc_iters(iterators...))
        f(begin, (iterators)...);
    return f;
}

#endif
