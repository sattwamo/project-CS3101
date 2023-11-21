// structures used throughout the program
typedef struct
{
    char userType;
    char id[6];
    char email[50];
    char password[15];
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
    float price;
} TICKET;
