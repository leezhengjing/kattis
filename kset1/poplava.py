def solve():
    N, X = map(int, input().split())
    visited = [False for _ in range(N + 1)]
    visited[-1] = True
    limit = max(0, int((N - 1) * (N - 2) / 2))
    if X > limit:
        print(-1)
    else:
        res = [N]
        for i in range(1, N - 1):
            if X <= N - 1 - i:
                res.append(N - 1 - X)
                res.append(N - 1)
                visited[N - 1 - X] = True
                visited[N - 1] = True
                break
            res.append(i)
            visited[i] = True
            X -= N - 1 - i
        for i in range(N - 2, 0, -1):
            if visited[i]:
                continue
            res.append(i)
        res = list(map(str, res))
        print(" ".join(res))


if __name__ == "__main__":
    solve()
