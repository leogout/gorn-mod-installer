#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <iostream>
#include <QtWidgets/QFileDialog>
#include "PlatformSelection.h"

PlatformSelection::PlatformSelection() {
    auto platform_options = new QMap<QString, PlatformConfig>;
    auto config_layout = new QVBoxLayout;
    auto path_layout = new QHBoxLayout;

    auto platform_input = new QComboBox();
    auto platform_button = new QPushButton("Ok");

    auto path_input = new QLineEdit(R"(C:\Program Files (x86)\Oculus Apps\Software\devolver-digital-gorn)");
    auto path_button = new QPushButton("...");
    path_button->setMaximumWidth(40);

    path_layout->addWidget(path_input);
    path_layout->addWidget(path_button);

    config_layout->addWidget(platform_input);
    config_layout->addLayout(path_layout);
    config_layout->addWidget(platform_button);

    // @todo check default Oculus path
    platform_options->insert("Oculus", PlatformConfig{PlatformType::Oculus, R"(C:\Program Files (x86)\Oculus Apps\Software\devolver-digital-gorn)"});
    platform_options->insert("Steam", PlatformConfig{PlatformType::Steam, R"(C:\Program Files (x86)\Steam\steamapps\common\GORN)"});

    platform_input->addItems(QStringList(platform_options->keys()));

    connect(platform_input, qOverload<const QString &>(&QComboBox::currentTextChanged), [platform_options, path_input, platform_input](const QString &text){
        PlatformConfig config = (*platform_options)[platform_input->currentText()];
        path_input->setText(config.path);
    });

    connect(path_button, &QPushButton::pressed, [this, path_input]{
        QString gorn_path = QFileDialog::getExistingDirectory(
                this,
                "Select GORN directory",
                ".",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        // @Todo add validator to check the correctness of the directory based on its content.
        if (gorn_path.isEmpty()) {
            return;
        }
        
        path_input->setText(gorn_path);
    });

    connect(platform_button, &QPushButton::pressed, [this, platform_options, path_input, platform_input]{
        PlatformType platform = (*platform_options)[platform_input->currentText()].platform;
        QString path = path_input->text();
        emit platformSelected(PlatformConfig {platform, path});
    });

    setLayout(config_layout);
}
