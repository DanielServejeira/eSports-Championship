#ifndef FUNCTIONS_
#define FUNCTIONS_

typedef struct data {
    int dia;
    int mes;
    int ano;
} DATA;

typedef enum ecivil {solteiro=1, casado, divorciado, viuvo} E_CIVIL;

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
    char cpf[12];
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

void numeroDeJogadores(FILE *jogadores, int *n);
void escreverJogador(FILE *jogadores, int n);
void lerJogador(JOGADOR lista[], int index);
void listarJogadoresAlfabetica(FILE *jogadores, int n);
void listarJogadoresRanking(FILE *file, int n);
void listarJogadoresVitorias(FILE *jogadores, int n);
void alterarJogador(FILE *jogadores, int *n);
void inserirResultado(FILE *jogadores, int n);
void listarClassificacao(FILE *jogadores, int n);
void pontuacaoMaiorQue(FILE *jogadores, int n);
void pontuacaoMenorQue(FILE *jogadores, int n);
void buscarJogadorNome(FILE *jogadores, int n);
void buscarJogadorRanking(FILE *file);
void mediaDeSeguidores(FILE *jogadores, int n);

#include "functions.c"

#endif // FUNCTIONS_
