#include <stdio.h>

static int bit_depuis_gauche(unsigned int valeur, int position) {
    const int total_bits = (int)(sizeof(unsigned int) * 8);
    if (position < 1 || position > total_bits) {
        return 0;
    }
    int decalage = total_bits - position;
    return (valeur >> decalage) & 1u;
}

int main(void) {
    const unsigned int d = 0xF0FF0FFFu;

    int bit4 = bit_depuis_gauche(d, 4);
    int bit20 = bit_depuis_gauche(d, 20);
    int resultat = (bit4 == 1 && bit20 == 1) ? 1 : 0;

    printf("Valeur : 0x%08X\n", d);
    printf("Bit 4 depuis la gauche : %d\n", bit4);
    printf("Bit 20 depuis la gauche : %d\n", bit20);
    printf("Résultat final : %d\n", resultat);

    return 0;
}

