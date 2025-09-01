#ifndef IPCONVERTERWINDOW_H
#define IPCONVERTERWINDOW_H

#include <QMainWindow>  // Base class for a main application window
#include <QLineEdit>    // Input field
#include <QLabel>       // Display text
#include <QPushButton>  // Button
#include <QRadioButton> // Radio button for choice
#include <QVBoxLayout>  // For arranging widgets vertically
#include <QHBoxLayout>  // For arranging widgets horizontally
#include <QWidget>      // Generic widget container

// Forward declare your IP conversion functions (or include the header if they're in a separate file)
// For simplicity, we'll assume they are defined directly in the .cpp here for this example.
// std::string decToBin(int dec);
// std::string binToDec(const std::string& bin);
// std::string ipDecToBin(const std::string& ipDec);
// std::string ipBinToDec(const std::string& ipBin);


class IpConverterWindow : public QMainWindow
{
    Q_OBJECT // This macro is essential for Qt's signal/slot mechanism

public:
    explicit IpConverterWindow(QWidget *parent = nullptr);
    ~IpConverterWindow();

private slots:
    void onConvertButtonClicked(); // This function will be called when the "Convert" button is clicked

private:
    QLineEdit *inputLineEdit;
    QLabel *outputLabel;
    QRadioButton *decToBinRadio;
    QRadioButton *binToDecRadio;
    QPushButton *convertButton;

    // Your existing IP conversion functions (re-declared or copied here for demonstration)
    std::string decToBin(int dec);
    int binToDec(const std::string& bin);
    std::string removeSpaces(const std::string& str);
    std::string ipDecToBin(const std::string& ipDec);
    std::string ipBinToDec(const std::string& ipBin);
};

#endif // IPCONVERTERWINDOW_H