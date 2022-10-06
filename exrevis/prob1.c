#include <stdio.h>

float parabola(float a, float x) {
    return a*x*x;
}

int main() {
    float a, lowend, upprend, increm;
    
    printf("Insira o valor de a: ");
    scanf("%f", &a);
    printf("Insira o intervalo: ");
    scanf("%f %f", &lowend, &upprend);
    printf("Insira o incremento: ");
    scanf("%f", &increm);

    if(upprend<lowend) {
        lowend+=upprend;
        upprend=lowend-upprend;
        lowend-=upprend;
    }

    while(lowend<=upprend) {
        printf("f(%f)=%.1f\n", lowend, parabola(a, lowend));
        lowend+=increm;
    }
}