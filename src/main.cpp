#include <iostream>
#include <QtCore/QtConfig>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto window = new QWidget;
    window->setWindowTitle("GORN Mods Installer");
    window->setWindowIcon(QIcon(":/icon.png"));

    // Buttons
    auto save_button = new QPushButton("Save");
    auto render_button = new QPushButton("Render");

    // Image
    auto image_zone = new QLabel;

    // Custom widgets


    // Layouts
    auto main_layout = new QHBoxLayout;
    auto config_layout = new QVBoxLayout;

    config_layout->addWidget(render_button);
    config_layout->addWidget(save_button);

    main_layout->addLayout(config_layout);
    main_layout->addWidget(image_zone);

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