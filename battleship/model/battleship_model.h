#ifndef BATTLESHIP_MODEL_H
#define BATTLESHIP_MODEL_H

#include "common/model_interface.h"
#include <memory>
#include <vector>
#include <functional>
#include "game.h"

class BattleshipObserver;
class UserInfo;

namespace MODEL {


/// acts primarely as a wrapper around MODEL::Game class. Especially we make use of its constructor & destructor. And we can dynamicallly switch between Host and Guest if so desired
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
     * Observer pattern as a part of MVC-Pattern
     * @param observer is usally a gui, that reflects/shows state-changes of the model
     */
    void registerObserver(BattleshipObserver& observer);
    
    /**
     * @see ModelInterface#startNewGameAsHost(const std::string&, int)
     */
    void startNewGameAsHost(UserInfo userInfo) override;
    
    /**
     * @see ModelInterface#startNewGameAsGuest(const std::string&, int, const std::string&, int)
     */
    void startNewGameAsGuest(const std::string& address, int port, UserInfo userInfo) override;
    
    /**
     * @see ModelInterface#cancelHosting()
     */
    void cancelHosting() override;
    
    /**
     * @see ModelInterface#placeShip(MODEL::Point, MODEL::Point)
     */
    void placeShip(MODEL::Point p1, MODEL::Point p2) override;
    
private:
    std::unique_ptr<MODEL::Game> game = nullptr;
    std::vector<std::reference_wrapper<BattleshipObserver>> observerList;
    
};

} // end NS
#endif // BATTLESHIP_MODEL_H
