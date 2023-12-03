#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

std::optional<unsigned int> getPowerOfGame(std::string line) {
    unsigned long maxRed   = 0;
    unsigned long maxGreen = 0;
    unsigned long maxBlue  = 0;

    auto handleEntry = [&](std::string entry) {
        auto const count = std::stoul(entry);
        if(entry.contains("red")) {
            maxRed = std::max(count, maxRed);
        }
        if(entry.contains("green")) {
            maxGreen = std::max(count, maxGreen);
        }
        if(entry.contains("blue")) {
            maxBlue = std::max(count, maxBlue);
        }
    };

    auto handleDraw = [&](std::string draw) {
        std::istringstream input{draw};
        for(std::string entry; std::getline(input, entry, ',');) {
            handleEntry(entry);
        }
    };

    auto const colonPos = std::find(line.begin(), line.end(), ':');
    if(colonPos == line.end()) {
        std::cerr << "bad input " << line << '\n';
    }
    line.erase(line.begin(), colonPos + 1);

    std::istringstream input{line};
    for(std::string draw; std::getline(input, draw, ';');) {
        handleDraw(draw);
    }

    return maxRed * maxGreen * maxBlue;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cerr << "no input file\n";
        return 1;
    }

    std::ifstream inFile{argv[1]};

    unsigned int sum{};
    for(std::string line; std::getline(inFile, line);) {
        auto const power = getPowerOfGame(line);
        if(power) {
            sum += *power;
        }
    }

    std::cout << sum << '\n';
    return 0;
}
