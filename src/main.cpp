#include <QtWidgets/QApplication>
#include <src/view/MainWindow.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto main_window = new MainWindow();
    main_window->show();

    return app.exec();
}


