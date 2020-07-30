#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using std::string;

class Player {
    private:
        bool AI;

    public:
        Player();
        explicit Player(bool _ai);
        [[nodiscard]] bool isAI() const {return AI;}
        void setAI(bool _ai) {AI = _ai;}
};

#endif
