#ifndef __INCLUDED_SYMBOLSET_SYMBOLSET_HPP__
#define __INCLUDED_SYMBOLSET_SYMBOLSET_HPP__

#include <symbolset/info.hpp>

namespace symbolset {
    // The template parameter T is derived class.
    // You must add the inheriting constructors as shown below to the all derived class:
    //   class derived_class: public base_class {
    //     using base_class::base_class;
    //   };
    template<class T>
    class symbolset_base {
    public:
        enum class value_type: uint8_t {};
        using info_type = info<symbolset_base>;
        
    protected:
        value_type value;
        
    public:
        constexpr symbolset_base() : value{} {};
        constexpr symbolset_base(value_type v) : value(v) {}
        constexpr explicit symbolset_base(uint8_t v) : value(static_cast<value_type>(v)) {}
        
        constexpr operator value_type() const {
            return this->value;
        }
        constexpr explicit operator int() const {
            return static_cast<int>(this->value);
        }
        
        static constexpr value_type invalid = static_cast<value_type>(0);
    };
    
    template<class T>
    constexpr typename symbolset_base<T>::value_type symbolset_base<T>::invalid;
    
    
    template<class T>
    class symbolset: public symbolset_base<T> {
        using my_symbolset_base = symbolset_base<T>;
        
    public:
        using my_symbolset_base::symbolset_base;
        
        constexpr symbolset() : my_symbolset_base() {}
        constexpr symbolset(my_symbolset_base v) : my_symbolset_base(v) {}
    };
    
    
    template<class T>
    inline constexpr T val(T v) {
        return v;
    }
}

#endif // __INCLUDED_SYMBOLSET_SYMBOLSET_HPP__
