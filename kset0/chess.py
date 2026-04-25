t = int(input())

while t > 0:
    t -= 1
    inp = input().split()
    start = (ord(inp[0]) - ord("A") + 1, int(inp[1]))
    end = (ord(inp[2]) - ord("A") + 1, int(inp[3]))
    start_sum = start[0] + start[1]
    end_sum = end[0] + end[1]
    change_x = end[0] - start[0]
    change_y = end[1] - start[1]

    start_set = set()
    end_set = set()

    directions = [(1, 1), (-1, 1), (1, -1), (-1, -1)]

    if start == end:
        print(f"0 {chr(start[0] + ord('A') - 1)} {start[1]}")
    elif (start_sum % 2) != (end_sum % 2):
        print("Impossible")
    else:

        res = []
        if abs(change_x) == abs(change_y):
            res.append("1")
            res.append(chr(start[0] + ord("A") - 1))
            res.append(start[1])
            res.append(chr(end[0] + ord("A") - 1))
            res.append(end[1])
            print(" ".join(list(map(str, res))))
            exit(0)

        x, y = start[0], start[1]
        a, b = end[0], end[1]
        for dy, dx in directions:
            tmp_x, tmp_y = x, y
            tmp_a, tmp_b = a, b
            while 0 < tmp_x + dx <= 8 and 0 < tmp_y + dy <= 8:
                new_x, new_y = tmp_x + dx, tmp_y + dy
                start_set.add((new_x, new_y))
                tmp_x, tmp_y = new_x, new_y
            while 0 < tmp_a + dx <= 8 and 0 < tmp_b + dy <= 8:
                end_x, end_y = tmp_a + dx, tmp_b + dy
                end_set.add((end_x, end_y))
                tmp_a, tmp_b = end_x, end_y

        valid = list(start_set & end_set)
        one_valid = valid[0]
        res.append(2)
        res.append(chr(start[0] + ord("A") - 1))
        res.append(start[1])
        res.append(chr(one_valid[0] + ord("A") - 1))
        res.append(one_valid[1])
        res.append(chr(end[0] + ord("A") - 1))
        res.append(end[1])
        print(" ".join(list(map(str, res))))
