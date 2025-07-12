#ifndef BDD_HPP
#define BDD_HPP

#define describe(name, fn) TEST_CASE(name) { fn(); }
#define context(name, fn) SECTION(name) { fn(); }
#define it(name, fn) SECTION(name) { fn(); }

#define before_each(fn) auto __setup = [&]() { fn(); }; __setup();
#define after_each(fn) auto __cleanup = [&]() { fn(); }; \
struct __Cleanup { \
std::function<void()> f; \
~__Cleanup() { f(); } \
} __cleanup_obj{__cleanup};

#define should(expr) REQUIRE(expr)
#define should_not(expr) REQUIRE_FALSE(expr)
#define should_eq(actual, expected) REQUIRE((actual) == (expected))
#define should_ne(actual, expected) REQUIRE((actual) != (expected))
#define should_throw(expr) REQUIRE_THROWS(expr)
#define should_nothrow(expr) REQUIRE_NOTHROW(expr)

#include <functional>

#endif