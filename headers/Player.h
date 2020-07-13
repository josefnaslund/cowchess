#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using std::string;

class Player {
    private:
        bool AI;

    public:
        Player();
        Player(bool _AI);
        bool isAI() {return AI;}
        void setAI(bool _AI) {AI = _AI;}
};

#endif
