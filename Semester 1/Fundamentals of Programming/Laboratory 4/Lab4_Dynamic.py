"""
- Deadline week 6
- Need to implement "the naive way" and then the dynamic programming way
- Need to display the data structure which memorizes the results
- Understand complexity
"""

"""
- Problem 2
- Given the set of positive integers S and the natural number k, display one of the subsets of S which sum to k.
  For example, if S = { 2, 3, 5, 7, 8 } and k = 14, subset { 2, 5, 7 } sums to 14.
"""


def using_bit_manipulation_to_find_a_subset_which_is_equal_to_the_sum_given(the_entire_set: list,
                                                                            length_of_the_original_set: int, sum_to_be_found: int):
    """
    Using the bit manipulation method, we consider "1" if the i / j th element is included and "0" if it's excluded
    Possibilities: 2 ^ n - 1
    """
    for i in range(1 << length_of_the_original_set):
        solution_for_a_subset, sum_of_the_current_subset = [], 0
        for j in range(length_of_the_original_set):
            if (i & (1 << j)) != 0:
                solution_for_a_subset.append(the_entire_set[j])
        for current_element in solution_for_a_subset:
            sum_of_the_current_subset = sum_of_the_current_subset + current_element
        if sum_of_the_current_subset == sum_to_be_found:
            print(f"Solution by bit manipulation: {solution_for_a_subset}")
            return None


def printing_the_subset_equal_to_the_given_sum_using_the_truth_table(truth_table_for_all_numbers_less_or_equal_to_sum,
                                                                     the_original_set_with_numbers: list,
                                                                     length_of_the_original_set: int, sum_to_be_found) -> None:
    """
    Backtrack to possible solution from the truth table, keeping in mind all the variables
    """
    if truth_table_for_all_numbers_less_or_equal_to_sum[length_of_the_original_set][sum_to_be_found] == 0:
        print("SUM IS IMPOSSIBLE")
        return None
    current_position_in_the_row, current_position_in_the_column = length_of_the_original_set, sum_to_be_found
    all_of_the_subsets_of_the_set = []
    while current_position_in_the_row > 0 and current_position_in_the_column > 0:
        if truth_table_for_all_numbers_less_or_equal_to_sum[current_position_in_the_row - 1][current_position_in_the_column]:
            current_position_in_the_row = current_position_in_the_row - 1
        else:
            all_of_the_subsets_of_the_set.append(the_original_set_with_numbers[current_position_in_the_row - 1])
            current_position_in_the_column = current_position_in_the_column - the_original_set_with_numbers[current_position_in_the_row - 1]
            current_position_in_the_row = current_position_in_the_row - 1
    for i in range(0, length_of_the_original_set):
        print(truth_table_for_all_numbers_less_or_equal_to_sum[i])
    print(f"Solution by dynamic programming: {all_of_the_subsets_of_the_set}")
    return None


def creating_truth_table_if_the_sum_of_numbers_less_or_equal_to_the_given_sum_is_found(the_original_set_with_numbers: list,
                                                                                       length_of_the_original_set: int,
                                                                                       sum_to_be_found: int) -> list:
    """
    Making a length * sum table with True / False
    """
    truth_table_for_all_numbers_less_or_equal_to_sum = ([[False for i in range(0, sum_to_be_found + 1)]
                                                         for i in range(0, length_of_the_original_set + 1)])
    for i in range(0, length_of_the_original_set + 1):
        truth_table_for_all_numbers_less_or_equal_to_sum[i][0] = True
    for i in range(1, sum_to_be_found + 1):
        truth_table_for_all_numbers_less_or_equal_to_sum[0][i] = False
    for i in range(1, length_of_the_original_set + 1):
        for j in range(1, sum_to_be_found + 1):
            if j < the_original_set_with_numbers[i - 1]:
                truth_table_for_all_numbers_less_or_equal_to_sum[i][j] = truth_table_for_all_numbers_less_or_equal_to_sum[i - 1][j]
            else:
                truth_table_for_all_numbers_less_or_equal_to_sum[i][j] = (truth_table_for_all_numbers_less_or_equal_to_sum[i - 1][j]
                                                                          or truth_table_for_all_numbers_less_or_equal_to_sum[i - 1][j - the_original_set_with_numbers[i - 1]])
    return truth_table_for_all_numbers_less_or_equal_to_sum


def reading_the_set_with_positive_integers_for_finding_subsets(size_of_the_desired_set: int) -> list:
    """
    Input list
    """
    list_to_be_returned_for_the_set = []
    for i in range(size_of_the_desired_set):
        list_to_be_returned_for_the_set.append(int(input()))
    return list_to_be_returned_for_the_set


def main():
    length_of_the_set = int(input("Length of list = "))
    print("Insert the desired set: ")
    set_with_positive_integers = reading_the_set_with_positive_integers_for_finding_subsets(length_of_the_set)
    the_desired_sum_to_be_found = int(input("Sum: "))
    truth_table_for_solution = creating_truth_table_if_the_sum_of_numbers_less_or_equal_to_the_given_sum_is_found(set_with_positive_integers,
                                                                                                                  length_of_the_set,
                                                                                                                  the_desired_sum_to_be_found)
    printing_the_subset_equal_to_the_given_sum_using_the_truth_table(truth_table_for_solution, set_with_positive_integers,
                                                                     length_of_the_set, the_desired_sum_to_be_found)
    using_bit_manipulation_to_find_a_subset_which_is_equal_to_the_sum_given(set_with_positive_integers, length_of_the_set, the_desired_sum_to_be_found)


if __name__ == "__main__":
    main()
