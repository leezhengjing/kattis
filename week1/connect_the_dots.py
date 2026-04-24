import sys
from string import digits, ascii_letters


def solve(grid):
    positions = {}
    n, m = len(grid), len(grid[0])
    alnums = digits + ascii_letters
    alnums_set = set(alnums)
    next_key = {alnums[i]: alnums[i + 1] for i in range(len(alnums) - 1)}
    for i in range(n):
        for j in range(m):
            if grid[i][j].isalnum():
                positions[grid[i][j]] = (i, j)

    for key in positions.keys():
        if key in next_key and next_key[key] in positions:
            curr_row, curr_col = positions[key]
            next_row, next_col = positions[next_key[key]]
            if curr_row != next_row and curr_col != next_col:
                continue
            for i in range(min(curr_row, next_row) + 1, max(curr_row, next_row)):
                if grid[i][curr_col] in alnums_set or grid[i][curr_col] == "+":
                    continue
                if grid[i][curr_col] == "-":
                    grid[i][curr_col] = "+"
                else:
                    grid[i][curr_col] = "|"
            for j in range(min(curr_col, next_col) + 1, max(curr_col, next_col)):
                if grid[curr_row][j] in alnums_set or grid[curr_row][j] == "+":
                    continue
                if grid[curr_row][j] == "|":
                    grid[curr_row][j] = "+"
                else:
                    grid[curr_row][j] = "-"

    for row in grid:
        print("".join(row))


if __name__ == "__main__":
    curr_grid = []
    for line in sys.stdin:
        line = line.rstrip()
        if line == "":
            if curr_grid:
                solve(curr_grid)
                print()
                curr_grid = []
        else:
            curr_grid.append(list(line))

    if curr_grid:
        solve(curr_grid)
