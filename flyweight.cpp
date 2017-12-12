#include <iostream>
#include <vector>
#include <map>
#include <string>

class Circle {
    private:
        std::string color;

        int x;
        int y;
    public:
        Circle() {}

        Circle(std::string color) {
            this->color = color;
        }

        void set_x(int x) {
            this->x = x;
        }

        void set_y(int y) {
            this->y = y;
        }

        void draw() {
            std::cout << "Circle : Draw() [Color : " << color << ", x : " << x << ", y : " << y << "]" << std::endl;
        }
};

class CircleFactory {
    private:
        std::map<std::string, Circle> circle_map;

    public:
        Circle get_circle(std::string color) {
            Circle circle;

            auto it = circle_map.find(color);

            if (it != circle_map.end()) {
                circle = it->second;
            } else {
                circle = Circle(color);
                circle_map.insert(std::pair<std::string, Circle>(color, circle));

                std::cout << "Creating circle of color : " << color << std::endl;
            }

            return circle;
        }
};

int get_rand_int() {
    return rand() % 100;
}

std::string get_rand_color(std::vector<std::string> colors) {
    return colors[rand() % colors.size()];
}

int main() {
    std::vector<std::string> colors;

    colors.push_back("Red");
    colors.push_back("Blue");
    colors.push_back("Green");
    colors.push_back("Yellow");

    CircleFactory circle_factory;

    srand(time(NULL));

    for (int index = 0; index < 10; index++) {
        Circle circle = circle_factory.get_circle(get_rand_color(colors));
        
        circle.set_x(get_rand_int());
        circle.set_y(get_rand_int());

        circle.draw();
    }

    return 0;
}


