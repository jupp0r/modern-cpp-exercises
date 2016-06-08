#include <gtest/gtest.h>


// NOTE: The easiest way to work through the tasks is by commenting out all the other tasks and fixing one task after the other.


// Task 0: auto
// ============
TEST(Task0, useAuto)
{
    // TODO
}




// Task 1: decltype and decltype(auto)
// ===================================
TEST(Task1, useDecltype)
{
    // nothing to do ...
}




// Task 2: nullptr
// ===============
#include <vector>
#include <algorithm>

TEST(Task2, useNullptr)
{
    class Foo;
    std::vector<Foo*> foos;
    std::fill(foos.begin(), foos.end(), 0);               // FIXME: Does not compile. Only change this line.
}




// Task 3: static_assert and <type_traits>
// =======================================
#include <type_traits>
#include <cmath>

template <class Foo>
int fround(Foo f)
{
    static_assert(
        std::is_floating_point<Foo>::value,
        "Foo is required to be a floating point type");
    return static_cast<int>(std::round(f));
};

TEST(Task3, useStaticAssert)
{
    EXPECT_EQ(2, fround(2));                              // FIXME: Does not compile. Only change this line.
}




// Task 4: <cstdint>
// =================
#include <cstdint>

TEST(Task4, useCstdint)
{
    static_assert(
        sizeof(std::int16_t) == 2,
        "Fundamental error!");
    static_assert(
        sizeof(std::int16_t) == sizeof(std::int_fast16_t),
        "Fundamental error!");                            // FIXME: Something is wrong here!
}




// Task 5: scoped enums (enum class|struct) / sized enums
// ======================================================
#include <cstdint>

TEST(Task5, useScopedEnum)
{
    enum class Color : std::uint8_t { red, green, blue };

    int i = red;                                          // FIXME: Does not compile. Only change this line.
}




// Task 6: uniform initialization
// ==============================
TEST(Task6, useUniformInitialization)
{
    // TODO
}




// Task 7: template aliases (using)
// ================================
TEST(Task7, useTemplateAliases)
{
    // Nothing to do ...
}




// Task 8: variadic templates
// ==========================
namespace useVariadicTemplates
{

template<typename T, typename... Args>
T add(T first, Args... args) {
    return first + add(args...);
}

TEST(Task8, useVariadicTemplates)
{
    EXPECT_EQ(21, add(1, 2, 3, 8, 7));                    // FIXME: Does not compile. Do not change this line.
    EXPECT_EQ(6, add(1, 2, 3));                           // FIXME: Does not compile. Do not change this line.
    EXPECT_EQ(3, add(1, 2));                              // FIXME: Does not compile. Do not change this line.
    EXPECT_EQ(1, add(1));                                 // FIXME: Does not compile. Do not change this line.
}

}




// Task 9: trailing return type (C++11) and return type deduction (C++14)
// ======================================================================
namespace useTrailingReturnType
{

namespace foo
{
    template<typename Value>
    struct DoSomething
    {
        using ResultType = typename std::decay<Value>::type;

        ResultType get();

        // ...
    };
}

template<typename Value>
ResultType foo::DoSomething<Value>::get()                 // FIXME: Does not compile.
                                                          // Fix by only changing this line but without adding the namespace or class prefix.
{
    return {/*...*/};
}

TEST(Task9, useTrailingReturnType)
{
    foo::DoSomething<const int&> doSomething;
    auto f = doSomething.get();
}

}




// Task 10: range based for loop
// =============================
TEST(Task10, useRangeBasedForLoop)
{
    std::vector<bool> v = {true, false, false, true};
    for (auto& x : v)                                     // FIXME: Does not compile.
    {
        x = !x;
    }

    const std::vector<bool> ref = {false, true, true, false};
    for (std::size_t i = 0; i < ref.size(); ++i)
    {
        EXPECT_EQ(v[i], ref[i]);
    }
}




// Task 11: binary literals (C++14) / digit seperators (C++14)
// ===========================================================
TEST(Task11, useBinaryLiterals)
{
    // Nothing to do ...
}




// Task 12: user defined literals (C++11)
// ===========================================================
TEST(Task12, useUserDefinedLiterals)
{
    // Nothing to do ...
}




// Topic 13: [[deprecated]] attributes (C++14)
// ===========================================
TEST(Task13, useDeprecatedAttribute)
{
    // Nothing to do ...
}
