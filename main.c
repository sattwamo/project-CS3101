#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char id[6];
    char email[50];
    char password[15];
    char userType;
}USERS;

typedef struct flight{
    char flightID[6];
    char date[9];
    char time[6];
    char source[20];
    char destination[20];
    float price[3]; 
    int availableSeats;
}FLIGHT;

typedef struct ticket{
    char ticketNum[9];
    char flightID[6];
    char name[30];
    char ticketType;
    int seatNum;
}TICKET;

void flightWrite(FLIGHT* flight){
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

void flightRead(){
    FILE *fptr;
    FLIGHT viewFlight;
    fptr = fopen("flights.txt", "r");

    while(fread(&viewFlight, sizeof(FLIGHT), 1, fptr)){
        printf ("FlightID = %s Source = %s Destination = %s\n", viewFlight.flightID, viewFlight.source, viewFlight.destination);
    }
    fclose(fptr);
}

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

    while(fread(&viewFlight, sizeof(FLIGHT), 1, fptr)){
        if ((strcmp(source,viewFlight.source) == 0) && (strcmp(destination,viewFlight.destination) == 0) && (strcmp(date,viewFlight.date) == 0)){
            printf("FlightID: %s\t\tTime: %s\tPrice: (I:%.2f |C: %.2f |A: %.2f)\t Remaining seats: %d\n",viewFlight.flightID,viewFlight.time,viewFlight.price[0],viewFlight.price[1],viewFlight.price[2],viewFlight.availableSeats);
        }
    }
    fclose(fptr);
}

FLIGHT* findFlight(char *flightID){
    FILE *fptr;
    FLIGHT viewFlight;
    fptr = fopen("flights.txt", "r");
    FLIGHT *flight;

    while(fread(&viewFlight, sizeof(FLIGHT), 1, fptr)){
        if (strcmp(flightID,viewFlight.flightID) == 0){
            flight = &viewFlight;
        }
    }
    fclose(fptr);
    return flight;
}

void makeTicket(char *flightID, char ticketType){
    char name[30];
    FLIGHT *flight = findFlight(flightID); 
    int seatNum = flight->availableSeats;
    TICKET ticket;
    char ticketNum[10];

    sprintf(ticketNum,"%s-%d",flightID,seatNum);
    printf("%s", ticketNum);
    printf("Enter passenger name: \n");
    gets(name);

    strcpy(ticket.name,name);
    ticket.seatNum=seatNum;
    strcpy(ticket.flightID,flightID);
    ticket.ticketType = ticketType;
    strcpy(ticket.ticketNum,ticketNum);

    ticketWrite(&ticket);
}

void bookFlight(){
    char flightID[6];
    char choice;

    printf("Enter flight ID: \n");
    scanf("%s",flightID);

    do{
        printf("Select ticket type (Infant: I / Child: C / Adult: A / Exit: e):\n");
        scanf("%c", &choice);

        switch(choice){
            case 'I':
                makeTicket(flightID,'I');
                break;
            case 'C':
                makeTicket(flightID,'C');
                break;
            case 'A':
                makeTicket(flightID,'A');
                break;
            case 'e':
                break;
            default:
                printf("Enter a valid choice!!!");
                break;
            
        }
    }while(choice != 'e');
}

int countFlight(){
    int count = 0;
    FILE *fptr;
    FLIGHT viewFlight;
    fptr = fopen("flights.txt", "r");

    while(fread(&viewFlight, sizeof(FLIGHT), 1, fptr)){
        count+=1;
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

void updateFlight(char *flightID){
    char date[9], time[6], source[20], destination[20];
    float price[3]; 
    int availableSeats;

    int choice;
    int count = 0;

    FLIGHT updateFlight;
    FILE *fptr;
    fptr = fopen("flights.txt", "r+");
    
    while (fread(&updateFlight, sizeof(FLIGHT), 1, fptr)){
        if (!strcmp(flightID, updateFlight.flightID)){
            count = 1;
            p1: printf("Select what you want to update:\
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
                strcpy(updateFlight.date,date);
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                break;
            
            case 2:
                printf("Enter new departure time (HH:MM): ");
                scanf("%s", time);
                strcpy(updateFlight.time,time);
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                break;
            
            case 3:
                printf("Enter new source location: ");
                scanf("%s", source);
                strcpy(updateFlight.source,source);
                fseek(fptr, -sizeof(FLIGHT), 1);
                fwrite(&updateFlight, sizeof(FLIGHT), 1, fptr);
                break;
            
            case 4:
                printf("Enter new destination location: ");
                scanf("%s", destination);
                strcpy(updateFlight.destination,destination);
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

    if (!count){
        printf("Enter valid flight ID!\n");
    }
}

int main() {
    // addFlight();
    flightRead();

    return 0;
}