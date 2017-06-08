#ifndef QTNETWORKCOOKIEJAR_H
#define QTNETWORKCOOKIEJAR_H
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QNetworkCookieJar>

class QtNetworkCookieJar:public QNetworkCookieJar
{
public:
    QtNetworkCookieJar();
    QList<QNetworkCookie> allCookies() const;
    void setAllCookies(const QList<QNetworkCookie> &cookieList);
};

#endif // QTNETWORKCOOKIEJAR_H
