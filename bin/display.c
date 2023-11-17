// #include <stdio.h>


void headerIntitial(){

    printf("=================================================================\n");
    printf("|                    Flight Reservation System                  |\n");
    printf("=================================================================\n");

}

// void headerCustomer(char* userID){

//     printf("=================================================================\n");
//     printf("|                     Logged in as %s                        |\n", userID);
//     printf("=================================================================\n");

// }

void headerCustomer(){

    printf("=================================================================\n");
    printf("|                       Customer Login                          |\n");
    printf("=================================================================\n");

}

void headerAdmin(){

    printf("=================================================================\n");
    printf("|                         Admin Login                           |\n");
    printf("=================================================================\n");

}

void awaitEnter() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nPress Enter to continue...");
    getchar();
}