
#ifndef __type_traits_h
#define __type_traits_h

//
// Type aliases are shortcut type names for various iterator trait types.

template<typename iter>
using iter_difference_type = typename std::iterator_traits<iter>::difference_type;

template<typename iter>
using iter_value_type = typename std::iterator_traits<iter>::value_type;

template<typename iter>
using iter_pointer_type = typename std::iterator_traits<iter>::pointer;

template<typename iter>
using iter_reference_type = typename std::iterator_traits<iter>::reference;

#endif
