#include <iostream>
#include <cstdlib>
#include <cstring>

int main(int argc, char* argv[]) {
    char *line = "This is the first line of data\nThis is the second line of data";
    std::cout << "" << line << std::endl;
    char *first_line = strtok(line, "\n");

    if (first_line != NULL) {
        std::cout << first_line << std::endl;
    }

    return 0;
}
