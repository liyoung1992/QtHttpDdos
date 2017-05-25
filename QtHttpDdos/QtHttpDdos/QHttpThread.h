#ifndef QHTTPTHREAD_H
#define QHTTPTHREAD_H

#include <QThread>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTimer>
#include <QMutex>

//线程处理类
class QHttpThread : public QThread
{
    Q_OBJECT
public:
    QHttpThread(QObject* parent);
    QHttpThread(const QString &url,const int &runCount,
                const QString &ua,const QString &cookie);

    void setParse(const QString &url,const int &runCount,
                  const QString &ua,const QString &cookie);
    ~QHttpThread();
    //初始化函数
    void init();
    //run函数实现多线程
    void run();
    //设置线程数
    void setRunCount(const int &count);
    //获取线程数量
    int getRunCount();
    //发送请求
    int sendRequest(const QString &url,const QString &ua,const QString &cookie);
    //获取当前线程请求次数
    int getRequestCount();
    //TODO 代理ip

public slots:
    //http请求结束
    void slot_requestFinished();
    //停止线程
    void stopThreadImmediately();

private:
    //线程数量
    int m_pRunCount;
    //网络管理类
    QNetworkAccessManager* m_pNetworkManager;
     //封装请求返回信息
    QNetworkReply* m_pNetworkReply;
    //请求url
    QString m_pUrl;
    //爬去ua
    QString m_pUserAgent;
    //cookie
    QString m_pCookie;

    //请求次数

    int m_pRequestCount;

    //判断是否能运行，加锁
    QMutex m_PLock;
    bool m_pIsCanRun;
};

#endif // QHTTPTHREAD_H
