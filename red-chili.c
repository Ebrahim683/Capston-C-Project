#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#define MAX_LIMIT 50

// function declaration
void sign_up(int stakeholder);
void login(int stakeholder);
void welcomeScreen(char massage[100]);
void auth_init();
void showMenu();
void adminDashboard();
void insertFood();
void insertTable();
void booked_table();
void showTable();
void handleTableError();
void makeAOrder();
void deleteFood();
void customerDashboard();

struct Menu_Item
{
    char food_id[10];
    char food_name[50];
    char food_price[10];
};
struct Auth_User
{
    char userName[MAX_LIMIT];
    char userEmail[MAX_LIMIT];
    char userPassword[MAX_LIMIT];
};

int main()
{
    welcomeScreen(" Welcome to Red Chili Restaurant ");
    printf("\n\n\n");
    auth_init();
    return 0;
}

void welcomeScreen(char massage[100])
{
    system("cls");
    int i;
    char a[100] = "";
    strcpy(a, massage);
    printf("\n\n\n\n\t\t");
    for (i = 0; i < 20; i++)
    {
        printf("\xB2");
        Sleep(10);
    }
    for (i = 0; i < 35; i++)
    {
        printf(" ");
        printf("%c", a[i]);
        Sleep(60);
    }
    for (i = 0; i < 20; i++)
    {
        printf("\xB2");
        Sleep(10);
    }
}

void auth_init()
{
    int authChoice;
    int registerChoice;
    int loginChoice;
    printf("\t\t1. Login \n");
    printf("\t\t2. Register \n");
    printf("\t\tEnter your choice: ");
    scanf("%d", &authChoice);
    switch (authChoice)
    {
    case 1:
        system("cls");
        printf("\n\n\t\t===================================\n");
        printf("\t\t\t Login Here\n");
        printf("\t\t===================================\n");
        printf("\t\t1. Admin Login\n");
        printf("\t\t2. Customer Login\n");
        printf("Press(1/2): ");
        scanf("%d", &loginChoice);
        switch (loginChoice)
        {
        case 1:
            login(1);
            break;
        case 2:
            login(2);
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
        break;
    case 2:
        // Register Here
        system("cls");
        printf("\n\n\t\t===================================\n");
        printf("\t\t\tRegister Here\n");
        printf("\t\t===================================\n");
        printf("\t\t1. Admin Registration\n");
        printf("\t\t2. Customer Registration\n");
        printf("Press(1/2): ");
        scanf("%d", &registerChoice);
        switch (registerChoice)
        {
        case 1:
            sign_up(1);
            break;
        case 2:
            sign_up(2);
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
        break;

    default:
        break;
    }
}

void sign_up(int stakeholder)
{
    system("cls");
    printf("\n\n\t\t============================================\n");
    printf("\t\t\tEnter you information\n");
    printf("\t\t============================================\n");

    struct Auth_User auth_user;

    fflush(stdin);
    printf("Enter email: ");
    gets(auth_user.userEmail);
    printf("Enter password: ");
    gets(auth_user.userPassword);
    // make data for file
    char das = '-';
    char userDetails[200] = "";
    strncat(auth_user.userEmail, &das, 1);
    strcat(userDetails, auth_user.userEmail);
    strcat(userDetails, auth_user.userPassword);
    /* insert information to file */
    FILE *userInfo;
    // open the file
    if (stakeholder == 1)
    {
        userInfo = fopen("adminInfo.txt", "a");
    }
    if (stakeholder == 2)
    {
        userInfo = fopen("userInfo.txt", "a");
    }

    // handle error
    if (userInfo == NULL)
    {
        fprintf(stderr, "Error opened file\n");
        exit(1);
    }
    else
    {
        fputs(userDetails, userInfo);
        fputs("\n", userInfo);
        printf("\n\t\t\t***** Registration successful *****\n");
    }
    fclose(userInfo);
    Sleep(2);
    login(stakeholder);
}

void login(int stakeholder)
{

    system("cls");
    printf("\n\n\t\t============================================\n");
    printf("\t\t\tEnter you Login information\n");
    printf("\t\t============================================\n");
    struct Auth_User input_user_info;

    fflush(stdin);
    printf("Enter email: ");
    gets(input_user_info.userEmail);
    printf("Enter password: ");
    gets(input_user_info.userPassword);
    // make data for check
    char das = '-';
    char userDetails[200] = "";
    strncat(input_user_info.userEmail, &das, 1);
    strcat(userDetails, input_user_info.userEmail);
    strcat(userDetails, input_user_info.userPassword);
    // strcat(userDetails, "\n");

    char inputEmail[50], inputPassword[50];
    char ch;
    FILE *file;

    // check and file open
    /* stakeholder = 1 for admin  and 2 for customer */
    if (stakeholder == 1)
    {
        file = fopen("adminInfo.txt", "r");
    }
    if (stakeholder == 2)
    {
        file = fopen("userInfo.txt", "r");
    }

    if (file == NULL)
    {
        printf("File not found");
    }
    else
    {

        char singleInfo[50];
        int result = 1;
        while (!feof(file))
        {
            fgets(singleInfo, 50, file);
            singleInfo[strlen(singleInfo) - 1] = '\0';
            int res = strcmp(singleInfo, userDetails);
            if (res == 0)
            {
                result = 0;
            }
        }
        if (result == 0)
        {
            printf("\t\t\t\t********** Successfully Login *********\n");
        }
        else
        {
            printf("\t\t\t\t******* Invalid email or password **********\n");
        }
        fclose(file);
    }

    if (stakeholder == 1)
    {
        adminDashboard();
    }
    else if (stakeholder == 2)
    {
        customerDashboard();
    }
}

/* ====================================================================================

============                    Admin Dashboard                      ==================
======================================================================================= */

void adminDashboard()
{
    system("cls");
    printf("\n\n\t\t==================================================\n");
    printf("\t\t\t Welcome to Admin Dashboard\n");
    printf("\t\t==================================================");

    printf("\n\n\n");
    printf("\t\t 1. Add Food to Menu \n");
    printf("\t\t 2. Delete Food from Menu \n");
    printf("\t\t 3. Add empty Table \n");
    printf("\t\t 4. Logout \n");

    int adminDashboardChoice;
    printf("Enter your choice: ");
    scanf("%d", &adminDashboardChoice);

    switch (adminDashboardChoice)
    {
    case 1:
        // printf("Add food");
        insertFood();
        break;
    case 2:
        deleteFood();
        break;
    case 3:
        insertTable();
        break;
    case 4:
        // printf("Logout");

        system("cls");
        welcomeScreen("Welcome to RED CHILI Restaurant");
        printf("\n\n");
        auth_init();
        break;

    default:
        break;
    }
}

void insertFood()
{
    system("cls");
    fflush(stdin);
    struct Menu_Item newFood;
    printf("\n\n\t\t\t Insert a new Food item \n");
    printf("\t\t============================================\n");
    printf("\tEnter food information :\n\n");
    printf("\t1.Food id: ");
    gets(newFood.food_id);
    printf("\t2.Food name: ");
    gets(newFood.food_name);
    printf("\t3.Food price: ");
    gets(newFood.food_price);

    // make data for insert file
    char das = '-';
    char foodDetails[200] = "";
    strncat(newFood.food_id, &das, 1);
    strncat(newFood.food_name, &das, 1);

    strcat(foodDetails, newFood.food_id);
    strcat(foodDetails, newFood.food_name);
    strcat(foodDetails, newFood.food_price);

    // printf("%s", foodDetails);

    // insert to file
    FILE *menuFile;

    menuFile = fopen("menuList.txt", "a");

    // handle error
    if (menuFile == NULL)
    {
        printf("File not found\n");
        exit(1);
    }
    else
    {
        fputs(foodDetails, menuFile);
        fputs("\n", menuFile);
        printf("\n\t\t\t***** Food add to menu  Successful *****\n");
        sleep(2);
    }
    fclose(menuFile);

    int addMenuChoice;
    printf("\t 1. Add another item \n");
    printf("\t 2. Exit \n");
    printf("\t Press (1/2): ");
    scanf("%d", &addMenuChoice);
    if (addMenuChoice == 1)
    {
        insertFood();
    }
    else if (addMenuChoice == 2)
    {
        adminDashboard();
    }
    else
    {
        printf("Invalid choice");
        Sleep(2);
        adminDashboard();
    }
}

void showMenu()
{
    // system("cls");
    FILE *menuFile;
    menuFile = fopen("menuList.txt", "r");

    char menuList[100];

    if (menuFile == NULL)
    {
        printf("File does not exist");
    }
    else
    {
        printf("\n\n\n");
        printf("\t\t\tFood id\t\t\tFood Name\t\t\tFood Price\n");
        printf("\t\t\t-------\t\t\t---------\t\t\t-----------\n");
        char singleFood[200] = "";

        while (!feof(menuFile))
        {
            // printf("%s\n", singleFood);
            char *broken_str = strtok(singleFood, "-");
            /* ==================Formate menu for display=============================== */

            while (broken_str != NULL && singleFood != "\n")
            {
                printf("\t\t\t%s", broken_str);

                // printf("%s ", broken_str);
                broken_str = strtok(NULL, "-");
            }

            printf("\n");

            fgets(singleFood, 200, menuFile);
            singleFood[strlen(singleFood) - 1] = '\0';
        }
        fclose(menuFile);
    }
}

void insertTable()
{
    fflush(stdin);
    system("cls");
    showTable();
    printf("\n\n\t\t\t Enter Empty Table Number\n");
    printf("\t\t=========================================\n");
    char tableNumber[5], status[10];
    printf("\tEnter table number: ");
    gets(tableNumber);
    printf("\tEnter status\n\t(Available/Booked): ");
    gets(status);

    /* add table to file */
    char das = '-';
    char tableDetails[10] = "";
    strncat(tableNumber, &das, 1);
    strcat(tableDetails, tableNumber);
    strcat(tableDetails, status);

    FILE *tableFile;

    char singleTable[30] = "";

    tableFile = fopen("tableInfo.txt", "a");
    if (tableFile == NULL)
    {
        fprintf(stderr, "Error opened file\n");
        exit(1);
    }
    else
    {
        fputs(tableDetails, tableFile);
        // fputs("\n", tableFile);
        printf("\n\t\t\t***** Table Added *****\n");
    }
    fclose(tableFile);

    /* choice */
    int addMenuChoice;
    printf("\t\t 1. Add another Table \n");
    printf("\t\t 2. Exit \n");
    printf("\t\t Press (1/2): ");
    scanf("%d", &addMenuChoice);
    if (addMenuChoice == 1)
    {
        insertTable();
    }
    else if (addMenuChoice == 2)
    {
        adminDashboard();
    }
    else
    {
        printf("Invalid choice");
        Sleep(2);
        adminDashboard();
    }
}

void showTable()
{
    system("cls");
    FILE *tableFile;
    tableFile = fopen("tableInfo.txt", "r");

    char menuList[100];

    if (tableFile == NULL)
    {
        printf("File does not exist");
    }
    else
    {
        printf("\n\n\t\t\t See your Table Status\n");
        printf("\t\t=============================================\n\n");
        // printf("\n\n\n");
        printf("\t\t\tTable No\t\tStatus\n");
        printf("\t\t\t-------\t\t\t----------\n");
        char singleTable[20] = "";

        while (!feof(tableFile))
        {

            // printf("%s\n", singleTable);
            char *broken_str = strtok(singleTable, "-");
            /* ==================Formate menu for display=============================== */

            while (broken_str != NULL)
            {
                // broken_str = "";
                printf("\t\t\t%s", broken_str);

                // printf("%s ", broken_str);
                broken_str = strtok(NULL, "-");
            }
            printf("\n");
            fgets(singleTable, 20, tableFile);
            singleTable[strlen(singleTable) - 1] = '\0';
        }
        fclose(tableFile);
    }
}

void deleteFood()
{
    system("cls");
    fflush(stdin);
    showMenu();
    printf("\n\n\t\t\t Enter Deleted Food Info\n");
    printf("\t\t=============================================\n\n");
    char deletedId[5];
    printf("\t\tEnter Food id : ");
    gets(deletedId);

    int count = 1, lineNo, isDelete = 0;
    FILE *menuFile;
    menuFile = fopen("menuList.txt", "r");

    // find line number for delete food

    char singleFood[200] = "";

    while (!feof(menuFile))
    {

        char *broken_str = strtok(singleFood, "-");

        while (broken_str != NULL)
        {

            int compare = strcmp(broken_str, deletedId);
            if ((compare == 0) && ((count - 1) % 3 == 0))
            {
                lineNo = ((count - 1) / 3) + 1;
                isDelete = 1;
            }
            count++;
            broken_str = strtok(NULL, "-");
        }
        fgets(singleFood, 200, menuFile);
        singleFood[strlen(singleFood) - 1] = '\0';
    }
    fclose(menuFile);

    // delete food now

    if (isDelete == 1)
    {
        FILE *menuFile, *tempFile;
        menuFile = fopen("menuList.txt", "r");
        tempFile = fopen("temp.txt", "a");
        char buffer[250];

        char singleFood[200] = "";
        int i = 0;
        while (!feof(menuFile))
        {
            if (i != lineNo)
            {
                fputs(singleFood, tempFile);
            }
            i++;
            fgets(singleFood, 200, menuFile);
        }
        fclose(menuFile);
        fclose(tempFile);

        remove("menuList.txt");
        rename("temp.txt", "menuList.txt");

        printf("\n\t\t********* Delete Food Successful ********** \n\n");

        /* choice */
        int addMenuChoice;
        printf("\t\t 1. Delete another item \n");
        printf("\t\t 2. Exit \n");
        printf("\t\t Press (1/2): ");
        scanf("%d", &addMenuChoice);
        if (addMenuChoice == 1)
        {
            deleteFood();
        }
        else if (addMenuChoice == 2)
        {
            adminDashboard();
        }
        else
        {
            printf("Invalid choice");
            Sleep(2);
            adminDashboard();
        }
    }
    else
    {
        printf("\t\t**** Food Id not valid \n\n");
    }
}

/* ====================================================================================

============                    Customer Dashboard                      ==================
======================================================================================= */

void customerDashboard()
{
    system("cls");
    printf("\n\n\t\t==================================================");
    printf("\n\n\t\t\tWelcome to Customer Dashboard\n");
    printf("\t\t==================================================");
    printf("\n\n\n");
    printf("\t\t 1. Show The Menu \n");
    printf("\t\t 2. Show Table Status \n");
    printf("\t\t 3. Make an order\n");
    printf("\t\t 4. Reserve a table \n");
    printf("\t\t 5. Logout \n");

    int customerDashboardChoice;
    printf("Enter your choice: ");
    scanf("%d", &customerDashboardChoice);

    switch (customerDashboardChoice)
    {
    case 1:
        printf("\n\n\t\t\t\tMenu List\n");
        printf("\t\t\t================================\n");
        showMenu();
        /* choice */
        int addMenuChoice;
        printf("\t\t 1. Make Order \n");
        printf("\t\t 2. Exit \n");
        printf("\t\t Press (1/2): ");
        scanf("%d", &addMenuChoice);
        if (addMenuChoice == 1)
        {
            makeAOrder();
        }
        else if (addMenuChoice == 2)
        {
            customerDashboard();
        }
        else
        {
            printf("Invalid choice");
            Sleep(2);
            customerDashboard();
        }
        break;
    case 2:
        // printf("\n\n\t\tShow all Table Status");
        showTable();
        int addMenuChoice2;
        printf("\t\t 1. Reserve a Table \n");
        printf("\t\t 2. Exit \n");
        printf("\t\t Press (1/2): ");
        scanf("%d", &addMenuChoice2);
        if (addMenuChoice2 == 1)
        {
            booked_table();
        }
        else if (addMenuChoice2 == 2)
        {
            customerDashboard();
        }
        else
        {
            printf("Invalid choice");
            Sleep(2);
            customerDashboard();
        }
        break;
    case 3:
        // printf("Make an order");
        showMenu();
        printf("\n\nChoose from menu\n");
        makeAOrder();
        break;
    case 4:
        printf("\n\n\t\t\tReserve Your favorite table\n");
        printf("\t\t\t================================\n");
        booked_table();
        break;
    case 5:
        system("cls");
        welcomeScreen("Welcome to RED CHILI Restaurant");
        printf("\n\n\n");
        auth_init();
        break;

    default:
        break;
    }
}

void booked_table()
{
    system("cls");
    fflush(stdin);
    showTable();
    char tableNo[4];
    printf("\t\tEnter table number :");
    gets(tableNo);

    // table file open for updated
    FILE *tableFile;
    tableFile = fopen("tableInfo.txt", "r");

    int count = 1, lineNo, isBooked = 0;
    char checkedTable[20] = "";
    if (tableFile == NULL)
    {
        printf("File does not exist");
    }
    else
    {

        char singleTable[20] = "";

        while (!feof(tableFile))
        {
            char currentSingleTable[20] = "";
            strcat(currentSingleTable, singleTable);

            // printf("%s\n", singleTable);
            char *broken_str = strtok(singleTable, "-");
            /* ==================Formate menu for display=============================== */

            while (broken_str != NULL)
            {
                // broken_str = "";
                // printf("%s ", broken_str);
                int compare = strcmp(broken_str, tableNo);
                if ((compare == 0) && ((count - 1) % 2 == 0))
                {
                    lineNo = ((count - 1) / 2) + 1;
                    strcat(checkedTable, currentSingleTable);
                }
                count++;
                broken_str = strtok(NULL, "-");
            }
            // printf("\n");
            fgets(singleTable, 20, tableFile);
            singleTable[strlen(singleTable) - 1] = '\0';
        }
        fclose(tableFile);
    }

    // printf("%s", checkedTable);
    // check table is already booked

    char *checked_broken = strtok(checkedTable, "-");
    while (checked_broken != NULL)
    {
        // strcat(myStr, "");

        int compare = strcmp(checked_broken, "Available");
        if (compare == 0)
        {
            isBooked = 1;
        }
        // printf("%s ", checked_broken);
        checked_broken = strtok(NULL, "-");
    }
    // printf("%d", isBooked);

    // printf("Line no =%d status=%d", lineNo, isBooked);
    if (isBooked == 1)
    {
        FILE *tableFile, *tempFile;
        tableFile = fopen("tableInfo.txt", "r");
        tempFile = fopen("temp.txt", "a");
        char newStr[25] = "";
        char das = '-';
        strcat(newStr, tableNo);
        strncat(newStr, &das, 1);
        strcat(newStr, "Booked");
        char singleTable[20] = "";
        int i = 0;

        while (!feof(tableFile))
        {
            if (i == lineNo)
            {
                fputs(newStr, tempFile);
                fputs("\n", tempFile);
            }
            if (i != lineNo)
            {
                fputs(singleTable, tempFile);
            }
            i++;
            fgets(singleTable, 20, tableFile);
        }
        fclose(tableFile);
        fclose(tempFile);
        remove("tableInfo.txt");
        rename("temp.txt", "tableInfo.txt");
        printf("\n\t\t********* Table Reserved Successful ********** \n\n");

        int addMenuChoice;
        printf("\t\t 1. Reserve another table \n");
        printf("\t\t 2. Exit \n");
        printf("\t\t Press (1/2): ");
        scanf("%d", &addMenuChoice);
        if (addMenuChoice == 1)
        {
            booked_table();
        }
        else if (addMenuChoice == 2)
        {
            customerDashboard();
        }
        else
        {
            printf("Invalid choice");
            Sleep(2);
            customerDashboard();
        }
    }else{
        
        handleTableError();
    }

    
}
void handleTableError(){
    fflush(stdin);
    system("cls");
    printf("\t\t**** Table no not valid \n\n");
    sleep(3);
    customerDashboard();
}

void makeAOrder()
{
    system("cls");
    // show menu function
    showMenu();
    /* make order section */
    printf("\n\n\tHow many item do you need ? = ");
    int numOfFood;
    scanf("%d", &numOfFood);
    printf("\n");
    int orderChecked = 1;
    for (int i = 0; i < numOfFood;)
    {
        printf("\tEnter food id (%d) :", i + 1);
        int foodId;
        scanf("%d", &foodId);
        // food id convert to str
        char foodIDstr[20];
        itoa(foodId, foodIDstr, 10);
        // now open file and search food in the menu list
        FILE *menuFile;
        menuFile = fopen("menuList.txt", "r");
        if (menuFile == NULL)
        {
            printf("Error");
            exit(1);
        }
        int myCheck = 0;
        char singleFood[200] = "";
        while (!feof(menuFile))
        {
            // printf("%s \n", singleFood);
            char *broken_str = strtok(singleFood, "-");

            while (broken_str != NULL)
            {
                // printf("%s\n", broken_str);
                orderChecked = 1;
                int compare = strcmp(broken_str, foodIDstr);

                if (compare == 0)
                {

                    // printf("%d ", i);
                    i++;
                    myCheck = 1;
                }
                broken_str = strtok(NULL, "-");
            }

            fgets(singleFood, 200, menuFile);
            singleFood[strlen(singleFood) - 1] = '\0';
        }
        fclose(menuFile);
        if (myCheck == 0)
        {
            printf("\t\t****Invalid id ! try again\n");
        }
    }

    printf("\t\t**** Order successfully placed *******\n");
    sleep(3);
    customerDashboard();
}