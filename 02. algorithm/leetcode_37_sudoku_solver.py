class Solution:
    def getStatus(self, board):
        memo = []
        for row, record in enumerate(board):
            for col, val in enumerate(record):
                if val == ".":
                    pos = (row, col)
                    avail = list(map(str, range(1, 10)))

                    for i in range(9):
                        if board[row][i] in avail:
                            avail.remove(board[row][i])

                    for i in range(9):
                        if board[i][col] in avail:
                            avail.remove(board[i][col])

                    brow = (row // 3) * 3
                    bcol = (col // 3) * 3
                    for i in range(3):
                        for j in range(3):
                            if board[brow + i][bcol + j] in avail:
                                avail.remove(board[brow + i][bcol + j])

                    memo.append((pos, avail))
        return sorted(memo, key=lambda x: len(x[1]))

    def solveSudoku(self, board) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        status = self.getStatus(board)
        

        if not status:
            # Failure
            print("Nothing to fill..")
            return
        else:
            pos, avail = status[0]
            for avl in avail:
                board[pos[0]][pos[1]] = avl
                # print(f"{avail}, Put {avl} at ({pos[0]}, {pos[1]})")
                self.solveSudoku(board)
                hasEmpty = self.getStatus(board)
                if not hasEmpty:
                    print("Clear!!")
                    return
            board[pos[0]][pos[1]] = '.'



sol = Solution()

sol.solveSudoku(
    [
        [".", ".", "9", "7", "4", "8", ".", ".", "."], 
        ["7", ".", ".", ".", ".", ".", ".", ".", "."], 
        [".", "2", ".", "1", ".", "9", ".", ".", "."], 
        [".", ".", "7", ".", ".", ".", "2", "4", "."], 
        [".", "6", "4", ".", "1", ".", "5", "9", "."], 
        [".", "9", "8", ".", ".", ".", "3", ".", "."], 
        [".", ".", ".", "8", ".", "3", ".", "2", "."], 
        [".", ".", ".", ".", ".", ".", ".", ".", "6"], 
        [".", ".", ".", "2", "7", "5", "9", ".", "."]
    ]
)
