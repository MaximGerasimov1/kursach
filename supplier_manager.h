#ifndef SUPPLIER_MANAGER_H
#define SUPPLIER_MANAGER_H

#include <QObject>
#include "supplier_registry.h"

/**
 * @brief Класс менеджера для управления взаимодействием между моделью данных оборудования и представлением
 */
class SupplierManager : public QObject {
    Q_OBJECT
public:
    explicit SupplierManager(SupplierRegistry *model, QObject *parent = nullptr);
    
    /**
     * @brief Добавить запись оборудования
     */
    void addSupplier(const Supplier &supplierData);
    
    /**
     * @brief Удалить запись оборудования
     */
    void removeSupplier(int rowIndex);
    
    /**
     * @brief Редактировать запись оборудования
     */
    void editSupplier(int rowIndex, const Supplier &supplierData);
    
    /**
     * @brief Загрузить данные из файла
     */
    bool loadDataFromFile(const QString &filePath);
    
    /**
     * @brief Сохранить данные в файл
     */
    bool saveDataToFile(const QString &filePath) const;
    
    /**
     * @brief Поиск по столбцу
     */
    QList<int> searchByColumn(int columnIndex, const QString &searchText) const;
    
    /**
     * @brief Глобальный поиск по всем столбцам
     */
    QPair<int, int> performGlobalSearch(const QString &searchText) const;
    
    /**
     * @brief Сортировка по столбцу
     */
    void sortDataByColumn(int columnIndex, Qt::SortOrder direction = Qt::AscendingOrder);
    
    /**
     * @brief Получить заголовок столбца
     */
    QVariant getHeaderTitle(int sectionIndex, Qt::Orientation orientation) const;
    
    /**
     * @brief Обновить отображение заголовков
     */
    void updateHeaderDisplay(Qt::Orientation orientation, int firstSection, int lastSection);
    
    /**
     * @brief Получить количество столбцов
     */
    int getColumnCount() const;
    
private:
    SupplierRegistry *m_dataModel;
};

#endif // SUPPLIER_MANAGER_H 