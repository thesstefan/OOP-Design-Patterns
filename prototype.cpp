#include <iostream>

class Monster {
    protected:
        int health;
        int power;

    public:
        Monster(int health, int power) {
            this->health = health;
            this->power = power;
        }

        virtual Monster *clone() = 0;

        virtual void stats() {
            std::cout << "Health : " << health << std::endl;
            std::cout << "Power : " << power << std::endl;
            std::cout << std::endl;
        }
};

class Goblin : public Monster {
    public:
        Goblin(int health, int power) : Monster(health, power) {}

        virtual Monster *clone() {
            return new Goblin(health, power);
        }

        virtual void stats() {
            std::cout << "Goblin" << std::endl;
            Monster::stats();
        }
};

class Ghost : public Monster {
    public:
        Ghost(int health, int power) : Monster(health, power) {}

        virtual Monster *clone() {
            return new Ghost(health, power);
        }

        virtual void stats() {
            std::cout << "Ghost" << std::endl;
            Monster::stats();
        }
};

class Spawner {
    private:
        Monster *prototype;

    public:
        Spawner(Monster *prototype) {
            this->prototype = prototype;
        }

        Monster *spawn_monster() {
            return prototype->clone();
        }
};

int main() {
    Monster *ghost_prototype = new Ghost(10, 20);
    Spawner *ghost_spawner = new Spawner(ghost_prototype);

    Monster *goblin_prototype = new Goblin(20, 10);
    Spawner *goblin_spawner = new Spawner(goblin_prototype);

    Monster *ghost = ghost_spawner->spawn_monster();
    Monster *goblin = goblin_spawner->spawn_monster();

    ghost->stats();
    goblin->stats();

    return 0;
}
