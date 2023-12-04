#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

std::vector<unsigned int> extractNumbers(std::string_view input) {
    std::vector<unsigned int> numbers;
    auto                      it = input.begin();
    while(it != input.end()) {
        while(*it == ' ' && it != input.end()) {
            ++it;
        }
        if(it == input.end()) {
            break;
        }
        unsigned int number;
        auto [ptr, ec] = std::from_chars(it, input.end(), number);
        if(ec != std::errc()) {
            break;
        }
        it = ptr;
        numbers.push_back(number);
    }
    return numbers;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cerr << "no input file\n";
        return 1;
    }

    std::ifstream inFile{argv[1]};

    unsigned int sum{};
    for(std::string line; std::getline(inFile, line);) {
        auto const colonPos = std::find(line.begin(), line.end(), ':');
        auto const linePos  = std::find(line.begin(), line.end(), '|');

        auto const winningCardsString   = std::string_view{colonPos + 1, linePos - 1};
        auto const availableCardsString = std::string_view{linePos + 1, line.end()};

        auto winningCards   = extractNumbers(winningCardsString);
        auto availableCards = extractNumbers(availableCardsString);

        std::sort(winningCards.begin(), winningCards.end());
        std::sort(availableCards.begin(), availableCards.end());

        std::vector<unsigned int> intersection;
        std::set_intersection(
          winningCards.begin(),
          winningCards.end(),
          availableCards.begin(),
          availableCards.end(),
          std::back_inserter(intersection));

        if(!intersection.empty()) {
            sum += 1 << (intersection.size() - 1);
        }
    }

    std::cout << sum << '\n';
    return 0;
}
