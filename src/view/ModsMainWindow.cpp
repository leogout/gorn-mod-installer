#include <iostream>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtWidgets/QVBoxLayout>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <src/utils/Registry.h>
#include <src/utils/Fetcher.h>
#include "ModsMainWindow.h"
#include "PlatformSelection.h"

ModsMainWindow::ModsMainWindow() {
    auto main_layout = new QVBoxLayout();
    auto lists_layout = new QHBoxLayout();

    m_installed_list_widget = new QListWidget;
    m_available_list_widget = new QListWidget;
    m_install_button = new QPushButton("Install");

    lists_layout->addWidget(m_installed_list_widget);
    lists_layout->addWidget(m_available_list_widget);
    main_layout->addLayout(lists_layout);
    main_layout->addWidget(m_install_button);

    setLayout(main_layout);

    m_api.list([this] (std::vector<QString> list) {
        for (auto &mod: list) {
            new QListWidgetItem(mod, m_available_list_widget);
        }
    });

    connect(m_install_button, &QPushButton::pressed, [this]{
        QString mod = m_available_list_widget->currentItem()->text();
        QString destination = QDir(Registry::getPlatformConfig().path).filePath("GORN_Data/mods");
        m_api.download(mod, destination);
    });
}
