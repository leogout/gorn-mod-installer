#include <QtWidgets/QVBoxLayout>
#include <src/utils/Registry.h>
#include <QtWidgets/QStackedWidget>
#include <src/MemeLoaderInstaller.h>
#include "MainWindow.h"
#include "PlatformSelection.h"
#include "ModsSelection.h"

MainWindow::MainWindow() {
    //Registry::unsetPlatform(); // <- for testing purposes
    m_stacked_widget = new QStackedWidget;
    m_platform_selection = new PlatformSelection;
    m_mods_selection = new ModsSelection;

    auto main_layout = new QVBoxLayout;
    auto signature_label = new QLabel();
    signature_label->setText("Author: <a href=\"https://github.com/leogout\">leogout</a>");
    signature_label->setTextFormat(Qt::RichText);
    signature_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    signature_label->setOpenExternalLinks(true);
    signature_label->setAlignment(Qt::AlignCenter);

    m_stacked_widget->addWidget(m_platform_selection );
    m_stacked_widget->addWidget(m_mods_selection);

    PlatformConfig config = Registry::getPlatformConfig();
    if (config.platform == PlatformType::None) {
        m_stacked_widget->setCurrentWidget(m_platform_selection );
    } else {
        m_stacked_widget->setCurrentWidget(m_mods_selection);
    }

    main_layout->addWidget(m_stacked_widget);
    main_layout->addWidget(signature_label);

    setMinimumSize(400, 100);
    setWindowTitle("GORN Mods Installer");
    setWindowIcon(QIcon(":/icon.png"));
    setLayout(main_layout);

    connect(m_platform_selection, &PlatformSelection::platformSelected, this, &MainWindow::onPlatformSelected);
}

void MainWindow::onPlatformSelected(PlatformConfig config) {
    bool ok = MemeLoaderInstaller::install(this, config);
    if (ok) {
        m_stacked_widget->setCurrentWidget(m_mods_selection);
    }
}
