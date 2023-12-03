#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

template<typename It>
std::optional<unsigned int> findDigit(It first, It last, bool reversed) {
    static constexpr std::array<std::string_view, 9>
      spelledDigits{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    auto const digitCondition = [](unsigned char c) { return std::isdigit(c); };
    auto const digitPos       = std::find_if(first, last, digitCondition);

    auto         spelledDigitPos = last;
    unsigned int foundIndex      = 0;
    unsigned int index           = 0;

    for(auto const& spelledDigit : spelledDigits) {
        ++index;

        auto const pos = [&]() {
            if(reversed) {
                return std::search(first, last, spelledDigit.rbegin(), spelledDigit.rend());
            } else {
                return std::search(first, last, spelledDigit.begin(), spelledDigit.end());
            }
        }();

        if(spelledDigitPos > pos) {
            foundIndex      = index;
            spelledDigitPos = pos;
        }
    }

    if(digitPos < spelledDigitPos && digitPos != last) {
        return *digitPos - '0';
    } else if(spelledDigitPos < digitPos && spelledDigitPos != last) {
        return foundIndex;
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

    std::string line;
    while(std::getline(inFile, line)) {
        auto const firstNumber = findDigit(line.begin(), line.end(), false);
        auto const lastNumber  = findDigit(line.rbegin(), line.rend(), true);

        if(!firstNumber || !lastNumber) {
            std::cerr << "bad input: " << line << "\n";
            return 1;
        }
        sum += (*firstNumber) * 10 + (*lastNumber);
    }

    std::cout << sum << '\n';
    return 0;
}
