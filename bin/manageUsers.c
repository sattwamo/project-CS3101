void usersWrite(USERS *user)
{
    FILE *fptr;
    fptr = fopen("./data/logins.txt", "a");
    fwrite(user, sizeof(USERS), 1, fptr);
    fclose(fptr);
}

USERS viewUser(char *userID)
{
    FILE *fptr;
    USERS user, viewUser;
    fptr = fopen("./data/logins.txt", "r");

    while (fread(&viewUser, sizeof(USERS), 1, fptr))
    {
        if (strcmp(viewUser.id, userID) == 0)
        {
            user = viewUser;
        }
    }

    fclose(fptr);
    return user;
}

int isUserPresent(char *userID)
{
    int check = 0;
    FILE *fptr;
    USERS viewUser;
    fptr = fopen("./data/logins.txt", "r");

    while (fread(&viewUser, sizeof(USERS), 1, fptr))
    {
        if (strcmp(viewUser.id, userID) == 0)
        {
            check = 1;
        }
    }
    fclose(fptr);

    return check;
}

void addUser()
{
    char id[6], email[50], password[5];
    char userType = 'B';
    USERS newuser;
    printf("*** Enter the following details with care to register yourself on the system ***\n");
    newuser.userType = userType;
    printf(">>> Enter your email: ");
    scanf("%49s", email);
    printf(">>> Enter a 5 digit alphanumeric id: ");
    scanf("%5s", id);
    printf(">>> Enter a 4 digit password: ");
    scanf("%4s", password);
    strcpy(newuser.id, id);
    strcpy(newuser.email, email);
    strcpy(newuser.password, password);
    usersWrite(&newuser);
    printf("\n*** Your user id is succesfully created :) ***\n\n");
}

void addAdmin()
{
    char id[6], email[50], password[5];
    char userType = 'A';
    USERS newuser;
    printf("*** Enter the following details with care to register yourself on the system ***\n");
    newuser.userType = userType;
    printf(">>> Enter your email: ");
    scanf("%49s", email);
    printf(">>> Enter a 5 digit alphanumeric id: ");
    scanf("%5s", id);
    printf(">>> Enter your 4 digit password: ");
    scanf("%4s", password);
    strcpy(newuser.id, id);
    strcpy(newuser.email, email);
    strcpy(newuser.password, password);
    usersWrite(&newuser);
    printf("\n*** The admin ID has been succesfully created :) ***\n\n");
}

int checkUser()
{
    int isLogin = 0;
    USERS user;
    char id[6];
    char password[5];

    printf("\n*** Enter your login credentials. ***\n");
    printf(">>> Enter your user ID: ");
    scanf("%5s", id);

    if (isUserPresent(id))
    {
        user = viewUser(id);
        printf(">>> Enter your 4 digit pasword: ");
        scanf("%4s", password);
        if (!strcmp(password, user.password))
        {
            isLogin = 1;
            printf("\nLogin Succesful.\n");
        }
        else
        {
            printf("\nIncorrect Password!!\n");
            // awaitEnter();
        }
    }

    else
    {
        printf("\n*** Enter valid user ID! ***\n");
        // awaitEnter();
    }
    return isLogin;
}

int checkAdmin()
{
    FILE *fptr;
    USERS viewadmin;
    fptr = fopen("./data/logins.txt", "r");
    char id[6];
    char password[5];
    int check = 0;
    printf("*** Enter your credentials ***\n");
    printf(">>> Enter your admin ID: ");
    scanf("%5s", id);
    while (fread(&viewadmin, sizeof(USERS), 1, fptr))
    {
        if (!strcmp(id, viewadmin.id) && viewadmin.userType == 'A')
        {
            printf(">>> Enter the 4 digit pasword: ");
            scanf("%4s", password);
            if (!strcmp(password, viewadmin.password))
            {
                // printf("\nLogged in succesfully as ADMIN... \n");
                check = 1;
            }
            else
            {
                printf("\n*** Incorrect Password ***\n");
            }
        }
    }
    fclose(fptr);
    return check;
}
