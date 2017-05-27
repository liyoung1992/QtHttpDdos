#ifndef QTHTTPDDOS_H
#define QTHTTPDDOS_H

#include <QWidget>
#include "QHttpThread.h"
#include <QQueue>
#include <QTimer>
#include <QThread>

namespace Ui {
class QtHttpDdos;
}

class QtHttpDdos : public QWidget
{
    Q_OBJECT

public:
    explicit QtHttpDdos(QWidget *parent = 0);
    ~QtHttpDdos();

private:
    //开始请求
    void startRequest();
    //停止请求
    void stopRequest();
    //开启线程
    void startThread();


private slots:
    //控制按钮槽函数
    void on_controllerpbn_clicked();
    //代理ip TODO
    void on_importIpbtn_clicked();
    //定时刷新访问次数
    void slot_flushRequestCount();

private:
    Ui::QtHttpDdos *ui;

    //定时刷新访问次数
    QTimer* m_pFlushRequestCountTimer;

    //定义一个维护所有线程的队列
    QQueue<QHttpThread*> m_pHttpList;
    //线程类
    QQueue<QThread *> m_pThreadList;
    //标志位，记录是否是新建线程还是开始暂停的线程
    bool m_pIsNewThread;
};

#endif // QTHTTPDDOS_H
