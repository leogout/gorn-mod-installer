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

    setLayout(config_layout);
}
