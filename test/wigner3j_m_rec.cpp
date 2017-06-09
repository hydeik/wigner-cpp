#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

#include <fstream>

#include "wigner/wigner_3nj.hpp"

using HalfInt           = wigner::HalfInteger<int>;
static const double eps = std::numeric_limits<double>::epsilon() * 100;

std::string input_file_name;

TEST_CASE("Wigner 3-j symbol: recursion over m2", "[wigner]")
{
    std::ifstream is(input_file_name);

    if (is.fail())
    {
        FAIL("cannot open file " << input_file_name);
    }

    std::string header;
    std::getline(is, header);

    if (header.find("WIGNER_3J_M_REC") == std::string::npos)
    {
        FAIL("invalid input file: " << input_file_name);
    }

    HalfInt j1, j2, j3, m1, mmin0, mmax0, m, mmax;
    double exact;

    wigner::Wigner3jSeriesM<double, HalfInt> w3j;

    while (is)
    {
        if (!(is >> j1 >> j2 >> j3 >> m1 >> mmin0 >> mmax0))
        {
            break;
        }

        INFO("# j1 = " << j1 << ", j2 = " << j2 << ", j3 = " << j3 << ", m1 = "
                       << m1 << ", mmin = " << mmin0 << ", mmax = " << mmax0);

        auto num = wigner::castTo<std::size_t>(mmax0 - mmin0) + 1;

        w3j.compute(j1, j2, j3, m1);
        m    = w3j.nmin();
        mmax = w3j.nmax();

        CHECK(m == mmin0);
        CHECK(mmax == mmax0);
        while (m <= mmax)
        {
            is >> exact;
            auto val = w3j.get(m);
            CHECK(val == Approx(exact).epsilon(eps));
            ++m;
        }
    }
}

int main(int argc, char* const argv[])
{
    Catch::Session session;

    int return_code = session.applyCommandLine(
        argc, argv, Catch::Session::OnUnusedOptions::Ignore);
    if (return_code != 0)
    {
        return return_code;
    }

    if (session.unusedTokens().empty())
    {
        std::cerr << "usage: " << argv[0]
                  << " <catch options> --<input_file_name>" << std::endl;
        return 1;
    }

    for (auto token : session.unusedTokens())
    {
        input_file_name = token.data;
    }

    return session.run();
}
