#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

unsigned int
gearSum(std::string const& prefLine, std::string const& line, std::string const& nextLine) {
    auto getGearRatio = [&](std::size_t gearPos) {
        std::map<std::tuple<std::size_t, std::size_t, std::size_t>, unsigned int> numbers;

        auto extractNumber = [&](std::string const& l, std::size_t lineNumber, std::size_t pos) {
            if(!std::isdigit(l[pos])) {
                return;
            }

            std::size_t numberStartPos = pos;
            std::size_t numberEndPos   = pos;
            while(std::isdigit(l[numberStartPos])) {
                numberStartPos--;
            }
            while(std::isdigit(l[numberEndPos])) {
                numberEndPos++;
            }

            auto const numberString
              = std::string{l.begin() + numberStartPos + 1, l.begin() + numberEndPos};

            numbers[std::make_tuple(numberStartPos, numberEndPos, lineNumber)]
              = std::stoul(numberString);
        };

        extractNumber(prefLine, 0, gearPos - 1);
        extractNumber(prefLine, 0, gearPos);
        extractNumber(prefLine, 0, gearPos + 1);

        extractNumber(line, 1, gearPos - 1);
        extractNumber(line, 1, gearPos + 1);

        extractNumber(nextLine, 2, gearPos - 1);
        extractNumber(nextLine, 2, gearPos);
        extractNumber(nextLine, 2, gearPos + 1);

        if(numbers.size() == 2) {
            unsigned int product = 1;
            for(auto num : numbers) {
                product *= num.second;
            }
            return product;
        }
        return unsigned{0};
    };

    unsigned int sum = 0;
    auto         it  = std::find(line.begin(), line.end(), '*');

    while(it != line.end()) {
        sum += getGearRatio(std::distance(line.begin(), it));

        it = std::find(it + 1, line.end(), '*');
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
        sum += gearSum(lines[index - 1], lines[index], lines[index + 1]);
    }

    std::cout << sum << '\n';
    return 0;
}
