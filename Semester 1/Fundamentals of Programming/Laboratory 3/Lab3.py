"""
Removed : - "steps" from lab 2
Implemented : - New options to the menu - 1) Best case
                                         - 2) Average case
                                         - 3) Worst case
              - Displaying the duration of the sorting algorithms + the length
Need to be improved : - The design of the code
"""
import timeit
from random import randint


def main():
    # Instruction set 1
    print("1. Best case")
    print("2. Average case")
    print("3. Worst case")
    while True:
        command_case = input("Insert the desired case: ")
        if command_case == "1" or command_case == "2" or command_case == "3":
            break
        print("INVALID INPUT")
    # Instruction set 2
    print("Select sorting algorithm")
    print("1. Cocktail Sort")
    print("2. Heap Sort")
    print("0. Exit")
    # Building the menu
    while True:
        command_number = input("Insert command number: ")
        if command_number == "1":
            printing_time_cocktail_sort(command_case)
        elif command_number == "2":
            printing_time_heap_sort(command_case)
        elif command_number == "0":
            break
        else:
            print("Invalid Input")


def printing_time_cocktail_sort(command_case: str) -> None:
    """
    :param command_case: Best, Average, Worst -> ?
    :return:
    """
    test_list = []
    length = 500
    for i in range(5):
        test_list = creating_lists_for_cocktail_sort(command_case, length)
        time_of_test_list: float = timeit.timeit(stmt='cocktail_sort(the_list_to_be_sorted=test_list)',
                                                 globals={**globals(), **locals()},
                                                 number=10)
        print(f"Time: {time_of_test_list}, length: {length}")
        length = length * 2


def printing_time_heap_sort(command_case: str) -> None:
    """
    :param command_case: Best, Average, Worst -> ?
    :return:
    """
    test_list = []
    length = 500
    for i in range(5):
        test_list = creating_lists_for_heap_sort(command_case, length)
        time_of_test_list: float = timeit.timeit(stmt='heap_sort(the_list_to_be_sorted=test_list)',
                                                 globals={**globals(), **locals()},
                                                 number=10)
        print(f"Time: {time_of_test_list}, length: {length}")
        length = length * 2


def creating_lists_for_cocktail_sort(the_name_of_the_case: str, length_of_list: int) -> list:
    """
    :param length_of_list: length_of_list at the given time
    :param the_name_of_the_case: Best - Average - Worst
    :return:
    """
    created_list = []
    if the_name_of_the_case == "1" or the_name_of_the_case == "Best Case":
        create_list_in_increasing_order(created_list, length_of_list)
    elif the_name_of_the_case == "2" or the_name_of_the_case == "Average case":
        create_list_with_randint(created_list, length_of_list)
    else:
        for i in range(length_of_list, 0, -1):
            created_list.append(i)
    return created_list


def creating_lists_for_heap_sort(the_name_of_the_case: str, length_of_list: int) -> list:
    created_list = []
    if the_name_of_the_case == "1" or the_name_of_the_case == "Best Case":
        for i in range(length_of_list):
            created_list.append(1)
    elif the_name_of_the_case == "2" or the_name_of_the_case == "Average case":
        create_list_with_randint(created_list, length_of_list)
    else:
        create_list_in_increasing_order(created_list, length_of_list)
    return created_list


def create_list_in_increasing_order(created_list: list, length_of_list: int) -> list:
    """
    :param length_of_list: length_of_list at the given time
    :param created_list: Giving them values
    :return:
    """
    for i in range(length_of_list):
        created_list.append(i)
    return created_list


def create_list_with_randint(created_list: list, length_of_list: int) -> list:
    for i in range(length_of_list):
        created_list.append(randint(0, 10000))
    return created_list


def swap_numbers(the_list_to_be_sorted: list, i: int, j: int) -> None:
    """
    :param the_list_to_be_sorted: the array given
    :param i: the position "i" in the array
    :param j: the position "j" in the array
    :return:
    """
    the_list_to_be_sorted[i], the_list_to_be_sorted[j] = the_list_to_be_sorted[j], the_list_to_be_sorted[i]


def cocktail_sort(the_list_to_be_sorted: list) -> None:
    """
    :param the_list_to_be_sorted: what the name implies
    :return:
    """
    swapped = True
    beginning = 0
    end = len(the_list_to_be_sorted) - 1
    while swapped:
        """
        The bubble sort step:
        We do the classic bubble sort algorithm, following it up with a new idea
        """
        swapped = False
        for i in range(beginning, end):
            if the_list_to_be_sorted[i] > the_list_to_be_sorted[i + 1]:
                swapped = True
                swap_numbers(the_list_to_be_sorted, i + 1, i)
        if swapped is False:
            break
        """
        After one step of bubble,
        we go in the opposite order and get the most lower number in the first position
        """
        end -= 1
        for i in range(end - 1, beginning - 1, -1):
            if the_list_to_be_sorted[i] > the_list_to_be_sorted[i + 1]:
                swap_numbers(the_list_to_be_sorted, i + 1, i)
                swapped = True
        beginning += 1


def heapify(the_list_to_be_sorted: list, i: int, upper_bound: int) -> None:
    """
    :param the_list_to_be_sorted: converting the list into a max heap
    :param i: the position i in the heap
    :param upper_bound: the last position which is not sorted
    :return:
    """
    # Iterative version
    """
    This function has the job of transforming the list into a max heap
    Max heap is structure with nodes, where we have terms like parents, children and leaves
    A rule in a max heap is that the parents MUST be bigger than the children so we will
    end up on position 0 with the highest number and then switch it to the last place of
    the list, and we won't consider that element in the next heapify
    """
    while True:
        left_children, right_children = i * 2 + 1, i * 2 + 2  # Formula for the children of the parent node
        if max(left_children, right_children) < upper_bound:
            if the_list_to_be_sorted[i] >= max(the_list_to_be_sorted[left_children],
                                               the_list_to_be_sorted[right_children]):
                break
            elif the_list_to_be_sorted[left_children] > the_list_to_be_sorted[right_children]:
                swap_numbers(the_list_to_be_sorted, i, left_children)
                i = left_children
            else:
                swap_numbers(the_list_to_be_sorted, i, right_children)
                i = right_children
        elif left_children < upper_bound:
            if the_list_to_be_sorted[left_children] > the_list_to_be_sorted[i]:
                swap_numbers(the_list_to_be_sorted, left_children, i)
                i = left_children
            else:
                break
        elif right_children < upper_bound:
            if the_list_to_be_sorted[right_children] > the_list_to_be_sorted[i]:
                swap_numbers(the_list_to_be_sorted, right_children, i)
                i = right_children
            else:
                break
        else:
            break


def heap_sort(the_list_to_be_sorted: list) -> None:
    """
    :param the_list_to_be_sorted: what the name implies
    :return:
    """
    """
    The first for is the part where the list becomes a max heap, while the second
    for makes sure to take the largest element and put it in it's right space in the
    last elements place of the list, and then heapify the new list, these 2 commands repeat
    until the list is sorted.
    """
    for j in range((len(the_list_to_be_sorted) - 2) // 2, -1, -1):
        heapify(the_list_to_be_sorted, j, len(the_list_to_be_sorted))
    for end in range(len(the_list_to_be_sorted) - 1, 0, -1):
        swap_numbers(the_list_to_be_sorted, 0, end)
        heapify(the_list_to_be_sorted, 0, end)


if __name__ == "__main__":
    main()
