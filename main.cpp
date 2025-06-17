#include <QApplication>
#include "supplier_management_system.h"

/**
 * @brief Точка входа в приложение
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SupplierManagementSystem w;
    w.show();
    return app.exec();
} 