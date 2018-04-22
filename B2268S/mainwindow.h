#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QNetworkInterface>
#include <QWebView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void delay(int millisecondsToWait);
    int randInt(int low, int high);


private slots:
    void on_pushButton_clicked();
    void rightMessage();
    void wrongMessage();
    //void ping(QListIterator<QString> i, QStringList arguments);
    void ping();
    void init();
    void click_save();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_actionAbout_triggered();

    void on_actionAbout_B2268S_Tool_triggered();

    void on_actionClose_triggered();

    void on_actionAbout_RedSec_triggered();

    void on_actionUpdates_triggered();

private:
    Ui::MainWindow *ui;
    QProcess *proc;
    QNetworkInterface netintfa;
    QString phantomjs;
    QStringList cmds;
    QStringList arguments;
    QString b2268s;
    QStringList login;
    QString ipaddress;
    int nextcmd = 0;
    int clicked = 0;
    QString alert;
    int loading;
    QStringList host;
    QStringList counthost;
    QString count = "putang ina mo";
    int counting = 0;
    int identify = 0;
};

#endif // MAINWINDOW_H
