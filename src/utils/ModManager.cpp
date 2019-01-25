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
void ModManager::download(QString mod, QString destination) {
    // @todo separate files discovery and download
    QStringList list = m_repository_api->listFiles(mod);

    double i = 0;
    for (auto &file : list) {
        downloadAndSave(file, destination);
        i++;

        progress(file, static_cast<int>((i / list.size()) * 100));
    }

    qDebug() << "Installed.";
    emit installed();
}

/**
 * Downloads what lies behind a target url to GORN mods directory + file relative path. Creates directories if needed.
 * @param relative_path
 * @param destination
 */
void ModManager::downloadAndSave(QString relative_path, QString destination) {
    QStringList list = m_repository_api->listFiles(relative_path);

    for (auto &file : list) {
        m_file_downloader->download(m_repository_api->getRepositoryUrl() + relative_path);
        connect(m_file_downloader, &FileDownloader::success, this, [this, relative_path, destination] (QTemporaryFile* file) {
            QString dest_path = QDir(destination).filePath(relative_path);

            // creates directory if it does not exist
            QDir(dest_path).mkpath(".");

            // @todo check if copy went well
            file->copy(dest_path);
            file->close();
        });
    }
}

void ModManager::remove(QString mod) {
    QString mod_path = QDir(QDir(Registry::getPlatformConfig().path).filePath("GORN_Data/mods")).filePath(mod);
    QDir dir(mod_path);

    qDebug() << "Removing " << mod_path;

    dir.removeRecursively();

    emit removed();
}

/**
 * Lists all the mods available in github's repository
 */
void ModManager::listAvailable() {
    QStringList list = m_repository_api->listFiles(".", 1);

    list.removeOne("MemeLoader");

    emit availableListed(list);
}

/**
 * Lists all the mods installed in user's directory
 */
void ModManager::listInstalled() {
    QDir mods_dir(QDir(Registry::getPlatformConfig().path).filePath("GORN_Data/mods"));
    QStringList list = mods_dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot);

    list.removeOne("MemeLoader");

    emit installedListed(list);
}

ModManager::ModManager(QObject *parent) :
    QObject(parent),
    m_file_downloader(new FileDownloader(this)),
    m_repository_api(new RepositoryApi(this, "https://api.github.com/repos/leogout/gorn-mod-gallery/contents/")) {}
