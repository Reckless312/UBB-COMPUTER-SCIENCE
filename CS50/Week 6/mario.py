from cs50 import get_int


def main():
    x = None

    while True:
        x = get_int("Height: ")
        if x >= 1 and x <= 8:
            break

    for i in range(x):
        PrintLevel(x, i)


def PrintBlocks(x, i):
    print("#" * (i + 1), end="")


def PrintSpace(x, i):
    print(" " * (x - (i + 1)), end="")


def PrintLevel(x, i):
    PrintSpace(x, i)
    PrintBlocks(x, i)
    print("  ", end="")
    PrintBlocks(x, i)
    print()


main()
