#ifndef GORN_MOD_INSTALLER_PLATFORMSELECTION_H
#define GORN_MOD_INSTALLER_PLATFORMSELECTION_H

#include <QtCore/QArgument>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <src/utils/ModManager.h>

enum PlatformType { Steam, Oculus, None };

struct PlatformConfig {
    PlatformType platform;
    QString path;
};

class PlatformSelection : public QWidget {
    Q_OBJECT
    QMap<QString, PlatformConfig> m_platform_options;
    ModManager* m_mod_manager;
    QComboBox* m_platform_input;
    QLineEdit* m_path_input;
    QPushButton* m_platform_button;
    QPushButton* m_path_button;
    void onPlatformSelected(const QString &text);
    void onPathButtonPressed();
    void onPlatformButtonPressed();
signals:
    void platformSelected();
public:
    explicit PlatformSelection(ModManager* mod_manager);
};


#endif //GORN_MOD_INSTALLER_PLATFORMSELECTION_H
