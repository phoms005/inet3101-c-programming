# Module 6: GNU Coreutils Modifications

## Problem Statement

The goal of this assignment is to modify two GNU Coreutils programs, `ls` and `whoami`.

By default, `ls` displays filenames in a short format. The requested modification changes the default output to a long listing, similar to running `ls -l`, displaying file permissions, ownership, file size, timestamps, and filenames.

The `whoami` program normally prints only the username of the current effective user. The requested modification adds the prefix `You are: ` before the username.

## Describe the Solution

### 1. Modified `ls.c`

The default output format was changed to `long_format`. This allows the program to display detailed file information without requiring the user to specify the `-l` option.

The modified program was rebuilt and tested. Running `ls` displayed the long listing by default.

### 2. Modified `whoami.c`

The original output statement was replaced with:

`printf ("You are: %s\n", pw->pw_name);`

This prints the text `You are: ` followed by the username of the current effective user.

The modified program was rebuilt and tested. Running `whoami` produced `You are: lucas` in the current Linux environment.

## Pros and Cons of your solution

### Pros
- The `ls` program displays useful file details by default.
- The `whoami` output is more descriptive and easier to understand.
- Both programs were rebuilt and tested after modification.

### Cons
- The long listing from `ls` takes up more terminal space than the original default output.
- The added text in `whoami` changes its standard output and may affect scripts that expect only the username.
- Users who prefer the original behavior would need to use a different version of the programs or revert the modifications.
