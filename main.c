#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./bin/structures.c"
#include "./bin/manageFlights.c"
#include "./bin/manageTickets.c"
#include "./bin/manageUsers.c"
#include "./bin/display.c"

int countFlight()
{
    int count = 0;
    FILE *fptr;
    FLIGHT viewFlight;
    fptr = fopen("flights.txt", "r");

    while (fread(&viewFlight, sizeof(FLIGHT), 1, fptr))
    {
        count += 1;
    }
    return count;
}

int main()
{
    char c;
    int choice, mainChoice;
    char userID[6];

    // addAdmin();

    do
    {
        // system("cls"); // for windows
        system("clear"); // for linux/unix
        headerIntitial();

        printf("\n");
        printf("1. Get admin access\n");
        printf("2. Continue to customer login\n");
        printf("3. Terminate the program.\n");
        printf("Choose an option from the list given above: ");
        scanf("%d", &mainChoice);

        switch (mainChoice)
        {
        case 1:
            // system("cls"); // for windows
            system("clear"); // for linux/unix
            headerAdmin();
            printf("\n");
            if (checkAdmin() == 1)
            {
                do
                {
                    system("clear");
                    headerAdmin();
                    printf("\n");
                    printf("1. Update existing flights.\n");
                    printf("2. Add new flights.\n");
                    printf("3. Logout\n");
                    printf("Choose one of the above options to continue: ");
                    scanf("%d", &choice);

                    switch (choice)
                    {
                    case 1:
                        system("clear");
                        headerAdmin();

                        printf("\n");
                        printf("Enter the Flight ID to be updated:\n");
                        scanf("%s", userID);

                        updateFlight(userID);

                        break;

                    case 2:
                        system("clear");
                        headerAdmin();

                        printf("\n");
                        addFlight();

                        break;
                    default:
                        printf("\n");
                        break;
                    }

                } while (choice != 3);
            }

            else
            {
                printf("You are not authorized to perform this action!\n");
                awaitEnter();
            }
            break;

        case 2:
            // system("cls"); // for windows
            system("clear"); // for linux/unix
            headerCustomer();

            printf("\n");
            printf("1. Login for already existing customers. \n");
            printf("2. New customer registration.\n");
            printf("Choose one of the above options to continue: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                // system("cls"); // for windows
                system("clear"); // for linux/unix
                headerIntitial();

                if (checkUser() == 1)
                {
                    do
                    {
                        // system("cls"); // for windows
                        system("clear"); // for linux/unix
                        headerCustomer();

                        printf("\n");
                        printf("1. Search for flights.\n");
                        printf("2. Book tickets.\n");
                        printf("3. View booked tickets.\n");
                        printf("4. Cancel tickets.\n");
                        printf("5. Logout\n");
                        printf("Choose one of the above options to continue: ");
                        scanf("%d", &choice);

                        switch (choice)
                        {
                        case 1:
                            system("clear");
                            headerCustomer();

                            searchFlight();
                            awaitEnter();
                            break;
                        case 2:
                            system("clear");
                            headerCustomer();

                            bookFlight();
                            awaitEnter();
                            break;
                        case 3:
                            system("clear");
                            headerCustomer();

                            viewTicket();
                            awaitEnter();
                            break;
                        case 5:
                            system("clear");
                            headerCustomer();
                            printf("Logging out...\n");
                            awaitEnter();
                            break;
                        default:
                            printf("#\n");
                            break;
                        }
                    } while (choice != 5);
                }
                else
                {

                    awaitEnter();
                }
                break;

            case 2:
                // system("cls"); // for windows
                system("clear"); // for linux/unix
                headerIntitial();
                addUser();
                break;

            default:
                // system("cls"); // for windows
                system("clear"); // for linux/unix
                // headerAdmin();
                // getchar();
                break;
            }
            break;
        case 3:
            system("clear");
            printf("Thank you for using our flight booking system.\n\n");
            printf("Made by Sattwamo Ghosh, Tanish Nimbalkar & Om Khare :)");

            awaitEnter();
            system("clear");
            break;

        default:
            printf("Enter a valid choice.\n");
            break;
        }

    } while (mainChoice != 3);

    // addAdmin();
    // addUser();
    // checkAdmin();

    // addFlight();
    // searchFlight();
    // bookFlight();
    // searchFlight();
    // findTicket("F2345-100");
    // printf("%d", isFlightPresent("F2345"));

    return 0;
}
