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

    if (header.find("GAUNT_J_REC") == std::string::npos)
    {
        FAIL("invalid input file: " << input_file_name);
    }

    int j1, j2, m1, m2, jmin0, jmax0, j, jmax;
    double exact;

    wigner::GauntSeriesJ<double> gauntj;

    while (is)
    {
        bool print_err = false;

        if (!(is >> j1 >> j2 >> m1 >> m2 >> jmin0 >> jmax0))
        {
            break;
        }

        INFO("# j1 = " << j1 << ", j2 = " << j2 << ", m1 = " << m1 << ", m2 = "
                       << m2 << ", jmin = " << jmin0 << ", jmax = " << jmax0);

        auto num = static_cast<std::size_t>(jmax0 - jmin0) / 2 + 1;

        gauntj.compute(j1, j2, m1, m2);
        j    = gauntj.nmin();
        jmax = gauntj.nmax();

        CHECK(j == jmin0);
        CHECK(jmax == jmax0);

        while (j <= jmax)
        {
            is >> exact;
            auto val = gauntj.get(j);
            CHECK(val == Approx(exact).epsilon(eps));
            j += 2;
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
