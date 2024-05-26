#ifndef FUNCOES_H
#define FUNCOES_H
#include <stdbool.h>

// definição das variaveis inicias 


typedef struct {
    double id; // Corrigindo para double para armazenar IDs inteiros
    char telefone[15]; // Ajustando o tamanho para 15 para armazenar números de telefone
    char nome[21]; // Ajustando o tamanho para 21 para armazenar nomes de até 20 caracteres + o caractere nulo
    char sobrenome[51]; // Ajustando o tamanho para 51 para armazenar sobrenomes de até 50 caracteres + o caractere nulo
    char e_mail[31]; // Ajustando o tamanho para 31 para armazenar e-mails de até 30 caracteres + o caractere nulo
} Contato;

typedef struct {
    Contato contatos_pessoais[255]; // Array para armazenar contatos pessoais
    Contato contatos_trabalho[255]; // Array para armazenar contatos de trabalho
    int qtd_pessoais; // Quantidade de contatos pessoais cadastrados
    int qtd_trabalho; // Quantidade de contatos de trabalho cadastrados
} ListaDeContatos;

void cadastrarContatoPessoal(ListaDeContatos *lt);
void cadastrarContatoTrabalho(ListaDeContatos *lt);
void listarContatosPessoais(ListaDeContatos lt);
void listarContatosTrabalho(ListaDeContatos lt);
void carregarContatos(ListaDeContatos *lt, const char *arquivo);
void salvarContatos(ListaDeContatos lt, const char *arquivo);
void deletarContato(ListaDeContatos *lt);
void alterarContato(ListaDeContatos *lt);
int validarEmail(const char *email);

#endif /* FUNCOES_H */
