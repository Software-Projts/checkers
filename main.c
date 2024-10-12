#include <stdio.h>

char board[8][8];
char makeBoard(char piece, char even, char odd, int outIt, int inIt);
int main() {
    //Sets ups the board with pieces in place
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            //2, 4, 6, 8 rows
            if(i % 2 == 0) {
                makeBoard('r', '1', '2', i, j);
            // 1, 3, 5, 7 rows
             }else {
                makeBoard('r', '2', '1', i, j);
             }
                    
        }
        printf("\n");
    }
}

char makeBoard(char piece, char even, char odd, int outIt, int inIt) {
    if(inIt % 2 == 0) {
        board[outIt][inIt] = even;
        printf("%c  ", board[outIt][inIt]);
    }else {
        if(inIt != 7) {
            board[outIt][inIt] = odd;
            printf("%c  ", board[outIt][inIt]);
        }else {
                board[outIt][inIt] = odd;
                printf("%c", board[outIt][inIt]);
        }
    }
}

