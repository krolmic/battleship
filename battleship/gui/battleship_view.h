#ifndef BATTLESHIPVIEW_H
#define BATTLESHIPVIEW_H

#include <string>

class ModelInterface;
class ControllerInterface;
class QDialog;

namespace GUI {
    
class BattleshipView
{
public:
    explicit BattleshipView(ModelInterface& model, ControllerInterface& controller);
    
    /**
     * @param msg actual error message message
     * @param title title of the window like QMessageBox
     */
    void showErrorMessage(const std::string& msg, const std::string& title =  "Oops, something went wrong");
    
    /**
     * inform user that he has to be patient. Being patient is always good... well at least for someone.
     */
    void showWaitingForGuestConnectingDialog();
    
    /**
     * closes top dialog programmatically, also without user having to click. Such dialog can be a popup informing about errors.
     */
    void closeTopDialog();
    
    
//     /**
//      * @see ViewInterface#showWaitingForGuestConnectingDialog()
//      */
//     void showWaitingForGuestConnectingDialog() override;
//     
//     /**
//      * @see ViewInterface#closeTopDialog()
//      */
//     void closeTopDialog() override;
//     
//     /**
//      * @see ViewInterface#showErrorMessage(const std::string&, const std::string&)
//      */
//     void showErrorMessage(const std::string& msg, const std::string& title) override;
    
private:
    ModelInterface& model;
    ControllerInterface& ctrl;
    
    QDialog* topDialog{ nullptr };
};

} // end NS
#endif // BATTLESHIPVIEW_H
