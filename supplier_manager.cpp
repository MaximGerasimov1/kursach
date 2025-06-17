#include "supplier_manager.h"

/**
 * @brief Конструктор менеджера вентиляционного оборудования
 * @param model Указатель на модель данных
 * @param parent Родительский объект
 */
SupplierManager::SupplierManager(SupplierRegistry *model, QObject *parent)
    : QObject(parent), m_dataModel(model)
{
}

/**
 * @brief Получить количество столбцов
 * @return Количество столбцов
 */
int SupplierManager::getColumnCount() const {
    return m_dataModel->columnCount();
}

/**
 * @brief Редактирует данные оборудования
 * @param rowIndex Индекс строки для редактирования
 * @param supplierData Новые данные оборудования
 */
void SupplierManager::editSupplier(int rowIndex, const Supplier &supplierData) {
    m_dataModel->updateSupplierData(rowIndex, supplierData);
}

/**
 * @brief Добавляет новое оборудование в модель
 * @param supplierData Структура с данными оборудования
 */
void SupplierManager::addSupplier(const Supplier &supplierData) {
    int rowIndex = m_dataModel->rowCount();
    m_dataModel->insertRows(rowIndex, 1);
    m_dataModel->updateSupplierData(rowIndex, supplierData);
}

/**
 * @brief Удаляет оборудование из модели
 * @param rowIndex Индекс строки для удаления
 */
void SupplierManager::removeSupplier(int rowIndex) {
    m_dataModel->removeRows(rowIndex, 1);
}

/**
 * @brief Сортирует данные модели по указанному столбцу
 * @param columnIndex Индекс столбца для сортировки
 * @param direction Порядок сортировки
 */
void SupplierManager::sortDataByColumn(int columnIndex, Qt::SortOrder direction) {
    m_dataModel->sortByColumn(columnIndex, direction);
}

/**
 * @brief Загружает данные об оборудовании из файла в модель
 * @param filePath Путь к файлу для загрузки
 * @return true если загрузка прошла успешно
 */
bool SupplierManager::loadDataFromFile(const QString &filePath) {
    return m_dataModel->importFromFile(filePath);
}

/**
 * @brief Сохраняет данные об оборудовании в файл
 * @param filePath Путь к файлу для сохранения
 * @return true если сохранение прошло успешно
 */
bool SupplierManager::saveDataToFile(const QString &filePath) const {
    return m_dataModel->exportToFile(filePath);
}

/**
 * @brief Выполняет поиск по определенному столбцу
 * @param columnIndex Индекс столбца для поиска
 * @param searchText Текст для поиска
 * @return Список индексов строк, содержащих искомый текст
 */
QList<int> SupplierManager::searchByColumn(int columnIndex, const QString &searchText) const {
    return m_dataModel->findInColumn(columnIndex, searchText);
}

/**
 * @brief Выполняет глобальный поиск по всем столбцам
 * @param searchText Текст для поиска
 * @return Пара (строка, столбец) первого найденного совпадения
 */
QPair<int, int> SupplierManager::performGlobalSearch(const QString &searchText) const {
    return m_dataModel->globalSearch(searchText);
}

/**
 * @brief Получает данные заголовка столбца
 * @param sectionIndex Индекс секции (столбца)
 * @param orientation Ориентация (горизонтальная/вертикальная)
 * @return Данные заголовка
 */
QVariant SupplierManager::getHeaderTitle(int sectionIndex, Qt::Orientation orientation) const {
    return m_dataModel->headerData(sectionIndex, orientation, Qt::DisplayRole);
}

/**
 * @brief Уведомляет о изменении заголовков
 * @param orientation Ориентация заголовков
 * @param firstSection Индекс первого измененного заголовка
 * @param lastSection Индекс последнего измененного заголовка
 */
void SupplierManager::updateHeaderDisplay(Qt::Orientation orientation, int firstSection, int lastSection) {
    m_dataModel->headerDataChanged(orientation, firstSection, lastSection);
} 