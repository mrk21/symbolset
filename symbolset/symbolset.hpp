#ifndef __INCLUDED_SYMBOLSET_SYMBOLSET_HPP__
#define __INCLUDED_SYMBOLSET_SYMBOLSET_HPP__

namespace symbolset {
    template<class T>
    class symbolset {
    public:
        enum class value_type: uint8_t {};
        
    protected:
        value_type value;
        
    public:
        constexpr symbolset() : value{} {};
        constexpr symbolset(value_type v) : value(v) {}
        constexpr explicit symbolset(uint8_t v) : value(static_cast<value_type>(v)) {}
        
        constexpr operator value_type() const {
            return this->value;
        }
        constexpr explicit operator int() const {
            return static_cast<int>(this->value);
        }
    };
}

#endif // __INCLUDED_SYMBOLSET_SYMBOLSET_HPP__
