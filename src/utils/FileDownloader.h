//
// Created by F78478 on 22/01/2019.
//

#ifndef GORN_MOD_INSTALLER_FILEDOWNLOADER_H
#define GORN_MOD_INSTALLER_FILEDOWNLOADER_H


#include <QtCore/QTemporaryFile>
#include <QtNetwork/QNetworkAccessManager>
#include "Fetcher.h"

class FileDownloader : public QObject {
    Q_OBJECT
    QNetworkAccessManager m_nam;
    void onDownloadFinished();
public:
    enum Error { NetworkError, FileSystemError };
    void download(QString url);
signals:
    void success(QTemporaryFile* file);
    void error(FileDownloader::Error err);
};


#endif //GORN_MOD_INSTALLER_FILEDOWNLOADER_H
