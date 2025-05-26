#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget{parent}
{
    init();
    show();
}

void MyWidget::init()
{
    initWidget();
    initTitle();
    initAddBtn();
}

void MyWidget::initWidget()
{
    m_widget = new QWidget(this);
    m_widget->move(50, 50);
    m_widget->setFixedSize(350, 350);

    m_widget->setStyleSheet(
        "border: 2px solid red; "  // 边框宽度和颜色
        "background-color: #f0f0f0;" // 背景颜色
        );
    m_widget->show();
}

void MyWidget::initTitle()
{
    m_title = new QLabel("标题", m_widget);
    m_title->move(0, 0);
    m_title->setFixedSize(350, 20);
    m_title->show();
}

void MyWidget::initAddBtn()
{
    m_addBtn = new QPushButton("添加", m_widget);
    m_addBtn->move(10, 40);
    m_addBtn->setFixedSize(40, 40);
    m_addBtn->show();
}
