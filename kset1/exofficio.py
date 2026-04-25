from typing import List


def solve():
    R, C = map(int, input().split())

    res: List[List[str]] = [[" " for _ in range(2 * C + 1)] for _ in range(R + 1)]

    # init
    for col in range(1, 2 * C + 1, 2):
        res[0][col] = "_"
        res[-1][col] = "_"

    res[0][-1] = ""

    for row in range(1, R + 1):
        res[row][0] = "|"
        res[row][-1] = "|"

    # point 1:
    # minimum of maximum gathering time given no addition of walls is R + C - 2.
    # for EVEN number of columns, one caveat, the maximum gathering time is actly
    # R + C - 2 + 1 = R + C - 1
    # If we can create a grid with walls that result in R + C - 2 distance between ANY two nodes, we have built a working algo
    #
    # naive algo
    # for R >= 1:
    #      on the 2i-th line add a full length of "_" except the middle index
    #      put a bunch of vertical lines "|" every 2j-th index <= 2 * C + 1, , on the 2i-th line (zero indexed), from [1, R + 1]
    #      for []

    if R % 2 != 0:
        mid = (R + 1) // 2
        for row in range(1, R + 1):
            if row == mid:
                continue
            for col in range(2, 2 * C, 2):
                res[row][col] = "|"
    else:
        mid = (2 * C + 1) // 2 if C % 2 != 0 else C + 1
        # add "_"
        for row in range(1, R + 1):
            for col in range(1, 2 * C, 2):
                if col == mid:
                    continue
                res[row][col] = "_"

        # if R > 3:
        #     for row in range(2, R, 2):
        #         for col in range(1, 2 * C, 2):
        #             res[row][col] = "_"
        #         res[row][mid] = " "
        #
        # # add "|"
        # if R > 1:
        #     for col in range(2, 2 * C, 2):
        #         res[1][col] = "|"
        # if R == 3:
        #     for col in range(2, 2 * C, 2):
        #         res[3][col] = "|"
        #
        # for row in range(4, R + 1, 2):
        #     for col in range(2, 2 * C, 2):
        #         res[row][col] = "|"

    for line in res:
        print("".join(line))


if __name__ == "__main__":
    solve()
