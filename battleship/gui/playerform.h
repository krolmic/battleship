#ifndef PLAYERFORM_H
#define PLAYERFORM_H
#include "player.h"
#include <QWidget>

class PlayerForm : public QDialog
{
public:
    PlayerForm();

private:
    Player *player;
    QLineEdit *nameLine;
    QLineEdit *ageLine;
    QDialogButtonBox *buttonBox;
    QGroupBox *horizontalGroupBox;

    void createPlayerInputFieldsGroup();
    void accept();
}; // Ende AdressBook

#endif
