class Foo {
public:
    Foo() { /* default constructor */ }
    Foo(int x = 1, int y = 2) { /* also default via defaults */ }
};

int main() {
    Foo foo{}; // ERROR: ambiguous which default constructor to use
    return 0;
}