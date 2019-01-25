//
// Created by F78478 on 22/01/2019.
//

#include "FileDownloader.h"
#include <QtCore/QTemporaryFile>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QEventLoop>

void FileDownloader::download(QString url) {
    QNetworkReply* reply = m_nam.get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, this, &FileDownloader::onDownloadFinished);
}

void FileDownloader::onDownloadFinished() {
    auto reply = (QNetworkReply*) QObject::sender();

    if (reply->error() != QNetworkReply::NetworkError::NoError) {
        emit error(Error::NetworkError);
        return;
    }

    auto file = new QTemporaryFile;

    if (not file->open()) {
        emit error(Error::FileSystemError);
        return;
    }

    emit success(file);

    reply->deleteLater();
}

FileDownloader::FileDownloader(QObject *parent) : QObject(parent) {}

FileDownloader::FileDownloader() = default;
