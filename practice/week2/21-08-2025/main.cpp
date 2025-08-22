int add(int a, int b) {
    return a + b;
}

extern int z;

int y = 5;

int main() {
    
    int a = 20;
    int b = 70;
    int c = 35;

    add(b, c);

    z = 5;
    y = 6;
}