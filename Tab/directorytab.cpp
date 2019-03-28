#include "directorytab.h"

QHTabWidget *DirectoryTab::tabwidget = nullptr;
QSqlDatabase DirectoryTab::db = QSqlDatabase::addDatabase("QSQLITE");

void DirectoryTab::sqlDataBase()
{
    WinOrLinux *winOrLinux = new WinOrLinux();
    QString stringWinOrLinux;
    stringWinOrLinux.append(winOrLinux->returnPathForDb());
    db.setDatabaseName(QString("%0").arg(stringWinOrLinux));
    db.open();
    if (!db.open())
    {
          qWarning() << db.lastError().text();
    }
}

void DirectoryTab::deleteTab()
{
    int pos = DirectoryTab::tabwidget->currentIndex();
    QString stringName = DirectoryTab::tabwidget->tabText(pos);
    QSqlQuery query;

    QDialog dlg(this);
    dlg.setWindowTitle("Сообщение");
    QVBoxLayout *layout = new QVBoxLayout();
    QLabel *labelText = new QLabel(QString("Вы действительно хотите удалить справочник %0?").arg(stringName));
    layout->addWidget(labelText);

    QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    layout->addWidget(btn_box);
    dlg.setLayout(layout);
    if(dlg.exec() == QDialog::Accepted)
    {
        tabwidget->removeTab(tabwidget->currentIndex());
        query.exec(QString("DROP table %0").arg(stringName));
    }
}

DirectoryTab::DirectoryTab(QWidget *parent) : QWidget(parent)
{
    sqlDataBase();

    mainlayout = new QBoxLayout(QBoxLayout::TopToBottom,this);
    layoutButtons = new QHBoxLayout();

    addDirectory = new QPushButton("Добавить справочник");
    deleteDirectory = new QPushButton("Удалить справочник");

    tabwidget = new QHTabWidget();
    tabwidget->layoutDirection();
    mainlayout->addWidget(tabwidget);

    layoutButtons->addWidget(addDirectory);
    layoutButtons->addWidget(deleteDirectory);

    mainlayout->addLayout(layoutButtons);

    QStringList dbList = db.tables();
    for(int i = 0; i < dbList.size(); i++)
    {
        if(dbList.at(i) != "sqlite_sequence")
        {
            tabwidget->addTab(new Directory, dbList.at(i));
        }
    }
    connect(deleteDirectory,SIGNAL(clicked(bool)),this,SLOT(deleteTab()));
    connect(addDirectory,SIGNAL(clicked(bool)),this,SLOT(tabWidget()));
}

DirectoryTab::~DirectoryTab()
{
    db.close();
}

void DirectoryTab::addDataBase(QString nameBaseData)
{
    QSqlQuery query;
    query.exec(QString("CREATE TABLE %0(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "name TEXT NOT NULL,"
                       "hours INTEGER NOT NULL,"
                       "kategory TEXT NOT NULL);").arg(nameBaseData));
}

void DirectoryTab::tabWidget()
{
    QDialog dlg(this);
    box = new QBoxLayout(QBoxLayout::TopToBottom);
    lineEdit = new QLineEdit();
    box->addWidget(lineEdit);
    dlg.setLayout(box);
    DirectoryAddButton = new QPushButton("Ок");
    box->addWidget(DirectoryAddButton);
    connect(DirectoryAddButton,&QPushButton::clicked,&dlg,&QDialog::accept);
    if(dlg.exec() == QDialog::Accepted)
    {
        tabwidget->addTab(new Directory,lineEdit->text());
        addDataBase(lineEdit->text());
    }
}

Directory::Directory(QWidget *parent) : QWidget(parent)
{

    mainlayout = new QBoxLayout (QBoxLayout::TopToBottom,this);

    barAndUpdateLayout = new QHBoxLayout();

    updateButton = new QPushButton();
    QPixmap pixmap(":/images/download.jpeg");
    QIcon ButtonIcon(pixmap);
    updateButton->setIcon(ButtonIcon);
    updateButton->setIconSize(pixmap.scaled(20,20).size());
    updateButton->setFixedSize(pixmap.scaled(21,21).size());

    //Таблица для занятий

    table = new QTableView();

    tableItemModel = new QStandardItemModel();

    tableItemModel->removeRows(0,tableItemModel->rowCount());

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    menu = new QMenuBar();
    menuAction = new QMenu(tr("Меню занятий"));
    menu->addMenu(menuAction);

    add = new QAction(tr("Добавить занятие"));
    menuAction->addAction(add);

    change = new QAction(tr("Изменить занятие"));
    change->setEnabled(false);
    menuAction->addAction(change);

    deletee =  new QAction(tr("Удалить занятие"));
    deletee->setEnabled(false);
    menuAction->addAction(deletee);

    barAndUpdateLayout->addWidget(menu);
    barAndUpdateLayout->addWidget(updateButton);

    mainlayout->addLayout(barAndUpdateLayout);
    mainlayout->addWidget(table);

    connect(table->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(sectionClicked(int)));

    connect(updateButton,SIGNAL(clicked(bool)),this,SLOT(slotAddTable()));

    connect(table, SIGNAL(pressed(QModelIndex)), this, SLOT(tableItemClicked()));

    connect(add,SIGNAL(triggered()),this,SLOT(slotAdd()));
    connect(change,SIGNAL(triggered()),this,SLOT(slotChange()));
    connect(deletee,SIGNAL(triggered()),this,SLOT(slotDelete()));

    connect(DirectoryTab::tabwidget,SIGNAL(currentChanged(int)),this,SLOT(getNameTabWidget()));
}

Directory::~Directory()
{

}

QString Directory::getNameTabWidget()
{
    int pos = DirectoryTab::tabwidget->currentIndex();
    QString stringName = DirectoryTab::tabwidget->tabText(pos);
    return stringName;
}

void Directory::sectionClicked(int flag)
{
    if(flag == 0)
    {
        table->sortByColumn(flag);
    }
    else if(flag == 1)
    {
        if(mn%2==1)
        {
            tableItemModel->clear();
            database.clear();
            createItemModel();

            query.prepare(QString("SELECT * FROM %0 ORDER BY hours").arg(getNameTabWidget()));
            query.exec();
            int i=0;
            while(query.next())
            {
                database.append(new Record(query.value("id").toInt(),
                                           query.value("name").toString(),
                                           query.value("hours").toInt(),
                                           query.value("kategory").toString()));

                item = new QStandardItem(database.at(i)->getName());
                tableItemModel->setItem(i,0,item);

                item = new QStandardItem(QString::number(database.at(i)->getHours()));
                tableItemModel->setItem(i,1,item);

                item = new QStandardItem(database.at(i)->getKategory());
                tableItemModel->setItem(i,2,item);

                i++;
            }
            table->setModel(tableItemModel);
        }
        else
        {
            tableItemModel->clear();
            database.clear();
            createItemModel();

            query.prepare(QString("SELECT * FROM %0 ORDER BY hours desc").arg(getNameTabWidget()));
            query.exec();
            int i=0;
            while(query.next())
            {
                database.append(new Record(query.value("id").toInt(),
                                           query.value("name").toString(),
                                           query.value("hours").toInt(),
                                           query.value("kategory").toString()));

                item = new QStandardItem(database.at(i)->getName());
                tableItemModel->setItem(i,0,item);

                item = new QStandardItem(QString::number(database.at(i)->getHours()));
                tableItemModel->setItem(i,1,item);

                item = new QStandardItem(database.at(i)->getKategory());
                tableItemModel->setItem(i,2,item);

                i++;
            }
            table->setModel(tableItemModel);
        }
    }
    else if(flag == 2)
    table->sortByColumn(flag);
    mn++;
}

void Directory::createItemModel()
{
    QStringList label;
    label.length();
    label.append("Название темы");
    label.append("Количество часов");
    label.append("Вид занятий");
    tableItemModel->setHorizontalHeaderLabels(label);
}

void Directory::addTable()
{
    tableItemModel->clear();

    createItemModel();
    query.exec(QString("SELECT * FROM %0").arg(getNameTabWidget()));
//    query.exec();
    int i=0;
    while(query.next())
    {
        database.append(new Record(query.value("id").toInt(),
                                   query.value("name").toString(),
                                   query.value("hours").toInt(),
                                   query.value("kategory").toString()));

        item = new QStandardItem(database.at(i)->getName());
        tableItemModel->setItem(i,0,item);

        item = new QStandardItem(QString::number(database.at(i)->getHours()));
        tableItemModel->setItem(i,1,item);

        item = new QStandardItem(database.at(i)->getKategory());
        tableItemModel->setItem(i,2,item);

        i++;
    }
    table->setModel(tableItemModel);
}

void Directory::tableItemClicked()
{
    change->setEnabled(true);
    deletee->setEnabled(true);
}

void Directory::slotAddTable()
{
    addTable();
}

void Directory::slotAdd()
{
    QDialog dlg(this);

    dlg.setWindowTitle("Сообщение");
    dlg.setWindowFlag(Qt::Window);
    dlg.setWindowFlag(Qt::WindowTitleHint);
    dlg.setWindowFlag(Qt::CustomizeWindowHint);
    dlg.setWindowFlag(Qt::WindowCloseButtonHint, false);

    QVBoxLayout *mainChangeLayout = new QVBoxLayout(&dlg);

    QHBoxLayout *changeLayout = new QHBoxLayout();

    mainChangeLayout->addLayout(changeLayout);

    QVBoxLayout *nameLayout = new QVBoxLayout();
    changeLayout->addLayout(nameLayout);

    QVBoxLayout *hoursLayout = new QVBoxLayout();
    changeLayout->addLayout(hoursLayout);

    QLabel *name  = new QLabel("Название темы: ");
    nameLayout->addWidget(name);
    QLineEdit *nameLineEdit  = new QLineEdit();
    hoursLayout->addWidget(nameLineEdit);

    QLabel *hours = new QLabel("Количество часов: ");
    nameLayout->addWidget(hours);
    QLineEdit *hoursLineEdit  = new QLineEdit();
    hoursLayout->addWidget(hoursLineEdit);
    QComboBox *comboBoxList = new QComboBox();

    QStringList stringList;
    stringList<<"Лекция"<<"Практика"<<"Семинар"<<"Лабораторная";

    comboBoxList->addItems(stringList);
    mainChangeLayout->addWidget(comboBoxList);

    QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    mainChangeLayout->addWidget(btn_box);
    dlg.setLayout(mainChangeLayout);
    if(dlg.exec() == QDialog::Accepted)
    {
        if (DirectoryTab::db.open())
        {
            QSqlQuery query;
            query.prepare(QString("INSERT INTO %0 (name, hours, kategory) VALUES (?, ?, ?);").arg(getNameTabWidget()));
            query.addBindValue(nameLineEdit->text());
            query.addBindValue(hoursLineEdit->text());
            query.addBindValue(comboBoxList->currentText());
            query.exec();
            database.clear();
        }
        addTable();
    }
}

void Directory::slotChange()
{
    int pos = 0;
    pos = table->selectionModel()->selectedRows().at(0).row();

    QDialog dlg(this);

    dlg.setWindowTitle("Сообщение");
    dlg.setWindowFlag(Qt::Window);
    dlg.setWindowFlag(Qt::WindowTitleHint);
    dlg.setWindowFlag(Qt::CustomizeWindowHint);
    dlg.setWindowFlag(Qt::WindowCloseButtonHint, false);

    QVBoxLayout *mainChangeLayout = new QVBoxLayout(&dlg);

    QHBoxLayout *changeLayout = new QHBoxLayout();

    mainChangeLayout->addLayout(changeLayout);

    QVBoxLayout *nameLayout = new QVBoxLayout();
    changeLayout->addLayout(nameLayout);

    QVBoxLayout *hoursLayout = new QVBoxLayout();
    changeLayout->addLayout(hoursLayout);

    QLabel *name  = new QLabel("Название темы: ");
    nameLayout->addWidget(name);
    QLineEdit *nameLineEdit  = new QLineEdit(database.at(pos)->getName());
    hoursLayout->addWidget(nameLineEdit);

    QLabel *hours = new QLabel("Количество часов: ");
    nameLayout->addWidget(hours);
    QLineEdit *hoursLineEdit  = new QLineEdit(QString::number(database.at(pos)->getHours()));
    hoursLayout->addWidget(hoursLineEdit);
    QComboBox *comboBoxList = new QComboBox();
    QStringList stringList;
    stringList<<"Лекция"<<"Практика"<<"Семинар"<<"Лабораторная";
    for(int i = 0; i < 4 ; i++)
    {
        if(database.at(pos)->getKategory() == stringList.at(i))
        {
            stringList.removeAt(i);
            break;
        }
    }
    comboBoxList->addItems(QStringList(database.at(pos)->getKategory()));
    comboBoxList->addItems(stringList);
    mainChangeLayout->addWidget(comboBoxList);

    QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    mainChangeLayout->addWidget(btn_box);
    dlg.setLayout(mainChangeLayout);

    if(dlg.exec() == QDialog::Accepted)
    {
        if (DirectoryTab::db.open())
        {
            QSqlQuery query;
            query.prepare(QString("UPDATE %0 SET name = ?, hours = ?, kategory = ? WHERE id = ? ;").arg(getNameTabWidget()));
            query.bindValue(0,nameLineEdit->text());
            query.bindValue(1,hoursLineEdit->text());
            query.bindValue(2,comboBoxList->currentText());
            query.bindValue(3,database.at(pos)->getId());
            query.exec();
            database.clear();
        }
        addTable();
    }
}

void Directory::slotDelete()
{
    QDialog dlg(this);
    int pos = 0;
    pos = table->selectionModel()->selectedRows().at(0).row();
    dlg.setWindowTitle("Сообщение");
    dlg.setWindowFlag(Qt::Window);
    dlg.setWindowFlag(Qt::WindowTitleHint);
    dlg.setWindowFlag(Qt::CustomizeWindowHint);
    dlg.setWindowFlag(Qt::WindowCloseButtonHint, false);

    QVBoxLayout *changelayout = new QVBoxLayout(&dlg);

    QLabel *label = new QLabel("Вы действительно хотите удалить эту запись?", &dlg);

    changelayout->addWidget(label);

    QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    changelayout->addWidget(btn_box);

    dlg.setLayout(changelayout);

    if(dlg.exec() == QDialog::Accepted)
    {
        if (DirectoryTab::db.open())
        {
            QSqlQuery query;
            query.prepare(QString("DELETE FROM %0 WHERE id=?").arg(getNameTabWidget()));
            query.bindValue(0,database.at(pos)->getId());
            query.exec();
            database.clear();
        }
        addTable();
    }
}
