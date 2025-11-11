import random
from sieve import sieve
from gcd_binary import gcd_binary

def find_k(b):
    k = 1
    for prime in sieve(b):
        copy = prime
        while copy <= b:
            k *= prime
            copy *= prime

    return k

def pollard_p1(n, k, b):
    while True:
        a_choices = []
        for i in range(2, b - 1):
            a_choices.append(i)

        while a_choices:
            a = random.choice(a_choices)
            a_choices.remove(a)

            a = pow(a, k, n)

            gcd = gcd_binary(a - 1, n)

            if gcd != 1 and gcd != n:
                return gcd, n // gcd

        b *= 2


if __name__ == "__main__":
    number = 1241143
    bound = 13
    k = find_k(bound)
    gcd, n = pollard_p1(number, k, bound)
    print(gcd, n)