#ifndef TIMETABLETAB_H
#define TIMETABLETAB_H

#include <QMainWindow>
#include <QtWidgets>
#include <qpagehandler.h>
#include <QRegExp>
#include <stdio.h>
#include <iostream>
//#include "infostruct.h"

class TimeTableTab : public QMainWindow
{
    Q_OBJECT
public:
    explicit TimeTableTab(QWidget *parent = nullptr);
    ~TimeTableTab();

    QPageHandler *pageHandler;

    QSplitter *mainSplitter = nullptr;
    QSplitter *rightSplitter = nullptr;

    QTableView *tableRasp = nullptr;
    QStandardItemModel *itemModelRasp = nullptr;

    QWidget *w1 = nullptr;

    QVBoxLayout *generalLayout = nullptr;
    QGridLayout *mainLayout = nullptr;

    QLabel *labelDate = nullptr;
    QDateEdit * dateEditDate = nullptr;

    QLabel *labelSemestr = nullptr;
    QComboBox *comboBoxSemestr = nullptr;

    QLabel *labelNameTeacher = nullptr;
    QLineEdit *lineEditNameTeacher = nullptr;

    QPushButton *pushButtonTimeTableInput = nullptr;
    QPushButton *pushButtonTimeTableOutput = nullptr;

    void writeSettings();
    void readSettings();

public slots:
    void initialization();
    void clickedButton();

};

#endif // TIMETABLETAB_H
