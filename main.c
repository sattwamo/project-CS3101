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
    char ticketNum[6];
    char flightID[6];
    char name[30];
    char priceType;
    char seatNum[4];
}TICKET;

void flightWrite(FLIGHT* flight){
    FILE *fptr;
    fptr = fopen("flights.txt", "a");

    fwrite(flight, sizeof(FLIGHT), 1, fptr);
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

int main() {
    addFlight();
    flightRead();

    return 0;
}