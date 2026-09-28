#include <stdio.h>

void to_base_n(unsigned long n, int base);

int main(void)
{
    unsigned long number;
    int base;

    printf("Enter an integer: ");
    scanf("%lu", &number);

    printf("Enter a base (2-16): ");
    scanf("%d", &base);

    if (base < 2 || base > 16)
    {
        printf("Error: base must be between 2 and 16.\n");
        return 1;
    }
    else if (base == 8)
        printf("0");
    else if (base == 16)
        printf("0x");

    to_base_n(number, base);

    putchar('\n');

    return 0;
}

void to_base_n(unsigned long n, int base)
{
    int remainder;
    char digits[] = "0123456789!@#$%^";

    remainder = n % base;

    if (n >= base)
        to_base_n(n / base, base);

    putchar(digits[remainder]);
}
