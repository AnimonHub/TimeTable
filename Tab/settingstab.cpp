#include "settingstab.h"

QFont SettingsTab::f;

SettingsTab::SettingsTab(QWidget *parent) : QWidget(parent)
{
    mainlayout = new QVBoxLayout(this);

    boxFont = new QGroupBox(tr("Настройка шрифта"),this);

    layoutFont = new QGridLayout(boxFont);

    labelFont = new QLabel("Шрифт: ");

    fontComboBox = new QComboBox();
    QStringList fontList;
    fontList<<"11"<<"12"<<"13"<<"14"<<"15"<<"16"<<"17"<<"18"<<"19"<<"20";

    fontComboBox->addItems(fontList);

    layoutFont->addWidget(labelFont,0,0);
    layoutFont->addWidget(fontComboBox,0,1,0,100);

    connect(fontComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(slotFont(QString)));

    //////////////////////////////////////////////////////

    boxSave = new QGroupBox(tr("Сохранение"),this);

    layoutSave = new QGridLayout(boxSave);

    lineEditSave = new QLineEdit();
    lineEditSave->setReadOnly(true);
    lineEditSave->setPlaceholderText("Путь к конечному пути файла");
    buttonSave = new QPushButton("Обзор");

    layoutSave->addWidget(lineEditSave,0,0);
    layoutSave->addWidget(buttonSave,0,1,0,10);
    connect(buttonSave,SIGNAL(clicked()),this,SLOT(slotSave()));

    ////////////////////////////////////////////////////////

    boxSemestr = new QGroupBox(tr("Длительность семестра"));
    layoutSemestr = new QGridLayout(boxSemestr);

    startSemestr = new QDateEdit();
    endSemestr = new QDateEdit();

    labelStartSemestr = new QLabel(tr("Начало семестра"));
    labelEndSemestr = new QLabel(tr("Конец семестра"));

    layoutSemestr->addWidget(labelStartSemestr,0,0);
    layoutSemestr->addWidget(labelEndSemestr,1,0);
    layoutSemestr->addWidget(startSemestr,0,1,1,100);
    layoutSemestr->addWidget(endSemestr,1,1,1,100);

    /////////////////////////////////////////////////////////

    boxTimeTable = new QGroupBox(tr("Установка расписания"));

    layoutTimeTable = new QGridLayout(boxTimeTable);

    clickedPushButton = new QPushButton(tr("кнопка пиздец"));
    connect(clickedPushButton,SIGNAL(clicked()),this,SLOT(slotPushButton()));

    tableCorrectTableWidget = new CorrectTableWidget();

    tableCorrectTableWidget->verticalHeader()->setVisible(false);

    layoutTimeTable->addWidget(clickedPushButton);
    layoutTimeTable->addWidget(tableCorrectTableWidget);

    tableCorrectTableWidget->setColumnCount(4);
    tableCorrectTableWidget->setRowCount(112);

    //tableViewTimeTable->setModel(itemModelTimeTable);
    tableCorrectTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList string;
    string<<"Понедельник"<<"Вторник"<<"Среда"<<"Четверг"<<"Пятница"<<"Суббота"<<"Воскресенье";

    QStringList stringHorizontalHeader;
    stringHorizontalHeader<<"День недели"<<"Время"<<"Название пары"<<"Тип пары";
    tableCorrectTableWidget->setHorizontalHeaderLabels(stringHorizontalHeader);

    QStringList stringTime;
    stringTime<<"8:00-9:30"<<"9:45-11:15"<<"11:25-12:55"<<"13:25-14:55"<<"15:05-16:35"<<"16:50-18:20"<<"18:30-20:00"<<"20:30-22:00";

    for(int i = 0; i < 112; i+=16)
    {
        tableCorrectTableWidget->setSpan(i,0,16,1);
        item = new QTableWidgetItem(string.at(i/16));
        tableCorrectTableWidget->setItem(i,0,item);
    }

    int j = 0;
    for(int i = 0; i < 112 ;i+=2)
    {
        tableCorrectTableWidget->setSpan(i,1,2,1);
        item = new QTableWidgetItem(stringTime.at(j));
        tableCorrectTableWidget->setItem(i,1,item);
        if(j != 7)
        {
            j++;
        }
        else
        {
            j = 0;
        }
    }

    mainlayout->addWidget(boxFont);
    mainlayout->addWidget(boxSave);
    mainlayout->addWidget(boxSemestr);
    mainlayout->addWidget(boxTimeTable);

    readSettings();
}

SettingsTab::~SettingsTab()
{
    writeSettings();
}

void SettingsTab::writeSettings()
{
    QSettings settings("GSTU","Vladimirov");
    settings.beginGroup("Font");
    settings.setValue("MyFontFamily", QApplication::font().family());
    settings.setValue("MyFontPointSize",QApplication::font().pointSize());
    settings.endGroup();

    settings.beginGroup("dateEditStartSemestr");
    settings.setValue("startSemestr", startSemestr->date());
    settings.endGroup();

    settings.beginGroup("dateEditEndSemestr");
    settings.setValue("endSemestr", endSemestr->date());
    settings.endGroup();
}

void SettingsTab::readSettings()
{
    QFont myFont;
    QSettings settings("GSTU","Vladimirov");
    settings.beginGroup("Font");
    myFont.setFamily(settings.value("MyFontFamily").toString());
    myFont.setPointSize(settings.value("MyFontPointSize").toInt());
    QApplication::setFont(myFont);
    settings.endGroup();

    settings.beginGroup("dateEditStartSemestr");
    startSemestr->setDate(settings.value("startSemestr").toDate());
    settings.endGroup();

    settings.beginGroup("dateEditEndSemestr");
    endSemestr->setDate(settings.value("endSemestr").toDate());
    settings.endGroup();
}

void SettingsTab::slotPushButton()
{

}

void SettingsTab::slotFont(QString string)
{
    f.setPointSize(string.toInt());
#if defined (Q_OS_LINUX)
    f.setFamily("Ubuntu");
#elif defined (Q_OS_WIN32)
    f.setFamily("Calibri");
#endif
    QApplication::setFont(f);
}

void SettingsTab::slotSave()
{
    lineEditSave->setText("");
    QString startAdress = winOrLinux->returnPathForDb();
    QString finalAdress = QFileDialog::getExistingDirectory(this, "Open Dialog");
    lineEditSave->setText(finalAdress+"/spravochnikSubject.db");
    QFile file;
    file.copy(startAdress,finalAdress+"/spravochnikSubject.db");
}
