#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

#include <fstream>

#include "wigner/gaunt.hpp"

static const double eps = std::numeric_limits<double>::epsilon() * 100;

std::string input_file_name;

TEST_CASE("Gaunt coefficient: function all args", "[wigner]")
{
    std::ifstream is(input_file_name);

    if (is.fail())
    {
        FAIL("cannot open file " << input_file_name);
    }

    int l1, l2, l3, m1, m2, m3;
    double exact;

    while (is)
    {
        if (!(is >> l1 >> l2 >> l3 >> m1 >> m2 >> m3 >> exact))
        {
            break;
        }

        double val = wigner::gaunt<double>(l1, l2, l3, m1, m2, m3);
        CHECK(val == Approx(exact).epsilon(eps));
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
