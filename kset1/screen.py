from collections import deque
from typing import Deque
from math import sqrt
from string import digits


def parse(op_queue: Deque[str], num_queue: Deque[int], is_sqrt=False):
    while op_queue:
        symbol = op_queue.popleft()
        first_num, second_num = num_queue.popleft(), num_queue.popleft()
        if symbol == "*":
            num_queue.appendleft(first_num * second_num)
        if symbol == "-" or symbol == "+":
            if op_queue and op_queue[0] == "*":
                _ = op_queue.popleft()
                third_num = num_queue.popleft()
                num_queue.appendleft(second_num * third_num)
                num_queue.appendleft(first_num)
                op_queue.appendleft(symbol)
                continue
            if symbol == "-":
                num_queue.appendleft(first_num - second_num)
            if symbol == "+":
                num_queue.appendleft(first_num + second_num)
    if is_sqrt:
        return int(sqrt(num_queue[0]))
    else:
        return num_queue[0]


def tokenize(arr):
    binop = set(["+", "-", "*"])
    digits_set = set(digits)
    op_queue, num_queue = deque([]), deque([])
    i = 0
    while i < len(arr):
        if arr[i] in binop:
            op_queue.append(arr[i])
            i += 1
            continue
        try:
            left = i
            while (
                i + 1 < len(arr) and arr[i] in digits_set and arr[i + 1] in digits_set
            ):
                i += 1
            num_queue.append(int("".join(arr[left : i + 1])))
            i += 1
        except ValueError:
            i += 1
            pass
    # print(op_queue, num_queue)
    return op_queue, num_queue


def solve():
    R, C = map(int, input().split())
    cols = [[] for _ in range(R)]

    for i in range(R):
        cols[i] = list(input().rstrip("\n"))
    if R == 1:
        op_queue, num_queue = tokenize(cols[0])
        res = parse(op_queue, num_queue)
        print(res)

    elif R == 2:
        _indices = deque([])
        left = 0
        found_left = False

        for right in range(C):
            if cols[0][right] == "_":
                if not found_left:
                    left = right
                    found_left = True
                if right == C - 1 or cols[0][right + 1] != "_":
                    _indices.append((left, right))
                    found_left = False

        for left, right in _indices:
            op_queue, num_queue = tokenize(cols[1][left : right + 1])
            cols[1][left : right + 1] = [
                str(parse(op_queue, num_queue, is_sqrt=True))
            ] + ["" for _ in range(right - left)]

        op_queue, num_queue = tokenize(cols[1])
        res = parse(op_queue, num_queue)
        print(res)

    elif R == 3:
        div_indices = deque([])
        left = 0
        found_left = False

        for right in range(C):
            if cols[1][right] == "=":
                if not found_left:
                    left = right
                    found_left = True
                if right == C - 1 or cols[1][right + 1] != "=":
                    div_indices.append((left, right))
                    found_left = False

        for left, right in div_indices:
            op_queue, num_queue = tokenize(cols[0][left : right + 1])
            top_res = parse(op_queue, num_queue)
            op_queue, num_queue = tokenize(cols[2][left : right + 1])
            bottom_res = parse(op_queue, num_queue)
            cols[1][left : right + 1] = [str(top_res // bottom_res)] + [
                "" for _ in range(right - left)
            ]
        # print(cols[1])
        ## settle sqrts
        _indices = deque([])
        left = 0
        found_left = False

        for right in range(C):
            if cols[0][right] == "_":
                if not found_left:
                    left = right
                    found_left = True
                if right == C - 1 or cols[0][right + 1] != "_":
                    _indices.append((left, right))
                    found_left = False

        for left, right in _indices:
            op_queue, num_queue = tokenize(cols[1][left : right + 1])
            cols[1][left : right + 1] = [
                str(parse(op_queue, num_queue, is_sqrt=True))
            ] + ["" for _ in range(right - left)]
        # print(cols[1])
        op_queue, num_queue = tokenize(cols[1])
        res = parse(op_queue, num_queue)
        print(res)


if __name__ == "__main__":
    solve()
