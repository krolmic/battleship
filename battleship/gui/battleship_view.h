#ifndef BATTLESHIPVIEW_H
#define BATTLESHIPVIEW_H

#include "view_interface.h"
class ModelInterface;
class ControllerInterface;
class QDialog;

namespace GUI {
    
class BattleshipView : public ViewInterface
{
public:
    explicit BattleshipView(ModelInterface& model, ControllerInterface& controller);
    
    void showWaitingForGuestConnectingDialog() override;
    void closeTopDialog() override;
    
private:
    ModelInterface& model;
    ControllerInterface& ctrl;
    
    QDialog* topDialog{ nullptr };
};

} // end NS
#endif // BATTLESHIPVIEW_H
