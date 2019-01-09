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
    auto platform_selection = new PlatformSelection;
    auto mods_selection = new ModsSelection;
    auto main_layout = new QHBoxLayout;
    auto stacked_widget = new QStackedWidget;

    stacked_widget->addWidget(platform_selection);
    stacked_widget->addWidget(mods_selection);

    PlatformConfig config = Registry::getPlatformConfig();
    if (config.platform == PlatformType::None) {
        stacked_widget->setCurrentWidget(platform_selection);
    } else {
        stacked_widget->setCurrentWidget(mods_selection);
    }

    connect(platform_selection, &PlatformSelection::platformSelected, [this, stacked_widget, mods_selection](PlatformConfig config){
        MemeLoaderInstaller::install(this, config);
        // @todo check if installation went OK
        stacked_widget->setCurrentWidget(mods_selection);
    });

    main_layout->addWidget(stacked_widget);

    setMinimumSize(400, 100);
    setWindowTitle("GORN Mods Installer");
    setWindowIcon(QIcon(":/icon.png"));
    setLayout(main_layout);
}
