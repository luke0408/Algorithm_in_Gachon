import networkx as nx
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

from sudoku_connections import SudokuConnections

class SudokuBoard:
    def __init__(self):

        self.board = self.getBoard()

        self.sudokuGraph = SudokuConnections()
        self.mappedGrid = self.__getMappedMatrix()  # Maps all the ids to the position in the matrix

        # for drawing the board


    def __getMappedMatrix(self):
        matrix = [[0 for cols in range(9)]
                  for rows in range(9)]

        count = 1
        for rows in range(9):
            for cols in range(9):
                matrix[rows][cols] = count
                count += 1
        return matrix

    def getBoard(self):

        board = [
            [0, 4, 3, 0, 8, 0, 2, 5, 0],
            [6, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 1, 0, 9, 4],
            [9, 0, 0, 0, 0, 4, 0, 7, 0],
            [0, 0, 0, 6, 0, 8, 0, 0, 0],
            [0, 1, 0, 2, 0, 0, 0, 0, 3],
            [8, 2, 0, 5, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 5],
            [0, 3, 4, 0, 9, 0, 7, 1, 0],
        ]
        return board

    def drawBord(self):

        # Set-up
        n = 3
        G = nx.sudoku_graph(n)
        puzzle = np.asarray(self.board)
        mapping = dict(zip(G.nodes(), puzzle.flatten()))
        pos = dict(zip(list(G.nodes()), nx.grid_2d_graph(n * n, n * n)))

        # We map the nodes 1-9 to a color map
        number_set = dict(zip(G.nodes(), range(0, 11)))
        low, *_, high = sorted(number_set.values())
        norm = mpl.colors.Normalize(vmin=low, vmax=high, clip=True)
        mapper = mpl.cm.ScalarMappable(norm=norm, cmap=mpl.cm.Pastel1)

        # Draw the graph
        plt.figure(figsize=(12, 12))
        nx.draw(
            G,
            labels=mapping,
            pos=pos,
            with_labels=True,
            node_color=[mapper.to_rgba(i) for i in mapping.values()],
            width=1,
            node_size=1000,
        )
        plt.show()

    def printBoard(self):
        board = list(zip(*self.board))[::-1]
        print("    1 2 3     4 5 6     7 8 9")
        for i in range(len(board)):
            if i % 3 == 0:  # and i != 0:
                print("  - - - - - - - - - - - - - - ")

            for j in range(len(board[i])):
                if j % 3 == 0:  # and j != 0 :
                    print(" |  ", end="")
                if j == 8:
                    print(board[i][j], " | ", i + 1)
                else:
                    print(f"{board[i][j]} ", end="")
        print("  - - - - - - - - - - - - - - ")

    def graphColoringInitializeColor(self):
        """
        fill the already given colors
        """
        color = [0] * (self.sudokuGraph.graph.totalV + 1)
        given = []  # list of all the ids whos value is already given. Thus cannot be changed
        for row in range(len(self.board)):
            for col in range(len(self.board[row])):
                if self.board[row][col] != 0:
                    # first get the idx of the position
                    idx = self.mappedGrid[row][col]
                    # update the color
                    color[idx] = self.board[row][col]  # this is the main imp part
                    given.append(idx)
        return color, given

    def solveGraphColoring(self, m=9):

        color, given = self.graphColoringInitializeColor()
        if self.__graphColorUtility(m=m, color=color, v=1, given=given) is None:
            print(":(")
            return False
        count = 1
        for row in range(9):
            for col in range(9):
                self.board[row][col] = color[count]
                count += 1
        return color

    def __graphColorUtility(self, m, color, v, given):

        if v == self.sudokuGraph.graph.totalV + 1:
            return True
        for c in range(1, m + 1):
            if self.__isSafe2Color(v, color, c, given) == True:
                color[v] = c
                if self.__graphColorUtility(m, color, v + 1, given):
                    return True
            if v not in given:
                color[v] = 0

    def __isSafe2Color(self, v, color, c, given):

        if v in given and color[v] == c:
            return True
        elif v in given:
            return False

        for i in range(1, self.sudokuGraph.graph.totalV + 1):
            if color[i] == c and self.sudokuGraph.graph.isNeighbour(v, i):
                return False
        return True


def main():
    s = SudokuBoard()
    print("BEFORE SOLVING ...")
    print("\n\n")
    s.printBoard()
    s.drawBord()
    print("\nSolving ...")
    print("\n\n\nAFTER SOLVING ...")
    print("\n\n")
    s.solveGraphColoring(m=9)
    s.printBoard()
    s.drawBord()


if __name__ == "__main__":
    main()