#ifndef MainWindow_H
#define MainWindow_H

#include <QtWidgets/QWidget>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

#include "proto.h"

namespace Ui {
class MainWindow;
}

enum arch_e {
    ARCH_LINUX = 0,
    ARCH_WIN,
};

enum download_step_e {
    E_CHECKSUM = 1,
    E_ASSETS
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void secureConnect();
    void socketStateChanged(QAbstractSocket::SocketState state);
    void socketEncrypted();
    void sslErrors(const QList<QSslError> &errors);
    void socketError(QAbstractSocket::SocketError);
    void socketReadyRead();
    void updateEnabledState();

    void onDownloadFileComplete(QNetworkReply *reply);

    void login();
    void play();

private:
    void addLog(QString msg);
    void setNcards(const int type);
    void downloadFileFromURL(const QString &url, const QString &filePath, enum download_step_e step);

    QFile *m_file;
    bool m_isReady;

    Proto proto;
    int ncards;
    Ui::MainWindow *ui;
    QSslSocket *socket;
    enum download_step_e assets_step;
};

/*
Q_OBJECT
QFile *m_file;
bool m_isReady = true;

public:
explicit Downloader(QObject *parent = 0) : QObject(parent) {}
virtual ~Downloader() { delete m_file; }

void downloadFileFromURL(const QString &url, const QString &filePath);

private slots:
void onDownloadFileComplete(QNetworkReply *reply);
*/
#endif // MainWindow_H
