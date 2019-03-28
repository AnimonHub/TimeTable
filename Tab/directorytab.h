#ifndef DIRECTORYTAB_H
#define DIRECTORYTAB_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>
#include "QHTab/qhtabwidget.h"
#include "QHTab/qhtabbar.h"
#include "record.h"
#include "intlistmodel.h"
#include <QMessageBox>
#include "winorlinux.h"

class DirectoryTab : public QWidget
{
    Q_OBJECT

public:
    static QSqlDatabase db;
    QLineEdit *lineEdit = nullptr;
    explicit DirectoryTab(QWidget *parent = nullptr);
    ~DirectoryTab();
    QFile file;
    QBoxLayout *mainlayout = nullptr;
    static QHTabWidget *tabwidget;

    QHBoxLayout *layoutButtons = nullptr;

    QPushButton *addDirectory = nullptr;
    QPushButton *deleteDirectory = nullptr;
    QBoxLayout *box = nullptr;

    QPushButton *DirectoryAddButton = nullptr;

    void addDataBase(QString nameBaseData);
    void sqlDataBase();

public slots:
    void deleteTab();
    void tabWidget();
};

class Directory : public QWidget
{
    Q_OBJECT
public:
    explicit Directory(QWidget *parent = nullptr);
    ~Directory();

    int mn = 1;

    QBoxLayout *mainlayout = nullptr;
    QHBoxLayout *barAndUpdateLayout = nullptr;
    QHBoxLayout *buttonLayout = nullptr;
    QPushButton *updateButton = nullptr;
    QSqlQuery query;
    QList<Record *> database;

    //добаление в базу данных
    QTableView *table = nullptr;
    QStandardItemModel *tableItemModel = nullptr;

    QStandardItem *item = nullptr;

    QMenuBar *menu = nullptr;
    QMenu *menuAction = nullptr;

    QAction *add = nullptr;
    QAction *change = nullptr;
    QAction *deletee = nullptr;

    void createItemModel();
    void addTable();

public slots:
    void tableItemClicked();

    QString getNameTabWidget();

    void sectionClicked(int flag);

    void slotAddTable();

    void slotAdd();

    void slotChange();

    void slotDelete();
};

#endif // DIRECTORYTAB_H
