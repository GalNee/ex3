/******************
Name: Gal Neeman
ID: 331981365
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};


void printMenu() {
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
        "1.Enter Daily Data For A Brand\n"
        "2.Populate A Day Of Sales For All Brands\n"
        "3.Provide Daily Stats\n"
        "4.Print All Data\n"
        "5.Provide Overall (simple) Insights\n"
        "6.Provide Average Delta Metrics\n"
        "7.exit\n");
}


void initCube(int cube[365][5][4]) {
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                cube[i][j][k] = -1;
            }
        }
    }
}

int isArrayPositive(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) return 0;
    }
    return 1;
}

void add1(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[]) {
    printf("hello world\n");
    int brand, sales[4];
    while (scanf("%d\n", &brand) && (brand < 0 || brand >= NUM_OF_BRANDS))
        printf("This brand is not valid\n");
    printf("Enter the sales for the brand\n");
    while (scanf(" %d %d %d %d\n", &sales[0], &sales[1], &sales[2], &sales[3]) &&
        !isArrayPositive(sales, 4)) printf("The sales are not valid\n");
    for (int i = 0; i < 4; i++) cube[days[brand]][brand][i] = sales[i];
    days[brand]++;
}

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    initCube(cube);
    int days[NUM_OF_BRANDS];
    int choice;
    printMenu();
    scanf("%d", &choice);
    while (choice != done) {
        switch (choice) {
            case addOne:
                add1(cube, days);
                break;

            case addAll:

                break;
            case stats:
                break;
            case print:
                break;
            case insights:
                break;
            case deltas:
                break;
            /*
             ......
             */
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}
