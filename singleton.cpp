#include <iostream>

class Singleton {
    private:
        int value;

        static Singleton *instance;

        Singleton() {}

        Singleton(int value) {
            this->value = value;
        }

    public:
        int get_value() {
            return this->value;
        }

        void set_value(int value) {
            this->value = value;
        }

        static Singleton *get_instance() {
            if (instance == 0)
                instance = new Singleton;

            return instance;
        }
};

Singleton *Singleton::instance = 0;

void function_1() {
    Singleton::get_instance()->set_value(1);

    std::cout << "function_1() : " << Singleton::get_instance()->get_value() << std::endl;
}

void function_2() {
    Singleton::get_instance()->set_value(2);

    std::cout << "function_2() : " << Singleton::get_instance()->get_value() << std::endl;
}

int main() {
    std::cout << "main() : " << Singleton::get_instance()->get_value() << std::endl;

    function_1();
    function_2();
}



