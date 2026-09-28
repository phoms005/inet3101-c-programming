\# Colossus Airlines Seating Reservation System



\## Problem Statement



The Colossus Airlines fleet consists of one plane with a seating capacity of 128. The plane makes two inbound and two outbound flights each day, for a total of four flights. The goal of this program is to create a seating reservation system that allows users to select a flight, view available seats, assign customers to seats, delete seat assignments, and view assigned customers alphabetically.



\## Describe the Solution



The program uses an array of structures to store information for 128 seats on each of the four flights. Each seat structure stores the seat number, whether the seat is assigned, the customer's first name, and the customer's last name.



The program provides a main menu for selecting an outbound flight, inbound flight, or quitting. After selecting a flight number, the user can:



1\. Show the number of empty seats

2\. Show a list of empty seats

3\. Show an alphabetical list of assigned customers

4\. Assign a customer to a seat

5\. Delete a seat assignment

6\. Return to the main menu



The program also allows users to cancel a seat assignment or deletion by entering `0`. It checks for invalid flight numbers, invalid seat numbers, and seats that are already assigned.



\## Pros and Cons of the Solution



\### Pros



\* Stores information for all four flights.

\* Uses structures to keep related seat information together.

\* Allows users to view available seats.

\* Prevents assigning an already occupied seat.

\* Allows customers to be assigned and removed.

\* Displays assigned customers in alphabetical order.

\* Provides options to cancel an assignment or deletion.



\### Cons



\* The program only supports 128 seats per flight.

\* Customer names are entered as single words and do not support spaces.

\* Information is only stored while the program is running.

\* The program uses a simple menu-based interface.



\## Screenshots



\### Screenshot 1 — Main Menu and Flight Selection



!\[Screenshot 1](screenshot1.png)



\### Screenshot 2 — Empty Seats



!\[Screenshot 2](screenshot2.png)



\### Screenshot 3 — Customer Assignment



!\[Screenshot 3](screenshot3.png)



\### Screenshot 4 — Alphabetical List



!\[Screenshot 4](screenshot4.png)



\### Screenshot 5 — Delete Seat Assignment



!\[Screenshot 5](screenshot5.png)



