# Stock Management System

## Project Description
A stock management system with an interactive menu featuring 10 different operations. The program allows adding stocks, displaying them, performing mathematical operations on prices, various sorting methods, and palindrome detection.

## Project Structure
- **Main File**: `stock-management.c`
- **Programming Language**: C
- **Supported Compiler**: GCC

## System Requirements
- GCC Compiler
- Operating System: Windows/Linux/MacOS

## Compilation and Execution

### Standard Compilation
```bash
gcc stock-management.c -o stock_management
./stock_management
```

### Running with Input/Output Files
```bash
gcc stock-management.c -o stock_management
./stock_management < input.txt > output.txt
```

## Menu Operations

### 1. Add Stock
- Add a new stock to the array
- **Stock Name**: Up to 20 characters, English letters only (A-Z, a-z)
- **Price**: Positive integer

### 2. Print Stocks
- Display all existing stocks in the system
- Format: `number. name - $price`

### 3. Double All Stocks Price
- Multiply all stock prices by 2

### 4. Drop Stocks Price by x%
- Reduce all stock prices by a certain percentage
- **Required Input**: Integer between 0-100

### 5. Find Less Expensive Stock
- Find and display the stock with the lowest price

### 6. Sort Stocks by Price
- Sort stocks from lowest to highest price

### 7. Sort Stocks Alphabetically
- Sort stocks alphabetically (A-Z)

### 8. Sort Stocks by ASCII Sum of Name
- Sort by the sum of ASCII values of the stock name characters

### 9. Check Palindromic Stock Names
- Check and identify stock names that are palindromes
- Case-insensitive check

### 10. Exit
- Exit the program

## Constraints and Conditions

### Menu Input
- One or two-digit number (0-99)
- Valid options: 1-10
- **Error System**: After 5 consecutive errors, the program will terminate
- Valid input resets the error counter

### System Limitations
- Maximum number of stocks: 10 (`MAX_STOCKS`)
- Stock name length: Up to 20 characters (`MAX_NAME_INPUT`)
- Maximum input length: 100 characters (`MAX_INPUT`)

## Data Structures

### Stock Structure
```c
typedef struct {
    char name[MAX_NAME_INPUT + 1];  // Stock name
    float price;                     // Stock price
} Stock;
```

## Main Functions

### Input and Validation Functions
- `get_valid_input()` - Get valid menu input
- `get_valid_name()` - Get valid stock name
- `get_valid_price()` - Get valid price
- `isValidName()` - Validate stock name
- `isValidPrice()` - Validate price
- `isValidPercent()` - Validate percentage

### Stock Management Functions
- `addStock()` - Add a stock
- `printStocks()` - Display stocks
- `doubleStocks()` - Double all prices
- `dropStocks()` - Drop prices by percentage
- `findLessExpensive()` - Find cheapest stock

### Sorting Functions
- `sortByPrice()` - Sort by price
- `sortByName()` - Sort alphabetically
- `sortByAsciiSum()` - Sort by ASCII sum

### Helper Functions
- `asciiSum()` - Calculate ASCII sum
- `isPalindrome()` - Check for palindrome
- `toLowerChar()` - Convert to lowercase
- `isEnglishLetter()` - Check if English letter
- `flushStdin()` - Clear input buffer

## Usage Examples

### Adding a Stock
```
Enter stock name: Apple
Enter stock price: 150

Stock added.
```

### Dropping Prices
```
Enter x%: 10

Stock prices has dropped by 10%.
```

### Finding Cheapest Stock
```
Less expensive stock: Tesla - $120.50
```

## Error Handling

### Input Errors
- Non-numeric input in menu
- Number outside range (0-99)
- Invalid stock name (non-letter characters)
- Negative or invalid price
- Percentage outside range (0-100)

### Error Messages
- `Invalid input.` - Invalid input
- `Invalid stock name.` - Invalid stock name
- `Invalid stock price.` - Invalid price
- `Invalid Percent.` - Invalid percentage
- `No stocks available.` - No stocks in system
- `There are no stocks to show.` - No stocks to display

## Important Notes
1. All inputs end with Enter key
2. Uses `fgets()` for input reading
3. All inputs must be validated
4. In sorting operations, items with equal values maintain their original order
5. Program uses only standard libraries: `stdio.h`, `string.h`


## License
This project was developed for the Introduction to Systems Programming course at Ben-Gurion University.
