#include <QtWidgets/QApplication>
#include <src/view/MainWindow.h>
#include <src/utils/Registry.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Registry::unsetPlatform(); // <- for testing purposes

    auto main_window = new MainWindow();
    main_window->show();

    return app.exec();
}


