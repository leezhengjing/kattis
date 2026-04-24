def solve():
    a, b = input().split()
    a_copy = "".join(sorted(a[:]))
    n = len(a)
    b = int(b)
    if n < 2 * b:
        left, right = n - b, b
        if a[left:right] == a_copy[left:right]:
            print("Yes")
        else:
            print("No")
    else:
        print("Yes")


if __name__ == "__main__":
    solve()
