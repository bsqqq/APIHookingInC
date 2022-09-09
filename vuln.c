#include <stdio.h>
#include <string.h>

// Aqui devemos dar um jeito de chegar na string da funcao vitoria() 
// porem sem chamar a funcao no corpo da main, apenas usando tecnicas de Buffer Overflow.
// recomendo usar o x32dbg para verificar quantos bytes sao necessarios para sobescrever o endereco de retorno da funcao... 😁
// para mais detalhes, consulte o arquivo exploit.c

void vitoria() {
    printf("Parabens, vc conseguiu!");
}

int main() {
    char var[50];
    gets(var);
    printf("Voce enviou: %s\n", var);
    return (0);
}