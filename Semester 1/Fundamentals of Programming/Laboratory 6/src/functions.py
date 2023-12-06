#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
from random import randint


"""
Function that get something
1) -get_tuple
"""


def get_tuple(split_commands: list) -> tuple:
    """
    Transform into tuple and makes into int 3 strings
    :param split_commands: Commands from the user
    :return: A tuple
    """
    first_problem, second_problem, third_problem = 1, 2, 3
    return int(split_commands[first_problem]), int(split_commands[second_problem]), int(split_commands[third_problem])


"""
Functions that generate something
1) -get_random_score-
2) -get_participants-
"""


def get_random_score() -> int:
    """
    Generates an int score from 0 -> 10
    :return: A integer
    """
    return randint(0, 10)


def get_participants(compendium_with_scores: list) -> list:
    """
    Creates a list of tuples with 10 participants
    :param compendium_with_scores: contains scores of form (x, y, z)
    :return: new list with contestants
    """
    for i in range(0, 10):
        compendium_with_scores.append((get_random_score(), get_random_score(), get_random_score()))
    return compendium_with_scores


"""
Functions that check properties related to "ADD" implementation
1) -is_int-
2) -is_score-
3) -is_0_to_10-
4) -is_a_valid_add-
"""


def is_int(variable: str):
    """
    Checks if a variable of type string can be converted to int
    :param variable: the string to be checked
    :return: True / Value Error
    """
    try:
        int(variable)
        return True
    except ValueError as ve:
        return False


def is_score(split_commands: list):
    """
    Checks if it's a possible score to be added
    :param split_commands: Commands from the user
    :return: True / Value Error
    """
    for position_of_scores in range(1, 4):
        if is_int(split_commands[position_of_scores]) is False or is_0_to_10(split_commands[position_of_scores]) is False:
            raise ValueError("NOT A SCORE")
    return True


def is_0_to_10(number: str) -> bool:
    """
    Checks if it's meeting the criteria for the score
    :param number: The value introduced
    :return: True / False
    """
    number = int(number)
    return 10 >= number >= 0


def is_a_valid_add(split_commands: list, compendium_with_scores: list):
    """
    Checks if the command from "add" is a valid one
    :param split_commands: Commands from user
    :param compendium_with_scores: Scores of participants
    :return: None / Value Error
    """
    length_of_input, length_of_add, length_of_insert, first_keyword = len(split_commands), 4, 6, 0
    second_keyword, insert_position, length_of_compendium = 4, 5, len(compendium_with_scores)
    if length_of_input < length_of_add:
        raise ValueError("INSERT A VALID ADD COMMAND")
    elif split_commands[first_keyword] == "add" and length_of_input == length_of_add:
        if is_score(split_commands) is False:
            raise ValueError("ADD A VALID SCORE")
    elif length_of_input < length_of_insert:
        raise ValueError("INSERT A VALID ADD COMMAND")
    elif split_commands[first_keyword] == "insert" and split_commands[second_keyword] == "at" and length_of_input == length_of_insert:
        if is_score(split_commands) is False:
            raise ValueError("ADD A VALID SCORE")
        if is_int(split_commands[insert_position]) and is_0_to_10(split_commands[insert_position]) is False or length_of_compendium - 1 < int(split_commands[insert_position]):
            raise ValueError("POSITION GREATER THAN LIST")
    else:
        raise ValueError("ADD A VALID SCORE")


"""
Functions that "ADD" a new participant
1) -do_add_command-
2) -do_insert_command-
"""


def do_add_command(split_commands: list, compendium_of_scores: list, save_solution: list) -> list:
    """
    Adds a new participants to the compendium
    :param save_solution: Stack for undo
    :param split_commands: Commands from the user
    :param compendium_of_scores: Scores of participants
    :return: New list
    """
    compendium_of_scores.append(get_tuple(split_commands))
    save_solution.append(list(compendium_of_scores))
    return compendium_of_scores


def do_insert_command(split_commands: list, compendium_of_scores: list, save_solution: list) -> list:
    """
    Insert a new participants at a given position
    :param save_solution: Stack for undo
    :param split_commands: Commands from the user
    :param compendium_of_scores: Scores of participants
    :return: New list
    """
    compendium_of_scores.append((0, 0, 0))
    key_position_value = 5
    position, length_of_compendium = int(split_commands[key_position_value]), len(compendium_of_scores)
    for participant in range(length_of_compendium - 1, position, - 1):
        compendium_of_scores[participant] = compendium_of_scores[participant - 1]
    compendium_of_scores[position] = get_tuple(split_commands)
    save_solution.append(list(compendium_of_scores))
    return compendium_of_scores


"""
Functions that checks the "MODIFY" command
1) -is_in_participant-
2) -is_a_valid_participant-
3) -is_a_problem-
4) -is_a_valid_modify-
"""


def is_in_participant(position: str, total_participants: int):
    """
    Checks if the position given is a part of the list
    :param position: where we change
    :param total_participants: number of participants
    :return: bool
    """
    if int(position) > total_participants - 1 or int(position) < 0:
        return False
    return True


def is_a_valid_participant(split_commands: list, participants: list, position: int):
    """
    Uses -is_in_participant- and -is_int- (from above) to check if we can use the modify function
    :param split_commands: list with all the commands introduced
    :param participants: list with participants problem scores
    :param position: where we want to modify the score
    :return: None / ValueError
    """
    if is_int(split_commands[position]) is False or is_in_participant(split_commands[position], len(participants)) is False:
        raise ValueError("INVALID MODIFY COMMAND")


def is_a_problem(split_commands: list, position: int):
    """
    Checks if the user selected one of the 3 problem scores at the position it's supposed to
    :param split_commands: commands from user
    :param position: where it's placed in command
    :return: True / ValueError
    """
    if split_commands[position] == "P1" or split_commands[position] == "P2" or split_commands[position] == "P3":
        return True
    raise ValueError("INVALID MODIFY COMMAND")
    
    
def is_a_valid_modify(split_commands: list, participants: list):
    """
    Checks the command given by the user and raises Errors if it's not a valid modify one
    :param split_commands: the user input
    :param participants: list with the scores
    :return: None / ValueError
    """
    keyword_instruction, keyword_remove, keyword_insert = 0, 2, 3
    command_remove_one_element_length, command_remove_multiple_elements_length, command_replace_length = 2, 4, 5
    user_input_length, position_to_modify_one, position_to_modify_two, position_of_problem = len(split_commands), 1, 3, 2
    if user_input_length < command_remove_one_element_length:
        raise ValueError("INSERT A VALID MODIFY COMMAND")
    elif split_commands[keyword_instruction] == "remove" and user_input_length == command_remove_one_element_length:
        is_a_valid_participant(split_commands, participants, position_to_modify_one)
    elif user_input_length < command_remove_multiple_elements_length:
        raise ValueError("INSERT A VALID MODIFY COMMAND")
    elif split_commands[keyword_instruction] == "remove" and split_commands[keyword_remove] == "to" and user_input_length == command_remove_multiple_elements_length:
        is_a_valid_participant(split_commands, participants, position_to_modify_one)
        is_a_valid_participant(split_commands, participants, position_to_modify_two)
    elif user_input_length < command_replace_length:
        raise ValueError("INSERT A VALID MODIFY COMMAND")
    elif split_commands[keyword_instruction] == "replace" and split_commands[keyword_insert] == "with" and user_input_length == command_replace_length:
        is_a_valid_participant(split_commands, participants, position_to_modify_one)
        is_a_problem(split_commands, position_of_problem)
        if is_0_to_10(split_commands[command_replace_length - 1]) is False:
            raise ValueError("MODIFY COMMAND IS WRONG")
    else:
        raise ValueError("MODIFY COMMAND IS WRONG")


"""
Functions that implement the modify of scores
1) -do_remove_command-
2) -do_replace_command-
"""


def do_remove_command(participants: list, user_input: list, save_solution: list):
    """
    Removes (sets to 0) the scores of participant from a starting position to its desired end
    :param save_solution: Stack for undo
    :param participants: list with scores
    :param user_input: list with commands
    :return: New list
    """
    command_start, command_end, user_input_length = 1, 3, len(user_input)
    from_start = int(user_input[command_start])
    if user_input_length == command_end + 1:
        to_finish = int(user_input[command_end]) + 1
    else:
        to_finish = from_start + 1
    for position in range(from_start, to_finish):
        scores = list(participants[position])
        scores, problem_one, problem_two, problem_three = [0, 0, 0], 0, 1, 2
        participants[position] = (scores[problem_one], scores[problem_two], scores[problem_three])
    save_solution.append(list(participants))


def do_replace_command(user_input: list, participants: list, save_solution: list):
    """
    Replaces the score of a problem set from a given participant
    :param save_solution: Stack for undo
    :param user_input: list of commands
    :param participants: list with scores
    :return: New list
    """
    command_place_participant, command_problem_set, command_desired_value = 1, 2, 4
    place_participant, problem_set = int(user_input[command_place_participant]), user_input[command_problem_set]
    desired_value = int(user_input[command_desired_value])
    score, problem_one, problem_two, problem_three = list(participants[place_participant]), 0, 1, 2
    if problem_set == "P1":
        score[problem_one] = desired_value
    elif problem_set == "P2":
        score[problem_two] = desired_value
    elif problem_set == "P3":
        score[problem_three] = desired_value
    participants[place_participant] = (score[problem_one], score[problem_two], score[problem_three])
    save_solution.append(list(participants))


"""
Functions that check the "DISPLAY" command
1) -is_a_comparison-
2) -is_a_valid_display-
"""


def is_a_comparison(user_input: list, position: int):
    """
    Checks if the comparison are present in the command
    :param user_input: list with commands
    :param position: where the comparison is placed
    :return: True or False / bool
    """
    return user_input[position] == "<" or user_input[position] == "=" or user_input[position] == ">"


def is_a_valid_display(user_input: list):
    """
    Checks if the display command is valid
    :param user_input: list with commands
    :return: None / ValueError
    """
    keyword_instruction, keyword_action, keyword_value = 0, 1, 2
    user_input_length = len(user_input)
    command_list_length, command_list_sorted, command_list_with_comparison_length = 1, 2, 3
    if user_input_length < command_list_length:
        raise ValueError("INSERT A VALID DISPLAY COMMAND")
    elif user_input[keyword_instruction] == "list" and user_input_length == command_list_length:
        pass
    elif user_input_length < command_list_sorted:
        raise ValueError("INSERT A VALID DISPLAY COMMAND")
    elif user_input[keyword_instruction] == "list" and user_input[keyword_action] == "sorted" and user_input_length == command_list_sorted:
        pass
    elif user_input_length < command_list_with_comparison_length:
        raise ValueError("INSERT A VALID DISPLAY COMMAND")
    elif user_input[keyword_instruction] == "list" and is_a_comparison(user_input, keyword_action) and user_input_length == command_list_with_comparison_length:
        if is_int(user_input[keyword_value]) is False and is_0_to_10(user_input[keyword_value]) is False:
            raise ValueError("DISPLAY COMMAND IS WRONG")
    else:
        raise ValueError("DISPLAY COMMAND IS WRONG")


"""
Functions that implement the display command
1) -get_average_score-
2) -do_display_list-  // moved to ui.py
3) -do_display_sorted_descending-  // moved to ui.py
4) -do_display_average_score_with_comparison-  // moved to ui.py
"""


def get_average_score(score: tuple):
    """
   Calculates the average score
    :param score: tuple with the scores of the problem sets
    :return: average score
    """
    number_of_problem_sets, average_score = 3, 0
    for element in score:
        average_score = average_score + element
    return average_score / number_of_problem_sets


"""
Functions that check the "ESTABLISH" command
1) -is_0_to_100-
2) -is_a_valid_top-
3) -is_a_valid_establish-
"""


def is_0_to_100(number: str) -> bool:
    """
    Checks if it's meeting the criteria for the score
    :param number: The value introduced
    :return: True / False
    """
    number = int(number)
    return 100 >= number >= 0


def is_a_valid_top(number: str, number_of_participants: int):
    """
    Checks if a podium can be created
    :param number: Numbers of participants to be put on the podium
    :param number_of_participants: total participants
    :return: True / ValueError
    """
    is_int(number)
    number = int(number)
    if number < 0 or number > number_of_participants:
        raise ValueError("NO PODIUM CAN BE CREATED")
    return True


def is_a_valid_establish(user_input: list, participants: list):
    """
    Checks if the command is a valid one
    :param user_input: commands from the user
    :param participants: scores of the problem sets
    :return: None / ValueError
    """
    key_command, key_participant, key_comparison, key_problem, key_value = 0, 1, 1, 2, 2
    input_length, command_top_length, command_top_problem_length, command_remove_length = len(user_input), 2, 3, 3
    total_participants = len(participants)
    if input_length < command_top_length:
        raise ValueError("INSERT A VALID ESTABLISH COMMAND")
    elif user_input[key_command] == "top" and is_a_valid_top(user_input[key_participant], total_participants) and command_top_length == input_length:
        pass
    elif input_length < command_top_problem_length:
        raise ValueError("INSERT A VALID ESTABLISH COMMAND")
    elif user_input[key_command] == "top" and is_a_valid_top(user_input[key_participant], total_participants) and is_a_problem(user_input, key_problem) and command_top_problem_length == input_length:
        pass
    elif user_input[key_command] == "remove" and is_a_comparison(user_input, key_comparison) and is_0_to_100(user_input[key_value]) and command_remove_length == input_length:
        pass
    else:
        raise ValueError("ESTABLISH COMMAND IS WRONG")


"""
Functions that implement the "ESTABLISH" command
1) -get_problem_score-
2) -do_top-  // moved to ui.py
3) -do_top_problem_set-  // moved to ui.py
4) -do_remove-
"""


def get_problem_score(user_input: list, score: tuple):
    """
    Used as a key in sorted
    :param user_input: commands from the user
    :param score: values of the problem set
    :return: one score
    """
    command_problem = 2
    first, second, third = 0, 1, 2
    if user_input[command_problem] == "P1":
        return score[first]
    elif user_input[command_problem] == "P2":
        return score[second]
    elif user_input[command_problem] == "P3":
        return score[third]


def do_remove(participants: list, user_input: list, save_solution: list):
    """
    Removes (sets to 0) all the scores that don't meet the criteria
    :param save_solution: Stack for undo
    :param participants: Score
    :param user_input: commands
    :return: Changes the list
    """
    command_comparison, command_value = 1, 2
    value, problem_sets_length, empty, total_participants = int(user_input[command_value]), 3, 0, len(participants)
    problem_one, problem_two, problem_three = 0, 1, 2
    if user_input[command_comparison] == "=":
        for position in range(total_participants):
            score = participants[position]
            if int(get_average_score(score) * 10) == value:
                score = (empty, empty, empty)
                participants[position] = score
    elif user_input[command_comparison] == "<":
        for position in range(total_participants):
            score = participants[position]
            if int(get_average_score(score) * 10) < value:
                score = (empty, empty, empty)
                participants[position] = score
    elif user_input[command_comparison] == ">":
        for position in range(total_participants):
            score = participants[position]
            if int(get_average_score(score) * 10) > value:
                score = (empty, empty, empty)
                participants[position] = score
    save_solution.append(list(participants))


"""
Function that check the "UNDO" command is valid
1) -is_a_valid_undo-
2) -is_empty-
"""


def is_a_valid_undo(user_input: list, stack_with_past_scores: list):
    """
    Check if empty and the valid command
    :param user_input: commands
    :param stack_with_past_scores: previous scores
    :return: ValueError / None
    """
    keyword = 0
    if user_input[keyword] == "undo":
        pass
    else:
        raise ValueError("INSERT A VALID UNDO COMMAND")
    is_empty(stack_with_past_scores)


def is_empty(stack_with_past_scores: list):
    """
    Checks if the stack has any more values
    :param stack_with_past_scores: list of scores
    :return: None / ValueError
    """
    if len(stack_with_past_scores) == 1:
        raise ValueError("NO MORE UNDO POSSIBLE")
