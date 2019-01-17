#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <iostream>
#include <QtWidgets/QFileDialog>
#include "PlatformSelection.h"

PlatformSelection::PlatformSelection() {
    auto config_layout = new QVBoxLayout;
    auto path_layout = new QHBoxLayout;

    m_platform_input = new QComboBox();
    platform_button = new QPushButton("Ok");

    m_path_input = new QLineEdit(R"(C:\Program Files (x86)\Oculus Apps\Software\devolver-digital-gorn)");
    m_path_button = new QPushButton("...");
    m_path_button->setMaximumWidth(40);

    path_layout->addWidget(m_path_input);
    path_layout->addWidget(m_path_button);

    config_layout->addWidget(m_platform_input);
    config_layout->addLayout(path_layout);
    config_layout->addWidget(platform_button);

    // @todo check default Oculus path
    m_platform_options.insert("Oculus", PlatformConfig{PlatformType::Oculus, R"(C:\Program Files (x86)\Oculus Apps\Software\devolver-digital-gorn)"});
    m_platform_options.insert("Steam", PlatformConfig{PlatformType::Steam, R"(C:\Program Files (x86)\Steam\steamapps\common\GORN)"});

    m_platform_input->addItems(QStringList(m_platform_options.keys()));

    setLayout(config_layout);

    connect(m_platform_input, qOverload<const QString &>(&QComboBox::currentTextChanged), this, &PlatformSelection::onPlatformSelected);
    connect(m_path_button, &QPushButton::pressed, this, &PlatformSelection::onPathButtonPressed);
    connect(platform_button, &QPushButton::pressed, this, &PlatformSelection::onPlatformButtonPressed);
}

void PlatformSelection::onPlatformSelected(const QString &text) {
    PlatformConfig config = m_platform_options[m_platform_input->currentText()];
    m_path_input->setText(config.path);
}

void PlatformSelection::onPathButtonPressed() {
    QString gorn_path = QFileDialog::getExistingDirectory(
            this,
            "Select GORN directory",
            ".",
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    // @Todo add validator to check the correctness of the directory based on its content.
    if (gorn_path.isEmpty()) {
        return;
    }

    m_path_input->setText(gorn_path);
}

void PlatformSelection::onPlatformButtonPressed() {
    PlatformType platform = m_platform_options[m_platform_input->currentText()].platform;
    QString path = m_path_input->text();
    emit platformSelected(PlatformConfig {platform, path});
}