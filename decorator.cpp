#include <iostream>
#include <string>

class Coffee {
    public:
        virtual double get_cost() = 0;
        virtual std::string get_ingredients() = 0;
};

class SimpleCoffee : public Coffee {
    public:
        double get_cost() {
            return 1;
        }

        std::string get_ingredients() {
            return "Coffee";
        }
};

class CoffeeDecorator : public Coffee {
    protected:
        Coffee *decorated_coffee;

    public:
        CoffeeDecorator(Coffee *coffee) {
            this->decorated_coffee = coffee;
        }

        double get_cost() {
            return decorated_coffee->get_cost();
        }
        
        std::string get_ingredients() {
            return decorated_coffee->get_ingredients();
        }
};

class WithMilk : public CoffeeDecorator {
    public:
        WithMilk(Coffee *coffee) : CoffeeDecorator(coffee) {}

        double get_cost() {
            return CoffeeDecorator::get_cost() + 0.5;
        }

        std::string get_ingredients() {
            return CoffeeDecorator::get_ingredients() + " + Milk";
        }
};

class WithSprinkles : public CoffeeDecorator {
    public:
        WithSprinkles(Coffee *coffee) : CoffeeDecorator(coffee) {}

        double get_cost() {
            return CoffeeDecorator::get_cost() + 0.2;
        }

        std::string get_ingredients() {
            return CoffeeDecorator::get_ingredients() + " + Sprinkles";
        }
};

void print_info(Coffee *coffee) {
    std::cout << "Cost : " << coffee->get_cost() << "; Ingredients : " << coffee->get_ingredients() << std::endl;
}

int main() {
    Coffee *coffee = new SimpleCoffee();
    print_info(coffee);

    coffee = new WithMilk(coffee);
    print_info(coffee);

    coffee = new WithSprinkles(coffee);
    print_info(coffee);
}



