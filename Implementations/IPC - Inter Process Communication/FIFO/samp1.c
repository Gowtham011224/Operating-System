#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define N 8 //board size

const char *fifo_path = "/tmp/queen_fifo";


// Function to write input configurations to FIFO
void writeInputConfiguration(int board[N][N])
{
	int fd = open(fifo_path, O_WRONLY);

        if (fd == -1)//unable to open FIFO
        {
                perror("Error opening FIFO for reading");
                exit(EXIT_FAILURE);
        }

	write(fd, board, N* N * sizeof(int));
	close(fd);
	return;
}

// Function to read queen configurations from FIFO
void readQueenConfiguration(int board[N][N]) 
{
	int fd = open(fifo_path, O_RDONLY);
    	
	if (fd == -1)//unable to open FIFO 
    	{
        	perror("Error opening FIFO for reading");
        	exit(EXIT_FAILURE);
    	}

       	int is_correct;
    	ssize_t bytes_read;

    	while ((bytes_read = read(fd, &is_correct, sizeof(int))) > 0) 
    	{
        	if (is_correct) 
		{
			printf("Program2: Correct Queen Configuration\n");
		}
		else
		{
			printf("Program2: Wrong Queen Configuration\n");
		}
            	for (int i = 0; i < N; ++i) 
	    	{
                	for (int j = 0; j < N; ++j) 
	                    	printf("%d ", board[i][j]);
                	printf("\n");
            	}
		printf("\n");
	}
    	close(fd);
}

int main() 
{
	printf("Program1 :\nEnter the position of queens in %d*%d board to validate it.\n",N,N);
	printf("Sample Input for 4*4 board : 1 3 2 4\nUser Input: ");
	
	int board[N][N]={{0}};
        int i,j;
	for(i=0; i<N ; i++)
	{	
		scanf("%d",&j);
		board[j-1][i]=1;
        }
	

	printf("Program1: Sending the given queen configuration to Program2...\n");
    	mkfifo(fifo_path, 0666);

	//code for wrting input to fifo	
	writeInputConfiguration(board);

	// result of given queen configurations from FIFO
    	readQueenConfiguration(board);

    	return 0;
}
