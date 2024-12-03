#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
char board[8][8];
//1 is a blank space
//2 is a unusable
//r is red(unkinged)
//b is black(unkinged)
//R is red King
//B is black King
int pieceNum = 1;
char playerTurn; //will hold 'b' or 'r' for whoevers turn in currently is
//add [] to board
int gone = -1;
bool done = false;

//Functions
char makeBoard(char even, char odd, int outIt, int inIt);
void printBoard();
void turn();
void getUserInput();
int convertLetter(char a);
bool pieceCanMove(int row, int col, char playerT);
char getYesOrNo();
bool isWithinBounds(int row, int col);
bool HasAnyLegalMoves(char playerT);
void TheKinging();
bool surrender();
char playAgain(int turn);

//Main function
int main() {

    while(playAgain(gone) == 'y') {
    done = false;
    gone = 0;
    //Sets black to have the first turn
    playerTurn = 'b';
    //Sets ups the board with pieces in place
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            //0, 2, 4, 6 rows
            if(i % 2 == 0) {
                
                if((i == 6)) {
                    makeBoard('r', '2', i, j);
                }else if ((i==0)||(i==2)) {
                    makeBoard('b', '2', i, j);
                }else {
                    makeBoard('1', '2', i, j);
                }
            // 1, 3, 5, 7 rows
             }else {
                if((i == 7)||(i == 5)) {
                    makeBoard('2', 'r', i, j);
                }else if(i==1) {
                    makeBoard('2', 'b', i, j);
                }else {
                    makeBoard('2', '1', i, j);
                }
             }        
        }
        // r == 72
        // b == 62
        printf("\n");
    }
    printf("\n");
    printBoard();
    while(HasAnyLegalMoves(playerTurn) && !done)
    {
    turn();
    }
    if(playerTurn == 'r')
    {
        printf("Congratulations Black you win!\n");
    }
    if(playerTurn == 'b')
    {
        printf("Congratulations Red you win!\n");
    }
}
    
}


char makeBoard(char even, char odd, int outIt, int inIt) {
    if(inIt % 2 == 0) {
        board[outIt][inIt] = odd;
    }else {
        board[outIt][inIt] = even;
    }
}

void printBoard() //for printing the board after every turn (we can add the graphics corresponding to values of the board later)
{
    printf("       a  b  c  d  e  f  g  h\n");
    printf("\n");
    for(int i=0; i<8; i++)
    {
        printf("%d      ", 8-i);
        for(int j=0; j<8;j++)
        {
            printf("%c  ", board[i][j]);
        }
        printf("\n");
    }

}

void turn()
{  
    
    int i = -1;
    int j = -1;
    if(playerTurn =='b')
    {
            gone++;
            //char checkIn[2];
            printf("It's Black's turn!\n");
            done = surrender(gone);
            if(done == true) {
                printf("Black resigned.\n");
                gone = 0;
                return;
            }
            printf("Please enter the piece you want to move.\n");
            //scanf("%2s", checkIn);
            char input[3]; //used for initial location
            char input2[3];
            //char input2[3]; //will be used for the end location later
            getUserInput(input);
            i= 7-(input[1]-'1');
            j = convertLetter(input[0]);
        //checks and makes user reinput
        while((playerTurn == 'b') && (!(board[i][j] == 'b' ||board[i][j] == 'B')|| !(pieceCanMove(i, j, playerTurn))))
        {
            if(!(board[i][j] == 'b' || board[i][j] == 'B'))
            {
                printf("This is not your piece!\n");
                printf("The value at this spot is: %c\n", board[i][j]);
                printf("Please enter the location of the piece you'd like to move.\n");
                getUserInput(input);
                i= 7-(input[1]-'1');
                j = convertLetter(input[0]);
            }
            if(!(pieceCanMove(i, j, playerTurn)))
            {
                printf("This piece you chose cannot move.\n");
                printf("The value at this spot is: %c\n", board[i][j]);
                printf("Please enter a different location of the piece you'd like to move.\n");
                getUserInput(input);
                i= 7-(input[1]-'1');
                j = convertLetter(input[0]);
            }
        }
        if((playerTurn == 'b') && (board[i][j] == 'b' || board[i][j] == 'B'))
        {
            printf("This is your piece!\n");
            printf("The value at this spot is: %c\n", board[i][j]); // this is a check statement
            
            printf("Where would you like to move?\n");
            //printf("It gets to right before input2\n");

            getUserInput(input2);
            int i2= 7-(input2[1]-'1');
            int j2= convertLetter(input2[0]);
            int doubleJump = 0;
            int validMove = 0;
            //take piece if statements
            if(board[i][j] == 'b')
            {
                printf("The value at %s is: %c\n", input2, board[i2][j2]);
                //printf("I2: %d\n", i2);
                //printf("i+1: %d\n", i+1);
                //printf("J2: %d\n", j2);
                //printf("J+1: %d\n", j+1);
                if(board[i2][j2] == '1')
                {
                    if((i2 == i+1) && (j2 == j-1))
                    {
                        board[i][j] = '1';
                        board[i2][j2] = 'b';
                        validMove = 1; 
                        //printf("I'm here it worked u saved me");
                    }
                    else
                    {
                        //this is empty !!!
                    }
                }
                if((isWithinBounds(i+1, j+1)) && (board[i+1][j+1] == '1'))    // make sure to get rid of the elses to fix the rest of the shit.
                {
                    if((i2 == i+1) && (j2 == j+1))
                    {
                        board[i][j] = '1';
                        board[i2][j2] = 'b';
                        validMove = 1;
                        //printf("I'm here it worked u saved me");
                    }
                }
                if(((isWithinBounds(i+1, j-1) && (isWithinBounds(i+2, j-2)))) && (((board[i+1][j-1] == 'r') || (board[i+1][j-1] == 'R')) && (board[i+2][j-2] == '1')))
                {
                    if((i2 == i+2) && (j2 == j-2))
                    {
                        board[i][j] = '1';
                        board[i+1][j-1] = '1';
                        board[i+2][j-2] = 'b';
                        validMove = 1;
                        doubleJump = 1;
                    }
                }
                if((isWithinBounds(i+1, j+1) && (isWithinBounds(i+2, j+2))) && ((board[i+1][j+1] == 'r') || (board[i+1][j+1] == 'R')) && (board[i+2][j+2] == '1'))
                {
                if((i2 == i+2) && (j2 == j+2))
                    {
                        board[i][j] = '1';
                        board[i+1][j+1] = '1';
                        board[i+2][j+2] = 'b';
                        validMove = 1;
                        doubleJump = 1;
                    } 
                }
                while (validMove == 0)
                {
                    printf("please input a valid move!\n");
                    printf("The value at %s is: %c\n", input2, board[i2][j2]);
                    getUserInput(input2);
                    i2= 7-(input2[1]-'1');
                    j2= convertLetter(input2[0]);
                    printf("The value at %s is: %c\n", input2, board[i2][j2]);
                    doubleJump = 0;
                    validMove = 0;
                    //take piece if statements
                    if(board[i][j] == 'b')
                    {
                        if((isWithinBounds(i+1, j-1)) && board[i+1][j-1] == '1')
                        {
                            if((i2 == i+1) && (j2 == j-1))
                            {
                                board[i][j] = '1';
                                board[i2][j2] = 'b';
                                validMove = 1; 
                            }
                        }
                        if((isWithinBounds(i+1, j+1)) && (board[i+1][j+1] == '1'))
                        {
                            if((i2 == i+1) && (j2 == j+1))
                            {
                                board[i][j] = '1';
                                board[i2][j2] = 'b';
                                validMove = 1;
                            }
                        }
                        if((isWithinBounds(i+1, j-1) && (isWithinBounds(i+2, j-2))) && (((board[i+1][j-1] == 'r') || (board[i+1][j-1] == 'R')) && (board[i+2][j-2] == '1')))
                        {
                            if((i2 == i+2) && (j2 == j-2))
                            {
                                board[i][j] = '1';
                                board[i+1][j-1] = '1';
                                board[i+2][j-2] = 'b';
                                validMove = 1;
                                doubleJump = 1;
                            }
                        }
                        if((isWithinBounds(i+1, j+1) && (isWithinBounds(i+2, j+2))) && ((board[i+1][j+1] == 'r') || (board[i+1][j+1] == 'R')) && (board[i+2][j+2] == '1'))
                        {
                        if((i2 == i+2) && (j2 == j+2))
                            {
                                board[i][j] = '1';
                                board[i+1][j+1] = '1';
                                board[i+2][j+2] = 'b';
                                validMove = 1;
                                doubleJump = 1;
                            } 
                        }
                    }
                }
            TheKinging();
            printBoard();
            }
            //printBoard after validMOVE




                //IMPORTANT DISTINCTION 
                //ABOVE WAS THE UNKINGED black,  BELOW IS KINGED BLACK

            if(board[i][j] == 'B') // the first step is to replace 'b' with 'B'
            {  
            
                printf("The value at %s is: %c\n", input2, board[i2][j2]);
                //printf("I2: %d\n", i2);
                //printf("i+1: %d\n", i+1);
                //printf("J2: %d\n", j2);
                //printf("J+1: %d\n", j+1);
                if(board[i2][j2] == '1')
                {
                    if((i2 == i+1) && (j2 == j-1))
                    {
                        board[i][j] = '1';
                        board[i2][j2] = 'B';
                        validMove = 1; 
                        //printf("I'm here it worked u saved me");
                    }
                    else
                    {
                        //this is empty !!!
                    }
                }
                if(isWithinBounds(i+1,j+1) && (board[i+1][j+1] == '1'))    // make sure to get rid of the elses to fix the rest of the shit.
                {
                    if((i2 == i+1) && (j2 == j+1))
                    {
                        board[i][j] = '1';
                        board[i2][j2] = 'B';
                        validMove = 1;
                        //printf("I'm here it worked u saved me");
                    }
                }
                //these next two if statements are for the BLACK KING specificially (move back 1)
                if(isWithinBounds(i-1,j-1) && board[i-1][j-1]== '1')
                {
                    if((i2 == i-1) && (j2 == j-1))
                                {
                                    board[i][j] = '1';
                                    board[i2][j2] = 'B';
                                    validMove = 1; 
                                }
                }
                if(isWithinBounds(i-1,j+1) && board[i-1][j+1]== '1')
                {
                    if((i2 == i-1) && (j2 == j+1))
                                {
                                    board[i][j] = '1';
                                    board[i2][j2] = 'B';
                                    validMove = 1; 
                                }
                }
                //end of king backwards by 1 move statements
                if(isWithinBounds(i+1,j-1) && isWithinBounds(i+2,j-2) && (((board[i+1][j-1] == 'r') || (board[i+1][j-1] == 'R')) && (board[i+2][j-2] == '1')))
                {
                    if((i2 == i+2) && (j2 == j-2))
                    {
                        board[i][j] = '1';
                        board[i+1][j-1] = '1';
                        board[i+2][j-2] = 'B';
                        validMove = 1;
                        doubleJump = 1;
                    }
                }
                if(isWithinBounds(i+1,j+1) && isWithinBounds(i+1,j+2) && ((board[i+1][j+1] == 'r') || (board[i+1][j+1] == 'R')) && (board[i+2][j+2] == '1'))
                {
                if((i2 == i+2) && (j2 == j+2))
                    {
                        board[i][j] = '1';
                        board[i+1][j+1] = '1';
                        board[i+2][j+2] = 'B';
                        validMove = 1;
                        doubleJump = 1;
                    } 
                }
                //start of king backwards by 2 move statements
                if(isWithinBounds(i-1,j-1) && isWithinBounds(i-2,j-2) && (((board[i-1][j-1] == 'r') || (board[i-1][j-1] == 'R')) && (board[i-2][j-2] == '1')))
                            {
                                if((i2 == i-2) && (j2 == j-2))
                                {
                                    board[i][j] = '1';
                                    board[i-1][j-1] = '1';
                                    board[i-2][j-2] = 'B';
                                    validMove = 1;
                                    doubleJump = 1;
                                }
                            }
                if(isWithinBounds(i-1,j+1) && isWithinBounds(i-2,j+2) && ((board[i-1][j+1] == 'r') || (board[i-1][j+1] == 'R')) && (board[i-2][j+2] == '1'))
                            {
                            if((i2 == i-2) && (j2 == j+2))
                                {
                                    board[i][j] = '1';
                                    board[i-1][j+1] = '1';
                                    board[i-2][j+2] = 'B';
                                    validMove = 1;
                                    doubleJump = 1;
                                } 
                            }
                //end of king backwards by 2 move statements
                while (validMove == 0)
                {
                    printf("please input a valid move!\n");
                    printf("The value at %s is: %c\n", input2, board[i2][j2]);
                    getUserInput(input2);
                    i2= 7-(input2[1]-'1');
                    j2= convertLetter(input2[0]);
                    printf("The value at %s is: %c\n", input2, board[i2][j2]);
                    doubleJump = 0;
                    validMove = 0;
                    //take piece if statements
                    if(board[i][j] == 'B')
                    {
                        if(isWithinBounds(i+1,j-1) && board[i+1][j-1] == '1')
                        {
                            if((i2 == i+1) && (j2 == j-1))
                            {
                                board[i][j] = '1';
                                board[i2][j2] = 'B';
                                validMove = 1; 
                            }
                        }
                        if(isWithinBounds(i+1,j+1) && (board[i+1][j+1] == '1'))
                        {
                            if((i2 == i+1) && (j2 == j+1))
                            {
                                board[i][j] = '1';
                                board[i2][j2] = 'B';
                                validMove = 1;
                            }
                        }
                        //these next two if statements are for the BLACK KING specificially (move back 1)
                        if(isWithinBounds(i-1,j-1) && board[i-1][j-1]== '1')
                        {
                            if((i2 == i-1) && (j2 == j-1))
                                        {
                                            board[i][j] = '1';
                                            board[i2][j2] = 'B';
                                            validMove = 1; 
                                        }
                        }
                        if(isWithinBounds(i-1,j+1) && board[i-1][j+1]== '1')
                        {
                            if((i2 == i-1) && (j2 == j+1))
                                        {
                                            board[i][j] = '1';
                                            board[i2][j2] = 'B';
                                            validMove = 1; 
                                        }
                        }
                        //end of king backwards by 1 move statements
                        if(isWithinBounds(i+1,j-1) && isWithinBounds(i+2,j-2) && (((board[i+1][j-1] == 'r') || (board[i+1][j-1] == 'R')) && (board[i+2][j-2] == '1')))
                        {
                            if((i2 == i+2) && (j2 == j-2))
                            {
                                board[i][j] = '1';
                                board[i+1][j-1] = '1';
                                board[i+2][j-2] = 'B';
                                validMove = 1;
                                doubleJump = 1;
                            }
                        }
                        if(isWithinBounds(i+1,j+1) && isWithinBounds(i+2,j+2) && ((board[i+1][j+1] == 'r') || (board[i+1][j+1] == 'R')) && (board[i+2][j+2] == '1'))
                        {
                        if((i2 == i+2) && (j2 == j+2))
                            {
                                board[i][j] = '1';
                                board[i+1][j+1] = '1';
                                board[i+2][j+2] = 'B';
                                validMove = 1;
                                doubleJump = 1;
                            } 
                        }
                        //start of king backwards by 2 move statements
                        if(isWithinBounds(i-1,j-1) && isWithinBounds(i-2,j-2) && (((board[i-1][j-1] == 'r') || (board[i-1][j-1] == 'R')) && (board[i-2][j-2] == '1')))
                                    {
                                        if((i2 == i-2) && (j2 == j-2))
                                        {
                                            board[i][j] = '1';
                                            board[i-1][j-1] = '1';
                                            board[i-2][j-2] = 'B';
                                            validMove = 1;
                                            doubleJump = 1;
                                        }
                                    }
                        if(isWithinBounds(i-1,j+1) && isWithinBounds(i-2,j+2) && ((board[i-1][j+1] == 'r') || (board[i-1][j+1] == 'R')) && (board[i-2][j+2] == '1'))
                                    {
                                    if((i2 == i-2) && (j2 == j+2))
                                        {
                                            board[i][j] = '1';
                                            board[i-1][j+1] = '1';
                                            board[i-2][j+2] = 'B';
                                            validMove = 1;
                                            doubleJump = 1;
                                        } 
                                    }
                        //end of king backwards by 2 move statements
                    }
                }
                TheKinging();
                printBoard();
            }
                    //end of the validMove while statement
            
        

                    //next is the doubleJump
        
            while(doubleJump == 1)
            {
                    int validMoreJump = 0;
                    i = i2;
                    j = j2;
                    if(board[i][j] == 'b')
                        {
                            if(((isWithinBounds(i+1, j-1) && (isWithinBounds(i+2, j-2)))) && (((board[i+1][j-1] == 'r') || (board[i+1][j-1] == 'R')) && (board[i+2][j-2] == '1')))
                            {
                                validMoreJump = 1;
                            }
                            if((isWithinBounds(i+1, j+1) && (isWithinBounds(i+2, j+2))) && ((board[i+1][j+1] == 'r') || (board[i+1][j+1] == 'R')) && (board[i+2][j+2] == '1'))
                            {
                                validMoreJump = 1;
                            }
                        }
                    if(board[i][j] == 'B')
                    {
                    if(((isWithinBounds(i+1, j-1) && (isWithinBounds(i+2, j-2)))) && (((board[i+1][j-1] == 'r') || (board[i+1][j-1] == 'R')) && (board[i+2][j-2] == '1')))
                            {
                                validMoreJump = 1;
                            }
                        if((isWithinBounds(i+1, j+1) && (isWithinBounds(i+2, j+2))) && ((board[i+1][j+1] == 'r') || (board[i+1][j+1] == 'R')) && (board[i+2][j+2] == '1'))
                            {
                                validMoreJump = 1;
                            } 
                        if(isWithinBounds(i-1,j-1) && isWithinBounds(i-2,j-2) && (((board[i-1][j-1] == 'r') || (board[i-1][j-1] == 'R')) && (board[i-2][j-2] == '1')))
                        {
                            validMoreJump = 1;
                        }
                        if(isWithinBounds(i-1,j+1) && isWithinBounds(i-2,j+2) && ((board[i-1][j+1] == 'r') || (board[i-1][j+1] == 'R')) && (board[i-2][j+2] == '1'))
                        {
                            validMoreJump = 1;
                        }
                        
                    }
                    char YorN = 'n';
                    if(validMoreJump == 1)
                    {
                    YorN = getYesOrNo();
                    }
                    if(YorN == 'n')
                    {
                        doubleJump = 0;
                        break;
                    }
                    else if(YorN == 'y')
                {       
                    printf("The value at your spot is: %c\n", board[i][j]); // this is a check statement
                    
                    printf("Where would you like to move?\n");
                    //printf("It gets to right before input2\n");

                    getUserInput(input2);
                    i2= 7-(input2[1]-'1');
                    j2= convertLetter(input2[0]);
                    doubleJump = 0;
                    validMove = 0;
                    //take piece if statements
                    if(board[i][j] == 'b')
                    {
                        printf("The value at %s is: %c\n", input2, board[i2][j2]);
                        //printf("I2: %d\n", i2);
                        //printf("i+1: %d\n", i+1);
                        //printf("J2: %d\n", j2);
                        //printf("J+1: %d\n", j+1);
                        if(((isWithinBounds(i+1, j-1) && (isWithinBounds(i+2, j-2)))) && (((board[i+1][j-1] == 'r') || (board[i+1][j-1] == 'R')) && (board[i+2][j-2] == '1')))
                        {
                            if((i2 == i+2) && (j2 == j-2))
                            {
                                board[i][j] = '1';
                                board[i+1][j-1] = '1';
                                board[i+2][j-2] = 'b';
                                validMove = 1;
                                doubleJump = 1;
                            }
                        }
                        if((isWithinBounds(i+1, j+1) && (isWithinBounds(i+2, j+2))) && ((board[i+1][j+1] == 'r') || (board[i+1][j+1] == 'R')) && (board[i+2][j+2] == '1'))
                        {
                        if((i2 == i+2) && (j2 == j+2))
                            {
                                board[i][j] = '1';
                                board[i+1][j+1] = '1';
                                board[i+2][j+2] = 'b';
                                validMove = 1;
                                doubleJump = 1;
                            } 
                        }
                        while(validMove == 0)
                        {
                            printf("please input a valid move!\n");
                            //printf("The value at %s is: %c\n", input2, board[i2][j2]);
                            getUserInput(input2);
                            i2= 7-(input2[1]-'1');
                            j2= convertLetter(input2[0]);
                            printf("The value at %s is: %c\n", input2, board[i2][j2]);
                            doubleJump = 0;
                            validMove = 0;
                            //take piece if statements
                            if(board[i][j] == 'b')
                            {
                                if((isWithinBounds(i+1, j-1) && (isWithinBounds(i+2, j-2))) && (((board[i+1][j-1] == 'r') || (board[i+1][j-1] == 'R')) && (board[i+2][j-2] == '1')))
                                {
                                    if((i2 == i+2) && (j2 == j-2))
                                    {
                                        board[i][j] = '1';
                                        board[i+1][j-1] = '1';
                                        board[i+2][j-2] = 'b';
                                        validMove = 1;
                                        doubleJump = 1;
                                    }
                                }
                                if((isWithinBounds(i+1, j+1) && (isWithinBounds(i+2, j+2))) && ((board[i+1][j+1] == 'r') || (board[i+1][j+1] == 'R')) && (board[i+2][j+2] == '1'))
                                {
                                if((i2 == i+2) && (j2 == j+2))
                                    {
                                        board[i][j] = '1';
                                        board[i+1][j+1] = '1';
                                        board[i+2][j+2] = 'b';
                                        validMove = 1;
                                        doubleJump = 1;
                                    } 
                                }
                            }
                        }

                    }
                    if(board[i][j] == 'B')
                    {
                        
                    
                        printf("The value at %s is: %c\n", input2, board[i2][j2]);
                        //printf("I2: %d\n", i2);
                        //printf("i+1: %d\n", i+1);
                        //printf("J2: %d\n", j2);
                        //printf("J+1: %d\n", j+1);
                        if(isWithinBounds(i+1,j-1) && isWithinBounds(i+2,j-2) && (((board[i+1][j-1] == 'r') || (board[i+1][j-1] == 'R')) && (board[i+2][j-2] == '1')))
                        {
                            if((i2 == i+2) && (j2 == j-2))
                            {
                                board[i][j] = '1';
                                board[i+1][j-1] = '1';
                                board[i+2][j-2] = 'B';
                                validMove = 1;
                                doubleJump = 1;
                            }
                        }
                        if(isWithinBounds(i+1,j+1) && isWithinBounds(i+1,j+2) && ((board[i+1][j+1] == 'r') || (board[i+1][j+1] == 'R')) && (board[i+2][j+2] == '1'))
                        {
                        if((i2 == i+2) && (j2 == j+2))
                            {
                                board[i][j] = '1';
                                board[i+1][j+1] = '1';
                                board[i+2][j+2] = 'B';
                                validMove = 1;
                                doubleJump = 1;
                            } 
                        }
                        //start of king backwards by 2 move statements
                        if(isWithinBounds(i-1,j-1) && isWithinBounds(i-2,j-2) && (((board[i-1][j-1] == 'r') || (board[i-1][j-1] == 'R')) && (board[i-2][j-2] == '1')))
                                    {
                                        if((i2 == i-2) && (j2 == j-2))
                                        {
                                            board[i][j] = '1';
                                            board[i-1][j-1] = '1';
                                            board[i-2][j-2] = 'B';
                                            validMove = 1;
                                            doubleJump = 1;
                                        }
                                    }
                        if(isWithinBounds(i-1,j+1) && isWithinBounds(i-2,j+2) && ((board[i-1][j+1] == 'r') || (board[i-1][j+1] == 'R')) && (board[i-2][j+2] == '1'))
                                    {
                                    if((i2 == i-2) && (j2 == j+2))
                                        {
                                            board[i][j] = '1';
                                            board[i-1][j+1] = '1';
                                            board[i-2][j+2] = 'B';
                                            validMove = 1;
                                            doubleJump = 1;
                                        } 
                                    }
                        //end of king backwards by 2 move statements
                        while (validMove == 0)
                        {
                            printf("please input a valid move!\n");
                            printf("The value at %s is: %c\n", input2, board[i2][j2]);
                            getUserInput(input2);
                            i2= 7-(input2[1]-'1');
                            j2= convertLetter(input2[0]);
                            printf("The value at %s is: %c\n", input2, board[i2][j2]);
                            doubleJump = 0;
                            validMove = 0;
                            //take piece if statements
                            if(board[i][j] == 'B')
                            {
                                if(isWithinBounds(i+1,j-1) && isWithinBounds(i+2,j-2) && (((board[i+1][j-1] == 'r') || (board[i+1][j-1] == 'R')) && (board[i+2][j-2] == '1')))
                                {
                                    if((i2 == i+2) && (j2 == j-2))
                                    {
                                        board[i][j] = '1';
                                        board[i+1][j-1] = '1';
                                        board[i+2][j-2] = 'B';
                                        validMove = 1;
                                        doubleJump = 1;
                                    }
                                }
                                if(isWithinBounds(i+1,j+1) && isWithinBounds(i+2,j+2) && ((board[i+1][j+1] == 'r') || (board[i+1][j+1] == 'R')) && (board[i+2][j+2] == '1'))
                                {
                                if((i2 == i+2) && (j2 == j+2))
                                    {
                                        board[i][j] = '1';
                                        board[i+1][j+1] = '1';
                                        board[i+2][j+2] = 'B';
                                        validMove = 1;
                                        doubleJump = 1;
                                    } 
                                }
                                //start of king backwards by 2 move statements
                                if(isWithinBounds(i-1,j-1) && isWithinBounds(i-2,j-2) && (((board[i-1][j-1] == 'r') || (board[i-1][j-1] == 'R')) && (board[i-2][j-2] == '1')))
                                            {
                                                if((i2 == i-2) && (j2 == j-2))
                                                {
                                                    board[i][j] = '1';
                                                    board[i-1][j-1] = '1';
                                                    board[i-2][j-2] = 'B';
                                                    validMove = 1;
                                                    doubleJump = 1;
                                                }
                                            }
                                if(isWithinBounds(i-1,j+1) && isWithinBounds(i-2,j+2) && ((board[i-1][j+1] == 'r') || (board[i-1][j+1] == 'R')) && (board[i-2][j+2] == '1'))
                                            {
                                            if((i2 == i-2) && (j2 == j+2))
                                                {
                                                    board[i][j] = '1';
                                                    board[i-1][j+1] = '1';
                                                    board[i-2][j+2] = 'B';
                                                    validMove = 1;
                                                    doubleJump = 1;
                                                } 
                                            }
                                //end of king backwards by 2 move statements
                            }
                        }
                    }
                    TheKinging();
                    printBoard();
                }
            
            }
                
                
        }   
        
        
    playerTurn = 'r';

        
    }
    else
    {
        printf("It's Red's turn!\n");
        {
            done = surrender(gone);
             if(done == true) {
                printf("Red resigned.\n");
                gone = 0;
                return;
            }
            //char checkIn[2];
            printf("Please enter the piece you want to move.\n");
            //scanf("%2s", checkIn);
            char input[3]; //used for initial location
            char input2[3];
            //char input2[3]; //will be used for the end location later
            getUserInput(input);
            i= 7-(input[1]-'1');
            j = convertLetter(input[0]);
        //checks and makes user reinput
        while((playerTurn == 'r') && (!(board[i][j] == 'r' ||board[i][j] == 'R')|| !(pieceCanMove(i, j, playerTurn))))
        {
            if(!(board[i][j] == 'r' || board[i][j] == 'R'))
            {
                printf("This is not your piece!\n");
                printf("The value at this spot is: %c\n", board[i][j]);
                printf("Please enter the location of the piece you'd like to move.\n");
                getUserInput(input);
                i= 7-(input[1]-'1');
                j = convertLetter(input[0]);
            }
            if(!(pieceCanMove(i, j, playerTurn)))
            {
                printf("This piece you chose cannot move.\n");
                printf("The value at this spot is: %c\n", board[i][j]);
                printf("Please enter a different location of the piece you'd like to move.\n");
                getUserInput(input);
                i= 7-(input[1]-'1');
                j = convertLetter(input[0]);
            }
        }
        if((playerTurn == 'r') && (board[i][j] == 'r' || board[i][j] == 'R'))
        {
            printf("This is your piece!\n");
            printf("The value at this spot is: %c\n", board[i][j]); // this is a check statement
            
            printf("Where would you like to move?\n");
            //printf("It gets to right before input2\n");

            getUserInput(input2);
            int i2= 7-(input2[1]-'1');
            int j2= convertLetter(input2[0]);
            int doubleJump = 0;
            int validMove = 0;
            //take piece if statements
            if(board[i][j] == 'r')
            {
                printf("The value at %s is: %c\n", input2, board[i2][j2]);
                //printf("I2: %d\n", i2);
                //printf("i+1: %d\n", i+1);
                //printf("J2: %d\n", j2);
                //printf("J+1: %d\n", j+1);
                if(board[i2][j2] == '1')
                {
                    if((i2 == i-1) && (j2 == j-1))
                    {
                        board[i][j] = '1';
                        board[i2][j2] = 'r';
                        validMove = 1; 
                        //printf("I'm here it worked u saved me");
                    }
                    else
                    {
                        //this is empty !!!
                    }
                }
                if((isWithinBounds(i-1, j+1)) && (board[i-1][j+1] == '1'))    // make sure to get rid of the elses to fix the rest of the shit.
                {
                    if((i2 == i-1) && (j2 == j+1))
                    {
                        board[i][j] = '1';
                        board[i2][j2] = 'r';
                        validMove = 1;
                        //printf("I'm here it worked u saved me");
                    }
                }
                if(((isWithinBounds(i-1, j-1) && (isWithinBounds(i-2, j-2)))) && (((board[i-1][j-1] == 'b') || (board[i-1][j-1] == 'B')) && (board[i-2][j-2] == '1')))
                {
                    if((i2 == i-2) && (j2 == j-2))
                    {
                        board[i][j] = '1';
                        board[i-1][j-1] = '1';
                        board[i-2][j-2] = 'r';
                        validMove = 1;
                        doubleJump = 1;
                    }
                }
                if((isWithinBounds(i-1, j+1) && (isWithinBounds(i-2, j+2))) && ((board[i-1][j+1] == 'b') || (board[i-1][j+1] == 'B')) && (board[i-2][j+2] == '1'))
                {
                if((i2 == i-2) && (j2 == j+2))
                    {
                        board[i][j] = '1';
                        board[i-1][j+1] = '1';
                        board[i-2][j+2] = 'r';
                        validMove = 1;
                        doubleJump = 1;
                    } 
                }
                while (validMove == 0)
                {
                    printf("please input a valid move!\n");
                    printf("The value at %s is: %c\n", input2, board[i2][j2]);
                    getUserInput(input2);
                    i2= 7-(input2[1]-'1');
                    j2= convertLetter(input2[0]);
                    printf("The value at %s is: %c\n", input2, board[i2][j2]);
                    doubleJump = 0;
                    validMove = 0;
                    //take piece if statements
                    if(board[i][j] == 'r')
                    {
                        if((isWithinBounds(i-1, j-1)) && board[i-1][j-1] == '1')
                        {
                            if((i2 == i-1) && (j2 == j-1))
                            {
                                board[i][j] = '1';
                                board[i2][j2] = 'r';
                                validMove = 1; 
                            }
                        }
                        if((isWithinBounds(i-1, j+1)) && (board[i-1][j+1] == '1'))
                        {
                            if((i2 == i-1) && (j2 == j+1))
                            {
                                board[i][j] = '1';
                                board[i2][j2] = 'r';
                                validMove = 1;
                            }
                        }
                        if((isWithinBounds(i-1, j-1) && (isWithinBounds(i-2, j-2))) && (((board[i-1][j-1] == 'b') || (board[i-1][j-1] == 'B')) && (board[i-2][j-2] == '1')))
                        {
                            if((i2 == i-2) && (j2 == j-2))
                            {
                                board[i][j] = '1';
                                board[i-1][j-1] = '1';
                                board[i-2][j-2] = 'r';
                                validMove = 1;
                                doubleJump = 1;
                            }
                        }
                        if((isWithinBounds(i-1, j+1) && (isWithinBounds(i-2, j+2))) && ((board[i-1][j+1] == 'b') || (board[i-1][j+1] == 'B')) && (board[i-2][j+2] == '1'))
                        {
                        if((i2 == i-2) && (j2 == j+2))
                            {
                                board[i][j] = '1';
                                board[i-1][j+1] = '1';
                                board[i-2][j+2] = 'r';
                                validMove = 1;
                                doubleJump = 1;
                            } 
                        }
                    }
                }
            TheKinging();
            printBoard();
            }
            //printBoard after validMOVE




                //IMPORTANT DISTINCTION 
                //ABOVE WAS THE UNKINGED black,  BELOW IS KINGED BLACK

            if(board[i][j] == 'R') // the first step is to replace 'r' with 'R'
            {  
            
                printf("The value at %s is: %c\n", input2, board[i2][j2]);
                //printf("I2: %d\n", i2);
                //printf("i+1: %d\n", i+1);
                //printf("J2: %d\n", j2);
                //printf("J+1: %d\n", j+1);
                if(board[i2][j2] == '1')
                {
                    if((i2 == i+1) && (j2 == j-1))
                    {
                        board[i][j] = '1';
                        board[i2][j2] = 'R';
                        validMove = 1; 
                        //printf("I'm here it worked u saved me");
                    }
                    else
                    {
                        //this is empty !!!
                    }
                }
                if(isWithinBounds(i+1,j+1) && (board[i+1][j+1] == '1'))    // make sure to get rid of the elses to fix the rest of the shit.
                {
                    if((i2 == i+1) && (j2 == j+1))
                    {
                        board[i][j] = '1';
                        board[i2][j2] = 'R';
                        validMove = 1;
                        //printf("I'm here it worked u saved me");
                    }
                }
                //these next two if statements are for the BLACK KING specificially (move back 1)
                if(isWithinBounds(i-1,j-1) && board[i-1][j-1]== '1')
                {
                    if((i2 == i-1) && (j2 == j-1))
                                {
                                    board[i][j] = '1';
                                    board[i2][j2] = 'R';
                                    validMove = 1; 
                                }
                }
                if(isWithinBounds(i-1,j+1) && board[i-1][j+1]== '1')
                {
                    if((i2 == i-1) && (j2 == j+1))
                                {
                                    board[i][j] = '1';
                                    board[i2][j2] = 'R';
                                    validMove = 1; 
                                }
                }
                //end of king backwards by 1 move statements
                if(isWithinBounds(i+1,j-1) && isWithinBounds(i+2,j-2) && (((board[i+1][j-1] == 'b') || (board[i+1][j-1] == 'B')) && (board[i+2][j-2] == '1')))
                {
                    if((i2 == i+2) && (j2 == j-2))
                    {
                        board[i][j] = '1';
                        board[i+1][j-1] = '1';
                        board[i+2][j-2] = 'R';
                        validMove = 1;
                        doubleJump = 1;
                    }
                }
                if(isWithinBounds(i+1,j+1) && isWithinBounds(i+1,j+2) && ((board[i+1][j+1] == 'b') || (board[i+1][j+1] == 'B')) && (board[i+2][j+2] == '1'))
                {
                if((i2 == i+2) && (j2 == j+2))
                    {
                        board[i][j] = '1';
                        board[i+1][j+1] = '1';
                        board[i+2][j+2] = 'R';
                        validMove = 1;
                        doubleJump = 1;
                    } 
                }
                //start of king backwards by 2 move statements
                if(isWithinBounds(i-1,j-1) && isWithinBounds(i-2,j-2) && (((board[i-1][j-1] == 'b') || (board[i-1][j-1] == 'B')) && (board[i-2][j-2] == '1')))
                            {
                                if((i2 == i-2) && (j2 == j-2))
                                {
                                    board[i][j] = '1';
                                    board[i-1][j-1] = '1';
                                    board[i-2][j-2] = 'R';
                                    validMove = 1;
                                    doubleJump = 1;
                                }
                            }
                if(isWithinBounds(i-1,j+1) && isWithinBounds(i-2,j+2) && ((board[i-1][j+1] == 'b') || (board[i-1][j+1] == 'B')) && (board[i-2][j+2] == '1'))
                            {
                            if((i2 == i-2) && (j2 == j+2))
                                {
                                    board[i][j] = '1';
                                    board[i-1][j+1] = '1';
                                    board[i-2][j+2] = 'R';
                                    validMove = 1;
                                    doubleJump = 1;
                                } 
                            }
                //end of king backwards by 2 move statements
                while (validMove == 0)
                {
                    printf("please input a valid move!\n");
                    printf("The value at %s is: %c\n", input2, board[i2][j2]);
                    getUserInput(input2);
                    i2= 7-(input2[1]-'1');
                    j2= convertLetter(input2[0]);
                    printf("The value at %s is: %c\n", input2, board[i2][j2]);
                    doubleJump = 0;
                    validMove = 0;
                    //take piece if statements
                    if(board[i][j] == 'R')
                    {
                        if(isWithinBounds(i+1,j-1) && board[i+1][j-1] == '1')
                        {
                            if((i2 == i+1) && (j2 == j-1))
                            {
                                board[i][j] = '1';
                                board[i2][j2] = 'R';
                                validMove = 1; 
                            }
                        }
                        if(isWithinBounds(i+1,j+1) && (board[i+1][j+1] == '1'))
                        {
                            if((i2 == i+1) && (j2 == j+1))
                            {
                                board[i][j] = '1';
                                board[i2][j2] = 'R';
                                validMove = 1;
                            }
                        }
                        //these next two if statements are for the BLACK KING specificially (move back 1)
                        if(isWithinBounds(i-1,j-1) && board[i-1][j-1]== '1')
                        {
                            if((i2 == i-1) && (j2 == j-1))
                                        {
                                            board[i][j] = '1';
                                            board[i2][j2] = 'R';
                                            validMove = 1; 
                                        }
                        }
                        if(isWithinBounds(i-1,j+1) && board[i-1][j+1]== '1')
                        {
                            if((i2 == i-1) && (j2 == j+1))
                                        {
                                            board[i][j] = '1';
                                            board[i2][j2] = 'R';
                                            validMove = 1; 
                                        }
                        }
                        //end of king backwards by 1 move statements
                        if(isWithinBounds(i+1,j-1) && isWithinBounds(i+2,j-2) && (((board[i+1][j-1] == 'b') || (board[i+1][j-1] == 'B')) && (board[i+2][j-2] == '1')))
                        {
                            if((i2 == i+2) && (j2 == j-2))
                            {
                                board[i][j] = '1';
                                board[i+1][j-1] = '1';
                                board[i+2][j-2] = 'R';
                                validMove = 1;
                                doubleJump = 1;
                            }
                        }
                        if(isWithinBounds(i+1,j+1) && isWithinBounds(i+2,j+2) && ((board[i+1][j+1] == 'b') || (board[i+1][j+1] == 'B')) && (board[i+2][j+2] == '1'))
                        {
                        if((i2 == i+2) && (j2 == j+2))
                            {
                                board[i][j] = '1';
                                board[i+1][j+1] = '1';
                                board[i+2][j+2] = 'R';
                                validMove = 1;
                                doubleJump = 1;
                            } 
                        }
                        //start of king backwards by 2 move statements
                        if(isWithinBounds(i-1,j-1) && isWithinBounds(i-2,j-2) && (((board[i-1][j-1] == 'b') || (board[i-1][j-1] == 'B')) && (board[i-2][j-2] == '1')))
                                    {
                                        if((i2 == i-2) && (j2 == j-2))
                                        {
                                            board[i][j] = '1';
                                            board[i-1][j-1] = '1';
                                            board[i-2][j-2] = 'R';
                                            validMove = 1;
                                            doubleJump = 1;
                                        }
                                    }
                        if(isWithinBounds(i-1,j+1) && isWithinBounds(i-2,j+2) && ((board[i-1][j+1] == 'b') || (board[i-1][j+1] == 'B')) && (board[i-2][j+2] == '1'))
                                    {
                                    if((i2 == i-2) && (j2 == j+2))
                                        {
                                            board[i][j] = '1';
                                            board[i-1][j+1] = '1';
                                            board[i-2][j+2] = 'R';
                                            validMove = 1;
                                            doubleJump = 1;
                                        } 
                                    }
                        //end of king backwards by 2 move statements
                    }
                }
                TheKinging();
                printBoard();
            }
                    //end of the validMove while statement
            
        

                    //next is the doubleJump
        
            while(doubleJump == 1)
            {
                    int validMoreJump = 0;
                    i = i2;
                    j = j2;
                    if(board[i][j] == 'r')
                        {
                            if(((isWithinBounds(i-1, j-1) && (isWithinBounds(i-2, j-2)))) && (((board[i-1][j-1] == 'b') || (board[i-1][j-1] == 'B')) && (board[i-2][j-2] == '1')))
                            {
                                validMoreJump = 1;
                            }
                            if((isWithinBounds(i-1, j+1) && (isWithinBounds(i-2, j+2))) && ((board[i-1][j+1] == 'b') || (board[i-1][j+1] == 'B')) && (board[i-2][j+2] == '1'))
                            {
                                validMoreJump = 1;
                            }
                        }
                    if(board[i][j] == 'R')
                    {
                    if(((isWithinBounds(i+1, j-1) && (isWithinBounds(i+2, j-2)))) && (((board[i+1][j-1] == 'b') || (board[i+1][j-1] == 'B')) && (board[i+2][j-2] == '1')))
                            {
                                validMoreJump = 1;
                            }
                        if((isWithinBounds(i+1, j+1) && (isWithinBounds(i+2, j+2))) && ((board[i+1][j+1] == 'b') || (board[i+1][j+1] == 'B')) && (board[i+2][j+2] == '1'))
                            {
                                validMoreJump = 1;
                            } 
                        if(isWithinBounds(i-1,j-1) && isWithinBounds(i-2,j-2) && (((board[i-1][j-1] == 'b') || (board[i-1][j-1] == 'B')) && (board[i-2][j-2] == '1')))
                        {
                            validMoreJump = 1;
                        }
                        if(isWithinBounds(i-1,j+1) && isWithinBounds(i-2,j+2) && ((board[i-1][j+1] == 'b') || (board[i-1][j+1] == 'B')) && (board[i-2][j+2] == '1'))
                        {
                            validMoreJump = 1;
                        }
                        
                    }
                    char YorN = 'n';
                    if(validMoreJump == 1)
                    {
                    YorN = getYesOrNo();
                    }
                    if(YorN == 'n')
                    {
                        doubleJump = 0;
                        break;
                    }
                    else if(YorN == 'y')
                {       
                    printf("The value at your spot is: %c\n", board[i][j]); // this is a check statement
                    
                    printf("Where would you like to move?\n");
                    //printf("It gets to right before input2\n");

                    getUserInput(input2);
                    i2= 7-(input2[1]-'1');
                    j2= convertLetter(input2[0]);
                    doubleJump = 0;
                    validMove = 0;
                    //take piece if statements
                    if(board[i][j] == 'r')
                    {
                        printf("The value at %s is: %c\n", input2, board[i2][j2]);
                        //printf("I2: %d\n", i2);
                        //printf("i+1: %d\n", i+1);
                        //printf("J2: %d\n", j2);
                        //printf("J+1: %d\n", j+1);
                        if(((isWithinBounds(i-1, j-1) && (isWithinBounds(i-2, j-2)))) && (((board[i-1][j-1] == 'b') || (board[i-1][j-1] == 'B')) && (board[i-2][j-2] == '1')))
                        {
                            if((i2 == i-2) && (j2 == j-2))
                            {
                                board[i][j] = '1';
                                board[i-1][j-1] = '1';
                                board[i-2][j-2] = 'r';
                                validMove = 1;
                                doubleJump = 1;
                            }
                        }
                        if((isWithinBounds(i-1, j+1) && (isWithinBounds(i-2, j+2))) && ((board[i-1][j+1] == 'b') || (board[i-1][j+1] == 'B')) && (board[i-2][j+2] == '1'))
                        {
                        if((i2 == i-2) && (j2 == j+2))
                            {
                                board[i][j] = '1';
                                board[i-1][j+1] = '1';
                                board[i-2][j+2] = 'r';
                                validMove = 1;
                                doubleJump = 1;
                            } 
                        }
                        while(validMove == 0)
                        {
                            printf("please input a valid move!\n");
                            //printf("The value at %s is: %c\n", input2, board[i2][j2]);
                            getUserInput(input2);
                            i2= 7-(input2[1]-'1');
                            j2= convertLetter(input2[0]);
                            printf("The value at %s is: %c\n", input2, board[i2][j2]);
                            doubleJump = 0;
                            validMove = 0;
                            //take piece if statements
                            if(board[i][j] == 'r')
                            {
                                if((isWithinBounds(i-1, j-1) && (isWithinBounds(i-2, j-2))) && (((board[i-1][j-1] == 'b') || (board[i-1][j-1] == 'B')) && (board[i-2][j-2] == '1')))
                                {
                                    if((i2 == i-2) && (j2 == j-2))
                                    {
                                        board[i][j] = '1';
                                        board[i-1][j-1] = '1';
                                        board[i-2][j-2] = 'r';
                                        validMove = 1;
                                        doubleJump = 1;
                                    }
                                }
                                if((isWithinBounds(i-1, j+1) && (isWithinBounds(i-2, j+2))) && ((board[i-1][j+1] == 'b') || (board[i-1][j+1] == 'B')) && (board[i-2][j+2] == '1'))
                                {
                                if((i2 == i-2) && (j2 == j+2))
                                    {
                                        board[i][j] = '1';
                                        board[i-1][j+1] = '1';
                                        board[i-2][j+2] = 'r';
                                        validMove = 1;
                                        doubleJump = 1;
                                    } 
                                }
                            }
                        }

                    }
                    if(board[i][j] == 'R')
                    {
                        
                    
                        printf("The value at %s is: %c\n", input2, board[i2][j2]);
                        //printf("I2: %d\n", i2);
                        //printf("i+1: %d\n", i+1);
                        //printf("J2: %d\n", j2);
                        //printf("J+1: %d\n", j+1);
                        if(isWithinBounds(i+1,j-1) && isWithinBounds(i+2,j-2) && (((board[i+1][j-1] == 'b') || (board[i+1][j-1] == 'B')) && (board[i+2][j-2] == '1')))
                        {
                            if((i2 == i+2) && (j2 == j-2))
                            {
                                board[i][j] = '1';
                                board[i+1][j-1] = '1';
                                board[i+2][j-2] = 'R';
                                validMove = 1;
                                doubleJump = 1;
                            }
                        }
                        if(isWithinBounds(i+1,j+1) && isWithinBounds(i+1,j+2) && ((board[i+1][j+1] == 'b') || (board[i+1][j+1] == 'B')) && (board[i+2][j+2] == '1'))
                        {
                        if((i2 == i+2) && (j2 == j+2))
                            {
                                board[i][j] = '1';
                                board[i+1][j+1] = '1';
                                board[i+2][j+2] = 'R';
                                validMove = 1;
                                doubleJump = 1;
                            } 
                        }
                        //start of king backwards by 2 move statements
                        if(isWithinBounds(i-1,j-1) && isWithinBounds(i-2,j-2) && (((board[i-1][j-1] == 'b') || (board[i-1][j-1] == 'B')) && (board[i-2][j-2] == '1')))
                                    {
                                        if((i2 == i-2) && (j2 == j-2))
                                        {
                                            board[i][j] = '1';
                                            board[i-1][j-1] = '1';
                                            board[i-2][j-2] = 'R';
                                            validMove = 1;
                                            doubleJump = 1;
                                        }
                                    }
                        if(isWithinBounds(i-1,j+1) && isWithinBounds(i-2,j+2) && ((board[i-1][j+1] == 'b') || (board[i-1][j+1] == 'B')) && (board[i-2][j+2] == '1'))
                                    {
                                    if((i2 == i-2) && (j2 == j+2))
                                        {
                                            board[i][j] = '1';
                                            board[i-1][j+1] = '1';
                                            board[i-2][j+2] = 'R';
                                            validMove = 1;
                                            doubleJump = 1;
                                        } 
                                    }
                        //end of king backwards by 2 move statements
                        while (validMove == 0)
                        {
                            printf("please input a valid move!\n");
                            printf("The value at %s is: %c\n", input2, board[i2][j2]);
                            getUserInput(input2);
                            i2= 7-(input2[1]-'1');
                            j2= convertLetter(input2[0]);
                            printf("The value at %s is: %c\n", input2, board[i2][j2]);
                            doubleJump = 0;
                            validMove = 0;
                            //take piece if statements
                            if(board[i][j] == 'R')
                            {
                                if(isWithinBounds(i+1,j-1) && isWithinBounds(i+2,j-2) && (((board[i+1][j-1] == 'b') || (board[i+1][j-1] == 'B')) && (board[i+2][j-2] == '1')))
                                {
                                    if((i2 == i+2) && (j2 == j-2))
                                    {
                                        board[i][j] = '1';
                                        board[i+1][j-1] = '1';
                                        board[i+2][j-2] = 'R';
                                        validMove = 1;
                                        doubleJump = 1;
                                    }
                                }
                                if(isWithinBounds(i+1,j+1) && isWithinBounds(i+2,j+2) && ((board[i+1][j+1] == 'b') || (board[i+1][j+1] == 'B')) && (board[i+2][j+2] == '1'))
                                {
                                if((i2 == i+2) && (j2 == j+2))
                                    {
                                        board[i][j] = '1';
                                        board[i+1][j+1] = '1';
                                        board[i+2][j+2] = 'R';
                                        validMove = 1;
                                        doubleJump = 1;
                                    } 
                                }
                                //start of king backwards by 2 move statements
                                if(isWithinBounds(i-1,j-1) && isWithinBounds(i-2,j-2) && (((board[i-1][j-1] == 'b') || (board[i-1][j-1] == 'B')) && (board[i-2][j-2] == '1')))
                                            {
                                                if((i2 == i-2) && (j2 == j-2))
                                                {
                                                    board[i][j] = '1';
                                                    board[i-1][j-1] = '1';
                                                    board[i-2][j-2] = 'R';
                                                    validMove = 1;
                                                    doubleJump = 1;
                                                }
                                            }
                                if(isWithinBounds(i-1,j+1) && isWithinBounds(i-2,j+2) && ((board[i-1][j+1] == 'b') || (board[i-1][j+1] == 'B')) && (board[i-2][j+2] == '1'))
                                            {
                                            if((i2 == i-2) && (j2 == j+2))
                                                {
                                                    board[i][j] = '1';
                                                    board[i-1][j+1] = '1';
                                                    board[i-2][j+2] = 'R';
                                                    validMove = 1;
                                                    doubleJump = 1;
                                                } 
                                            }
                                //end of king backwards by 2 move statements
                            }
                        }
                    }
                    TheKinging(); 
                    printBoard();
                }
            
            }
                
                
        }   
        
        
    playerTurn = 'b';

        
    }
    }
    
}









void getUserInput(char input[])
    {
    //printf("GettingUserInput(IS INSIDE OF GETUSERINPUT FUNCTION)\n");
    printf("Please enter the location in the form LetterNumber (EX: a5): ");
    scanf("%2s", input);
    printf("\nYou inputed: %s\n",input);
    while(!((input[0] >= 'a' && input[0] <= 'h') || (input[0] >= 'A' && input[0] <= 'H')) || !(input[1] >= '1' && input[1] <= '8'))
    {
        printf("Error please correct your input: ");
        scanf("%2s", input);
        printf("\nYou inputed: %s\n",input);
    }
    }
int convertLetter(char a) //converts the letter from location to its corresponding int value
{
   int j;
        if(a == 'a' ||a == 'A')
        {
            j=0;
        }
        else if(a == 'b' || a =='B')
        {
            j=1;
        }
        else if(a == 'c' ||a =='C')
        {
            j=2;
        }
        else if(a == 'd' ||a =='D')
        {
            j=3;
        }
        else if(a == 'e' ||a =='E')
        {
            j=4;
        }
        else if(a == 'f' ||a =='F')
        {
            j=5;
        }
        else if(a == 'g' ||a =='G')
        {
            j=6;
        }
        else if(a == 'h' ||a =='H')
        {
            j=7;
        } 
        return j;
}
bool pieceCanMove(int i, int j, char playerT)
{
    if(playerT == 'b')
    {
    if(board[i][j] == 'b'){
        if((isWithinBounds(i+1, j-1) && (board[i+1][j-1] == '1')) || (isWithinBounds(i+1, j+1) && (board[i+1][j+1] == '1')) || 
        ((isWithinBounds(i+1, j-1) && isWithinBounds(i+2, j-2)) &&((board[i+1][j-1] == 'r') || (board[i+1][j-1] == 'R')) && (board[i+2][j-2] == '1')) || 
        ((isWithinBounds(i+1, j+1) && isWithinBounds(i+2, j+2)) && (board[i+1][j+1] == 'r') || (board[i+1][j+1] == 'R')) && (board[i+2][j+2] == '1'))
        {
            //printf("Has open spot to move!\n");
            return true;
        }
    }
    if(board[i][j] == 'B')
    {
        if(
        (isWithinBounds(i+1, j-1) && (board[i+1][j-1] == '1')) || (isWithinBounds(i+1, j+1) && (board[i+1][j+1] == '1')) || 
        (isWithinBounds(i-1, j-1) && board[i-1][j-1] == '1') || (isWithinBounds(i-1, j+1) && (board[i-1][j+1] == '1')) || //adds king backwards check
        ((isWithinBounds(i+1, j-1) && isWithinBounds(i+2, j-2)) && ((board[i+1][j-1] == 'r') || (board[i+1][j-1] == 'R')) && (board[i+2][j-2] == '1')) || 
        ((isWithinBounds(i+1, j+1) && isWithinBounds(i+2, j+2)) && (board[i+1][j+1] == 'r') || (board[i+1][j+1] == 'R')) && (board[i+2][j+2] == '1') ||
        ((isWithinBounds(i-1, j-1) && isWithinBounds(i-2, j-2)) && (board[i-1][j-1] == 'r') || (board[i-1][j-1] == 'R')) && (board[i-2][j-2] == '1') || //adds king backwards jump check
        ((isWithinBounds(i-1, j+1) && isWithinBounds(i-2, j+2)) && (board[i-1][j+1] == 'r') || (board[i-1][j+1] == 'R')) && (board[i-2][j+2] == '1') ) //^
        {
            //printf("Has open spot to move!\n");
            return true;
        }
        
    }
        //printf("Does not have open spot (B).\n");
    }
    if(playerT == 'r')
    {
    if(board[i][j] == 'r'){
        if((isWithinBounds(i-1, j-1) && (board[i-1][j-1] == '1')) || (isWithinBounds(i-1, j+1) && (board[i-1][j+1] == '1')) || 
        ((isWithinBounds(i-1, j-1) && isWithinBounds(i-2, j-2)) &&((board[i-1][j-1] == 'b') || (board[i-1][j-1] == 'B')) && (board[i-2][j-2] == '1')) || 
        ((isWithinBounds(i-1, j+1) && isWithinBounds(i-2, j+2)) && (board[i-1][j+1] == 'b') || (board[i-1][j+1] == 'B')) && (board[i-2][j+2] == '1'))
        {
            //printf("Has open spot to move!\n");
            return true;
        }
    }
    if(board[i][j] == 'R')
    {
        if(
        (isWithinBounds(i+1, j-1) && (board[i+1][j-1] == '1')) || (isWithinBounds(i+1, j+1) && (board[i+1][j+1] == '1')) || 
        (isWithinBounds(i-1, j-1) && board[i-1][j-1] == '1') || (isWithinBounds(i-1, j+1) && (board[i-1][j+1] == '1')) || //adds king backwards check
        ((isWithinBounds(i+1, j-1) && isWithinBounds(i+2, j-2)) && ((board[i+1][j-1] == 'b') || (board[i+1][j-1] == 'B')) && (board[i+2][j-2] == '1')) || 
        ((isWithinBounds(i+1, j+1) && isWithinBounds(i+2, j+2)) && (board[i+1][j+1] == 'b') || (board[i+1][j+1] == 'B')) && (board[i+2][j+2] == '1') ||
        ((isWithinBounds(i-1, j-1) && isWithinBounds(i-2, j-2)) && (board[i-1][j-1] == 'b') || (board[i-1][j-1] == 'B')) && (board[i-2][j-2] == '1') || //adds king backwards jump check
        ((isWithinBounds(i-1, j+1) && isWithinBounds(i-2, j+2)) && (board[i-1][j+1] == 'b') || (board[i-1][j+1] == 'B')) && (board[i-2][j+2] == '1') ) //^
        {
            //printf("Has open spot to move!\n");
            return true;
        }
        
    }
        //printf("Does not have open spot(R).\n");
    }
    return false;
}  


// Function to get a valid 'y' or 'n' character from the user
char getYesOrNo() {
    char userInput;
    while (1) 
    {
        printf("Would you like to double jump?:\n ");
        printf("Please enter 'y' or 'n': ");
        scanf(" %c", &userInput); // The space before %c ignores any leading whitespace
        // Convert to lowercase to handle 'Y' or 'N'
        userInput = tolower(userInput);
        if (userInput == 'y' || userInput == 'n') 
        {
            return userInput; // Valid input
        } 
        else 
        {
            printf("Invalid input. ");
        }
    }
}

bool isWithinBounds(int row, int col) 
{
    return (row >= 0) && (row < 8) && (col >= 0) && (col < 8);
}

bool HasAnyLegalMoves(char playerT)
{   bool yesOrNo = false;

        for(int i =0;i<8;i++)
        {
            for(int j = 0; j<8; j++)
            {
                if(pieceCanMove(i,j,playerT))
                {
                    yesOrNo = true;
                }
            }
        }
    return yesOrNo;  
}
void TheKinging()
{
    for(int i = 0;i<8;i++)
    {
        if(board[0][i] == 'r')
        {
            board[0][i] = 'R';
        }
        if(board[7][i] == 'b')
        {
            board[7][i] = 'B';
        }
    }
}

bool surrender(int turn) {
    char yn;
    if(!(turn >=5)) {
        return false;
    } else {
       printf("Would you like to surrender?(y or n): ");
       scanf(" %c", &yn);
       if(yn != 'y' && yn != 'n') {
        printf("Try again");
        return surrender(turn);
       } else if(yn == 'y') {

            return true;
       }else {
            return false;
       }
    }
}

char playAgain(int turn) {
    char yesNo;
    if(turn == -1) {
        printf("Would you like to play checkers?: ");
        printf("Please enter 'y' or 'n': ");
        scanf(" %c", &yesNo);
    } else {
        printf("Would you like to play again?: ");
        printf("Please enter 'y' or 'n': ");
        scanf(" %c", &yesNo);
    }
    return yesNo;
}