Alunos: Heloísa Dias Viotto e Guilherme Eduardo Gonçalves da Silva

FUNÇÕES AUXILIARES:

Em rede_metabolica.c:
	* Separa: recebe um vetor de caracteres LINHA e um caractere SEPARADOR. Retorna LINHA com a adição de '\0' no primeiro SEPARADOR encontrado. Utilizado na leitura do arquivo.
	* ehEnzima: recebe um vértice V e retorna 1 caso ele pertença ao partição ENZIMA, 0 caso contrário. Utilizado na função PROCESSA.
	* qtd_enzima: recebe um vértice V e retorna a quantidade de vértices enzimas ligadas a ele.


PONTOS IMPORTANTE DE IMPLEMENTAÇÃO:

Em rede_metabolica.c:
	* adiona_reacao_falsa: como a lista de substrato torna-se vazia nesta função e ela não é utilizada em nenhum momento, é liberado a memória desta lista.
	* adiona_reacao_falsa: os vértices RF e SF possuem, respectivamente, índices 0 e -1 e são ligadas por arestas de id negativo.
	* inicializa_custos: para inicializar o variável CUSTO de um vértice, é utilizado o define INT_MAX.

Em analise.c:
	* adição da função destroi_grafo.


RESULTADOS DA IMPLEMENTAÇÃO:
	* Dada uma reação R3 que utiliza dois metabólitos M1 e M2 e forma M3. M1 pode ser formada por uma reação R1 de custo 0 ou por R2 de custo 1, a qual também forma M2. Ao imprimir o caminho mínimo de M3, aparecerá as reações R3 R2 R1. Na realidade, não é necessário as duas reações, apenas a R2 que produz ambos os substratos, no entanto, devido a forma em que o programa foi implementado, é ambas as reações, visto que o pai de M1 é diferente de M2, apesar de poderem ser formadas pela mesma reação. 
