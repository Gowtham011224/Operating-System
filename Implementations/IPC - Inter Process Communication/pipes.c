#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 6

// Function to check if placing a queen at a given position is safe
int isSafe(int board[N][N], int row, int col) {
    int i, j;
    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return 0;
    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;
    // Check lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return 0;
    return 1;
}

// Function to solve the N Queens problem recursively
void solveNQueens(int board[N][N], int col, int pipefd[], int process_id) {
    if (col == N) {
        // If all queens are placed, send the solution back through the pipe
        write(pipefd[1], board, N * N * sizeof(int));
        return;
    }
    // Try placing a queen in each row of the current column
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            // If placing a queen at (i, col) is safe, mark it on the board
            board[i][col] = 1;
            // Recur to place queens in the next columns
            solveNQueens(board, col + 1, pipefd, process_id);
            // Backtrack: remove the queen from (i, col) to explore other possibilities
            board[i][col] = 0;
        }
    }
}

int main() {
    int pipefd[2];
    int k = 0;
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        int child_id = getpid() + k; // Increment child process ID
        printf("Requested child processes..\n");
        // Close the unused read end of the pipe
        close(pipefd[0]);
        // Initialize a 4x4 chessboard
        int board[N][N] = {0};
        // Solve the N Queens problem and send the solutions through the pipe
        solveNQueens(board, 0, pipefd, child_id);
        // Close the write end of the pipe after sending the solutions
        close(pipefd[1]);
        _exit(EXIT_SUCCESS);
    } else { // Parent process
        int parent_id = getpid();
        printf("Parent Process ID: %d\n", parent_id);
        // Close the unused write end of the pipe
        close(pipefd[1]);
        int receivedBoard[N][N];
        // Read solutions from the child process through the pipe
        while (read(pipefd[0], receivedBoard, N * N * sizeof(int)) > 0) {
            // Process the received solution (print it, etc.)
            printf("Solution found by Child Process ID: %d\n", pid + k);
            k++;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++)
                    printf("%d ", receivedBoard[i][j]);
                printf("\n");
            }
        }
        // Close the read end of the pipe after reading all solutions
        close(pipefd[0]);
        // Wait for the child process to exit
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}
