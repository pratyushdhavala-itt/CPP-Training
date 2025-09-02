#include <iostream>
using namespace std;


int main() {
    int *m = (int*) malloc(5 * sizeof(int));
    int *c = (int*) calloc(5, sizeof(int));

    cout << "malloc:\n" << endl;
    for (int i = 0; i < 5; i++) printf("%d ", m[i]);
    printf("\n");

    cout << "calloc:\n" << endl;
    for (int i = 0; i < 5; i++) printf("%d ", c[i]);
    cout << "\n" << endl;

    free(m);
    free(c);
}
