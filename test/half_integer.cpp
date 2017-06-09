#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include "wigner/half_integer.hpp"

using HalfInt = wigner::HalfInteger<int>;

TEST_CASE("Test constructors of HalfInteger", "[half_integer]")
{
    SECTION("is default contractible")
    {
        HalfInt j1;
        REQUIRE(j1.twice() == 0);
    }
    SECTION("can be create from an integer")
    {
        HalfInt j2(2);
        REQUIRE(j2.twice() == 4);
        HalfInt j3(-3, wigner::make_half);
        REQUIRE(j3.twice() == -3);
    }
    SECTION(
        "can be create from a floating point (rounded to nearest half-integer)")
    {
        HalfInt j1(1.0);
        REQUIRE(j1.twice() == 2);
        HalfInt j2(2.5);
        REQUIRE(j2.twice() == 5);
        HalfInt j3(-2.5);
        REQUIRE(j3.twice() == -5);
        HalfInt j4(2.49);
        REQUIRE(j4.twice() == 5);
        HalfInt j5(-2.49);
        REQUIRE(j5.twice() == -5);
        HalfInt j6(2.1);
        REQUIRE(j6.twice() == 4);
        HalfInt j7(-2.1);
        REQUIRE(j7.twice() == -4);
    }
    SECTION("is copy constructible")
    {
        HalfInt j1(2);
        HalfInt j2(j1);
        REQUIRE(j2.twice() == j1.twice());
    }
    SECTION("is move constructible")
    {
        HalfInt j1(-3, wigner::make_half);
        HalfInt j2(std::move(j1));
        REQUIRE(j2.twice() == -3);
    }
}

TEST_CASE("assignment operations for HalfInteger", "[half_integer]")
{
    HalfInt j1(1);
    HalfInt j2(-2);
    HalfInt j3(3, wigner::make_half);

    HalfInt j;

    SECTION("is copiable")
    {
        j = j1;
        REQUIRE(j.twice() == 2);

        j = j2;
        REQUIRE(j.twice() == -4);
    }
    SECTION("is movable")
    {
        j = std::move(j3);
        REQUIRE(j.twice() == 3);
    }
    SECTION("can assign an integer value")
    {
        j = 5;
        REQUIRE(j.twice() == 10);
        j = -2;
        REQUIRE(j.twice() == -4);
    }
    SECTION("can assign a floating point value")
    {
        j = 0.5;
        REQUIRE(j.twice() == 1);
        j = -2.5;
        REQUIRE(j.twice() == -5);
    }
}

TEST_CASE("arithmetic operators for HalfInteger", "[half_integer]")
{
    HalfInt j0(0);
    HalfInt j1(2);
    HalfInt j2(-5);
    HalfInt j3(1.5);
    HalfInt j;
    //
    // Increment/Decrement
    //
    SECTION("increment: ++a, a++")
    {
        ++j0;
        REQUIRE(j0.twice() == 2);
        j = j0++;
        REQUIRE(j.twice() == 2);
        REQUIRE(j0.twice() == 4);
    }
    SECTION("decrement: --a== a--")
    {
        --j0;
        REQUIRE(j0.twice() == -2);
        j = j0--;
        REQUIRE(j.twice() == -2);
        REQUIRE(j0.twice() == -4);
    }
    SECTION("unary plus: +a")
    {
        j = +j0;
        REQUIRE(j.twice() == 0);
        j = +j1;
        REQUIRE(j.twice() == 4);
        j = +j2;
        REQUIRE(j.twice() == -10);
    }
    SECTION("unary minus: -a")
    {
        j = -j0;
        REQUIRE(j.twice() == 0);
        j = -j1;
        REQUIRE(j.twice() == -4);
        j = -j2;
        REQUIRE(j.twice() == 10);
    }
    SECTION("addition assignment: b += a")
    {
        j = 0;
        j += j1;
        REQUIRE(j.twice() == 4);
        j += j2;
        REQUIRE(j.twice() == -6);
        j += j3;
        REQUIRE(j.twice() == -3);

        j += 1;
        REQUIRE(j.twice() == -1);
        j += -2;
        REQUIRE(j.twice() == -5);
        j += 2.5;
        REQUIRE(j.twice() == 0);
    }
    SECTION("subtraction assignment: b -= a")
    {
        j -= j1;
        REQUIRE(j.twice() == -4);
        j -= j2;
        REQUIRE(j.twice() == 6);
        j -= j3;
        REQUIRE(j.twice() == 3);

        j -= 1;
        REQUIRE(j.twice() == 1);
        j -= -2;
        REQUIRE(j.twice() == 5);
        j -= 2.5;
        REQUIRE(j.twice() == 0);
    }
    SECTION("addition: a + b")
    {
        j = j1 + j2;
        REQUIRE(j.twice() == -6);
        j = j1 + j3;
        REQUIRE(j.twice() == 7);

        j = j1 + 2;
        REQUIRE(j.twice() == 8);
        j = -3 + j1;
        REQUIRE(j.twice() == -2);

        j = j3 + 1.5;
        REQUIRE(j.twice() == 6);
        j = 1.5 + j3;
        REQUIRE(j.twice() == 6);
    }
    SECTION("subtraction: a - b")
    {
        j = j1 - j2;
        REQUIRE(j.twice() == 14);
        j = j1 - j3;
        REQUIRE(j.twice() == 1);

        j = j1 - 2;
        REQUIRE(j.twice() == 0);
        j = -3 - j1;
        REQUIRE(j.twice() == -10);

        j = j3 - 2.5;
        REQUIRE(j.twice() == -2);
        j = 2.5 - j3;
        REQUIRE(j.twice() == 2);
    }
}

TEST_CASE("comparison operators for HalfInteger", "[half_integer]")
{
    HalfInt j0(0);
    HalfInt j1(2);
    HalfInt j2(-5);
    HalfInt j3 = j1;

    SECTION("equal to: a == b")
    {
        REQUIRE(j1 == j3);
    }
    SECTION("not equal to: a != b")
    {
        REQUIRE(j1 != j2);
    }
    SECTION("less than: a < b")
    {
        REQUIRE(j2 < j1);
    }
    SECTION("greater than: a > b")
    {
        REQUIRE(j1 > j2);
    }
    SECTION("less than or equal to: a <= b")
    {
    }
    SECTION("greater than or equal to: a >= b")
    {
        REQUIRE(j1 >= j3);
        REQUIRE(j1 >= j2);
    }
    SECTION("boolean conversion")
    {
        REQUIRE(!j0);
        REQUIRE(j1);
        REQUIRE(j2);
    }
}

TEST_CASE("member functions for HalfInteger", "[half_integer]")
{
    HalfInt j1, j2;

    j1.setHalfOf(5);
    REQUIRE(j1.twice() == 5);
    REQUIRE(j1.isHalfInteger());
    REQUIRE(!j1.isInteger());

    j2.setHalfOf(-2);
    REQUIRE(j2.twice() == -2);
    REQUIRE(!j2.isHalfInteger());
    REQUIRE(j2.isInteger());

    auto j = wigner::abs(j1);
    REQUIRE(j.twice() == 5);
    j = wigner::abs(j2);
    REQUIRE(j.twice() == 2);

    j = j1.negate();
    REQUIRE(j.twice() == -5);
    j = j2.negate();
    REQUIRE(j.twice() == 2);
}
