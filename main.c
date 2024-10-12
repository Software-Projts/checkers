#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int piecNumber = 1;
char board[8][8];
char red[3];
char black[3];
char num1[];
char num2[];
//Functions
char makeBoard(char even[], char odd[], int outIt, int inIt);

//Main function
int main() {
    num1[0] = 1;
    num2[0] = 2;
    //Sets ups the board with pieces in place
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            //0, 2, 4, 6 rows
            if(i % 2 == 0) {
                
                if((i == 6)) {
                    char intToChar = '0' + piecNumber;
                    red[0] = 'r';
                    red[1] = intToChar;
                    red[2] = '\0';
                    makeBoard(num2, red, i, j);
                }else if ((i==0)||(i==2)) {
                    char intToChar = '0' + piecNumber;
                    black[0] = 'b';
                    black[1] = intToChar;
                    black[2] = '\0';
                    makeBoard(num1, black, i, j);
                }else {
                    makeBoard(num1, num2, i, j);
                }
            // 1, 3, 5, 7 rows
             }else {
                if((i == 7)||(i == 5)) {
                    char intToChar = '0' + piecNumber;
                    red[0] = 'r';
                    red[1] = intToChar;
                    red[2] = '\0';
                    makeBoard(red, num2, i, j);
                }else if(i==1) {
                    char intToChar = '0' + piecNumber;
                    black[0] = 'b';
                    black[1] = intToChar;
                    black[2] = '\0';
                    makeBoard(black, num2, i, j);
                }else {
                    makeBoard(num2, num1, i, j);
                }
             }        
        }
        printf("\n");
    }
}

char makeBoard(char even[], char odd[], int outIt, int inIt) {
    if(inIt % 2 == 0) {
        board[outIt][inIt] = even[0];
        printf("%c  ", board[outIt][inIt]);
    }else {
        if(inIt != 7) {
            board[outIt][inIt] = odd[0];
            printf("%c  ", board[outIt][inIt]);
        }else {
            board[outIt][inIt] = odd;
            printf("%c", board[outIt][inIt]);
        }
    }
}

