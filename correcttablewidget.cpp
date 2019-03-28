#include "correcttablewidget.h"

CorrectTableWidget::CorrectTableWidget(QTableWidget *parent) : QTableWidget(parent)
{
   if(menuSpan == nullptr)
   {
   menuSpan = new QMenu(this);
   menuSpan->addAction("Объединить ячейки");
   menuSpan->addAction("Разъединить ячейки");
   }
   connect(menuSpan,SIGNAL(triggered(QAction*)),this,SLOT(slotSpanAndUnspan(QAction*)));
}

//void CorrectTableWidget::mousePressEvent(QMouseEvent *event)
//{
//    if(QApplication::mouseButtons() == Qt::RightButton)
//    {

//    }
//    QTableWidget::mousePressEvent(event);
//}

void CorrectTableWidget::slotSpanAndUnspan(QAction* action)
{
    QVector<int> rowIndexes;

    qWarning()<<"asd";

    QList<QTableWidgetSelectionRange> rangesList = CorrectTableWidget::selectedRanges();

    foreach (QTableWidgetSelectionRange range, rangesList)
    {
        qWarning() << range.topRow();
        rowIndexes.append(range.topRow());
    }

    QString nameStr = action->text();

    if(nameStr == "Объединить ячейки")
    CorrectTableWidget::setSpan(rowIndexes.at(0),2,2,1);
    else if(nameStr == "Разъединить ячейки")
    CorrectTableWidget::setSpan(rowIndexes.at(0),2,1,1);
    rowIndexes.clear();
}

void CorrectTableWidget::contextMenuEvent(QContextMenuEvent *pe)
{
    menuSpan->exec(pe->globalPos());
}
