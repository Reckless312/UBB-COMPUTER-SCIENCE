import random
#
# Write the implementation for A5 in this file
#
"""
Laboratory 5: Problem 3 - > 10
Naive Implementation: Length and elements of a longest subarray of numbers having increasing modulus.
Dynamic Programming Implementation: The length and elements of a longest increasing subsequence,
                                    when considering each number's real part.
"""
# My own block of instructions

# Functions that check properties


def check_string_to_float(string_of_characters: str) -> bool:
    try:
        float(string_of_characters)
        return True
    except ValueError:
        return False


def is_complex_number(real_part: str, imaginary_part: str) -> bool:
    if check_string_to_float(real_part) is True and check_string_to_float(imaginary_part) is True:
        return True
    return False


# Functions that returns values


def generate_float_number():
    return round(random.uniform(0, 100), 1)
# 
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


def get_real_part(complex_number):
    """
    Using list / dictionary representation
    """
    # return complex_number[0]
    return complex_number["real_part"]


def get_imaginary_part(complex_number):
    """
    Using list / dictionary representation
    """
    # return complex_number[1]
    return complex_number["imaginary_part"]


def add_new_complex_number(storage_of_numbers: list):
    storage_of_numbers.append(read_complex_numbers())


def generate_10_initial_complex_numbers():
    """
    Using list / dictionary representation
    """
    storage_of_numbers, number_of_elements = [], 10
    while number_of_elements > 0:
        real_part = generate_float_number()
        imaginary_part = generate_float_number()
        # storage_of_numbers.append((real_part, imaginary_part))
        storage_of_numbers.append(transform_to_dictionary(generate_float_number(), generate_float_number()))
        number_of_elements = number_of_elements - 1
    return storage_of_numbers


def create_a_new_complex_number(real_part: str, imaginary_part: str):
    if is_complex_number(real_part, imaginary_part):
        return float(real_part), float(imaginary_part)
    raise ValueError("INSERT A CORRECT COMBINATION!")


def transform_into_representation_of_numbers(complex_number):
    """
    Using list / dictionary representation
    """
    # if complex_number[1] < 0:
    #     return "z = " + str(complex_number[0]) + " " + str(complex_number[1]) + " * i"
    # return "z = " + str(complex_number[0]) + " + " + str(complex_number[1]) + " * i"
    if complex_number["imaginary_part"] < 0:
        return "z = " + str(complex_number["real_part"]) + " " + str(complex_number["imaginary_part"]) + " * i"
    return "z = " + str(complex_number["real_part"]) + " + " + str(complex_number["imaginary_part"]) + " * i"


#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
"""
There aren't many functions here because they've been implemented in the list representation part,
but commented.
"""


def create_a_new_complex_number_with_dictionaries(real_part: str, imaginary_part: str):
    if is_complex_number(real_part, imaginary_part):
        return {"real_part": float(real_part), "imaginary_part": float(imaginary_part)}
    raise ValueError("INSERT A CORRECT COMBINATION!")


def transform_to_dictionary(real_part: float, imaginary_part: float):
    return {"real_part": real_part, "imaginary_part": imaginary_part}


#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


"""
3. Length and elements of a longest subarray of numbers having increasing modulus.
"""


def find_modulus(complex_number):
    return get_real_part(complex_number) ** 2 + get_imaginary_part(complex_number) ** 2


def find_the_longest_subarray_with_increasing_modulus(storage_of_numbers: list):
    final_solution, number_of_elements, length_of_storage = [], 0, len(storage_of_numbers)
    for starting_position in range(length_of_storage):
        complex_numbers_found, possible_solution, maximum_modulus = 1, [storage_of_numbers[starting_position]], find_modulus(storage_of_numbers[starting_position])
        current_position = starting_position + 1
        while current_position <= length_of_storage - 1 and find_modulus(storage_of_numbers[current_position]) > maximum_modulus:
            complex_numbers_found, maximum_modulus = complex_numbers_found + 1, find_modulus(storage_of_numbers[current_position])
            possible_solution.append((storage_of_numbers[current_position]))
            current_position = current_position + 1
        if complex_numbers_found > number_of_elements:
            final_solution, number_of_elements = possible_solution, complex_numbers_found
    length_of_solution = len(final_solution)
    call_to_print_answer_to_subarray(final_solution, length_of_solution)


def call_to_print_answer_to_subarray(solution_subarray: list, length_of_subarray: int):
    print_tags()
    print_length_subarray(length_of_subarray)
    print_complex_numbers(solution_subarray)
    print_tags()


"""
10. The length and elements of a longest increasing subsequence, when considering each number's real part
"""


def find_the_longest_increasing_subsequence_considering_the_real_part(storage_of_numbers: list):
    storage_length = len(storage_of_numbers)
    increasing_subsequence_length_at_index = [1] * storage_length
    backtrack_to_solution = [1] * storage_length
    for i in range(storage_length - 2, -1, -1):
        for j in range(i + 1, storage_length):
            if get_real_part(storage_of_numbers[i]) < get_real_part(storage_of_numbers[j]) and increasing_subsequence_length_at_index[i] < increasing_subsequence_length_at_index[j] + 1:
                increasing_subsequence_length_at_index[i] = 1 + increasing_subsequence_length_at_index[j]
                backtrack_to_solution[i] = j
    longest_subsequence, backtrack_index, subsequence_found = 0, 0, []
    for length_of_subsequence in range(storage_length):
        if increasing_subsequence_length_at_index[length_of_subsequence] > longest_subsequence:
            longest_subsequence = increasing_subsequence_length_at_index[length_of_subsequence]
            backtrack_index = length_of_subsequence
    until_the_length_is_equal = 0
    while until_the_length_is_equal < longest_subsequence:
        subsequence_found.append(storage_of_numbers[backtrack_index])
        backtrack_index = backtrack_to_solution[backtrack_index]
        until_the_length_is_equal = until_the_length_is_equal + 1
    call_to_print_answer_to_subsequence(subsequence_found, longest_subsequence)


def call_to_print_answer_to_subsequence(solution_subarray: list, length_of_subarray: int):
    print_tags()
    print_length_subsequence(length_of_subarray)
    print_complex_numbers(solution_subarray)
    print_tags()


#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#


def print_length_subarray(longest_subarray: int):
    print(f"The longest subarray with the property is of size {longest_subarray}")


def print_length_subsequence(longest_subsequence: int):
    print(f"The longest subsequence is of size {longest_subsequence}")


def print_complex_numbers(storage_of_numbers):
    print("Complex numbers: ")
    for complex_number in storage_of_numbers:
        # print(transform_into_representation_of_numbers(complex_number))
        print(transform_into_representation_of_numbers(complex_number))


def print_tags():
    print("#############################")


def read_complex_numbers():
    real_part = input("Desired Real Part: ")
    imaginary_part = input("Desired Imaginary Part: ")
    # return create_a_new_complex_number(real_part, imaginary_part)
    return create_a_new_complex_number_with_dictionaries(real_part, imaginary_part)


def print_menu(command_print: str, command_add: str, command_set_a: str, command_set_b: str, command_close: str):
    print("Choose option:")
    print(f"\t Print the current data / {command_print}")
    print(f"\t Add a new complex number / {command_add}")
    print(f"\t Solve Set A / {command_set_a}")
    print(f"\t Solve Set B / {command_set_b}")
    print(f"\t Exit the program / {command_close}")


def start_application():
    storage_of_numbers = generate_10_initial_complex_numbers()
    print_in_menu, add_in_menu, solve_set_a, solve_set_b, close_the_program = "Print", "Add", "A", "B", "Close"
    print("Starting menu...")
    while True:
        print_menu(print_in_menu, add_in_menu, solve_set_a, solve_set_b, close_the_program)
        desired_option = input("> ")
        if desired_option == print_in_menu:
            print_tags()
            print_complex_numbers(storage_of_numbers)
            print_tags()
        elif desired_option == add_in_menu:
            try:
                add_new_complex_number(storage_of_numbers)
            except ValueError as ve:
                print_tags()
                print(ve)
                print_tags()
        elif desired_option == solve_set_a:
            find_the_longest_subarray_with_increasing_modulus(storage_of_numbers)
        elif desired_option == solve_set_b:
            find_the_longest_increasing_subsequence_considering_the_real_part(storage_of_numbers)
        elif desired_option == close_the_program:
            print("Closing menu...")
            break
        else:
            print("INVALID OPTION!")


if __name__ == "__main__":
    start_application()
