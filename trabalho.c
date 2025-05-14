// Matricula: 2023123456 - João da Silva - joao@email.com
// Contribuição: Criou as funções para empilhar e desempilhar os alunos

// Matricula: 2023543210 - Maria Oliveira - maria@email.com
// Contribuição: Fez a função de busca e ajudou com os testes

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura para guardar as informações de um aluno
typedef struct {
    int matricula;
    float notaG1;
    float notaG2;
    float media;
} Aluno;

// Estrutura da pilha
typedef struct {
    Aluno *itens;   // Vetor com os alunos
    int topo;       // Índice do topo da pilha
    int capacidade; // Tamanho máximo da pilha
} Pilha;

// Funções da pilha
Pilha* criarPilha(int tamanho);
bool pilhaVazia(Pilha *p);
bool empilhar(Pilha *p, Aluno aluno);
bool desempilhar(Pilha *p, Aluno *aluno);
void liberarPilha(Pilha *p);
void buscarPorMatricula(Pilha *p, int matricula);
void mostrarAluno(Aluno aluno);
void cadastrarAluno(Pilha *p);

int main() {
    int tamanho, opcao, matriculaBusca;
    Pilha *pilha;
    Aluno alunoRemovido;

    printf("Digite o tamanho máximo da pilha de alunos: ");
    scanf("%d", &tamanho);

    pilha = criarPilha(tamanho);

    if (pilha == NULL) {
        printf("Erro ao criar a pilha.\n");
        return 1;
    }

    do {
        printf("\n--- MENU ---\n");
        printf("1. Cadastrar aluno\n");
        printf("2. Remover aluno\n");
        printf("3. Verificar se a pilha está vazia\n");
        printf("4. Buscar aluno por matrícula\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarAluno(pilha);
                break;
            case 2:
                if (desempilhar(pilha, &alunoRemovido)) {
                    printf("\nAluno removido:\n");
                    mostrarAluno(alunoRemovido);
                } else {
                    printf("A pilha está vazia.\n");
                }
                break;
            case 3:
                if (pilhaVazia(pilha)) {
                    printf("A pilha está vazia.\n");
                } else {
                    printf("A pilha tem %d aluno(s).\n", pilha->topo + 1);
                }
                break;
            case 4:
                printf("Digite a matrícula do aluno: ");
                scanf("%d", &matriculaBusca);
                buscarPorMatricula(pilha, matriculaBusca);
                break;
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 5);

    liberarPilha(pilha);
    return 0;
}

// Cria a pilha e aloca memória
Pilha* criarPilha(int tamanho) {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) return NULL;

    p->itens = (Aluno*) malloc(tamanho * sizeof(Aluno));
    if (p->itens == NULL) {
        free(p);
        return NULL;
    }

    p->topo = -1;
    p->capacidade = tamanho;

    return p;
}

// Verifica se a pilha está vazia
bool pilhaVazia(Pilha *p) {
    return (p->topo == -1);
}

// Empilha um aluno
bool empilhar(Pilha *p, Aluno aluno) {
    if (p->topo == p->capacidade - 1) {
        printf("A pilha está cheia.\n");
        return false;
    }

    p->topo++;
    p->itens[p->topo] = aluno;
    return true;
}

// Desempilha um aluno
bool desempilhar(Pilha *p, Aluno *aluno) {
    if (pilhaVazia(p)) {
        return false;
    }

    *aluno = p->itens[p->topo];
    p->topo--;
    return true;
}

// Mostra os dados de um aluno
void mostrarAluno(Aluno aluno) {
    printf("Matrícula: %d\n", aluno.matricula);
    printf("Nota G1: %.2f\n", aluno.notaG1);
    printf("Nota G2: %.2f\n", aluno.notaG2);
    printf("Média: %.2f\n", aluno.media);
}

// Cadastra um novo aluno e empilha
void cadastrarAluno(Pilha *p) {
    Aluno novo;

    printf("\n--- Cadastro de Aluno ---\n");
    printf("Matrícula: ");
    scanf("%d", &novo.matricula);

    printf("Nota G1: ");
    scanf("%f", &novo.notaG1);

    printf("Nota G2: ");
    scanf("%f", &novo.notaG2);

    novo.media = (novo.notaG1 + novo.notaG2) / 2;

    if (empilhar(p, novo)) {
        printf("Aluno cadastrado com sucesso!\n");
    }
}

// Libera a memória usada pela pilha
void liberarPilha(Pilha *p) {
    free(p->itens);
    free(p);
}

// Busca um aluno por matrícula respeitando a ordem LIFO
void buscarPorMatricula(Pilha *p, int matricula) {
    Pilha pilhaAux;
    pilhaAux.itens = (Aluno*) malloc(p->capacidade * sizeof(Aluno));
    pilhaAux.topo = -1;
    pilhaAux.capacidade = p->capacidade;

    Aluno temp;
    bool achou = false;

    while (!pilhaVazia(p)) {
        desempilhar(p, &temp);
        if (temp.matricula == matricula && !achou) {
            printf("\nAluno encontrado:\n");
            mostrarAluno(temp);
            achou = true;
        }
        empilhar(&pilhaAux, temp);
    }

    while (!pilhaVazia(&pilhaAux)) {
        desempilhar(&pilhaAux, &temp);
        empilhar(p, temp);
    }

    if (!achou) {
        printf("Aluno não encontrado.\n");
    }

    free(pilhaAux.itens);
}
