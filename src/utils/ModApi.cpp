#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <src/utils/Registry.h>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QNetworkReply>
#include "ModApi.h"

/**
 * Downloads one file at a time for a given mod, recurse if it encounters a folder
 * Put the downloaded files in destination
 * @param mod
 * @param destination
 */
void ModApi::download(QString &mod, QString &destination) {
    m_fetcher.get(m_baseurl + mod, [this] (QNetworkReply* reply) {
        qDebug() << "Received.";
        QJsonArray rootObj = QJsonDocument::fromJson(reply->readAll()).array();

        for (auto obj: rootObj) {
            QString type = obj.toObject().value("type").toString();
            QString relative_path = obj.toObject().value("path").toString();

            if (type == "dir") {
                qDebug() << "Directory found, recursing...";
                download(relative_path, destination);
            } else if (type == "file") {
                qDebug() << "File found, downloading...";
                downloadAndSave(relative_path, destination);
            } else {
                qDebug() << "Unknown type: " << type;
            }
        }
    });
}

void ModApi::downloadAndSave(QString &relative_path, QString &destination) {
    m_fetcher.get(m_baseurl + relative_path, [relative_path] (QNetworkReply* reply) {
        QString dest_path = QDir(destination).filePath(relative_path);
        QFile file(QDir(destination).filePath(relative_path));

        // creates directory if it does not exist
        QDir(QFileInfo(file).absoluteDir()).mkpath(".");

        // @todo check if open went well
        file.open(QIODevice::WriteOnly);
        file.write(reply->readAll());
        file.close();
    });
}

void ModApi::list(std::function<void(std::vector<QString>)> callback) {
    m_fetcher.get(m_baseurl, [callback] (QNetworkReply* reply) {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonArray root = document.array();
        std::vector<QString> list;
        for (auto obj: root) {
            list.push_back(obj.toObject().value("name").toString());
        }

        callback(list);
    });
}


