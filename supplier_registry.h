#ifndef SUPPLIER_REGISTRY_H
#define SUPPLIER_REGISTRY_H

#include <QAbstractTableModel>
#include <QVector>
#include <QString>
#include <QMessageBox>

/**
 * @brief Структура, описывающая вентиляционное оборудование
 */
struct Supplier {
    QString name;             ///< Название и марка оборудования
    QString contractNumber;   ///< Инвентарный номер
    QString registrationDate; ///< Дата регистрации
    QString productCategory;  ///< Категория оборудования
    QString qualityRating;    ///< Рейтинг качества (от 1 до 5)
    QString deliveryTime;     ///< Срок эксплуатации (в днях)
    QString contactPerson;    ///< Отдел, где установлено
    QString phoneNumber;      ///< Телефон
    QString emailAddress;     ///< Электронная почта отдела
};

/**
 * @brief Модель данных вентиляционного оборудования для таблицы QTableView
 */
class SupplierRegistry : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit SupplierRegistry(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    /**
     * @brief Загрузка данных из текстового файла
     * @param filePath Путь к файлу
     * @return true, если загрузка успешна
     */
    bool importFromFile(const QString &filePath);
    
    /**
     * @brief Сохранение данных в текстовый файл
     * @param filePath Путь к файлу
     * @return true, если сохранение успешно
     */
    bool exportToFile(const QString &filePath) const;
    
    /**
     * @brief Проверка структуры текстового файла
     * @param filePath Путь к файлу
     * @return true, если структура файла корректна
     */
    static bool verifyFileFormat(const QString &filePath);

    /**
     * @brief Поиск оборудования по столбцу
     * @param columnIndex Индекс столбца
     * @param searchText Текст для поиска
     * @return Список индексов найденных строк
     */
    QList<int> findInColumn(int columnIndex, const QString &searchText) const;
    
    /**
     * @brief Получить данные об оборудовании по индексу
     * @param rowIndex Индекс строки
     * @return Структура Supplier
     */
    Supplier getSupplierData(int rowIndex) const;
    
    /**
     * @brief Установить данные об оборудовании по индексу
     * @param rowIndex Индекс строки
     * @param supplierData Данные об оборудовании
     */
    void updateSupplierData(int rowIndex, const Supplier &supplierData);
    
    /**
     * @brief Глобальный поиск по всем данным об оборудовании
     * @param searchText Текст для поиска
     * @return Индекс первого найденного соответствия (строка, столбец) или (-1, -1) если ничего не найдено
     */
    QPair<int, int> globalSearch(const QString &searchText) const;
    
    /**
     * @brief Сортировка данных об оборудовании по столбцу
     * @param columnIndex Индекс столбца для сортировки
     * @param sortOrder Порядок сортировки (по возрастанию/убыванию)
     */
    void sortByColumn(int columnIndex, Qt::SortOrder sortOrder = Qt::AscendingOrder);
    
    /**
     * @brief Очистить все данные об оборудовании
     */
    void clearAllData();

    /**
     * @brief Проверить корректность данных об оборудовании
     * @param inputValue Значение
     * @param columnIndex Индекс столбца
     * @return Корректное значение или пустая строка, если некорректно
     */
    static QString validateInputData(const QString &inputValue, int columnIndex);
    
    /**
     * @brief Отформатировать инвентарный номер
     * @param contractNum Номер договора
     * @return Форматированный инвентарный номер
     */
    static QString formatContractNumber(const QString &contractNum);
    
    /**
     * @brief Отформатировать дату регистрации
     * @param date Дата
     * @return Форматированная дата
     */
    static QString formatRegistrationDate(const QString &date);
    
    /**
     * @brief Отформатировать номер телефона
     * @param phone Номер телефона
     * @return Форматированный номер телефона
     */
    static QString formatPhoneNumber(const QString &phone);

private:
    QVector<Supplier> m_supplierData; ///< Данные об оборудовании
    int m_sortColumnIndex; ///< Колонка сортировки
    Qt::SortOrder m_sortOrder; ///< Порядок сортировки
};

#endif // SUPPLIER_REGISTRY_H 