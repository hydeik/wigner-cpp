#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

#include <fstream>

#include "wigner/gaunt.hpp"

static const double eps = std::numeric_limits<double>::epsilon() * 100;

std::string input_file_name;

TEST_CASE("Gaunt coefficient: recursion over j3", "[wigner]")
{
    std::ifstream is(input_file_name);

    if (is.fail())
    {
        FAIL("cannot open file " << input_file_name);
    }

    std::string header;
    std::getline(is, header);

    if (header.find("GAUNT_M_REC") == std::string::npos)
    {
        FAIL("invalid input file: " << input_file_name);
    }

    int j1, j2, j3, m1, mmin0, mmax0, m, mmax;
    double exact;

    wigner::GauntSeriesM<double> gauntm;

    while (is)
    {
        if (!(is >> j1 >> j2 >> j3 >> m1 >> mmin0 >> mmax0))
        {
            break;
        }

        INFO("# j1 = " << j1 << ", j2 = " << j2 << ", j3 = " << j3 << ", m1 = "
                       << m1 << ", mmin = " << mmin0 << ", mmax = " << mmax0);

        auto num = static_cast<std::size_t>(mmax0 - mmin0) / 2 + 1;

        gauntm.compute(j1, j2, j3, m1);
        m    = gauntm.nmin();
        mmax = gauntm.nmax();
        CHECK(m == mmin0);
        CHECK(mmax == mmax0);

        while (m <= mmax)
        {
            is >> exact;
            auto val = gauntm.get(m);
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
