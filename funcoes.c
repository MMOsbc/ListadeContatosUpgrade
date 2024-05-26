#include <stdio.h>

#include <string.h>
#include "funcoes.h"

#include <stdbool.h>
#include <ctype.h>
// inclusão das bibliotecas



// criação da função
int validarEmail(const char *email) {
    int tamanho = strlen(email);
    int i, at = 0, ponto = 0;

    // Verifica se o primeiro caractere é uma letra
    if (!isalpha(email[0]))
        return false;

    for (i = 0; i < tamanho; i++) {
        // Verifica se o caractere é uma letra, dígito, '.', '_', '-' ou '@'
        if (!(isalnum(email[i]) || email[i] == '.' || email[i] == '_' || email[i] == '-' || email[i] == '@'))
            return false;

        if (email[i] == '@') {
            at++;
            if (at > 1) // Se houver mais de um '@', o e-mail é inválido
                return false;
        }

        if (email[i] == '.') {
            ponto++;
            if (ponto > 1) // Se houver mais de um '.', o e-mail é inválido
                return false;
        }
    }

    // Verifica se o último caractere é uma letra ou um dígito
    if (!isalnum(email[tamanho - 1]))
        return false;

    // Verifica se há pelo menos um caractere antes do '@' e depois do '.'
    if (at == 0 || ponto == 0)
        return false;

    return true;
}


void cadastrarContatos(ListaDeContatos *lt) {
    if (lt->qtd >= 255) {
        printf("A lista de contatos está cheia. Não é possível cadastrar mais contatos\n");
        return;
    }

    Contato novoContato;

    printf("Número de cadastro: ");
    scanf("%lf", &novoContato.id); // Usando %lf para ler um double

    printf("Telefone: ");
    scanf("%s", novoContato.telefone); // Lendo como uma string

    // Verificar se o número de telefone já existe na lista
    for (int i = 0; i < lt->qtd; i++) {
        if (strcmp(lt->contatos[i].telefone, novoContato.telefone) == 0) {
            printf("Este número de telefone já está cadastrado.\n");
            return;
        }
    }

    printf("Nome (até 20 caracteres): ");
    scanf("%s", novoContato.nome); // Lendo como uma string

    printf("Sobrenome (até 50 caracteres): ");
    scanf("%s", novoContato.sobrenome); // Lendo como uma string

    // Loop para solicitar e-mail até que seja inserido um formato válido
    do {
        printf("E-mail (até 30 caracteres): ");
        scanf("%s", novoContato.e_mail); // Lendo como uma string

        // Validar e-mail
        if (!validarEmail(novoContato.e_mail)) {
            printf("E-mail inválido. Por favor, insira um e-mail válido.\n");
        }
    } while (!validarEmail(novoContato.e_mail)); // Repetir até que um e-mail válido seja inserido

    lt->contatos[lt->qtd] = novoContato;
    lt->qtd++;

    printf("Contato cadastrado com sucesso!\n");
}


void listarContatos(ListaDeContatos lt) {
    if (lt.qtd == 0) {
        printf("A lista de contatos está vazia.\n");
        return;
    }

    printf("Lista de Contatos:\n");

    for (int i = 0; i < lt.qtd; i++) {
        printf("ID %d:\n", i + 1);
        printf("ID: %.0lf\n", lt.contatos[i].id); // Corrigindo para %.0lf para imprimir um double como um inteiro
        printf("Telefone: %s\n", lt.contatos[i].telefone);
        printf("Nome: %s\n", lt.contatos[i].nome);
        printf("Sobrenome: %s\n", lt.contatos[i].sobrenome);
        printf("E-mail: %s\n", lt.contatos[i].e_mail);
        printf("\n");
    }
}

void carregarContatos(ListaDeContatos*lt, const char *arquivo) {
    FILE *file = fopen(arquivo, "rb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo de contatos.\n");
        return;
    }

    fread(&(lt->qtd), sizeof(int), 1, file);

    if (lt->qtd > 255) {
        printf("Erro: O número de contatos no arquivo é maior do que o limite permitido.\n");
        fclose(file);
        return;
    }

    fread(lt->contatos, sizeof(Contato), lt->qtd, file); // Corrigindo para lt->contatos

    fclose(file);
    printf("Contatos carregados com sucesso a partir do arquivo: %s\n", arquivo);
}

void salvarContatos(ListaDeContatos lt, const char *arquivo) {
    FILE *file = fopen(arquivo, "wb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar Contatos.\n");
        return;
    }

    fwrite(&(lt.qtd), sizeof(int), 1, file);
    fwrite(lt.contatos, sizeof(Contato), lt.qtd, file); // Corrigindo para lt.contatos

    fclose(file);
    printf("Contatos salvos com sucesso no arquivo: %s\n", arquivo);
}

void deletarContato(ListaDeContatos *lt) {
    int posicao = -1;
    char telefone[15];
    printf("Digite o número de telefone do contato que deseja deletar: ");
    scanf("%s", telefone);

    // Procurar o contato pelo telefone
    for (int i = 0; i < lt->qtd; i++) {
        if (strcmp(lt->contatos[i].telefone, telefone) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("Contato com o telefone %s não encontrado.\n", telefone);
        return;
    }

    // Remover o contato encontrando deslocando os contatos restantes para a esquerda
    for (int i = posicao; i < lt->qtd - 1; i++) {
        lt->contatos[i] = lt->contatos[i + 1];
    }

    lt->qtd--;

    printf("Contato com o telefone %s deletado com sucesso.\n", telefone);
}

void alterarContato(ListaDeContatos *lt) {
    if (lt->qtd == 0) {
        printf("A lista de contatos está vazia. Não há contatos para alterar.\n");
        return;
    }

    char telefone[15];
    printf("Digite o número de telefone do contato que deseja alterar: ");
    scanf("%s", telefone);

    // Procurar o contato pelo telefone
    int posicao = -1;
    for (int i = 0; i < lt->qtd; i++) {
        if (strcmp(lt->contatos[i].telefone, telefone) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("Contato com o telefone %s não encontrado.\n", telefone);
        return;
    }

    // Imprimir os dados atuais do contato
    printf("Dados atuais do contato:\n");
    printf("Nome: %s\n", lt->contatos[posicao].nome);
    printf("Sobrenome: %s\n", lt->contatos[posicao].sobrenome);
    printf("E-mail: %s\n", lt->contatos[posicao].e_mail);

    Contato novoContato;

    printf("Novo nome (até 20 caracteres): ");
    scanf("%s", novoContato.nome); // Lendo como uma string

    printf("Novo sobrenome (até 50 caracteres): ");
    scanf("%s", novoContato.sobrenome); // Lendo como uma string

    // Loop para solicitar e-mail até que seja inserido um formato válido
    do {
        printf("Novo e-mail (até 30 caracteres): ");
        scanf("%s", novoContato.e_mail); // Lendo como uma string

        // Validar e-mail
        if (!validarEmail(novoContato.e_mail)) {
            printf("E-mail inválido. Por favor, insira um e-mail válido.\n");
        }
    } while (!validarEmail(novoContato.e_mail)); // Repetir até que um e-mail válido seja inserido

    // Atualizar os dados do contato
    lt->contatos[posicao] = novoContato;

    printf("Contato alterado com sucesso!\n");
}

