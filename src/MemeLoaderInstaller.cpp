#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtWidgets/QMessageBox>
#include <src/view/PlatformSelection.h>
#include "MemeLoaderInstaller.h"
#include "utils/Registry.h"

void MemeLoaderInstaller::install(QWidget* parent, PlatformConfig config) {
    QString destination_path = QDir(config.path).filePath("GORN_Data/Managed/Assembly-CSharp.dll");
    QString backup_path = QDir(config.path).filePath("GORN_Data/Managed/Assembly-CSharp.backup.dll");
    QString readme_path = QDir(config.path).filePath("GORN_Data/mods/MemeLoader/README.txt");
    QString uiobject_path = QDir(config.path).filePath("GORN_Data/mods/MemeLoader/models/uiobject.asset");
    QString loader_path = QDir(config.path).filePath("GORN_Data/mods/MemeLoader/models/loader.meme");



    // @todo check for writing permission
    // @todo download MemeLoader from github directly
    // Check if destination file exists
    if (not QFile::exists(destination_path)) {
        QMessageBox::critical(parent, "Incorrect GORN path", "The file \"" + destination_path + "\" does not exist.");
        return;
    }

    // Remove backup file if needed
    if (QFile::exists(backup_path)) {
        QMessageBox::StandardButton reply = (QMessageBox::StandardButton) QMessageBox::question(
                parent,
                "Backup file already exists", "The file \"" + backup_path + "\" already exists, do you want to replace it ?",
                QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            QFile::remove(backup_path);
        }
    }

    // Creates folders hierarchy
    QDir(QDir(config.path).filePath("GORN_Data/mods/MemeLoader/models")).mkpath(".");

    // Copy is performed only if the file does not already exist, no risk to replace the destination files
    QFile::copy(destination_path, backup_path);
    QFile::remove(destination_path);
    QFile::copy(config.platform == PlatformType::Oculus ?
                ":/memeloader/oculus.dll" :
                ":/memeloader/steam.dll",
                destination_path);
    QFile::copy(":/memeloader/README.txt", readme_path);
    QFile::copy(":/memeloader/uiobject.asset", uiobject_path);
    QFile::copy(":/memeloader/loader.meme", loader_path);

    Registry::savePlatformConfig(config);

    QMessageBox::information(parent, "Success", "MemeLoader has been added to GORN successfully.");
}
