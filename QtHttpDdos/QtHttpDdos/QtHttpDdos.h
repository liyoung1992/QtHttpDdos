#ifndef QTHTTPDDOS_H
#define QTHTTPDDOS_H

#include <QWidget>
#include "QHttpThread.h"
#include <QQueue>
#include <QTimer>

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

private slots:
    //控制按钮槽函数
    void on_controllerpbn_clicked();
    //代理ip TODO
    void on_importIpbtn_clicked();

private:
    Ui::QtHttpDdos *ui;
    //线程类
    QHttpThread* m_pRequestThead;
    //定时刷新访问次数
    QTimer* m_pFlushRequestCountTimer;

    //定义一个维护所有线程的队列
    QQueue<QHttpThread*> m_pThreadList;
};

#endif // QTHTTPDDOS_H
