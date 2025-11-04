#include <stdio.h>
int gcd(int a, int b);

int main(){
    int a ,b;
    printf("Inserisci i due valori dei quali vuoi trovare il gcd\n");
    printf("======\n");
    printf("Primo numero:\n");
    scanf("%d", &a);
    if (a < 0) {
        printf("I numeri devono essere maggiori o uguali 0");
        return 0;
    }
    printf("Secondo numero:\n");
    scanf("%d", &b);
    if (b < 0) {
        printf("I numeri devono essere maggiori o uguali 0");
        return 0;
    }
    printf("MCD uguale a: %d", gcd(a,b));
return 0;
}

int gcd(int a, int b) {
    if(b > a) return gcd(b, a);
    //termination cases
    if(a == b) return b;
    if(a%b == 0) return b;
    if(b == 1) return b;
    if(a%2 == 0 && b%2 == 0) return 2*gcd(a/2, b/2);
    if(a%2 != 0 && b%2 == 0) return gcd(a, b/2);
    if(a%2 == 0 && b%2 != 0) return gcd(a/2, b);
    if(a%2 != 0 && b%2 != 0) return gcd((a-b)/2, b);

}