#include <bandit/bandit.h>
#include <symbolset/symbolset.hpp>

namespace symbolset {
    namespace symbolset_test {
        struct symtest: public symbolset<symtest> {
            using symbolset::symbolset;
            constexpr symtest() : symbolset() {};
            constexpr symtest(const symbolset & v) : symbolset(static_cast<value_type>(v)) {}
        };
        
        struct symtest_ex: public symtest {
            using symtest::symtest;
        };
        
        struct symtest_ex2: public symtest_ex {
            using symtest_ex::symtest_ex;
        };
    }
    
go_bandit([]{
    using namespace bandit;
    
    describe("symbolset<T>", [&]{
        using namespace symbolset_test;
        
        describe("#symbolset(int value), #operator int()", [&]{
            it("should be the value", [&]{
                symtest v = static_cast<symtest>(3);
                AssertThat(static_cast<int>(v), Equals(3));
            });
        });
        
        describe("#symbolset(value_type value)", [&]{
            it("should set the value", [&]{
                symtest v = static_cast<symtest::value_type>(3);
                AssertThat(static_cast<int>(v), Equals(3));
            });
        });
        
        describe("#operator value_type()", [&]{
            it("should convert", [&]{
                symtest v(3);
                AssertThat(static_cast<symtest::value_type>(v), Equals(static_cast<symtest::value_type>(3)));
            });
        });
        
        it("should convert the bese class to the derived class", [&]{
            symtest_ex v1 = static_cast<symtest>(3);
            AssertThat(static_cast<int>(v1), Equals(3));
            
            symtest_ex2 v2 = static_cast<symtest>(3);
            AssertThat(static_cast<int>(v2), Equals(3));
            
            symtest_ex2 v3 = static_cast<symtest_ex>(3);
            AssertThat(static_cast<int>(v3), Equals(3));
        });
    });
});
}
