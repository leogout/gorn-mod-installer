#ifndef GORN_MOD_INSTALLER_PLATFORMSELECTION_H
#define GORN_MOD_INSTALLER_PLATFORMSELECTION_H

#include <QtCore/QArgument>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>

enum PlatformType { Steam, Oculus, None };

struct PlatformConfig {
    PlatformType platform;
    QString path;
};

class PlatformSelection : public QWidget {
    Q_OBJECT
    QMap<QString, PlatformConfig> m_platform_options;
    QComboBox* m_platform_input;
    QLineEdit* m_path_input;
    QPushButton* platform_button;
    QPushButton* m_path_button;
    void onPlatformSelected(const QString &text);
    void onPathButtonPressed();
    void onPlatformButtonPressed();
signals:
    void platformSelected(PlatformConfig platform);
public:
    explicit PlatformSelection();
};


#endif //GORN_MOD_INSTALLER_PLATFORMSELECTION_H
