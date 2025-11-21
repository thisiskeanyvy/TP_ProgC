#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(void) {
    const double rayon = 6.0;
    const double aire = M_PI * rayon * rayon;
    const double perimetre = 2.0 * M_PI * rayon;

    printf("Rayon : %.2f\n", rayon);
    printf("Aire : %.4f\n", aire);
    printf("Périmètre : %.4f\n", perimetre);

    return 0;
}
