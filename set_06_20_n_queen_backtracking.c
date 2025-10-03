#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to check if placing a queen at (row, col) is safe
bool isSafe(int *board, int row, int col) {
    // Check if any queen in previous rows threatens this position
    for (int i = 0; i < row; i++) {
        // Check same column
        if (board[i] == col) return false;
        
        // Check diagonals: if the difference between row and column indices are equal
        if (abs(board[i] - col) == abs(i - row)) return false;
    }
    return true;
}
// Recursive function to solve N-Queens problem
bool solveNQueens(int *board, int row, int n) {
    // If all queens are placed, return true
    if (row == n) return true;
    
    // Try placing queen in all columns of current row
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col)) {
            // Place the queen
            board[row] = col;
            
            // Recur to place rest of the queens
            if (solveNQueens(board, row + 1, n)) {
                return true;
            }
            
            // If placing queen at (row, col) doesn't lead to a solution, backtrack
            board[row] = -1;
        }
    }
    
    // If queen cannot be placed in any column of this row, return false
    return false;
}

// Function to print the board
void printBoard(int *board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i] == j) {
                printf("Q ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the number of queens (N): ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Invalid input. N must be a positive integer.\n");
        return 1;
    }
    
    // Allocate memory for the board
    int *board = (int *)malloc(n * sizeof(int));
    
    // Initialize board with -1 (no queen placed)
    for (int i = 0; i < n; i++) {
        board[i] = -1;
    }
    
    // Solve the N-Queens problem
    if (solveNQueens(board, 0, n)) {
        printf("Solution for %d-Queens problem:\n", n);
        printBoard(board, n);
    } else {
        printf("No solution exists for %d-Queens problem.\n", n);
    }
    
    free(board);
    return 0;
}