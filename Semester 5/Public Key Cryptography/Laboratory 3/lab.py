import random
from sieve import sieve
from gcd_binary import gcd_binary

def find_k(b=13):
    k = 1
    for prime in sieve(b):
        copy = prime
        while copy <= b:
            k *= prime
            copy *= prime

    return k

def pollard_p1(n, k, b=13):
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

        return -1, -1
        # Commenting this next line cause I don't get if the algorithm should go until it finds the factor (it probably won't :< )
        #b *= 2


if __name__ == "__main__":
    number = 12411431
    try:
        bound = int(input("Enter the bound: "))
        k = find_k(bound)
        gcd, n = pollard_p1(number, k, bound)
    except Exception:
        k = find_k()
        gcd, n = pollard_p1(number, k)

    #-1, -1 -> need a better bound
    print(gcd, n)