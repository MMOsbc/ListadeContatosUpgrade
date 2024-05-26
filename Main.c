#include <stdio.h> // Biblioteca padrão de entrada e saída
#include "funcoes.h" // Inclui o cabeçalho com as declarações das funções

int main() {
    ListaDeContatos listaContatos; // Declara uma variável para armazenar a lista de contatos
    listaContatos.qtd_pessoais = 0; // Inicializa a quantidade de contatos pessoais como zero
    listaContatos.qtd_trabalho = 0; // Inicializa a quantidade de contatos de trabalho como zero

    int opcao; // Declara uma variável para armazenar a opção do usuário

    do {
        printf("\nMenu:\n"); // Exibe o menu de opções para o usuário
        printf("1. Cadastrar Contato Pessoal\n"); // Opção para cadastrar um contato pessoal
        printf("2. Cadastrar Contato de Trabalho\n"); // Opção para cadastrar um contato de trabalho
        printf("3. Listar Contatos\n"); // Opção para listar os contatos
        printf("4. Carregar Contatos de Arquivo\n"); // Opção para carregar os contatos de um arquivo
        printf("5. Salvar Contatos em Arquivo\n"); // Opção para salvar os contatos em um arquivo
        printf("6. Deletar Contato\n"); // Opção para deletar um contato
        printf("7. Editar Contato\n"); // Opção para editar um contato
        printf("0. Sair\n"); // Opção para sair do programa
        printf("Escolha uma opção: "); // Solicita ao usuário que escolha uma opção
        scanf("%d", &opcao); // Lê a opção escolhida pelo usuário

        switch (opcao) { // Inicia a estrutura de controle switch para executar a ação correspondente à opção escolhida
            case 1: // Caso a opção seja 1 (Cadastrar Contato Pessoal)
                cadastrarContatoPessoal(&listaContatos); // Chama a função para cadastrar um contato pessoal
                break; // Encerra o case
            case 2: // Caso a opção seja 2 (Cadastrar Contato de Trabalho)
                cadastrarContatoTrabalho(&listaContatos); // Chama a função para cadastrar um contato de trabalho
                break; // Encerra o case
            case 3: // Caso a opção seja 3 (Listar Contatos)
                listarContatos(listaContatos); // Chama a função para listar os contatos
                break; // Encerra o case
            case 4: // Caso a opção seja 4 (Carregar Contatos de Arquivo)
                carregarContatos(&listaContatos, "arquivo"); // Chama a função para carregar os contatos de um arquivo
                break; // Encerra o case
            case 5: // Caso a opção seja 5 (Salvar Contatos em Arquivo)
                salvarContatos(listaContatos, "arquivo"); // Chama a função para salvar os contatos em um arquivo
                break; // Encerra o case
            case 6: // Caso a opção seja 6 (Deletar Contato)
                deletarContato(&listaContatos); // Chama a função para deletar um contato
                break; // Encerra o case
            case 7: // Caso a opção seja 7 (Editar Contato)
                alterarContato(&listaContatos); // Chama a função para editar um contato
                break; // Encerra o case
            case 0: // Caso a opção seja 0 (Sair)
                printf("Encerrando o programa...\n"); // Exibe uma mensagem indicando que o programa está sendo encerrado
                break; // Encerra o case
            default: // Caso a opção não corresponda a nenhuma das anteriores
                printf("Opção inválida.\n"); // Exibe uma mensagem indicando que a opção escolhida é inválida
        }
    } while (opcao != 0); // Repete o loop enquanto a opção escolhida for diferente de 0 (Sair)

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso
}
