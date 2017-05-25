#include "QHttpThread.h"
#include <QDebug>
#include <QUrl>
#include <QTextCodec>
#include <QMutexLocker>

QHttpThread::QHttpThread(QObject* parent):QThread(parent)
{
    init();
}

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
void QHttpThread::setParse(const QString &url, const int &runCount, const QString &ua, const QString &cookie)
{
    init();
    m_pUrl = url;
    m_pRunCount = runCount;
    m_pUserAgent = ua;
    m_pCookie = cookie;
}

//析构函数
QHttpThread::~QHttpThread()
{
    m_pNetworkManager->deleteLater();
    this->deleteLater();
}


//初始化
void QHttpThread::init()
{
    //默认开启100个线程
    m_pRunCount = 100;
    m_pNetworkManager = new QNetworkAccessManager(this);
    m_pNetworkReply = NULL;
    m_pRequestCount = 0;
}

//多线程处理函数
void QHttpThread::run()
{
    m_pIsCanRun = true;
    while(1){
        sendRequest(m_pUrl,m_pUserAgent,m_pCookie);
        m_pRequestCount++;
        qDebug() <<"requestCount:" + QString::number(m_pRequestCount);
        QMutexLocker locker(&m_PLock);
        if(!m_pIsCanRun)//在每次循环判断是否可以运行，如果不行就退出循环
         {
             return;
         }
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
                             const QString &cookie)
{
    QNetworkRequest netRequest;
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    netRequest.setUrl(QUrl(url)); //地址信息
    if(url.toLower().startsWith("https"))//https请求，需ssl支持(下载openssl拷贝libeay32.dll和ssleay32.dll文件至Qt bin目录或程序运行目录)
    {
        QSslConfiguration sslConfig;
        sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
        sslConfig.setProtocol(QSsl::TlsV1_1);
        netRequest.setSslConfiguration(sslConfig);
    }
    //TODO 添加对post请求的支持
    //    QString strBody; //http body部分，可封装参数信息
    //    QByteArray contentByteArray = strBody.toLatin1();//转成二进制
    //    m_pNetworkReply = m_pNetworkManager->post(netRequest,contentByteArray);//发起post请求

    //发起get请求
    m_pNetworkReply = m_pNetworkManager->get(netRequest);
    //请求完成信号
    connect(m_pNetworkReply,SIGNAL(finished()),this,SLOT(slot_requestFinished()));

}

int QHttpThread::getRequestCount()
{
    return m_pRequestCount;
}


//请求完成
void QHttpThread::slot_requestFinished()
{
    QByteArray resultContent = m_pNetworkReply->readAll();
    QTextCodec* pCodec = QTextCodec::codecForName("UTF-8");
    QString strResult = pCodec->toUnicode(resultContent);
    int nHttpCode = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
    if(nHttpCode == 200)//成功
    {
        qDebug() << "接口："<< m_pNetworkReply->url() <<"请求成功！";
    }
    else
    {
        qDebug() << "请求失败！！";
    }
    m_pNetworkReply->deleteLater();
}

void QHttpThread::stopThreadImmediately()
{
    QMutexLocker  locker(&m_PLock);
    m_pIsCanRun = false;
}


