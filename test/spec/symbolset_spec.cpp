#include <bandit/bandit.h>
#include <symbolset/symbolset.hpp>

namespace symbolset {
go_bandit([]{
    using namespace bandit;
    
    describe("symbolset", [&]{
        it("should be true", [&]{
            AssertThat(true, Equals(true));
        });
    });
});
}
