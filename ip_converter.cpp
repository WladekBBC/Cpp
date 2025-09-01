#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <cmath>
#include <sstream>

// Function to convert a decimal number to binary
std::string decToBin(int dec) {
    if (dec == 0) return "00000000"; 
    std::string bin;
    for (int i = 7; i >= 0; --i) {
        bin += ((dec >> i) & 1) ? '1' : '0';
    }
    return bin;
}

// Function to convert a binary string to decimal
int binToDec(const std::string& bin) {
    int dec = 0;
    int power = 0;
    for (int i = bin.length() - 1; i >= 0; --i) {
        if (bin[i] == '1') {
            dec += std::pow(2, power);
        }
        power++;
    }
    return dec;
}

// Function to remove all spaces from a string (still useful for decToBin for robustness)
std::string removeSpaces(const std::string& str) {
    std::string result = str;
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

std::string ipDecToBin(const std::string& ipDec) {

    std::string cleanedIpDec = removeSpaces(ipDec); 
    std::string result = "";
    std::string segment;
    std::stringstream ss(cleanedIpDec);
    std::vector<std::string> segments;

    while (std::getline(ss, segment, '.')) { 
        segments.push_back(segment);
    }

    if (segments.size() != 4) {
        return "Invalid Decimal IP Address Format";
    }

    for (const std::string& seg : segments) {
        try {
            int decValue = std::stoi(seg);
            if (decValue < 0 || decValue > 255) {
                return "Invalid Decimal IP Address (segment out of range)";
            }
            result += decToBin(decValue) + ".";
        } catch (const std::invalid_argument& e) {
            return "Invalid Decimal IP Address (non-numeric segment)";
        } catch (const std::out_of_range& e) {
            return "Invalid Decimal IP Address (segment out of range)";
        }
    }
    result.pop_back(); 
    return result;
}

// Function to convert a binary IP address to decimal
std::string ipBinToDec(const std::string& ipBin) {

    std::string tempIpBin = ipBin;
    std::replace(tempIpBin.begin(), tempIpBin.end(), '.', ' '); 

    std::string result = "";
    std::string segment;
    std::stringstream ss(tempIpBin);
    std::vector<std::string> segments;

    while (ss >> segment) {
        segments.push_back(segment);
    }

    if (segments.size() != 4) {
        return "Invalid Binary IP Address Format (expected 4 octets)";
    }

    for (const std::string& seg : segments) {
        if (seg.length() != 8) {
            return "Invalid Binary IP Address (segment not 8 bits)";
        }
        for (char c : seg) {
            if (c != '0' && c != '1') {
                return "Invalid Binary IP Address (contains non-binary characters)";
            }
        }
        result += std::to_string(binToDec(seg)) + ".";
    }
    result.pop_back();
    return result;
}

int main() {
    // ANSI color codes
    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string BLUE = "\033[34m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string CYAN = "\033[36m";

    std::string ipAddress;
    int choice;

    std::cout << BOLD << BLUE << "┌───────────────────────────────────────────┐" << RESET << std::endl;
    std::cout << BOLD << BLUE << "│" << RESET << "       " << YELLOW << "IP Address Converter" << RESET << "        " << BOLD << BLUE << "│" << RESET << std::endl;
    std::cout << BOLD << BLUE << "├───────────────────────────────────────────┤" << RESET << std::endl;
    std::cout << BOLD << BLUE << "│ " << GREEN << "1. Convert Decimal IP to Binary" << RESET << "         " << BOLD << BLUE << "│" << RESET << std::endl;
    std::cout << BOLD << BLUE << "│ " << GREEN << "2. Convert Binary IP to Decimal" << RESET << "         " << BOLD << BLUE << "│" << RESET << std::endl;
    std::cout << BOLD << BLUE << "└───────────────────────────────────────────┘" << RESET << std::endl;
    std::cout << CYAN << "Enter your choice: " << RESET;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    if (choice == 1) {
        std::cout << YELLOW << "Enter a Decimal IP Address (e.g., 192 . 168 . 1 . 1): " << RESET;
        std::getline(std::cin, ipAddress);
        std::cout << GREEN << "Binary IP Address: "<< RESET << ipDecToBin(ipAddress) << std::endl;
    } else if (choice == 2) {
        std::cout << YELLOW << "Enter a Binary IP Address (e.g., 11000000 10101000 00000001 00000001): " << RESET;
        std::getline(std::cin, ipAddress);
        std::cout << GREEN << "Decimal IP Address: " << RESET << ipBinToDec(ipAddress) << std::endl;
    } else {
        std::cout << "Invalid choice." << std::endl;
    }
    
}