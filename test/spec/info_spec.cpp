#include <bandit/bandit.h>
#include <symbolset/symbolset.hpp>
#include <algorithm>

namespace symbolset {
    namespace info_test {
        struct symtest: public symbolset<symtest> {
            using symbolset::symbolset;
            constexpr symtest() : symbolset() {};
            constexpr symtest(const symbolset & v) : symbolset(static_cast<value_type>(v)) {}
            
            static constexpr value_type a = static_cast<value_type>(1);
            static constexpr value_type b = static_cast<value_type>(2);
            static constexpr value_type c = static_cast<value_type>(3);
        };
    }
    
go_bandit([]{
    using namespace bandit;
    
    describe("info", [&]{
        using namespace info_test;
        
        symtest::info const info{
            {val(symtest::a), "a"},
            {val(symtest::b), "b"},
            {val(symtest::c), "c"},
        };
        
        describe("#name_of(symbol_type v)", [&]{
            it("should be name of the v", [&]{
                AssertThat(info.name_of(symtest::a), Equals("a"));
            });
            
            describe("when the v was not existed", [&]{
                it("should be the invalid", [&]{
                    AssertThat(info.name_of(static_cast<symtest>(100)), Equals("invalid"));
                });
            });
        });
        
        describe("#symbol_of(name_type v)", [&]{
            it("should be name of the v", [&]{
                AssertThat(info.symbol_of("a"), Equals(val(symtest::a)));
            });
            
            describe("when the v been not existed", [&]{
                it("should be the symbolset<T>::invalid", [&]{
                    AssertThat(info.symbol_of("not_exists"), Equals(symtest::invalid));
                });
            });
        });
        
        describe("#names()", [&]{
            it("should get", [&]{
                symtest::info::name_list expected{"a","b","c"};
                const symtest::info::name_list & actual = info.names();
                AssertThat(actual.size(), Equals(expected.size()));
                AssertThat(std::equal(actual.begin(), actual.end(), expected.begin()), Equals(true));
            });
        });
        
        describe("#symbols()", [&]{
            it("should get", [&]{
                symtest::info::symbol_list expected{
                    symtest::a,
                    symtest::b,
                    symtest::c,
                };
                const symtest::info::symbol_list & actual = info.symbols();
                AssertThat(actual.size(), Equals(expected.size()));
                AssertThat(std::equal(actual.begin(), actual.end(), expected.begin()), Equals(true));
            });
        });
    });
});
}
