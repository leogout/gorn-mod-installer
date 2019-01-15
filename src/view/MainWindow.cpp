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
    auto main_layout = new QVBoxLayout;
    auto stacked_widget = new QStackedWidget;
    auto signature_label = new QLabel();
    signature_label->setText("Author: <a href=\"https://github.com/leogout\">leogout</a>");
    signature_label->setTextFormat(Qt::RichText);
    signature_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    signature_label->setOpenExternalLinks(true);
    signature_label->setAlignment(Qt::AlignCenter);

    stacked_widget->addWidget(platform_selection);
    stacked_widget->addWidget(mods_selection);

    PlatformConfig config = Registry::getPlatformConfig();
    if (config.platform == PlatformType::None) {
        stacked_widget->setCurrentWidget(platform_selection);
    } else {
        stacked_widget->setCurrentWidget(mods_selection);
    }

    connect(platform_selection, &PlatformSelection::platformSelected, [this, stacked_widget, mods_selection](PlatformConfig config){
        bool ok = MemeLoaderInstaller::install(this, config);
         if (ok) {
             stacked_widget->setCurrentWidget(mods_selection);
         }
    });

    main_layout->addWidget(stacked_widget);
    main_layout->addWidget(signature_label);

    setMinimumSize(400, 100);
    setWindowTitle("GORN Mods Installer");
    setWindowIcon(QIcon(":/icon.png"));
    setLayout(main_layout);
}
