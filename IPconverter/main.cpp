#include <QApplication> // Necessary for any Qt GUI application
#include "ipconverterwindow.h" // Your custom main window class

int main(int argc, char *argv[]) {
    QApplication a(argc, argv); // Create the application object
    IpConverterWindow w;        // Create an instance of your main window
    w.show();                   // Display the window
    return a.exec();            // Start the Qt event loop
}