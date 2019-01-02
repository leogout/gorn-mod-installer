//
// Created by F78478 on 02/01/2019.
//

#ifndef GORN_MOD_INSTALLER_DOWNLOADMANAGER_H
#define GORN_MOD_INSTALLER_DOWNLOADMANAGER_H


#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QHash>
#include <QtCore/QSignalMapper>

class DownloadManager  : public QObject {
    Q_OBJECT
    int m_id = 0;
    QNetworkAccessManager *m_nam;
    QSignalMapper *m_mapper;
    QHash<int, QNetworkReply*> m_replies;
public:
    DownloadManager();
    void get(QString url, std::function<void(QNetworkReply *)>);
};


#endif //GORN_MOD_INSTALLER_DOWNLOADMANAGER_H
