"""
Need to implement:
1)Cocktail Sort
2)Heap Sort
3) A menu - option 1: a list with n random generated numbers
          - option 2: sort by the first algorithm
          - option 3: sort by the second algorithm
          - option 4: print out the set
          - option 0: exit
4)A main function
5)Need to be specific
"""

# We can implement the "random" library, or at least the randint

from random import randint


def main():
    # Instruction
    print("1. Generate a random number")
    print("2. Cocktail Sort")
    print("3. Heap Sort")
    print("4. Print the list")
    # Need to make an empty list
    array_with_numbers = []
    # Making the menu
    while True:
        command_number = input("Insert command number: ")
        if command_number == "1":
            array_with_numbers.append(randint(0, 101))
            # The first command generates random numbers in a list
        elif command_number == "2":
            cocktail_sort(array_with_numbers, int(input("Enter number of steps: ")))
            # The second command sorts the list with the Cocktail Sort
        elif command_number == "3":
            heap_sort(array_with_numbers, int(input("Enter number of steps: ")))
            # The third command sorts the list with the Heap Sort
        elif command_number == "4":
            printing_array(array_with_numbers)
            # The fourth command prints the list
        elif command_number == "0":
            break
            # Exit the menu (program)
        else:
            print("Invalid input!")


def swap_numbers(the_list_to_be_sorted: list, i: int, j: int) -> None:
    """
    :param the_list_to_be_sorted: the array given
    :param i: the position "i" in the array
    :param j: the position "j" in the array
    :return:
    """
    the_list_to_be_sorted[i], the_list_to_be_sorted[j] = the_list_to_be_sorted[j], the_list_to_be_sorted[i]


def printing_array(the_filled_list: list) -> None:
    """
    :param the_filled_list: What we want to print
    :return:
    """
    print(the_filled_list, sep=", ")


def cocktail_sort(the_list_to_be_sorted: list, step: int) -> None:
    """
    :param the_list_to_be_sorted: what the name implies
    :param step: shows the sorting algorithm in action
    :return:
    """
    is_sorted, end = False, len(the_list_to_be_sorted)
    numbers_of_steps, beginning = 0, 0
    while not is_sorted:
        """
        The bubble sort step:
        We do the classic bubble sort algorithm, following it up with a new idea
        """
        is_sorted = True
        for i in range(beginning, end - 1):
            if the_list_to_be_sorted[i] > the_list_to_be_sorted[i + 1]:
                is_sorted = False
                swap_numbers(the_list_to_be_sorted, i + 1, i)
        numbers_of_steps += 1
        end -= 1
        if numbers_of_steps % step == 0 and is_sorted is False:  # Showing the work of the algorithm
            printing_array(the_list_to_be_sorted)
        if is_sorted is True:
            break
        """
        After one step of bubble,
        we go in the opposite order and get the most lower number in the first position
        """
        for i in range(end - 1, beginning, -1):
            if the_list_to_be_sorted[i - 1] > the_list_to_be_sorted[i]:
                swap_numbers(the_list_to_be_sorted, i - 1, i)
        beginning += 1
        numbers_of_steps += 1
        if numbers_of_steps % step == 0 and is_sorted is False:
            printing_array(the_list_to_be_sorted)


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


def heap_sort(the_list_to_be_sorted: list, steps: int) -> None:
    """
    :param the_list_to_be_sorted: what the name implies
    :param steps: shows the sorting algorithm in action
    :return:
    """
    """
    The first for is the part where the list becomes a max heap, while the second
    for makes sure to take the largest element and put it in it's right space in the
    last elements place of the list, and then heapify the new list, these 2 commands repeat
    until the list is sorted.
    """
    number_of_steps = 0
    for j in range((len(the_list_to_be_sorted) - 2) // 2, -1, -1):
        heapify(the_list_to_be_sorted, j, len(the_list_to_be_sorted))
    for end in range(len(the_list_to_be_sorted) - 1, 0, -1):
        swap_numbers(the_list_to_be_sorted, 0, end)
        number_of_steps += 1
        if number_of_steps % steps == 0:
            printing_array(the_list_to_be_sorted)
        heapify(the_list_to_be_sorted, 0, end)


if __name__ == "__main__":
    main()
