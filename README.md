
# Objetivo

O objetivo deste trabalho é manipular estruturas para a representação e análise de redes metabólicas. Para tanto, um programa e suas devidas funções devem ser implementadas com base na biblioteca de grafos disponibilizada ao final deste enunciado.

# Contextualização

Uma **rede metabólica** pode ser representada por uma grafo direcionado no qual o conjunto de vértices é particionado em **metabólitos**, **reações metabólicas**  e **enzimas**. A direção dos arcos é relevante: se **M** é um metabólito que serve como substrato para uma reação **R**, então há um arco de  **M**  para  **R**; se **M** é um metabólito produzido por uma reação  **R**, então há um arco de  **R**  para  **M**; e se  **E** é uma enzima que catalisa uma reação  **R**, então há um arco de  **E**  para  **R**. No caso mais geral, um mesmo metabólito pode servir como substrato para várias reações, e pode também ser produzido por diferentes reações. Uma reação, por sua vez, pode precisar de vários substratos, e pode também produzir vários metabólitos.

# Especificação

Um programa  **analise**  deve ser escrito para ler informações de uma rede metabólica de um arquivo de texto com terminação  **.met** com a seguinte estrutura:

-   Cada linha do arquivo apresenta uma  **reação metabólica**  definida por um nome, uma sequência de metabólitos (substratros) e enzimas necessárias, e uma sequência de metabólitos produzidos pela reação. Exemplo:  **R1 M1 + _E1 => M2 .**  (reação chamada  **R1**  precisa do metabólito  **M1**  e da enzima  **_E1**  para produzir o metabólito  **M2**).
-   Todos os atributos (nome, metabólitos e enzimas) são strings sem espaço, mas sempre há um espaço entre os atributos e outros símbolos necessários ("+" e "=>"). Para diferenciar enzimas de metabólitos, toda enzima começa com o caractere "_". A linha termina com um espaço seguido do caractere "." (ponto).
-   A última linha do arquivo contém apenas a string "FIM" e indica o final da rede metabólica

O programa deve construir um grafo direcionado 3-partido representando a rede lida. O grafo construído deve ser impresso na tela.

Na sequência, o programa deve ler da entrada padrão uma sequência de metabólitos separados por espaço representando substratos iniciais (disponíveis). A linha termina com a string "FIM". O programa deve então calcular e mostrar na tela, para todos os metabólitos da rede, qual é o conjunto de reações necessárias para gerar esse metabólito, a partir dos substratos iniciais, com a menor quantidade possível de enzimas.

O programa deve ser chamado da seguinte maneira:

**$ ./analise rede.met < substratos.in**

onde  **substratos.in**  contém os substratos iniciais a serem lidos pela entrada padrão.

Considere as seguintes dicas para desenvolver o seu algoritmo:

1.  Adicione ao grafo um "metabólito falso" e uma "reação falsa" que produz, a partir deste metabólito, todos os substratos iniciais;
2.  Execute um algoritmo baseado no Algoritmo de Dijkstra para encontrar os caminhos mínimos do "metabólito falso" para todos os demais no grafo, respeitando a direção dos arcos.
3.  O custo de um metabólito até outro é a soma das quantidades de enzimas que cada reação intermediária precisa.

# Entrega

Ao final deste enunciado estão disponíveis cabeçalhos e códigos parcialmente implementados para auxiliar no desenvolvimento do programa. As assinaturas das funções e estruturas de dados podem ser modificadas, mas  **não é recomendável**, pois são suficientes para o desenvolvimento de todo o programa. Em particular, a implementação de lista disponível é suficiente para todos os algoritmos neste trabalho. Por outro lado,  **é recomendável**  que funções auxiliares adicionais sejam criadas sempre que necessário.

Um arquivo  **LEIAME**  deve ser criado com os nomes dos autores e informações relevantes sobre o programa, tais como: detalhes de implementação, funções auxiliares criadas, funções e/ou estruturas de dados modificadas, limitações de funcionamento, etc.

O trabalho pode ser feito individual ou em dupla. Um arquivo  **.zip** deve ser entregue contendo todos os arquivos do programa, Makefile e LEIAME.

# Critérios de Avaliação

-   **10% da nota:**  qualidade do código, clareza e documentação
-   **20% da nota:**  adequação à especificação, entrada e saída
-   **20% da nota:**  manipulação adequada das estruturas de dados para grafos
-   **20% da nota:**  criação adequada da rede metabólica
-   **30% da nota:**  funcionamento do algoritmo de busca

# Exemplos e Materiais

Como exemplo de entrada e saída, anexado a este enunciado estão disponíveis os arquivos  **rede.met**, **substratos.in**  e  **resultado.out**, sendo este último a saída do programa com os outros arquivos como entrada:# Objetivo

O objetivo deste trabalho é manipular estruturas para a representação e análise de redes metabólicas. Para tanto, um programa e suas devidas funções devem ser implementadas com base na biblioteca de grafos disponibilizada ao final deste enunciado.

# Contextualização

Uma **rede metabólica** pode ser representada por uma grafo direcionado no qual o conjunto de vértices é particionado em **metabólitos**, **reações metabólicas**  e **enzimas**. A direção dos arcos é relevante: se **M** é um metabólito que serve como substrato para uma reação **R**, então há um arco de  **M**  para  **R**; se **M** é um metabólito produzido por uma reação  **R**, então há um arco de  **R**  para  **M**; e se  **E** é uma enzima que catalisa uma reação  **R**, então há um arco de  **E**  para  **R**. No caso mais geral, um mesmo metabólito pode servir como substrato para várias reações, e pode também ser produzido por diferentes reações. Uma reação, por sua vez, pode precisar de vários substratos, e pode também produzir vários metabólitos.

# Especificação

Um programa  **analise**  deve ser escrito para ler informações de uma rede metabólica de um arquivo de texto com terminação  **.met** com a seguinte estrutura:

-   Cada linha do arquivo apresenta uma  **reação metabólica**  definida por um nome, uma sequência de metabólitos (substratros) e enzimas necessárias, e uma sequência de metabólitos produzidos pela reação. Exemplo:  **R1 M1 + _E1 => M2 .**  (reação chamada  **R1**  precisa do metabólito  **M1**  e da enzima  **_E1**  para produzir o metabólito  **M2**).
-   Todos os atributos (nome, metabólitos e enzimas) são strings sem espaço, mas sempre há um espaço entre os atributos e outros símbolos necessários ("+" e "=>"). Para diferenciar enzimas de metabólitos, toda enzima começa com o caractere "_". A linha termina com um espaço seguido do caractere "." (ponto).
-   A última linha do arquivo contém apenas a string "FIM" e indica o final da rede metabólica

O programa deve construir um grafo direcionado 3-partido representando a rede lida. O grafo construído deve ser impresso na tela.

Na sequência, o programa deve ler da entrada padrão uma sequência de metabólitos separados por espaço representando substratos iniciais (disponíveis). A linha termina com a string "FIM". O programa deve então calcular e mostrar na tela, para todos os metabólitos da rede, qual é o conjunto de reações necessárias para gerar esse metabólito, a partir dos substratos iniciais, com a menor quantidade possível de enzimas.

O programa deve ser chamado da seguinte maneira:

**$ ./analise rede.met < substratos.in**

onde  **substratos.in**  contém os substratos iniciais a serem lidos pela entrada padrão.

Considere as seguintes dicas para desenvolver o seu algoritmo:

1.  Adicione ao grafo um "metabólito falso" e uma "reação falsa" que produz, a partir deste metabólito, todos os substratos iniciais;
2.  Execute um algoritmo baseado no Algoritmo de Dijkstra para encontrar os caminhos mínimos do "metabólito falso" para todos os demais no grafo, respeitando a direção dos arcos.
3.  O custo de um metabólito até outro é a soma das quantidades de enzimas que cada reação intermediária precisa.

# Entrega

Ao final deste enunciado estão disponíveis cabeçalhos e códigos parcialmente implementados para auxiliar no desenvolvimento do programa. As assinaturas das funções e estruturas de dados podem ser modificadas, mas  **não é recomendável**, pois são suficientes para o desenvolvimento de todo o programa. Em particular, a implementação de lista disponível é suficiente para todos os algoritmos neste trabalho. Por outro lado,  **é recomendável**  que funções auxiliares adicionais sejam criadas sempre que necessário.

Um arquivo  **LEIAME**  deve ser criado com os nomes dos autores e informações relevantes sobre o programa, tais como: detalhes de implementação, funções auxiliares criadas, funções e/ou estruturas de dados modificadas, limitações de funcionamento, etc.

O trabalho pode ser feito individual ou em dupla. Um arquivo  **.zip** deve ser entregue contendo todos os arquivos do programa, Makefile e LEIAME.

# Critérios de Avaliação

-   **10% da nota:**  qualidade do código, clareza e documentação
-   **20% da nota:**  adequação à especificação, entrada e saída
-   **20% da nota:**  manipulação adequada das estruturas de dados para grafos
-   **20% da nota:**  criação adequada da rede metabólica
-   **30% da nota:**  funcionamento do algoritmo de busca

# Exemplos e Materiais

Como exemplo de entrada e saída, anexado a este enunciado estão disponíveis os arquivos  **rede.met**, **substratos.in**  e  **resultado.out**, sendo este último a saída do programa com os outros arquivos como entrada:
