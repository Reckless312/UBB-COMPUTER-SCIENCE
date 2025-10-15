import datetime
import multiprocessing


def gcd_euclid(x, y):
    x_copy = x
    y_copy = y
    starting_time = datetime.datetime.now()
    if x < 0 or y < 0:
        return -1

    if x == 0:
        if y == 0:
            return -1
        else:
            return y

    while x != y:
        if x > y:
            x = x - y
        else:
            y = y - x

    final_time = datetime.datetime.now()
    print(f"Euclid -> GCD({x_copy}, {y_copy}) = {x} ({(final_time - starting_time).total_seconds() * 1000:.2f} ms)")
    return x, final_time - starting_time

def gcd_modern_euclid(x, y):
    starting_time = datetime.datetime.now()
    if x < 0 or y < 0:
        return -1

    if x == 0:
        if y == 0:
            return -1
        else:
            return y

    while y != 0:
        x, y = y, x % y

    final_time = datetime.datetime.now()
    return x, final_time - starting_time

def gcd_binary (x, y):
    starting_time = datetime.datetime.now()
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

    final_time = datetime.datetime.now()
    return (2 ** d) * x, final_time - starting_time

x = [98765432123456789, 100000000000000003, 922337203685477580, 12345678901234567890, 4294967296, 67280421310721, 982451653, 18446744073709551615, 2305843009213693951, 9999999967]
y = [12345678998765432, 9999999967, 9223372036854775783, 9876543210987654321, 2147483648, 67280421310725, 57885161, 18446744073709551557, 2305843009213693953, 100000000003]




for i in range(len(x)):
    process = multiprocessing.Process(target=gcd_euclid, args=(x[i], y[i]))
    process.start()
    modern_euclid_gcd, modern_euclid_time = gcd_modern_euclid(x[i], y[i])
    binary_gcd, binary_time = gcd_binary(x[i], y[i])
    print(f"Modern Euclid -> GCD({x[i]}, {y[i]}) = {modern_euclid_gcd} ({modern_euclid_time.total_seconds() * 1000:.2f} ms)")
    print(f"Binary -> GCD({x[i]}, {y[i]}) = {binary_gcd} ({binary_time.total_seconds() * 1000:.2f} ms)")
    process.join(timeout=5)
    if process.is_alive():
        print(f"Euclidean -> GCD({x[i]}, {y[i]}) = {x[i]} (timeout)")
        process.terminate()
    print("--------------------------------------------------------------------------------------")