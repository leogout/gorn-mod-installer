#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <iostream>
#include <QtWidgets/QFileDialog>
#include <src/utils/ModManager.h>
#include <QtWidgets/QMessageBox>
#include <src/utils/Registry.h>
#include "PlatformSelection.h"

PlatformSelection::PlatformSelection(ModManager* mod_manager): m_mod_manager(mod_manager) {
    auto config_layout = new QVBoxLayout;
    auto path_layout = new QHBoxLayout;

    m_platform_input = new QComboBox();
    m_platform_button = new QPushButton("Ok");

    m_path_input = new QLineEdit(R"(C:\Program Files (x86)\Oculus Apps\Software\devolver-digital-gorn)");
    m_path_button = new QPushButton("...");
    m_path_button->setMaximumWidth(40);

    path_layout->addWidget(m_path_input);
    path_layout->addWidget(m_path_button);

    config_layout->addWidget(m_platform_input);
    config_layout->addLayout(path_layout);
    config_layout->addWidget(m_platform_button);

    // @todo check default Oculus path
    m_platform_options.insert("Oculus", PlatformConfig{PlatformType::Oculus, R"(C:\Program Files (x86)\Oculus Apps\Software\devolver-digital-gorn)"});
    m_platform_options.insert("Steam", PlatformConfig{PlatformType::Steam, R"(C:\Program Files (x86)\Steam\steamapps\common\GORN)"});

    m_platform_input->addItems(QStringList(m_platform_options.keys()));

    setLayout(config_layout);

    connect(m_platform_input, qOverload<const QString &>(&QComboBox::currentTextChanged), this, &PlatformSelection::onPlatformSelected);
    connect(m_path_button, &QPushButton::pressed, this, &PlatformSelection::onPathButtonPressed);
    connect(m_platform_button, &QPushButton::pressed, this, &PlatformSelection::onPlatformButtonPressed);
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

    if (gorn_path.isEmpty()) {
        return;
    }

    m_path_input->setText(gorn_path);
}

void PlatformSelection::onPlatformButtonPressed() {
    PlatformType platform = m_platform_options[m_platform_input->currentText()].platform;
    QString path = m_path_input->text();

    PlatformConfig config{platform, path};

    QString assembly_path = QDir(config.path).filePath("GORN_Data/Managed/Assembly-CSharp.dll");
    QString assembly_backup_path = QDir(config.path).filePath("GORN_Data/Managed/Assembly-CSharp.backup.dll");

    // @todo check for writing permission
    // @todo download MemeLoader from github directly
    // Check if destination file exists
    if (not QFile::exists(assembly_path)) {
        QMessageBox::critical(this, "Incorrect GORN path", "The file \"" + assembly_path + "\" does not exist.");
    }

    Registry::savePlatformConfig(config);

    // backup files
    QMessageBox::StandardButton reply = (QMessageBox::StandardButton) QMessageBox::question(
            this,
            "Backup", "Do you want to create a backup of your game files ?",
            QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (QFile::exists(assembly_backup_path)) {
            QFile::remove(assembly_backup_path);
        }
        QFile::copy(assembly_path, assembly_backup_path);
    }

    QString platform_str(config.platform == PlatformType::Oculus ? "oculus" : "steam");
    m_mod_manager->download("MemeLoader/" + platform_str, config.path);

    QMessageBox::information(this, "Success", "You can start installing mods now.");

    emit platformSelected();
}