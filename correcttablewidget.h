#ifndef CORRECTTABLEWIDGET_H
#define CORRECTTABLEWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QMouseEvent>
#include <QAction>

class CorrectTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit CorrectTableWidget(QTableWidget *parent = nullptr);
    //virtual void mousePressEvent(QMouseEvent *event);
    QMenu *menuSpan = nullptr;
public slots:
    void slotSpanAndUnspan(QAction* action);
protected:
    virtual void contextMenuEvent(QContextMenuEvent* pe);
};

#endif // CORRECTTABLEWIDGET_H
