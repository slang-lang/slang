#!/usr/bin/python3

from typing import List, Tuple

# Define the Sudoku puzzle
sudoku_board = [
    [3, 0, 5, 0, 8, 0, 0, 0, 9],
    [7, 8, 0, 0, 0, 4, 2, 6, 0],
    [2, 0, 0, 0, 3, 0, 0, 0, 0],
    [0, 1, 0, 0, 2, 0, 4, 0, 0],
    [4, 0, 0, 3, 6, 7, 0, 0, 1],
    [0, 0, 8, 0, 4, 0, 0, 2, 0],
    [0, 0, 0, 0, 7, 0, 0, 0, 4],
    [0, 4, 3, 2, 0, 0, 0, 7, 8],
    [8, 0, 0, 0, 9, 0, 1, 0, 2],
]

# Sudoku solver using backtracking
def is_valid(board: List[List[int]], row: int, col: int, num: int) -> bool:
    block_row, block_col = 3 * (row // 3), 3 * (col // 3)
    return (
        num not in board[row] and
        num not in [board[r][col] for r in range(9)] and
        num not in [board[r][c] for r in range(block_row, block_row + 3)
                               for c in range(block_col, block_col + 3)]
    )

def find_empty(board: List[List[int]]) -> Tuple[int, int]:
    for r in range(9):
        for c in range(9):
            if board[r][c] == 0:
                return r, c
    return -1, -1

def solve_sudoku(board: List[List[int]]) -> bool:
    row, col = find_empty(board)
    if row == -1:  # No empty space left
        return True
    for num in range(1, 10):
        if is_valid(board, row, col, num):
            board[row][col] = num
            if solve_sudoku(board):
                return True
            board[row][col] = 0  # backtrack
    return False

# Solve the puzzle
solve_sudoku(sudoku_board)
sudoku_board

