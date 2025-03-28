#include <iostream>
#include <fstream>
#include <unordered_map>

int main() {
    std::string filename;
    std::cout << "Podaj nazwę pliku: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Nie można otworzyć pliku: " << filename << std::endl;
        return 1;
    }

    std::unordered_map<char, int> charCount;
    char c;
    while (file.get(c)) {
        charCount[c]++;
    }

    file.close();

    char mostFrequentChar = 0;
    int maxCount = 0;

    for (const auto& pair : charCount) {
        if (pair.second > maxCount) {
            mostFrequentChar = pair.first;
            maxCount = pair.second;
        }
    }

    if (maxCount > 0) {
        std::cout << "Najczęściej występujący znak to: \""<< mostFrequentChar <<"\" i występuje on " << maxCount << " razy." << std::endl;
    } else {
        std::cout << "Plik jest pusty lub nie zawiera żadnych znaków." << std::endl;
    }

    return 0;
}
