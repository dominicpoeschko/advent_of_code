#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

unsigned int
lineSum(std::string const& prefLine, std::string const& line, std::string const& nextLine) {
    auto checkIfSymbol = [&](std::size_t start, std::size_t end) {
        auto condition = [&](auto c) {
            if(c == '.' || std::isdigit(c)) {
                return false;
            }
            return true;
        };

        return std::any_of(prefLine.begin() + start, prefLine.begin() + end, condition)
            || std::any_of(nextLine.begin() + start, nextLine.begin() + end, condition)
            || condition(line[start]) || condition(line[end - 1]);
    };

    unsigned int sum = 0;
    auto         it  = line.begin();

    while(it != line.end()) {
        it = std::find_if(it, line.end(), [](unsigned char c) { return std::isdigit(c); });
        if(it == line.end()) {
            break;
        }

        unsigned int number{};
        auto [ptr, ec] = std::from_chars(&(*it), &(*line.end()), number);
        if(ec != std::errc()) {
            std::cerr << "bad input\n";
            return 0;
        }
        if(checkIfSymbol(std::distance(line.begin(), it) - 1, std::distance(line.data(), ptr) + 1))
        {
            sum += number;
        }
        it = line.begin() + std::distance(line.data(), ptr);
    }

    return sum;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cerr << "no input file\n";
        return 1;
    }

    std::ifstream inFile{argv[1]};

    std::vector<std::string> lines;
    lines.resize(1);

    for(std::string line; std::getline(inFile, line);) {
        lines.push_back(line);
    }

    auto emptyLine = std::string(lines[1].size(), '.');
    lines[0]       = emptyLine;
    lines.push_back(emptyLine);

    for(auto& line : lines) {
        line.insert(line.begin(), '.');
        line.push_back('.');
    }

    unsigned int sum = 0;
    for(auto index = 1; index < lines.size() - 1; ++index) {
        sum += lineSum(lines[index - 1], lines[index], lines[index + 1]);
    }

    std::cout << sum << '\n';
    return 0;
}
