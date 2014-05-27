#include <bandit/bandit.h>
#include <symbolset/symbolset.hpp>
#include <symbolset/preprocessor.hpp>
#include <iostream>
#include <sstream>

namespace symbolset {
    namespace preprocessor_test {
        SYMBOLSET_DEFINE(symtest, (
            value_a,
            value_b,
            value_c
        ));
        
        SYMBOLSET_DEFINE(symtest_ex, symtest, (
            value_d,
            value_e,
            value_f
        ));
        
        SYMBOLSET_DEFINE(symtest_ex2, symtest_ex, (
            value_g,
            value_h,
            value_i
        ));
    }
    
go_bandit([]{
    using namespace bandit;
    
    describe("SYMBOLSET_PP(type[ ,base_type], symbols)", [&]{
        using namespace preprocessor_test;
        
        describe("#info().name_of(value_type v)", [&]{
            it("should be a name of the v", [&]{
                AssertThat(symtest::info().name_of(symtest::value_a), Equals("value_a"));
            });
        });
        
        describe("operator <<(std::ostream & out, type value)", [&]{
            it("should be a name of the `value`", [&]{
                std::ostringstream oss;
                oss << symtest(symtest::value_a);
                AssertThat(oss.str(), Equals("value_a"));
            });
        });
        
        describe("with the `base_type`", [&]{
            describe("#info().name_of(value_type v)", [&]{
                it("should be a name of the v", [&]{
                    AssertThat(symtest_ex::info().name_of(symtest_ex::value_a), Equals("value_a"));
                    AssertThat(symtest_ex::info().name_of(symtest_ex::value_d), Equals("value_d"));
                    
                    AssertThat(symtest_ex2::info().name_of(symtest_ex2::value_a), Equals("value_a"));
                    AssertThat(symtest_ex2::info().name_of(symtest_ex2::value_d), Equals("value_d"));
                    AssertThat(symtest_ex2::info().name_of(symtest_ex2::value_g), Equals("value_g"));
                });
            });
            
            describe("operator <<(std::ostream & out, type value)", [&]{
                it("should be a name of the `value`", [&]{
                    { std::ostringstream oss; oss << symtest_ex(symtest_ex::value_a); AssertThat(oss.str(), Equals("value_a")); }
                    { std::ostringstream oss; oss << symtest_ex(symtest_ex::value_d); AssertThat(oss.str(), Equals("value_d")); }
                    
                    { std::ostringstream oss; oss << symtest_ex2(symtest_ex2::value_a); AssertThat(oss.str(), Equals("value_a")); }
                    { std::ostringstream oss; oss << symtest_ex2(symtest_ex2::value_d); AssertThat(oss.str(), Equals("value_d")); }
                    { std::ostringstream oss; oss << symtest_ex2(symtest_ex2::value_g); AssertThat(oss.str(), Equals("value_g")); }
                });
            });
        });
    });
});
}
