#ifndef SETTINGSTAB_H
#define SETTINGSTAB_H

#include <QWidget>
#include <QtWidgets>
#include <winorlinux.h>
#include <QSettings>
#include "contextmenu.h"
#include <QMouseEvent>
#include "correcttablewidget.h"

class SettingsTab : public QWidget
{
    Q_OBJECT
private:

public:
    explicit SettingsTab(QWidget * parent = nullptr);
    ~SettingsTab();

    static QFont f;

    QVBoxLayout *mainlayout = nullptr;

    WinOrLinux *winOrLinux = nullptr;

    QGroupBox *boxFont = nullptr;
    QGridLayout *layoutFont = nullptr;
    QLabel *labelFont = nullptr;
    QComboBox *fontComboBox = nullptr;
    QFont currentFont;

    QGroupBox *boxSave = nullptr;
    QGridLayout *layoutSave = nullptr;
    QLineEdit *lineEditSave = nullptr;
    QPushButton *buttonSave = nullptr;

    QGroupBox *boxSemestr = nullptr;
    QGridLayout *layoutSemestr = nullptr;
    QDateEdit *startSemestr = nullptr;
    QDateEdit *endSemestr = nullptr;

    QGroupBox *boxTimeTable = nullptr;
    QGridLayout *layoutTimeTable = nullptr;
    //QTableWidget *tableWidgetTimeTable = nullptr;
    CorrectTableWidget *tableCorrectTableWidget = nullptr;
    //QStandardItemModel *itemModelTimeTable = nullptr;
    QTableWidgetItem *item = nullptr;
    QPushButton *clickedPushButton = nullptr;

    QLabel *labelStartSemestr = nullptr;
    QLabel *labelEndSemestr = nullptr;

    void writeSettings();
    void readSettings();

public slots:

    void slotPushButton();

    void slotFont(QString string);
    void slotSave();

};


#endif // SETTINGSTAB_H
