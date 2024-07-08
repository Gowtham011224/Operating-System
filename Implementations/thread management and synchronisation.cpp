#include <iostream>
#include <thread>
#include <vector>
#include <array>

#define N 4

bool isSafe(const std::array<std::array<char, N>, N>& board, int row, int col) {
    int i, j;

    // Check this row on the left side
    for (i = 0; i < col; i++)
        if (board[row][i] == 'Q')
            return false;

    // Check upper diagonal on the left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 'Q')
            return false;

    // Check lower diagonal on the left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j] == 'Q')
            return false;

    return true;
}

void printSolution(const std::array<std::array<char, N>, N>& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            std::cout << board[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void solveNQueens(std::array<std::array<char, N>, N> board, int col) {
    if (col == N) {
        // If all queens are placed, print the solution
        printSolution(board);
        return;
    }

    std::vector<std::thread> threads;

    for (int i = 0; i < N; i++) {
        // Check if the queen can be placed on board[i][col]
        if (isSafe(board, i, col)) {
            // Place the queen
            board[i][col] = 'Q';

            // Create a thread to explore further possibilities
            threads.emplace_back(solveNQueens, board, col + 1);

            // Backtrack and remove the queen from board[i][col]
            board[i][col] = '-';
        }
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }
}

int main() {
    std::array<std::array<char, N>, N> board;
    // Initialize board with empty cells '-'
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = '-';

    solveNQueens(board, 0);

    return 0;
}
