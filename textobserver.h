#ifndef __TEXTOBSERVER_H__
#define __TEXTOBSERVER_H__
#include "observer.h"
#include "game.h"

class TextObserver : public Observer {
    Game *subject;
public:
    TextObserver(Game *g);
    void notify() override;
    ~TextObserver();
};

#endif
