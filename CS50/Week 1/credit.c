#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    long credit_card_number = get_long("Number: ");
    long copy_credit_card_number = credit_card_number;
    bool position = false;
    int sum = 0;
    int total_digits = 0;
    while (copy_credit_card_number != 0)
    {
        int digit = copy_credit_card_number % 10;
        if (position == true)
        {
            digit *= 2;
            while (digit != 0)
            {
                sum += digit % 10;
                digit /= 10;
            }
        }
        else
        {
            sum += digit;
        }
        total_digits++;
        position = !position;
        copy_credit_card_number /= 10;
    }
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    copy_credit_card_number = credit_card_number;
    while (copy_credit_card_number > 99)
    {
        copy_credit_card_number /= 10;
    }
    if (total_digits == 15 && (copy_credit_card_number == 34 || copy_credit_card_number == 37))
    {
        printf("AMEX\n");
        return 0;
    }
    if (total_digits == 16 && (copy_credit_card_number == 51 || copy_credit_card_number == 52 ||
                               copy_credit_card_number == 53 || copy_credit_card_number == 54 ||
                               copy_credit_card_number == 55))
    {
        printf("MASTERCARD\n");
        return 0;
    }
    copy_credit_card_number /= 10;
    if ((total_digits == 13 || total_digits == 16) && copy_credit_card_number == 4)
    {
        printf("VISA\n");
        return 0;
    }
    printf("INVALID\n");
    return 0;
}
