#ifndef VIEWINTERFACE_H
#define VIEWINTERFACE_H

class ViewInterface //https://stackoverflow.com/questions/14323595/best-way-to-declare-an-interface-in-c11
{
public:
    virtual ~ViewInterface () { }
    
    virtual void showWaitingForGuestConnectingDialog() = 0;
    virtual void closeTopDialog() = 0;
};

#endif // VIEWINTERFACE_H
