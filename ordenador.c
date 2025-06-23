#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
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

    if (strcmp(argv[1], "-s") == 0) {
        // Caso seja um arquivo de texto

        int line_number = 0;

        char c;
        for (c = getc(input_file); c != EOF; c = getc(input_file)) {
            // Read the number of lines in the file
            if (c == '\n')
                line_number++;
        }

        rewind(input_file);
        // Move o pointer para o inicio do arquivo

        printf("numero de linhas: %d\n", line_number+1);

        int *tamanho_dos_nomes = malloc(sizeof(int) * line_number);
        
        int name_size = 0;
        int name_posi = 0;
        int combined_names_size = 0;
        do {
            c = getc(input_file);

            if (c == '\n') {
                tamanho_dos_nomes[name_posi] = name_size;
                name_size=0;
                name_posi++;
            } else {
                name_size++;
                combined_names_size++;
            }

        } while (c != EOF);


        tamanho_dos_nomes[name_posi] = name_size;
        // Adiciona o ultimo elemento

        // Alocar memoria para o array de nomes
        // Inicializar as strings dos nomes



    } else if (strcmp(argv[1], "-f") == 0) {
        // Caso seja um arquivo de numeros

        int line_number = 0;

        char c;
        for (c = getc(input_file); c != EOF; c = getc(input_file)) {
            // Read the number of lines in the file
            if (c == '\n')
                line_number++;
        }

        rewind(input_file);
        // Move o pointer para o inicio do arquivo

        float *line_values = malloc(sizeof(float)*line_number);

        
        for (int posi=0; posi <= line_number; posi++) {
            fscanf(input_file, "%f", &line_values[posi]);
            // Le os valores para um array
        }

        qsort(line_values,line_number+1, sizeof(float), comp);
        // Organiza os valores

        for(int i = 0; i <=line_number; i++) {
            fprintf(output_file,"%.1f\n", line_values[i]);
            // Coloca todos os valores no arquivo de final
        }

        free(line_values);

    } else {
        printf("Opcao invalida, tente novamente\n");

    }

    fclose(input_file);
    fclose(output_file);
    // Fecha os arquivos utilizados

    return 0;
}