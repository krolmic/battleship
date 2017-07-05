#ifndef BATTLESHIPCONTROLLER_H
#define BATTLESHIPCONTROLLER_H

#include "common/controller_interface.h"
#include "common/model_interface.h"
// #include "common/view_interface.h"
#include "gui/battleship_view.h"
#include <memory>

class QString;

/// Provides model data to the view and interprets user actions
class BattleshipController : public ControllerInterface
{
public:
    explicit BattleshipController(ModelInterface& model);
    
        
    /**
     * @see ModelInterface#startNewGameAsHost(const std::string&, int)
     */
    void startNewGameAsHost(const QString& playerName, const QString& age) override;
    
    /**
     * @see ModelInterface#startNewGameAsGuest(const std::string&, int, const std::string&, int)
     */
    void startNewGameAsGuest(const QString& address, const QString& port, const QString& playerName, const QString& age) override;
    
private:
    ModelInterface& model;
//     std::unique_ptr<ViewInterface> view;
    GUI::BattleshipView view;
    
};

#endif // BATTLESHIPCONTROLLER_H
