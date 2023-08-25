#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_CLIENTES 100
#define MAX_CONTAS 100
#define MAX_TRANSACOES 100

typedef struct {
    char tipo;   // 'D' para depósito, 'S' para saque
    float valor; // Valor da transação
} Transacao;

typedef struct {
    int numeroConta;
    float saldo;
    Transacao historico[MAX_TRANSACOES]; // Array de transações
    int numTransacoes; // Número de transações registradas
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

Cliente* buscarCliente(int numeroCliente) {
    int i;
    for (i = 0; i < numClientes; i++) {
        if (clientes[i].numeroCliente == numeroCliente) {
            return &clientes[i];
        }
    }
    return NULL;
}

void cadastrarContaCliente() {
    int numeroCliente;
    printf("Digite o número do cliente: ");
    scanf("%d", &numeroCliente);

    Cliente* cliente = buscarCliente(numeroCliente);

    if (cliente == NULL) {
        printf("Cliente não encontrado.\n");
        return;
    }

    printf("Digite o número da conta: ");
    scanf("%d", &cliente->conta.numeroConta);

    cliente->conta.saldo = 0.0;

    printf("Conta cadastrada com sucesso.\n");
}

void realizarSaque() {
    int numeroCliente;
    printf("Digite o número do cliente: ");
    scanf("%d", &numeroCliente);
    
    Cliente* cliente = buscarCliente(numeroCliente);

    if (cliente == NULL) {
        printf("Cliente não encontrado.\n");
        return;
    }

    float valor;
    printf("Digite o valor do saque: ");
    scanf("%f", &valor);

    if (cliente->conta.saldo < valor) {
        printf("Saldo insuficiente.\n");
        return;
    }

    // Registrar a transação no histórico
    if (cliente->conta.numTransacoes < MAX_TRANSACOES) {
        cliente->conta.historico[cliente->conta.numTransacoes].tipo = 'S';
        cliente->conta.historico[cliente->conta.numTransacoes].valor = valor;
        cliente->conta.numTransacoes++;
    } else {
        printf("Número máximo de transações atingido.\n");
        return;
    }

    cliente->conta.saldo -= valor;
    printf("Saque realizado com sucesso. Saldo atual: %.2f\n", cliente->conta.saldo);
}


void realizarDeposito() {
    int numeroCliente;
    printf("Digite o numero do cliente: ");
    scanf("%d", &numeroCliente);

    Cliente* cliente = buscarCliente(numeroCliente);

    if (cliente == NULL) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    float valor;
    printf("Digite o valor do deposito: ");
    scanf("%f", &valor);

    cliente->conta.saldo += valor;

    // Registrar a transação no histórico
    if (cliente->conta.numTransacoes < MAX_TRANSACOES) {
        cliente->conta.historico[cliente->conta.numTransacoes].tipo = 'D';
        cliente->conta.historico[cliente->conta.numTransacoes].valor = valor;
        cliente->conta.numTransacoes++;
    } else {
        printf("Número máximo de transações atingido.\n");
        return;
    }

    printf("Deposito realizado com sucesso. Saldo atual: %.2f\n", cliente->conta.saldo);
}

// Função para registrar uma transação na conta
void registrarTransacao(Conta *conta, Transacao transacao) {
    if (conta->numTransacoes < MAX_TRANSACOES) {
        conta->historico[conta->numTransacoes] = transacao;
        conta->numTransacoes++;
    } else {
        printf("Limite de transações atingido.\n");
    }
}

void consultarSaldo() {
    int numeroCliente;
    printf("Digite o numero do cliente: ");
    scanf("%d", &numeroCliente);

    Cliente* cliente = buscarCliente(numeroCliente);

    if (cliente == NULL) {
       

 printf("Cliente nao encontrado.\n");
        return;
    }

    printf("Saldo atual: %.2f\n", cliente->conta.saldo);
}
void listarClientes() {
    if (numClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    int i;
    for (i = 0; i < numClientes; i++) {
        printf("Numero do cliente: %d\n", clientes[i].numeroCliente);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Número da conta: %d\n", clientes[i].conta.numeroConta);
        printf("Saldo: %.2f\n\n", clientes[i].conta.saldo);
    }
}

void exibirExtrato() {
    int numeroCliente;
    printf("Digite o numero do cliente: ");
    scanf("%d", &numeroCliente);

    Cliente* cliente = buscarCliente(numeroCliente);

    if (cliente == NULL) {
        printf("Cliente não encontrado.\n");
        return;
    }

    printf("Extrato da conta do cliente %d:\n", cliente->numeroCliente);
    printf("Saldo inicial: %.2f\n", cliente->conta.saldo);
    
    if (cliente->conta.numTransacoes == 0) {
        printf("Nenhuma operacao registrada.\n");
    } else {
        printf("Operacoes realizadas:\n");

        for (int i = 0; i < cliente->conta.numTransacoes; i++) {
            printf("Operacao %d: ", i);
            if (cliente->conta.historico[i].tipo == 'D') {
                printf("Deposito de %.2f\n", cliente->conta.historico[i].valor);
            } else if (cliente->conta.historico[i].tipo == 'S') {
                printf("Saque de %.2f\n", cliente->conta.historico[i].valor);
            }
        }
    }
}



int main() {
	setlocale(LC_ALL, "portuguese");
    int opcao;

    do {
    	system("cls");
        printf("======== BancoShow ========\n");
        printf("\n1. Cadastrar cliente");
        printf("\n2. Cadastrar conta de cliente");
        printf("\n3. Realizar saque");
        printf("\n4. Realizar deposito");
        printf("\n5. Consultar saldo");
        printf("\n6. Listar clientes");
        printf("\n7. Exibir extrato");
        printf("\n8. Sair\n");
        printf("\nDigite sua opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                system("pause");
                break;
            case 2:
                cadastrarContaCliente();
                system("pause");
                break;
            case 3:
                realizarSaque();
                system("pause");
                break;
            case 4:
                realizarDeposito();
                system("pause");
                break;
            case 5:
                consultarSaldo();
                system("pause");
                break;
            case 6:
                listarClientes();
                system("pause");
                break;
            case 7:
                exibirExtrato();
                system("pause");
                break;
            case 8:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
                
        }

        printf("\n");
    } while (opcao != 8);

    return 0;
}
