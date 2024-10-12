#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int piecNumber = 1;
int board[8][8];
//Functions
char makeBoard(int even, int odd, int outIt, int inIt);

//Main function
int main() {
    //Sets ups the board with pieces in place
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            //0, 2, 4, 6 rows
            if(i % 2 == 0) {
                
                if((i == 6)) {
                    makeBoard(2, 1, i, j);
                }else if ((i==0)||(i==2)) {
                    makeBoard(1, 2, i, j);
                }else {
                    makeBoard(1, 2, i, j);
                }
            // 1, 3, 5, 7 rows
             }else {
                if((i == 7)||(i == 5)) {
                    makeBoard(1, 2, i, j);
                }else if(i==1) {
                    makeBoard(1, 2, i, j);
                }else {
                    makeBoard(2, 1, i, j);
                }
             }        
        }
        printf("\n");
    }
}

char makeBoard(int even, int odd, int outIt, int inIt) {
    if(inIt % 2 == 0) {
        board[outIt][inIt] = 2;
        printf("%d  ", board[outIt][inIt]);
    }else {
        if(inIt != 7) {
            board[outIt][inIt] = 1 ;
            printf("%d  ", board[outIt][inIt]);
        }else {
            board[outIt][inIt] = 1;
            printf("%d", board[outIt][inIt]);
        }
    }
}

