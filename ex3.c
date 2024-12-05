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

//function that sets cube to -1s
void initCube(int cube[365][5][4]) {
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                cube[i][j][k] = -1;
            }
        }
    }
}

//checks if all the array is positive
int isArrayPositive(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) return 0;
    }
    return 1;
}

//checks if a certain value is in an array
int contains(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) return 1;
    }
    return 0;
}

//asks the user for a brand until they give a valid one
int inputBrand() {
    int brand;
    while (scanf(" %d", &brand) && (brand < 0 || brand >= NUM_OF_BRANDS))
        printf("This brand is not valid\n");
    return brand;
}

//same thing but for sales
void inputSales(int sales[NUM_OF_TYPES]) {
    while (scanf(" %d %d %d %d", &sales[0], &sales[1], &sales[2], &sales[3]) &&
           !isArrayPositive(sales, NUM_OF_TYPES))
        printf("The sales are not valid\n");
}

//updates the cube by the day's sales
void update(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS], int brand,
            int sales[NUM_OF_TYPES]) {
    for (int i = 0; i < NUM_OF_TYPES; i++) cube[days[brand]][brand][i] = sales[i];
    days[brand]++;
}

//finds the max value in an array and gives it and the index of it in the array
void max(int arr[], int size, int max[]) {
    for (int i = 0; i < size; i++) {
        if (arr[i] > max[0]) {
            max[0] = arr[i];
            max[1] = i;
        }
    }
}

//returns the sum of the array
int sum(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}


int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    initCube(cube);
    int days[NUM_OF_BRANDS] = {0};
    int choice;
    printMenu();
    scanf("%d", &choice);
    while (choice != done) {
        switch (choice) {
            case addOne:
                int brand = inputBrand(), sales[NUM_OF_TYPES];
                inputSales(sales);
                update(cube, days, brand, sales);
                break;
            case addAll:
                //an array that stores which brands were already added
                int added[] = {-1, -1, -1, -1, -1};

                while (contains(added, NUM_OF_BRANDS, -1)) {
                    printf("No data for brands ");
                    for (int i = 0; i < NUM_OF_BRANDS; i++) {
                        if (!contains(added, NUM_OF_BRANDS, i)) {
                            printf("%s ", brands[i]);
                        }
                    }
                    printf("\nPlease complete the data\n");
                    int brand1 = inputBrand(), sales1[NUM_OF_TYPES];
                    while (contains(added,NUM_OF_BRANDS, brand1)) {
                        printf("This brand is not valid\n");
                        brand1 = inputBrand();
                    }
                    inputSales(sales1);
                    added[brand1] = brand1;
                    update(cube, days, brand1, sales1);
                }
                break;
            case stats:
                printf("What day would you like to analyze?\n");
                int day;
                while (scanf(" %d", &day) && (day > days[0] || day < 1)) {
                    printf("Please enter a valid day.\nWhat day would you like to analyze?\n");
                }
                int salesForType[NUM_OF_TYPES];
                int salesForBrand[NUM_OF_BRANDS];
                int totalSales = 0;
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    for (int j = 0; j < NUM_OF_TYPES; j++) {
                        totalSales += cube[day - 1][i][j];
                        salesForBrand[i] += cube[day - 1][i][j];
                        salesForType[j] += cube[day - 1][i][j];
                    }
                }
                int maxBrand[2];
                int maxType[2];
                max(salesForBrand, NUM_OF_BRANDS, maxBrand);
                max(salesForType, NUM_OF_TYPES, maxType);
                printf(
                    "In day number %d:\n"
                    "The sales total was %d\n"
                    "The best sold brand with %d sales was %s\n"
                    "The best sold type with %d sales was %s\n", day, totalSales, maxBrand[0], brands[maxBrand[1]],
                    maxType[0], types[maxType[1]]);
                printf("\n");
                break;
            case print:
                printf("*****************************************\n\n");
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    printf("Sales for %s:\n", brands[i]);
                    for (int j = 0; j < days[0]; j++) {
                        printf("Day %d- ", j + 1);
                        for (int k = 0; k < NUM_OF_TYPES; k++) printf("%s: %d ", types[k], cube[j][i][k]);
                        printf("\n");
                    }
                }
                printf("\n*****************************************\n");
                break;
            case insights:
                int totalBrandProfit[NUM_OF_BRANDS], totalTypeProfit[NUM_OF_TYPES],
                        totalDayProfit[DAYS_IN_YEAR], bestBrand[2], bestType[2], bestDay[2];
                for (int i = 0; i < days[0]; i++) {
                    for (int j = 0; j < NUM_OF_BRANDS; j++) {
                        for (int k = 0; k < NUM_OF_TYPES; k++) {
                            totalBrandProfit[j] += cube[i][j][k];
                            totalTypeProfit[k] += cube[i][j][k];
                            totalDayProfit[i] += cube[i][j][k];
                        }
                    }
                }
                max(totalBrandProfit, NUM_OF_BRANDS, bestBrand);
                max(totalTypeProfit, NUM_OF_TYPES, bestType);
                max(totalDayProfit, days[0] - 1, bestDay);
                printf("The best-selling brand overall is %s: %d$\n"
                       "The best-selling type of car is %s: %d$\n"
                       "The most profitable day was day number %d: %d$\n",
                       brands[bestBrand[1]], bestBrand[0], types[bestType[1]],bestType[0], bestDay[1] + 1, bestDay[0]);
                break;

            case deltas:
                int delta[NUM_OF_BRANDS][DAYS_IN_YEAR] = {0};
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    for (int j = 0; j < NUM_OF_TYPES; j++) {
                        for (int k = 0; k < days[0] - 1; k++) {
                            delta[i][k] += cube[k + 1][i][j] - cube[k][i][j];
                        }
                    }
                }
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    float avg = (float)sum(delta[i], days[0] - 1) / (float)(days[0] - 1);
                    printf("Brand: %s, Average Delta: %f\n", brands[i], avg);
                }
                break;
            default:
                printf("Invalid input\n");
                break;
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}
