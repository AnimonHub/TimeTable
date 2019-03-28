#ifndef RECORD_H
#define RECORD_H

#include <QtWidgets>
#include <QString>

class Record
{
public:
    Record(int id, QString name, int hours, QString kategory);

    void setId(int id);
    void setName(QString name);
    void setHours(int hours);
    void setKategory(QString kategory);

    int getId();
    QString getName();
    int getHours();
    QString getKategory();
private:
    int id;
    QString name;
    int hours;
    QString kategory;
    int asd;
};

#endif // RECORD_H
