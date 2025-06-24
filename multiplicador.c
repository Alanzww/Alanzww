void ULA_MUL(int8_t *A, int8_t *Q, int8_t *M, int8_t *overflow) {
    uint8_t acc = 0;               // A: acumulador dos bits mais significativos
    uint8_t q = (uint8_t)(*Q);     // Q: multiplicador
    uint8_t m = (uint8_t)(*M);     // M: multiplicando
    uint8_t carry = 0;             // Carry da soma
    uint8_t ovf = 0;               // Overflow da soma
    uint8_t soma = 0;              // Valor temporario da soma

    for (int i = 0; i < 8; i++) {
        if (bit_get(&q, 0)) {  // Se o bit menos significativo de Q e 1
            somador8bits(&acc, &m, &carry, &soma, &carry, &ovf);
            acc = soma;
        }

        // Deslocamento para a direita
        uint8_t lsbAcc = bit_get(&acc, 0);
        q >>= 1;
        if (lsbAcc)
            bit_set(&q, 7);
        else
            bit_clr(&q, 7);
        acc >>= 1;
    }

    *A = (int8_t)acc;
    *Q = (int8_t)q;
    *overflow = 0;  //(Aviso): O overflow não tá sendo notificado
}
