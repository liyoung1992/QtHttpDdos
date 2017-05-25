/********************************************************************************
** Form generated from reading UI file 'QtHttpDdos.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTHTTPDDOS_H
#define UI_QTHTTPDDOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtHttpDdos
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *urlEdt;
    QPushButton *importIpbtn;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *uaEdt;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *cookieEdt;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QLineEdit *runCountEdt;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_6;
    QLabel *requestCountLab;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *controllerpbn;

    void setupUi(QWidget *QtHttpDdos)
    {
        if (QtHttpDdos->objectName().isEmpty())
            QtHttpDdos->setObjectName(QStringLiteral("QtHttpDdos"));
        QtHttpDdos->resize(382, 223);
        QtHttpDdos->setLayoutDirection(Qt::LeftToRight);
        verticalLayoutWidget = new QWidget(QtHttpDdos);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 371, 211));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(80, 0));
        label->setLayoutDirection(Qt::RightToLeft);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        urlEdt = new QLineEdit(verticalLayoutWidget);
        urlEdt->setObjectName(QStringLiteral("urlEdt"));

        horizontalLayout->addWidget(urlEdt);

        importIpbtn = new QPushButton(verticalLayoutWidget);
        importIpbtn->setObjectName(QStringLiteral("importIpbtn"));

        horizontalLayout->addWidget(importIpbtn);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(80, 0));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        uaEdt = new QLineEdit(verticalLayoutWidget);
        uaEdt->setObjectName(QStringLiteral("uaEdt"));

        horizontalLayout_2->addWidget(uaEdt);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(80, 0));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_3);

        cookieEdt = new QLineEdit(verticalLayoutWidget);
        cookieEdt->setObjectName(QStringLiteral("cookieEdt"));

        horizontalLayout_4->addWidget(cookieEdt);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_4);

        runCountEdt = new QLineEdit(verticalLayoutWidget);
        runCountEdt->setObjectName(QStringLiteral("runCountEdt"));

        horizontalLayout_6->addWidget(runCountEdt);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_6->addWidget(label_5);

        lineEdit_3 = new QLineEdit(verticalLayoutWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_6->addWidget(lineEdit_3);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_7->addWidget(label_6);

        requestCountLab = new QLabel(verticalLayoutWidget);
        requestCountLab->setObjectName(QStringLiteral("requestCountLab"));

        horizontalLayout_7->addWidget(requestCountLab);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        controllerpbn = new QPushButton(verticalLayoutWidget);
        controllerpbn->setObjectName(QStringLiteral("controllerpbn"));

        horizontalLayout_7->addWidget(controllerpbn);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalLayoutWidget->raise();

        retranslateUi(QtHttpDdos);

        QMetaObject::connectSlotsByName(QtHttpDdos);
    } // setupUi

    void retranslateUi(QWidget *QtHttpDdos)
    {
        QtHttpDdos->setWindowTitle(QApplication::translate("QtHttpDdos", "QtHttpDdos", Q_NULLPTR));
        label->setText(QApplication::translate("QtHttpDdos", "\347\233\256\346\240\207URL:", Q_NULLPTR));
        urlEdt->setText(QApplication::translate("QtHttpDdos", "http://127.0.0.1", Q_NULLPTR));
        importIpbtn->setText(QApplication::translate("QtHttpDdos", "\345\257\274\345\205\245\344\273\243\347\220\206IP", Q_NULLPTR));
        label_2->setText(QApplication::translate("QtHttpDdos", "\346\265\217\350\247\210\345\231\250\347\261\273:", Q_NULLPTR));
        uaEdt->setText(QApplication::translate("QtHttpDdos", "\346\255\244\345\244\204\345\241\253\345\206\231\346\265\217\350\247\210\345\231\250UA\344\277\241\346\201\257\346\210\226\347\210\254\350\231\253\346\254\272\351\252\227UA", Q_NULLPTR));
        label_3->setText(QApplication::translate("QtHttpDdos", "Cookie:", Q_NULLPTR));
        label_4->setText(QApplication::translate("QtHttpDdos", "\347\272\277\347\250\213\346\225\260:", Q_NULLPTR));
        runCountEdt->setText(QApplication::translate("QtHttpDdos", "100", Q_NULLPTR));
        label_5->setText(QApplication::translate("QtHttpDdos", "\350\266\205\346\227\266:", Q_NULLPTR));
        lineEdit_3->setText(QApplication::translate("QtHttpDdos", "5000", Q_NULLPTR));
        label_6->setText(QApplication::translate("QtHttpDdos", "\345\275\223\345\211\215\350\257\267\346\261\202:", Q_NULLPTR));
        requestCountLab->setText(QApplication::translate("QtHttpDdos", "0", Q_NULLPTR));
        label_7->setText(QApplication::translate("QtHttpDdos", "\346\254\241", Q_NULLPTR));
        controllerpbn->setText(QApplication::translate("QtHttpDdos", "start", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtHttpDdos: public Ui_QtHttpDdos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTHTTPDDOS_H
