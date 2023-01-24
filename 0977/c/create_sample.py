#!/usr/bin/env python3

import random
import sys


def main(argv):
    if len(argv) != 3:
        sys.exit("Wrong number of arguments: [sort|rand|dup] n k")

    kind = argv[0]
    assert kind == "sort" or kind == "rand" or kind == "dup"
    n = int(argv[1])
    assert 1 <= n and n <= 2e5
    k = int(argv[2])
    assert 0 <= k and k <= n
    print(f'{n} {k}')

    if kind == "sort":
        for a in range(1, n+1):
            print(f'{a} ', end='')
    elif kind == "rand":
        for a in range(1, n+1):
            rand = random.randint(1, 1e9)
            print(f'{rand} ', end='')
    elif kind == "dup":
        for a in range(1, n+1):
            rand = random.randint(1, 1e9)
            if a % 7 == 0:
                print('1 ', end='')
            elif a % 5 == 0:
                print('1 ', end='')
            elif a % 3 == 0:
                print('1 ', end='')
            else:
                print(f'{rand} ', end='')
    print('')


if __name__ == "__main__":
    main(sys.argv[1:])
