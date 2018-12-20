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
            QString destination_path = QDir(config.path).filePath("GORN_Data/Assembly-CSharp.dll");
            QString backup_path = QDir(config.path).filePath("GORN_Data/Assembly-CSharp.backup.dll");

            // Check if destination file exists
            if (not QFile::exists(destination_path)) {
                QMessageBox::critical(window, "Incorrect GORN path", "The file \"" + destination_path + "\" does not exist.");
                return;
            }

            // Remove backup file if needed
            if (QFile::exists(backup_path)) {
                QMessageBox::StandardButton reply = QMessageBox::question(
                        window,
                        "Backup file already exists", "The file \"" + backup_path + "\" already exists, do you want to replace it ?",
                        QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes) {
                    QFile::remove(backup_path);
                }
            }

            // Copy is performed only if the file does not already exist
            QFile::copy(destination_path, backup_path);
            QFile::remove(destination_path);
            QFile::copy(":/test.txt", destination_path);

            savePlatformConfig(config);

            QMessageBox::information(window, "Success", "MemeLoader has been added to GORN successfully.");
        });
    } else {
        auto platform_selection = new QLabel("Game path is : " + config.path);
        main_layout->addWidget(platform_selection);
    }

    window->setLayout(main_layout);

    window->show();

    return app.exec();
}