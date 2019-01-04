#include <iostream>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtWidgets/QVBoxLayout>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <src/Registry.h>
#include <src/DownloadManager.h>
#include "ModsMainWindow.h"
#include "PlatformSelection.h"

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

    m_dm.get("https://api.github.com/repos/leogout/gorn-mod-installer/contents/mods", [&] (QNetworkReply* reply) {
        qDebug() << "Initial download succeeded.";
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonArray rootObj = document.array();

        for (auto obj: rootObj) {
            new QListWidgetItem(obj.toObject().value("name").toString(), m_available_list_widget);
        }
    });

    connect(m_install_button, &QPushButton::pressed, [&]{
        QString url = "https://api.github.com/repos/leogout/gorn-mod-installer/contents/mods/" + m_available_list_widget->currentItem()->text();
        recursiveDownload(url);
    });
}

void ModsMainWindow::recursiveDownload(QString &url) {
    m_dm.get(url, [&] (QNetworkReply* reply) {
        QJsonArray rootObj = QJsonDocument::fromJson(reply->readAll()).array();

        for (auto obj: rootObj) {
            // @todo check if it is a directory and recurse if it is
            QString url = obj.toObject().value("download_url").toString();
            QString type = obj.toObject().value("type").toString();
            QString filename = obj.toObject().value("name").toString();

            qDebug() << type;
        }
    });
}

void saveFile(QString filename, QNetworkReply* reply) {
    //QString mods_path = QDir(Registry::getPlatformConfig().path).filePath("GORN_Data/mods");
    QString mods_path = QDir("C:/Users/F78478/Documents/projects/gorn-mod-installer/cmake-build-debug").filePath("GORN_Data/mods");
    QFile file(QDir(mods_path).filePath(filename));
    // @todo check if open went well
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    file.close();
}