#include <stdio.h>

char board[8][8];

int main() {
    //Sets ups the board with pieces in place
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(i % 2 == 0) {
                if(j % 2 == 0) {
                    board[i][j] = '1';
                    printf("%c  ", board[i][j]);
                }else {
                    if(j != 7) {
                        if((j>=0 && j<=2)||(j>=5)) {
                            board[i][j] = 'r';
                            printf("%c  ", board[i][j]);
                        }else {
                            board[i][j] = '2';
                            printf("%c  ", board[i][j]);
                        }
                    }else {
                        board[i][j] = 'r';
                        printf("%c", board[i][j]);
                    }
                }
             }else {
                if(j % 2 == 0) {
                    board[i][j] = '2';
                    printf("%c  ", board[i][j]);
                }else {
                    if(j != 7) {
                        board[i][j] = '1';
                        printf("%c  ", board[i][j]);
                    }else {
                        board[i][j] = '1';
                        printf("%c", board[i][j]);
                    }
                }
             }
        }
        printf("\n");
    }
}

