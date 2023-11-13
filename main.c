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
    int rank;

} JOGADOR;

void main() {
    setlocale(LC_ALL, "Portuguese");

    system("Pause");
    return;
}
