# Projeto2

Programa que abre um arquivo de texto contendo um conjunto de números de ponto flutuante ou um conjunto de nomes.

O programa então conta o número de linhas presentes no arquivo e aloca uma quantia adequada de memória para a criação de uma lista com os valores.

Essa lista é então organizada de forma crescente e tem seus valores escritos para um arquivo de texto com o nome igual ao do arquivo lido mas terminado em "_sorted.c".


# Utilização
Primeiro é necessário gerar um executável do código fonte, para isso basta usar o comando `gcc ordenador.c -o NOME`, onde NOME é o nome do executavel gerado.

Depois disso podemos executar o executavel, sempre passando como segundo parametro -s caso estejamos tentando ordenar uma lista de nomes, ou -f se queremos ordenar uma lista de números. Por fim o terceiro parametro deve ser o nome do arquivo de texto onde os valores estão.