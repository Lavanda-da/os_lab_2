#include <iostream>
#include <cstdlib>

int main() {
    std::string s;
    char c;
    for (int i = 0; i < 1000; ++i) {
        c = 'a' + (rand() % 26);
        s += c;
    }
    std::cout << s << std::endl;
    return 0;
}