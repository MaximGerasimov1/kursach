/********************************************************************************
** Form generated from reading UI file 'about_program_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_PROGRAM_DIALOG_H
#define UI_ABOUT_PROGRAM_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AboutProgramDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *infoLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AboutProgramDialog)
    {
        if (AboutProgramDialog->objectName().isEmpty())
            AboutProgramDialog->setObjectName("AboutProgramDialog");
        AboutProgramDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(AboutProgramDialog);
        verticalLayout->setObjectName("verticalLayout");
        infoLabel = new QLabel(AboutProgramDialog);
        infoLabel->setObjectName("infoLabel");
        infoLabel->setAlignment(Qt::AlignCenter);
        infoLabel->setWordWrap(true);

        verticalLayout->addWidget(infoLabel);

        buttonBox = new QDialogButtonBox(AboutProgramDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AboutProgramDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, AboutProgramDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, AboutProgramDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(AboutProgramDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutProgramDialog)
    {
        AboutProgramDialog->setWindowTitle(QCoreApplication::translate("AboutProgramDialog", "About Program", nullptr));
        infoLabel->setText(QCoreApplication::translate("AboutProgramDialog", "<b>Ventilation Equipment Suppliers Management System</b><br>Institute: [\320\230\320\275\321\201\321\202\320\270\321\202\321\203\321\202]<br>Course: [\320\232\321\203\321\200\321\201]<br>Group: [\320\223\321\200\321\203\320\277\320\277\320\260]<br>Name: [\320\244\320\260\320\274\320\270\320\273\320\270\321\217 \320\230\320\274\321\217 \320\236\321\202\321\207\320\265\321\201\321\202\320\262\320\276]", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutProgramDialog: public Ui_AboutProgramDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_PROGRAM_DIALOG_H
