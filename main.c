#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "./modules/structures.c"
#include "./modules/display.c"
#include "./modules/manageFlights.c"
#include "./modules/manageTickets.c"
#include "./modules/manageUsers.c"

int main()
{
    char c;
    int choice, mainChoice;
    char userID[6];

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
                    printf("1. List all available flights.\n");
                    printf("2. Search flights through a general query.\n");
                    printf("3. Update existing flights.\n");
                    printf("4. Add new flights.\n");
                    printf("5. Logout\n");
                    printf("\n>>> Choose one of the above options to continue: ");
                    scanf("%d", &choice);

                    switch (choice)
                    {
                    case 1:
                        system("clear");
                        headerLoginAdmin();

                        flightRead();
                        awaitEnter();
                        break;
                    
                    case 2:
                        system("clear");
                        headerLoginAdmin();
                        printf("\nThis is a very rudimentary search function.\nUser can input any data regarding the flights they want to see\n(like source, destination, departure date, time, etc.) and get corresponding results.\nThe admin can use flight ID to search here as well.\nNOTE: Enter full source/destination name in order to get result\n\n");
                        
                        generalQuery();
                        awaitEnter();

                        break;

                    case 3:
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

                    case 4:
                        system("clear");
                        headerLoginAdmin();

                        printf("\n");
                        addFlight();
                        awaitEnter();
                        break;

                    case 5:
                        system("clear");
                        headerAdmin();

                        printf("\n[-] Logging out.\n");
                        awaitEnter();
                    default:
                        printf("\n");
                        break;
                    }

                } while (choice != 5);
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
                        printf("2. Search for flights through a general query.\n");
                        printf("3. Search for specific flights.\n");
                        printf("4. Book tickets.\n");
                        printf("5. View booked tickets.\n");
                        printf("6. Cancel tickets.\n");
                        printf("7. Logout\n");
                        printf("\n>>> Choose one of the above options to continue: ");
                        scanf("%d", &choice);

                        switch (choice)
                        {
                        case 3:
                            system("clear");
                            headerCustomer();

                            searchFlight();
                            awaitEnter();
                            break;
                        case 2:
                            system("clear");
                            headerCustomer();
                            printf("\nThis is a very rudimentary search function.\nUser can input any data regarding the flights they want to see\n(like source, destination, departure date, time, etc.) and get corresponding results.\nThe input can be of any type, such as names of places, date(DD-MM-YY), time(HH:MM), in a single query\nNOTE: Enter full source/destination name in order to get result\n\n");
                            
                            generalQuery();
                            awaitEnter();
                            break;
                        case 1:
                            system("clear");
                            headerCustomer();

                            flightRead();
                            awaitEnter();
                            break;
                        case 4:
                            system("clear");
                            headerCustomer();

                            bookFlight();
                            awaitEnter();
                            break;
                        case 5:
                            system("clear");
                            headerCustomer();

                            viewTicket();
                            awaitEnter();
                            break;
                        case 6:
                            system("clear");
                            headerCustomer();

                            cancelTicket();
                            awaitEnter();
                            break;
                        case 7:
                            system("clear");
                            headerCustomer();
                            printf("\n[-] Logging out...\n");
                            awaitEnter();
                            break;
                        default:
                            printf("#\n");
                            break;
                        }
                    } while (choice != 7);
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
