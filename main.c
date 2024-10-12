#include <stdio.h>

char board[8][8];
char makeBoard(char even, char odd, int outIt, int inIt);
int main() {
    //Sets ups the board with pieces in place
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            //0, 2, 4, 6 rows
            if(i % 2 == 0) {
                if((i == 6)) {
                    makeBoard('r', '2', i, j);
                }else {
                    makeBoard('1', '2', i, j);
                }
            // 1, 3, 5, 7 rows
             }else {
                if((i == 7)||(i == 5)) {
                    makeBoard('1', 'r', i, j);
                }else {
                    makeBoard('2', '1', i, j);
                }
             }
                    
        }
        printf("\n");
    }
}

char makeBoard(char even, char odd, int outIt, int inIt) {
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
