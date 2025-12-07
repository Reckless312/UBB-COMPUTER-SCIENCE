def gcd_binary (x, y):
    if x < 0 or y < 0:
        return -1

    if x == 0:
        if y == 0:
            return -1
        else:
            return y

    d = 0

    while x % 2 == 0 and y % 2 == 0:
        x = x // 2
        y = y // 2
        d += 1

    while x % 2 == 0:
        x = x // 2

    while y % 2 == 0:
        y = y // 2

    while x != y:
        if x > y:
            x = x - y
            while x % 2 == 0:
                x = x // 2
        else:
            y = y - x
            while y % 2 == 0:
                y = y // 2

    return (2 ** d) * x