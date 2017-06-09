# -*- mode: python -*-
#!/usr/bin/env sage

import sys
from sage.all import *

def usage():
    print("Usage: {0} jmax [prec]".format(sys.argv[0]))


def gen_wigner3j_table_j_recursion(jmax, prec = None):
    # j1, j2, m1, m2, j3min, j3max
    tmpl1 = "{0:5.1f} {1:5.1f} {2:5.1f} {3:5.1f} {4:5.1f} {5:5.1f}\n"
    tmpl2 = "{0:23.15e}\n"
    half = QQ('1/2')
    with open("wigner3j_j_rec_jmax{0}".format(jmax), 'w') as out:
        out.write("WIGNER_3J_J_REC\n")
        j1 = 0
        while j1 <= jmax:
            j2 = 0
            while j2 <= jmax - j1:
                m1 = -j1
                while m1 <= j1:
                    m2 = -j2
                    while m2 <= j2:
                        m3 = -m1 - m2
                        j3 = max(abs(j1 - j2), abs(m3))
                        j3max = j1 + j2
                        out.write(tmpl1.format(float(j1), float(j2),
                                               float(m1), float(m2),
                                               float(j3), float(j3max)))
                        while j3 <= j3max:
                            v = wigner_3j(j1, j2, j3, m1, m2, m3, prec = prec)
                            out.write(tmpl2.format(float(v)))
                            j3 += 1
                        m2 += 1
                    m1 += 1
                j2 += half
            j1 += half

    return


def gen_wigner3j_table_m_recursion(jmax, prec = None):
    # j1, j2, j3, m1, m2min, m2max
    tmpl1 = "{0:5.1f} {1:5.1f} {2:5.1f} {3:5.1f} {4:5.1f} {5:5.1f}\n"
    tmpl2 = "{0:23.15e}\n"
    half = QQ('1/2')

    with open("wigner3j_m_rec_jmax{0}".format(jmax), 'w') as out:
        out.write("WIGNER_3J_M_REC\n")
        j1 = 0
        while j1 <= jmax:
            j2 = 0
            while j2 <= jmax - j1:
                j3 = abs(j1 - j2)
                j3max = min(jmax, j1 + j2)
                while j3 <= j3max:
                    m1 = -j1
                    while m1 <= j1:
                        m2 = max(-j2, -j3-m1)
                        m2max = min(j2, j3-m1)
                        out.write(tmpl1.format(float(j1), float(j2), float(j3),
                                               float(m1), float(m2), float(m2max)))
                        while m2 <= m2max:
                            m3 = -m1 - m2;
                            v = wigner_3j(j1, j2, j3, m1, m2, m3)
                            out.write(tmpl2.format(float(v)))
                            m2 += 1
                        m1 += 1
                    j3 += 1
                j2 += half
            j1 += half
    return


def gen_wigner3j_table_j_recursion_int_only(jmax, prec = None):
    # j1, j2, m1, m2, j3min, j3max
    tmpl1 = "{0:4d} {1:4d} {2:4d} {3:4d} {4:4d} {5:4d}\n"
    tmpl2 = "{0:23.15e}\n"

    with open("wigner3j_j_rec_jmax{0}".format(jmax), 'w') as out:
        out.write("WIGNER_3J_J_REC\n")
        for j1 in xrange(jmax + 1):
            for j2 in xrange(jmax - j1 + 1):
            # for j2 in xrange(0, jmax + 1):
                for m1 in xrange(-j1, j1+1):
                    for m2 in xrange(-j2, j2+1):
                        m3 = -m1 - m2
                        j3min = max(abs(j1 - j2), abs(m3))
                        j3max = j1 + j2
                        # n = j3max - j3min + 1
                        out.write(tmpl1.format(j1, j2, m1, m2, j3min, j3max))
                        for j3 in xrange(j3min, j3max+1):
                            v = wigner_3j(j1, j2, j3, m1, m2, m3, prec = prec)
                            out.write(tmpl2.format(float(v)))
    return


def gen_wigner3j_table_m_recursion_int_only(jmax, prec = None):
    # j1, j2, j3, m1, m2min, m2max
    tmpl1 = "{0:4d} {1:4d} {2:4d} {3:4d} {4:4d} {5:4d}\n"
    tmpl2 = "{0:23.15e}\n"

    with open("wigner3j_m_rec_jmax{0}".format(jmax), 'w') as out:
        out.write("WIGNER_3J_M_REC\n")
        for j1 in xrange(jmax + 1):
            for j2 in xrange(jmax + 1):
                for j3 in xrange(abs(j1 - j2), min(jmax, j1 + j2) + 1):
                    for m1 in xrange(-j1, j1+1):
                        m2min = max(-j2, -j3-m1)
                        m2max = min(j2, j3-m1)
                        out.write(tmpl1.format(j1, j2, j3, m1, m2min, m2max))
                        for m2 in xrange(m2min, m2max + 1):
                            m3 = -m1 - m2;
                            v = wigner_3j(j1, j2, j3, m1, m2, m3)
                            out.write(tmpl2.format(float(v)))
    return


def gen_wigner3j000_table_j_recursion_int_only(jmax, prec = None):
    # j1, j2, m1, m2, j3min, j3max
    tmpl1 = "{0:4d} {1:4d} {2:4d} {3:4d}\n"
    tmpl2 = "{0:23.15e}\n"

    with open("wigner3j000_jmax{0}".format(jmax), 'w') as out:
        out.write("WIGNER_3J_000\n")
        for j1 in xrange(jmax + 1):
            for j2 in xrange(j1, jmax - j1 + 1):
                j3min = abs(j1 - j2)
                j3max = j1 + j2
                out.write(tmpl1.format(j1, j2, j3min, j3max))
                for j3 in xrange(j3min, j3max+1, 2):
                    v = wigner_3j(j1, j2, j3, 0, 0, 0, prec = prec)
                    out.write(tmpl2.format(float(v)))
    return


def gen_gauntpre_table_j_recursion_int_only(jmax, prec = None):
    # j1, j2, m1, m2, j3min, j3max
    tmpl1 = "{0:4d} {1:4d} {2:4d} {3:4d}\n"
    tmpl2 = "{0:23.15e}\n"

    with open("gauntpre_jmax{0}".format(jmax), 'w') as out:
        out.write("GAUNT_PRE_J_REC\n")
        for j1 in xrange(jmax + 1):
            for j2 in xrange(j1, jmax - j1 + 1):
                j3min = abs(j1 - j2)
                j3max = j1 + j2
                out.write(tmpl1.format(j1, j2, j3min, j3max))
                for j3 in xrange(j3min, j3max+1, 2):
                    v = wigner_3j(j1, j2, j3, 0, 0, 0, prec = prec)
                    v *= sqrt((2*j1 + 1) * (2 *j2 + 1) * (2*j3 + 1) / (4 * pi))
                    out.write(tmpl2.format(float(v)))
    return


if __name__ == "__main__":
    if not (len(sys.argv) == 2 or len(sys.argv) == 3):
        usage()
        sys.exit(1)

    prec = None
    if len(sys.argv) == 3:
        prec = int(sys.argv[2])
    jmax = int(sys.argv[1])
    # gen_wigner3j000_table_j_recursion_int_only(jmax, prec)
    gen_wigner3j_table_j_recursion(jmax, prec)
    gen_wigner3j_table_m_recursion(jmax, prec)
    # gen_gauntpre_table_j_recursion_int_only(jmax, prec)
