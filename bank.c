#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_CLIENTES 100
#define MAX_CONTAS 100

typedef struct {
    int numeroConta;
    float saldo;
} Conta;

typedef struct {
    int numeroCliente;
    char nome[50];
    Conta conta;
} Cliente;

Cliente clientes[MAX_CLIENTES];
int numClientes = 0;

void cadastrarCliente() {
    if (numClientes == MAX_CLIENTES) {
        printf("Limite de clientes atingido.\n");
        return;
    }

    Cliente novoCliente;

    printf("Digite o número do cliente: ");
    scanf("%d", &novoCliente.numeroCliente);

    printf("Digite o nome do cliente: ");
    scanf("%s", novoCliente.nome);

    printf("Digite o número da conta: ");
    scanf("%d", &novoCliente.conta.numeroConta);

    novoCliente.conta.saldo = 0.0;

    clientes[numClientes] = novoCliente;
    numClientes++;

    printf("Cliente cadastrado com sucesso.\n");
}
