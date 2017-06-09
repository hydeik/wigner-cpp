#include <fstream>
#include <iostream>

#include <wigner/gaunt.hpp>

// Tolerance
static const double eps = 1.0e-14;

void test_gaunt_coeffs(std::istream& is)
{
    int l1, l2, l3, m1, m2, m3;
    double exact;

    while (is)
    {
        if (!(is >> l1 >> l2 >> l3 >> m1 >> m2 >> m3 >> exact))
        {
            break;
        }

        double val   = wigner::gaunt<double>(l1, l2, l3, m1, m2, m3);
        auto abs_err = std::abs(val - exact);
        auto rel_err = exact == 0.0 ? val : std::abs(abs_err / exact);

        if (abs_err > eps || rel_err > eps)
        {
            std::cerr << "G(" << l1 << ',' << l2 << ',' << l3 << ", " << m1
                      << ',' << m2 << ',' << m3 << "): value     = " << val
                      << ", exact     = " << exact
                      << ", abs_error = " << abs_err
                      << ", rel_error = " << rel_err << '\n';
        }
    }
}

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);
    std::cout.setf(std::ios::showpos);
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
        return 1;
    }

    std::ifstream ifs(argv[1]);
    if (ifs.fail())
    {
        std::cerr << "Error: cannot open file '" << argv[1] << '\''
                  << std::endl;
        return 1;
    }

    test_gaunt_coeffs(ifs);

    return 0;
}
