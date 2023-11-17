void ticketWrite(TICKET *ticket)
{
    FILE *fptr;
    fptr = fopen("./data/tickets.txt", "a");

    fwrite(ticket, sizeof(TICKET), 1, fptr);
    fclose(fptr);
}

int isTicketPresent(char *ticketNum)
{

    FILE *fptr;
    TICKET viewTicket;
    fptr = fopen("./data/tickets.txt", "r");

    int check = 0;

    while (fread(&viewTicket, sizeof(TICKET), 1, fptr))
    {
        if (strcmp(ticketNum, viewTicket.ticketNum) == 0)
        {
            check = 1;
        }
    }

    fclose(fptr);
    return check;
}

// Tanish


TICKET findTicket(char *ticketNum){

    FILE *fptr;
    TICKET viewTicket, ticket;
    fptr = fopen("./data/tickets.txt", "r");

    while (fread(&viewTicket, sizeof(TICKET), 1, fptr))
    {
        if (strcmp(ticketNum, viewTicket.ticketNum) == 0)
        {
            ticket = viewTicket;
        }
    }

    fclose(fptr);
    return ticket;
}

void viewTicket(){
    char ticketNum[10];

    printf("Enter ticket number: ");
    scanf("%s",ticketNum);

    if (isTicketPresent(ticketNum))
    {
        TICKET ticket = findTicket(ticketNum);
        FLIGHT flight = findFlight(ticket.flightID);

        printf("\nBooked ticket details: \n\n");

        printf("Flight ID: %s\n", ticket.flightID);
        printf("Source: %s\n", flight.source);
        printf("Destination: %s\n", flight.destination);
        printf("Departure date: %s\n", flight.date);
        printf("Departure time: %s\n", flight.time);
        printf("Passenger name: %s\n", ticket.name);
        printf("Ticket type: %c\n", ticket.ticketType);
        printf("Seat number: %d\n", ticket.seatNum);
    }

    else
    {
        printf("\nEnter valid ticket number!!\n");
    }
}

// Sattwamo


// Tanish
char* makeTicket(char *flightID, int ticketType){
    TICKET ticket;
    FLIGHT flight = findFlight(flightID);
    int seatNum = flight.availableSeats;
    float price = flight.price[ticketType - 1];
    char* ticketNum = (char*)malloc(10 * sizeof(char));
    char name[30];

    sprintf(ticketNum, "%s-%d", flightID, seatNum);
    printf("Enter passenger name: \n");
    scanf("%s", name);

    ticket.price = price;
    strcpy(ticket.name, name);
    ticket.seatNum = seatNum;
    strcpy(ticket.flightID, flightID);
    strcpy(ticket.ticketNum, ticketNum);

    if (ticketType == 1)
    {
        ticket.ticketType = 'I';
    }
    else if (ticketType == 2)
    {
        ticket.ticketType = 'C';
    }
    else
    {
        ticket.ticketType = 'A';
    }

    ticketWrite(&ticket);
    updateSeats(flightID);

    return ticketNum;
}

// Tanish
void bookFlight(){
    char flightID[6];
    int choice = 5, i = 0;
    char* allTicket[10];
    char display[150] = "Booked ticket numbers: ";
    TICKET getTicket;

    float totalPrice = 0;

    printf("Enter flight ID: \n");
    scanf("%s", flightID);

    if (isFlightPresent(flightID))
    {
        while (choice)
        {
            printf("\nAvailable ticket type: \n1. Infant \n2. Child \n3. Adult\n");
            printf("\nSelect one of the above int values or 0 to continue without adding more tickets: ");
            scanf("%d", &choice);

            if (choice == 1 || choice == 2 || choice == 3)
            {
                allTicket[i] = makeTicket(flightID, choice);
                i++;
            }
            else if (choice == 0)
            {
                for (int j = 0; j < i; j++){
                    getTicket = findTicket(allTicket[j]);
                    strcat(display, getTicket.ticketNum);
                    strcat(display, "\t ");
                    totalPrice += getTicket.price;
                }
                printf("Total ticket price is Rs. %.2f\n", totalPrice);
                printf("%s", display);
            }
            else
            {
                printf("Invalid choice!! Enter valid option!!\n");
            }
        }
    }

    else
    {
        printf("Enter valid flight ID!");
    }
}