# Solve the problem from the second set here

"""
Problem 6 -> Calendar date, 2 integers, a year and a day, have to figure out what day / month / year we are in
Need to keep in mind the years that 4 divides to +++ that not every start of a century is a leap year

"""


def main():
    print("Enter the year: ")
    year = reading()
    print("Enter the number of days: ")
    day = reading()
    month = "Empty"
    year, day = fast_forward(year, day)  # Tells us what year we are in + the remaining days
    months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October",
              "November", "December"]  # A list with all the months to access them quickly
    days_months = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]  # The amount of days in each month
    year, month, day = calculate(year, day, months, days_months, month)  # Calculates the values
    print(year, month, day)  # Printing the answers
    return 0


def reading():  # A simple reading function
    x = int(input())
    return x


def fast_forward(year: int, day: int):
    while True:
        if (year % 4 == 0 and year % 100 != 0) or year % 400 == 0:  # A condition that finds out leap years
            if day <= 366:
                break
            day -= 366  # Subtracting 366 if it's a leap year
        else:
            if day <= 365:
                break
            day -= 365  # Subtracting 365 if it's a regular year
        year += 1
    return year, day  # Return both values


def calculate(year: int, day: int, months: list, days_months: list, month: str):  # We calculate the day of the month
    if year % 4 == 0:                                                            # And the month itself
        days_months[1] += 1  # Adding up for February
    for i in range(0, 12):
        if days_months[i] >= day:
            month = months[i]
            break
        day -= days_months[i]
    return year, month, day  # Returns all the values


# Calling main
if __name__ == "__main__":
    main()
