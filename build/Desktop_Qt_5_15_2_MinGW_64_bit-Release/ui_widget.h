/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QComboBox *colorComboBox;
    QComboBox *dirComboBox;
    QPushButton *pushButton;
    QWidget *TrafficLightShowWidget;
    QPushButton *clsBtn_3;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLineEdit *idLineEdit;
    QPlainTextEdit *history;
    QPushButton *clsBtn;
    QGroupBox *propertyGroupBox;
    QPushButton *updateBtn;
    QLabel *imgLabel;
    QLabel *idLabel1;
    QLabel *colorLabel;
    QLabel *directionLabel;
    QComboBox *directionComboBox;
    QLabel *idLabel;
    QComboBox *laneComboBox;
    QLabel *directionLabel_2;
    QPushButton *propertyGroupBoxCloseBtn;
    QLabel *idLabel_4;
    QLabel *lightSecLabel;
    QGroupBox *ConditionGroupBox_2;
    QPushButton *exeGroupBoxUpdateBtn;
    QLabel *idLabel_3;
    QPushButton *exeGroupBoxCloseBtn;
    QGroupBox *ConditionGroupBox;
    QPushButton *conditionGroupBoxUpdateBtn;
    QLabel *idLabel_2;
    QPushButton *conditionGroupBoxCloseBtn;
    QComboBox *rulesListComBox;
    QPushButton *updateRulesBtn;
    QPlainTextEdit *conditionShowWidget;
    QPushButton *editRuleBtn;
    QPushButton *deleteRulesBtn;
    QPushButton *addRulesBtn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1240, 830);
        colorComboBox = new QComboBox(Widget);
        colorComboBox->addItem(QString());
        colorComboBox->addItem(QString());
        colorComboBox->addItem(QString());
        colorComboBox->setObjectName(QString::fromUtf8("colorComboBox"));
        colorComboBox->setGeometry(QRect(20, 100, 80, 30));
        dirComboBox = new QComboBox(Widget);
        dirComboBox->addItem(QString());
        dirComboBox->addItem(QString());
        dirComboBox->addItem(QString());
        dirComboBox->addItem(QString());
        dirComboBox->addItem(QString());
        dirComboBox->setObjectName(QString::fromUtf8("dirComboBox"));
        dirComboBox->setGeometry(QRect(20, 60, 80, 30));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(120, 50, 61, 51));
        TrafficLightShowWidget = new QWidget(Widget);
        TrafficLightShowWidget->setObjectName(QString::fromUtf8("TrafficLightShowWidget"));
        TrafficLightShowWidget->setGeometry(QRect(10, 10, 1221, 125));
        TrafficLightShowWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(247, 216, 255);"));
        clsBtn_3 = new QPushButton(TrafficLightShowWidget);
        clsBtn_3->setObjectName(QString::fromUtf8("clsBtn_3"));
        clsBtn_3->setGeometry(QRect(1148, 90, 60, 30));
        pushButton_2 = new QPushButton(TrafficLightShowWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(1048, 90, 90, 30));
        lineEdit = new QLineEdit(TrafficLightShowWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(860, 90, 180, 30));
        idLineEdit = new QLineEdit(Widget);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));
        idLineEdit->setGeometry(QRect(20, 20, 81, 25));
        history = new QPlainTextEdit(Widget);
        history->setObjectName(QString::fromUtf8("history"));
        history->setGeometry(QRect(750, 170, 480, 650));
        clsBtn = new QPushButton(Widget);
        clsBtn->setObjectName(QString::fromUtf8("clsBtn"));
        clsBtn->setGeometry(QRect(1160, 180, 61, 28));
        propertyGroupBox = new QGroupBox(Widget);
        propertyGroupBox->setObjectName(QString::fromUtf8("propertyGroupBox"));
        propertyGroupBox->setGeometry(QRect(770, 770, 400, 350));
        propertyGroupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(239, 245, 255);"));
        updateBtn = new QPushButton(propertyGroupBox);
        updateBtn->setObjectName(QString::fromUtf8("updateBtn"));
        updateBtn->setGeometry(QRect(310, 320, 91, 31));
        imgLabel = new QLabel(propertyGroupBox);
        imgLabel->setObjectName(QString::fromUtf8("imgLabel"));
        imgLabel->setGeometry(QRect(20, 40, 60, 60));
        imgLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/src/trafficLight/unknown/black.png);"));
        idLabel1 = new QLabel(propertyGroupBox);
        idLabel1->setObjectName(QString::fromUtf8("idLabel1"));
        idLabel1->setGeometry(QRect(100, 40, 21, 20));
        colorLabel = new QLabel(propertyGroupBox);
        colorLabel->setObjectName(QString::fromUtf8("colorLabel"));
        colorLabel->setGeometry(QRect(100, 70, 120, 20));
        directionLabel = new QLabel(propertyGroupBox);
        directionLabel->setObjectName(QString::fromUtf8("directionLabel"));
        directionLabel->setGeometry(QRect(20, 150, 41, 30));
        directionComboBox = new QComboBox(propertyGroupBox);
        directionComboBox->addItem(QString());
        directionComboBox->addItem(QString());
        directionComboBox->addItem(QString());
        directionComboBox->addItem(QString());
        directionComboBox->addItem(QString());
        directionComboBox->addItem(QString());
        directionComboBox->setObjectName(QString::fromUtf8("directionComboBox"));
        directionComboBox->setGeometry(QRect(80, 150, 100, 30));
        idLabel = new QLabel(propertyGroupBox);
        idLabel->setObjectName(QString::fromUtf8("idLabel"));
        idLabel->setGeometry(QRect(130, 40, 81, 20));
        laneComboBox = new QComboBox(propertyGroupBox);
        laneComboBox->addItem(QString());
        laneComboBox->addItem(QString());
        laneComboBox->addItem(QString());
        laneComboBox->addItem(QString());
        laneComboBox->setObjectName(QString::fromUtf8("laneComboBox"));
        laneComboBox->setGeometry(QRect(80, 210, 100, 30));
        directionLabel_2 = new QLabel(propertyGroupBox);
        directionLabel_2->setObjectName(QString::fromUtf8("directionLabel_2"));
        directionLabel_2->setGeometry(QRect(20, 190, 41, 30));
        propertyGroupBoxCloseBtn = new QPushButton(propertyGroupBox);
        propertyGroupBoxCloseBtn->setObjectName(QString::fromUtf8("propertyGroupBoxCloseBtn"));
        propertyGroupBoxCloseBtn->setGeometry(QRect(300, 20, 91, 31));
        idLabel_4 = new QLabel(propertyGroupBox);
        idLabel_4->setObjectName(QString::fromUtf8("idLabel_4"));
        idLabel_4->setGeometry(QRect(170, 90, 81, 20));
        lightSecLabel = new QLabel(propertyGroupBox);
        lightSecLabel->setObjectName(QString::fromUtf8("lightSecLabel"));
        lightSecLabel->setGeometry(QRect(100, 100, 120, 20));
        ConditionGroupBox_2 = new QGroupBox(Widget);
        ConditionGroupBox_2->setObjectName(QString::fromUtf8("ConditionGroupBox_2"));
        ConditionGroupBox_2->setGeometry(QRect(840, 940, 400, 350));
        ConditionGroupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(239, 245, 255);"));
        exeGroupBoxUpdateBtn = new QPushButton(ConditionGroupBox_2);
        exeGroupBoxUpdateBtn->setObjectName(QString::fromUtf8("exeGroupBoxUpdateBtn"));
        exeGroupBoxUpdateBtn->setGeometry(QRect(308, 316, 91, 31));
        idLabel_3 = new QLabel(ConditionGroupBox_2);
        idLabel_3->setObjectName(QString::fromUtf8("idLabel_3"));
        idLabel_3->setGeometry(QRect(130, 40, 81, 20));
        exeGroupBoxCloseBtn = new QPushButton(ConditionGroupBox_2);
        exeGroupBoxCloseBtn->setObjectName(QString::fromUtf8("exeGroupBoxCloseBtn"));
        exeGroupBoxCloseBtn->setGeometry(QRect(220, 316, 91, 31));
        ConditionGroupBox = new QGroupBox(ConditionGroupBox_2);
        ConditionGroupBox->setObjectName(QString::fromUtf8("ConditionGroupBox"));
        ConditionGroupBox->setGeometry(QRect(40, -20, 400, 350));
        ConditionGroupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(239, 245, 255);"));
        conditionGroupBoxUpdateBtn = new QPushButton(ConditionGroupBox);
        conditionGroupBoxUpdateBtn->setObjectName(QString::fromUtf8("conditionGroupBoxUpdateBtn"));
        conditionGroupBoxUpdateBtn->setGeometry(QRect(308, 316, 91, 31));
        idLabel_2 = new QLabel(ConditionGroupBox);
        idLabel_2->setObjectName(QString::fromUtf8("idLabel_2"));
        idLabel_2->setGeometry(QRect(130, 40, 81, 20));
        conditionGroupBoxCloseBtn = new QPushButton(ConditionGroupBox);
        conditionGroupBoxCloseBtn->setObjectName(QString::fromUtf8("conditionGroupBoxCloseBtn"));
        conditionGroupBoxCloseBtn->setGeometry(QRect(220, 316, 91, 31));
        rulesListComBox = new QComboBox(Widget);
        rulesListComBox->setObjectName(QString::fromUtf8("rulesListComBox"));
        rulesListComBox->setGeometry(QRect(10, 140, 91, 25));
        updateRulesBtn = new QPushButton(Widget);
        updateRulesBtn->setObjectName(QString::fromUtf8("updateRulesBtn"));
        updateRulesBtn->setGeometry(QRect(110, 140, 71, 28));
        conditionShowWidget = new QPlainTextEdit(Widget);
        conditionShowWidget->setObjectName(QString::fromUtf8("conditionShowWidget"));
        conditionShowWidget->setGeometry(QRect(10, 170, 730, 650));
        editRuleBtn = new QPushButton(Widget);
        editRuleBtn->setObjectName(QString::fromUtf8("editRuleBtn"));
        editRuleBtn->setGeometry(QRect(640, 180, 93, 28));
        deleteRulesBtn = new QPushButton(Widget);
        deleteRulesBtn->setObjectName(QString::fromUtf8("deleteRulesBtn"));
        deleteRulesBtn->setGeometry(QRect(200, 140, 71, 28));
        addRulesBtn = new QPushButton(Widget);
        addRulesBtn->setObjectName(QString::fromUtf8("addRulesBtn"));
        addRulesBtn->setGeometry(QRect(280, 140, 71, 28));
        colorComboBox->raise();
        dirComboBox->raise();
        pushButton->raise();
        idLineEdit->raise();
        history->raise();
        clsBtn->raise();
        TrafficLightShowWidget->raise();
        propertyGroupBox->raise();
        ConditionGroupBox_2->raise();
        rulesListComBox->raise();
        updateRulesBtn->raise();
        conditionShowWidget->raise();
        editRuleBtn->raise();
        deleteRulesBtn->raise();
        addRulesBtn->raise();

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        colorComboBox->setItemText(0, QCoreApplication::translate("Widget", "\347\272\242", nullptr));
        colorComboBox->setItemText(1, QCoreApplication::translate("Widget", "\347\273\277", nullptr));
        colorComboBox->setItemText(2, QCoreApplication::translate("Widget", "\351\273\204", nullptr));

        dirComboBox->setItemText(0, QCoreApplication::translate("Widget", "\345\234\206", nullptr));
        dirComboBox->setItemText(1, QCoreApplication::translate("Widget", "\345\267\246", nullptr));
        dirComboBox->setItemText(2, QCoreApplication::translate("Widget", "\347\233\264", nullptr));
        dirComboBox->setItemText(3, QCoreApplication::translate("Widget", "\345\217\263", nullptr));
        dirComboBox->setItemText(4, QCoreApplication::translate("Widget", "\346\216\211", nullptr));

        pushButton->setText(QCoreApplication::translate("Widget", "\346\267\273\345\212\240", nullptr));
        clsBtn_3->setText(QCoreApplication::translate("Widget", "cls", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "\350\277\236\346\216\245\347\233\270\346\234\272", nullptr));
        lineEdit->setText(QCoreApplication::translate("Widget", "192.168.12.14:7878", nullptr));
        idLineEdit->setText(QCoreApplication::translate("Widget", "1", nullptr));
        clsBtn->setText(QCoreApplication::translate("Widget", "cls", nullptr));
        propertyGroupBox->setTitle(QCoreApplication::translate("Widget", "\347\201\257\345\261\236\346\200\247\357\274\232", nullptr));
        updateBtn->setText(QCoreApplication::translate("Widget", "\346\233\264\346\226\260\345\261\236\346\200\247", nullptr));
        imgLabel->setText(QString());
        idLabel1->setText(QCoreApplication::translate("Widget", "id:", nullptr));
        colorLabel->setText(QCoreApplication::translate("Widget", "\345\275\223\345\211\215\351\242\234\350\211\262:", nullptr));
        directionLabel->setText(QCoreApplication::translate("Widget", "\346\226\271\345\220\221:", nullptr));
        directionComboBox->setItemText(0, QCoreApplication::translate("Widget", "\345\234\206\345\275\242", nullptr));
        directionComboBox->setItemText(1, QCoreApplication::translate("Widget", "\345\267\246\350\275\254", nullptr));
        directionComboBox->setItemText(2, QCoreApplication::translate("Widget", "\347\233\264\350\241\214", nullptr));
        directionComboBox->setItemText(3, QCoreApplication::translate("Widget", "\345\217\263\350\275\254", nullptr));
        directionComboBox->setItemText(4, QCoreApplication::translate("Widget", "\346\216\211\345\244\264", nullptr));
        directionComboBox->setItemText(5, QCoreApplication::translate("Widget", "\346\234\252\347\237\245", nullptr));

        idLabel->setText(QString());
        laneComboBox->setItemText(0, QCoreApplication::translate("Widget", "\346\234\272\345\212\250\350\275\246\351\201\223", nullptr));
        laneComboBox->setItemText(1, QCoreApplication::translate("Widget", "\351\235\236\346\234\272\345\212\250\350\275\246\351\201\223", nullptr));
        laneComboBox->setItemText(2, QCoreApplication::translate("Widget", "\344\272\272\350\241\214\351\201\223", nullptr));
        laneComboBox->setItemText(3, QCoreApplication::translate("Widget", "\346\234\252\347\237\245", nullptr));

        directionLabel_2->setText(QCoreApplication::translate("Widget", "\350\275\246\351\201\223:", nullptr));
        propertyGroupBoxCloseBtn->setText(QCoreApplication::translate("Widget", "x", nullptr));
        idLabel_4->setText(QString());
        lightSecLabel->setText(QCoreApplication::translate("Widget", "\345\267\262\344\272\256\346\227\266\351\225\277:", nullptr));
        ConditionGroupBox_2->setTitle(QCoreApplication::translate("Widget", "\347\273\223\346\236\234\347\252\227\345\217\243\357\274\232", nullptr));
        exeGroupBoxUpdateBtn->setText(QCoreApplication::translate("Widget", "\344\277\256\346\224\271", nullptr));
        idLabel_3->setText(QString());
        exeGroupBoxCloseBtn->setText(QCoreApplication::translate("Widget", "x", nullptr));
        ConditionGroupBox->setTitle(QCoreApplication::translate("Widget", "\346\235\241\344\273\266\347\252\227\345\217\243\357\274\232", nullptr));
        conditionGroupBoxUpdateBtn->setText(QCoreApplication::translate("Widget", "\344\277\256\346\224\271", nullptr));
        idLabel_2->setText(QString());
        conditionGroupBoxCloseBtn->setText(QCoreApplication::translate("Widget", "x", nullptr));
        updateRulesBtn->setText(QCoreApplication::translate("Widget", "\351\207\215\350\275\275\350\247\204\345\210\231", nullptr));
        conditionShowWidget->setPlainText(QString());
        editRuleBtn->setText(QCoreApplication::translate("Widget", "\347\274\226\350\276\221\350\247\204\345\210\231", nullptr));
        deleteRulesBtn->setText(QCoreApplication::translate("Widget", "\345\210\240\351\231\244\350\247\204\345\210\231", nullptr));
        addRulesBtn->setText(QCoreApplication::translate("Widget", "\346\267\273\345\212\240\350\247\204\345\210\231", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
