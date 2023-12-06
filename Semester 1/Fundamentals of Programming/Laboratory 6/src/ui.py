#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
from functions import *


def do_display_list(participants: list):
    """
    Displays the list
    :param participants: the score of participants
    :return: None
    """
    for score in participants:
        print(score)


def do_display_sorted_descending(participants: list):
    """
    Displays the sorted list by the average score, in descending order
    :param participants: scores of participants
    :return: None
    """
    sorted_participants = participants.copy()
    sorted_participants = sorted(sorted_participants, key=get_average_score, reverse=True)
    for score in sorted_participants:
        print(score)


def do_display_average_score_with_comparison(participants: list, user_input: list):
    """
    Displays the list with a property(<, =, >)
    For convenience this is set for integers via problem statement and examples
    :param participants: scores of participants
    :param user_input: commands from the user
    :return: None
    """
    keyword_comparison, keyword_score = 1, 2
    if user_input[keyword_comparison] == "=":
        for score in participants:
            if int(get_average_score(score)) == int(user_input[keyword_score]):
                print(score)
    elif user_input[keyword_comparison] == ">":
        for score in participants:
            if get_average_score(score) > int(user_input[keyword_score]):
                print(score)
    elif user_input[keyword_comparison] == "<":
        for score in participants:
            if get_average_score(score) < int(user_input[keyword_score]):
                print(score)


def do_top(participants: list, user_input: list):
    """
    Implements the podium of a number of participants
    :param participants: scores
    :param user_input: commands
    :return: None
    """
    command_podium, copy_participants = 1, participants.copy()
    podium_count = int(user_input[command_podium])
    copy_participants = sorted(copy_participants, key=get_average_score, reverse=True)
    for i in range(0, podium_count):
        print(copy_participants[i])


def do_top_problem_set(participants: list, user_input: list):
    """
    Implements the podium for a given problem
    :param participants: scores
    :param user_input: commands
    :return: None
    """
    command_podium, copy_participants = 1, participants.copy()
    podium_count = int(user_input[command_podium])
    copy_participants = sorted(copy_participants, key=lambda score: get_problem_score(user_input, score), reverse=True)
    for i in range(0, podium_count):
        print(copy_participants[i])


def print_tags():
    print("##########################")


def print_value_error(error: ValueError):
    print_tags()
    print(error)
    print_tags()


def print_menu():
    print("Add the result of a new participant:")
    print("\t -> add <P1 score> <P2 score> <P3 score>")
    print("\t -> insert <P1 score> <P2 score> <P3 score> at <position>")
    print("Modify scores:")
    print("\t -> remove <position>")
    print("\t -> remove <start position> to <end position>")
    print("\t -> replace <old score> <P1 | P2 | P3> with <new score>")
    print("Display participants whose score has different properties:")
    print("\t -> list")
    print("\t -> list sorted")
    print("\t -> list [ < | = | > ] <score>")
    print("Establish the podium:")
    print("\t -> top <number>")
    print("\t -> top <number> <P1 | P2 | P3>")
    print("\t -> remove [ < | = | > ] <score>")
    print("Undo:")
    print("\t -> undo")
    print("Exit the program:")
    print("\t -> exit")


def menu():
    contest_participants = get_participants([])
    first_keyword_position, stack_with_past_scores = 0, [list(contest_participants)]
    second_keyword_position, empty, one_element = 1, 0, 1
    while True:
        print_menu()
        command_action = input().split()
        command_length = len(command_action)
        if command_length == empty:
            print("WRONG COMMAND")
        elif command_action[first_keyword_position] == "add":
            try:
                is_a_valid_add(command_action, contest_participants)
                do_add_command(command_action, contest_participants, stack_with_past_scores)
            except ValueError as ve:
                print_value_error(ve)
        elif command_action[first_keyword_position] == "insert":
            try:
                is_a_valid_add(command_action, contest_participants)
                do_insert_command(command_action, contest_participants, stack_with_past_scores)
            except ValueError as ve:
                print_value_error(ve)
        elif command_action[first_keyword_position] == "remove":
            if command_length == one_element:
                print("WRONG COMMAND")
            elif is_a_comparison(command_action, second_keyword_position) is True:
                try:
                    is_a_valid_establish(command_action, contest_participants)
                    do_remove(contest_participants, command_action, stack_with_past_scores)
                except ValueError as ve:
                    print_value_error(ve)
            else:
                try:
                    is_a_valid_modify(command_action, contest_participants)
                    do_remove_command(contest_participants, command_action, stack_with_past_scores)
                except ValueError as ve:
                    print_value_error(ve)
        elif command_action[first_keyword_position] == "replace":
            try:
                is_a_valid_modify(command_action, contest_participants)
                do_replace_command(command_action, contest_participants, stack_with_past_scores)
            except ValueError as ve:
                print_value_error(ve)
        elif command_action[first_keyword_position] == "list":
            try:
                is_a_valid_display(command_action)
                command_list, command_list_sorted, command_list_with_comparison = 1, 2, 3
                if command_length == command_list:
                    do_display_list(contest_participants)
                elif command_length == command_list_sorted:
                    do_display_sorted_descending(contest_participants)
                elif command_length == command_list_with_comparison:
                    do_display_average_score_with_comparison(contest_participants, command_action)
            except ValueError as ve:
                print_value_error(ve)
        elif command_action[first_keyword_position] == "top":
            try:
                is_a_valid_establish(command_action, contest_participants)
                command_top, command_top_problem = 2, 3
                if command_length == command_top:
                    do_top(contest_participants, command_action)
                elif command_length == command_top_problem:
                    do_top_problem_set(contest_participants, command_action)
            except ValueError as ve:
                print_value_error(ve)
        elif command_action[first_keyword_position] == "undo":
            try:
                is_a_valid_undo(command_action, stack_with_past_scores)
                stack_with_past_scores.pop()
                contest_participants = list(stack_with_past_scores[-1])
            except ValueError as ve:
                print_value_error(ve)
        elif command_action[first_keyword_position] == "exit" and command_length == one_element:
            break
        else:
            print("WRONG COMMAND")


if __name__ == "__main__":
    pass
