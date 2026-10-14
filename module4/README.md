\# Colossus Airlines Reservation System — Module 4



\## Problem Statement



The Colossus Airlines reservation system allows users to select flights, view available seats, assign customers to seats, and delete reservations. In the previous version, reservation information was stored only in memory and was lost when the program ended.



The goal of Module 4 is to add file persistence so that reservations are saved and can be retrieved when the program is run again.



\## Describe the Solution



The program is written in C and uses a text file named `reservations.txt` to store reservation information.



The solution includes three main functions related to persistence:



\- `initialize\\\_seats()` initializes the seats for all four flights.

\- `load\\\_reservations()` reads saved reservations from `reservations.txt` when the program starts.

\- `save\\\_reservations()` writes current reservations to the file after a seat is assigned or deleted.



Each saved reservation contains the flight number, seat number, first name, and last name. This allows the program to restore customer assignments after it closes and restarts.



The original menu features remain available, including displaying empty seats, listing assigned seats, assigning customers, and deleting assignments.



\## Pros and Cons



\### Pros



\- Reservations persist after the program closes.

\- Saved data is stored in a simple, human-readable text file.

\- Existing reservation features remain available.

\- The program saves changes after assignments and deletions.



\### Cons



\- The program uses a local text file rather than a database.

\- Names are stored as single words, so names containing spaces are not fully supported.

\- The file does not provide advanced security or protection against unauthorized changes.

\- The program has limited error handling for invalid user input and file errors.



\## Screenshots / Recording



Screenshots demonstrating the program's functionality will be included here.



1\. Successful seat assignment.

2\. Reservation data saved in `reservations.txt`.

3\. Reservation successfully loaded after restarting the program.



