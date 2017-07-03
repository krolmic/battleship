#ifndef BATTLESHIP_MODEL_H
#define BATTLESHIP_MODEL_H

#include "model_interface.h"
#include <memory>
#include "game.h"

namespace MODEL {

class BattleshipModel : public ModelInterface
{
public:
    explicit BattleshipModel();
    ~BattleshipModel() {}
    BattleshipModel(BattleshipModel const &) = delete; //disable copy-constructor
    BattleshipModel& operator=(BattleshipModel const &other) = delete; //disable assign-operator
    BattleshipModel(BattleshipModel&& other) = delete; //disable move-constructor
    BattleshipModel& operator=(BattleshipModel&& other) = delete; //disable move assign-operator
    
    /**
     * @see ModelInterface#startNewGameAsHost(const std::string&, int)
     */
    void startNewGameAsHost(const std::string& playerName, int age) override;
    
    /**
     * @see ModelInterface#startNewGameAsGuest(const std::string&, int, const std::string&, int)
     */
    void startNewGameAsGuest(const std::string& address, int port, const std::string& playerName, int age) override;
    
    /**
     * @see ModelInterface#cancelHosting()
     */
    void cancelHosting() override;
    
private:
    std::unique_ptr<MODEL::Game> game = nullptr;
    
};

} // end NS
#endif // BATTLESHIP_MODEL_H
