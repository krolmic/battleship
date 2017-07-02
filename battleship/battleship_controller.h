#ifndef BATTLESHIPCONTROLLER_H
#define BATTLESHIPCONTROLLER_H

#include "controller_interface.h"
#include "model_interface.h"
#include "view_interface.h"
#include <memory>

class BattleshipController : public ControllerInterface
{
public:
    explicit BattleshipController(ModelInterface& model);
    
        
    /**
     * @see ModelInterface#startNewGameAsHost(const std::string&, int)
     */
    void startNewGameAsHost(const std::string& playerName, int age) override;
    
    /**
     * @see ModelInterface#startNewGameAsGuest(const std::string&, int, const std::string&, int)
     */
    void startNewGameAsGuest(const std::string& address, int port, const std::string& playerName, int age) override;
    
private:
    ModelInterface& model;
    std::unique_ptr<ViewInterface> view;
    
};

#endif // BATTLESHIPCONTROLLER_H
