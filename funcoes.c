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

