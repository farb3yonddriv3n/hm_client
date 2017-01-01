#include <QApplication>
#include <QMessageBox>
#include <QStyle>
#include <QDesktopWidget>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!QSslSocket::supportsSsl()) {
        QMessageBox::information(0, "Secure Socket Client",
                                 "This system does not support OpenSSL.");
        return -1;
    }

    MainWindow w;

    w.setGeometry(
        QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, w.size(), qApp->desktop()->availableGeometry())
    );
    w.show();

    return a.exec();
}
