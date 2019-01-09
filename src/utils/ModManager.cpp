#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <src/utils/Registry.h>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QNetworkReply>
#include "ModManager.h"

/**
 * Downloads one file at a time for a given mod, recurse if it encounters a folder
 * Put the downloaded files in destination
 * @param mod
 * @param destination
 */
void ModManager::download(QString &mod, QString destination) {
    m_fetcher.get(m_baseurl + mod, [this, destination] (QNetworkReply* reply) {
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

/**
 * Downloads what lies behind a target url to GORN mods directory + file relative path. Creates directories if needed.
 * @param relative_path
 * @param destination
 */
void ModManager::downloadAndSave(QString relative_path, QString destination) {
    m_fetcher.get(m_baseurl + relative_path, [relative_path, destination] (QNetworkReply* reply) {
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

/**
 * Lists all the mods available in github's repository
 */
void ModManager::listAvailable() {
    m_fetcher.get(m_baseurl, [this] (QNetworkReply* reply) {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonArray root = document.array();
        QStringList list;
        for (auto obj: root) {
            list.push_back(obj.toObject().value("name").toString());
        }
        emit availableListed(list);
    });
}

void ModManager::listInstalled() {
    std::vector<QString> files;

    QDir mods_dir(QDir(Registry::getPlatformConfig().path).filePath("GORN_Data/mods"));
    QStringList list = mods_dir.entryList(QDir::AllEntries|QDir::NoDotAndDotDot);

    emit installedListed(list);
}


