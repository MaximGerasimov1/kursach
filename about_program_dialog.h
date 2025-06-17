#ifndef ABOUT_PROGRAM_DIALOG_H
#define ABOUT_PROGRAM_DIALOG_H

#include <QDialog>

/**
 * @brief Диалоговое окно с информацией о программе учета поставщиков вентиляции
 */
class AboutProgramDialog : public QDialog {
    Q_OBJECT
public:
    explicit AboutProgramDialog(QWidget *parent = nullptr);
    ~AboutProgramDialog();
};

#endif // ABOUT_PROGRAM_DIALOG_H 