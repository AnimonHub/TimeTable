#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    generallayout = new QVBoxLayout(this);

    layoutPassword = new QGridLayout(this);

    layoutButtons = new QHBoxLayout();

    generallayout->addLayout(layoutPassword);

    labelLogin = new QLabel("Логин");
    lineLogin = new QLineEdit();

    labelPassword = new QLabel("Пароль");
    linePassword = new QLineEdit();

    layoutPassword->addWidget(labelLogin,0,0);
    layoutPassword->addWidget(lineLogin,0,1,1,4);
    layoutPassword->addWidget(labelPassword,1,0);
    layoutPassword->addWidget(linePassword,1,1);

    linePassword->setEchoMode(QLineEdit::Password);

    checkParam = new QCheckBox("show");
    layoutPassword->addWidget(checkParam,1,2);

    ok = new QPushButton("Ок");
    exit = new QPushButton("Выход");

    layoutButtons->addWidget(ok);
    layoutButtons->addWidget(exit);
    generallayout->addLayout(layoutButtons);

    w1 = new QWidget();

    tabwidget = new QHTabWidget();

    mainLayout = new QVBoxLayout(w1);
    w1->setLayout(mainLayout);
    mainLayout->addWidget(tabwidget);

    settingsTab = new SettingsTab(this);
    timeTableTab = new TimeTableTab(this);
    directoryTab = new DirectoryTab(this);
    directory = new Directory();

    tabwidget->setTabPosition(QTabWidget::West);

    tabwidget->addTab(timeTableTab,QIcon(":/images/timetable.jpg"),"Расписание");

    tabwidget->addTab(directoryTab,QIcon(":/images/animon.jpg"),"Справочники");

    tabwidget->addTab(settingsTab ,QIcon(":/images/settings.png"),"Настройки");


    connect(ok,SIGNAL(clicked()),this,SLOT(slotOk()));
    connect(exit,SIGNAL(clicked()),this,SLOT(close()));
    connect(checkParam,SIGNAL(clicked()),this,SLOT(slotToggle()));

    readSettings();
}

void MainWindow::slotToggle()
{
    if(checkParam->isChecked())
    {
        linePassword->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        linePassword->setEchoMode(QLineEdit::Password);
    }
}

void MainWindow::slotOk()
{
    QString stringLogin = "1";
    QString stringLogin_ = lineLogin->text();
    QString stringPassword = "1";
    QString stringPassword_ = linePassword->text();
    if(stringLogin == stringLogin_ && stringPassword == stringPassword_)
    {
        w1->setWindowTitle("Расписание");
        w1->show();
        QWidget::close();
    }
    else
    {
        QMessageBox::critical(nullptr,"Ошибка",QString("Вы ввели неправильный логин и пароль"));
    }
}

MainWindow::~MainWindow()
{
    delete timeTableTab;
    delete settingsTab;
    delete directoryTab;
    delete directory;
    writeSettings();
}

void MainWindow::writeSettings()
{
    QSettings settings("GSTU","Vladimirov");
    settings.beginGroup("mainWindow");
    settings.setValue("geometry", w1->saveGeometry());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("GSTU","Vladimirov");
    settings.beginGroup("mainWindow");
    w1->restoreGeometry(settings.value("geometry").toByteArray());
    settings.endGroup();
}


