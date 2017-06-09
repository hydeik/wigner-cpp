# -*- mode: python -*-
#!/usr/bin/env sage

import sys
from sage.all import *

def usage():
    print("Usage: {0} Lmax [precision]".format(sys.argv[0]))


def gen_gaunt_table_j_recursion(lmax, prec = None):

    tmpl1 = "{0:4d} {1:4d} {2:4d} {3:4d} {4:4d} {5:5d}\n"
    tmpl2 = "{0:23.15e}\n"
    with open("gaunt_j_rec_lmax{0}".format(lmax), 'w') as out:
        out.write("GAUNT_J_REC\n")
        for l1 in xrange(lmax + 1):
            for l2 in xrange(l1, lmax - l1 + 1):
                for m1 in xrange(-l1, l1+1):
                    for m2 in xrange(-l2, l2+1):
                        m3 = -m1 - m2
                        l3min = max(abs(l1 - l2), abs(m3))
                        l3max = l1 + l2
                        if (l3min + l3max) % 2 == 1:
                            l3min += 1
                        out.write(tmpl1.format(l1, l2, m1, m2, l3min, l3max))
                        for l3 in xrange(l3min, l3max+1, 2):
                            v = gaunt(l1, l2, l3, m1, m2, m3, prec = prec)
                            out.write(tmpl2.format(float(v)))
    return


def gen_gaunt_table_m_recursion(lmax, prec = None):

    tmpl1 = "{0:4d} {1:4d} {2:4d} {3:4d} {4:4d} {5:5d}\n"
    tmpl2 = "{0:23.15e}\n"
    with open("gaunt_m_rec_lmax{0}".format(lmax), 'w') as out:
        out.write("GAUNT_M_REC\n")
        for l1 in xrange(lmax + 1):
            for l2 in xrange(l1, lmax - l1 + 1):
                for l3 in xrange(abs(l1-l2), min(l1 + l2, lmax) + 1, 2):
                    for m1 in xrange(-l1, l1+1):
                        m2min = max(-l2, -l3-m1)
                        m2max = min(l2, l3-m1)
                        out.write(tmpl1.format(l1, l2, l3, m1, m2min, m2max))
                        for m2 in xrange(m2min, m2max + 1):
                            m3 = -m1 - m2;
                            v = gaunt(l1, l2, l3, m1, m2, m3)
                            out.write(tmpl2.format(float(v)))
    return


if __name__ == "__main__":
    if not (len(sys.argv) == 2 or len(sys.argv) == 3):
        usage()
        sys.exit(1)

    prec = None
    if len(sys.argv) == 3:
        prec = int(sys.argv[2])

    lmax = int(sys.argv[1])
    gen_gaunt_table_j_recursion(lmax, prec = prec)
    gen_gaunt_table_m_recursion(lmax, prec = prec)
