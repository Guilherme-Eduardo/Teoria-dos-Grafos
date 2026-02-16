# ================================ Imports =========================================

#Imprime as informações (Periferia)retiradas de main.py

import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans


df = pd.read_csv("bn-mouse_visual-cortex_2.edges", sep='\s+', header=None, names=["node_1", "node_2"])

G = nx.from_pandas_edgelist(df, "node_1", "node_2", create_using=nx.Graph())

periferia = [61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 150, 151, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146]

node_colors = [
    "red" if node in periferia else "blue" for node in G.nodes()
]

plt.figure(figsize=(8, 6))
pos = nx.spring_layout(G, seed=42)  # Layout para o grafo
nx.draw(
    G,
    pos,
    with_labels=True,
    node_color=node_colors,
    node_size=800,
    font_color="white",
    font_size=10,
)
plt.title("Periferia em vermelho")
plt.savefig("periferia.png", dpi=300, bbox_inches="tight")
plt.show()
