#include "QHttpThread.h"
#include <QDebug>
#include <QUrl>
#include <QTextCodec>
#include <QMutexLocker>
#include <QEventLoop>
#include <QNetworkCookie> //单个cookie
#include <QNetworkCookieJar> //储存cookie

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
    m_pNetworkManager->deleteLater();
    m_pOutTimer->deleteLater();
    this->deleteLater();
}


//初始化
void QHttpThread::init()
{

    m_pNetworkManager = new QNetworkAccessManager();
    m_pNetworkReply = NULL;

    //默认开启10个线程
    m_pRunCount = 10;
    m_pRequestCount = 0;
    m_pRuning = true;
    //请求超时控制
    m_pOutTimer = new QTimer();
    connect(m_pOutTimer,SIGNAL(timeout()),this,
            SLOT(slot_requestTimeout()),Qt::DirectConnection);
}

//多线程处理函数
void QHttpThread::run()
{
    qDebug() << "m_pRequestCount：" << QString::number(m_pRequestCount);
    //    m_pStop.lock();
    if(!m_pRuning)
        return ;
    sendRequest(m_pUrl,m_pUserAgent,m_pCookie);
    m_pRequestCount++;
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
                             const QString &cookie)
{
    QNetworkRequest netRequest;
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    netRequest.setRawHeader("User-Agent", ua.toLatin1());
    //TODO 添加cookie的支持
    //netRequest.setHeader(QNetworkRequest::CookieHeader,QVariant::fromValue(QString(cookie)));

    netRequest.setUrl(QUrl(url)); //地址信息
    //https请求，需ssl支持(下载openssl拷贝libeay32.dll和ssleay32.dll文件至Qt bin目录或程序运行目录)
    if(url.toLower().startsWith("https"))
    {
        QSslConfiguration sslConfig;
        sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
        sslConfig.setProtocol(QSsl::TlsV1_1);
        netRequest.setSslConfiguration(sslConfig);
    }

    m_pNetworkReply  = m_pNetworkManager->get(netRequest);
    //开始计算是否请求超时
    m_pOutTimer->start(5000);
    //请求完成信号
    connect(m_pNetworkReply,SIGNAL(finished()),
            this,SLOT(slot_requestFinished()),Qt::DirectConnection);
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


//请求完成
void QHttpThread::slot_requestFinished()
{
    //请求成功，停止计时器
    m_pOutTimer->stop();

    QByteArray resultContent = m_pNetworkReply->readAll();
    QTextCodec* pCodec = QTextCodec::codecForName("UTF-8");
    QString strResult = pCodec->toUnicode(resultContent);
    //http返回码
    int nHttpCode = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(nHttpCode == 200)//成功
    {
        qDebug() << "接口："<< m_pNetworkReply->url() <<"请求成功！" << m_pNetworkReply->thread()->currentThreadId();
    }
    else
    {
        qDebug() << "请求失败！！";
    }
    //删除请求
    if(m_pNetworkReply != NULL)
        delete m_pNetworkReply;
    run();
}

void QHttpThread::slot_requestTimeout()
{
    //删除请求
    if(m_pNetworkReply != NULL)
        delete m_pNetworkReply;
    m_pOutTimer->stop();
    run();
}



