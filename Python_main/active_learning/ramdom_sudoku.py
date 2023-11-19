import networkx as nx
from random import sample
import matplotlib as mpl
import matplotlib.pyplot as plt

# Generate a random sudoku
def generate_random_sudoku(n):
  side = n * n
  
  def _pattern(r, c):
    return (n * (r % n) + r // n + c) % side
  
  rBase = range(n)
  rows = [g * n + r for g in sample(rBase, n) for r in sample(rBase, n)]
  cols = [g * n + c for g in sample(rBase, n) for c in sample(rBase, n)]
  nums = sample(range(1, n * n + 1), n * n)
  
  print("rows: ", rows)
  print("cols: ", cols)
  print("nums: ", nums)
  
  board = [nums[_pattern(r, c)] for r in rows for c in cols]
  
  # board printing
  print("board: ", board)
  
  return board

# Set-up
n = 3
G = nx.sudoku_graph(n)
board = generate_random_sudoku(n)
mapping = dict(zip(G.nodes, board))
pos = dict(zip(list(G.nodes()), nx.grid_2d_graph(n * n, n* n)))

# We map the nodes 1-9 to a color map
low, *_, high = sorted(mapping.values())
norm = mpl.colors.Normalize(vmin=low, vmax=high, clip=True)
mapper = mpl.cm.ScalarMappable(norm=norm, cmap=mpl.cm.Pastel1)

# Draw the graph
plt.figure(1, figsize=(12, 12))
nx.draw(
    G,
    pos=pos,
    labels=mapping,
    node_size=1000,
    node_color=[mapper.to_rgba(i) for i in mapping.values()],
    with_labels=True,
)

# plt.show()