#ifndef PLAYERFORM_H
#define PLAYERFORM_H
#include "player.h"
#include <QDialog>

class QLineEdit;
class QDialogButtonBox;
class QGroupBox;
class QPushButton;
class ControllerInterface;

namespace GUI {

/// A simple class that defines graphical interface of the form in which players are able enter the name and age
class PlayerForm : public QDialog
{
    Q_OBJECT
public:
    PlayerForm(ControllerInterface& ctrl, QWidget* parent = nullptr);
//     ~PlayerForm() { qDebug() << "~PlayerForm() dtor !!!!!"; }
    
// protected:
//     void closeEvent(QCloseEvent*) override;

private slots:
//     void hostGame();
//     void connectToHost();
//     void accept();
    
private:
    void createPlayerInputFieldsGroup();
    QGroupBox* createPlayerConnectionSelectGroup();
    /**
     * @return true if name is not empty
     */
    bool validateUserInput();
    
    ControllerInterface& ctrl;
    Player *player;
    QLineEdit *nameLine;
    QLineEdit *ageLine;
//     QDialogButtonBox *buttonBox;
    QGroupBox *horizontalGroupBox;
    QPushButton* hostGameBtn;
    QPushButton* directConnBtn;
};

} // end NS
#endif
