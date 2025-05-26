#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    void init();
    void initWidget();
    void initTitle();
    void initAddBtn();

signals:

private:;
    QWidget* m_widget;
    QLabel* m_title;
    QPushButton* m_addBtn;
};

#endif // MYWIDGET_H
