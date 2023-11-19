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

    printf("\n>>> Enter ticket number: ");
    scanf("%9s",ticketNum);

    if (isTicketPresent(ticketNum))
    {
        TICKET ticket = findTicket(ticketNum);
        FLIGHT flight = findFlight(ticket.flightID);

        printf("\n*** Booked ticket details: ***\n");

        printf("[*] Flight ID: %s\n", ticket.flightID);
        printf("[*] Source: %s\n", flight.source);
        printf("[*] Destination: %s\n", flight.destination);
        printf("[*] Departure date: %s\n", flight.date);
        printf("[*] Departure time: %s\n", flight.time);
        printf("[*] Passenger name: %s", ticket.name);
        printf("[*] Ticket type: %c\n", ticket.ticketType);
        printf("[*] Seat number: %d\n\n", ticket.seatNum);
    }

    else
    {
        printf("\n*** Enter valid ticket number! ***\n");
    }
}

char* makeTicket(char *flightID, int ticketType){
    TICKET ticket;
    FLIGHT flight = findFlight(flightID);
    int seatNum = flight.availableSeats;
    float price = flight.price[ticketType - 1];
    char* ticketNum = (char*)malloc(10 * sizeof(char));
    char name[30];

    sprintf(ticketNum, "%s-%d", flightID, seatNum);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf(">>> Enter passenger name: ");
    fgets(name, 30, stdin);

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

void bookFlight(){
    char flightID[6];
    int choice = 5, i = 0;
    char* allTicket[10];
    char display[150] = "[*] Booked ticket numbers: ";
    TICKET getTicket;

    float totalPrice = 0;

    printf("\n>>> Enter flight ID: ");
    scanf("%5s", flightID);

    if (isFlightPresent(flightID))
    {
        while (choice)
        {
            printf("\nAvailable ticket type: \n1. Infant \n2. Child \n3. Adult\n");
            printf("\n>>> Select one of the above int values or 0 to continue without adding more tickets: ");
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
                printf("\n[*] Total ticket price is Rs. %.2f\n", totalPrice);
                printf("%s\n", display);
            }
            else
            {
                printf("\n*** Enter a valid choice! *** \n");
            }
        }
    }

    else
    {
        printf("\n*** Enter valid flight ID! ***\n");
    }
}

void cancelTicket(){
    FILE *fptr1, *fptr2;
    TICKET updateTicket;
    char ticketNum[10];

    printf("\n>>> Enter ticket number to cancel: ");
    scanf("%s", ticketNum);

    fptr1 = fopen("./data/tickets.txt", "r");

    if (isTicketPresent(ticketNum)){
    fptr2 = fopen("./data/temp.txt", "w");
        while (fread(&updateTicket, sizeof(TICKET), 1, fptr1)){
            if(strcmp(updateTicket.ticketNum, ticketNum) != 0){
                fwrite(&updateTicket, sizeof(TICKET), 1, fptr2);
            }
        }
    puts("\n[-] Ticket cancelled successfully.");
    
    remove("./data/tickets.txt");
    rename("./data/temp.txt", "./data/tickets.txt");
    }
    else{
        printf("\n*** Enter valid ticket number! ***\n");
    }

    fclose(fptr1);
    fclose(fptr2);

}