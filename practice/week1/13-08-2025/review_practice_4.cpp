#include <iostream>
using namespace std;

struct Human {
    int age;
    int height;
    int weight;

    Human(int x_age, int x_height, int x_weight) {

        age = x_age;
        height = x_height;
        weight = x_weight;
    }

    void display() {
        cout << "(" << age << ", " << height << ", " << weight << ")" << '\n';
    }
};

void printPerson(Human &human) {
    cout << "Age: " << human.age << ", Height: " << human.height << ", Weight: " << human.weight << '\n';
}

enum class Color {
    RED,
    GREEN,
    YELLOW,
};

union Number {
    int i;
    long l;
    float f;
};

int main() {

    Human pratyush(22, 6, 60);
    pratyush.display();
    printPerson(pratyush);

    Color fav_color = Color::YELLOW;

    cout << static_cast<int>(fav_color) << endl;

    Number n;
    cout << sizeof(n);

}