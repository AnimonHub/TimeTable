#ifndef QPAGEHANDLER_H
#define QPAGEHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QList>
#include <QUrl>
#include <QFile>
#include <QDebug>

class QPageHandler: public QObject
{
    Q_OBJECT
public:
    QString STR_;
    explicit QPageHandler(QObject *parent = 0);
signals:
    void onReady();     //говорим приложению, что получение данных прошло успешно
                        //можно приступать к дальнейшей работе
public slots:
    void getData();     // Метод инициализации запроса на получение данных
    void onResult(QNetworkReply *reply);    // Слот обработки ответа о полученных данных

private:
    QNetworkAccessManager *manager; // менеджер сетевого доступа
};

#endif // QPAGEHANDLER_H
