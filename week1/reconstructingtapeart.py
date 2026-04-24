from collections import defaultdict


def solve():
    n = int(input())
    arr = list(map(int, input().split()))

    positions = defaultdict(list)

    for i in range(n):
        positions[arr[i]].append(i)

    res = []

    prefix_arr = [0 for _ in range(n + 1)]
    for elem in positions.keys():
        left, right = positions[elem][0], positions[elem][-1]
        prefix_arr[left] += 1
        prefix_arr[right + 1] = -1
    for i in range(1, n + 1):
        prefix_arr[i] += prefix_arr[i - 1]

    for elem in positions.keys():
        left, right = positions[elem][0], positions[elem][-1]
        if prefix_arr[left] != prefix_arr[right]:
            print("IMPOSSIBLE")
            exit(0)
        res.append([left + 1, right + 1, elem])

    print(len(res))
    for item in res:
        print(" ".join(map(str, item)))


if __name__ == "__main__":
    solve()
