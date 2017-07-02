#ifndef PLAYERFORM_H
#define PLAYERFORM_H
#include "player.h"
#include <QDialog>

class QLineEdit;
class QDialogButtonBox;
class QGroupBox;
class QPushButton;
class Application;


class PlayerForm : public QDialog
{
    Q_OBJECT
public:
    PlayerForm(Application& app, QWidget* parent = nullptr);
//     ~PlayerForm() { qDebug() << "~PlayerForm() dtor !!!!!"; }
    
// protected:
//     void closeEvent(QCloseEvent*) override;

private slots:
    void hostGame();
    void connectToHost();
    void accept();
    
private:
    Application& app;
    Player *player;
    QLineEdit *nameLine;
    QLineEdit *ageLine;
    QDialogButtonBox *buttonBox;
    QGroupBox *horizontalGroupBox;
    QPushButton* hostGameBtn;
    QPushButton* directConnBtn;

    void createPlayerInputFieldsGroup();
    QGroupBox* createPlayerConnectionSelectGroup();
};

#endif
