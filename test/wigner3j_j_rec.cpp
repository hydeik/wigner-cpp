#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

#include <fstream>

#include "wigner/wigner_3nj.hpp"

using HalfInt           = wigner::HalfInteger<int>;
static const double eps = std::numeric_limits<double>::epsilon() * 100;

std::string input_file_name;

TEST_CASE("Wigner 3-j symbol: recursion over j3", "[wigner]")
{
    std::ifstream is(input_file_name);

    if (is.fail())
    {
        FAIL("cannot open file " << input_file_name);
    }

    std::string header;
    std::getline(is, header);

    if (header.find("WIGNER_3J_J_REC") == std::string::npos)
    {
        FAIL("invalid input file: " << input_file_name);
    }

    HalfInt j1, j2, m1, m2, jmin0, jmax0, j, jmax;
    double exact;
    wigner::Wigner3jSeriesJ<double, HalfInt> w3j;

    int status = 0; // 0: success, 1: failed
    while (is)
    {
        if (!(is >> j1 >> j2 >> m1 >> m2 >> jmin0 >> jmax0))
        {
            break;
        }

        // msg.str("");
        INFO("# j1 = " << j1 << ", j2 = " << j2 << ", m1 = " << m1 << ", m2 = "
                       << m2 << ", jmin =  " << jmin0 << ", jmax = " << jmax0);

        auto num = wigner::castTo<std::size_t>(jmax0 - jmin0) + 1;
        w3j.compute(j1, j2, m1, m2);
        j    = w3j.nmin();
        jmax = w3j.nmax();

        CHECK(j == jmin0);
        CHECK(jmax == jmax0);

        while (j <= jmax)
        {
            is >> exact;
            auto val = w3j.get(j);
            CHECK(val == Approx(exact).epsilon(eps));
            ++j;
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
