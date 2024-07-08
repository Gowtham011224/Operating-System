#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define N 8 //board size

const char *fifo_path = "/tmp/queen_fifo";

// Function to check if the input board is a valid solution for N Queens
int isSafe(int board[N][N]) {
    int i, j;

    for (i = 0; i < N; i++) {
        int queenCount = 0;
        for (j = 0; j < N; j++) {
            if (board[i][j] == 1) {
                queenCount++;
            }
        }
        if (queenCount != 1) {
            return 0;
        }
    }

    for (j = 0; j < N; j++) {
        int queenCount = 0;
        for (i = 0; i < N; i++) {
            if (board[i][j] == 1) {
                queenCount++;
            }
        }
        if (queenCount != 1) {
            return 0;
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (board[i][j] == 1) {
                for (int k = i - 1, l = j - 1; k >= 0 && l >= 0; k--, l--) {
                    if (board[k][l] == 1) {
                        return 0;
                    }
                }
                for (int k = i + 1, l = j - 1; k < N && l >= 0; k++, l--) {
                    if (board[k][l] == 1) {
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}


// Function to solve the N Queens problem recursively
void solveNQueens(int board[N][N]) 
{	
	int correctness_flag = isSafe(board);
	printf("Program1:\n\tGiven board:\n\t");
	for (int i = 0; i < N; ++i)
                {
                        for (int j = 0; j < N; ++j)
                                printf("%d ", board[i][j]);
                        printf("\n\t");
                }
        printf("\t");
	printf("Validation:%d\n\n",correctness_flag);
     	int fd=open(fifo_path,O_WRONLY);
	write(fd, &correctness_flag, sizeof(int)); // Send the correctness flag
       	return;
	close(fd);
}

int main() 
{
	printf("Program2: Waiting for program1 to send queen's configuration...\n");
    	mkfifo(fifo_path, 0666);
	int fd = open(fifo_path, O_RDONLY);
    	if (fd == -1) 
    	{
        	perror("Error opening FIFO for writing");
        	exit(EXIT_FAILURE);
    	}
	
    	// Initialize an empty N x N chessboard
	int board[N][N];
	

	read(fd, board, sizeof(board));
	printf("Program1: Sent the input configuration.\n");
	
	close(fd);

	// Start solving the N Queens problem and send solutions through the pipe
    	solveNQueens(board); 
	printf("Program2: Finished validating the given queen's configuration.\nExiting...\n");

    	//Delete the FIFO
    	unlink(fifo_path);
	return 0;
}
