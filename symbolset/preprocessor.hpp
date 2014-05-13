#ifndef __INCLUDED_SYMBOLSET_PREPROCESSOR_HPP__
#define __INCLUDED_SYMBOLSET_PREPROCESSOR_HPP__

#define BOOST_PP_VARIADICS
#include <boost/preprocessor.hpp>


// utils
#define SYMBOLSET_PP_ARG_TUPLE(data_tuple) \
    BOOST_PP_TUPLE_ELEM(0, data_tuple)

#define SYMBOLSET_PP_VAL_TUPLE(data_tuple) \
    BOOST_PP_TUPLE_ELEM(1, data_tuple)

#define SYMBOLSET_PP_ARG(i, data_tuple) \
    BOOST_PP_TUPLE_ELEM(i, \
        SYMBOLSET_PP_ARG_TUPLE(data_tuple) \
    )

#define SYMBOLSET_PP_VAL(i, data_tuple) \
    BOOST_PP_TUPLE_ELEM(i, \
        SYMBOLSET_PP_VAL_TUPLE(data_tuple) \
    )

#define SYMBOLSET_PP_STR(i, data_tuple) \
    BOOST_PP_STRINGIZE( \
        SYMBOLSET_PP_VAL(i, data_tuple) \
    )

#define SYMBOLSET_PP_EACH(callback, data_tuple) \
    BOOST_PP_REPEAT( \
        BOOST_PP_TUPLE_SIZE(SYMBOLSET_PP_VAL_TUPLE(data_tuple)), \
        callback, \
        data_tuple \
    )


// display the symbols
#define SYMBOLSET_PP_SYMBOL_LIST(data_tuple) \
    SYMBOLSET_PP_EACH(SYMBOLSET_PP_SYMBOL, data_tuple)

#define SYMBOLSET_PP_SYMBOL(unused, i, data_tuple) \
    SYMBOLSET_PP_SYMBOL_IMPL( \
        SYMBOLSET_PP_VAL(i, data_tuple), i \
    )

#define SYMBOLSET_PP_SYMBOL_IMPL(symbol, value) \
    static constexpr value_type symbol = static_cast<value_type>(value);


// display the symbol-name mapping list
#define SYMBOLSET_PP_NAME_LIST(data_tuple) \
    BOOST_PP_SEQ_ENUM( \
        SYMBOLSET_PP_EACH(SYMBOLSET_PP_NAME, data_tuple) \
    )

#define SYMBOLSET_PP_NAME(unused, i, data_tuple) \
    SYMBOLSET_PP_NAME_IMPL( \
        SYMBOLSET_PP_ARG(0, data_tuple), \
        SYMBOLSET_PP_VAL(i, data_tuple), \
        SYMBOLSET_PP_STR(i, data_tuple) \
    )

#define SYMBOLSET_PP_NAME_IMPL(type, symbol, name) \
    ({::symbolset::val(type::symbol)) (name})


// display the static_assert() list
#define SYMBOLSET_PP_ASSERT_LIST(data_tuple) \
    SYMBOLSET_PP_EACH(SYMBOLSET_PP_ASSERT, data_tuple)

#define SYMBOLSET_PP_ASSERT(unused, i, data_tuple) \
    SYMBOLSET_PP_ASSERT_IMPL( \
        SYMBOLSET_PP_STR(i, data_tuple), \
        "Symbol name is empty! (index: " #i ")"  \
    )

#define SYMBOLSET_PP_ASSERT_IMPL(name, message) \
    static_assert(name[0] != '\0', message);


// display the symbolset
#define SYMBOLSET_DEFINE(type, symbols) \
    SYMBOLSET_PP_DEFINE(type, ((type), symbols))

#define SYMBOLSET_PP_DEFINE(type, data_tuple) \
    SYMBOLSET_PP_ASSERT_LIST(data_tuple) \
    \
    struct type: public ::symbolset::symbolset<type> { \
        using symbolset::symbolset; \
        \
        SYMBOLSET_PP_SYMBOL_LIST(data_tuple) \
        \
        static const info_type & info() { \
            static info_type const data{ \
                SYMBOLSET_PP_NAME_LIST(data_tuple) \
            }; \
            return data; \
        } \
    };

#endif // __INCLUDED_SYMBOLSET_PREPROCESSOR_HPP__
