#include <stdio.h>

int division(int a, int b) {
    // On suppose que b est différent de zéro
    __CPROVER_assume(b != 0);
    
    // On calcule le résultat de la division
    int result = a / b;
    
    // On vérifie si le résultat est toujours correct
    __CPROVER_assert(result * b == a, "Division incorrecte");

    return result;
}

int main() {
    int a = 10;
    int b = 2;
    
    int result = division(a, b);
    
    printf("%d / %d = %d\n", a, b, result);
    
    return 0;
}
