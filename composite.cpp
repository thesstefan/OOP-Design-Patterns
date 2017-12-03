#include <vector>
#include <iostream>

class WindowComponent {
    public:
        virtual void resize() = 0;
};

class TextBox : public WindowComponent {
    public:
        void resize() {
            std::cout << "Resize text box " << std::endl;
        }
};

class Image : public WindowComponent {
    public:
        void resize() {
            std::cout << "Resize image " << std::endl;
        }
};

class Button : public WindowComponent {
    public:
        void resize() {
            std::cout << "Resize button " << std::endl;
        }
};

// Window = composite for WindowComponent
class Window : public WindowComponent {
    private:
        std::vector<WindowComponent *> components;

    public:
        void add(WindowComponent *component) { 
            components.push_back(component);
        }
            
        void resize() {
            for (std::vector<WindowComponent *>::iterator index = components.begin(); index != components.end(); index++)
                (*index)->resize();
        }
};

int main() {
    Window *window_1 = new Window();
    Window *window_2 = new Window();

    TextBox *text = new TextBox();
    Image *img = new Image();
    Button *button = new Button();

    window_1->add(text);
    window_1->add(text);
    window_1->add(img);
    window_1->add(button);
    window_1->add(button);

    window_2->add(text);
    window_2->add(text);
    window_2->add(img);
    window_2->add(img);
    window_2->add(img);
    window_2->add(img);
    window_2->add(button);

    window_1->resize();

    std::cout << std::endl;

    window_2->resize();

    return 0;
}
