#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 3
#define COLS 3


//Number of each symbol in each reel
const char *symbol[4] = {"A", "B", "C", "D"};
const int counts[4] = {2, 4, 6, 8};

//Value of each Symbol
typedef struct {
    char symbols;
    int value;
} SYMBOL_VALUE;

SYMBOL_VALUE values[] = {
    {'A', 5},
    {'B', 4},
    {'C', 3},
    {'D', 2}
};

char* addElement(char* array, int* size, char element){
    char* newArray = realloc(array, (*size + 1) * sizeof(char));
    //Error handling
    if(newArray == NULL){
        printf("Error allocating memory.\n");
        free(array);
        exit(EXIT_FAILURE);
    }
    newArray[*size] = element;
    (*size)++;
    return newArray;
}

void removeElement(char array[], int* size, int indexToRemove){
    if(indexToRemove < 0 || indexToRemove >= (*size)){
        printf("Index out of bounds.\n");
        return;
    }
    for(int i = indexToRemove; i < *size; i++){
        array[i] = array[i + 1];
    }
    (*size)--;
}

int deposit(){
    
    while(1){
        int depositAmount = 0; 
        printf("Enter the amount you wish to deposit: ");
        if(scanf("%d", &depositAmount) == 1 && depositAmount > 0){
            return depositAmount;
        }else{
            printf("Please enter a valid amount.\n");
            while (getchar() != '\n' && getchar() != EOF);
        }
    }   
}

int getNumberOfLines(){
    int lines;
    while(1){
        printf("Enter the number of lines(1-3): ");
        if(scanf("%d", &lines) == 1 && lines > 0 && lines <= 3){
            return lines;
        }else{
            printf("Please enter a valid number of lines.\n");
            while (getchar() != '\n' && getchar() != EOF);
        }
    }
}    

int getBettingAmount(int balance,int lines){
    int bet,betAmount = 0;
    while(1){
        printf("Enter the the amount to bet (per line): ");
        if(scanf("%d", &bet) == 1 && bet < balance/lines && bet > 0){
            return bet;
        }else{
            printf("You have insufficient funds! Please enter a valid betting amount.\n");
            while (getchar() != '\n' && getchar() != EOF);
        }
    }
}

char *spinSlot(){
    char* symbols = NULL;
    int symbolSize = 0;
    srand(time(NULL));
    for (int i = 0; i < sizeof(symbol)/sizeof(symbol[0]); i++) {
        for(int j = 0; j < counts[i]; j++){
            symbols = addElement(symbols, &symbolSize, symbol[i][0]);
        }
    }
    char *reelContent = malloc(ROWS * COLS * sizeof(char));
    if (reelContent == NULL){
        printf("Couldn't allocate memory");
        exit(EXIT_FAILURE);
    }
    //{{'A','A','A'}, {'A','A','A'}, {'A','A','A'}};
    for (int i = 0; i < COLS; i++) {
        int availableSymbolSize = 20;
        char availableSymbols[20];
        for (int j = 0; j < symbolSize; j++)availableSymbols[j] = symbols[j];
        for (int j = 0; j < ROWS; j++) {
            int selectedSymbol = rand() % symbolSize;
            reelContent[i * COLS + j] = availableSymbols[selectedSymbol];
            removeElement(availableSymbols, &symbolSize, selectedSymbol);
        }
    }
    free(symbols);
    return reelContent;    
}

char *transpose(char reels[]){
    char *rows = malloc(ROWS * COLS * sizeof(char));
    for (int i = 0; i < COLS; i++) {
        for(int j = 0; j < ROWS; j++){
            rows[i * COLS + j] = reels[j * COLS + i];
        }
    }
    return rows;
}

void printRows(char rows[]){
    for(int i =0; i < ROWS;i++){
        for(int j =0; j < COLS;j++){
            printf("%c", rows[i * COLS + j]);
            if ( j != COLS -1){
                printf(" | ");
            }
        }
        printf("\n");
    }
}

int getWinnings(char rows[], int bet, int lines){
    int winnings = 0;
    for (int row = 0; row < lines; row++){
        int allSame = 1;
        char *symbols;
        for (int i = 0; i < ROWS; i++) {
            symbols = &rows[row * COLS]; 
        }
        for (int i = 1; i < COLS; i++){
            if(symbols[i] != symbols[0]){
                allSame = 0;
                break;
            }
        }
        if(allSame == 1){
            printf("All Same. \n");
            for(int i = 0; i < sizeof(values)/sizeof(values[0]); i++){
                if(values[i].symbols == symbols[0]){
                    winnings += bet * values[i].value;
                    break;
                }
            }
        }
    }
        return winnings;
}

void game(){
    int balance = 0;
    balance += deposit();
    while(1){
        printf("\nYou have a balance of $ %d\n",balance);
        const int numberOfLines = getNumberOfLines();
        int bettingAmount = getBettingAmount(balance, numberOfLines);
        balance -= bettingAmount * numberOfLines;
        char *reels = spinSlot();
        char *rows = transpose(reels);
        printf("Reels: \n");
        printRows(rows);
        int winnings = getWinnings(rows, bettingAmount, numberOfLines);
        printf("You won $ %d\n", winnings);
        balance += winnings;
        if(balance <= 0){
            printf("You have insufficient funds!\n");
            break;
        }
        printf("Do you want to play again? (y/n): ");
        char playAgain;
        int result = scanf(" %c", &playAgain);
        if (result == 1 && playAgain == 'n' || playAgain == 'N'){
            break;
        }else{
            while (getchar() != '\n' && getchar() != EOF);
        }
    }
}
int main(){
    game();
}