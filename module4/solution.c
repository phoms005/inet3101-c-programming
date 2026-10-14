
#include <stdio.h>
#include <string.h>

#define NUM_FLIGHTS 4
#define NUM_SEATS 128
#define DATA_FILE "reservations.txt"

struct seat {
    int seat_number;
    int assigned;
    char last_name[50];
    char first_name[50];
};

int flight_numbers[NUM_FLIGHTS] = {1001, 1002, 1003, 1004};
struct seat flights[NUM_FLIGHTS][NUM_SEATS];

void initialize_seats(void)
{
    for (int flight = 0; flight < NUM_FLIGHTS; flight++)
    {
        for (int seat = 0; seat < NUM_SEATS; seat++)
        {
            flights[flight][seat].seat_number = seat + 1;
            flights[flight][seat].assigned = 0;
            flights[flight][seat].last_name[0] = '\0';
            flights[flight][seat].first_name[0] = '\0';
        }
    }
}

void load_reservations(void)
{
    FILE *file = fopen(DATA_FILE, "r");

    if (file == NULL)
    {
        return;
    }

    int flight_number;
    int seat_number;
    char first_name[50];
    char last_name[50];

    while (fscanf(file, "%d %d %49s %49s",
                  &flight_number, &seat_number,
                  first_name, last_name) == 4)
    {
        int flight_index = -1;

        for (int i = 0; i < NUM_FLIGHTS; i++)
        {
            if (flight_numbers[i] == flight_number)
            {
                flight_index = i;
                break;
            }
        }

        if (flight_index >= 0 &&
            seat_number >= 1 && seat_number <= NUM_SEATS)
        {
            struct seat *current = &flights[flight_index][seat_number - 1];

            current->assigned = 1;
            strcpy(current->first_name, first_name);
            strcpy(current->last_name, last_name);
        }
    }

    fclose(file);
}

void save_reservations(void)
{
    FILE *file = fopen(DATA_FILE, "w");

    if (file == NULL)
    {
        printf("Error: Could not save reservations.\n");
        return;
    }

    for (int flight = 0; flight < NUM_FLIGHTS; flight++)
    {
        for (int seat = 0; seat < NUM_SEATS; seat++)
        {
            if (flights[flight][seat].assigned == 1)
            {
                fprintf(file, "%d %d %s %s\n",
                        flight_numbers[flight],
                        flights[flight][seat].seat_number,
                        flights[flight][seat].first_name,
                        flights[flight][seat].last_name);
            }
        }
    }

    fclose(file);
}

int main(void)
{
    char choice;

    initialize_seats();
    load_reservations();

    printf("Colossus Airlines Seating Reservation System\n");

    do
    {
        printf("\nTo choose a function, enter its letter label:\n");
        printf("a. Outbound Flight\n");
        printf("b. Inbound Flight\n");
        printf("c. Quit\n");
        printf("Choice: ");
        scanf(" %c", &choice);

        if (choice == 'c')
        {
            printf("Goodbye!\n");
        }
        else if (choice == 'a' || choice == 'b')
        {
            char flight_choice;

            do
            {
                printf("\n1. Flight Number\n");
                printf("2. Back to Main\n");
                printf("Choice: ");
                scanf(" %c", &flight_choice);

                if (flight_choice == '2')
                {
                    break;
                }
                else if (flight_choice == '1')
                {
                    int flight_number;
                    int flight_index = -1;

                    printf("\nEnter flight number (1001-1004): ");
                    scanf("%d", &flight_number);

                    for (int i = 0; i < NUM_FLIGHTS; i++)
                    {
                        if (flight_numbers[i] == flight_number)
                        {
                            flight_index = i;
                            break;
                        }
                    }

                    if (flight_index == -1)
                    {
                        printf("Invalid flight number. Please try again.\n");
                    }
                    else
                    {
                        printf("Flight %d selected.\n", flight_number);

                        char third_choice;

                        do
                        {
                            printf("\nThird Level Menu\n");
                            printf("1. Show number of empty seats\n");
                            printf("2. Show list of empty seats\n");
                            printf("3. Show alphabetical list of seats\n");
                            printf("4. Assign a customer to a seat assignment\n");
                            printf("5. Delete a seat assignment\n");
                            printf("6. Return to Main menu\n");
                            printf("Choice: ");
                            scanf(" %c", &third_choice);

                            if (third_choice == '6')
                            {
                                break;
                            }
                            else if (third_choice == '1')
                            {
                                int empty_seats = 0;

                                for (int i = 0; i < NUM_SEATS; i++)
                                {
                                    if (flights[flight_index][i].assigned == 0)
                                    {
                                        empty_seats++;
                                    }
                                }

                                printf("Number of empty seats: %d\n", empty_seats);
                            }
                            else if (third_choice == '2')
                            {
                                printf("Empty seats:\n");

                                for (int i = 0; i < NUM_SEATS; i++)
                                {
                                    if (flights[flight_index][i].assigned == 0)
                                    {
                                        printf("%d ", flights[flight_index][i].seat_number);
                                    }
                                }

                                printf("\n");
                            }
                            else if (third_choice == '3')
                            {
                                int assigned_seats = 0;

                                for (int i = 0; i < NUM_SEATS; i++)
                                {
                                    if (flights[flight_index][i].assigned == 1)
                                    {
                                        assigned_seats++;
                                    }
                                }

                                if (assigned_seats == 0)
                                {
                                    printf("No assigned seats yet.\n");
                                }
                                else
                                {
                                    printf("Alphabetical list of seats:\n");

                                    for (int i = 0; i < NUM_SEATS; i++)
                                    {
                                        if (flights[flight_index][i].assigned == 1)
                                        {
                                            printf("%s, %s - Seat %d\n",
                                                   flights[flight_index][i].last_name,
                                                   flights[flight_index][i].first_name,
                                                   flights[flight_index][i].seat_number);
                                        }
                                    }
                                }
                            }
                            else if (third_choice == '4')
                            {
                                int seat_number;

                                printf("\nEnter seat number (1-128), or 0 to cancel: ");
                                scanf("%d", &seat_number);

                                if (seat_number == 0)
                                {
                                    printf("Assignment cancelled.\n");
                                }
                                else if (seat_number < 1 || seat_number > NUM_SEATS)
                                {
                                    printf("Invalid seat number.\n");
                                }
                                else if (flights[flight_index][seat_number - 1].assigned == 1)
                                {
                                    printf("That seat is already assigned.\n");
                                }
                                else
                                {
                                    printf("Enter first name: ");
                                    scanf("%49s", flights[flight_index][seat_number - 1].first_name);

                                    printf("Enter last name: ");
                                    scanf("%49s", flights[flight_index][seat_number - 1].last_name);

                                    flights[flight_index][seat_number - 1].assigned = 1;
                                    save_reservations();

                                    printf("Seat %d assigned to %s %s.\n",
                                           seat_number,
                                           flights[flight_index][seat_number - 1].first_name,
                                           flights[flight_index][seat_number - 1].last_name);
                                }
                            }
                            else if (third_choice == '5')
                            {
                                int seat_number;

                                printf("\nEnter seat number to delete (1-128), or 0 to cancel: ");
                                scanf("%d", &seat_number);

                                if (seat_number == 0)
                                {
                                    printf("Deletion cancelled.\n");
                                }
                                else if (seat_number < 1 || seat_number > NUM_SEATS)
                                {
                                    printf("Invalid seat number.\n");
                                }
                                else if (flights[flight_index][seat_number - 1].assigned == 0)
                                {
                                    printf("That seat is already empty.\n");
                                }
                                else
                                {
                                    flights[flight_index][seat_number - 1].assigned = 0;
                                    flights[flight_index][seat_number - 1].last_name[0] = '\0';
                                    flights[flight_index][seat_number - 1].first_name[0] = '\0';

                                    save_reservations();

                                    printf("Seat %d assignment deleted.\n", seat_number);
                                }
                            }
                            else
                            {
                                printf("Invalid choice. Please try again.\n");
                            }

                        } while (third_choice != '6');
                    }
                }
                else
                {
                    printf("Invalid choice. Please try again.\n");
                }

            } while (flight_choice != '2');
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 'c');

    return 0;
}
