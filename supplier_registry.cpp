#include "supplier_registry.h"
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <algorithm>

/**
 * @brief Конструктор модели данных вентиляционного оборудования
 * @param parent Родительский объект
 */
SupplierRegistry::SupplierRegistry(QObject *parent)
    : QAbstractTableModel(parent), m_sortColumnIndex(-1), m_sortOrder(Qt::AscendingOrder) {}

/**
 * @brief Возвращает количество строк в модели
 * @param parent Родительский индекс (не используется)
 * @return Количество строк
 */
int SupplierRegistry::rowCount(const QModelIndex &/*parent*/) const {
    return m_supplierData.size();
}

/**
 * @brief Очистить все данные об оборудовании
 */
void SupplierRegistry::clearAllData() {
    beginResetModel();
    m_supplierData.clear();
    endResetModel();
}

/**
 * @brief Возвращает количество столбцов в модели
 * @param parent Родительский индекс (не используется)
 * @return Количество столбцов
 */
int SupplierRegistry::columnCount(const QModelIndex &/*parent*/) const {
    return 9; // количество полей в структуре Supplier
}

/**
 * @brief Форматирует инвентарный номер оборудования
 * @param contractNum Инвентарный номер
 * @return Отформатированный инвентарный номер
 */
QString SupplierRegistry::formatContractNumber(const QString &contractNum) {
    QString result = contractNum.trimmed().toUpper();
    
    // Удаляем все пробелы из номера договора
    QString filtered;
    for (const QChar &ch : result) {
        if (!ch.isSpace()) {
            filtered.append(ch);
        }
    }
    
    return filtered;
}

/**
 * @brief Загружает данные из файла
 * @param filePath Путь к файлу
 * @return true если данные были успешно загружены
 */
bool SupplierRegistry::importFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    
    QTextStream in(&file);
    QVector<Supplier> tempData;
    
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(QStringLiteral(";"));
        
        if (parts.size() != 9)
            continue;
            
        Supplier supplier;
        supplier.name = parts[0];
        supplier.contractNumber = parts[1];
        supplier.registrationDate = parts[2];
        supplier.productCategory = parts[3];
        supplier.qualityRating = parts[4];
        supplier.deliveryTime = parts[5];
        supplier.contactPerson = parts[6];
        supplier.phoneNumber = parts[7];
        supplier.emailAddress = parts[8];
        
        tempData.append(supplier);
    }
    
    beginResetModel();
    m_supplierData = tempData;
    endResetModel();
    
    return true;
}

/**
 * @brief Возвращает данные для отображения в таблице
 * @param index Индекс модели
 * @param role Роль для отображения
 * @return Данные для отображения
 */
QVariant SupplierRegistry::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_supplierData.size() || index.column() >= 9)
        return QVariant();
        
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        const Supplier &supplier = m_supplierData[index.row()];
        switch (index.column()) {
        case 0: return supplier.name;
        case 1: return supplier.contractNumber;
        case 2: return supplier.registrationDate;
        case 3: return supplier.productCategory;
        case 4: return supplier.qualityRating;
        case 5: return supplier.deliveryTime;
        case 6: return supplier.contactPerson;
        case 7: return supplier.phoneNumber;
        case 8: return supplier.emailAddress;
        default: return QVariant();
        }
    }
    
    return QVariant();
}

/**
 * @brief Сохраняет данные в файл
 * @param filePath Путь к файлу
 * @return true если данные были успешно сохранены
 */
bool SupplierRegistry::exportToFile(const QString &filePath) const {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
        
    QTextStream out(&file);
    for (const Supplier &supplier : m_supplierData) {
        out << supplier.name << ";" << supplier.contractNumber << ";" 
            << supplier.registrationDate << ";" << supplier.productCategory << ";"
            << supplier.qualityRating << ";" << supplier.deliveryTime << ";"
            << supplier.contactPerson << ";" << supplier.phoneNumber << ";"
            << supplier.emailAddress << "\n";
    }
    
    return true;
}

/**
 * @brief Возвращает заголовки столбцов и строк
 * @param section Номер секции (столбца или строки)
 * @param orientation Ориентация (горизонтальная или вертикальная)
 * @param role Роль для отображения
 * @return Данные заголовка
 */
QVariant SupplierRegistry::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();
        
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return tr("Company Name");
        case 1: return tr("Contract Number");
        case 2: return tr("Registration Date");
        case 3: return tr("Product Category");
        case 4: return tr("Quality Rating");
        case 5: return tr("Delivery Time (days)");
        case 6: return tr("Contact Person");
        case 7: return tr("Phone Number");
        case 8: return tr("Email Address");
        default: return QVariant();
        }
    }
    
    return QVariant();
}

/**
 * @brief Форматирует дату регистрации
 * @param date Дата
 * @return Отформатированная дата
 */
QString SupplierRegistry::formatRegistrationDate(const QString &date) {
    // Проверка формата даты ДД.ММ.ГГГГ
    QString formatted = date.trimmed();
    
    // Удаляем все нецифровые символы кроме точек
    QString filtered;
    for (const QChar &ch : formatted) {
        if (ch.isDigit() || ch == QLatin1Char('.')) {
            filtered.append(ch);
        }
    }
    
    // Простое форматирование даты
    QStringList parts = filtered.split(QStringLiteral("."));
    if (parts.size() == 3) {
        // День
        QString day = parts[0];
        if (day.length() == 1) day = QStringLiteral("0") + day;
        
        // Месяц
        QString month = parts[1];
        if (month.length() == 1) month = QStringLiteral("0") + month;
        
        // Год
        QString year = parts[2];
        if (year.length() == 2) year = QStringLiteral("20") + year; // Предполагаем 20xx год
        
        return day + QStringLiteral(".") + month + QStringLiteral(".") + year;
    }
    
    return formatted;
}

/**
 * @brief Форматирует номер телефона
 * @param phone Номер телефона
 * @return Отформатированный номер телефона
 */
QString SupplierRegistry::formatPhoneNumber(const QString &phone) {
    QString formatted = phone.trimmed();
    
    // Удаляем все символы кроме цифр, скобок, дефиса и плюса
    QString filtered;
    for (const QChar &ch : formatted) {
        if (ch.isDigit() || ch == QLatin1Char('+') || ch == QLatin1Char('(') || ch == QLatin1Char(')') || ch == QLatin1Char('-')) {
            filtered.append(ch);
        }
    }
    
    // Если нет символа +, добавляем его в начало
    if (!filtered.startsWith(QStringLiteral("+"))) {
        if (filtered.length() >= 10) {
            if (filtered.startsWith(QStringLiteral("8")) && filtered.length() >= 11) {
                filtered = QStringLiteral("+7") + filtered.mid(1);
            } else if (!filtered.startsWith(QStringLiteral("7"))) {
                filtered = QStringLiteral("+7") + filtered;
            } else {
                filtered = QStringLiteral("+") + filtered;
            }
        }
    }
    
    return filtered;
}

/**
 * @brief Возвращает флаги для ячеек таблицы
 * @param index Индекс модели
 * @return Флаги для ячейки
 */
Qt::ItemFlags SupplierRegistry::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
        
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

/**
 * @brief Устанавливает данные в модель
 * @param index Индекс модели
 * @param value Значение для установки
 * @param role Роль для установки
 * @return true если данные были успешно установлены
 */
bool SupplierRegistry::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || index.row() >= m_supplierData.size() || index.column() >= 9)
        return false;
        
    if (role == Qt::EditRole) {
        Supplier &supplier = m_supplierData[index.row()];
        QString validatedValue = validateInputData(value.toString(), index.column());
        
        // Для обязательных полей проверяем на пустоту
        if ((index.column() == 0 || index.column() == 1 || index.column() == 2) && validatedValue.isEmpty()) {
            return false;
        }
        
        switch (index.column()) {
        case 0: supplier.name = validatedValue; break;
        case 1: supplier.contractNumber = validatedValue; break;
        case 2: supplier.registrationDate = validatedValue; break;
        case 3: supplier.productCategory = validatedValue; break;
        case 4: supplier.qualityRating = validatedValue; break;
        case 5: supplier.deliveryTime = validatedValue; break;
        case 6: supplier.contactPerson = validatedValue; break;
        case 7: supplier.phoneNumber = validatedValue; break;
        case 8: supplier.emailAddress = validatedValue; break;
        default: return false;
        }
        
        emit dataChanged(index, index);
        return true;
    }
    
    return false;
}

/**
 * @brief Проверяет и форматирует данные
 * @param inputValue Значение для проверки
 * @param columnIndex Индекс столбца для определения типа проверки
 * @return Проверенное и отформатированное значение или пустую строку в случае ошибки
 */
QString SupplierRegistry::validateInputData(const QString &inputValue, int columnIndex) {
    if (inputValue.isEmpty()) return QString();
    
    switch (columnIndex) {
    case 0: // Название компании
        {
            if (inputValue.length() < 3) {
                QMessageBox::warning(nullptr, QObject::tr("Invalid Data"), 
                                    QObject::tr("Company name is too short"));
                return QString();
            }
            return inputValue.trimmed();
        }
    case 1: // Номер договора
        {
            QString contractNum = inputValue.trimmed();
            
            if (contractNum.length() < 5) {
                QMessageBox::warning(nullptr, QObject::tr("Invalid Data"), 
                                    QObject::tr("Contract number must be at least 5 characters"));
                return QString();
            }
            
            return formatContractNumber(contractNum);
        }
    case 2: // Дата регистрации
        {
            QString date = inputValue.trimmed();
            
            // Простая проверка на формат даты ДД.ММ.ГГГГ
            QStringList parts = date.split(QStringLiteral("."));
            if (parts.size() == 3) {
                bool dayOk, monthOk, yearOk;
                int day = parts[0].toInt(&dayOk);
                int month = parts[1].toInt(&monthOk);
                int year = parts[2].toInt(&yearOk);
                
                if (dayOk && monthOk && yearOk && 
                    day >= 1 && day <= 31 && 
                    month >= 1 && month <= 12 && 
                    year >= 2000 && year <= QDate::currentDate().year()) {
                    return formatRegistrationDate(date);
                }
            }
            
            QMessageBox::warning(nullptr, QObject::tr("Invalid Data"), 
                                QObject::tr("Invalid date format. Please use DD.MM.YYYY"));
            return QString();
        }
    case 3: // Категория продукции
        {
            QString category = inputValue.trimmed();
            
            if (category.length() < 3) {
                QMessageBox::warning(nullptr, QObject::tr("Invalid Data"), 
                                    QObject::tr("Product category name is too short"));
                return QString();
            }
            
            return category;
        }
    case 4: // Рейтинг качества
        {
            bool ok;
            int rating = inputValue.toInt(&ok);
            
            if (ok && rating >= 1 && rating <= 5) {
                return QString::number(rating);
            } else {
                QMessageBox::warning(nullptr, QObject::tr("Invalid Data"), 
                                    QObject::tr("Invalid quality rating. Must be between 1 and 5."));
                return QString();
            }
        }
    case 5: // Срок поставки
        {
            bool ok;
            int days = inputValue.toInt(&ok);
            
            if (ok && days > 0 && days <= 365) {
                return QString::number(days);
            } else {
                QMessageBox::warning(nullptr, QObject::tr("Invalid Data"), 
                                    QObject::tr("Invalid delivery time. Must be between 1 and 365 days."));
                return QString();
            }
        }
    case 6: // Контактное лицо
        {
            QString contactName = inputValue.trimmed();
            
            if (contactName.length() < 5) {
                QMessageBox::warning(nullptr, QObject::tr("Invalid Data"), 
                                    QObject::tr("Contact person name is too short"));
                return QString();
            }
            
            return contactName;
        }
    case 7: // Номер телефона
        {
            QString phone = inputValue.trimmed();
            
            if (phone.length() < 10) {
                QMessageBox::warning(nullptr, QObject::tr("Invalid Data"), 
                                    QObject::tr("Phone number is too short"));
                return QString();
            }
            
            return formatPhoneNumber(phone);
        }
    case 8: // Email
        {
            QString email = inputValue.trimmed();
            
            // Простая проверка на наличие @ и . в адресе
            if (!email.contains(QStringLiteral("@")) || !email.contains(QStringLiteral("."))) {
                QMessageBox::warning(nullptr, QObject::tr("Invalid Data"), 
                                    QObject::tr("Invalid email address format"));
                return QString();
            }
            
            return email;
        }
    default:
        return inputValue;
    }
}

/**
 * @brief Вставляет строки в модель
 * @param row Позиция вставки
 * @param count Количество строк для вставки
 * @param parent Родительский индекс
 * @return true если строки были успешно вставлены
 */
bool SupplierRegistry::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        m_supplierData.insert(row, Supplier());
    }
    endInsertRows();
    return true;
}

/**
 * @brief Удаляет строки из модели
 * @param row Позиция удаления
 * @param count Количество строк для удаления
 * @param parent Родительский индекс
 * @return true если строки были успешно удалены
 */
bool SupplierRegistry::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
        m_supplierData.removeAt(row);
    }
    endRemoveRows();
    return true;
}

/**
 * @brief Проверяет структуру файла
 * @param filePath Путь к файлу
 * @return true если структура файла корректна
 */
bool SupplierRegistry::verifyFileFormat(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
        
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(QStringLiteral(";"));
        if (parts.size() != 9)
            return false;
    }
    
    return true;
}

/**
 * @brief Возвращает данные оборудования по индексу строки
 * @param rowIndex Индекс строки
 * @return Структура данных оборудования
 */
Supplier SupplierRegistry::getSupplierData(int rowIndex) const {
    if (rowIndex < 0 || rowIndex >= m_supplierData.size())
        return Supplier();
        
    return m_supplierData[rowIndex];
}

/**
 * @brief Устанавливает данные оборудования по индексу строки
 * @param rowIndex Индекс строки
 * @param supplierData Данные об оборудовании
 */
void SupplierRegistry::updateSupplierData(int rowIndex, const Supplier &supplierData) {
    if (rowIndex < 0 || rowIndex >= m_supplierData.size())
        return;
        
    m_supplierData[rowIndex] = supplierData;
    emit dataChanged(index(rowIndex, 0), index(rowIndex, 8));
}

/**
 * @brief Ищет данные в указанном столбце
 * @param columnIndex Индекс столбца
 * @param searchText Текст для поиска
 * @return Список индексов строк, содержащих искомый текст
 */
QList<int> SupplierRegistry::findInColumn(int columnIndex, const QString &searchText) const {
    QList<int> result;
    for (int i = 0; i < m_supplierData.size(); ++i) {
        QString value;
        switch (columnIndex) {
        case 0: value = m_supplierData[i].name; break;
        case 1: value = m_supplierData[i].contractNumber; break;
        case 2: value = m_supplierData[i].registrationDate; break;
        case 3: value = m_supplierData[i].productCategory; break;
        case 4: value = m_supplierData[i].qualityRating; break;
        case 5: value = m_supplierData[i].deliveryTime; break;
        case 6: value = m_supplierData[i].contactPerson; break;
        case 7: value = m_supplierData[i].phoneNumber; break;
        case 8: value = m_supplierData[i].emailAddress; break;
        }
        
        if (value.contains(searchText, Qt::CaseInsensitive))
            result.append(i);
    }
    
    return result;
}

/**
 * @brief Выполняет глобальный поиск по всем столбцам и строкам
 * @param searchText Текст для поиска
 * @return Пара (строка, столбец) первого найденного совпадения или (-1, -1), если ничего не найдено
 */
QPair<int, int> SupplierRegistry::globalSearch(const QString &searchText) const {
    for (int row = 0; row < m_supplierData.size(); ++row) {
        const Supplier &supplier = m_supplierData[row];
        
        if (supplier.name.contains(searchText, Qt::CaseInsensitive))
            return qMakePair(row, 0);
        if (supplier.contractNumber.contains(searchText, Qt::CaseInsensitive))
            return qMakePair(row, 1);
        if (supplier.registrationDate.contains(searchText, Qt::CaseInsensitive))
            return qMakePair(row, 2);
        if (supplier.productCategory.contains(searchText, Qt::CaseInsensitive))
            return qMakePair(row, 3);
        if (supplier.qualityRating.contains(searchText, Qt::CaseInsensitive))
            return qMakePair(row, 4);
        if (supplier.deliveryTime.contains(searchText, Qt::CaseInsensitive))
            return qMakePair(row, 5);
        if (supplier.contactPerson.contains(searchText, Qt::CaseInsensitive))
            return qMakePair(row, 6);
        if (supplier.phoneNumber.contains(searchText, Qt::CaseInsensitive))
            return qMakePair(row, 7);
        if (supplier.emailAddress.contains(searchText, Qt::CaseInsensitive))
            return qMakePair(row, 8);
    }
    
    // Not found
    return qMakePair(-1, -1);
}

/**
 * @brief Сортирует данные модели по указанному столбцу
 * @param columnIndex Индекс столбца для сортировки
 * @param sortOrder Порядок сортировки (по возрастанию или убыванию)
 */
void SupplierRegistry::sortByColumn(int columnIndex, Qt::SortOrder sortOrder) {
    if (m_sortColumnIndex == columnIndex) {
        if (m_sortOrder == sortOrder) {
            m_sortColumnIndex = -1;
            m_sortOrder = Qt::AscendingOrder;
            
            beginResetModel();
            endResetModel();
            return;
        }
    }
    
    m_sortColumnIndex = columnIndex;
    m_sortOrder = sortOrder;
    
    beginResetModel();
    std::sort(m_supplierData.begin(), m_supplierData.end(), [this](const Supplier &a, const Supplier &b) {
        QString valueA, valueB;
        switch (m_sortColumnIndex) {
        case 0: valueA = a.name; valueB = b.name; break;
        case 1: valueA = a.contractNumber; valueB = b.contractNumber; break;
        case 2: valueA = a.registrationDate; valueB = b.registrationDate; break;
        case 3: valueA = a.productCategory; valueB = b.productCategory; break;
        case 4:
            {
                // Числовое сравнение для рейтинга качества
                bool okA, okB;
                int numA = a.qualityRating.toInt(&okA);
                int numB = b.qualityRating.toInt(&okB);
                if (okA && okB) {
                    return m_sortOrder == Qt::AscendingOrder ? numA < numB : numA > numB;
                }
                valueA = a.qualityRating;
                valueB = b.qualityRating;
                break;
            }
        case 5:
            {
                // Числовое сравнение для срока поставки
                bool okA, okB;
                int numA = a.deliveryTime.toInt(&okA);
                int numB = b.deliveryTime.toInt(&okB);
                if (okA && okB) {
                    return m_sortOrder == Qt::AscendingOrder ? numA < numB : numA > numB;
                }
                valueA = a.deliveryTime;
                valueB = b.deliveryTime;
                break;
            }
        case 6: valueA = a.contactPerson; valueB = b.contactPerson; break;
        case 7: valueA = a.phoneNumber; valueB = b.phoneNumber; break;
        case 8: valueA = a.emailAddress; valueB = b.emailAddress; break;
        default: return false;
        }
        
        if (m_sortOrder == Qt::AscendingOrder)
            return valueA < valueB;
        else
            return valueA > valueB;
    });
    endResetModel();
} 