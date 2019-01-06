#ifndef GORN_MOD_INSTALLER_MODDOWNLOADER_H
#define GORN_MOD_INSTALLER_MODDOWNLOADER_H


#include <src/utils/Fetcher.h>
#include <QtCore/QString>

class ModApi {
    Fetcher m_fetcher;
    const QString m_baseurl = "https://api.github.com/repos/leogout/gorn-mod-gallery/contents";
    void downloadAndSave(QString &mod, QString &destination);
public:
    void download(QString &mod, QString &destination);
    void list(std::function<void(std::vector<QString>)> callback);
};

#endif //GORN_MOD_INSTALLER_MODDOWNLOADER_H
