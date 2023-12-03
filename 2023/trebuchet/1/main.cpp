#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cerr << "no input file\n";
        return 1;
    }

    std::ifstream inFile{argv[1]};

    unsigned int sum{};
    std::string  line;
    while(std::getline(inFile, line)) {
        auto condition = [](unsigned char c) { return std::isdigit(c); };

        auto firstNumberPos = std::find_if(line.begin(), line.end(), condition);
        auto lastNumberPos  = std::find_if(line.rbegin(), line.rend(), condition);

        if(firstNumberPos == line.end() || lastNumberPos == line.rend()) {
            std::cerr << "bad input\n";
            return 1;
        }
        sum += ((*firstNumberPos) - '0') * 10 + ((*lastNumberPos) - '0');
    }

    std::cout << sum << '\n';
    return 0;
}
