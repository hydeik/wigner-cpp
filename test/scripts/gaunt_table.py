# -*- mode: python -*-
#!/usr/bin/env sage

import sys
from sage.all import *

def usage():
    print("Usage: {0} Lmax [precision]".format(sys.argv[0]))


def gen_gaunt_table(lmax, prec = None):

    tmpl = "{0:4d} {1:4d} {2:4d} {3:4d} {4:4d} {5:5d} {6:23.15e}\n"
    with open("gaunt_lmax{0}".format(lmax), 'w') as out:
        for l1 in range(lmax + 1):
            for l2 in range(lmax + 1):
                for l3 in range(lmax + 1):
                    if (l1 + l2 + l3) % 2 == 1:
                        continue
                    for m1 in range(-l1, l1+1):
                        for m2 in range(-l2, l2+1):
                            for m3 in range(-l3, l3+1):
                                v = gaunt(l1, l2, l3, m1, m2, m3, prec = prec)
                                out.write(tmpl.format(l1, l2, l3, m1, m2, m3,
                                          float(v)))
    return



if __name__ == "__main__":
    if not (len(sys.argv) == 2 or len(sys.argv) == 3):
        usage()
        sys.exit(1)

    prec = None
    if len(sys.argv) == 3:
        prec = int(sys.argv[2])

    lmax = int(sys.argv[1])
    gen_gaunt_table(lmax, prec = prec)
