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
signals:
    void platformSelected(PlatformConfig platform);
public:
    explicit PlatformSelection();
};


#endif //GORN_MOD_INSTALLER_PLATFORMSELECTION_H
