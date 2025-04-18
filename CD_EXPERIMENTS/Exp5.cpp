#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function declarations
void calculateFollowFirstSet(char symbol, int productionIndex, int position);
void calculateFollowSet(char nonTerminal);
void calculateFirstSet(char symbol, int productionIndex, int position);
void printGrammar(void);

int totalProductions, firstSetIndex = 0;

// Arrays to store the results
char firstSetTable[10][100];
char followSetTable[10][100];
int followSetIndex = 0;

// Grammar storage
char grammarRules[10][10];
char followSet[10], firstSet[10];
int currentIndex;
char currentSymbol;
int currentProductionIndex;

int main(int argc, char** argv)
{
    int firstSetPos = 0;
    int followSetPos = 0;
    int i, choice;
    char symbol, currentChar;
    totalProductions = 8;

    // Initialize grammar rules
    strcpy(grammarRules[0], "E=TR");
    strcpy(grammarRules[1], "R=+TR");
    strcpy(grammarRules[2], "R=e");
    strcpy(grammarRules[3], "T=FY");
    strcpy(grammarRules[4], "Y=*FY");
    strcpy(grammarRules[5], "Y=e");
    strcpy(grammarRules[6], "F=(E)");
    strcpy(grammarRules[7], "F=i");

    // Print the input grammar
    printf("The Input Grammar is:\n");
    printGrammar();
    printf("\nOutput:\n");

    int tableIndex;
    char processedSymbols[totalProductions];
    int symbolCount = -1;

    // Initialize firstSetTable
    for (currentIndex = 0; currentIndex < totalProductions; currentIndex++) {
        for (tableIndex = 0; tableIndex < 100; tableIndex++) {
            firstSetTable[currentIndex][tableIndex] = '!';
        }
    }
    int currentPos = 0, nextPos, isProcessed;

    // Calculate and print First sets
    for (currentIndex = 0; currentIndex < totalProductions; currentIndex++) {
        symbol = grammarRules[currentIndex][0];
        nextPos = 0;
        isProcessed = 0;

        for (tableIndex = 0; tableIndex <= symbolCount; tableIndex++)
            if (symbol == processedSymbols[tableIndex])
                isProcessed = 1;

        if (isProcessed == 1)
            continue;

        calculateFirstSet(symbol, 0, 0);
        symbolCount += 1;

        processedSymbols[symbolCount] = symbol;
        printf("First(%c)= { ", symbol);
        firstSetTable[currentPos][nextPos++] = symbol;

        for (i = 0 + firstSetPos; i < firstSetIndex; i++) {
            int isDuplicate = 0, found = 0;

            for (isDuplicate = 0; isDuplicate < nextPos; isDuplicate++) {
                if (firstSet[i] == firstSetTable[currentPos][isDuplicate]) {
                    found = 1;
                    break;
                }
            }
            if (found == 0) {
                printf("%c, ", firstSet[i]);
                firstSetTable[currentPos][nextPos++] = firstSet[i];
            }
        }
        printf("}\n");
        firstSetPos = firstSetIndex;
        currentPos++;
    }
    printf("\n");
    printf("-----------------------------------------------\n\n");
    
    char processedFollowSymbols[totalProductions];
    symbolCount = -1;

    // Initialize followSetTable
    for (currentIndex = 0; currentIndex < totalProductions; currentIndex++) {
        for (tableIndex = 0; tableIndex < 100; tableIndex++) {
            followSetTable[currentIndex][tableIndex] = '!';
        }
    }
    currentPos = 0;
    int rulesProcessed = 0;
    
    // Calculate and print Follow sets
    for (currentProductionIndex = 0; currentProductionIndex < totalProductions; currentProductionIndex++) {
        currentSymbol = grammarRules[currentProductionIndex][0];
        nextPos = 0;
        isProcessed = 0;

        for (tableIndex = 0; tableIndex <= symbolCount; tableIndex++)
            if (currentSymbol == processedFollowSymbols[tableIndex])
                isProcessed = 1;

        if (isProcessed == 1)
            continue;
        rulesProcessed += 1;

        calculateFollowSet(currentSymbol);
        symbolCount += 1;

        processedFollowSymbols[symbolCount] = currentSymbol;
        printf("Follow(%c) = { ", currentSymbol);
        followSetTable[currentPos][nextPos++] = currentSymbol;

        for (i = 0 + followSetPos; i < followSetIndex; i++) {
            int isDuplicate = 0, found = 0;
            for (isDuplicate = 0; isDuplicate < nextPos; isDuplicate++) {
                if (followSet[i] == followSetTable[currentPos][isDuplicate]) {
                    found = 1;
                    break;
                }
            }
            if (found == 0) {
                printf("%c, ", followSet[i]);
                followSetTable[currentPos][nextPos++] = followSet[i];
            }
        }
        printf("}\n\n");
        followSetPos = followSetIndex;
        currentPos++;
    }
}

void printGrammar(void) {
    for(int i = 0; i < totalProductions; i++) {
        if(i > 0 && grammarRules[i][0] == grammarRules[i-1][0]) {
            printf("| ");
            for(int j = 2; grammarRules[i][j] != '\0'; j++) {
                printf("%c", grammarRules[i][j]);
            }
            printf("\n");
        } else {
            printf("%c -> ", grammarRules[i][0]);
            for(int j = 2; grammarRules[i][j] != '\0'; j++) {
                printf("%c", grammarRules[i][j]);
            }
            printf("\n");
        }
    }
}

void calculateFollowSet(char nonTerminal)
{
    int i, j;

    if (grammarRules[0][0] == nonTerminal) {
        followSet[followSetIndex++] = '$';
    }
    for (i = 0; i < 10; i++) {
        for (j = 2; j < 10; j++) {
            if (grammarRules[i][j] == nonTerminal) {
                if (grammarRules[i][j + 1] != '\0') {
                    calculateFollowFirstSet(grammarRules[i][j + 1], i, (j + 2));
                }

                if (grammarRules[i][j + 1] == '\0' && nonTerminal != grammarRules[i][0]) {
                    calculateFollowSet(grammarRules[i][0]);
                }
            }
        }
    }
}

void calculateFirstSet(char symbol, int productionIndex, int position)
{
    int j;

    if (!(isupper(symbol))) {
        firstSet[firstSetIndex++] = symbol;
    }
    for (j = 0; j < totalProductions; j++) {
        if (grammarRules[j][0] == symbol) {
            if (grammarRules[j][2] == 'e') {
                if (grammarRules[productionIndex][position] == '\0')
                    firstSet[firstSetIndex++] = 'e';
                else if (grammarRules[productionIndex][position] != '\0'
                         && (productionIndex != 0 || position != 0)) {
                    calculateFirstSet(grammarRules[productionIndex][position], 
                                   productionIndex, (position + 1));
                }
                else
                    firstSet[firstSetIndex++] = 'e';
            }
            else if (!isupper(grammarRules[j][2])) {
                firstSet[firstSetIndex++] = grammarRules[j][2];
            }
            else {
                calculateFirstSet(grammarRules[j][2], j, 3);
            }
        }
    }
}

void calculateFollowFirstSet(char symbol, int productionIndex, int position)
{
    int k;

    if (!(isupper(symbol)))
        followSet[followSetIndex++] = symbol;
    else {
        int tableRow = 0, tableCol = 1;
        for (tableRow = 0; tableRow < totalProductions; tableRow++) {
            if (firstSetTable[tableRow][0] == symbol)
                break;
        }

        while (firstSetTable[tableRow][tableCol] != '!') {
            if (firstSetTable[tableRow][tableCol] != 'e') {
                followSet[followSetIndex++] = firstSetTable[tableRow][tableCol];
            }
            else {
                if (grammarRules[productionIndex][position] == '\0') {
                    calculateFollowSet(grammarRules[productionIndex][0]);
                }
                else {
                    calculateFollowFirstSet(grammarRules[productionIndex][position], 
                                         productionIndex, position + 1);
                }
            }
            tableCol++;
        }
    }
}