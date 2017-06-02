#include "qtwebview.h"


MainWindow::MainWindow(QtHttpDdos *parent)
{
    setupUi(this);

    //初始化qthttpddos
    m_pHttpDdos = parent;
    m_pNetworkManager = new QNetworkAccessManager();
    m_pNetworkReply = NULL;


    addressEdit = new QLineEdit;
    tbAddress->insertWidget(actionGo, new QLabel(tr("Address")));
    tbAddress->insertWidget(actionGo, addressEdit);

    connect(addressEdit, SIGNAL(returnPressed()), actionGo, SLOT(trigger()));
    connect(actionBack, SIGNAL(triggered()), WebBrowser, SLOT(GoBack()));
    connect(actionForward, SIGNAL(triggered()), WebBrowser, SLOT(GoForward()));
    connect(actionStop, SIGNAL(triggered()), WebBrowser, SLOT(Stop()));
    connect(actionRefresh, SIGNAL(triggered()), WebBrowser, SLOT(Refresh()));
    connect(actionHome, SIGNAL(triggered()), WebBrowser, SLOT(GoHome()));
    connect(actionSearch, SIGNAL(triggered()), WebBrowser, SLOT(GoSearch()));
    connect(WebBrowser, SIGNAL(signal(const QString&, int, void*)), this, SLOT(slot(const QString&, int, void*)));
    //    pb = new QProgressBar(statusBar());
    //    pb->setTextVisible(false);
    //    pb->hide();
    //    statusBar()->addPermanentWidget(pb);

    connect(&locationActionMapper, SIGNAL(mapped(QString)), this, SLOT(navigate(QString)));

    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray restoredGeometry = settings.value(QLatin1String(geometryKey)).toByteArray();
    if (restoredGeometry.isEmpty() || !restoreGeometry(restoredGeometry)) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        const QSize size = (availableGeometry.size() * 4) / 5;
        resize(size);
        move(availableGeometry.center() - QPoint(size.width(), size.height()) / 2);
    }
    //    const QString restoredVersion = settings.value(QLatin1String(versionKey)).toString();
    //    QList<Location> bookmarks = readBookMarks(settings);
    ////    if (bookmarks.isEmpty() || restoredVersion.isEmpty())
    ////        bookmarks = defaultBookmarks();
    ////    foreach (const Location &bookmark, bookmarks)
    ////        addBookmark(bookmark);

}

//! [1]

MainWindow::~MainWindow()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());
    saveBookMarks(bookmarks(), settings);
    settings.setValue(QLatin1String(versionKey), QLatin1String(QT_VERSION_STR));
    settings.setValue(QLatin1String(geometryKey), saveGeometry());
}

QAction *MainWindow::addLocation(const Location &location, QMenu *menu)
{
    QAction *action = menu->addAction(location.title);
    action->setData(QVariant::fromValue(location));
    locationActionMapper.setMapping(action, location.address);
    connect(action, SIGNAL(triggered()), &locationActionMapper, SLOT(map()));
    return action;
}

QList<Location> MainWindow::bookmarks() const
{
    QList<Location> result;
    foreach (const QAction *action, bookmarkActions)
        result.append(locationFromAction(action));
    return result;
}

//void MainWindow::on_actionAddBookmark_triggered()
//{
//    if (!historyActions.isEmpty()) {
//        const Location location = locationFromAction(historyActions.last());
//        if (!containsAddress(bookmarks(), location.address))
//            addBookmark(location);
//    }
//}

//! [2]
void MainWindow::on_WebBrowser_TitleChange(const QString &title)
{
    // This is called multiple times after NavigateComplete().
    // Add new URLs to history here.
    setWindowTitle("Qt WebBrowser - " + title);
    const QString currentAddress = address();
    const QString historyAddress = historyActions.isEmpty() ?
                QString() : locationFromAction(historyActions.last()).address;
    if (currentAddress.isEmpty() || currentAddress == "about:blank" || currentAddress == historyAddress)
        return;
    historyActions << addLocation(Location(title, currentAddress), HistoryMenu);
    if (historyActions.size() > 10)
        delete historyActions.takeFirst();
}

//void MainWindow::on_WebBrowser_ProgressChange(int a, int b)
//{
//    if (a <= 0 || b <= 0) {
//        pb->hide();
//        return;
//    }
//    pb->show();
//    pb->setRange(0, b);
//    pb->setValue(a);
//}

void MainWindow::on_WebBrowser_CommandStateChange(int cmd, bool on)
{
    switch (cmd) {
    case 1:
        actionForward->setEnabled(on);
        break;
    case 2:
        actionBack->setEnabled(on);
        break;
    }
}
void MainWindow::slot(const QString &name, int argc, void *argv)
{
    VARIANTARG *params = (VARIANTARG*)argv;
//    qDebug << params;
    if (name.startsWith("BeforeNavigate2(")) {
        IDispatch *pDisp = params[argc-1].pdispVal;
        VARIANTARG URL = *params[argc-2].pvarVal;
        VARIANTARG Flags = *params[argc-3].pvarVal;
        VARIANTARG TargetFrameName = *params[argc-4].pvarVal;
        VARIANTARG PostData = *params[argc-5].pvarVal;
        VARIANTARG Headers = *params[argc-6].pvarVal;
        //            bool *Cancel = params[argc-7].pboolVal;

    }
}
void MainWindow::on_WebBrowser_BeforeNavigate()
{
    actionStop->setEnabled(true);
}

void MainWindow::on_WebBrowser_NavigateComplete(const QString &url)
{
    actionStop->setEnabled(false);
    const bool blocked = addressEdit->blockSignals(true);
    addressEdit->setText(url);
    addressEdit->blockSignals(blocked);
    qDebug() << WebBrowser->generateDocumentation();
}

//! [3]
void MainWindow::on_actionGo_triggered()
{
    navigate(address());
}

//! [2]

void MainWindow::navigate(const QString &url)
{
    //TODO 发送http请求
    QVariant var;
    var.setValue(WebBrowser->dynamicCall("Navigate(const QString&)", url));
    qDebug() << url << var;
    qDebug() << WebBrowser->generateDocumentation();

}

void MainWindow::on_actionNewWindow_triggered()
{
    MainWindow *window = new MainWindow;
    window->show();
    if (addressEdit->text().isEmpty())
        return;
    window->addressEdit->setText(addressEdit->text());
    window->actionStop->setEnabled(true);
    window->on_actionGo_triggered();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About WebBrowser"),
                       tr("This Example has been created using the ActiveQt integration into Qt Designer.\n"
                          "It demonstrates the use of QAxWidget to embed the Internet Explorer ActiveX\n"
                          "control into a Qt application."));
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::on_actionFileClose_triggered()
{
    close();
}

