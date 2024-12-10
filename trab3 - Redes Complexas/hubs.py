# ================================ Imports =========================================

#Imprime as informações (Hubs)retiradas de main.py


import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans


df = pd.read_csv("bn-mouse_visual-cortex_2.edges", sep='\s+', header=None, names=["node_1", "node_2"])



G = nx.from_pandas_edgelist(df, "node_1", "node_2", create_using=nx.Graph())

hubs = [9,10,2,5,82,149,11,7,103,104,105,12]


node_colors = [
    "red" if node in hubs else "blue" for node in G.nodes()
]


plt.figure(figsize=(8, 6))
pos = nx.spring_layout(G, seed=42)  # Layout para o grafo
nx.draw(
    G,
    pos,
    with_labels=True,
    node_color=node_colors,
    node_size=300,
    font_color="white",
    font_size=7,
)
plt.title("Principais Hubs")
plt.savefig("hubs.png", dpi=300, bbox_inches="tight")
plt.show()