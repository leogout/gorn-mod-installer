//
// Created by leogout on 12/23/2018.
//

#include <src/view/PlatformSelection.h>
#include <QtCore/QSettings>
#include "Registry.h"

PlatformConfig Registry::getPlatformConfig() {
    QSettings settings("Leogout", "Gorn Mods Installer");

    PlatformConfig config {
            (PlatformType) settings.value("config/platform", PlatformType::None).toInt(),
            settings.value("config/path").toString(),
    };

    return config;
}

void Registry::savePlatformConfig(PlatformConfig config) {
    QSettings settings("Leogout", "Gorn Mods Installer");
    settings.setValue("config/platform", config.platform);
    settings.setValue("config/path", config.path);
}

void Registry::unsetPlatform() {
    QSettings settings("Leogout", "Gorn Mods Installer");
    settings.remove("config/platform");
    settings.remove("config/path");
}