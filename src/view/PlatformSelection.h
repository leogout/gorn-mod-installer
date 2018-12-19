#ifndef GORN_MOD_INSTALLER_PLATFORMSELECTION_H
#define GORN_MOD_INSTALLER_PLATFORMSELECTION_H

#include <QtCore/QArgument>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>

enum GamePlatform { Steam, Oculus, None };

class PlatformSelection : public QWidget {
    Q_OBJECT
public:
    explicit PlatformSelection();

private:
    QComboBox* m_platform_input;
    QPushButton* m_platform_button;
    QMap<QString, GamePlatform> m_platform_options;
signals:
    void platformSelected(GamePlatform platform);
};


#endif //GORN_MOD_INSTALLER_PLATFORMSELECTION_H
