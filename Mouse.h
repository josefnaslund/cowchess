#ifndef MOUSE_H
#define MOUSE_H

class Mouse {
        private:
            int posX;
            int posY;
            bool locked;

        public:
            Mouse();
            int getPosX() const {return posX;}
            int getPosY() const {return posY;}
            void setPosX(int _x);
            void setPosY(int _y);

            bool isLocked() const {return locked;}
            void setLocked(bool _l) {locked = _l;}

};



#endif
