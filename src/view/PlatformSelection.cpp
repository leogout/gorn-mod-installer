#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <iostream>
#include "PlatformSelection.h"

PlatformSelection::PlatformSelection() {
    auto config_layout = new QVBoxLayout;

    m_platform_input = new QComboBox();
    m_platform_button = new QPushButton("Ok");

    config_layout->addWidget(m_platform_input);
    config_layout->addWidget(m_platform_button);

    m_platform_options.insert("Oculus", GamePlatform::Oculus);
    m_platform_options.insert("Steam", GamePlatform::Steam);

    m_platform_input->addItems(QStringList(m_platform_options.keys()));

    connect(m_platform_button, &QPushButton::pressed, [&]{
        QString selected_platform = m_platform_input->currentText();
        emit platformSelected(m_platform_options[selected_platform]);
    });

    setLayout(config_layout);
}
