#include <QtNetwork/QNetworkReply>
#include <iostream>
#include <QtCore/QEventLoop>
#include "Fetcher.h"

void Fetcher::get(QString url, std::function<void(QNetworkReply *)> callback) {
    int id = m_id++;
    QNetworkReply *reply = m_nam.get(QNetworkRequest(QUrl(url)));
    m_replies.insert(id, reply);

    connect(reply, &QNetworkReply::finished, this, [&, id, callback]() {
        QNetworkReply *r = m_replies.take(id);

        callback(r);

        r->deleteLater();
    });
}

void Fetcher::getSync(QString url, std::function<void(QNetworkReply *)> callback) {
    QNetworkReply *reply = m_nam.get(QNetworkRequest(QUrl(url)));

    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    callback(reply);

    reply->deleteLater();
}


