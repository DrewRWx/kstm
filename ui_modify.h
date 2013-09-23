/********************************************************************************
** Form generated from reading ui file 'modify.ui'
**
** Created: Fri Jul 24 18:34:13 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MODIFY_H
#define UI_MODIFY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_modifyDialog
{
public:
    QVBoxLayout *verticalLayout;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *modifyDialog)
    {
        if (modifyDialog->objectName().isEmpty())
            modifyDialog->setObjectName(QString::fromUtf8("modifyDialog"));
        modifyDialog->resize(584, 323);
        verticalLayout = new QVBoxLayout(modifyDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        buttonBox = new QDialogButtonBox(modifyDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(modifyDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), modifyDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), modifyDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(modifyDialog);
    } // setupUi

    void retranslateUi(QDialog *modifyDialog)
    {
        modifyDialog->setWindowTitle(QApplication::translate("modifyDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(modifyDialog);
    } // retranslateUi

};

namespace Ui {
    class modifyDialog: public Ui_modifyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFY_H
