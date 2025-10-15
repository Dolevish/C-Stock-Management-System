#include <stdio.h>
#include <string.h>

#define MAX_ERRORS 5 // max number of errors in row in the input
#define MAX_INPUT 100 // max number of chars in the input
#define MAX_STOCKS 10 // max number of stocks in the stocks array
#define MAX_NAME_INPUT 20 // max number of chars in the stock name input



typedef struct {
    char name[MAX_NAME_INPUT + 1];
    float price;
} Stock;

void printMenu(); //function to print the main menu.
int get_valid_input(); //function to get a valid input from the user.
void get_valid_name(char*); //function to get a valid name of a stock from the user.
int isEnglishLetter(char); // function to check if a char is an English letter.
void get_valid_price(float* ptr_price); //function to get a valid price of a stock from the user.
void printNoStocksMessage(); //function to tell the user to enter stock.
void flushStdin();  //clean the get buffer
void addStock(Stock stocks[], int* ptr_stock_count); // add new stock
int isValidName(const char* str_buf);
int isValidPrice(const char* str_buf, float* ptr_price);
void printStocks(Stock stocks[], int stock_count);
void doubleStocks(Stock stocks[], int stock_count);
void dropStocks(Stock stocks[], int stock_count);
int isValidPercent(const char* str_buf, int* ptr_percent);
void findLessExpensive(Stock stocks[], int stock_count);
void sortByPrice(Stock stocks[], int stock_count);
void sortByName(Stock stocks[], int stock_count);
void sortByAsciiSum(Stock stocks[], int stock_count);
int asciiSum(const char* str);
void findPalindromes(Stock stocks[], int stock_count);
int isPalindrome(const char* str);
char toLowerChar(char c);


int main(void) {
    unsigned int input;
    Stock stocks[MAX_STOCKS];
    int stock_count = 0; // how many stocks

    while (1) {

        input = get_valid_input();
        // valid input. do switch - case
        printf("\n");

        switch (input) {
            case -1:
                // got to MAX_ERRORS
                return 1; // invalid exit code

            case 1:
                addStock(stocks,&stock_count);
                break;

            case 2:
                if (stock_count == 0) {
                    printf("There are no stocks to show.\n");
                }
                else {
                    printStocks(stocks, stock_count);
                }
                break;

            case 3:
                if (stock_count == 0) {
                    printNoStocksMessage();
                    continue;
                }
                // double all the stock prices
                doubleStocks(stocks, stock_count);
                break;

            case 4:
                if (stock_count == 0) {
                    printNoStocksMessage();
                    continue;
                }
                // what percentage?
                dropStocks(stocks, stock_count);
                break;

            case 5:
                if (stock_count == 0) {
                    printNoStocksMessage();
                    continue;
                }
               findLessExpensive(stocks, stock_count);
                break;

            case 6:
                if (stock_count == 0) {
                    printNoStocksMessage();
                    continue;
                }
                sortByPrice(stocks, stock_count);
                printf("Sorted by price.\n");
                break;

            case 7:
                if (stock_count == 0) {
                    printNoStocksMessage();
                    continue;
                }
                sortByName(stocks, stock_count);
                printf("Sorted by name.\n");
                break;

            case 8:
                if (stock_count == 0) {
                    printNoStocksMessage();
                    continue;
                }
                sortByAsciiSum(stocks, stock_count);
                printf("Sorted by ASCII sum.\n");
                break;

            case 9:
                if (stock_count == 0) {
                    printNoStocksMessage();
                    continue;
                }
                findPalindromes(stocks, stock_count);
                break;

            case 10:
                printf("Exiting program...\n");
                return 0;
        }
    }
}

void printNoStocksMessage() {
    printf("No stocks available.\n");
}

void printStocks(Stock stocks[], int stock_count) {
        // print all the stocks
        for (int i = 0; i < stock_count; i++) {
            printf("%d. %s - $%.2f\n", i + 1, stocks[i].name, stocks[i].price);

    }

}

void printMenu() {
    printf("\n");
    printf("=== Stock Management Menu ===\n");
    printf("1. Add Stock\n");
    printf("2. Print Stocks\n");
    printf("3. Double All Stocks Price\n");
    printf("4. Drop Stocks Price by x%%\n");
    printf("5. Find Less Expensive Stock\n");
    printf("6. Sort Stocks by Price\n");
    printf("7. Sort Stocks Alphabetically\n");
    printf("8. Sort Stocks by ASCII Sum of Name\n");
    printf("9. Check Palindromic Stock Names\n");
    printf("10. Exit\n");
    printf("Please enter a number between 0-99: ");
}

int get_valid_input() {
    // returns the valid input, or exits the code.
    char buffer[MAX_INPUT];
    int number;
    int errors = 0;

    while (errors < MAX_ERRORS) {

        if (errors == 0)
            printMenu();
        else
            printf("Please enter a number between 0-99: ");

        //flushStdin();
        // gets a full row of input from the user - checks if the input is legal.
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            // Either there is an input error or we reached EOF before we received anything.
            errors++;
            printf("\nInvalid input.\nYou made %d errors from %d, try again.\n",
                   errors, MAX_ERRORS);
            continue;  //back for another input
        }

        if (buffer[0] == ' ' || buffer[0] == '\t' || buffer[0] == '\n') {
            errors++;
            printf("\nInvalid input.\nYou made %d errors from %d, try again.\n",
                               errors, MAX_ERRORS);
            continue;
        }

        // trying to convert the input to an integer
        char extra;
        if (sscanf(buffer, "%d %c", &number, &extra) != 1) {
            // if there is another char after the integer, not including spaces, it is an illegal input.
            errors++;
            printf("\nInvalid input.\nYou made %d errors from %d, try again.\n", errors, MAX_ERRORS);
            continue; //back for another input
        }

        // the input is integer. is it in the range?
        if (number >= 1 && number <= 10)
            return number; // valid input
        if (number >= 0 && number <= 99) {
            printf("\nNot in menu option.\n");
            errors = 0; // valid input zeros the errors.
            continue; // back for another input
        }
        //illegal input.
        errors++;
        printf("\nInvalid input.\nYou made %d errors from %d, try again.\n", errors, MAX_ERRORS);

    }

    // got to MAX_ERRORS
    printf("Exiting program...\n");
    return -1;
}

int isEnglishLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void flushStdin() {
    // empties buffer.
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int isValidName(const char* str_buf) {
    int len = strlen(str_buf);
    if (len == 0 || len > MAX_NAME_INPUT) {
        flushStdin();
        return 0; // Invalid stock name
    }
    for (int i = 0; i < len; i++) {
        if (!isEnglishLetter(str_buf[i])) return 0; // Invalid stock name
    }
    return 1;  // valid stock name
}

void get_valid_name(char* nameBuffer) {
    // updates the valid input.
    // enter a string of 20 chars.
    printf("Enter stock name: ");
    fgets(nameBuffer, MAX_NAME_INPUT + 2, stdin); // 21 chars including '\0'
    nameBuffer[strcspn(nameBuffer, "\n")] = '\0'; // if there is \n, removes it.
    if (!isValidName(nameBuffer)) {
        // invalid name
        //printf("Invalid stock name.\n");
        nameBuffer[0] = '\0';
        //flushStdin();
    }
}

int isValidPrice(const char* str_buf, float* ptr_price) {
    int number; char extra;

    //user pressed enter only → valid
    if (str_buf[0] == '\0') {
        number = 0;
        *ptr_price = (float)number;
        return 1; // treat empty input as valid (do not change price)
    }

    if (sscanf(str_buf, "%d%c", &number, &extra) != 1 || number < 0) {
        return 0; //Invalid price
    }

    // valid price - update price
    *ptr_price = (float)number;
    return 1;
}

void get_valid_price(float* ptr_price) {
    // returns the valid input.
    char buffer[MAX_INPUT];

    // enter a positive integer
    printf("\nEnter stock price: ");
    fgets(buffer, sizeof(buffer), stdin) ;
    // Remove newline if present
    buffer[strcspn(buffer, "\n")] = '\0';
    if (!isValidPrice(buffer, ptr_price)) {
        // invalid price
        ptr_price[0] = 0.1f;
    }
}

void addStock(Stock stocks[], int* ptr_stock_count) {
    get_valid_name(stocks[*ptr_stock_count].name);
    if (stocks[*ptr_stock_count].name[0] == '\0') {
        printf("\nInvalid stock name.\n");
    } else {
        get_valid_price(&stocks[*ptr_stock_count].price);
        if ((stocks[*ptr_stock_count].price) == 0.1f) {
            printf("\nInvalid stock price.\n");
        } else {
            (*ptr_stock_count)++;
            printf("\nStock added.\n");
            //printf("stock amount: %d", *ptr_stock_count);
        }
    }
}

void dropStocks(Stock stocks[], int stock_count) {
    char buffer[MAX_INPUT];
    int x ;

    // enter a positive integer
    printf("Enter x%%: ");
    fgets(buffer, sizeof(buffer), stdin);
    if (isValidPercent(buffer,&x) == 0) {
        printf("\nInvalid Percent.\n");
        return;
    }
    for (int i = 0; i < stock_count; i++) {
        stocks[i].price *= (float)(100 - x) / 100;
    }
    printf("\nStock prices has dropped by %d%%.\n", x);
}

int isValidPercent(const char* str_buf, int* ptr_percent) {
    int number;
    if (str_buf == NULL) {  // stdin - the input is from the keyboard
        return 0;
    }
    // trying to convert the input to an integer
    char extra;
    if (sscanf(str_buf, "%d %c", &number, &extra) != 1) {
        // if there is another char after the integer, not including spaces, it is an illegal input.
       return 0;
    }

    // the input is integer. is it positive?
    if (number >= 0 && number <= 100) {
        *ptr_percent = number;
        return 1; // valid input
    }
    return 0;
}

void doubleStocks(Stock stocks[], int stock_count) {
    for (int i = 0; i < stock_count; i++) {
        stocks[i].price *= 2;
    }
    printf("Stock prices have doubled.\n");
}

void findLessExpensive(Stock stocks[], int stock_count) {
    int index = 0;
    for (int i = 1; i < stock_count; i++) {
        if (stocks[i].price < stocks[index].price)
            index = i;
    }
    printf("Less expensive stock: %s - $%.2f\n", stocks[index].name, stocks[index].price);
}

void sortByPrice(Stock stocks[], int stock_count) {
    int i, j;
    Stock temp;
    for (i = 0; i < stock_count - 1; i++) {
        for (j = 0; j < stock_count - i - 1; j++) {
            if (stocks[j].price > stocks[j + 1].price) {
                temp = stocks[j];
                stocks[j] = stocks[j + 1];
                stocks[j + 1] = temp;
            }
        }
    }
}

void sortByName(Stock stocks[], int stock_count) {
    int i, j;
    Stock temp;
    for (i = 0; i < stock_count - 1; i++) {
        for (j = 0; j < stock_count - i - 1; j++) {
            if (strcmp(stocks[j].name, stocks[j + 1].name) > 0) {
                temp = stocks[j];
                stocks[j] = stocks[j + 1];
                stocks[j + 1] = temp;
            }
        }
    }
}

int asciiSum(const char* str) {
    int sum = 0;
    while (*str != '\0') {
        sum += (int)(*str);
        str++;
    }
    return sum;
}

void sortByAsciiSum(Stock stocks[], int stock_count) {
    int i, j;
    Stock temp;
    for (i = 0; i < stock_count - 1; i++) {
        for (j = 0; j < stock_count - i - 1; j++) {
            if (asciiSum(stocks[j].name) > asciiSum(stocks[j + 1].name)) {
                temp = stocks[j];
                stocks[j] = stocks[j + 1];
                stocks[j + 1] = temp;
            }
        }
    }
}

char toLowerChar(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

int isPalindrome(const char* str) {
    int i = 0;
    int j = strlen(str) - 1;
    while (i < j) {
        char a = toLowerChar(str[i]);
        char b = toLowerChar(str[j]);
        if (a != b) {
            return 0;
        }
        i++;
        j--;
    }
    return 1;
}

void findPalindromes(Stock stocks[], int stock_count) {
    int i;
    int found = 0;
    for (i = 0; i < stock_count; i++) {
        if (isPalindrome(stocks[i].name)) {
            printf("Palindrome stock: %s\n", stocks[i].name);
            found = 1;
        }
    }
    if (!found) {
        printf("No palindromic stock names found.\n");
    }
}

