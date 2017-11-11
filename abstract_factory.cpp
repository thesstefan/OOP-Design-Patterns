#include <iostream>
#define LINUX

class Widget {
    public:
        virtual void draw() = 0;
};

class LinuxButton : public Widget {
    public:
        void draw() {
            std::cout << "Linux Button" << std::endl;
        }
};

class LinuxMenu : public Widget {
    public:
        void draw() {
            std::cout << "Linux Menu" << std::endl;
        }
};

class WindowsButton : public Widget {
    public:
        void draw() {
            std::cout << "Windows Button" << std::endl;
        }
};

class WindowsMenu : public Widget {
    public:
        void draw() {
            std::cout << "Windows Menu" << std::endl;
        }
};

class Factory {
    public:
        virtual Widget *create_button() = 0;
        virtual Widget *create_menu() = 0;
};

class LinuxFactory : public Factory {
    public:
        Widget *create_button() {
            return new LinuxButton;
        }

        Widget *create_menu() {
            return new LinuxMenu;
        }
};

class WindowsFactory : public Factory {
    public:
        Widget *create_button() {
            return new WindowsButton;
        }

        Widget *create_menu() {
            return new WindowsMenu;
        }
};

class Screen {
    private:
        Factory *factory;

    public:
        Screen(Factory *f) {
            factory = f;
        }

        void draw() {
            Widget *button = factory->create_button();
            Widget *menu = factory->create_menu();

            button->draw();
            menu->draw();
        }
};

int main() {
    Factory *factory;

#ifdef LINUX
    factory = new LinuxFactory;
#else
    factory = new WindowsFactory;
#endif

    Screen *screen = new Screen(factory);

    screen->draw();

    return 0;
}
