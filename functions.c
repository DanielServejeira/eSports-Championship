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

        fseek(file, 0, SEEK_SET);
        while(i < fseek(file, 0, SEEK_END)) {
            while(fread(&jogador, sizeof(JOGADOR), 1, file)) {
                if(jogador.ranking == i + 1) {
                    printf("%d - %s\n", jogador.ranking, jogador.nickname);
                    i++;
                    break;
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
            fseek(file, 0, SEEK_SET);
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
                system("cls");


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
        int i = 1, indice, menuPontuacao;
        JOGADOR jogador;

        do {
            fseek(file, 0, SEEK_SET);
            while(fread(&jogador, sizeof(JOGADOR), 1, file)) {
                printf("%d - %s\n", i, jogador.nickname);
                i++;
            }

            printf("\n\tInsira o índice do jogador desejado para alterar sua pontuação.\n\n");
            printf("0 - Voltar ao menu\n\n");
            scanf("%d", &indice);
            getchar();
            indice--;

            if(indice == -1) {
                printf("\n");
                break;
            }
            if(indice >= 0 && indice < i - 1) {
                system("cls");
                printf("\n\tJogador escolhido: %s", jogador.nickname);
                printf("\n\tPontuação atual: %d", jogador.status.pontuacao);
                printf("\n\nInserir \n"
                       "1 - Vitória\n"
                       "2 - Empate\n"
                       "3 - Derrota\n");
                scanf("%d", menuPontuacao);

                switch(menuPontuacao) {
                case 1:
                    jogador.status.vitorias += 1;
                    jogador.status.pontuacao += 3;
                    break;
                case 2:
                    jogador.status.empates += 1;
                    jogador.status.pontuacao += 1;
                    break;
                case 3:
                    jogador.status.derrotas += 1;
                    break;
                default:
                    printf("\n\tInsira um comando válido.\n\n");
                    system("Pause");
                    system("cls");
                    inserirResultado(file);
                    break;
                }
                fseek(file, indice * sizeof(file), SEEK_SET);
                fwrite(&jogador, sizeof(JOGADOR), 1, file);

                printf("\n\tPontuação alterada com sucesso.\n\n");
                system("Pause");
                system("cls");
                inserirResultado(file);
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

void listarClassificacao(FILE *file) {
    setlocale(LC_ALL, "Portuguese");

    if(file) {
        int i = 0;
        JOGADOR jogador;

        while(i < fseek(file, 0, SEEK_END)) {
            fseek(file, 0, SEEK_SET);
            while(fread(&jogador, sizeof(JOGADOR), 1, file)) {
                if(jogador.ranking == i + 1) {
                    printf("%d - %s\n", i, jogador.nome);
                    printf("Pontuação: %d\n", jogador.status.pontuacao);
                    printf("Vitórias: %d\n", jogador.status.vitorias);
                    printf("Empates: %d\n", jogador.status.empates);
                    printf("Derrotas: %d\n\n", jogador.status.derrotas);
                    i++;
                    break;
                }
            }
        }
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
        int i = 0, indice;
        JOGADOR jogador;

        printf("\n\tInsira um número para listar jogadores com uma pontuação menor.\n\n");
        scanf("%d", &indice);
        printf("\n");

        if(indice < 0) {
            printf("\n\tInsira um comando válido.\n\n");
            system("Pause");
            system("cls");
            pontuacaoMenorQue(file);
        }

        while(indice >= 0) {
            fseek(file, 0, SEEK_SET);
            while(fread(&jogador, sizeof(JOGADOR), 1, file)) {
                if(jogador.status.pontuacao == indice) {
                    printf("%d - %s\n", jogador.ranking, jogador.nickname);
                    printf("Pontuação: %d\n\n", jogador.status.pontuacao);
                }
            }
            indice--;
        }
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
        JOGADOR jogador;
        int busca, verif = 1;

        do {
            printf("\n\tInsira um número para ver o jogador que está em seu ranking\n");
            printf("\n0 - Voltar ao menu.\n\n");
            scanf("%d", &busca);

            if(busca < 0) {
                printf("\n\tInsira um comando válido.\n\n");
                system("Pause");
                system("cls");
            }
            else {
                if(busca == 0) {
                    printf("\n");
                    break;
                }
                else {
                    fseek(file, 0, SEEK_SET);
                    while(fread(&jogador, sizeof(JOGADOR), 1, file)) {
                        if(jogador.ranking == busca) {
                            printf("\n\tJogador encontrado.\n\n");
                            printf("%d - %s\n\n", jogador.ranking, jogador.nickname);
                            verif = 0;
                            break;
                        }
                    }

                    if(verif) {
                        printf("\n\tJogador não encontrado.\n\n");
                        system("Pause");
                        system("cls");
                    }
                }
            }
        } while(busca != 0);
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
