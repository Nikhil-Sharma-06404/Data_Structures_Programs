def solve_n_queens(n):
    board = [-1] * n
    solution_found = False

    def is_safe(row, col):
        for i in range(col):
            if board[i] == row or abs(board[i] - row) == abs(i - col):
                return False
        return True

    def print_solution():
        # Print the board as a matrix with 'Q' and '.'
        for r in range(n):
            row_output = []
            for c in range(n):
                if board[c] == r:
                    row_output.append("Q")
                else:
                    row_output.append(".")
            print(" ".join(row_output))
        # Print the queen positions; index: column, value: row
        print("Position:", tuple(board))
        print()

    def backtrack(col):
        nonlocal solution_found
        if col == n:
            print_solution()
            solution_found = True
            return
        for row in range(n):
            if is_safe(row, col):
                board[col] = row
                backtrack(col + 1)
                if solution_found:
                    return
                board[col] = -1

    backtrack(0)


print("Solution for 4-Queens:")
solve_n_queens(4)

print("Solution for 8-Queens:")
solve_n_queens(8)
