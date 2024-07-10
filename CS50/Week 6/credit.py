import re
import cs50


def main():
    number = cs50.get_string("Number: ")

    length = len(number)

    if length not in [13, 15, 16]:
        print("INVALID")
        return 0

    type = find_type(number)

    if type == "INVALID":
        print(type)
        return 0

    sum = luhn_algorithm(int(number))

    if sum % 10 == 0:
        print(type)
    else:
        print("INVALID")


def luhn_algorithm(number):
    position = False

    sum = 0

    while number:
        if position:
            digit = (number % 10) * 2
            while digit:
                sum += digit % 10
                digit = digit // 10
        else:
            sum = sum + number % 10
        position = not position
        number = number // 10

    return sum


def find_type(number):
    type = ""

    amex = re.search("^3[47]", number)

    mastercard = re.search("^5[1-5]", number)

    visa = re.search("^4", number)

    if amex:
        type = "AMEX"
    elif mastercard:
        type = "MASTERCARD"
    elif visa:
        type = "VISA"
    else:
        type = "INVALID"

    return type


main()
