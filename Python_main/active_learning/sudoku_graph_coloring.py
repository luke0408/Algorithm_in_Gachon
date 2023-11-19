import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import networkx as nx
from networkx.algorithms.coloring import greedy_color
import itertools

# Create sudoku puzzle
puzzle = np.asarray(
  [
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
)

# Set-up
n = 3
G = nx.sudoku_graph(n)
number_set = set(range(1, n * n + 1))
mapping = dict(zip(G.nodes(), puzzle.flatten()))
pos = dict(zip(list(G.nodes()), nx.grid_2d_graph(n * n, n* n)))

# We map the nodes 1-9 to a color map
low, *_, high = sorted(mapping.values())
norm = mpl.colors.Normalize(vmin=low, vmax=high, clip=True)
mapper = mpl.cm.ScalarMappable(norm=norm, cmap=mpl.cm.Pastel1)

# Draw the graph
def draw_graph(G, mapping, pos):
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
  
draw_graph(G, mapping, pos)

# get edges
def sudoku_edges(g, n):
  box_edges = []
  row_edges = []
  col_edges = []
  boxes = []
  
  for i in range(n):
    for j in range(n):
      box = [
        (n * i) + (j * (n * n * n)) + ((n * n) * k) + l
        for k in range(n)
        for l in range(n)
      ]
      boxes.append(box)
      
  for i in range(n * n):
    row_edges += list(itertools.combinations([i + (n * n) * j for j in range(n * n)], 2))
    box_edges += list(itertools.combinations(boxes[i], 2))
    col_edges += list(itertools.combinations(list(g.nodes())[i * n * n : (i + 1) * n * n], 2))

  return row_edges, col_edges, box_edges

# Solve the puzzle using graph coloring
def sudoku_graph_coloring(G, puzzle, number_set, mapping, pos):
  colors = {}
  
  for node in G.nodes():
    neighbors = set(G.neighbors(node))
    neighbor_colors =  {colors[n] for n in neighbors if n in colors}
    available_colors = number_set - neighbor_colors
    
    if len(available_colors) == 0:
      return None
  
    colors[node] = min(available_colors)
    
  node_colors = [colors[node] for node in G.nodes()]
  nx.draw(G, pos, node_colors=node_colors, labels=mapping, cmap=plt.cm.Pastel1, node_size=1000)
  plt.show()
  
  for node, color in colors.items():
    puzzle[node] = color
  
  return puzzle

solved_puzzle = sudoku_graph_coloring(G, puzzle, number_set, mapping, pos)
if solved_puzzle is not None:
    # Display solved puzzle
    print("Solved Sudoku Puzzle:")
    print(np.array(solved_puzzle).reshape(9, 9))
else:
    print("No solution possible for the given Sudoku puzzle.")

    
  