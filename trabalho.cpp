/*
Trabalho Prático - Algoritmos e Programação II (T05, 2020).

Programador: Gabriel Cardoso dos Santos Herculino.

Objetivo: Praticar/aplicar o conceito de REGISTROS e entender as diversas 
características de algoritmos de ordenação, assim como implementá-los.

Descrição: A corretora de valores D$nD$n precisa com frequência ordenar os dados de seus
clientes de acordo com algum critério. Você tem como tarefa implementar um programa que 
permita consultar os dados de um cliente, realizar transferências entre duas contas,
listar os dados dos clientes ordenados pelo seu saldo e listar os clientes ordenados
pelo nome de forma decrescente.
*/

// Bibliotecas Utilizadas
#include <stdio.h>
#include <string.h>

// Constante Definida
#define MAX 500

// Definição do registro utilizado
struct Cliente {
    char nome[50];
    int num_conta;
    float saldo;
};

// Definição das Funções utilizadas
void consultaCliente(int nCadastros, Cliente dados[]);
void realizaTransferencia(int nCadastros, Cliente dados[]);
void listaPorSaldo(int nCadastros, Cliente dados[]);
void listaPorNome(int nCadastros, Cliente dados[]);
void ordenaSaldo(int n, Cliente vetor[]);
void ordenaNomes(int n, Cliente vetor[]);
void imprimeDados(int tamanho, Cliente dados[]);

// Função Principal
int main(void) {
    
    // Leitura da quantidade de cadastros que serão realizados (menor ou igual a 500)
    int num_cadastros, leituraRealizada = 0;

    while (leituraRealizada == 0) {
        printf("Quantos Clientes você deseja cadastrar na base de dados? ");
        scanf("%d", &num_cadastros);
        if(num_cadastros > 0 && num_cadastros <= MAX)
            leituraRealizada = 1;
            
        else if(num_cadastros == -404) {
            printf("Erro de execução! A quantidade deve ser um número inteiro positivo.\n");
            return -1;
        }
        else {
            printf("Quantidade de clientes inválidas (0 < quantidade <= 500).\n");  
            num_cadastros = -404; 
        }
    }

    // Leitura dos dados dos clientes
    int i, j, repeticoes, erro = 0;
    Cliente dados[MAX];
    
    for(i = 0; i < num_cadastros; i++){
        
        repeticoes = 0;
        printf("\nNome do Cliente %d: ", i+1);
        scanf(" %[^\n]", dados[i].nome); 
        
        printf("Número da conta de %s: ", dados[i].nome);
        scanf("%d", &dados[i].num_conta);

        printf("Saldo da conta de %s: ", dados[i].nome);
        scanf("%f", &dados[i].saldo);

        // Verificação de existência de números de contas repetidos
        for (j = 0; j < i+1; j++) {
            if (dados[i].num_conta == dados[j].num_conta) {
                repeticoes++;
                if(repeticoes > 1)
                    erro = 1;
            }
            if (dados[i].num_conta > 99999)
                erro = 2;
        }
    }

    // Se houver números de contas repetidas, encerrar programa após terminar as leituras
    if (erro == 1) {
        printf("Não podem existir clientes com número de conta iguais!\nPrograma finalizado!\n");
        return -1;
    }
    
    // Ou então, se houver número de contas com mais de 5 digitos, encerrar programa após terminar as leituras
    else if(erro == 2) {
        printf("O número da conta dos clientes deve ser um inteiro positivo de até 5 digitos!\nPrograma finalizado!\n");
        return -1;
    }

    // Menu de interação com o usuário
    char escolha;
    int finalizar = 0;
    while(finalizar == 0) {
        printf("\n    - 1. Consultar dados de um cliente\n");
        printf("    - 2. Transferência de valor entre contas\n");
        printf("    - 3. Listagem de contas em ordem crescente de saldo\n");
        printf("    - 4. Listagem dos clientes em ordem alfabética\n");
        printf("    - 5. Finalizar programa\n");
        scanf(" %c", &escolha);

        switch (escolha){
            // Consultar dados de um cliente
            case '1':
                consultaCliente(num_cadastros, dados);
                break;
            
            // Realizar transferência entre contas
            case '2':
                realizaTransferencia(num_cadastros, dados);
                break;

            // Listar contas pelo saldo em ordem crescente
            case '3':
                listaPorSaldo(num_cadastros, dados);
                break;

            // Listar clientes pelo nome em ordem decrescente
            case '4':
                listaPorNome(num_cadastros, dados);
                break;

            // Finalizar programa
            case '5':
                printf("   - Programa finalizado!\n");
                finalizar = 1;
                break;

            // Opção não reconhecida
            default:
                printf("   - Opção inválida\n");
                break;
        }
    }
    return 0;
}

// Função que realiza a consulta de dados de um cliente
void consultaCliente(int nCadastros, Cliente dados[]) {
    
    int i = 0, encontrou = 0, contaBuscada, pos;

    printf("   - Informe o número da conta do Cliente:\n");
    scanf("%d", &contaBuscada);

    while (i < nCadastros){
        if(dados[i].num_conta == contaBuscada) {
            encontrou++;
            pos = i;
            if(encontrou > 1) {
                break;
            }
        }
        i++;
    }
    if(encontrou == 0)
        printf("Cliente não encontrado!\n");
    else if(encontrou == 1)
        printf("Nome: %-30s || Conta: %5d || Saldo: %10.2f\n", dados[pos].nome, dados[pos].num_conta, dados[pos].saldo);
    else
        printf("Erro! Existe mais de uma conta com esse número.\n");
}

// Função que realiza a tranferência de um valor entre duas contas
void realizaTransferencia(int nCadastros, Cliente dados[]) {
    
    int origem, posicaoOrigem = -1, destino, posicaoDestino = -1;
    float valor;
    printf("   - Digite o número da conta de origem, conta de destino e valor da transferênca (nesta ordem).\n");
    scanf("%d %d %f", &origem, &destino, &valor);

    // Encontrar posições das contas no vetor
    int i = 0;
    while ((i < nCadastros) && (posicaoOrigem == -1 || posicaoDestino == -1)){
        if(dados[i].num_conta == origem) {
            posicaoOrigem = i;
        }
            
        else if(dados[i].num_conta == destino) {
            posicaoDestino = i;
        }
        i++;
    }

    // Realizar operação com o valor nas posições encontradas
    if((posicaoOrigem != -1) && (posicaoDestino != -1)) {
        if(dados[posicaoOrigem].saldo >= valor) {
            dados[posicaoOrigem].saldo -= valor;
            dados[posicaoDestino].saldo += valor;
        } else
            printf("Saldo insuficiente para completar a transferência.\n");
    } else
        printf("Verifique se o número das contas está correto e tente novamente.\n");
}

// Função que lista os clientes ordenados pelo saldo de forma crescente
void listaPorSaldo(int nCadastros, Cliente dados[]) {
    ordenaSaldo(nCadastros, dados);
    imprimeDados(nCadastros, dados);
}

// Função que lista os clientes ordenados pelo nome de forma decrescente
void listaPorNome(int nCadastros, Cliente dados[]) {
    ordenaNomes(nCadastros, dados);
    imprimeDados(nCadastros, dados);
}

// Função que ordena os Clientes pelo saldo utilizando o algoritmo Insertion Sort
void ordenaSaldo(int n, Cliente vetor[]) {  
    int i, j, comparacoes = 0, trocas = 0;
    Cliente x;
    for (i = 1; i < n; i++) {
        x = vetor[i];
        j = i - 1; 
        while (j >= 0 && vetor[j].saldo > x.saldo) {  
            comparacoes++;
            vetor[j + 1] = vetor[j];  
            j = j - 1;  
        }  
        vetor[j + 1] = x;  
        trocas++;
    }
    printf("Comparações = %d, Trocas =   %d\n", comparacoes, trocas);
}

// Função que ordena os clientes pelo nome utilizando o algoritmo Selection Sort
void ordenaNomes(int n, Cliente vetor[]) {
    Cliente aux;
    int i, j, min, comp, comparacoes = 0, trocas = 0;
    for(i = 0; i < n - 1; i++) {
        min = i;
        for(j = i+1; j < n; j++) {
            comp = strcmp(vetor[j].nome, vetor[min].nome);
            comparacoes++;
            if (comp < 0)
                min = j;
        }
        // Troca menor valor encontrado para a menor posição do vetor atual
        aux = vetor[i];
        vetor[i] = vetor[min];
        vetor[min] = aux;
        trocas++;
    }
    printf("Comparações = %d, Trocas =   %d\n", comparacoes, trocas);
}

void imprimeDados(int tamanho, Cliente dados[]) {
    printf("\n=============================================================\n");
    printf("||%7s Nome %19s|| Conta ||     Saldo    ||\n", "", "");
    for(int i = 0; i < tamanho; i++){
        printf("|| %-30s || %5d || %10.2f   ||\n", dados[i].nome, dados[i].num_conta, dados[i].saldo);
    }
    printf("=============================================================\n");
}