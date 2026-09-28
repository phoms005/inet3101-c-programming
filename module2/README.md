# Problem Statement

The goal of this assignment is to create a C program that converts a decimal integer into a number in a selected base from 2 to 16. The program uses a function called `to_base_n()` to perform the conversion. Bases outside the range of 2 to 16 should display an error message.

The program also uses a custom alphabet for hexadecimal-style digits. The values 10 through 15 are represented by `!`, `@`, `#`, `$`, `%`, and `^`. Base 8 output must start with `0`, and base 16 output must start with `0x`.

# Describe the Solution

The program asks the user to enter a decimal integer and a target base from 2 to 16. It checks that the base is valid and then uses the `to_base_n()` function to convert the number. The function uses division and remainders to determine each digit and recursion to print the digits in the correct order. A custom digit string is used so that values 10 through 15 are represented by `!`, `@`, `#`, `$`, `%`, and `^`.

# Pros and Cons of the Solution

## Pros
- The program supports bases from 2 to 16.
- The recursive function keeps the conversion logic simple.
- The custom digit string handles values 10 through 15.
- The program checks for invalid bases and displays an error message.

## Cons
- The program only converts one number at a time.
- The program does not repeatedly ask for another number after the first conversion.
- The program does not provide additional input validation if the user enters something that is not a number.
