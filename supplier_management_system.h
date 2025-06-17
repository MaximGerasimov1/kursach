#ifndef SUPPLIER_MANAGEMENT_SYSTEM_H
#define SUPPLIER_MANAGEMENT_SYSTEM_H

#include <QMainWindow>
#include <QTableView>
#include <QMenu>
#include <QAction>
#include <QTranslator>
#include <string>
#include "supplier_registry.h"
#include "supplier_manager.h"

/**
 * @brief Главное окно программы учета вентиляционного оборудования
 */
class SupplierManagementSystem : public QMainWindow {
    Q_OBJECT
public:
    explicit SupplierManagementSystem(QWidget *parent = nullptr);
    ~SupplierManagementSystem();

private slots:
    /**
     * @brief Загрузить данные из файла
     */
    void loadFromFile();
    
    /**
     * @brief Выгрузить данные в файл
     */
    void saveToFile();
    
    /**
     * @brief Добавить новое оборудование
     */
    void createNewSupplier();
    
    /**
     * @brief Удалить выбранное оборудование
     */
    void removeSelectedSupplier();
    
    /**
     * @brief Поиск по выбранному столбцу
     */
    void searchInCurrentColumn();
    
    /**
     * @brief Глобальный поиск по всей таблице
     */
    void executeGlobalSearch();
    
    /**
     * @brief Сортировка по столбцу
     * @param columnIndex Индекс столбца
     */
    void applySorting(int columnIndex);
    
    /**
     * @brief Показать информацию о программе
     */
    void displayAboutDialog();
    
    /**
     * @brief Переключить язык интерфейса
     */
    void switchLanguage();
    
    /**
     * @brief Показать контекстное меню
     * @param position Позиция курсора
     */
    void showContextMenu(const QPoint &position);

private:
    void initializeMenus();
    void setupActionButtons();
    void configureTableView();
    void loadUserSettings();
    void saveUserSettings();
    void updateTranslatedTexts();

    QTableView *m_tableView;
    SupplierRegistry *m_dataModel;
    SupplierManager *m_manager;
    QMenu *m_fileMenu;
    QMenu *m_editMenu;
    QMenu *m_languageMenu;
    QMenu *m_helpMenu;
    QAction *m_loadAction;
    QAction *m_saveAction;
    QAction *m_addAction;
    QAction *m_deleteAction;
    QAction *m_columnSearchAction;
    QAction *m_globalSearchAction;
    QAction *m_aboutAction;
    QAction *m_langRuAction;
    QAction *m_langEnAction;
    QAction *m_langTtAction;
    QTranslator *m_translator;
    std::string m_currentLanguage;
    int m_activeColumnIndex;  // Выбранный столбец для поиска/сортировки
};

#endif // SUPPLIER_MANAGEMENT_SYSTEM_H 