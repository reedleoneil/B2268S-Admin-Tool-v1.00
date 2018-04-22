#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTime>
#include <QLabel>
#include <QMovie>
#include <QWebView>
#include <QUrl>

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        QPixmap pixmap(":/images/splash.gif");
        QSplashScreen splash(pixmap);
        //splash.setEnabled(false);

        QWebView *webview = new QWebView(&splash);
        QUrl tweeter("qrc:/others/das.html");
        webview->load(tweeter);

        QMovie *movie = new QMovie(":/images/splash.gif");
        QLabel image(&splash);
        image.setMovie(movie);
        movie->start();

        //QLabel image(&splash);
        MainWindow window;
        window.show();
        splash.show();
        QTime dieTime = QTime::currentTime().addMSecs( 24000 );
        while( QTime::currentTime() < dieTime )
        {
            app.processEvents();
        }
        //MainWindow window;
        //window.show();
        //splash.finish();
        return app.exec();

}
