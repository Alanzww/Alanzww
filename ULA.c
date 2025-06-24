#include "ULA.h"
#include <stdio.h>

//Uma função static só pode ser usada dentro do arquivo .c onde foi declarada

//Somador Baseado no livro Willian Stallings 10ed, capítulo 10, pag. 334
static void somadorCompleto(uint8_t A, uint8_t B, uint8_t cin, uint8_t * s, uint8_t * cout){
    *s = A ^ B ^ cin;
    *cout = (A & B) | (A & cin) | (B & cin);
}

static void somadorCompleto(uint8_t A, uint8_t B, uint8_t cin, uint8_t * s, uint8_t * cout){
    *s = A ^ B ^ cin;
    *cout = (A & B) | (A & cin) | (B & cin);
}

static void somador8bits(uint8_t *regA, uint8_t *regB, uint8_t *Cin, uint8_t *soma, uint8_t *Cout, uint8_t *overflow) {
    *Cout = *Cin;
    uint8_t somatorio;

    for (int i = 0; i < 8; i++) {
        uint8_t A = bit_get(regA, i);
        uint8_t B = bit_get(regB, i);

        somadorCompleto(A, B, *Cout, &somatorio, Cout);

        if (somatorio == 1) {
            bit_set(soma, i);
        } else {
            bit_clr(soma, i);
        }
    }

    // Overflow
    uint8_t msbA = bit_get(regA, 7);
    uint8_t msbB = bit_get(regB, 7);
    uint8_t msbSoma = bit_get(soma, 7);

    if ((msbA == msbB) && (msbSoma != msbA)) {
        *overflow = 1;
    } else {
        *overflow = 0;
    }
}

static void complementador(uint8_t *A) {
    *A = ~(*A);  // Inverte os bits (complemento de 1)

    uint8_t um = 1;         
    uint8_t carry = 0;      
    uint8_t resultado = 0;   
    uint8_t overflow = 0;   

    somador8bits(A, &um, &carry, &resultado, &carry, &overflow);

    *A = resultado;
}


//Adição de A e B e grava resultado em A
void ULA_ADD(int8_t *regA, int8_t *regB, int8_t *overflow) {
    uint8_t a = (uint8_t)*regA;
    uint8_t b = (uint8_t)*regB;
    uint8_t soma = 0;
    uint8_t cout = 0;
    uint8_t ovf = 0;
    uint8_t cin = 0;

    somador8bits(&a, &b, &cin, &soma, &cout, &ovf);

    *regA = (int8_t)soma;
    *overflow = ovf;
}

//Subtração de A e B e grava resultado em A
void ULA_SUB(int8_t * regA, int8_t * regB, int8_t * overflow){
    //Implemente o código aqui
}

//Multiplicação de Q(8bits) com M(8bits) gera resultado de 16bits que está em A(8bits) e Q(8bits)
void ULA_MUL(int8_t * A, int8_t * Q, int8_t * M,  int8_t * overflow){
//Implemente o código aqui
}

//Divisão com sinal de Q(Dividendo de 8bits) por M(Divisor de 8bits) com Quociente em Q(8bits) e Resto em A(8bits)
void ULA_DIV(int8_t * A, int8_t * Q, int8_t * M, int8_t * overflow){
    //Implemente o código aqui
}
