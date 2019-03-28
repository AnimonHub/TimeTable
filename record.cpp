#include "record.h"

Record::Record(int id, QString name, int hours, QString kategory)
{
    this->id = id;
    this->name = name;
    this->hours =hours;
    this->kategory = kategory;
}

void Record::setId(int id)
{
    this->id = id;
}

int Record::getId()
{
    return this->id;
}

void Record::setName(QString name)
{
    this->name = name;
}

QString Record::getName()
{
    return this->name;
}

void Record::setHours(int hours)
{
    this->hours = hours;
}

void Record::setKategory(QString kategory)
{
    this->kategory = kategory;
}

int Record::getHours()
{
    return this->hours;
}

QString Record::getKategory()
{
    return  this->kategory;
}
