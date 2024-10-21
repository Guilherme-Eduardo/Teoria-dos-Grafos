
# Objetivo

O objetivo deste exercício é manipular estruturas para a representação de moléculas.

# Especificação

Escolha a sua dupla para a realização do Trabalho 2 da disciplina e troquem os códigos entregues no  [Trabalho 1](https://moodle.c3sl.ufpr.br/mod/assign/view.php?id=54673 "Trabalho 1"). Cada membro irá trabalhar com o código do(a) colega. Quaisquer erros que sejam identificados no código devem ser corrigidos e informados por meio de comentários no código e em um arquivo LEIAME a ser entregue. Após as correções, a biblioteca deve ser alterada (se necessário) para representar multi-grafos.

Um programa  **molecula**  deve ser escrito para ler informações de uma molécula no formato **.mol**:

-   As 3 primeiras linhas do arquivo contém cabeçalhos e podem ser ignoradas.
-   Na linha seguinte há diversos valores, mas apenas os 2 primeiros são relevantes neste trabalho. O primeiro é o número **n** de átomos e o segundo é o número **m** de ligações.
-   As próximas **n** linhas contém a descrição de cada átomo, sendo relevante apenas a coluna 4, referente ao  **elemento**  de cada átomo.
-   As **m** linhas seguintes contém informações das ligações, sendo relevantes as colunas 1, 2 e 3, onde as duas primeiras identificam os átomos ligados (numerado de **1** a **n**) e a terceira identifica o  **tipo da ligação**  (1 = simples, 2 = dupla, 3 = tripla).
-   Linhas restantes podem ser ignoradas.

O programa deve construir um multi-grafo representando a molécula lida, onde vértices representam átomos e ligações representam arestas. Ligações duplas e triplas geram, respectivamente, 2 e 3 arestas entre os respectivos vértices. O multi-grafo construído deve ser impresso na tela.

O exercício deve ser entregue de forma individual, mas o(a) colega pode ser consultado(a) para esclarecer dúvidas do código original. Um arquivo **.zip** deve ser entregue contendo todos os arquivos do programa, Makefile e LEIAME.

Arquivos no formato  **.mol**  pode ser obtidos (e visualizados em 3D) no site  [https://hmdb.ca/metabolites](https://hmdb.ca/metabolites). Um bom exemplo para testes é o arquivo  **adenine.mol**


# Mudanças realizadas

## testa_grafo.c:
Adição de controle de casos em digitações de números inválidos (vértice menor ou igual a zero e aresta envolvendo vértices inexistentes) Adição de "printf" antes das escritas, indicando o que deve ser recebido, e em caso de erro.

## grafo.c:
Adição da função subgrafo, a qual transforma o grafo G em um grafo induzido de acordo com os vértices do vetor X Adição de uma função de busca utilizada na função SUBGRAFO dando a informação se um vértice deve ou não ser removido para formar o grafo induzido. Adição de um inteiro PESO na estrutura de dados da aresta. Mudança da função IMPRIME_ARESTA, adicionando a nova informação da aresta, o seu peso, entre colchetes antes dos vértices. Adição da função ATUALIZA_PESO a qual atribui o peso na aresta passada por parâmetro.
## lista.h e lista.c:
 Adição da função "percorre_lista", a qual aplica uma função ACAO em todos os nodos da lista l. Ela foi criada para poder mudar os pesos das aretas ao ter uma aresta ou vertice removidos ou uma nova aresta inserida.
