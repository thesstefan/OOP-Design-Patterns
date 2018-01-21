#include <iostream>
#include <vector>

class Memento {
    friend class Originator;

    private:
        std::string state;

        Memento(std::string state) {
            this->state = state;
        }

        void set_state(std::string state) {
            this->state = state;
        }

        std::string get_state() {
            return this->state;
        }
};

class Originator {
    private:
        std::string state;

    public:
        void set_state(std::string state) {
            this->state = state;

            std::cout << "State set to : " << state << std::endl;
        }

        std::string get_state() {
            return this->state;
        }

        void set_memento(Memento *meme) {
            state = meme->get_state();
        }

        Memento *create_memento() {
            return new Memento(state);
        }
};

class CareTaker {
    private:
        Originator *originator;
        std::vector<Memento *> history;

    public:
        CareTaker(Originator *originator) {
            this->originator = originator;
        }

        ~CareTaker() {
            for (auto it = history.begin(); it != history.end(); it++)
                delete *it;

            history.clear();
        }

        void save() {
            std::cout << "State saved" << std::endl;
            history.push_back(originator->create_memento());
        }

        void undo() {
            std::cout << "State undid" << std::endl;
            originator->set_memento(history.back());
            history.pop_back();
        }
};

int main() {
    Originator *originator = new Originator();
    CareTaker *care_taker = new CareTaker(originator);

    originator->set_state("Coding");
    care_taker->save();

    originator->set_state("Feeling happy");
    care_taker->save();

    originator->set_state("Feeling sad");
    care_taker->undo();

    std::cout << "Actual state : " << originator->get_state() << std::endl;

    delete originator;
    delete care_taker;

    return 0;
}
