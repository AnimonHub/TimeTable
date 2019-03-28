#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "QHTab/qhtabbar.h"
#include "QHTab/qhtabwidget.h"
#include "Tab/timetabletab.h"
#include "Tab/directorytab.h"
#include "Tab/settingstab.h"
#include <QSettings>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SettingsTab *settingsTab = nullptr;
    TimeTableTab *timeTableTab = nullptr;
    DirectoryTab *directoryTab = nullptr;
    Directory *directory = nullptr;

    QVBoxLayout * generallayout = nullptr;
    QGridLayout *layoutPassword = nullptr;
    QLabel *labelLogin = nullptr;
    QLabel *labelPassword = nullptr;

    QLineEdit *lineLogin = nullptr;
    QLineEdit *linePassword = nullptr;

    QHBoxLayout *layoutButtons = nullptr;

    QCheckBox *checkParam = nullptr;

    QPushButton * ok = nullptr;
    QPushButton * exit = nullptr;

    QWidget *w1 = nullptr;

    QHTabWidget *tabwidget=nullptr;

    QVBoxLayout *mainLayout;

    //test
    QListView *DirectoryListView = nullptr;
    QStringListModel *DirectoryListModel = nullptr;
    //work
    QStringList *DirectoryStringList = nullptr;
    QListWidget *DirectoryListWidget = nullptr;
    QVBoxLayout *DirectoryVBoxLayout = nullptr;

    QPushButton * DirectoryAdd = nullptr;
    QPushButton * DirectoryAddButton=nullptr;
    QBoxLayout *box=nullptr;
    QDialog *dlg=nullptr;
    QLineEdit *lineedit=nullptr;

    void writeSettings();
    void readSettings();

public slots:

    void slotToggle();
    void slotOk();
};

#endif // MAINWINDOW_H
