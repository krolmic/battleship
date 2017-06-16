#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QTcpSocket>

//! [0]
class Thread : public QThread
{
    Q_OBJECT

public:
    Thread(int socketDescriptor, const QString &fortune, QObject *parent);

    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    QString text;
};
//! [0]

#endif
