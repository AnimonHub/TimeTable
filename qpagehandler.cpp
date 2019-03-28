#include "qpagehandler.h"

QPageHandler::QPageHandler(QObject *parent) : QObject(parent)
{
    // Инициализируем менеджер ...
    manager = new QNetworkAccessManager();
    // ... и подключаем сигнал о завершении получения данных к обработчику полученного ответа
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onResult(QNetworkReply*)));
}

void QPageHandler::getData()
{
    QObject::sender();
    QString rr="http://rasp.gstu.by/rasp_df/db/get/getRaspByPrepod.php?prepod=%27%27,%27%D0%A1%D0%B0%D1%85%D0%B0%D1%80%D1%83%D0%BA%20%D0%90.%D0%92.%27&sem=summer&fuckult=both&type=Print&theDate=2019-05-14&brouser=Opera"+STR_;
    //QUrl url("http://kontakt.by/gomel/predprijatija/magazini-264/?q_l=%D0%93%D0%BE%D0%BC%D0%B5%D0%BB%D1%8C&l%5B0%5D=72&c%5B0%5D=264&page=1");
    QUrl url(rr);
    QNetworkRequest request;    // Отправляемый запрос
    request.setUrl(url);        // Устанавлвиваем URL в запрос
    manager->get(request);      // Выполняем запрос
}

void QPageHandler::onResult(QNetworkReply *reply)
{
    // Если в процесе получения данных произошла ошибка
    if(reply->error())
    {
        // Сообщаем об этом и показываем информацию об ошибках
        qWarning() << "ERROR";
        qWarning() << reply->errorString();
    }
    else
    {
        // В противном случае создаём объект для работы с файлом
        QFile *file = new QFile("/home/animon/TimeParsing/file.xml");

        // Создаём файл или открываем его на перезапись ...
        if(file->open(QFile::WriteOnly))
        {
            file->write(reply->readAll());  // ... и записываем всю информацию со страницы в файл
            file->close();                  // закрываем файл
        qWarning() << "Downloading is completed";
        emit onReady(); // Посылаем сигнал о завершении получения файла
        }
    }
}
