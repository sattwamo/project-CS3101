#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char id[6];
    char email[50];
    char password[15];
    char userType;
} USERS;

typedef struct flight
{
    char flightID[6];
    char date[9];
    char time[6];
    char source[20];
    char destination[20];
    float price[3];
    int availableSeats;
} FLIGHT;

typedef struct ticket
{
    char ticketNum[10];
    char flightID[6];
    char name[30];
    char ticketType;
    int seatNum;
} TICKET;

// Sattwamo
void flightWrite(FLIGHT *flight)
{
    FILE *fptr;
    fptr = fopen("flights.txt", "a");

    fwrite(flight, sizeof(FLIGHT), 1, fptr);
    fclose(fptr);
}


void ticketWrite(TICKET* ticket){
    FILE *fptr;
    fptr = fopen("tickets.txt", "a");

    fwrite(ticket, sizeof(TICKET), 1, fptr);
    fclose(fptr);
}

// Sattwamo
void flightRead()
{
    FILE *fptr;
    FLIGHT viewFlight;
    fptr = fopen("flights.txt", "r");

    while (fread(&viewFlight, sizeof(FLIGHT), 1, fptr))
    {
        printf("FlightID = %s Source = %s Destination = %s\n", viewFlight.flightID, viewFlight.source, viewFlight.destination);
    }
    fclose(fptr);
}

int isFlightPresent(char *flightID)
{

    FILE *fptr;
    FLIGHT viewFlight;
    fptr = fopen("flights.txt", "r");

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

int isTicketPresent(char *ticketNum)
{

    FILE *fptr;
    TICKET viewTicket;
    fptr = fopen("tickets.txt", "r");

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
FLIGHT findFlight(char *flightID){
    FILE *fptr;
    FLIGHT viewFlight, flight;
    fptr = fopen("flights.txt", "r");

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

TICKET findTicket(char *ticketNum){

    FILE *fptr;
    TICKET viewTicket, ticket;
    fptr = fopen("tickets.txt", "r");

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

void viewTicket(char *ticketNum){

    if (isTicketPresent(ticketNum))
    {
        TICKET ticket = findTicket(ticketNum);
        FLIGHT flight = findFlight(ticket.flightID);

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
void addFlight(){
    char flightID[6], date[9], time[6], source[20], destination[20];
    float price[3];
    int availableSeats;
    FLIGHT newFlight;

    printf("Enter flight ID: ");
    scanf("%s", flightID);

    printf("Enter Date (DD-MM-YY): ");
    scanf("%s", date);

    printf("Enter departure time (HH:MM): ");
    scanf("%s", time);

    printf("Enter source location: ");
    scanf("%s", source);

    printf("Enter destination location: ");
    scanf("%s", destination);

    printf("Enter number of available seats: ");
    scanf("%d", &availableSeats);

    printf("Enter price of tickets for infants (in Rs.): ");
    scanf("%f", &price[0]);

    printf("Enter price of tickets for children (in Rs.): ");
    scanf("%f", &price[1]);

    printf("Enter price of tickets for adults (in Rs.): ");
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
}

// Tanish
void searchFlight(){
    char source[20], destination[20], date[9];
    FILE *fptr;
    FLIGHT viewFlight;
    fptr = fopen("flights.txt", "r");

    printf("Enter Date (DD-MM-YY): ");
    scanf("%s", date);
    printf("Enter source location: ");
    scanf("%s", source);
    printf("Enter destination location: ");
    scanf("%s", destination);

    while (fread(&viewFlight, sizeof(FLIGHT), 1, fptr))
    {
        if ((strcmp(source, viewFlight.source) == 0) && (strcmp(destination, viewFlight.destination) == 0) && (strcmp(date, viewFlight.date) == 0))
        {
            printf("FlightID: %s\t\tTime: %s\tPrice: (I:%.2f |C: %.2f |A: %.2f)\t Remaining seats: %d\n", viewFlight.flightID, viewFlight.time, viewFlight.price[0], viewFlight.price[1], viewFlight.price[2], viewFlight.availableSeats);
        }
    }
    fclose(fptr);
}

// Sattwamo
void updateSeats(char *flightID){
    FLIGHT updateFlight;
    FILE *fptr;
    fptr = fopen("flights.txt", "r+");

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

// Tanish
float makeTicket(char *flightID, int ticketType){
    TICKET ticket;
    FLIGHT flight = findFlight(flightID);
    int seatNum = flight.availableSeats;
    float price = flight.price[ticketType - 1];
    char ticketNum[10];
    char name[30];

    sprintf(ticketNum, "%s-%d", flightID, seatNum);
    printf("Enter passenger name: \n");
    scanf("%s", name);

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

    return price;
}

// Tanish
void bookFlight(){
    char flightID[6];
    int choice = 5;

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
                totalPrice += makeTicket(flightID, choice);
            }
            else if (choice == 0)
            {
                printf("Total ticket price is Rs. %.2f", totalPrice);
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

// Tanish
int countFlight(){
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

/*
void availPlaces(){
    char places[20][20];
    FILE *fptr;
    FLIGHT viewFlight;
    fptr = fopen("flights.txt", "r");

    while(fread(&viewFlight, sizeof(FLIGHT), 1, fptr)){
        if (){

        }
    }
}
*/

// Sattwamo
void updateFlight(char *flightID)
{
    char date[9], time[6], source[20], destination[20];
    float price[3];
    int availableSeats;

    int choice;
    int count = 0;

    FLIGHT updateFlight;
    FILE *fptr;
    fptr = fopen("flights.txt", "r+");

    while (fread(&updateFlight, sizeof(FLIGHT), 1, fptr))
    {
        if (!strcmp(flightID, updateFlight.flightID))
        {
            count = 1;
        p1:
            printf("Select what you want to update:\
            \n1. Departure date\
            \n2. Departure time\
            \n3. Source location\
            \n4. Destination location\
            \n5. Number of available seats\
            \n6. Price of tickets for infants\
            \n7. Price of tickets for children\
            \n8. Price of tickets for adults\
            \n0. Continue without making any changes\n");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("Enter new date (DD-MM-YY): ");
                scanf("%s", date);
                strcpy(updateFlight.date, date);
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                break;

            case 2:
                printf("Enter new departure time (HH:MM): ");
                scanf("%s", time);
                strcpy(updateFlight.time, time);
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                break;

            case 3:
                printf("Enter new source location: ");
                scanf("%s", source);
                strcpy(updateFlight.source, source);
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                break;

            case 4:
                printf("Enter new destination location: ");
                scanf("%s", destination);
                strcpy(updateFlight.destination, destination);
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                break;

            case 5:
                printf("Enter new number of available seats: ");
                scanf("%d", &availableSeats);
                updateFlight.availableSeats = availableSeats;
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                break;

            case 6:
                printf("Enter new price of tickets for infants (in Rs.): ");
                scanf("%f", &price[0]);
                updateFlight.price[0] = price[0];
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                break;

            case 7:
                printf("Enter new price of tickets for children (in Rs.): ");
                scanf("%f", &price[1]);
                updateFlight.price[1] = price[1];
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                break;

            case 8:
                printf("Enter new price of tickets for adults (in Rs.): ");
                scanf("%f", &price[2]);
                updateFlight.price[2] = price[2];
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                break;

            case 0:
                printf("Continuiung... ");
                break;

            default:
                printf("Enter a valid choice!!!");
                break;
                // goto p1;
            }
        }
    }

    fclose(fptr);

    if (!count)
    {
        printf("Enter valid flight ID!\n");
    }
}

// Om
void usersWrite(USERS *user)
{
    FILE *fptr;
    fptr = fopen("logins.txt", "a");
    fwrite(user, sizeof(USERS), 1, fptr);
    fclose(fptr);
}

USERS viewUser(char *userID){
    FILE* fptr;
    USERS user, viewUser;
    fptr = fopen("logins.txt", "r");

    while(fread(&viewUser, sizeof(USERS), 1, fptr)){
        if (strcmp(viewUser.id, userID) == 0){
            user = viewUser;
        }
    }

    fclose(fptr);
    return user;
}

int isUserPresent(char* userID){
    int check;
    FILE *fptr;
    USERS viewUser;
    fptr = fopen("logins.txt", "r");
    
    while(fread(&viewUser, sizeof(USERS), 1, fptr)){
        if(strcmp(viewUser.id, userID) == 0){
            check = 1;
        }
    
    fclose(fptr);
    return check;
    
    }
}

void adduser()
{
    char id[6], email[50], password[5];
    char userType = 'B';
    USERS newuser;
    printf("enter the following details with care to register yourself on the system\n");
    newuser.userType = userType;
    printf("enter your email:\n");
    scanf("%s", email);
    printf("enter a 5 digit alphanumeric id:\n");
    scanf("%s", id);
    printf("enter your 4 digit password:\n");
    scanf("%s", password);
    strcpy(newuser.id, id);
    strcpy(newuser.email, email);
    strcpy(newuser.password, password);
    usersWrite(&newuser);
    printf("Your user id is succesfully created :)\n\n");
}

void addadmin()
{
    char id[6], email[50], password[4];
    char userType = 'A';
    USERS newadmin;
    printf("enter the following details with care to register yourself on the system\n");
    newadmin.userType = userType;
    printf("enter your email:\n");
    scanf("%s", email);
    printf("enter a 6 digit alphanumeric id:\n");
    scanf("%s", id);
    printf("enter your 4 digit password:\n");
    scanf("%s", password);
    strcpy(newadmin.id, id);
    strcpy(newadmin.email, email);
    strcpy(newadmin.password, password);
    usersWrite(&newadmin);
    printf("Your admin id is succesfully created :)\n\n");
}

void checkuser()
{
    // FILE *fptr;
    USERS user;
    // fptr = fopen("logins.txt", "r");
    char id[6];
    char password[4];
    printf("Enter your login credentials\n");
    printf("enter your login id:\n");
    scanf("%s", id);
    // int count = 0;

    // while (fread(&viewuser, sizeof(USERS), 1, fptr))
    // {
    //     if (id == viewuser.id)
    //     {
    //         count = 1;
    //         printf("enter your 4 digit pasword:\n");
    //         scanf("%s", password);
    //         if (password == viewuser.id)
    //         {
    //             printf("Login Succesfull\n");
    //         }
    //         else
    //         {
    //             printf("Incorrect Password\n");
    //         }
    //     }
    // }

    // if (!count){
    //     printf("User ID not found!!!");
    // }

    if (isUserPresent){
        user = viewUser(id);
        printf("enter your 4 digit pasword:\n");
        scanf("%s", password);
        if (strcmp(password, user.id)){
            printf("Login Succesfull\n");
        }
        else{
            printf("Incorrect Password\n");
        }
    }

    else{
        printf("Enter valid user ID\n");
    }
    // fclose(fptr);
}

void checkadmin()
{
    FILE *fptr;
    USERS viewadmin;
    fptr = fopen("logins.txt", "r");
    char id[6];
    char password[4];
    printf("Enter your login credentials\n");
    printf("enter your login id:\n");
    scanf("%s", id);
    while (fread(&viewadmin, sizeof(USERS), 1, fptr))
    {
        if (id == viewadmin.id)
        {
            printf("enter your 4 digit pasword:\n");
            scanf("%s", password);
            if (password == viewadmin.id)
            {
                printf("Login Succesfull\n");
            }
            else
            {
                printf("Incorrect Password\n");
            }
        }
    }
    fclose(fptr);
}

void admin()
{
    addadmin();
    checkadmin();
}

void user()
{
    adduser();
    checkuser();
}

void intro()
{
    printf("Welcome to Spicy Flight Reservation System:)\n");
    int type;
    printf("Enter 0 if you are a admin or 1 if you are a customer: ");
    scanf("%d", &type);
    switch (type)
    {
        case 0:
            admin();
            break;
        case 1:
            user();
            break;
        default:
            printf("Invalid Input");
            break;
    }
}

int main()
{
    // addFlight();
    // flightRead();
    // searchFlight();
    // bookFlight();
    // searchFlight();
    // findTicket("F2345-100");
    viewTicket("F2345-100");
    // printf("%d", isFlightPresent("F2345"));

    return 0;
}