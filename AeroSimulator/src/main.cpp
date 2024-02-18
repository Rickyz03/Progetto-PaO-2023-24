#include <QApplication>
#include <QFile>

#include "View/MainWindow.h"

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("Assets/Icona.svg"));

    View::MainWindow window;
    window.resize(1024, 576);
    window.show();

    return app.exec();
}