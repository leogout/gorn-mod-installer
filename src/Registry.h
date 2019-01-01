//
// Created by leogout on 12/23/2018.
//

#ifndef GORN_MOD_INSTALLER_REGISTRY_H
#define GORN_MOD_INSTALLER_REGISTRY_H

#include "view/PlatformSelection.h"

class Registry {
public:
    static void unsetPlatform();
    static void savePlatformConfig(PlatformConfig config);
    static PlatformConfig getPlatformConfig();
};


#endif //GORN_MOD_INSTALLER_REGISTRY_H
