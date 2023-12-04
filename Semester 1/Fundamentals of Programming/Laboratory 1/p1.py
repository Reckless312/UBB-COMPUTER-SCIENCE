# Solve the problem from the first set here
"""
-Given natural number n, determine the prime numbers p1 and p2 such that n = p1 + p2-
Make a list from number 2,


-The goldbach conjecture -> even numbers can be written as a sum of 2 prime numbers
-Ciurul lui Eratostene for finding out the prime numbers and access them quickly
"""

# We need a main function


def main():
    natural_number = reading()  # Calling the input function
    ciurul_lui_eratostene = []  # Initializing a list
    insert(ciurul_lui_eratostene, natural_number)  # Calling the function that sets up the list with numbers
    remove(ciurul_lui_eratostene)  # Calling the function which removes all the numbers that are not prime
    if printing(ciurul_lui_eratostene, natural_number) == 1:  # A small "Error" if we can't apply the theory
        print("The Goldbach's conjecture doesn't work for this number!")


def reading():
    while True:  # Applied a loop, so we DEFINITELY get a natural number, or an error if people type words...
        x = int(input("Enter natural number: "))
        if x > 0:
            break
    return x


def insert(array: list, number: int):  # I added every number from 2 to the natural number given
    for i in range(2, number + 1):
        array.append(i)
    return


def remove(array: list):  # I applied the "Ciurul lui Eratostene" theory
    for i in array:
        for j in array:
            if j % i == 0 and i != j:
                array.remove(j)
    return


def printing(array: list, number: int):  # Printing out the results
    for i in array:
        for j in array:
            if i + j == number:
                print(f"Number one: {i} and Number two: {j}")
                return 0
    return 1


# Calling the main function

if __name__ == "__main__":
    main()
