#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./bin/structures.c"
#include "./bin/display.c"
#include "./bin/manageFlights.c"
#include "./bin/manageTickets.c"
#include "./bin/manageUsers.c"

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
        printf("\n>>> Choose an option from the list given above: ");
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
                    headerLoginAdmin();
                    printf("\n");
                    printf("1. Update existing flights.\n");
                    printf("2. Add new flights.\n");
                    printf("3. Logout\n");
                    printf("\n>>> Choose one of the above options to continue: ");
                    scanf("%d", &choice);

                    switch (choice)
                    {
                    case 1:
                        system("clear");
                        headerLoginAdmin();

                        printf("\n");
                        printf(">>> Enter the Flight ID to be updated: ");
                        scanf("%s", userID);
                        printf("");
                        system("clear");
                        headerLoginAdmin();
                        updateFlight(userID);
                        awaitEnter();

                        break;

                    case 2:
                        system("clear");
                        headerLoginAdmin();

                        printf("\n");
                        addFlight();
                        awaitEnter();
                        break;

                    case 3:
                        system("clear");
                        headerAdmin();

                        printf("\n[-] Logging out.\n");
                        awaitEnter();
                    default:
                        printf("\n");
                        break;
                    }

                } while (choice != 3);
            }

            else
            {
                printf("\n*** You are not authorized to perform this action! ***\n");
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
            printf("\n>>> Choose one of the above options to continue: ");
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
                        printf("1. List all the available flights.\n");
                        printf("2. Search for specific flights.\n");
                        printf("3. Book tickets.\n");
                        printf("4. View booked tickets.\n");
                        printf("5. Cancel tickets.\n");
                        printf("6. Logout\n");
                        printf("\n>>> Choose one of the above options to continue: ");
                        scanf("%d", &choice);

                        switch (choice)
                        {
                        case 2:
                            system("clear");
                            headerCustomer();

                            searchFlight();
                            awaitEnter();
                            break;
                        case 1:
                            system("clear");
                            headerCustomer();

                            flightRead();
                            awaitEnter();
                            break;
                        case 3:
                            system("clear");
                            headerCustomer();

                            bookFlight();
                            awaitEnter();
                            break;
                        case 4:
                            system("clear");
                            headerCustomer();

                            viewTicket();
                            awaitEnter();
                            break;
                        case 5:
                            system("clear");
                            headerCustomer();

                            cancelTicket();
                            awaitEnter();
                            break;
                        case 6:
                            system("clear");
                            headerCustomer();
                            printf("\n[-] Logging out...\n");
                            awaitEnter();
                            break;
                        default:
                            printf("#\n");
                            break;
                        }
                    } while (choice != 6);
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
                break;
            }
            break;
        case 3:
            system("clear");
            printf("Thank you for using our flight booking system.\n\n");
            printf("Made by Sattwamo Ghosh, Tanish Nimbalkar & Om Khare :)\n");

            awaitEnter();
            system("clear");
            break;

        default:
            printf("*** Enter a valid choice! ***\n");
            awaitEnter();
            break;
        }

    } while (mainChoice != 3);

    return 0;
}
