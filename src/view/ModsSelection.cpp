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
#include <src/utils/Fetcher.h>
#include "ModsSelection.h"
#include "PlatformSelection.h"

ModsSelection::ModsSelection() {
    auto main_layout = new QVBoxLayout;
    auto lists_layout = new QHBoxLayout;
    auto buttons_layout = new QHBoxLayout;

    m_mod_manager = new ModManager;
    m_installed_list_widget = new QListWidget;
    m_available_list_widget = new QListWidget;
    m_remove_button = new QPushButton("Remove");
    m_install_button = new QPushButton("Install");

    lists_layout->addWidget(m_installed_list_widget);
    lists_layout->addWidget(m_available_list_widget);
    buttons_layout->addWidget(m_remove_button);
    buttons_layout->addWidget(m_install_button);
    main_layout->addLayout(lists_layout);
    main_layout->addLayout(buttons_layout);

    setLayout(main_layout);

    connect(m_mod_manager, &ModManager::availableListed, [this] (QStringList list) {
        m_available_list_widget->clear();
        for (auto &mod: list) {
            new QListWidgetItem(mod, m_available_list_widget);
        }
    });

    connect(m_mod_manager, &ModManager::installedListed, [this] (QStringList list) {
        m_installed_list_widget->clear();
        for (auto &mod: list) {
            new QListWidgetItem(mod, m_installed_list_widget);
        }
    });

    connect(m_mod_manager, &ModManager::installed, [this] {
        m_mod_manager->listInstalled(); // called to update the list of installed mods
    });

    connect(m_mod_manager, &ModManager::removed, [this] {
        m_mod_manager->listInstalled(); // called to update the list of installed mods
    });

    connect(m_remove_button, &QPushButton::pressed, [this]{
        QString mod = m_installed_list_widget->currentItem()->text();
        qDebug() << mod;
        m_mod_manager->remove(mod);
    });

    connect(m_install_button, &QPushButton::pressed, [this]{
        QString mod = m_available_list_widget->currentItem()->text();
        QString destination = QDir(Registry::getPlatformConfig().path).filePath("GORN_Data/mods");
        m_mod_manager->download(mod, destination);
    });
}

void ModsSelection::showEvent(QShowEvent *event) {
    if (event->spontaneous()){
        qDebug() << "Issued by the system";
        return;
    }

    qDebug() << "doing";

    m_mod_manager->listAvailable();
    m_mod_manager->listInstalled();

    qDebug() << "done";
}

