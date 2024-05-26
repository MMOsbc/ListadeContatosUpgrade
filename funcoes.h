#ifndef FUNCOES_H
#define FUNCOES_H
// definição das variaveis inicias 
typedef struct {
    double id; // Corrigindo para double para armazenar IDs inteiros
    char telefone[15]; // Ajustando o tamanho para 15 para armazenar números de telefone
    char nome[21]; // Ajustando o tamanho para 21 para armazenar nomes de até 20 caracteres + o caractere nulo
    char sobrenome[51];
    char e_mail[31]; // Ajustando o tamanho para 51 para armazenar sobrenomes de até 50 caracteres + o caractere nulo
} Contato;
// struct quantidade de contatos
typedef struct {
    Contato contatos[255];
    int qtd;
} ListaDeContatos;
// assinaturas
void cadastrarContatos(ListaDeContatos *lt);
void listarContatos(ListaDeContatos lt);
void salvarContatos(ListaDeContatos lt, const char *arquivo);
void carregarContatos(ListaDeContatos *lt, const char *arquivo);
void deletarContato(ListaDeContatos *lt);
int validarEmail(const char *email); // Protótipo da função validarEmail
void alterarContato(ListaDeContatos *lt);


#endif /* FUNCOES_H */
