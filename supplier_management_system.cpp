#include "supplier_management_system.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QSettings>
#include <QHeaderView>
#include <QApplication>
#include <QTranslator>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <string>
#include "about_program_dialog.h"

/**
 * @brief Конструктор главного окна
 */
SupplierManagementSystem::SupplierManagementSystem(QWidget *parent)
    : QMainWindow(parent),
      m_tableView(new QTableView(this)),
      m_dataModel(new SupplierRegistry(this)),
      m_manager(new SupplierManager(m_dataModel, this)),
      m_activeColumnIndex(0)
{
    // Загружаем русский язык по умолчанию
    m_currentLanguage = "ru";
    
    // Создаем переводчика и пробуем загрузить перевод
    m_translator = new QTranslator(this);
    
    // Получаем абсолютный путь к директории с переводами
    QString translationsPath = QCoreApplication::applicationDirPath() + QStringLiteral("/translations/");
    std::string qmFile = translationsPath.QString::toStdString() + m_currentLanguage + ".qm";

    // Проверяем, что файл существует
    QFile file(QString::fromStdString(qmFile));
    qDebug() << "Translation file exists:" << file.exists() << qmFile;
    
    // Загружаем перевод
    bool loaded = m_translator->load(QString::fromStdString(qmFile));
    qDebug() << "Translator loaded from file:" << loaded << qmFile;
    
    // Устанавливаем переводчик для приложения
    if (loaded) {
        qApp->installTranslator(m_translator);
    }

    configureTableView();
    setupActionButtons();
    initializeMenus();
    setCentralWidget(m_tableView);
    loadUserSettings();
    updateTranslatedTexts();
    connect(m_tableView->horizontalHeader(), &QHeaderView::sectionClicked, this, &SupplierManagementSystem::applySorting);
    m_tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_tableView, &QTableView::customContextMenuRequested, this, &SupplierManagementSystem::showContextMenu);
}

/**
 * @brief Деструктор главного окна
 */
SupplierManagementSystem::~SupplierManagementSystem() {
    saveUserSettings();
}

void SupplierManagementSystem::configureTableView() {
    m_tableView->setModel(m_dataModel);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    m_tableView->setAlternatingRowColors(true);
}

void SupplierManagementSystem::setupActionButtons() {
    m_loadAction = new QAction(tr("Import"), this);
    m_saveAction = new QAction(tr("Export"), this);
    m_addAction = new QAction(tr("Add Supplier"), this);
    m_deleteAction = new QAction(tr("Delete"), this);
    m_globalSearchAction = new QAction(tr("Global Search"), this);
    m_columnSearchAction = new QAction(tr("Search in Column"), this);
    m_aboutAction = new QAction(tr("About"), this);
    m_langRuAction = new QAction(tr("Russian"), this);
    m_langEnAction = new QAction(tr("English"), this);
    m_langTtAction = new QAction(tr("Tatar"), this);

    connect(m_loadAction, &QAction::triggered, this, &SupplierManagementSystem::loadFromFile);
    connect(m_saveAction, &QAction::triggered, this, &SupplierManagementSystem::saveToFile);
    connect(m_addAction, &QAction::triggered, this, &SupplierManagementSystem::createNewSupplier);
    connect(m_deleteAction, &QAction::triggered, this, &SupplierManagementSystem::removeSelectedSupplier);
    connect(m_columnSearchAction, &QAction::triggered, this, &SupplierManagementSystem::searchInCurrentColumn);
    connect(m_globalSearchAction, &QAction::triggered, this, &SupplierManagementSystem::executeGlobalSearch);
    connect(m_aboutAction, &QAction::triggered, this, &SupplierManagementSystem::displayAboutDialog);
    connect(m_langRuAction, &QAction::triggered, this, &SupplierManagementSystem::switchLanguage);
    connect(m_langEnAction, &QAction::triggered, this, &SupplierManagementSystem::switchLanguage);
    connect(m_langTtAction, &QAction::triggered, this, &SupplierManagementSystem::switchLanguage);
}

void SupplierManagementSystem::initializeMenus() {
    m_fileMenu = menuBar()->addMenu(tr("File"));
    m_fileMenu->addAction(m_loadAction);
    m_fileMenu->addAction(m_saveAction);
    m_editMenu = menuBar()->addMenu(tr("Edit"));
    m_editMenu->addAction(m_addAction);
    m_editMenu->addAction(m_deleteAction);
    m_editMenu->addAction(m_globalSearchAction);
    m_languageMenu = menuBar()->addMenu(tr("Language"));
    m_languageMenu->addAction(m_langRuAction);
    m_languageMenu->addAction(m_langEnAction);
    m_languageMenu->addAction(m_langTtAction);
    m_helpMenu = menuBar()->addMenu(tr("Help"));
    m_helpMenu->addAction(m_aboutAction);
}

void SupplierManagementSystem::loadFromFile() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QStringLiteral(""), tr("Text Files (*.txt)"));
    if (!filePath.isEmpty()) {
        if (!SupplierRegistry::verifyFileFormat(filePath)) {
            QMessageBox::warning(this, tr("Error"), tr("File structure is invalid!"));
            return;
        }
        if (!m_manager->loadDataFromFile(filePath)) {
            QMessageBox::warning(this, tr("Error"), tr("Failed to load file!"));
        }
    }
}

void SupplierManagementSystem::saveToFile() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), QStringLiteral(""), tr("Text Files (*.txt)"));
    if (!filePath.isEmpty()) {
        if (!m_manager->saveDataToFile(filePath)) {
            QMessageBox::warning(this, tr("Error"), tr("Failed to save file!"));
        }
    }
}

void SupplierManagementSystem::createNewSupplier() {
    Supplier supplier; // Можно добавить диалог для ввода данных, пока пустой
    m_manager->addSupplier(supplier);
}

void SupplierManagementSystem::removeSelectedSupplier() {
    QModelIndexList selection = m_tableView->selectionModel()->selectedRows();
    if (!selection.isEmpty()) {
        m_manager->removeSupplier(selection.first().row());
    }
}

/**
 * @brief Показывает контекстное меню
 * @param position Позиция курсора
 */
void SupplierManagementSystem::showContextMenu(const QPoint &position) {
    // Преобразуем координаты в глобальные для правильного позиционирования меню
    QPoint globalPos = m_tableView->viewport()->mapToGlobal(position);
    
    // Получаем индекс по позиции клика
    QModelIndex index = m_tableView->indexAt(position);
    if (index.isValid()) {
        // Сохраняем столбец, по которому был клик
        m_activeColumnIndex = index.column();
    }
    
    QMenu menu(this);
    menu.addAction(m_addAction);
    menu.addAction(m_deleteAction);
    menu.addAction(m_columnSearchAction);
    menu.exec(globalPos);
}

/**
 * @brief Выполняет поиск по выбранному столбцу
 * 
 * Запрашивает у пользователя текст для поиска и выполняет поиск
 * только в текущем выбранном столбце таблицы
 */
void SupplierManagementSystem::searchInCurrentColumn() {
    bool ok;
    
    // Используем сохраненный столбец
    int column = m_activeColumnIndex;
    
    QString text = QInputDialog::getText(this, tr("Search in Column"), 
                                        tr("Enter search text for column %1:").arg(m_manager->getHeaderTitle(column, Qt::Horizontal).toString()), 
                                        QLineEdit::Normal, QStringLiteral(""), &ok);
                                        
    if (ok && !text.isEmpty()) {
        QList<int> results = m_manager->searchByColumn(column, text);
        if (!results.isEmpty()) {
            // Выбираем первую найденную строку
            m_tableView->selectRow(results.first());
            m_tableView->scrollTo(m_tableView->model()->index(results.first(), column));
        } else {
            QMessageBox::information(this, tr("Search"), tr("No results found in this column."));
        }
    }
}

/**
 * @brief Выполняет глобальный поиск по всем столбцам таблицы
 * 
 * Запрашивает у пользователя текст для поиска и выполняет поиск
 * по всем столбцам и строкам таблицы
 */
void SupplierManagementSystem::executeGlobalSearch() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Global Search"), tr("Enter search text:"), QLineEdit::Normal, QStringLiteral(""), &ok);
    if (ok && !text.isEmpty()) {
        QPair<int, int> result = m_manager->performGlobalSearch(text);
        if (result.first >= 0) {
            // Выбираем строку и прокручиваем до найденного элемента
            m_tableView->selectRow(result.first);
            m_tableView->scrollTo(m_tableView->model()->index(result.first, result.second));
        } else {
            QMessageBox::information(this, tr("Search"), tr("No results found."));
        }
    }
}

void SupplierManagementSystem::applySorting(int columnIndex) {
    static int currentColumn = -1;
    static Qt::SortOrder currentOrder = Qt::AscendingOrder;
    
    if (currentColumn == columnIndex) {
        // Переключаем порядок сортировки
        currentOrder = (currentOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
    } else {
        currentColumn = columnIndex;
        currentOrder = Qt::AscendingOrder;
    }
    
    m_manager->sortDataByColumn(columnIndex, currentOrder);
}

void SupplierManagementSystem::displayAboutDialog() {
    AboutProgramDialog dlg(this);
    dlg.exec();
}

void SupplierManagementSystem::switchLanguage() {
    QAction *action = qobject_cast<QAction*>(sender());
    if (!action) return;
    std::string lang;
    if (action == m_langRuAction) lang = "ru";
    else if (action == m_langEnAction) lang = "en";
    else if (action == m_langTtAction) lang = "ro";
    if (lang == m_currentLanguage) return;
    
    qApp->removeTranslator(m_translator);
    m_currentLanguage = lang;
    
    delete m_translator;
    m_translator = new QTranslator(this);
    
    // Получаем абсолютный путь к директории с переводами
    QString translationsPath = QCoreApplication::applicationDirPath() + QStringLiteral("/translations/");
    std::string qmFile = translationsPath.QString::toStdString() + m_currentLanguage + ".qm";
    
    // Проверяем, что файл существует
    QFile file(QString::fromStdString(qmFile));
    qDebug() << "Translation file exists:" << file.exists() << qmFile;
    
    // Загружаем перевод
    bool loaded = m_translator->load(QString::fromStdString(qmFile));
    qDebug() << "Translator loaded from file:" << loaded << qmFile;
    
    if (loaded) {
        qApp->installTranslator(m_translator);
    }
    
    updateTranslatedTexts();
    m_manager->updateHeaderDisplay(Qt::Horizontal, 0, m_manager->getColumnCount() - 1);
}

void SupplierManagementSystem::loadUserSettings() {
    QSettings settings(QStringLiteral("VentilationSuppliers"), QStringLiteral("MainWindow"));
    restoreGeometry(settings.value(QStringLiteral("geometry")).toByteArray());
    restoreState(settings.value(QStringLiteral("windowState")).toByteArray());
    
    QHeaderView *header = m_tableView->horizontalHeader();
    for (int i = 0; i < m_manager->getColumnCount(); ++i) {
        QString key = QStringLiteral("column_width_") + QString::number(i);
        if (settings.contains(key)) {
            int width = settings.value(key).toInt();
            header->resizeSection(i, width);
        }
    }
}

void SupplierManagementSystem::saveUserSettings() {
    QSettings settings(QStringLiteral("VentilationSuppliers"), QStringLiteral("MainWindow"));
    settings.setValue(QStringLiteral("geometry"), saveGeometry());
    settings.setValue(QStringLiteral("windowState"), saveState());

    QHeaderView *header = m_tableView->horizontalHeader();
    for (int i = 0; i < m_manager->getColumnCount(); ++i) {
        QString key = QStringLiteral("column_width_") + QString::number(i);
        settings.setValue(key, header->sectionSize(i));
    }
}

void SupplierManagementSystem::updateTranslatedTexts() {
    m_loadAction->setText(tr("Import"));
    m_saveAction->setText(tr("Export"));
    m_addAction->setText(tr("Add Supplier"));
    m_deleteAction->setText(tr("Delete"));
    m_columnSearchAction->setText(tr("Search in Column"));
    m_globalSearchAction->setText(tr("Global Search"));
    m_aboutAction->setText(tr("About"));
    m_langRuAction->setText(tr("Russian"));
    m_langEnAction->setText(tr("English"));
    m_langTtAction->setText(tr("Romanian"));
    m_fileMenu->setTitle(tr("File"));
    m_editMenu->setTitle(tr("Edit"));
    m_languageMenu->setTitle(tr("Language"));
    m_helpMenu->setTitle(tr("Help"));
    setWindowTitle(tr("Ventilation Equipment Suppliers Management System"));
    
    m_manager->updateHeaderDisplay(Qt::Horizontal, 0, m_manager->getColumnCount() - 1);
} 
