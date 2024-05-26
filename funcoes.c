#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "funcoes.h"




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

void cadastrarContatoPessoal(ListaDeContatos *lt) {
    if (lt->qtd_pessoais >= 255) {
        printf("A lista de contatos pessoais está cheia. Não é possível cadastrar mais contatos.\n");
        return;
    }

    Contato novoContato;

    printf("Número de cadastro: ");
    scanf("%lf", &novoContato.id); // Usando %lf para ler um double

    printf("Telefone: ");
    scanf("%s", novoContato.telefone); // Lendo como uma string

    // Verificar se o número de telefone já existe na lista
    for (int i = 0; i < lt->qtd_pessoais; i++) {
        if (strcmp(lt->contatos_pessoais[i].telefone, novoContato.telefone) == 0) {
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

    lt->contatos_pessoais[lt->qtd_pessoais] = novoContato;
    lt->qtd_pessoais++;

    printf("Contato pessoal cadastrado com sucesso!\n");
}

void cadastrarContatoTrabalho(ListaDeContatos *lt) {
    if (lt->qtd_trabalho >= 255) {
        printf("A lista de contatos de trabalho está cheia. Não é possível cadastrar mais contatos.\n");
        return;
    }

    Contato novoContato;

    printf("Número de cadastro: ");
    scanf("%lf", &novoContato.id); // Usando %lf para ler um double

    printf("Telefone: ");
    scanf("%s", novoContato.telefone); // Lendo como uma string

    // Verificar se o número de telefone já existe na lista
    for (int i = 0; i < lt->qtd_trabalho; i++) {
        if (strcmp(lt->contatos_trabalho[i].telefone, novoContato.telefone) == 0) {
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

    lt->contatos_trabalho[lt->qtd_trabalho] = novoContato;
    lt->qtd_trabalho++;

    printf("Contato de trabalho cadastrado com sucesso!\n");
}

void listarContatos(ListaDeContatos lt) {
    if (lt.qtd_pessoais == 0 && lt.qtd_trabalho == 0) {
        printf("A lista de contatos está vazia.\n");
        return;
    }

    printf("Lista de Contatos Pessoais:\n");
    for (int i = 0; i < lt.qtd_pessoais; i++) {
        printf("ID %d:\n", i + 1);
        printf("ID: %.0lf\n", lt.contatos_pessoais[i].id);
        printf("Telefone: %s\n", lt.contatos_pessoais[i].telefone);
        printf("Nome: %s\n", lt.contatos_pessoais[i].nome);
        printf("Sobrenome: %s\n", lt.contatos_pessoais[i].sobrenome);
        printf("E-mail: %s\n", lt.contatos_pessoais[i].e_mail);
        printf("\n");
    }

    printf("Lista de Contatos de Trabalho:\n");
    for (int i = 0; i < lt.qtd_trabalho; i++) {
        printf("ID %d:\n", i + 1);
        printf("ID: %.0lf\n", lt.contatos_trabalho[i].id);
        printf("Telefone: %s\n", lt.contatos_trabalho[i].telefone);
        printf("Nome: %s\n", lt.contatos_trabalho[i].nome);
        printf("Sobrenome: %s\n", lt.contatos_trabalho[i].sobrenome);
        printf("E-mail: %s\n", lt.contatos_trabalho[i].e_mail);
        printf("\n");
    }
}

void carregarContatos(ListaDeContatos*lt, const char *arquivo) {
    FILE *file = fopen(arquivo, "rb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo de contatos.\n");
        return;
    }

    fread(&(lt->qtd_pessoais), sizeof(int), 1, file);
    fread(lt->contatos_pessoais, sizeof(Contato), lt->qtd_pessoais, file);

    fread(&(lt->qtd_trabalho), sizeof(int), 1, file);
    fread(lt->contatos_trabalho, sizeof(Contato), lt->qtd_trabalho, file);

    fclose(file);
    printf("Contatos carregados com sucesso a partir do arquivo: %s\n", arquivo);
}

void salvarContatos(ListaDeContatos lt, const char *arquivo) {
    FILE *file = fopen(arquivo, "wb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar Contatos.\n");
        return;
    }

    fwrite(&(lt.qtd_pessoais), sizeof(int), 1, file);
    fwrite(lt.contatos_pessoais, sizeof(Contato), lt.qtd_pessoais, file);

    fwrite(&(lt.qtd_trabalho), sizeof(int), 1, file);
    fwrite(lt.contatos_trabalho, sizeof(Contato), lt.qtd_trabalho, file);

    fclose(file);
    printf("Contatos salvos com sucesso no arquivo: %s\n", arquivo);
}

void deletarContato(ListaDeContatos *lt) {
    char telefone[15];
    printf("Digite o número de telefone do contato que deseja deletar: ");
    scanf("%s", telefone);

    bool encontrado = false;

    // Procurar o contato pelo telefone
    for (int i = 0; i < lt->qtd_pessoais; i++) {
        if (strcmp(lt->contatos_pessoais[i].telefone, telefone) == 0) {
            for (int j = i; j < lt->qtd_pessoais - 1; j++) {
                lt->contatos_pessoais[j] = lt->contatos_pessoais[j + 1];
            }
            lt->qtd_pessoais--;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        for (int i = 0; i < lt->qtd_trabalho; i++) {
            if (strcmp(lt->contatos_trabalho[i].telefone, telefone) == 0) {
                for (int j = i; j < lt->qtd_trabalho - 1; j++) {
                    lt->contatos_trabalho[j] = lt->contatos_trabalho[j + 1];
                }
                lt->qtd_trabalho--;
                encontrado = true;
                break;
            }
        }
    }

    if (encontrado) {
        printf("Contato com o telefone %s deletado com sucesso.\n", telefone);
    } else {
        printf("Contato com o telefone %s não encontrado.\n", telefone);
    }
}

void alterarContato(ListaDeContatos *lt) {
    char telefone[15];
    printf("Digite o número de telefone do contato que deseja alterar: ");
    scanf("%s", telefone);

    bool encontrado = false;

    // Procurar o contato pelo telefone
    for (int i = 0; i < lt->qtd_pessoais; i++) {
        if (strcmp(lt->contatos_pessoais[i].telefone, telefone) == 0) {
            printf("Dados atuais do contato:\n");
            printf("Nome: %s\n", lt->contatos_pessoais[i].nome);
            printf("Sobrenome: %s\n", lt->contatos_pessoais[i].sobrenome);
            printf("E-mail: %s\n", lt->contatos_pessoais[i].e_mail);
            printf("\n");

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
            lt->contatos_pessoais[i] = novoContato;
            printf("Contato pessoal alterado com sucesso!\n");
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        for (int i = 0; i < lt->qtd_trabalho; i++) {
            if (strcmp(lt->contatos_trabalho[i].telefone, telefone) == 0) {
                printf("Dados atuais do contato:\n");
                printf("Nome: %s\n", lt->contatos_trabalho[i].nome);
                printf("Sobrenome: %s\n", lt->contatos_trabalho[i].sobrenome);
                printf("E-mail: %s\n", lt->contatos_trabalho[i].e_mail);
                printf("\n");

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
                lt->contatos_trabalho[i] = novoContato;
                printf("Contato de trabalho alterado com sucesso!\n");
                encontrado = true;
                break;
            }
        }
    }

    if (!encontrado) {
        printf("Contato com o telefone %s não encontrado.\n", telefone);
    }
}

