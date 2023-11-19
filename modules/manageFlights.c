void flightWrite(FLIGHT *flight)
{
    FILE *fptr;
    fptr = fopen("./data/flights.txt", "a");

    fwrite(flight, sizeof(FLIGHT), 1, fptr);
    fclose(fptr);
}

void flightRead()
{
    FILE *fptr;
    FLIGHT viewFlight;
    fptr = fopen("./data/flights.txt", "r");

    printf("\n*** List of all the available flights ***\n");
    printf("    Flight ID | Source          | Destination     | Date       | Departure Time | Seats Available | Infant Price | Child Price | Adult Price\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");

    while (fread(&viewFlight, sizeof(FLIGHT), 1, fptr))
    {
        printf("[*] %-9s | %-15s | %-15s | %-10s | %-14s | %-15d | %-12.2f | %-11.2f | %-11.2f\n", viewFlight.flightID, viewFlight.source, viewFlight.destination, viewFlight.date, viewFlight.time, viewFlight.availableSeats, viewFlight.price[0], viewFlight.price[1], viewFlight.price[2]);
    }
    fclose(fptr);
    printf("\n");
}

int isFlightPresent(char *flightID)
{

    FILE *fptr;
    FLIGHT viewFlight;
    fptr = fopen("./data/flights.txt", "r");

    int check = 0;

    while (fread(&viewFlight, sizeof(FLIGHT), 1, fptr))
    {
        if (strcmp(flightID, viewFlight.flightID) == 0)
        {
            check = 1;
        }
    }
    fclose(fptr);

    return check;
}

FLIGHT findFlight(char *flightID)
{
    FILE *fptr;
    FLIGHT viewFlight, flight;
    fptr = fopen("./data/flights.txt", "r");

    while (fread(&viewFlight, sizeof(FLIGHT), 1, fptr))
    {
        if (strcmp(flightID, viewFlight.flightID) == 0)
        {
            flight = viewFlight;
        }
    }
    fclose(fptr);
    return flight;
}

void addFlight()
{
    char flightID[6], date[9], time[6], source[20], destination[20];
    float price[3];
    int availableSeats;
    FLIGHT newFlight;

    printf(">>> Enter flight ID: ");
    scanf("%5s", flightID);

    printf(">>> Enter Date (DD-MM-YY): ");
    scanf("%8s", date);

    printf(">>> Enter departure time (HH:MM): ");
    scanf("%5s", time);

    printf(">>> Enter source location: ");
    scanf("%19s", source);

    printf(">>> Enter destination location: ");
    scanf("%19s", destination);

    printf(">>> Enter number of available seats: ");
    scanf("%d", &availableSeats);

    printf(">>> Enter price of tickets for infants (in Rs.): ");
    scanf("%f", &price[0]);

    printf(">>> Enter price of tickets for children (in Rs.): ");
    scanf("%f", &price[1]);

    printf(">>> Enter price of tickets for adults (in Rs.): ");
    scanf("%f", &price[2]);

    strcpy(newFlight.flightID, flightID);
    strcpy(newFlight.date, date);
    strcpy(newFlight.time, time);
    strcpy(newFlight.source, source);
    strcpy(newFlight.destination, destination);
    newFlight.availableSeats = availableSeats;
    newFlight.price[0] = price[0];
    newFlight.price[1] = price[1];
    newFlight.price[2] = price[2];

    flightWrite(&newFlight);

    printf("\n[+] Flight No. %s added successfully.", flightID);
}

void searchFlight()
{
    char source[20], destination[20], date[9];
    FILE *fptr;
    FLIGHT viewFlight;
    fptr = fopen("./data/flights.txt", "r");

    printf("\n>>> Enter Date (DD-MM-YY): ");
    scanf("%s", date);
    printf(">>> Enter source location: ");
    scanf("%s", source);
    printf(">>> Enter destination location: ");
    scanf("%s", destination);
    int flightsFound = 0;
    printf("\n");

        printf("    Flight ID | Departure Time | Seats Available | Infant Price | Child Price | Adult Price\n");
        printf("-------------------------------------------------------------------------------------------\n");
    while (fread(&viewFlight, sizeof(FLIGHT), 1, fptr))
    {
        if ((strcmp(source, viewFlight.source) == 0) && (strcmp(destination, viewFlight.destination) == 0) && (strcmp(date, viewFlight.date) == 0))
        {
            ++flightsFound;
            // printf("[*] FlightID: %s\tTime: %s\tPrice: (I:%.2f |C: %.2f |A: %.2f)\t Remaining seats: %d\n", viewFlight.flightID, viewFlight.time, viewFlight.price[0], viewFlight.price[1], viewFlight.price[2], viewFlight.availableSeats);

            printf("[*] %-9s | %-14s | %-15d | %-12.2f | %-11.2f | %-11.2f\n", viewFlight.flightID, viewFlight.time, viewFlight.availableSeats, viewFlight.price[0], viewFlight.price[1], viewFlight.price[2]);







        }
    }

    if (flightsFound == 0)
        {printf("*** No flights found for your search. ***\n");}
    else{printf("\n");}
    fclose(fptr);
}

void updateSeats(char *flightID)
{
    FLIGHT updateFlight;
    FILE *fptr;
    fptr = fopen("./data/flights.txt", "r+");

    while (fread(&updateFlight, sizeof(FLIGHT), 1, fptr))
    {
        if (!strcmp(updateFlight.flightID, flightID))
        {
            updateFlight.availableSeats--;
            fseek(fptr, -sizeof(FLIGHT), 1);
            fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
        }
    }

    fclose(fptr);
}

void updateFlight(char *flightID)
{
    char date[9], time[6], source[20], destination[20];
    float price[3];
    int availableSeats;

    int choice;
    int count = 0;

    FLIGHT updateFlight;
    FILE *fptr;
    fptr = fopen("./data/flights.txt", "r+");

    while (fread(&updateFlight, sizeof(FLIGHT), 1, fptr))
    {
        if (!strcmp(flightID, updateFlight.flightID))
        {
            count = 1;
            printf("\nSelect what you want to update:\
            \n1. Departure date\
            \n2. Departure time\
            \n3. Source location\
            \n4. Destination location\
            \n5. Number of available seats\
            \n6. Price of tickets for infants\
            \n7. Price of tickets for children\
            \n8. Price of tickets for adults\
            \n0. Continue without making any changes\n");
            printf("\n>>> Choose any one of the above options: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("\n>>> Enter new date (DD-MM-YY): ");
                scanf("%8s", date);
                strcpy(updateFlight.date, date);
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                printf("\n[+] Departure date of flight no. %s updated successfully.", flightID);
                break;

            case 2:
                printf("\n>>> Enter new departure time (HH:MM): ");
                scanf("%5s", time);
                strcpy(updateFlight.time, time);
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                printf("\n[+] Departure time of flight no. %s updated successfully.", flightID);
                break;

            case 3:
                printf("\n>>> Enter new source location: ");
                scanf("%19s", source);
                strcpy(updateFlight.source, source);
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                printf("\n[+] Source of flight no. %s updated successfully.", flightID);
                break;

            case 4:
                printf("\n>>> Enter new destination location: ");
                scanf("%19s", destination);
                strcpy(updateFlight.destination, destination);
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                printf("\n[+] Destination of flight no. %s updated successfully.", flightID);
                break;

            case 5:
                printf("\n>>> Enter new number of available seats: ");
                scanf("%d", &availableSeats);
                updateFlight.availableSeats = availableSeats;
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                printf("\n[+] Number of available seats of flight no. %s updated successfully.", flightID);
                break;

            case 6:
                printf("\n>>> Enter new price of tickets for infants (in Rs.): ");
                scanf("%f", &price[0]);
                updateFlight.price[0] = price[0];
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                printf("\n[+] Price of tickets for infants in flight no. %s updated successfully.", flightID);
                break;

            case 7:
                printf("\n>>> Enter new price of tickets for children (in Rs.): ");
                scanf("%f", &price[1]);
                updateFlight.price[1] = price[1];
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                printf("\n[+] Price of tickets for children in flight no. %s updated successfully.", flightID);
                break;

            case 8:
                printf("\n>>> Enter new price of tickets for adults (in Rs.): ");
                scanf("%f", &price[2]);
                updateFlight.price[2] = price[2];
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                printf("\n[+] Price of tickets for adults in flight no. %s updated successfully.", flightID);
                break;

            case 0:
                system("clear");
                headerLoginAdmin();
                printf("\n*** Returning to main menu.***\n ");
                break;

            default:
                printf("\n*** Enter a valid choice! ***\n");
                // awaitEnter();
                break;
            }
        }
    }

    fclose(fptr);

    if (!count)
    {
        printf("\n*** Enter valid flight ID! ***\n");
        awaitEnter();
    }
}