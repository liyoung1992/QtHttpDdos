

#include <QApplication>
#include <QMessageBox>
#include <QProgressBar>
#include <QLineEdit>
#include <QLabel>
#include <QStatusBar>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QAbstractEventDispatcher>
#include <QSignalMapper>
#include <QVariant>
#include <QSettings>
#include "QtHttpDdos.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>


#include "ui_qtwebview.h"

static const char qtUrl[] = "www.baidu.com";
static const char iWebBrowser2DocumentationUrl[] = "http://msdn.microsoft.com/en-us/library/aa752127%28v=vs.85%29.aspx";
static const char versionKey[] = "Version";
static const char geometryKey[] = "Geometry";

struct Location {
    Location(const QString &t = QString(), const QString &a = QString()) : title(t), address(a) {}

    QString title;
    QString address;
};

Q_DECLARE_METATYPE(Location)

static QList<Location> defaultBookmarks()
{
    QList<Location> result;
    result.append(Location(QStringLiteral("Qt"), QLatin1String(qtUrl)));
    result.append(Location(QStringLiteral("Digia"), QStringLiteral("http://www.wall.cc/")));
    result.append(Location(QStringLiteral("IWebBrowser2 MSDN Documentation"), QLatin1String(iWebBrowser2DocumentationUrl)));
    return result;
}

static bool containsAddress(const QList<Location> &locations, const QString &address)
{
    foreach (const Location &location, locations) {
        if (location.address == address)
            return true;
    }
    return false;
}

static inline Location locationFromAction(const QAction *action)
{
    return action->data().value<Location>();
}

static QList<Location> readBookMarks(QSettings &settings)
{
    QList<Location> result;
    if (const int count = settings.beginReadArray(QStringLiteral("Bookmarks"))) {
        const QString titleKey = QStringLiteral("title");
        const QString addressKey = QStringLiteral("address");
        for (int i = 0; i < count; ++i) {
            settings.setArrayIndex(i);
            result.append(Location(settings.value(titleKey).toString(),
                                   settings.value(addressKey).toString()));
        }
    }
    settings.endArray();
    return result;
}

static void saveBookMarks(const QList<Location> &bookmarks, QSettings &settings)
{
    const int count = bookmarks.size();
    settings.beginWriteArray(QStringLiteral("Bookmarks"));
    const QString titleKey = QStringLiteral("title");
    const QString addressKey = QStringLiteral("address");
    for (int i = 0; i < count; ++i) {
        settings.setArrayIndex(i);
        settings.setValue(titleKey, bookmarks.at(i).title);
        settings.setValue(addressKey, bookmarks.at(i).address);
    }
    settings.endArray();
}

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
public:
    MainWindow(QtHttpDdos *parent = NULL);
    ~MainWindow();


public slots:
    void navigate(const QString &address);
    void on_WebBrowser_TitleChange(const QString &title);
//    void on_WebBrowser_ProgressChange(int a, int b);
    void on_WebBrowser_CommandStateChange(int cmd, bool on);
    void on_WebBrowser_BeforeNavigate();
    void on_WebBrowser_NavigateComplete(const QString &address);

    void on_actionGo_triggered();
    void on_actionNewWindow_triggered();
//    void on_actionAddBookmark_triggered();
    void on_actionAbout_triggered();
    void on_actionAboutQt_triggered();
    void on_actionFileClose_triggered();

    void slot(const QString &name, int argc, void *argv);

private:
    inline const QString address() const
        { return addressEdit->text().trimmed(); }
    QList<Location> bookmarks() const;
    QAction *addLocation(const Location &location, QMenu *menu);

    QProgressBar *pb;
    QLineEdit *addressEdit;
    QList<QAction *> bookmarkActions;
    QList<QAction *> historyActions;
    QSignalMapper locationActionMapper;
    QtHttpDdos* m_pHttpDdos;

    //网络管理类
    QNetworkAccessManager* m_pNetworkManager;
     //封装请求返回信息
    QNetworkReply* m_pNetworkReply;
};
