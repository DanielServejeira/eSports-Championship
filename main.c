//Trabalho Prático 3 da matéria de Algoritmos e Técnicas de Programação 2
//Integrantes: Daniel Henrique e Pedro Alonso

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

#include "functions.h"

void main() {
    setlocale(LC_ALL, "Portuguese");

    int menu;
    FILE *file;

    do {
        printf("\n\tMENU\n\n");
        printf("1 - Escrita e Leitura de Jogadores\n");
        printf("2 - Listar Jogadores\n");
        printf("3 - Listar Posição dos Jogadores no Ranking\n");
        printf("4 - Listar Jogadores com mais Vitórias\n");
        printf("5 - Alterar Dados de um Jogador\n");
        printf("6 - Inserir e Atualizar Pontuação no Campeonato\n");
        printf("7 - Listar Classificação do Campeonato\n");
        printf("8 - Listar Jogadores com Pontuação Maior que um Valor\n");
        printf("9 - Listar Jogadores com Pontuação Menor que um Valor\n");
        printf("10 - Buscar Jogador por Nome\n");
        printf("11 - Buscar Jogador por Posição no Ranking\n");
        printf("12 - Mostrar a Quantidade Média de Seguidores de um Jogador\n");
        printf("0 - Sair\n\n");
        scanf("%d", &menu);
        system("cls");

        switch(menu) {
        case 0:
            break;
        case 1:
            escreverJogador(file);
            lerJogador(file);
            system("Pause");
            system("cls");
            break;
        case 2:
            listarJogadoresAlfabetica(file);
            system("Pause");
            system("cls");
            break;
        case 3:
            file = fopen("banco.dat", "rb");
            listarJogadoresRanking(file);
            fclose(file);
            system("Pause");
            system("cls");
            break;
        case 4:
            listarJogadoresVitorias(file);
            system("Pause");
            system("cls");
            break;
        case 5:
            file = fopen("banco.dat", "rb+");
            alterarJogador(file);
            fclose(file);
            system("Pause");
            system("cls");
            break;
        case 6:
            inserirResultado(file);
            system("Pause");
            system("cls");
            break;
        case 7:
            listarClassificacao(file);
            system("Pause");
            system("cls");
            break;
        case 8:
            pontuacaoMaiorQue(file);
            system("Pause");
            system("cls");
            break;
        case 9:
            pontuacaoMenorQue(file);
            system("Pause");
            system("cls");
            break;
        case 10:
            buscarJogadorNome(file);
            system("Pause");
            system("cls");
            break;
        case 11:
            buscarJogadorRanking(file);
            system("Pause");
            system("cls");
            break;
        case 12:
            mediaDeSeguidores(file);
            system("Pause");
            system("cls");
            break;
        default:
            printf("\n\tInsira um comando válido.\n\n");
            system("Pause");
            system("cls");
            break;
        }
    } while(menu != 0);

    return;
}
