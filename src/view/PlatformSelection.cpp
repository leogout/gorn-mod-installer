#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <iostream>
#include <QtWidgets/QFileDialog>
#include "PlatformSelection.h"

PlatformSelection::PlatformSelection() {
    auto config_layout = new QVBoxLayout;

    m_platform_input = new QComboBox();
    m_platform_button = new QPushButton("Ok");

    m_path_input = new QLineEdit("default/path/to/oculus/gorn");
    m_path_button = new QPushButton("...");

    config_layout->addWidget(m_platform_input);
    config_layout->addWidget(m_path_input);
    config_layout->addWidget(m_path_button);
    config_layout->addWidget(m_platform_button);

    m_platform_options.insert("Oculus", PlatformPath{GamePlatform::Oculus, "default/path/to/oculus/gorn"});
    m_platform_options.insert("Steam", PlatformPath{GamePlatform::Steam, R"(C:\Program Files (x86)\Steam\steamapps\common\GORN)"});

    m_platform_input->addItems(QStringList(m_platform_options.keys()));

    connect(m_platform_input, qOverload<const QString &>(&QComboBox::currentTextChanged), [&](const QString &text){
        PlatformPath selection = m_platform_options[m_platform_input->currentText()];
        m_path_input->setText(selection.path);
    });

    connect(m_path_button, &QPushButton::pressed, [&]{
        PlatformPath selection = m_platform_options[m_platform_input->currentText()];
        QString gorn_path = QFileDialog::getExistingDirectory(
                this,
                "Select GORN directory",
                ".",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        // @Todo add validator to check the correctness of the directory based on its content.
        // @Todo May contain different things depending on the platform (oculus vs steam).
        m_path_input->setText(gorn_path);
    });

    connect(m_platform_button, &QPushButton::pressed, [&]{
        PlatformPath selection = m_platform_options[m_platform_input->currentText()];
        emit platformSelected(selection.platform);
    });

    setLayout(config_layout);
}
