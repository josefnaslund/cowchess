#ifndef PLAYER_H
#define PLAYER_H

/**
 * @brief Class used to keep track who is playing - human or AI.
 */
class Player {
    private:
        bool AI;

    public:
        /**
         * @brief Initializes a human player
         */
        Player();

        /**
         * @brief Initialization constructor to directly set an AI player.
         *
         * @param _ai true if player is AI.
         */
        explicit Player(bool _ai);

        /**
         * @brief Query if a player is AI.
         *
         * @return true if player is not biological.
         */
        [[nodiscard]] bool isAI() const {return AI;}

        /**
         * @brief Set ai to bool argument
         *
         * @param _ai true to set player to AI. false to set humanoid.
         */
        void setAI(bool _ai) {AI = _ai;}
};

#endif
