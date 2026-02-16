# ================================ Imports =========================================


#Imprime as informações (Centralidade)retiradas de main.py

import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans


df = pd.read_csv("bn-mouse_visual-cortex_2.edges", sep='\s+', header=None, names=["node_1", "node_2"])

G = nx.from_pandas_edgelist(df, "node_1", "node_2", create_using=nx.Graph())

centralidade_grau = 10
centralidade_proximidade = 82
intermediacao = 5

node_colors = [
    "red" if node == centralidade_grau else
    "green" if node == centralidade_proximidade else
    "purple" if node == intermediacao else
    "blue"  # Cor padrão para outros nós
    for node in G.nodes()
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
plt.title("Vértices centrais destacados")
plt.savefig("vertices_destacados.png", dpi=300, bbox_inches="tight")
plt.show()
