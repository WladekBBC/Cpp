#include "ipconverterwindow.h"
#include <QMessageBox> // For showing error messages
#include <limits>      // For std::numeric_limits
#include <algorithm>   // For std::remove, std::replace
#include <sstream>     // For std::stringstream
#include <cmath>       // For std::pow

// --- Start of your original IP conversion functions (copied here for simplicity) ---
std::string IpConverterWindow::decToBin(int dec) {
    if (dec == 0) return "00000000";
    std::string bin;
    for (int i = 7; i >= 0; --i) {
        bin += ((dec >> i) & 1) ? '1' : '0';
    }
    return bin;
}

int IpConverterWindow::binToDec(const std::string& bin) {
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

std::string IpConverterWindow::removeSpaces(const std::string& str) {
    std::string result = str;
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

std::string IpConverterWindow::ipDecToBin(const std::string& ipDec) {
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

std::string IpConverterWindow::ipBinToDec(const std::string& ipBin) {
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
// --- End of your original IP conversion functions ---


IpConverterWindow::IpConverterWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // --- 1. Create Widgets ---
    decToBinRadio = new QRadioButton("Decimal to Binary", this);
    binToDecRadio = new QRadioButton("Binary to Decimal", this);
    inputLineEdit = new QLineEdit(this);
    convertButton = new QPushButton("Convert", this);
    outputLabel = new QLabel("Result will appear here", this); // Initial text

    // Set a default selection for radio buttons
    decToBinRadio->setChecked(true);
    inputLineEdit->setPlaceholderText("Enter IP Address (e.g., 192.168.1.1 or 1100...001)");


    // --- 2. Arrange Widgets using Layouts ---
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Layout for radio buttons
    QHBoxLayout *radioLayout = new QHBoxLayout();
    radioLayout->addWidget(decToBinRadio);
    radioLayout->addWidget(binToDecRadio);
    radioLayout->addStretch(); // Pushes buttons to the left

    mainLayout->addLayout(radioLayout);
    mainLayout->addWidget(inputLineEdit);
    mainLayout->addWidget(convertButton);
    mainLayout->addWidget(outputLabel);
    mainLayout->addStretch(); // Pushes content to the top

    // --- 3. Connect Signals and Slots ---
    // When convertButton is clicked, call onConvertButtonClicked()
    connect(convertButton, &QPushButton::clicked, this, &IpConverterWindow::onConvertButtonClicked);

    // Set window title
    setWindowTitle("IP Address Converter");
    resize(400, 200); // Set initial window size
}

IpConverterWindow::~IpConverterWindow()
{
    // Qt's parent-child ownership model usually handles deletion of child widgets
    // so explicit deletion here is often not strictly necessary if they have a parent,
    // but it's good practice for top-level allocations if not using QScopedPointer.
    // For simplicity, omitting explicit deletes here.
}

// Slot implementation
void IpConverterWindow::onConvertButtonClicked()
{
    QString inputIp = inputLineEdit->text(); // Get text from input field
    std::string result;

    if (decToBinRadio->isChecked()) {
        result = ipDecToBin(inputIp.toStdString());
    } else if (binToDecRadio->isChecked()) {
        result = ipBinToDec(inputIp.toStdString());
    }

    // Display the result or an error
    if (result.rfind("Invalid", 0) == 0) { // Check if result starts with "Invalid"
        QMessageBox::warning(this, "Error", QString::fromStdString(result));
        outputLabel->setText("Error: " + QString::fromStdString(result));
        outputLabel->setStyleSheet("color: red;"); // Make error messages red
    } else {
        outputLabel->setText(QString::fromStdString(result));
        outputLabel->setStyleSheet("color: black;"); // Reset color for valid results
    }
}