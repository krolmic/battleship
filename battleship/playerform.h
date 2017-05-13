#ifndef PLAYERFORM_H
#define PLAYERFORM_H

#include <QWidget>

class PlayerForm : public QDialog
{
public:
    PlayerForm();

private:
    QLineEdit *nameLine;
    QDialogButtonBox *buttonBox;
    QGroupBox *horizontalGroupBox;

    void createPlayerInputFieldsGroup();
    void accept();
}; // Ende AdressBook

#endif
