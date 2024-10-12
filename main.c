#include <stdio.h>

int board[8][8];

int main() {
    //Sets ups the board with pieces in place
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(i % 2 == 0) {
                if(j % 2 == 0) {
                    board[i][j] = 1;
                    printf("%d  ", board[i][j]);
                }else {
                    if(j != 7) {
                        board[i][j] = 2;
                        printf("%d  ", board[i][j]);
                    }else {
                        board[i][j] = 2;
                        printf("%d", board[i][j]);
                    }
                }
             }else {
                if(j % 2 == 0) {
                    board[i][j] = 2;
                    printf("%d  ", board[i][j]);
                }else {
                    if(j != 7) {
                        board[i][j] = 1;
                        printf("%d  ", board[i][j]);
                    }else {
                        board[i][j] = 2;
                        printf("%d", board[i][j]);
                    }
                }
             }
        }
        printf("\n");
    }
}
