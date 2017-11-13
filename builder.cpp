#include <iostream>
#include <string>

class Processor {
    public:
        std::string power;
};

class Battery {
    public:
        std::string capacity;
};

class Memory {
    public:
        std::string quantity;
};

class Phone {
    public:
        Processor *processor;
        Battery *battery;
        Memory *memory;

        void specs() {
            std::cout << "Processor : " << processor->power << std::endl;
            std::cout << "Battery: " << battery->capacity << std::endl;
            std::cout << "Memory : " << memory->quantity << std::endl;
        }
};

class Builder {
    public:
        virtual Processor *get_processor() = 0;
        virtual Battery *get_battery() = 0;
        virtual Memory *get_memory() = 0;
};

class Director {
    Builder *builder;

    public:
        void set_builder(Builder *builder) {
            this->builder = builder;
        }

        Phone *get_phone() {
            Phone *phone = new Phone();

            phone->processor = builder->get_processor();
            phone->battery = builder->get_battery();
            phone->memory = builder->get_memory();

            return phone;
        }
};

class SamsungBuilder : public Builder {
    public:
        Processor *get_processor() {
            Processor *processor = new Processor();

            processor->power = "4 x 2.35 GHz & 4 x 1.9 GHz";

            return processor;
        }

        Battery *get_battery() {
            Battery *battery = new Battery();

            battery->capacity = "3000 mAh";

            return battery;
        }

        Memory *get_memory() {
            Memory *memory = new Memory();

            memory->quantity = "4GB";

            return memory;
        }
};

class PixelBuilder : public Builder {
    public:
        Processor *get_processor() {
            Processor *processor = new Processor();

            processor->power = "4 x 2.35 GHz & 4 x 1.9 GHz";

            return processor;
        }

        Battery *get_battery() {
            Battery *battery = new Battery();

            battery->capacity = "2700 mAh";

            return battery;
        }

        Memory *get_memory() {
            Memory *memory = new Memory();

            memory->quantity = "4GB";

            return memory;
        }
};

class IPhoneBuilder : public Builder {
    public:
        Processor *get_processor() {
            Processor *processor = new Processor();

            processor->power = "10 x 2.39 GHz";

            return processor;
        }

        Battery *get_battery() {
            Battery *battery = new Battery();

            battery->capacity = "2716 mAh";

            return battery;
        }

        Memory *get_memory() {
            Memory *memory = new Memory();

            memory->quantity = "3GB";

            return memory;
        }
};

int main() {
    Phone *phone;
    Director director;

    SamsungBuilder samsung_builder;
    IPhoneBuilder iphone_builder;
    PixelBuilder pixel_builder;

    std::cout << std::endl << "Samsung" << std::endl;
    director.set_builder(&samsung_builder);
    phone = director.get_phone();
    phone->specs();

    std::cout << std::endl << "IPhone" << std::endl;
    director.set_builder(&iphone_builder);
    phone = director.get_phone();
    phone->specs();

    std::cout << std::endl << "Pixel" << std::endl;
    director.set_builder(&pixel_builder);
    phone = director.get_phone();
    phone->specs();
    return 0;
}


