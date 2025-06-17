/********************************************************************************
** Form generated from reading UI file 'supplier_management_system.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUPPLIER_MANAGEMENT_SYSTEM_H
#define UI_SUPPLIER_MANAGEMENT_SYSTEM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SupplierManagementSystem
{
public:
    QAction *actionImport;
    QAction *actionExport;
    QAction *actionAddSupplier;
    QAction *actionDelete;
    QAction *actionSearchInColumn;
    QAction *actionGlobalSearch;
    QAction *actionAbout;
    QAction *actionRussian;
    QAction *actionEnglish;
    QAction *actionRomanian;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTableView *suppliersTableView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuLanguage;
    QMenu *menuHelp;
    QToolBar *toolBar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SupplierManagementSystem)
    {
        if (SupplierManagementSystem->objectName().isEmpty())
            SupplierManagementSystem->setObjectName("SupplierManagementSystem");
        SupplierManagementSystem->resize(800, 600);
        actionImport = new QAction(SupplierManagementSystem);
        actionImport->setObjectName("actionImport");
        actionExport = new QAction(SupplierManagementSystem);
        actionExport->setObjectName("actionExport");
        actionAddSupplier = new QAction(SupplierManagementSystem);
        actionAddSupplier->setObjectName("actionAddSupplier");
        actionDelete = new QAction(SupplierManagementSystem);
        actionDelete->setObjectName("actionDelete");
        actionSearchInColumn = new QAction(SupplierManagementSystem);
        actionSearchInColumn->setObjectName("actionSearchInColumn");
        actionGlobalSearch = new QAction(SupplierManagementSystem);
        actionGlobalSearch->setObjectName("actionGlobalSearch");
        actionAbout = new QAction(SupplierManagementSystem);
        actionAbout->setObjectName("actionAbout");
        actionRussian = new QAction(SupplierManagementSystem);
        actionRussian->setObjectName("actionRussian");
        actionEnglish = new QAction(SupplierManagementSystem);
        actionEnglish->setObjectName("actionEnglish");
        actionRomanian = new QAction(SupplierManagementSystem);
        actionRomanian->setObjectName("actionRomanian");
        centralwidget = new QWidget(SupplierManagementSystem);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        suppliersTableView = new QTableView(centralwidget);
        suppliersTableView->setObjectName("suppliersTableView");
        suppliersTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(suppliersTableView);

        SupplierManagementSystem->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SupplierManagementSystem);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuLanguage = new QMenu(menubar);
        menuLanguage->setObjectName("menuLanguage");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        SupplierManagementSystem->setMenuBar(menubar);
        toolBar = new QToolBar(SupplierManagementSystem);
        toolBar->setObjectName("toolBar");
        SupplierManagementSystem->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);
        statusbar = new QStatusBar(SupplierManagementSystem);
        statusbar->setObjectName("statusbar");
        SupplierManagementSystem->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuLanguage->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionImport);
        menuFile->addAction(actionExport);
        menuEdit->addAction(actionAddSupplier);
        menuEdit->addAction(actionDelete);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSearchInColumn);
        menuEdit->addAction(actionGlobalSearch);
        menuLanguage->addAction(actionRussian);
        menuLanguage->addAction(actionEnglish);
        menuLanguage->addAction(actionRomanian);
        menuHelp->addAction(actionAbout);
        toolBar->addAction(actionImport);
        toolBar->addAction(actionExport);
        toolBar->addSeparator();
        toolBar->addAction(actionAddSupplier);
        toolBar->addAction(actionDelete);
        toolBar->addSeparator();
        toolBar->addAction(actionSearchInColumn);
        toolBar->addAction(actionGlobalSearch);
        toolBar->addSeparator();
        toolBar->addAction(actionAbout);

        retranslateUi(SupplierManagementSystem);

        QMetaObject::connectSlotsByName(SupplierManagementSystem);
    } // setupUi

    void retranslateUi(QMainWindow *SupplierManagementSystem)
    {
        SupplierManagementSystem->setWindowTitle(QCoreApplication::translate("SupplierManagementSystem", "Ventilation Equipment Suppliers Management System", nullptr));
        actionImport->setText(QCoreApplication::translate("SupplierManagementSystem", "Import", nullptr));
        actionExport->setText(QCoreApplication::translate("SupplierManagementSystem", "Export", nullptr));
        actionAddSupplier->setText(QCoreApplication::translate("SupplierManagementSystem", "Add Supplier", nullptr));
        actionDelete->setText(QCoreApplication::translate("SupplierManagementSystem", "Delete", nullptr));
        actionSearchInColumn->setText(QCoreApplication::translate("SupplierManagementSystem", "Search in Column", nullptr));
        actionGlobalSearch->setText(QCoreApplication::translate("SupplierManagementSystem", "Global Search", nullptr));
        actionAbout->setText(QCoreApplication::translate("SupplierManagementSystem", "About", nullptr));
        actionRussian->setText(QCoreApplication::translate("SupplierManagementSystem", "Russian", nullptr));
        actionEnglish->setText(QCoreApplication::translate("SupplierManagementSystem", "English", nullptr));
        actionRomanian->setText(QCoreApplication::translate("SupplierManagementSystem", "Romanian", nullptr));
        menuFile->setTitle(QCoreApplication::translate("SupplierManagementSystem", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("SupplierManagementSystem", "Edit", nullptr));
        menuLanguage->setTitle(QCoreApplication::translate("SupplierManagementSystem", "Language", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("SupplierManagementSystem", "Help", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("SupplierManagementSystem", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SupplierManagementSystem: public Ui_SupplierManagementSystem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUPPLIER_MANAGEMENT_SYSTEM_H
