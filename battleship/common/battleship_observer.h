#ifndef BATTLESHIPOBSERVER_H
#define BATTLESHIPOBSERVER_H

/// A base interface class, includes methods, which communicate with model and gui
class BattleshipObserver //https://stackoverflow.com/questions/14323595/best-way-to-declare-an-interface-in-c11
{
public:
    virtual ~BattleshipObserver () { }
    
    
    /**
     * after players connect to each other, they receive username of the opponent,
     * timer starts (limited time for ship placement) and of course gui opens appropriate dialog/menu
     */
    virtual void shipPlacementStarted() = 0;
    
};


#endif // BATTLESHIPOBSERVER_H
