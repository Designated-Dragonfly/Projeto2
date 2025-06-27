#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcao para comparacao de numeros
int comp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

//Funcao de comparação para strings
int comp_str(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return strcmp(str1, str2);
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        // Caso o numero de valores passados na chamada do programa seja diferente de 3
        // Imprime mensagem de erro e retorna 1
        printf("Numero de parametros invalidos, tente novamente\n");
        return 1;
    }

    int file_name_last_char = strlen(argv[2]) - 4;    
    char output_file_name[file_name_last_char+11];
    // Cria um array para armazenar o nome do novo arquivo
    char *sufix = "_sorted.txt,";

    for (int letter_posi=0; letter_posi <= file_name_last_char + 11; letter_posi++) {
        if (letter_posi < file_name_last_char) {
            output_file_name[letter_posi] = argv[2][letter_posi];
        } else {
            output_file_name[letter_posi] = sufix[letter_posi-file_name_last_char];
        }
        // Copia os caracterres para o novo nome
    }
    output_file_name[file_name_last_char+11] = '\0';
    // Adiciona o caracter de fim da stirng

    FILE *input_file = fopen(argv[2], "r");
    FILE *output_file = fopen(output_file_name, "w");
    // Abre o arquivo para leitura e cria o dos resultados

    // Checa se os arquivos foram corretamente abertos/criados
    if (input_file == NULL) {
        printf("Nao foi possivel abrir o arquivo\n");
    } else if (output_file == NULL) {
        printf("Nao foi possivel criar/abrir o arquivo de resultados");
    }

// PARTE DOS NOMES ---

    if (strcmp(argv[1], "-s") == 0) {
        // Caso seja um arquivo de texto com nomes

        int line_number = 0;
        char buffer[1000];

        // Contar número de linhas
        while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
            line_number++;
        }

        rewind(input_file); //  Voltar ao início do arquivo

        // Alocar espaço para os nomes
        char **nomes = malloc(sizeof(char*) * line_number);

        for (int i = 0; i < line_number; i++) {
            fgets(buffer, sizeof(buffer), input_file);
            buffer[strcspn(buffer, "\n")] = '\0'; // Remove o '\n'

            nomes[i] = malloc(strlen(buffer) + 1);
            strcpy(nomes[i], buffer); // Copia o nome
        }

        //Ordenar os nomes
        qsort(nomes, line_number, sizeof(char *), comp_str);

        //  Escrever nomeno arquivo de saída
        for (int i = 0; i < line_number; i++) {
            fprintf(output_file, "%s\n", nomes[i]);
            free(nomes[i]); // Liberar memória individual
        }

        free(nomes); // Liberar array de ponteiros

    } else if (strcmp(argv[1], "-f") == 0) {
        int line_number = 0;

        // Conta o numero de linhas no arquivo
        char c;
        for (c = getc(input_file); c != EOF; c = getc(input_file)) {
            if (c == '\n')
                line_number++;
        }

        // Move o cursor de volta para o inicio
        rewind(input_file);

        // Aloca memoria para a lista de numeros
        float *line_values = malloc(sizeof(float)*line_number);

        for (int posi=0; posi <= line_number; posi++) {
            // Le todos os numeros para a lista
            fscanf(input_file, "%f", &line_values[posi]);
            
        }

        // Ordena a lista de numeros
        qsort(line_values,line_number+1, sizeof(float), comp);

        // Escreve os numeros da lista para o arquivo de output
        for(int i = 0; i <=line_number; i++) {
            fprintf(output_file,"%.8f\n", line_values[i]);
            printf("%f\n", line_values[i]);
        }

        // Libera a memoria utilizada para a lista
        free(line_values);

    } else {
        printf("Opcao invalida, tente novamente\n");
    }

    // Fecha os dois arquivos
    fclose(input_file);
    fclose(output_file);

    return 0;
}
