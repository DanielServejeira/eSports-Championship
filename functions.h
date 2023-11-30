#ifndef FUNCTIONS_
#define FUNCTIONS_

void escreverJogador(FILE *file);
void lerJogador(FILE *file);
void listarJogadoresAlfabetica(FILE *file);
void listarJogadoresRanking(FILE *file);
void listarJogadoresVitorias(FILE *file);
void alterarJogador(FILE *file);
void inserirResultado(FILE *file);
void listarClassificacao(FILE *file);
void pontuacaoMaiorQue(FILE *file);
void pontuacaoMenorQue(FILE *file);
void buscarJogadorNome(FILE *file);
void buscarJogadorRanking(FILE *file);
void mediaDeSeguidores(FILE *file);

#include "functions.c"

#endif // FUNCTIONS_
