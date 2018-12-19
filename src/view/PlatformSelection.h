//
// Created by F78478 on 19/12/2018.
//

#ifndef GORN_MOD_INSTALLER_PLATFORMSELECTION_H
#define GORN_MOD_INSTALLER_PLATFORMSELECTION_H

#include <QtCore/QArgument>
#include <QWidget>

enum GamePlatform { Steam, Oculus };

class PlatformSelection : public QWidget {
    Q_OBJECT
public:
    explicit PlatformSelection();
};


#endif //GORN_MOD_INSTALLER_PLATFORMSELECTION_H
