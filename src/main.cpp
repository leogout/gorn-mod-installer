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

GamePlatform getPlatform() {
    QSettings settings("Leogout", "Gorn Mods Installer");

    // If platform undefined in registry, returns GamePlatform::None
    return (GamePlatform) settings.value("platform", GamePlatform::None).toInt();
}

void savePlatform(GamePlatform platform) {
    QSettings settings("Leogout", "Gorn Mods Installer");
    settings.setValue("platform", platform);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto window = new QWidget;
    window->setMinimumSize(400, 100);
    window->setWindowTitle("GORN Mods Installer");
    window->setWindowIcon(QIcon(":/icon.png"));

    // Image


    // Layouts
    auto main_layout = new QHBoxLayout;

    // @Todo find more elegant (eleganter?) way to handle this
    if (getPlatform() == GamePlatform::None) {
        auto platform_selection = new PlatformSelection();
        main_layout->addWidget(platform_selection);

        window->connect(platform_selection, &PlatformSelection::platformSelected, [&](GamePlatform selection){
            savePlatform(selection);
        });
    } else {
        auto platform_selection = new QLabel("Platform is :" + QString::number(getPlatform()));
        main_layout->addWidget(platform_selection);
    }

    window->setLayout(main_layout);

    window->show();

    return app.exec();
}