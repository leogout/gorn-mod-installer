#include <QtWidgets/QApplication>
#include <src/view/MainWindow.h>
#include <src/utils/Registry.h>
#include <src/utils/FileDownloader.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Registry::unsetPlatform(); // <- for testing purposes

//    auto main_window = new MainWindow();
//    main_window->show();
    auto fd = new FileDownloader;

    fd->download("https://www.qt.iqsdqsdo");

    fd->connect(fd, &FileDownloader::success, fd, [] (QTemporaryFile* file) {
        qDebug() << "success";
    });

    fd->connect(fd, &FileDownloader::error, fd, [] (FileDownloader::Error error) {
        qDebug() << "error";
    });

    return app.exec();
}


