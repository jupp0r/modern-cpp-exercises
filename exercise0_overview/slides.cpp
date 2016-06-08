// Topic 0: auto
// =============

namespace useAuto
{

// ...

}




// Topic 1: decltype and decltype(auto)
// ====================================

namespace useDecltype
{

int f1() {return 0;};
int& f2() {static int a; return a;};
const int& f3() {static int a; return a;};

auto a1 = f1(); // C++11: a1 is int
auto a2 = f2(); // C++11: a1 is int
auto a3 = f3(); // C++11: a1 is int

decltype(f1()) b1 = f1(); // C++11: b1 is int
decltype(f2()) b2 = f2(); // C++11: b2 is int&
decltype(f3()) b3 = f3(); // C++11: b3 is const int&

decltype(auto) c1 = f1(); // C++14: c1 is int
decltype(auto) c2 = f2(); // C++14: c2 is int&
decltype(auto) c3 = f3(); // C++14: c3 is const int&

// NOTE: decltype(auto) not supported in VC12 but in VC14

struct A { double x; };
const A* a4 = new A{0};
decltype(a4->x) y;       // C++11: type of y is double (declared type)
decltype((a4->x)) z = y; // C++11: type of z is const double& (lvalue expression)

}



// Topic 2: nullptr
// ================

namespace useNullptr
{

class Foo;

void func(int) {}
void func(const Foo*) {}

void test()
{
  func(0);                          // Calls func(int)
  func(static_cast<const Foo*>(0)); // Calls func(const Foo*)
  func(nullptr);                    // Calls func(const Foo*)
}

// TIP: Always use nullptr!

}




// Topic 3: static_assert and <type_traits>
// ========================================
#include <type_traits>
// In #include <boost/version.h>
#define BOOST_VERSION 106100

namespace useStaticAssert
{

static_assert(
    BOOST_VERSION >= 105600,
    "The boost version used is too low!");

template <class Foo>
void swap(Foo& a, Foo& b)
{
    static_assert(
        std::is_copy_constructible<Foo>::value,
        "Swap requires copying");
    auto c = b;
    b = a;
    a = c;
}

template <class Foo>
struct data_structure
{
    static_assert(
        std::is_default_constructible<Foo>::value,
        "Data Structure requires default-constructible elements");
};

static_assert(
    std::is_same<
        typename std::decay<const float&>::type,
        float
    >::value,
    "Fundamental error!");

}




// Topic 4: <cstdint>
// ==================

#include <cstdint>

namespace useCstdint
{

// integral type aliases with specific width requirements

std::int8_t a;        // optional
std::uint8_t b;       // optional
std::int16_t c;       // optional
// ...
std::int64_t h;       // optional

// The optional types are available with all platforms / compilers we support.

std::int_least8_t i;  // fastest signed integer type with width of at least ...
std::uint_least8_t j; // fastest unsigned integer type with width of at least ...
// ...

std::int_fast8_t q;   // smallest signed integer type with width of at least ...
std::uint_fast8_t r;  // smallest unsigned integer type with width of at least ...
// ...

}




// Topic 5: scoped enums (enum class|struct) / sized enums
// =======================================================
#include <cstdint>

namespace useScopedEnum
{

enum Color { red, green, blue };
Color col0 = red;
Color col1 = Color::red;                // C++11, not allowed in C++98
int col2 = red;
int col3 = red | green;

enum class Temperature { cold, medium, hot };
//Temperature temp0 = cold;              // error: 'cold' was not declared in this scope
Temperature temp1 = Temperature::medium; // C++11
//int temp2 = Temperature::medium;       // error: cannot convert 'Temperature' to 'int' in initialization
//Temperature temp3 = Temperature::medium | Temperature::hot; // error: no match for 'operator|' (operand types are 'Temperature' and 'Temperature')

enum EnumDefault {};                 // C++98: Value type is int
enum EnumTyped : std::uint16_t {};   // C++11: Value type is std::uint16_t

}




// Topic 6: uniform initialization
// ===============================
#include <string>

namespace useUniformInitialization
{

int s = 42;   // C++98
int t(43);    // C++98
int u{44};    // C++11
int v = {45}; // C++11

class Foo {
public:
    Foo(int, double, std::string) {}
};
Foo foo0 (5, 3.14, "zero");     // C++98
Foo foo1 {5, 3.14, "one"};      // C++11
Foo foo2 = {5, 3.14, "two"};    // C++11

Foo getFoo()
{
    return {5, 3.14, "five"};   // C++11
}

// NOTE: Be carefull with std::initializer_list<...> as this constructor is preferred when using uniform initialization

}




// Topic 7: template aliases (using)
// =================================
#include <memory>
#include <iostream>

namespace useTemplateAliases
{

// typedef == using
typedef std::ios_base::fmtflags flags0; // C++98
using flags1 = std::ios_base::fmtflags; // C++11

typedef void (*fn)(int, int);           // C++98
using fn = void (*)(int, int);          // C++11

template<typename T>
struct Container { using value_type = T; };

// alias template
template <class T>
using ptr_to_T = T*;
ptr_to_T<int> x;

template<typename T>
using DecayedSharedPtr = std::shared_ptr<std::decay<T>>;

// TIP: Always use using instead of typedef because it is easier to read!

}



// Topic 8: variadic templates
// ===========================
#include <iostream>

namespace useVariadicTemplates
{

// Termination version used for zero argument call
void printLn()
{
    std::cout << std::endl;
}

// Version used for one or more argument call
template<typename Arg1, typename... Args>
void printLn(const Arg1& arg1, const Args&... args)
{
    // First argument
    std::cout << arg1;
    // Rest
    // ... == pack expansion into comma-separated instantiations of the pattern,
    // where the name of the parameter pack is replaced by each of the elements from the pack, in order.
    printLn(args...); // note: arg1 does not appear here!
}

template<class... Args>
std::size_t count(const Args&...)
{
    return sizeof...(Args);
}

void useVariadicTemplates()
{
    printLn("Hello", " world", '!', ' ', 123);                          // prints 'Hello world! 123'
    std::cout << count("Hello", " world", '!', ' ', 123) << std::endl;  // prints '5'
}

}




// Topic 9: trailing return type (C++11) and return type deduction (C++14)
// =======================================================================
namespace useTrailingReturnType
{

float pi0() {return 3.1415f;}           // C++98
auto pi1() -> float {return 3.1415f;}   // trailing return type (C++11)
auto pi2() {return 3.1415f;}            // return type deduction (C++14)

// Does not compile: lhs and rhs are not in scope
//template <typename L, typename R>
//decltype(lhs * rhs) multiply(L lhs, R rhs)
//{
//    return lhs * rhs;
//}

// C++98
template <typename Ret, typename L, typename R>
Ret multiply(L lhs, R rhs)
{
    return lhs * rhs;
}

// C++11
template <typename L, typename R>
auto multiply(L lhs, R rhs) -> decltype(lhs * rhs)
{
    return lhs * rhs;
}

// C++14: Not supported in VC12 but in VC14
template <typename L, typename R>
auto multiply(L lhs, R rhs)
{
    return lhs * rhs;
}

}




// Topic 10: range based for loop
// ==============================
#include <vector>
#include <iostream>

void useRangeBasedForLoop()
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5};

    for(const auto& i : v)
        std::cout << i << ' ';
    std::cout << std::endl;

    for(const auto& n : {0, 1, 2, 3, 4, 5})
        std::cout << n << ' ';
    std::cout << std::endl;

    int a[] = {0, 1, 2, 3, 4, 5};
    for(const auto& n : a)
        std::cout << n << ' ';
    std::cout << std::endl;

    std::string str = "0 1 2 3 4 5";
    for(const auto& c : str)
        std::cout << c;
    std::cout << std::endl;

    for(auto&& i : v)
        std::cout << ++i << ' ';
    std::cout << std::endl;
}

// TIP:
// When not changing the contents of the vector:
//  - capture by 'const auto&'
//  - or capture by 'auto' if element copies are cheap
// When changing the contents of the vector:
//  - capture by 'auto&&'
//  - or capture by 'auto&' if you are sure the container does not return proxy objects




// Topic 11: binary literals (C++14) / digit seperators (C++14)
// ============================================================

namespace useBinaryLiterals
{

#if !defined(_MSC_VER) || (_MSC_VER >= 1900) // NOTE: Not supported in VC12 but in VC14

auto binary_literal = 0b0100'1100'0110;
auto integer_literal = 1'000'000;
auto floating_point_literal = 0.000'015'3;

#endif

}




// Topic 12: user defined literals (C++11/C++14)
// =============================================
#include <vector>
#include <string>
#include <chrono>

namespace useUserDefinedLiterals
{

// C++11
// User defined literals have to start with '_'
size_t operator "" _KiB(unsigned long long size)
{
   return static_cast<size_t>(size * 1024);
}

std::vector<unsigned char> buffer(4_KiB);

// C++14
#if !defined(_MSC_VER) || (_MSC_VER >= 1900) // NOTE: C++14 parts not supported in VC12 but in VC14

using namespace std::string_literals;
auto str = "hello world"s;  // auto deduces string

using namespace std::literals::chrono_literals;
auto dur0 = 60s;            // auto deduces chrono::seconds
auto dur1 = 24min;          // auto deduces chrono::minutes

#endif

}



// Topic 13: [[deprecated]] attributes (C++14)
// ===========================================

namespace useDeprecatedAttribute
{

#if !defined(_MSC_VER) || (_MSC_VER >= 1900) // NOTE: Not supported in VC12 but in VC14

[[deprecated]] int f() {return 42;}

[[deprecated("g() is NOT thread-safe. Use w() instead!")]]
void g(int&) {}

void w(int&) {}

void testDeprecated() {
  int a = f();  // warning: 'f' is deprecated
  g(a);         // warning: 'g' is deprecated: g() is thread-unsafe. Use h() instead
}

#endif

}
