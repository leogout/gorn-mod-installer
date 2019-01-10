#ifndef GORN_MOD_INSTALLER_DOWNLOADMANAGER_H
#define GORN_MOD_INSTALLER_DOWNLOADMANAGER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QHash>
#include <QtCore/QSignalMapper>

class Fetcher : public QObject {
    Q_OBJECT
    int m_id = 0;
    QNetworkAccessManager m_nam;
    QHash<int, QNetworkReply*> m_replies;
public:
    void get(QString url, std::function<void(QNetworkReply *)>);
    void getSync(QString url, std::function<void(QNetworkReply *)>);
};

#endif //GORN_MOD_INSTALLER_DOWNLOADMANAGER_H
