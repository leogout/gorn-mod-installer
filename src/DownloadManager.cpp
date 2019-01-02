//
// Created by F78478 on 02/01/2019.
//

#include <QtNetwork/QNetworkReply>
#include "DownloadManager.h"

DownloadManager::DownloadManager() {
    m_nam = new QNetworkAccessManager();
    m_mapper = new QSignalMapper();
    m_replies = QHash<int, QNetworkReply*>();
}

void DownloadManager::get(QString url, std::function<void(QNetworkReply *)> callback) {
    int id = m_id++;
    QNetworkReply *reply = m_nam->get(QNetworkRequest(QUrl(url)));
    m_replies.insert(id, reply);

    connect(reply, &QNetworkReply::finished, this, [&, id, callback]() {
        QNetworkReply *r = m_replies.take(id);

        callback(r);

        r->deleteLater();
    });
}


