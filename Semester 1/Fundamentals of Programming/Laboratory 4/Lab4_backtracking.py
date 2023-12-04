"""
 - Deadline week 5
 - Need to have an iterative + recursive versions
 - Understand complexity
"""

"""
- Problem 4
  Pronosport: "1" -> The first team wins
              "X" -> Draw
              "2" -> The second team wins
  Conditions:
              - Can't choose "X" for the last game
              - Can't be more than 2 values of "1"
  Need to generate all possible alternatives
  
"""


def main():
    """
    Menu
    :return: -> prints the menu and calls the other functions
    """
    print("Welcome to Pronosport")
    print("Insert score options: ")
    list_with_input_options = input_options_for_pronosport_lottery()  # Making our options list
    print("Recursive Backtracking: ")  # We call the backtracking_recursive function
    backtracking_recursive_to_generate_all_possible_alternatives_for_pronosport(list_with_input_options, 4, 0,
                                                                                [0, 0, 0, 0], [0, 0, 0, 0])
    print("Iterative Backtracking: ")  # Calling the iterative version
    backtracking_iterative_to_generate_all_possible_alternatives_for_pronosport(list_with_input_options,
                                                                                4, [0, 0, 0, 0])


def backtracking_recursive_to_generate_all_possible_alternatives_for_pronosport(original_list: list,
                                                                                number_of_games: int, step: int,
                                                                                visited_in_list: list,
                                                                                list_to_be_returned: list) -> None:
    """
    :param original_list:        Our input options
    :param number_of_games:      The length of the list
    :param step:                 Our current step in finding a possible solution
    :param visited_in_list:      We keep in mind every element we already checked
    :param list_to_be_returned:  This is where the solutions are stored
    :return: We print the values
    """
    for i in range(number_of_games):  # We always have 4 games
        if visited_in_list[i] == 0:  # Checking if it's been visited before
            visited_in_list[i] = 1   # If not, we make it visited
            list_to_be_returned[step] = original_list[i]  # Forming the solution
            if step < number_of_games - 1:
                # Recursion:
                backtracking_recursive_to_generate_all_possible_alternatives_for_pronosport(original_list,
                                                                                            number_of_games, step + 1,
                                                                                            visited_in_list,
                                                                                            list_to_be_returned)
            else:
                if verification_test_if_list_is_a_possible_alternative_for_pronosport(list_to_be_returned):
                    print(list_to_be_returned)
            visited_in_list[i] = 0  # Reset the visited value


def verification_test_if_list_is_a_possible_alternative_for_pronosport(list_to_be_tested: list) -> bool:
    """
    :param list_to_be_tested: A solution which is checked if it's ending with "X" or if it has more than 2 values of "1"
    :return: True or False
    """
    if list_to_be_tested[len(list_to_be_tested) - 1] == "X":  # If "X" is on the last position -> False
        return False
    counter_of_number_1 = 0
    for i in range(len(list_to_be_tested)):
        if list_to_be_tested[i] == "1":
            counter_of_number_1 = counter_of_number_1 + 1
    if counter_of_number_1 > 2:  # If the number 1 appears more than 2 times -> False
        return False
    return True


def backtracking_iterative_to_generate_all_possible_alternatives_for_pronosport(original_list: list,
                                                                                numbers_of_games: int,
                                                                                visited_in_list: list) -> None:
    """
    This version uses a lot of extra function that makes sure that we get the correct result but also
    cuts down the duplicates which the recursion version doesn't
    :param original_list: the introduced list
    :param numbers_of_games: the length of the list
    :param visited_in_list: if we used the element before
    :return: we are printing the values
    """
    stack_to_mimic_rec = [(list(original_list), 0, list(visited_in_list))]  # We are using a stack
    all_solutions = []  # Where all the solutions are stored
    while stack_to_mimic_rec:  # Until the stack is empty
        possible_solution, length_of_list, visited_in_list =\
            stack_to_mimic_rec.pop()  # Pop the list with the numbers of elem
        if length_of_list == len(original_list):  # If it's a possible solution
            if verification_test_if_list_is_a_possible_alternative_for_pronosport(possible_solution):
                all_solutions.append(possible_solution)  # Only if it's meets the criteria
        else:
            for i in range(numbers_of_games):  # Simulate the backtracking
                if visited_in_list[i] == 0:
                    visited_in_list[i] = 1
                    possible_solution[length_of_list] = original_list[i]
                    stack_to_mimic_rec.append((list(possible_solution), length_of_list + 1, list(visited_in_list)))
                    visited_in_list[i] = 0
    for every_solution in all_solutions:
        print(every_solution)  # Printing the solutions


def input_options_for_pronosport_lottery() -> list:
    """
    :return: Returning the options list
    """
    list_to_be_returned = []
    for i in range(1, 5):
        while True:
            option = input()
            if option == "1" or option == "X" or option == "2":
                list_to_be_returned.append(option)
                break
            else:
                print("INVALID INPUT, TRY AGAIN")
    return list_to_be_returned


if __name__ == "__main__":
    main()
