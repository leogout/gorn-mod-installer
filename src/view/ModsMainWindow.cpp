#include <iostream>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtWidgets/QVBoxLayout>
#include "ModsMainWindow.h"

ModsMainWindow::ModsMainWindow() {
    m_network_manager = new QNetworkAccessManager(this);

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

    m_network_manager->get(QNetworkRequest(QUrl("https://api.github.com/repos/leogout/gorn-mod-installer/contents/mods")));

    connect(m_network_manager, &QNetworkAccessManager::finished, this, [&](QNetworkReply* reply){
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonArray rootObj = document.array();

        for (auto obj: rootObj) {
            new QListWidgetItem(obj.toObject().value("name").toString(), m_available_list_widget);
        }
    });

    connect(m_install_button, &QPushButton::pressed, [&]{
        m_network_manager->get(QNetworkRequest(QUrl("https://api.github.com/repos/leogout/gorn-mod-installer/contents/mods/" + m_installed_list_widget->currentItem()->text())));
    });
}
