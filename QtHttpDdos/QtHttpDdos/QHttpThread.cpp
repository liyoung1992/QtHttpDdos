#include "QHttpThread.h"
#include <QDebug>
#include <QUrl>
#include <QTextCodec>
#include <QMutexLocker>
#include <QEventLoop>
#include <QNetworkCookie> //单个cookie
#include <QNetworkCookieJar> //储存cookie
#include <QNetworkProxy>
#include <QApplication>

QHttpThread::QHttpThread(QObject* parent)
{
    init();
}
//构造函数
QHttpThread::QHttpThread(const QString &url, const int &runCount,
                         const QString &ua, const QString &cookie)
{
    init();
    m_pUrl = url;
    m_pRunCount = runCount;
    m_pUserAgent = ua;
    m_pCookie = cookie;
}

//设置参数,
void QHttpThread::setParse(const QString &url, const int &runCount,
                           const QString &ua, const QString &cookie)
{
    m_pUrl = url;
    m_pRunCount = runCount;
    m_pUserAgent = ua;
    m_pCookie = cookie;
}

//析构函数
QHttpThread::~QHttpThread()
{
    stopThread();
    m_pNetworkManager->deleteLater();
    m_pCookieJar->deleteLater();
    this->deleteLater();
}


//初始化
void QHttpThread::init()
{
    m_pNetworkManager = new QNetworkAccessManager();
    m_pNetworkReply = NULL;
    m_pCookieJar = new QNetworkCookieJar();
    //默认不开启代理ip
    m_pIsProxyIp = false;
    //默认开启10个线程
    m_pRunCount = 10;
    m_pRequestCount = 0;
    m_pRuning = true;
    //开启随意分页
    m_pIsOpenPage = false;
}

//多线程处理函数
void QHttpThread::run()
{

    //    m_pStop.lock();
    if(!m_pRuning)
        return ;
    while(1){
        sendRequest(m_pUrl,m_pUserAgent,m_pCookie);
        m_pRequestCount++;
        QApplication::processEvents();
        if(!m_pRuning)
            return ;
    }

}

//设置线程数量
void QHttpThread::setRunCount(const int &count)
{
    m_pRunCount = count;
}

//获取线程数量
int QHttpThread::getRunCount()
{
    return m_pRunCount;
}

//发送http请求
int QHttpThread::sendRequest(const QString &url, const QString &ua,
                             const QString &cookies)
{
    QNetworkRequest netRequest;
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    netRequest.setRawHeader("User-Agent", ua.toLatin1());
    if(cookies.length() > 5){

        QStringList list = cookies.split(";");
        QList<QNetworkCookie> cookieList;
        for(int i = 0; i < list.length(); i++){
            QStringList cookieStr = list.at(i).split("=");
            QByteArray cookieName = cookieStr.at(0).toLatin1();
            QByteArray cookieValue = cookieStr.at(1).toLatin1();

            QNetworkCookie cookie(cookieName,cookieValue);
            cookie.setExpirationDate(QDateTime::currentDateTime().addMonths(1));
            cookie.setSecure(true);
            cookieList.append(cookie);
        }
        QVariant var;
        var.setValue(cookieList);
        //        m_pNetworkManager->setCookieJar(m_pCookieJar);

        //        m_pNetworkManager->cookieJar()->setAllCookies(cookieList);
        netRequest.setHeader(QNetworkRequest::CookieHeader, var);
    }

    //地址信息
    if(m_pIsOpenPage){
        netRequest.setUrl(QUrl(getPageUrl()));
    }else{
         netRequest.setUrl(QUrl(url));
    }
    //https请求，需ssl支持(下载openssl拷贝libeay32.dll和ssleay32.dll文件至Qt bin目录或程序运行目录)
    if(url.toLower().startsWith("https"))
    {
        QSslConfiguration sslConfig;
        sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
        sslConfig.setProtocol(QSsl::TlsV1_1);
        netRequest.setSslConfiguration(sslConfig);
    }
    if(m_pIsProxyIp){
        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        int index = getRandIpIndex();
        proxy.setHostName(m_pProxyIpList.at(index));
        proxy.setPort(m_pProxyPortList.at(index).toInt());
        proxy.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
        proxy.setRawHeader("User-Agent", ua.toLatin1());

        m_pNetworkManager->setProxy(proxy);
        QNetworkProxy::setApplicationProxy(proxy);
    }
    QNetworkReply* m_pNetworkReplyTest;
    m_pNetworkReplyTest = NULL;
    m_pNetworkReplyTest  = m_pNetworkManager->get(netRequest);
    //释放内存
    if(m_pNetworkReplyTest != NULL)
        delete  m_pNetworkReplyTest;
    return 0;
}

int QHttpThread::getRequestCount()
{
    return m_pRequestCount;
}

void QHttpThread::startThread()
{
    m_pStop.lock();
    m_pRuning = true;
    m_pStop.unlock();
}

void QHttpThread::stopThread()
{
    m_pStop.lock();
    m_pRuning = false;
    m_pStop.unlock();
}
//添加代理ip
void QHttpThread::addProxyIp(const QString &ip)
{
    m_pProxyIpList.enqueue(ip);
}
//添加代理ip端口
void QHttpThread::addProxyPort(const QString &port)
{
    m_pProxyPortList.enqueue(port);
}
//代理ip开关
void QHttpThread::switchProxyIp(bool on_off)
{
    m_pIsProxyIp = on_off;
}
//获取随机的代理ip
int QHttpThread::getRandIpIndex()
{

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    int rand = qrand() % m_pProxyIpList.length();
    return rand;
}
//设置随意分页范围
void QHttpThread::setPageRange(const int &start, const int &end)
{
    m_pPageStart = start;
    m_pPageEnd  = end;
    m_pIsOpenPage = true;
}
//组装分页url（随机获取）
QString QHttpThread::getPageUrl()
{
    QString pre_url = m_pUrl.left(m_pUrl.length() - 1);
    qDebug() << pre_url;
    return pre_url + QString::number(getRandPage());
}
//获取随机页
int QHttpThread::getRandPage()
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    int rand = qrand() % m_pPageEnd;
    if(rand < m_pPageStart)
        return m_pPageStart + qrand() %(m_pPageEnd - m_pPageStart);

    return rand;
}









