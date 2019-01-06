//
// Created by leogout on 1/6/2019.
//

#include <QtWidgets/QHBoxLayout>
#include <src/utils/Registry.h>
#include <QtWidgets/QStackedWidget>
#include <src/MemeLoaderInstaller.h>
#include "MainWindow.h"
#include "PlatformSelection.h"
#include "ModsSelection.h"

MainWindow::MainWindow() {
    //Registry::unsetPlatform(); // <- for testing purposes

    m_platform_selection = new PlatformSelection();
    m_mods_selection = new ModsSelection();

    m_stacked_widget = new QStackedWidget;
    m_stacked_widget->addWidget(m_platform_selection);
    m_stacked_widget->addWidget(m_mods_selection);

    PlatformConfig config = Registry::getPlatformConfig();
    if (config.platform == PlatformType::None) {
        m_stacked_widget->setCurrentWidget(m_platform_selection);
    } else {
        m_stacked_widget->setCurrentWidget(m_mods_selection);
    }

    connect(m_platform_selection, &PlatformSelection::platformSelected, [this](PlatformConfig config){
        MemeLoaderInstaller::install(this, config);
        // @todo check if installation went OK
        m_stacked_widget->setCurrentWidget(m_mods_selection);
    });

    auto main_layout = new QHBoxLayout;
    main_layout->addWidget(m_stacked_widget);

    setMinimumSize(400, 100);
    setWindowTitle("GORN Mods Installer");
    setWindowIcon(QIcon(":/icon.png"));
    setLayout(main_layout);
}
