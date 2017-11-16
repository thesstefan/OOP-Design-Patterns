#include <iostream>

class Rectangle {
    public:
        virtual void draw() = 0;
};

class OldRectangle {
    private:
        int x_1;
        int x_2;
        int y_1;
        int y_2;
    public:
        OldRectangle(int x_1, int y_1, int x_2, int y_2) {
            this->x_1 = x_1;
            this->x_2 = x_2;
            this->y_1 = y_1;
            this->y_2 = y_2;
        }

        void old_draw() {
            std::cout << "Old Rectangle : draw -> " << x_1 << ", " << x_2 << ", " << y_1 << " " << y_2 << std::endl;
        }
};

class RectangleAdapter : public Rectangle, private OldRectangle {
    public:
        RectangleAdapter(int x, int y, int width, int height) : OldRectangle(x, y, x + width, y + height) {}

        virtual void draw() {
            std::cout << "RectangleAdapter : draw" << std::endl;

            old_draw();
        }
};

int main() {
    Rectangle *rect = new RectangleAdapter(20, 30, 30, 20);

    rect->draw();

    return 0;
}
