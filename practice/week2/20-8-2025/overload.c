#include <stdio.h>

// First function
int add(int a, int b) {
    return a + b;
}

// Second function (attempt to overload)
double add(double a, double b) {
    return a + b;
}

int main() {
    int x = add(2, 3);          // Calls int version
    double y = add(2.5, 3.7);   // Should call double version

    printf("x = %d\n", x);
    printf("y = %f\n", y);

    return 0;
}