# Solve the problem from the third set here

"""
Problem 12 -> age of a person in number of days, from the day of birth to the "current date"
Resources : https://www.w3schools.com/python/python_classes.asp
            https://www.omnicalculator.com/everyday-life/days-old - for the formulas
            We need to make a sum of 3:
            1) From the current day we subtract the number of days from birth
            2) Subtract from current month, the birth month, and, if it's smaller we add 12
            We also subtract 1 from current year if the condition is true
            3) Subtract the years
            --> Before we sum them we need to multiply the month with "30.4" and the years with "365.25"
!! It will only work if the correct numbers / keywords are introduced (year numbers, the name of the months and the day)
"""

# Making a "struct"


class Date:  # Made a "struct" to keep the information together
    def __init__(self, year: int, month: str, day: int):
        self.year = year
        self.month = month
        self.day = day


def main():
    birth_date = Date(year=int(input("Birth_Date Year: ")), month=input("Birth_Date Month: "),
                      day=int(input("Birth_Date Day: ")))  # Initializing the first set
    current_date = Date(year=int(input("Current_Day Year: ")), month=input("Current_Day Month: "),
                        day=int(input("Current_Day Day: ")))  # Initializing the second set
    months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October",
              "November", "December"]
    subtract_days = current_date.day - birth_date.day  # The first subtract
    month1 = find(birth_date.month, months)  # Assigning the number of each month, starting from 0
    month2 = find(current_date.month, months)
    if month2 < month1:  # Treating the special case
        month2 += 12
        current_date.year -= 1
    subtract_months = month2 - month1
    subtract_years = current_date.year - birth_date.year  # The rest of subtraction
    subtract_months *= 30.4
    subtract_years *= 365.25  # Multiplying the values
    total_days = int(subtract_days + subtract_months + subtract_years)  # The result
    print(f"You lived for {total_days}")


def find(x: str, array: list):  # Finding the number of the month
    for i in range(0, 12):
        if array[i] == x:
            return i


if __name__ == "__main__":
    main()
