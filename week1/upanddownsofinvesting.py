import sys


def solve():
    s, n, m = map(int, input().split())
    arr = []
    for line in sys.stdin:
        arr.extend(list(map(int, line.split())))

    origin, peak_idx, valley_idx = 0, 0, 0
    increasing = False

    peak_count, valley_count = 0, 0

    visited = set()
    for i in range(1, s):
        if arr[i] > arr[i - 1]:
            if not increasing:
                increasing = True
                valley_idx = i - 1
                origin = peak_idx
            if (
                (valley_idx - origin + 1) >= m
                and (i - valley_idx + 1) >= m
                and valley_idx not in visited
            ):
                visited.add(valley_idx)
                valley_count += 1

        if arr[i] < arr[i - 1]:
            if increasing:
                increasing = False
                peak_idx = i - 1
                origin = valley_idx
            if (
                (peak_idx - origin + 1) >= n
                and (i - peak_idx + 1) >= n
                and peak_idx not in visited
            ):
                visited.add(peak_idx)
                peak_count += 1

    print(peak_count, valley_count)


if __name__ == "__main__":
    solve()
