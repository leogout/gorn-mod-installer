//
// Created by leogout on 1/22/2019.
//

#ifndef GORN_MOD_INSTALLER_GITHUBAPI_H
#define GORN_MOD_INSTALLER_GITHUBAPI_H


class RepositoryApi : public QObject {
    Q_OBJECT
    QString m_baseurl;
    QNetworkAccessManager m_nam;
    void listFilesRecursive(QString directory, QStringList &list, int depth);
public:
    QStringList listFiles(QString directory, int depth=-1);
    QString getRepositoryUrl();
    RepositoryApi(QObject *parent, const QString &m_baseurl);
};


#endif //GORN_MOD_INSTALLER_GITHUBAPI_H
