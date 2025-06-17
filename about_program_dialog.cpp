#include "about_program_dialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

/**
 * @brief Конструктор диалогового окна информации о программе
 */
AboutProgramDialog::AboutProgramDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("About Program"));
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel(tr("<b>Ventilation Equipment Suppliers Management System</b><br>Institute: [Институт]<br>Course: [Курс]<br>Group: [Группа]<br>Name: [Фамилия Имя Отчество]"), this);
    layout->addWidget(label);
    QPushButton *closeButton = new QPushButton(tr("Close"), this);
    connect(closeButton, &QPushButton::clicked, this, &AboutProgramDialog::accept);
    layout->addWidget(closeButton);
    setLayout(layout);
}

AboutProgramDialog::~AboutProgramDialog() {} 