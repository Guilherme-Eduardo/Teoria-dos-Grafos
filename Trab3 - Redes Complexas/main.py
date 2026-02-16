# ================================ Imports =========================================

import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from networkx.algorithms.community import k_clique_communities
from networkx.algorithms.community import girvan_newman


# Ler o arquivo com pandas
df = pd.read_csv("bn-mouse_visual-cortex_2.edges", sep='\s+', header=None, names=["node_1", "node_2"])


# Criar o grafo usando o DataFrame. "node_1" e "node_2" são os vertices.
G = nx.from_pandas_edgelist(df, "node_1", "node_2", create_using=nx.Graph())


print("\n=============================== Tipos de grafos ==========================================\n")

# Verifica se ele é direcionado
if (nx.is_directed(G)):
    print ("O grafo analisado é direcionado")
else: 
    print ("O grafo analisado NAO é direcionado")



print("\n================================ Análise das centralidades  ================================\n")


# Analise os tipos de centralidade


# Degree Centrality
degree = nx.degree_centrality(G)
degCent_sorted = dict(sorted(degree.items(), key=lambda item: item[1], reverse=True))
most_central_deg = list(degCent_sorted.keys())[0]
print(f"Nó com maior centralidade de grau: {most_central_deg} (valor: {degCent_sorted[most_central_deg]})")


# Closeness centrality
closeness = nx.closeness_centrality(G)
closeness_sorted = dict(sorted(closeness.items(), key=lambda item: item[1], reverse=True))
most_central_closeness = list(closeness_sorted.keys())[0]
print (f"Nó com maior centralidade de proximidade: {most_central_closeness} (valor: {closeness_sorted[most_central_closeness]})")



#betweenness_centrality
betweenness = nx.betweenness_centrality(G)
betCent_sorted = dict(sorted(betweenness.items(), key=lambda item: item[1], reverse=True))
most_central_bet = list(betCent_sorted.keys())[0]
print(f"Nó com maior centralidade de intermediação: {most_central_bet} (valor: {betCent_sorted[most_central_bet]})")



print("\n=============================== Raio, diametro, periferia e  centro =============================\n")

# Verifica se o grafo é conexo. Sendo assim, passa as demais informações sobre
if nx.is_connected(G):
    print ("Grafo é conectado!")
    radius = nx.radius(G)
    print(f"O raio do grafo é: {radius}")
    
    diameter = nx.diameter(G)
    print(f"O diâmetro do grafo é: {diameter}")
    
    periphery = nx.periphery(G)
    print(f"A periferia do grafo é: {periphery}")
    
    center = nx.center(G)
    print(f"O centro do grafo é: {center}")
else:
    print("O grafo não é conectado; não é possível calcular raio, diâmetro, periferia ou centro.")



print("\n================================= Ciclo ===============================================\n")


# Verifica o maior ciclo
cicle = sorted (nx.cycle_basis(G))
maior_ciclo = max(cicle, key=len)
print(f"O maior ciclo possui {len(maior_ciclo)} vertices e é composto por: {maior_ciclo}")


# Classifica por tamanho de elementos 
ciclos_por_tamanho = {}
for ciclo in cicle:
    tamanho = len(ciclo)
    ciclos_por_tamanho[tamanho] = ciclos_por_tamanho.get(tamanho, 0) + 1

# Numero total de ciclos do grafo
total_ciclos = len(cicle)
print(f"Total de ciclos: {total_ciclos}")
print (f"Ciclos: {cicle}")


print("\nClassificação dos ciclos por tamanho:")
for tamanho, quantidade in sorted(ciclos_por_tamanho.items()):
    print(f"{quantidade} ciclos com {tamanho} vértices")



print("\n================================= componente conexa =================================\n")

# Obtendo as componentes conexas
componente_conexa = nx.connected_components(G)

# Convertendo para lista e ordenando pelo tamanho (do maior para o menor)
componentes = sorted(componente_conexa, key=len, reverse=True)

# Imprimindo a maior componente conexa
if componentes:
    print(f"Tamanho da maior componente conexa: {len(componentes[0])}")
    print(f"Formada por: {list(componentes[0])}")
else:
    print("O grafo não possui componentes conexas.")



print("\n================================= Distribuiçao dos graus ===============================\n")


# Verificando vertice com maior grau do Grafo
maior_grau = max(G.degree(), key=lambda x: x[1])  # Retorna (nó, grau)

# Separando o nó e o grau
no = maior_grau[0]
grau = maior_grau[1]
print(f"Nó com maior grau: {no}, Grau: {grau}")


# Calculando a sequência de graus
dist_grau = sorted([d for n, d in G.degree()], reverse=True)

# conf. gráfico
fig = plt.figure("Distribuição dos Graus", figsize=(12, 8))
axgrid = fig.add_gridspec(5, 4)

# Plotando
ax1 = fig.add_subplot(axgrid[3:, :2])
ax1.plot(dist_grau, "b-", marker="o")
ax1.set_title("Distribuição dos Graus")
ax1.set_ylabel("Grau")
ax1.set_xlabel("Classificação")

# Exibindo o gráfico
plt.tight_layout()
plt.savefig("Grau_vertice.png", dpi=300, bbox_inches="tight")
plt.show()


print("\n================================ Arvore geradora =====================================\n")

# Verifica a árvore geradora 
T = nx.minimum_spanning_tree (G)
print(list(T.nodes()))

print ("Imprimindo arvore geradora")
print (T)


plt.figure(figsize=(10,10))
pos = nx.spring_layout(T, seed=42)
nx.draw(
    G,
    pos,
    with_labels=True,
    node_color="blue",
    node_size=150,
    font_color="white",
    font_size=10,
)
plt.title("Arvore Geradora")
plt.savefig("Arvore Geradora.png", dpi=300, bbox_inches="tight")
plt.show()



print("\n================================= Hubs =================================\n")
 
# Calcula os hubs conforme funcao hits
hubs, _ = nx.hits(G, max_iter=100, tol=1e-8, normalized=True)

# Identificar os maiores hubs
hubs_sorted = sorted(hubs.items(), key=lambda x: x[1], reverse=True)

# Exibir os maiores hubs
print("Maiores Hubs:")
for node, score in hubs_sorted:
    print(f"Nó {node}: Pontuação de Hub {score:.4f}")



print("\n================================ clusters =====================================\n")

# Cria os clusters conforme o algoritmo de Girva-Newman

communities = girvan_newman(G)

first_division = next(communities)
print ("Comunidade encontradas: ", [list(c) for c in first_division])


# Divisão em 2 clusters
cluster1 = list(first_division[0])
cluster2 = list(first_division[1])

print ("Cluster 1: ", cluster1)
print ("Cluster 2: ", cluster2)


node_colors = [
    "red" if node in cluster1 else "blue" if node in cluster2 else "gray" for node in G.nodes()
]

plt.figure(figsize=(8, 6))
pos = nx.spring_layout(G, seed=42)  # Layout para o grafo
nx.draw(
    G,
    pos,
    with_labels=True,
    node_color=node_colors,
    node_size=200,
    font_color="white",
    font_size=10,
)
plt.title("Separação por clusters")
plt.savefig("clusters.png", dpi=300, bbox_inches="tight")
plt.show()


print("\n================================== Cliques ============================================\n")


# Verifica os cliques do grafo, a quantidade e o tamanho 

cliques = list(nx.find_cliques(G))
cliques_sorted = sorted(cliques, key=len, reverse=True)
print("Cliques maximos:", cliques_sorted)

largest_clique = max(cliques, key=len)
print("Maior clique:", largest_clique)

num_cliques = len(cliques)
print(f"Quantidade de cliques encontrados: {num_cliques}")


# Contar cliques por tamanho
cliques_por_tamanho = {}
for clique in cliques:
    tamanho = len(clique)
    if tamanho in [2, 3]:  # Filtrar apenas os tamanhos desejados (2 e 3)
        cliques_por_tamanho[tamanho] = cliques_por_tamanho.get(tamanho, 0) + 1


# Exibir a contagem
for tamanho, quantidade in cliques_por_tamanho.items():
    print(f"{quantidade} cliques com tamanho {tamanho}")



print("\n================================= Conjunto independente =================================\n")

# Verifica os conjuntos independentes (subconjunto aproximado) = NP-Dificil

maximal = nx.maximal_independent_set(G)
aproxCI = nx.approximation.maximum_independent_set(G)


maximal_sorted = sorted(maximal, reverse=True)
aproxCI_sorted = sorted(aproxCI, reverse=True)

print(f"Tamanho do conjunto maximal: {len(maximal_sorted)}")
print(f"Conjunto maximal ordenado (decrescente): {maximal_sorted}")
print()
print(f"Tamanho do conjunto aproximado: {len(aproxCI_sorted)}")
print(f"Conjunto aproximado ordenado (decrescente): {aproxCI_sorted}")


print("\n================================= Densidade =================================\n")

densidade = nx.density(G)

print (f"A densidade do grafo é: {densidade}")


#================================== Plotando o grafo ==============================================


plt.figure(figsize=(12,12))
nx.draw_networkx(G, with_labels=True, node_size=200, node_color='skyblue', font_size=8, font_weight='bold')


plt.title("Grafo")
plt.savefig("Grafo.png", dpi=300, bbox_inches="tight")
plt.show()

print(f'Número de nós: {G.number_of_nodes()}')
print(f'Número de arestas: {G.number_of_edges()}')
