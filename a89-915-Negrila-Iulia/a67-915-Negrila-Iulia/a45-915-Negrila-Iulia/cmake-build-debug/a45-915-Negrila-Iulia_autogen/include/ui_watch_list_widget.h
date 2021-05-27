/********************************************************************************
** Form generated from reading UI file 'watch_list_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WATCH_LIST_WIDGET_H
#define UI_WATCH_LIST_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_watch_list_widget
{
public:

    void setupUi(QWidget *watch_list_widget)
    {
        if (watch_list_widget->objectName().isEmpty())
            watch_list_widget->setObjectName(QString::fromUtf8("watch_list_widget"));
        watch_list_widget->resize(400, 300);

        retranslateUi(watch_list_widget);

        QMetaObject::connectSlotsByName(watch_list_widget);
    } // setupUi

    void retranslateUi(QWidget *watch_list_widget)
    {
        watch_list_widget->setWindowTitle(QCoreApplication::translate("watch_list_widget", "watch_list_widget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class watch_list_widget: public Ui_watch_list_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WATCH_LIST_WIDGET_H
