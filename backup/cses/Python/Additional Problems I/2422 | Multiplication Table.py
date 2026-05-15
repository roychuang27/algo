# Submission ID: 16997253
# Problem: Multiplication Table
# Link: https://cses.fi/problemset/task/2422

import sys


def solve():
    n = int(sys.stdin.readline().strip())

    l, r = 1, n * n
    target = (n * n + 1) // 2

    while l < r:
        mid = (l + r) // 2
        cnt = 0

        for i in range(1, n + 1):
            cnt += min(mid // i, n)

        if cnt >= target:
            r = mid
        else:
            l = mid + 1

    print(l)


if __name__ == "__main__":
    solve()
