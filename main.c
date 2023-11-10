#include <stdio.h>

typedef struct flight{
    char flightID[5];
    char date[8];
    char time[5];
    char source[20];
    char destination[20];
    float price[3]; 
    int availableSeats;
}FLIGHT;

typedef struct ticket{
    char ticketNum[5];
    char flightID[5];
    char name[30];
    char priceType;
    char seatNum[3];
}TICKET;

int main(){
    printf("Samaaj");

    return 0;
}