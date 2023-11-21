// functions handled by Sattwamo Ghosh, 21MS204
// functions to print the various headers
void headerIntitial(){

    printf("=================================================================\n");
    printf("|                    Flight Reservation System                  |\n");
    printf("=================================================================\n");

}

void headerCustomer(){

    printf("=================================================================\n");
    printf("|                       Customer Login                          |\n");
    printf("=================================================================\n");

}

void headerAdmin(){

    printf("=================================================================\n");
    printf("|                         Admin Panel                           |\n");
    printf("=================================================================\n");

}

void headerLoginAdmin(){

    printf("=================================================================\n");
    printf("|          ---       Logged in as $ADMIN$        ---            |\n");
    printf("=================================================================\n");

}

// function handled by Tanish Nimbalkar, 21MS207
// function to wait until user input detected
void awaitEnter() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Press Enter to continue...");
    getchar();
}