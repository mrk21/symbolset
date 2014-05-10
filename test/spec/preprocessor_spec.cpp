#include <bandit/bandit.h>
#include <symbolset/symbolset.hpp>
#include <symbolset/preprocessor.hpp>
#include <iostream>

namespace symbolset {
    namespace preprocessor_test {
        SYMBOLSET_DEFINE(symtest, (
            value_a,
            value_b,
            value_c
        ));
    }
    
go_bandit([]{
    using namespace bandit;
    
    describe("SYMBOLSET_PP(type, symbols)", [&]{
        using namespace preprocessor_test;
        
        describe("#info().name_of(value_type v)", [&]{
            it("should be a name of the v", [&]{
                AssertThat(symtest::info().name_of(symtest::value_a), Equals("value_a"));
            });
        });
    });
});
}
