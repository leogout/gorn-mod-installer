//
// Created by F78478 on 19/12/2018.
//

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QComboBox>
#include "PlatformSelection.h"

PlatformSelection::PlatformSelection() {
    auto config_layout = new QVBoxLayout;

    auto m_platform_input = new QComboBox();

    config_layout->addWidget(m_platform_input);

    QMap<QString, GamePlatform> platform_options;

    platform_options.insert("Oculus", GamePlatform::Oculus);
    platform_options.insert("Steam", GamePlatform::Steam);

    m_platform_input->addItems(QStringList(platform_options.keys()));

    setLayout(config_layout);
}
