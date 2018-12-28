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
#include "Registry.h"
#include "MemeLoaderInstaller.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto window = new QWidget;
    window->setMinimumSize(400, 100);
    window->setWindowTitle("GORN Mods Installer");
    window->setWindowIcon(QIcon(":/icon.png"));

    // Layouts
    auto main_layout = new QHBoxLayout;

    Registry::unsetPlatform(); // <- for testing purposes

    PlatformConfig config = Registry::getPlatformConfig();

    auto platform_selection = new PlatformSelection();
    auto mods_installer = new QLabel("Game path is : " + config.path);

    auto stacked_widget = new QStackedWidget;
    stacked_widget->addWidget(mods_installer);
    stacked_widget->addWidget(platform_selection);

    window->connect(platform_selection, &PlatformSelection::platformSelected, [&](PlatformConfig config){
        MemeLoaderInstaller::install(window, config);
        // @todo check if installation went OK
        stacked_widget->setCurrentWidget(mods_installer);
    });

    if (config.platform == PlatformType::None) {
        stacked_widget->setCurrentWidget(platform_selection);
    } else {
        stacked_widget->setCurrentWidget(mods_installer);
    }

    main_layout->addWidget(stacked_widget);

    auto networkManager = new QNetworkAccessManager(window);

    networkManager->get(QNetworkRequest(QUrl("https://api.github.com/repos/leogout/gorn-mod-installer/contents/mods")));

    window->connect(networkManager, &QNetworkAccessManager::finished, window, [&](QNetworkReply* reply){
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonArray rootObj = document.array();
        std::cout << "Parsing..." << std::endl;

        for (auto obj: rootObj) {
            std::cout << obj.toObject().value("_links").toObject().value("self").toString().toStdString() << std::endl;
        }
    });

    window->setLayout(main_layout);

    window->show();

    return app.exec();
}


