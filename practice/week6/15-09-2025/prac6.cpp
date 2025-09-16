#include <iostream>

class A {
public:
    int a;
    virtual void f() {}
};

class B : virtual public A {
public:
    int b;
    void f() override {}
};

class C : virtual public A {
public:
    int c;
    void f() override {}
};

class D : public B, public C {
public:
    int d;
    void f() override {}
};

int main() { D obj; }
