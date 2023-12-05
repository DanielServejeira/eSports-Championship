#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>

void numeroDeJogadores(FILE *jogadores, int *n){

    if (jogadores != NULL) {
        fseek(jogadores, 0, SEEK_END);
        if (ftell(jogadores) != 0){
            *n = ftell(jogadores)/sizeof(JOGADOR);
            // Se o arquivo existir e não estiver vazio, retorna quantos jogadores há
        } else *n = 1; // Se estiver vazio, inicia n como 1
    } else {
        jogadores = fopen("banco.dat", "wb");
        fclose(jogadores);
        fopen("banco.dat", "rb");
        *n = 1; // Cria o arquivo e inicia n como 1
    }
    printf("\nn> %d", *n);
    fclose(jogadores);
}

int verificarDia(JOGADOR player){
    int
    ano = player.nascimento.ano,
    mes = player.nascimento.mes,
    dia = player.nascimento.dia;
    if (dia < 1) return 0;
    switch (mes){
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if (dia > 31) return 0;
    case 2:
        if (ano % 4 == 0){
            if (dia > 29) return 0;
        } else if (dia > 28) return 0;
    case 4: case 6: case 9: case 11:
        if (dia > 30) return 0;
    } return 1;
}

int verificarCPF(JOGADOR *player){
    if (strlen(player->cpf) != 11) return 0;
    for (int i = 0; i < strlen(player->cpf); i++){
        if (player->cpf[i] > '9' || player->cpf[i] < '0') return 0;
    } return 1;
}

int verificarRanking(JOGADOR player, FILE *jogadores, int n){
    int ranking = player.ranking, i;
    if (ranking < 0) return 0;
    JOGADOR lista[n];
    fread(lista, sizeof(lista), 1, jogadores);
    for (i = 0; i < n; i++){
        if (lista[i].ranking == ranking){
            printf("\nRanking já ocupado, selecionar outro\n");
            return 0;
        }
    } return 1;
}

void escreverJogador(FILE *jogadores, int n) {
    if(jogadores) {
        JOGADOR np, *novoJogador = &np;

        printf("\n===== INSERINDO NOVO JOGADOR =====\n");

        // DADOS DO JOGADOR
        printf("Nome do jogador: ");
        fflush(stdin);
        gets(novoJogador->nome);
        do{printf("Ano de nascimento: ");
        scanf("%d", &novoJogador->nascimento.ano);}while((novoJogador->nascimento.ano) < 1923 || (novoJogador->nascimento.ano) > 2013);
        do{printf("Mês de nascimento: ");
        scanf("%d", &novoJogador->nascimento.mes);}while(novoJogador->nascimento.mes < 1 || novoJogador->nascimento.mes > 12);
        do{printf("Dia de nascimento: ");
        scanf("%d", &novoJogador->nascimento.dia);}while(verificarDia(np) == 0);
        do{printf("CPF do jogador (somente os 11 dígitos): ");
        fflush(stdin);
        gets(novoJogador->cpf);}while(verificarCPF(novoJogador) == 0);
        do{printf("Gênero do jogador [M/F]: ");
        scanf("%c", &novoJogador->genero);}while(novoJogador->genero != 'M' && novoJogador->genero != 'F');
        printf("Estado Civil\n[1] Solteiro\n[2] Casado\n[3] Divorciado\n[4] Viúvo\n");
        do{printf(">>> ");
        scanf("%d", &novoJogador->estadoCivil);}while(novoJogador->estadoCivil < 1 || novoJogador->estadoCivil > 4);

        // EQUIPE DO JOGADOR
        printf("\n===== Equipe =====\n");
        printf("Nome da equipe: ");
        fflush(stdin);
        gets(novoJogador->equipe.nome);
        printf("Nickname da equipe: ");
        gets(novoJogador->equipe.nickname);
        do{printf("Seguidores da equipe: ");
        scanf("%d", &novoJogador->equipe.seguidores);}while(novoJogador->equipe.seguidores < 0);

        // MAIS INFORMAÇÕES
        printf("\n===== Outras informações =====\n");
        printf("Patrocinador do jogador: ");
        fflush(stdin);
        gets(novoJogador->patrocinador);
        printf("Nickname do jogador: ");
        gets(novoJogador->nickname);
        do{printf("Seguidores do jogador: ");
        scanf("%d", &novoJogador->seguidores);}while(novoJogador->seguidores < 0);

        // HARDWARE
        printf("\n===== Hardware =====\n");
        printf("Modelo do computador do jogador: ");
        fflush(stdin);
        gets(novoJogador->equip.modelo);
        printf("Processador da máquina do jogador: ");
        gets(novoJogador->equip.processador);
        printf("Placa gráfica da máquina do jogador: ");
        gets(novoJogador->equip.placaGrafica);
        do{printf("Memória RAM da máquina do jogador (GB): ");
        scanf("%d", &novoJogador->equip.memRAM);}while(novoJogador->equip.memRAM < 0);

        // STATUS DO CAMPEONATO
        printf("\n===== Status do campeonato =====\n");
        do{printf("Vitórias do jogador: ");
        scanf("%d", &novoJogador->status.vitorias);}while(novoJogador->status.vitorias < 0);
        do{printf("Derrotas do jogador: ");
        scanf("%d", &novoJogador->status.derrotas);}while(novoJogador->status.derrotas < 0);
        do{printf("Empates do jogador: ");
        scanf("%d", &novoJogador->status.empates);}while(novoJogador->status.empates < 0);
        novoJogador->status.pontuacao = (novoJogador->status.vitorias)*3 + (novoJogador->status.empates);

        // CONQUISTAS
        printf("\n===== Conquistas do jogador =====\n");
        do{printf("Quantidade de títulos do jogador: ");
        scanf("%d", &novoJogador->titulos);}while(novoJogador->titulos < 0);
        do{printf("Posição do jogador no ranking: ");
        scanf("%d", &novoJogador->ranking);}while(verificarRanking(np, jogadores, n) == 0);

        fwrite(novoJogador, sizeof(JOGADOR), 1, jogadores);
        fclose(jogadores);
    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void calcularPontuacao(JOGADOR *player){
    player->status.pontuacao = (player->status.vitorias) * 3 + player->status.empates;
    return;
}

void lerJogador(JOGADOR lista[], int index) {
        // DADOS DO JOGADOR
        printf("\n===== JOGADOR =====\n");
        printf("Nome do jogador: %s\n", lista[index].nome);
        printf("Data de nascimento: %d/%d/%d\n",
            lista[index].nascimento.dia,
            lista[index].nascimento.mes,
            lista[index].nascimento.ano);
        printf("CPF do jogador: %s\n", lista[index].cpf);
        printf("Gênero do jogador [M/F]: %c\n", lista[index].genero);
        printf("Estado Civil: ");
        switch (lista[index].estadoCivil){
        case 1:
            printf("Solteiro\n");
            break;
        case 2:
            printf("Casado\n");
            break;
        case 3:
            printf("Divorciado\n");
            break;
        case 4:
            printf("Viúvo\n");
            break;
        default:
            printf("N/A\n");
            break;
        }

        // EQUIPE DO JOGADOR
        printf("\n===== Equipe =====\n");
        printf("Nome da equipe: %s\n", lista[index].equipe.nome);
        printf("Nickname da equipe: %s\n", lista[index].equipe.nickname);
        printf("Seguidores da equipe: %d\n", lista[index].equipe.seguidores);

        // MAIS INFORMAÇÕES
        printf("\n===== Outras informações =====\n");
        printf("Patrocinador do jogador: %s\n", lista[index].patrocinador);
        printf("Nickname do jogador: %s\n", lista[index].nickname);
        printf("Seguidores do jogador: %d\n", lista[index].seguidores);

        // HARDWARE
        printf("\n===== Hardware =====\n");
        printf("Modelo do computador do jogador: %s\n", lista[index].equip.modelo);
        printf("Processador da máquina do jogador: %s\n", lista[index].equip.processador);
        printf("Placa gráfica da máquina do jogador: %s\n", lista[index].equip.placaGrafica);
        printf("Memória RAM da máquina do jogador (GB): %d\n", lista[index].equip.memRAM);

        // STATUS DO CAMPEONATO
        printf("\n===== Status do campeonato =====\n");
        calcularPontuacao(&lista[index]);
        printf("Pontuação total do jogador: %d\n", lista[index].status.pontuacao);
        printf("Vitórias do jogador: %d\n", lista[index].status.vitorias);
        printf("Derrotas do jogador: %d\n", lista[index].status.derrotas);
        printf("Empates do jogador: %d\n", lista[index].status.empates);

        // CONQUISTAS
        printf("\n===== Conquistas do jogador =====\n");
        printf("Quantidade de títulos do jogador: %d\n", lista[index].titulos);
        printf("Posição do jogador no ranking: %d\n\n", lista[index].ranking);
    return;
}

int comparePlayersName(const void *a, const void *b) {
    return (strcmp(((const JOGADOR *)a)->nome, ((const JOGADOR *)b)->nome));
}

void listarJogadoresAlfabetica(FILE *jogadores, int n) {
    if(jogadores) {
        JOGADOR lista[n];
        int playerIndex;
        fread(lista, sizeof(lista), 1, jogadores);

        qsort(lista, n, sizeof(JOGADOR), comparePlayersName);

        printf("===== JOGADORES =====\n");
        for (int i = 0; i < sizeof(lista)/sizeof(JOGADOR); i ++){
            printf("[%d] %s\n", i+1, lista[i].nome);
        }
        printf("\n Digite o índice do jogador para fazer a leitura (0 para sair)\n>>> ");
        scanf("%d", &playerIndex);

        if (playerIndex == 0) {
            return;
        } if (playerIndex < 0 || playerIndex > n) {
            printf("Valor inválido. Considerado como 0. Retornando...\n");
            return;
        } else {
            lerJogador(lista, playerIndex-1);
        }
    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

int comparePlayersRanking(const void *a, const void *b) {
    return (((const JOGADOR *)a)->ranking - ((const JOGADOR *)b)->ranking);
}

void listarJogadoresRanking(FILE *jogadores, int n) {
    if(jogadores) {
        JOGADOR lista[n];
        int playerIndex;
        fread(lista, sizeof(lista), 1, jogadores);

        qsort(lista, n, sizeof(JOGADOR), comparePlayersRanking);

        printf("===== JOGADORES =====\n");
        for (int i = 0; i < sizeof(lista)/sizeof(JOGADOR); i ++){
            printf("[%d] %dº - %s\n", i+1, lista[i].ranking, lista[i].nickname);
        }
        printf("\n Digite o índice do jogador para fazer a leitura (0 para sair)\n>>> ");
        scanf("%d", &playerIndex);

        if (playerIndex == 0) {
            return;
        } if (playerIndex < 0 || playerIndex > n) {
            printf("Valor inválido. Considerado como 0. Retornando...\n");
            return;
        } else {
            lerJogador(lista, playerIndex-1);
        }
    }
    else perror("\tErro ao abrir o arquivo.\n\n");
    return;
}

int comparePlayersWin(const void *a, const void *b) {
    return (((const JOGADOR *)a)->status.vitorias - ((const JOGADOR *)b)->status.vitorias);
}

void listarJogadoresVitorias(FILE *jogadores, int n) {
    if(jogadores) {
        JOGADOR lista[n];
        int playerIndex;
        fread(lista, sizeof(lista), 1, jogadores);

        qsort(lista, n, sizeof(JOGADOR), comparePlayersWin);

        printf("===== JOGADORES =====\n");
        for (int i = 0; i < sizeof(lista)/sizeof(JOGADOR); i ++){
            printf("[%d] %d vitórias - %s\n", i+1, lista[i].status.vitorias, lista[i].nickname);
        }
        printf("\n Digite o índice do jogador para fazer a leitura (0 para sair)\n>>> ");
        scanf("%d", &playerIndex);

        if (playerIndex == 0) {
            return;
        } if (playerIndex < 0 || playerIndex > n) {
            printf("Valor inválido. Considerado como 0. Retornando...\n");
            return;
        } else {
            lerJogador(lista, playerIndex-1);
        }

    }
    else perror("\tErro ao abrir o arquivo.\n\n");
}

void alterarJogador(FILE *jogadores, int *n) {
    if(jogadores) {
        JOGADOR lista[*n];
        int playerIndex, toChange, a;
        fread(lista, sizeof(lista), 1, jogadores);

        qsort(lista, *n, sizeof(JOGADOR), comparePlayersName);

        printf("===== JOGADORES =====\n");
        for (int i = 0; i < sizeof(lista)/sizeof(JOGADOR); i ++){
            printf("[%d] %s\n", i+1, lista[i].nickname);
        }
        printf("\n=====\n Digite o índice do jogador para fazer a alteração de dados (0 para sair)\n>>> ");
        scanf("%d", &playerIndex);

        if (playerIndex == 0) {
            return;
        } if (playerIndex < 0 || playerIndex > *n) {
            printf("Valor inválido. Considerado como 0. Retornando...\n");
            return;
        } else {
            playerIndex--;
            lerJogador(lista, playerIndex);
            printf("=====\nDigite a informação que deseja alterar (0 para cancelar):\n");
            printf("[1] Nome\n[2] Dia de nascimento\n[3] Mês de nascimento\n[4] Ano de nascimento\n[5] CPF\n");
            printf("[6] Gênero\n[7] Estado Civil\n[8] Nome da equipe\n[9] Nickname da equipe\n[10] Seguidores da equipe\n");
            printf("[11] Patrocinadora\n[12] Nickname do jogador\n[13] Seguidores do jogador\n[14] Modelo do computador\n[15] Processador do computador\n");
            printf("[16] Placa gráfica do computador\n[17] Memória RAM do computador\n[18] Vitórias no campeonato\n[19] Derrotas no campeonato\n[20] Empates no campeonato\n");
            printf("[21] Títulos do jogador\n[22] Posição no ranking mundial\n[23] Deletar jogador\n>>> ");
            scanf("%d", &toChange);
            printf(">>> ");

            switch (toChange){
                case 1:
                    fflush(stdin);
                    gets(lista[playerIndex].nome);
                    break;
                case 2:
                    do{scanf("%d", &lista[playerIndex].nascimento.dia);}while(verificarDia(lista[playerIndex]) == 0);
                    break;
                case 3:
                    do{scanf("%d", &lista[playerIndex].nascimento.mes);}while(lista[playerIndex].nascimento.mes < 1 || lista[playerIndex].nascimento.mes > 12);
                    break;
                case 4:
                    do{scanf("%d", &lista[playerIndex].nascimento.ano);}while((lista[playerIndex].nascimento.ano) < 1923 || (lista[playerIndex].nascimento.ano) > 2013);
                    break;
                case 5:
                    do{fflush(stdin);
                    gets(lista[playerIndex].cpf);}while(verificarCPF(&lista[playerIndex]) == 0);
                    break;
                case 6:
                    do{fflush(stdin);
                    scanf("%c", &lista[playerIndex].genero);}while(lista[playerIndex].genero != 'M' && lista[playerIndex].genero != 'F');
                    break;
                case 7:
                    printf("[1] Solteiro\n[2] Casado\n[3] Divorciado\n[4] Viúvo\n>>> ");
                    do{scanf("%d", &lista[playerIndex].estadoCivil);}while(lista[playerIndex].estadoCivil < 1 || lista[playerIndex].estadoCivil > 4);
                    break;
                case 8:
                    fflush(stdin);
                    gets(lista[playerIndex].equipe.nome);
                    break;
                case 9:
                    fflush(stdin);
                    gets(lista[playerIndex].equipe.nickname);
                    break;
                case 10:
                    do{scanf("%d", &lista[playerIndex].equipe.seguidores);}while(lista[playerIndex].equipe.seguidores < 0);
                    break;
                case 11:
                    fflush(stdin);
                    gets(lista[playerIndex].patrocinador);
                    break;
                case 12:
                    fflush(stdin);
                    gets(lista[playerIndex].nickname);
                    break;
                case 13:
                    do{scanf("%d", &lista[playerIndex].seguidores);}while(lista[playerIndex].seguidores < 0);
                    break;
                case 14:
                    fflush(stdin);
                    gets(lista[playerIndex].equip.modelo);
                    break;
                case 15:
                    fflush(stdin);
                    gets(lista[playerIndex].equip.processador);
                    break;
                case 16:
                    fflush(stdin);
                    gets(lista[playerIndex].equip.placaGrafica);
                    break;
                case 17:
                    do{scanf("%d", &lista[playerIndex].equip.memRAM);}while(lista[playerIndex].equip.memRAM < 0);
                    break;
                case 18:
                    do{scanf("%d", &lista[playerIndex].status.vitorias);}while(lista[playerIndex].status.vitorias < 0);
                    calcularPontuacao(&lista[playerIndex]);
                    break;
                case 19:
                    do{scanf("%d", &lista[playerIndex].status.derrotas);}while(lista[playerIndex].status.derrotas < 0);
                    break;
                case 20:
                    do{scanf("%d", &lista[playerIndex].status.empates);}while(lista[playerIndex].status.empates < 0);
                    calcularPontuacao(&lista[playerIndex]);
                    break;
                case 21:
                    do{scanf("%d", &lista[playerIndex].titulos);}while(lista[playerIndex].titulos < 0);
                    break;
                case 22:
                    do{scanf("%d", &lista[playerIndex].ranking);}while(verificarRanking(lista[playerIndex], jogadores, *n) == 0);
                    break;
                case 23:
                    printf("Tem certeza?\n[1] Deletar jogador\n[2] Cancelar operação\n");
                    do{printf(">>> ");
                    scanf("%d", &a);} while(a != 1 && a != 2);
                    if (a == 1){
                        a = *n;
                        JOGADOR temp = lista[a-1];
                        lista[a-1] = lista[playerIndex];
                        lista[playerIndex] = temp;
                        (*n)--;
                        printf("Jogador deletado", *n);
                        break;
                    } else {
                        printf("Operação cancelada! Retornando...\n");
                        return;
                    }

                case 0:
                    return;
                default:
                    printf("Valor inválido. Considerado como 0. Retornando...\n");
                    return;
            }

            fclose(jogadores);
            jogadores = fopen("banco.dat", "wb");
            fwrite(lista, sizeof(JOGADOR), *n, jogadores);
            fclose(jogadores);
        }
    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void inserirResultado(FILE *jogadores, int n) {
    if(jogadores) {
        JOGADOR lista[n];
        int playerIndex, menuPontuacao;
        fread(lista, sizeof(lista), 1, jogadores);

        qsort(lista, n, sizeof(JOGADOR), comparePlayersName);

        printf("===== JOGADORES =====\n");
        for (int i = 0; i < sizeof(lista)/sizeof(JOGADOR); i ++){
            printf("[%d] %s\n", i+1, lista[i].nickname);
        }

        printf("\nInsira o índice do jogador desejado para alterar sua pontuação (0 para voltar):\n");
        printf(">>> ");
        scanf("%d", &playerIndex);
        getchar();
        playerIndex--;

        if(playerIndex == -1 || playerIndex > n-1) {
            printf("\n");
            return;
        }
        if(playerIndex >= 0) {
            system("cls");
            calcularPontuacao(&lista[playerIndex]);
            printf("\nJogador escolhido: %s", lista[playerIndex].nickname);
            printf("\nPontuação atual: %d", lista[playerIndex].status.pontuacao);
            printf("\n\nInserir \n"
                   "[1] Vitória\n"
                   "[2] Empate\n"
                   "[3] Derrota\n>>> ");
            scanf("%d", &menuPontuacao);

            switch(menuPontuacao) {
                case 1:
                    lista[playerIndex].status.vitorias += 1;
                    lista[playerIndex].status.pontuacao += 3;
                    break;
                case 2:
                    lista[playerIndex].status.empates += 1;
                    lista[playerIndex].status.pontuacao += 1;
                    break;
                case 3:
                    lista[playerIndex].status.derrotas += 1;
                    break;
                default:
                    printf("\n\tInsira um comando válido.\n\n");
                    system("Pause");
                    system("cls");
                    inserirResultado(jogadores, n);
                    break;
            }
            fclose(jogadores);
            jogadores = fopen("banco.dat", "wb");
            fwrite(lista, sizeof(JOGADOR), n, jogadores);
            fclose(jogadores);

            printf("\nPontuação alterada com sucesso.\n\n");
            system("Pause");
            system("cls");
        }
        else {
            printf("\n\tInsira um comando válido.\n\n");
            system("Pause");
            system("cls");
        }
    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

int comparePlayersPoints(const void *a, const void *b) {
    return (((const JOGADOR *)a)->status.pontuacao - ((const JOGADOR *)b)->status.pontuacao);
}

void listarClassificacao(FILE *jogadores, int n) {
    if(jogadores) {
        JOGADOR lista[n];
        int j=1;
        fread(lista, sizeof(lista), 1, jogadores);

        qsort(lista, n, sizeof(JOGADOR), comparePlayersPoints);

        printf("===== JOGADORES =====\n");
        for (int i = n-1; i >= 0 ; i --){
            printf("[%d] %d pontos - %s\n", j, lista[i].status.pontuacao, lista[i].nickname);
            printf("%d V | %d E | %d D\n", lista[i].status.vitorias, lista[i].status.empates, lista[i].status.derrotas);
            printf("---------------------\n");
            j++;
        }
    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void pontuacaoMaiorQue(FILE *jogadores, int n) {
    if(jogadores) {
        JOGADOR lista[n];
        int j=1, min;
        fread(lista, sizeof(lista), 1, jogadores);

        qsort(lista, n, sizeof(JOGADOR), comparePlayersPoints);

        printf("Pontuação mínima: ");
        scanf("%d", &min);

        printf("===== JOGADORES =====\n");
        for (int i = n-1; i >= 0 ; i --){
            if (lista[i].status.pontuacao >= min){
                printf("[%d] %d pontos - %s\n", j, lista[i].status.pontuacao, lista[i].nickname);
                printf("%d V | %d E | %d D\n", lista[i].status.vitorias, lista[i].status.empates, lista[i].status.derrotas);
                printf("---------------------\n");
            } j++;
        }
    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void pontuacaoMenorQue(FILE *file, int n) {
    if(file) {
        int i = 0, indice, j=1;
        JOGADOR jogador;

        printf("\nPontuação máxima: ");
        scanf("%d", &indice);
        printf("\n");

        if(indice < 0) {
            printf("\n\tInsira um comando válido.\n\n");
            system("Pause");
            system("cls");
            pontuacaoMenorQue(file, n);
        }

        while(indice >= 0) {
            fseek(file, 0, SEEK_SET);
            while(fread(&jogador, sizeof(JOGADOR), 1, file)) {
                j++;
                if(jogador.status.pontuacao == indice) {
                    printf("[%d] %d pontos - %s\n", j, jogador.status.pontuacao, jogador.nickname);
                    printf("%d V | %d E | %d D\n", jogador.status.vitorias, jogador.status.empates, jogador.status.derrotas);
                    printf("---------------------\n");
                }
            }
            indice--;
        }
    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void buscarJogadorNome(FILE *jogadores, int n) {
    if(jogadores) {
        JOGADOR lista[n], aux[n], ptrJog, *jogador = &ptrJog;
        fread(lista, sizeof(lista), 1, jogadores);
        char busca[50], nome[50];
        int j = 0, i, playerIndex;
        printf("Digite o nome do jogador a ser procurado: ");
        fflush(stdin);
        gets(busca);

        for (i = 0; i < n; i++){
            fseek(jogadores, i*sizeof(JOGADOR), SEEK_SET);
            fread(jogador, sizeof(JOGADOR), 1, jogadores);
            strcpy(nome, jogador->nome);
            if (strcasecmp(busca, nome) == 0){
                aux[j] = ptrJog;
                j++;
            }
        } if (j == 0){
            printf("Não há correspondências.");
            return;
        } else {
            for (i = 0; i < j; i++){
                printf("[%d] %s\n", i+1, aux[i].nickname);
            }
            printf("\nDigite o índice do jogador para ver as informações (0 para voltar)\n>>> ");
            scanf("%d", &playerIndex);
            if (playerIndex < 1 || playerIndex > j){
                printf("Valor inválido. Considerando como 0. Retornando...\n");
            } else{
                lerJogador(aux, playerIndex-1);
                return;
            }
        }
    }

    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}

void buscarJogadorRanking(FILE *file) {
    if(file) {
        JOGADOR jogador;
        int busca, verif = 1;

        printf("\nInsira um número para ver o jogador que está em seu ranking\n\n");
        scanf("%d", &busca);

        if(busca < 1) {
            printf("\nInsira um comando válido.\n\n");
            system("Pause");
            system("cls");
            buscarJogadorRanking(file);
        }

        fseek(file, 0, SEEK_SET);
        while(fread(&jogador, sizeof(JOGADOR), 1, file)) {
            if(jogador.ranking == busca) {
                printf("\nJogador encontrado.\n\n");
                printf("[%d] - %s\n\n", jogador.ranking, jogador.nickname);
                verif = 0;
                break;
            }
        }

        if(verif) {
            printf("\nJogador não encontrado.\n\n");
        }

    }
    else perror("Erro ao abrir o arquivo.\n\n");

    return;
}

void mediaDeSeguidores(FILE *jogadores, int n) {
    if(jogadores) {
        JOGADOR lista[n];
        fread(lista, sizeof(lista), 1, jogadores);
        int i, total=0;

        for (i = 0; i < n; i++){
            total += lista[i].seguidores;
        }
        double a=n/1.0, media=total/a;
        printf("Média de seguidores dos jogadores do campeonato: %.3f\n", media);
        return;

    }
    else perror("\tErro ao abrir o arquivo.\n\n");

    return;
}
