#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

#define N 4

bool isSafe(char board[N][N], int row, int col) {
    int i, j;

    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i] == 'Q')
            return false;

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 'Q')
            return false;

    // Check lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j] == 'Q')
            return false;

    return true;
}

void printSolution(char board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            std::cout << board[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void solveNQueens(char board[N][N], int col) {
    if (col == N) {
        // If all queens are placed, print the solution
        printSolution(board);
        return;
    }

    for (int i = 0; i < N; i++) {
        // Check if the queen can be placed on board[i][col]
        if (isSafe(board, i, col)) {
            // Place the queen
            board[i][col] = 'Q';

            // Fork a child process to explore further possibilities
            pid_t pid = fork();

            if (pid == 0) { // Child process
                std::cout << "Child Process ID: " << getpid() << std::endl;
                solveNQueens(board, col + 1);
                _exit(0);
            } else if (pid > 0) { // Parent process
                // Wait for the child process to finish
                wait(NULL);
            } else { // Forking error
                std::cerr << "Fork failed." << std::endl;
                _exit(1);
            }

            // Backtrack and remove the queen from board[i][col]
            board[i][col] = '-';
        }
    }
}
int main() {
    char board[N][N];
    // Initialize board with empty cells '-'
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            board[i][j] = '-';

    std::cout << "Parent Process ID: " << getpid() << std::endl;
    solveNQueens(board, 0);

    return 0;
}
