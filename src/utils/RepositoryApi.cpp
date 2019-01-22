#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QEventLoop>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include "RepositoryApi.h"

void RepositoryApi::listFilesRecursive(QString directory, QStringList &list, int depth) {
    if (depth == 0) {
        return;
    }

    QNetworkReply *reply = m_nam.get(QNetworkRequest(QUrl(m_baseurl + directory)));

    // synchronous call logic
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QJsonArray rootObj = QJsonDocument::fromJson(reply->readAll()).array();

    for (auto obj : rootObj) {
        QString type = obj.toObject().value("type").toString();
        QString relative_path = obj.toObject().value("path").toString();

        if (type == "dir") {
            qDebug() << "Directory found, recursing...";
            listFilesRecursive(relative_path, list, depth - 1);
        } else if (type == "file") {
            qDebug() << "File found, added to download list...";
            list.push_back(relative_path);
        } else {
            qDebug() << "Unknown type: " << type;
        }
    }

    reply->deleteLater();
}

QStringList RepositoryApi::listFiles(QString directory, int depth=-1) {
    QStringList list;
    listFilesRecursive(directory, list, depth);
}

RepositoryApi::RepositoryApi(QObject *parent, const QString &m_baseurl) : QObject(parent), m_baseurl(m_baseurl) {}
