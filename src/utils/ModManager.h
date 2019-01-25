#ifndef GORN_MOD_INSTALLER_MODDOWNLOADER_H
#define GORN_MOD_INSTALLER_MODDOWNLOADER_H


#include <QtCore/QString>
#include <QtCore/QStringList>
#include "FileDownloader.h"
#include "RepositoryApi.h"

class ModManager : public QObject {
    Q_OBJECT
    FileDownloader* m_file_downloader;
    RepositoryApi* m_repository_api;

    void downloadAndSave(QString mod, QString destination);
public:
    ModManager(QObject *parent);

    void download(QString mod, QString destination);
    void listAvailable();
    void listInstalled();
    void remove(QString mod);
signals:
    void availableListed(QStringList list);
    void installedListed(QStringList list);
    void progress(QString file, int percentage);
    void installed();
    void removed();
};

#endif //GORN_MOD_INSTALLER_MODDOWNLOADER_H
