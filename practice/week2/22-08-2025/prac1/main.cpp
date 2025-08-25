#include <dlfcn.h>
#include <iostream>
static int c = 56;
int g = 11;
// extern int d;
// extern int e;

// extern "C" int add(int a, int b) {
//     return a + b;
// }

int add(int a, int b);

int main() {

    void* pToLib = dlopen("./libdysampletwoo.so", RTLD_LAZY);

    if (!pToLib) {
        std::cerr << dlerror() << std::endl;
        return 1;
    }

    dlerror();

    int (*add)(int, int) = (int(*)(int, int)) dlsym(pToLib, "add");
    static int z = 4;
    int c = 4;

    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'add': " << dlsym_error << '\n';
        dlclose(pToLib);
        return 1;
    }

    // extern int f;
    int a = 12;
    int b = 15;
    // d = 5;
    // e = 20;
    b = 5;
    // f = 7;
    std::cout << add(a, b) << std::endl;
}