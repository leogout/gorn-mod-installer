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

    Registry::unsetPlatform(); // <- for testing purposes, uncomment this

    PlatformConfig config = Registry::getPlatformConfig();

    auto platform_selection = new PlatformSelection();
    auto mods_installer = new QLabel("Game path is : " + config.path);

    auto stacked_widget = new QStackedWidget;
    stacked_widget->addWidget(mods_installer);
    stacked_widget->addWidget(platform_selection);

    window->connect(platform_selection, &PlatformSelection::platformSelected, [&](PlatformConfig config){
        MemeLoaderInstaller::install(window, config);
        stacked_widget->setCurrentWidget(mods_installer);
    });

    if (config.platform == PlatformType::None) {
        stacked_widget->setCurrentWidget(platform_selection);
    } else {
        stacked_widget->setCurrentWidget(mods_installer);
    }

    main_layout->addWidget(stacked_widget);
    window->setLayout(main_layout);

    window->show();

    return app.exec();
}