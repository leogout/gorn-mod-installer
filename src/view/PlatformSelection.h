#ifndef GORN_MOD_INSTALLER_PLATFORMSELECTION_H
#define GORN_MOD_INSTALLER_PLATFORMSELECTION_H

#include <QtCore/QArgument>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>

enum GamePlatform { Steam, Oculus, None };

struct PlatformPath {
    GamePlatform platform;
    QString path;
};

class PlatformSelection : public QWidget {
    Q_OBJECT
public:
    explicit PlatformSelection();

private:
    QComboBox* m_platform_input;
    QPushButton* m_platform_button;
    QLineEdit* m_path_input;
    QPushButton* m_path_button;
    QMap<QString, PlatformPath> m_platform_options;
signals:
    void platformSelected(GamePlatform platform);
};


#endif //GORN_MOD_INSTALLER_PLATFORMSELECTION_H
