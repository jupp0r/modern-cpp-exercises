#include <type_traits>

#include "gmock/gmock.h"
#include "exercise.h"

TEST(Task1, DataShouldBeFinal)
{
    EXPECT_TRUE(std::is_final<Data>::value);
}

TEST(Task2, BShouldReplaceFoo) {
    B b;
    EXPECT_EQ(1, b.foo());
}

TEST(Task3, StructShouldBeNonCopyable) {
    EXPECT_FALSE(std::is_copy_constructible<NonCopyable>::value);
    EXPECT_FALSE(std::is_copy_assignable<NonCopyable>::value);
}

TEST(Task4, ImplementationShouldBeFreedViaInterface)
{
    EXPECT_TRUE(std::has_virtual_destructor<Interface>::value);
}

TEST(Task5, ShouldUseDelegatingConstructors) {
    C c("hello world!");
    EXPECT_EQ(5, c.intField);
}
