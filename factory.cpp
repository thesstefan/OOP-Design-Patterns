#include <iostream>

class Shape {
    public:
        virtual void draw() = 0;
};

class Square : public Shape {
    public:
        void draw() {
            std::cout << "Square" << std::endl;
        }
};

class Circle : public Shape {
    public:
        void draw() {
            std::cout << "Circle" << std::endl;
        }
};

Shape *factory_get_shape(std::string type) {
    if (type == "Circle") 
        return new Circle;

    if (type == "Square")
        return new Square;

    return NULL;
}

int main() {
    Shape *shape_1 = factory_get_shape("Circle");
    shape_1->draw();
    
    Shape *shape_2 = factory_get_shape("Square");
    shape_2->draw();

    return 0;
}
