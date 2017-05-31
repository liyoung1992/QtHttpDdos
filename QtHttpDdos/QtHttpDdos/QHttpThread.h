#ifndef QHTTPTHREAD_H
#define QHTTPTHREAD_H

#include <QThread>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTimer>
#include <QMutex>
#include <QQueue>

//线程处理类
class QHttpThread : public QObject
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
    int sendRequest(const QString &url,const QString &ua,
                    const QString &cookie);
    //获取当前线程请求次数
    int getRequestCount();
    //开启线程
    void startThread();
    //停止线程
    void stopThread();
    //添加代理ip
    void addProxyIp(const QString& ip);
    //添加端口
    void addProxyPort(const QString& port);
    //设置是否启用代理ip
    void switchProxyIp(bool on_off);
    //得到随机代理ip的下标
    int  getRandIpIndex();

public slots:
    //http请求结束
    void slot_requestFinished();
    //请求超时
    void slot_requestTimeout();
    //停止线程
//    void stopThreadImmediately();


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
    int64_t m_pRequestCount;
    //设置超时计时器
    QTimer* m_pOutTimer;
    //线程锁
    QMutex m_pStop;
    //是否运行
    bool m_pRuning;
    //是否使用代理ip
    bool m_pIsProxyIp;
    //代理ip列表
    QQueue<QString> m_pProxyIpList;
    //端口
    QQueue<QString> m_pProxyPortList;
};

#endif // QHTTPTHREAD_H
