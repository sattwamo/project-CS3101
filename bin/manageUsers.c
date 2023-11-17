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

void addAdmin()
{
    char id[6], email[50], password[5];
    char userType = 'A';
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

int checkUser()
{
    int isLogin = 0;
    USERS user;
    char id[6];
    char password[4];

    printf("Enter your login credentials\n");
    printf("enter your login id:\n");
    scanf("%s", id);

    if (isUserPresent(id))
    {
        user = viewUser(id);
        printf("enter your 4 digit pasword:\n");
        scanf("%s", password);
        if (strcmp(password, user.id))
        {
            isLogin = 1;
            printf("Login Succesfull\n");
        }
        else
        {
            printf("Incorrect Password\n");
        }
    }

    else
    {
        printf("Enter valid user ID\n");
    }
    return isLogin;
}

int checkAdmin()
{
    FILE *fptr;
    USERS viewadmin;
    fptr = fopen("./data/logins.txt", "r");
    char id[6];
    char password[4];
    int check = 0;
    printf("Enter your login credentials\n");
    printf("enter your login id:\n");
    scanf("%s", id);
    while (fread(&viewadmin, sizeof(USERS), 1, fptr))
    {
        if (!strcmp(id, viewadmin.id) && viewadmin.userType == 'A')
        {
            printf("enter your 4 digit pasword:\n");
            scanf("%s", password);
            if (!strcmp(password, viewadmin.password))
            {
                printf("Login Succesfull\n");
                check = 1;
            }
            else
            {
                printf("Incorrect Password\n");
                // return 0;
            }
        }
    }
    fclose(fptr);
    return check;
}
