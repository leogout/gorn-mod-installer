#include <iostream>
#include <QtCore/QtConfig>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QApplication>
#include <QtCore/QFile>
#include <QtCore/QSettings>
#include <src/view/PlatformSelection.h>
#include <QtCore/QDir>
#include <QtWidgets/QErrorMessage>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStackedWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <src/view/ModsSelection.h>
#include <src/view/MainWindow.h>
#include "utils/Registry.h"
#include "MemeLoaderInstaller.h"
#include "utils/Fetcher.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto main_window = new MainWindow();
    main_window->show();

    return app.exec();
}


