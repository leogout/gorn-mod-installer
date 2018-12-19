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

void writeToRegistry() {
    QSettings settings("Leogout", "Gorn Mods Installer");
    settings.setValue("platform", "aaa");
    std::cout << settings.value("zdzdz").toString().isNull();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto window = new QWidget;
    window->setMinimumSize(400, 100);
    window->setWindowTitle("GORN Mods Installer");
    window->setWindowIcon(QIcon(":/icon.png"));

    // Buttons
    auto save_button = new QPushButton("Save");
    auto render_button = new QPushButton("Render");

    // Image

    // Custom widgets
//    writeToRegistry();
    auto platform_selection = new PlatformSelection();

    // Layouts
    auto main_layout = new QHBoxLayout;
    auto config_layout = new QVBoxLayout;

    config_layout->addWidget(platform_selection);
    config_layout->addWidget(render_button);
    config_layout->addWidget(save_button);

    main_layout->addLayout(config_layout);

    window->setLayout(main_layout);

    // Connect
    window->connect(render_button, &QPushButton::pressed, [&]{
        std::cout << "Hello 1" << std::endl;
    });

    window->connect(save_button, &QPushButton::pressed, [&]{
        std::cout << "Hello 2" << std::endl;
    });

    window->show();

    return app.exec();
}