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

PlatformConfig getPlatformConfig() {
    QSettings settings("Leogout", "Gorn Mods Installer");

    PlatformConfig config {
        (PlatformType) settings.value("config/platform", PlatformType::None).toInt(),
        settings.value("config/path").toString(),
    };

    return config;
}

void savePlatformConfig(PlatformConfig config) {
    QSettings settings("Leogout", "Gorn Mods Installer");
    settings.setValue("config/platform", config.platform);
    settings.setValue("config/path", config.path);
}

void unsetPlatform() {
    QSettings settings("Leogout", "Gorn Mods Installer");
    settings.remove("config/platform");
    settings.remove("config/path");
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto window = new QWidget;
    window->setMinimumSize(400, 100);
    window->setWindowTitle("GORN Mods Installer");
    window->setWindowIcon(QIcon(":/icon.png"));

    // Layouts
    auto main_layout = new QHBoxLayout;

    unsetPlatform(); // <- for testing purposes, uncomment this

    // @Todo find more elegant (eleganter?) way to handle this
    PlatformConfig config = getPlatformConfig();
    if (config.platform == PlatformType::None) {
        auto platform_selection = new PlatformSelection();
        main_layout->addWidget(platform_selection);

        window->connect(platform_selection, &PlatformSelection::platformSelected, [&](PlatformConfig config){
            savePlatformConfig(config);

            QString path = config.path;

            // add trailing slash if missing
            path += path.endsWith("/") or path.endsWith("\\") ? "test.txt" : "/test.txt";

            QFile::copy(":/test.txt", path);
        });
    } else {
        auto platform_selection = new QLabel("Game path is : " + config.path);
        main_layout->addWidget(platform_selection);
    }

    window->setLayout(main_layout);

    window->show();

    return app.exec();
}