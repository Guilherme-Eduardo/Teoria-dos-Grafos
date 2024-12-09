# ================================ Imports =========================================

import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

# Passo 1: Ler o arquivo com pandas (usando 'sep' para separar por espaços)
df = pd.read_csv("bn-mouse_visual-cortex_2.edges", sep='\s+', header=None, names=["node_1", "node_2"])


# Passo 2: Criar o grafo usando o DataFrame. "node_1" e "node_2" são os vertices.
G = nx.from_pandas_edgelist(df, "node_1", "node_2", create_using=nx.Graph())


# =============================== Tipos de grafos ==========================================

#Se é direcionado
if (nx.is_directed(G)):
    print ("O grafo analisado é direcionado")
else: 
    print ("O grafo analisado NAO é direcionado")



#================================ Análise das centralidades  ================================


# Esse é o passo a passo para cada tipo de centralidade:

# 1 networkX possui os tipos de centralidade -> ele forma uma lista
# 2 Criamos um dicionario com base nessa lista e ordenamos ela de forma decrescente pelo valor de centralidade (por isso o item[1])
# 3 pegamos o maior vertice com base na centralidade

# O algoritmo abaixo foi baseado nesse link abaixo que eu achei
# https://stackoverflow.com/questions/70027288/identify-the-most-central-nodes-in-a-network-using-networkx


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


# =============================== Raio, diametro, periferia e  centro =============================


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



# ================================= Ciclo ===============================================

# Retorna uma lista de nós

cicle = sorted (nx.simple_cycles (G))
max_cicle = cicle[0]
print (f"O maior ciclo simples possui {len(max_cicle)} e é composto por: {max_cicle}")

cicle = sorted (nx.cycle_basis(G))
max_cicle = cicle[0]
print (f"O maior ciclo basis possui {len(max_cicle)} e é composto por: {max_cicle}")


# ================================= componente conexa =================================

# Obtendo as componentes conexas
connected_components = nx.connected_components(G)

# Convertendo para lista e ordenando pelo tamanho (do maior para o menor)
components_list = sorted(connected_components, key=len, reverse=True)

# Imprimindo a maior componente conexa
if components_list:
    print(f"Tamanho da maior componente conexa: {len(components_list[0])}")
    print(f"Formada por: {list(components_list[0])}")
else:
    print("O grafo não possui componentes conexas.")


# ================================= Distribuiçao dos graus ===============================


# O site abaixo disponibiliza um algoritmo para ver como está a distribuicao dos graus.

#  Poderia dar um bizu? Serviu como base. ELe plota um grafico que mostra os graus...

# https://networkx.org/documentation/stable/auto_examples/drawing/plot_degree.html

# Encontrando o nó com maior grau (parece ser a mesma coisa do degree centrality)
maior_grau = max(G.degree(), key=lambda x: x[1])  # Retorna (nó, grau)

# Separando o nó e o grau
no = maior_grau[0]
grau = maior_grau[1]
print(f"Nó com maior grau: {no}, Grau: {grau}")


# Calculando a sequência de graus
degree_sequence = sorted([d for n, d in G.degree()], reverse=True)

# Configurando o layout do gráfico
fig = plt.figure("Distribuição dos Graus", figsize=(12, 8))
axgrid = fig.add_gridspec(5, 4)

# Subplot 1: Gráfico da sequência de graus
ax1 = fig.add_subplot(axgrid[3:, :2])
ax1.plot(degree_sequence, "b-", marker="o")
ax1.set_title("Distribuição dos Graus")
ax1.set_ylabel("Grau")
ax1.set_xlabel("Classificação")

# Exibindo o gráfico
plt.tight_layout()


# ================================ Arvore geradora e clusters =====================================

# Arvore gerado minimas ? nao entendi a relação disso com redes complexas....


# Clusterização. Fiquei em duvida se ele separa por grupos. Documentação está meio magra

# Perguntei pro chat e ele me disse isso

# Coeficiente de Clusterização Local
# Fórmula:
# Para um nó uuu com kkk vizinhos, o coeficiente de clusterização local C(u)C(u)C(u) é definido como:

# C(u)=nuˊmero de arestas reais entre os vizinhos de unuˊmero maˊximo de arestas possıˊveis entre os vizinhos de uC(u) = \frac{\text{número de arestas reais entre os vizinhos de } u}{\text{número máximo de arestas possíveis entre os vizinhos de } u}C(u)=nuˊmero maˊximo de arestas possıˊveis entre os vizinhos de unuˊmero de arestas reais entre os vizinhos de u​

# Componentes da Fórmula:
# Número de Arestas Reais:

# O número de arestas entre os vizinhos de uuu.
# Número Máximo de Arestas Possíveis:

# Para kkk vizinhos, o número máximo de arestas possíveis entre eles é: k(k−1)2\frac{k(k-1)}{2}2k(k−1)​
# Valores de C(u)C(u)C(u):
# C(u)=1.0C(u) = 1.0C(u)=1.0: Todos os vizinhos de uuu estão completamente conectados entre si (formam um clique completo).
# 0.0<C(u)<1.00.0 < C(u) < 1.00.0<C(u)<1.0: Parte dos vizinhos de uuu está conectada.
# C(u)=0.0C(u) = 0.0C(u)=0.0: Nenhum vizinho de uuu está conectado a outro vizinho.


cluster = nx.clustering (G)
avg_clustering = nx.average_clustering(G)

print (f"Imprimindo clustering: {cluster}")
print("Coeficiente de clusterização médio:", avg_clustering)


# # Kmeans

# # K-means com matriz de adjacência
# adj_matrix = nx.to_numpy_array(G)
# kmeans = KMeans(n_clusters=2, random_state=0, n_init="auto").fit(adj_matrix)
# print(f"Labels do K-means: {kmeans.labels_}")

# ================================== Cliques ============================================

# Encontrar cliques maximais
cliques = list(nx.find_cliques(G))
cliques_sorted = sorted(cliques, key=len, reverse=True)
print("Cliques maximos:", cliques_sorted)

# Encontrar o maior clique
largest_clique = max(cliques, key=len)
print("Maior clique:", largest_clique)


# ================================= Conjunto independente =================================

# Existem 2 códigos que tratam o CI: 

maximal = nx.maximal_independent_set(G)  # NP dificil. Há uma observação no site: Este algoritmo não resolve o problema do conjunto independente máximo.
aproxCI = nx.approximation.maximum_independent_set(G)


maximal_sorted = sorted(maximal, reverse=True)
aproxCI_sorted = sorted(aproxCI, reverse=True)

print(f"Tamanho do conjunto maximal: {len(maximal_sorted)}")
print(f"Conjunto maximal ordenado (decrescente): {maximal_sorted}")

print(f"Tamanho do conjunto aproximado: {len(aproxCI_sorted)}")
print(f"Conjunto aproximado ordenado (decrescente): {aproxCI_sorted}")


# ==========================================================================================



# Pergunta que devemos responder(esta no texto do moodle): qual modelo de grafo melhor representa a rede escolhida?



#================================== Plotando o grafo ==============================================


# Info para plotar o grafo
# Isso está em : https://networkx.org/documentation/stable/reference/generated/networkx.drawing.nx_pylab.draw_networkx.html#networkx.drawing.nx_pylab.draw_networkx
# with_labels: Defina como Verdadeiro para desenhar rótulos nos nós
# Node_size: tamanho dos nós
# node_color = cor
# lista nodelist (padrão=list(G)) = Desenhar apenas nós especificados



plt.figure(figsize=(12,12))
nx.draw_networkx(G, with_labels=True, node_size=200, node_color='skyblue', font_size=8, font_weight='bold')

# Exibir o grafo. Na doc do networkX fala para usarmos juntamente com o matplotlib
plt.show()

print(f'Número de nós: {G.number_of_nodes()}')
print(f'Número de arestas: {G.number_of_edges()}')