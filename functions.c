#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

typedef struct data {
    int dia;
    int mes;
    int ano;
} DATA;

typedef enum ecivil {solteiro, casado, divorciado, viuvo} E_CIVIL;

typedef struct equipe {
    char nome[30];
    char nickname[30];
    int seguidores;
} EQUIPE;

typedef struct hardware {
    char modelo[50];
    char processador[50];
    char placaGrafica[50];
    int memRAM;
} HARDWARE;

typedef struct campeonato {
    int pontuacao;
    int vitorias;
    int derrotas;
    int empates;
} STATUS_CAMPEONATO;

typedef struct jogador{
    char nome[50];
    DATA nascimento;
    char cpf[11];
    char genero;
    E_CIVIL estadoCivil;
    EQUIPE equipe;
    char patrocinador[50];
    char nickname[30];
    int seguidores;
    HARDWARE equip;
    STATUS_CAMPEONATO status;
    int titulos;
    int ranking;
} JOGADOR;

void escreverJogador(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {

    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void lerJogador(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {

    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void listarJogadoresAlfabetica(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {

    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void listarJogadoresRanking(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {
        int i = 0;
        JOGADOR jogador;

        while(i < fseek(file, 0, SEEK_END)) {
            while(fread(&jogador, sizeof(JOGADOR), 1, file)) {
                if(jogador.ranking == i + 1) {
                    printf("%d - %s\n", jogador.ranking, jogador.nickname);
                    i++;
                }
            }
            fseek(file, 0, SEEK_SET);
        }
    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void listarJogadoresVitorias(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {

    }
    else perror("\tErro ao abrir o arquivo.\n\n");
}

void alterarJogador(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {
        int i = 1, indice;
        JOGADOR jogador;

        do {
            while(fread(&jogador, sizeof(JOGADOR), 1, file)) {
                printf("%d - %s\n", i, jogador.nickname);
                i++;
            }

            printf("\n\tInsira o índice do jogador que deseja alterar.\n\n");
            printf("0 - Voltar ao menu\n\n");
            scanf("%d", &indice);
            getchar();
            indice--;

            if(indice == -1) {
                printf("\n");
                break;
            }
            if((indice >= 0 && indice < i - 1)) {

                fseek(file, indice * sizeof(file), SEEK_SET);
                fwrite(&jogador, sizeof(JOGADOR), 1, file);

                printf("\n\tDados alterados com sucesso.\n\n");
                system("Pause");
                system("cls");
                alterarJogador(file);
            }
            else {
                printf("\n\tInsira um comando válido.\n\n");
                system("Pause");
                system("cls");
            }
        } while(indice != -1);
    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void inserirResultado(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {

    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void listarClassificacao(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {

    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void pontuacaoMaiorQue(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {

    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void pontuacaoMenorQue(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {

    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void buscarJogadorNome(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {

    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void buscarJogadorRanking(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {

    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void mediaDeSeguidores(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {

    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}
