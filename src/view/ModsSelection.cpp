#include <iostream>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QShowEvent>
#include <QtCore/QJsonArray>
#include <QtWidgets/QVBoxLayout>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <src/utils/Registry.h>
#include "ModsSelection.h"
#include "PlatformSelection.h"

ModsSelection::ModsSelection(ModManager* mod_manager): m_mod_manager(mod_manager) {
    auto main_layout = new QVBoxLayout;
    auto lists_layout = new QHBoxLayout;
    auto progress_layout = new QVBoxLayout;
    auto buttons_layout = new QHBoxLayout;

    m_installed_list_widget = new QListWidget;
    m_available_list_widget = new QListWidget;
    m_install_label = new QLabel;
    m_install_progress = new QProgressBar;
    m_remove_button = new QPushButton("Remove");
    m_install_button = new QPushButton("Install");

    m_install_label->hide();
    m_install_progress->hide();

    lists_layout->addWidget(m_installed_list_widget);
    lists_layout->addWidget(m_available_list_widget);

    progress_layout->addWidget(m_install_label);
    progress_layout->addWidget(m_install_progress);

    buttons_layout->addWidget(m_remove_button);
    buttons_layout->addWidget(m_install_button);
    main_layout->addLayout(lists_layout);
    main_layout->addLayout(progress_layout);
    main_layout->addLayout(buttons_layout);

    setLayout(main_layout);

    connect(m_mod_manager, &ModManager::availableListed, this, &ModsSelection::onListAvailable);
    connect(m_mod_manager, &ModManager::installedListed, this, &ModsSelection::onListInstalled);

    connect(m_install_button, &QPushButton::pressed, this, &ModsSelection::onInstallPressed);
    connect(m_remove_button, &QPushButton::pressed, this, &ModsSelection::onRemovePressed);

    connect(m_mod_manager, &ModManager::progress, this, &ModsSelection::onProgress);
    connect(m_mod_manager, &ModManager::installed, this, &ModsSelection::onInstalled);
    connect(m_mod_manager, &ModManager::removed, this, &ModsSelection::onRemoved);
}

void ModsSelection::onListAvailable(QStringList list) {
    m_available_list_widget->clear();
    for (auto &mod: list) {
        new QListWidgetItem(mod, m_available_list_widget);
    }
}

void ModsSelection::onListInstalled(QStringList list) {
    m_installed_list_widget->clear();
    for (auto &mod: list) {
        new QListWidgetItem(mod, m_installed_list_widget);
    }
}

void ModsSelection::onRemoved() {
    m_mod_manager->listInstalled(); // called to update the list of installed mods
    enableButtons();
}

void ModsSelection::onInstalled() {
    m_install_label->hide();
    m_install_progress->hide();
    m_mod_manager->listInstalled(); // called to update the list of installed mods
    enableButtons();
}

void ModsSelection::onProgress(QString file, int percentage) {
    m_install_label->setText(file);
    m_install_progress->setValue(percentage);
}

void ModsSelection::onRemovePressed() {
    disableButtons();
    QString mod = m_installed_list_widget->currentItem()->text();
    m_mod_manager->remove(mod);
}

void ModsSelection::onInstallPressed() {
    disableButtons();
    m_install_label->setText("");
    m_install_progress->setValue(0);
    m_install_label->show();
    m_install_progress->show();
    QString mod = m_available_list_widget->currentItem()->text();
    QString destination = QDir(Registry::getPlatformConfig().path).filePath("GORN_Data/mods");
    m_mod_manager->download(mod, destination);
}

void ModsSelection::disableButtons() {
    m_install_button->setDisabled(true);
    m_remove_button->setDisabled(true);
}

void ModsSelection::enableButtons() {
    m_install_button->setEnabled(true);
    m_remove_button->setEnabled(true);
}

void ModsSelection::showEvent(QShowEvent *event) {
    if (event->spontaneous()){
        return;
    }

    m_mod_manager->listAvailable();
    m_mod_manager->listInstalled();
}

