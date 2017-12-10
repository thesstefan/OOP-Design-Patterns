#include <iostream>

class Kitchen {
    public:
        void clean() {
            std::cout << "Kitchen cleaned" << std::endl;
        }
};

class Bedroom {
    public:
        void clean() {
            std::cout << "Bedroom cleaned" << std::endl;
        }
};

class Bathroom {
    public:
       void clean() {
           std::cout << "Bathroom cleaned" << std::endl;
       }
};

class HouseFacade {
    protected:
        Kitchen *kitchen;
        Bedroom *bedroom;
        Bathroom *bathroom;

    public:
        HouseFacade() {
            this->kitchen = new Kitchen;
            this->bedroom = new Bedroom;
            this->bathroom = new Bathroom;
        }

        void clean() {
            std::cout << "Cleaning house ... " << std::endl;
            std::cout << std::endl;

            this->kitchen->clean();
            this->bedroom->clean();
            this->bathroom->clean();

            std::cout << std::endl;
            std::cout << "House cleaned !" << std::endl;
        }
};

int main() {
    HouseFacade *house = new HouseFacade;

    house->clean();

    return 0;
}
