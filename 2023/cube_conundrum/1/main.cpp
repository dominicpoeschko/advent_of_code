#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

std::optional<unsigned int> getIdIfValidGame(std::string line) {
    auto isEntryValid = [](std::string entry) {
        auto const count = std::stoul(entry);
        if(entry.contains("red")) {
            return count <= 12;
        }
        if(entry.contains("green")) {
            return count <= 13;
        }
        if(entry.contains("blue")) {
            return count <= 14;
        }
        return false;
    };

    auto isValidDraw = [&](std::string draw) {
        std::istringstream input{draw};
        for(std::string entry; std::getline(input, entry, ',');) {
            bool valid = isEntryValid(entry);
            if(!valid) {
                return false;
            }
        }
        return true;
    };

    line.erase(0, 5);
    auto const gameId = std::stoul(line);

    auto const colonPos = std::find(line.begin(), line.end(), ':');
    if(colonPos == line.end()) {
        std::cerr << "bad input " << line << '\n';
    }
    line.erase(line.begin(), colonPos + 1);

    std::istringstream input{line};
    bool               allValid = true;
    for(std::string draw; std::getline(input, draw, ';');) {
        if(!isValidDraw(draw)) {
            allValid = false;
        }
    }

    if(allValid) {
        return gameId;
    }
    return std::nullopt;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cerr << "no input file\n";
        return 1;
    }

    std::ifstream inFile{argv[1]};

    unsigned int sum{};
    for(std::string line; std::getline(inFile, line);) {
        auto id = getIdIfValidGame(line);
        if(id) {
            sum += *id;
        }
    }

    std::cout << sum << '\n';
    return 0;
}
