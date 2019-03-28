#include "timetabletab.h"

TimeTableTab::TimeTableTab(QWidget *parent) : QMainWindow(parent)
{
    pageHandler = new QPageHandler();

    rightSplitter = new QSplitter;

    tableRasp = new QTableView;
    itemModelRasp = new QStandardItemModel;

    itemModelRasp->setColumnCount(2);
    itemModelRasp->setRowCount(5);
    tableRasp->setModel(itemModelRasp);

    w1 = new QWidget;

    generalLayout = new QVBoxLayout(w1);
    mainLayout = new QGridLayout();
    generalLayout->addLayout(mainLayout);

/////////////////////////////////////////
    labelDate = new QLabel(tr("Дата"));

    dateEditDate = new QDateEdit;

/////////////////////////////////////////
    labelSemestr = new QLabel(tr("Семестр"));
    QStringList stringList;
    stringList<<"Весенний"<<"Осенний";
    comboBoxSemestr = new QComboBox;
    comboBoxSemestr->addItems(stringList);

/////////////////////////////////////////

    labelNameTeacher = new QLabel(tr("Преподователь"));
    lineEditNameTeacher = new QLineEdit;
    lineEditNameTeacher->setPlaceholderText("Сахарук А.В.");

/////////////////////////////////////////
    pushButtonTimeTableOutput = new QPushButton(tr("Вывод расписания"));

    connect(pushButtonTimeTableOutput,SIGNAL(clicked(bool)),pageHandler,SLOT(getData()));
    connect(pageHandler,SIGNAL(onReady()),this,SLOT(clickedButton()));

    pushButtonTimeTableInput = new QPushButton(tr("Ввод расписания"));
    connect(pushButtonTimeTableInput,SIGNAL(clicked()),this,SLOT(initialization()));

    mainLayout->addWidget(labelDate,0,0);
    mainLayout->addWidget(labelSemestr,1,0);
    mainLayout->addWidget(labelNameTeacher,2,0);

    mainLayout->addWidget(dateEditDate,0,1);
    mainLayout->addWidget(comboBoxSemestr,1,1);
    mainLayout->addWidget(lineEditNameTeacher,2,1);

    generalLayout->addStretch(0);
    generalLayout->addWidget(pushButtonTimeTableInput,0,Qt::AlignRight);
    generalLayout->addWidget(pushButtonTimeTableOutput,0,Qt::AlignRight);

    rightSplitter = new QSplitter(Qt::Horizontal);
    rightSplitter->addWidget(tableRasp);
    rightSplitter->addWidget(w1);
    rightSplitter->setStretchFactor(1,1);

    setCentralWidget(rightSplitter);

    readSettings();
}

TimeTableTab::~TimeTableTab()
{
    writeSettings();
}

void TimeTableTab::writeSettings()
{
    QSettings settings("GSTU","Vladimirov");
    settings.beginGroup("mainWindow");
    settings.setValue("rightSplitter", rightSplitter->saveState());
    settings.endGroup();

    settings.beginGroup("timeTableTabEdits");
    settings.setValue("dateEditDate", dateEditDate->date());
    settings.endGroup();
}

void TimeTableTab::readSettings()
{
    QSettings settings("GSTU","Vladimirov");
    settings.beginGroup("mainWindow");
    rightSplitter->restoreState(settings.value("rightSplitter").toByteArray());
    settings.endGroup();

    settings.beginGroup("timeTableTabEdits");
    dateEditDate->setDate(settings.value("dateEditDate").toDate());
    settings.endGroup();
}

void TimeTableTab::initialization()
{
    QWidget *widgetTimeTable = new QWidget();
    QGridLayout *gridLayout = new QGridLayout(widgetTimeTable);

    QTableWidget *tableWidget = new QTableWidget();
    QTableWidgetItem *tableWidgetItem = new QTableWidgetItem();
    tableWidget->setColumnCount(10);
    tableWidget->setRowCount(10);
    gridLayout->addWidget(tableWidget);

    widgetTimeTable->show();
}

void TimeTableTab::clickedButton()
{
    qWarning()<<"asd";
}
