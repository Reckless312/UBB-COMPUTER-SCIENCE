import random
from dataclasses import dataclass
from typing import Tuple, List
from gcd import gcd_binary
from sieve import sieve

def create_alphabet():
    return {
        "_" : 0,
        "A" : 1,
        "B" : 2,
        "C" : 3,
        "D" : 4,
        "E" : 5,
        "F" : 6,
        "G" : 7,
        "H" : 8,
        "I" : 9,
        "J" : 10,
        "K" : 11,
        "L" : 12,
        "M" : 13,
        "N" : 14,
        "O" : 15,
        "P" : 16,
        "Q" : 17,
        "R" : 18,
        "S" : 19,
        "T" : 20,
        "U" : 21,
        "V" : 22,
        "W" : 23,
        "X" : 24,
        "Y" : 25,
        "Z" : 26
}

def create_reversed_alphabet(alphabet):
    reversed_alphabet = {}
    for key, value in alphabet.items():
        reversed_alphabet[value] = key
    return reversed_alphabet


def generate_prime(min_value = 1000, max_value = 5000):
    sieve_list = sieve(max_value)

    for prime in sieve_list:
        if prime < min_value:
            sieve_list.remove(prime)

    return random.choice(sieve_list)


def get_prime_factors(n):
    prime_factors = []

    prime_numbers = sieve(n)

    for prime in prime_numbers:
        if n % prime == 0:
            prime_factors.append(prime)
            n = n // prime

    return prime_factors



def get_generator(p, n):
    prime_factors = get_prime_factors(n)

    possible_g_values = []

    for i in range(2, n):
        possible_g_values.append(i)

    while possible_g_values:
        g = random.choice(possible_g_values)
        possible_g_values.remove(g)

        is_generator = True
        for factor in prime_factors:
            a = pow(g, n // factor, p)
            if a == 1:
                is_generator = False
                break

        if is_generator:
            return g

    return -1


@dataclass
class ElGamalPublicKey:
    p: int  # large prime
    g: int  # generator
    y: int  # g^x mod p


@dataclass
class ElGamalPrivateKey:
    p: int
    g: int
    x: int  # secret exponent


def generate_keys() -> Tuple[ElGamalPublicKey, ElGamalPrivateKey]:
    p = generate_prime()
    n = p - 1
    g = get_generator(p, n)
    a = random.randint(2, p - 1)
    g_to_a = pow(g, a, p)

    public_key = ElGamalPublicKey(p=p, g=g, y=g_to_a)
    private_key = ElGamalPrivateKey(p=p, g=g, x=a)
    return public_key, private_key


def encrypt_char(m: int, public_key: ElGamalPublicKey) -> Tuple[int, int]:
    """
    Encrypt a single symbol (integer m) using ElGamal.
    Returns a pair (a, b) = (g^k mod p, m * y^k mod p).
    """
    if not (0 <= m < ALPHABET_SIZE):
        raise ValueError("Plaintext symbol outside alphabet range")

    p, g, y = public_key.p, public_key.g, public_key.y
    k = random.randrange(2, p - 1)  # ephemeral secret
    a = pow(g, k, p)
    b = (m * pow(y, k, p)) % p
    return a, b


def decrypt_char(a: int, b: int, private_key: ElGamalPrivateKey) -> int:
    """
    Decrypt a single symbol given (a, b) and the private key.
    m = b * (a^x)^(-1) mod p
    """
    p, x = private_key.p, private_key.x
    s = pow(a, x, p)
    s_inv = modinv(s, p)
    m = (b * s_inv) % p
    return m


def encrypt_text(plaintext: str, public_key: ElGamalPublicKey) -> List[Tuple[int, int]]:
    """
    Encrypt a plaintext string using the 27-character alphabet.
    Returns a list of ciphertext pairs (a_i, b_i).
    """
    symbols = text_to_numbers(plaintext)
    return [encrypt_char(m, public_key) for m in symbols]


def decrypt_text(ciphertext: List[Tuple[int, int]], private_key: ElGamalPrivateKey) -> str:
    """Decrypt a list of (a, b) pairs to recover the plaintext string."""
    symbols = [decrypt_char(a, b, private_key) for a, b in ciphertext]
    return numbers_to_text(symbols)


def validate_plaintext(text: str) -> bool:
    """Return True iff all characters are in the allowed 27-character alphabet."""
    try:
        _ = text_to_numbers(text)
        return True
    except ValueError:
        return False


def validate_ciphertext(ciphertext: List[Tuple[int, int]], p: int) -> bool:
    """
    Basic ciphertext validation:
    - each element is a pair of integers
    - 0 <= a, b < p
    """
    try:
        for a, b in ciphertext:
            if not (0 <= a < p and 0 <= b < p):
                return False
    except Exception:
        return False
    return True


def format_ciphertext(ciphertext: List[Tuple[int, int]]) -> str:
    """
    Represent ciphertext as a human-readable string: '(a1,b1)|(a2,b2)|...'.
    Useful for printing and manual copying.
    """
    return "|".join(f"({a},{b})" for a, b in ciphertext)


def parse_ciphertext(s: str) -> List[Tuple[int, int]]:
    """
    Parse ciphertext from the format produced by format_ciphertext().
    Example input: '(123,456)|(789,101)'
    """
    s = s.strip()
    if not s:
        return []
    parts = s.split("|")
    result: List[Tuple[int, int]] = []
    for part in parts:
        part = part.strip()
        if not (part.startswith("(") and part.endswith(")")):
            raise ValueError(f"Invalid ciphertext block: {part!r}")
        a_str, b_str = part[1:-1].split(",")
        result.append((int(a_str), int(b_str)))
    return result


def demo_cli() -> None:
    """
    Very simple command-line interface for demonstration and testing.
    """
    print("=== ElGamal (basic version) over 27-character alphabet ===")
    public_key, private_key = generate_keys()
    print(f"Public key:  p = {public_key.p}, g = {public_key.g}, y = {public_key.y}")
    print(f"Private key: x = {private_key.x}")
    print()

    while True:
        print("Choose an option:")
        print(" 1) Encrypt a plaintext")
        print(" 2) Decrypt a ciphertext")
        print(" 3) Exit")
        choice = input("Your choice: ").strip()

        if choice == "1":
            plaintext = input("Enter plaintext (allowed: space + A-Z): ")
            if not validate_plaintext(plaintext):
                print("Error: plaintext contains invalid characters.")
                continue
            ct = encrypt_text(plaintext, public_key)
            print("Ciphertext pairs:")
            print(format_ciphertext(ct))
            print()
        elif choice == "2":
            s = input("Enter ciphertext in format '(a1,b1)|(a2,b2)|...': ")
            try:
                ct = parse_ciphertext(s)
            except ValueError as e:
                print(f"Error while parsing ciphertext: {e}")
                continue
            if not validate_ciphertext(ct, private_key.p):
                print("Error: ciphertext values are out of range.")
                continue
            pt = decrypt_text(ct, private_key)
            print(f"Recovered plaintext: {pt!r}")
            print()
        elif choice == "3":
            print("Goodbye.")
            break
        else:
            print("Invalid choice, please try again.\n")


if __name__ == "__main__":
    demo_cli()

