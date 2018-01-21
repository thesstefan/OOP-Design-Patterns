#include <iostream>
#include <string>

#define BOLD 0
#define ITALIC 1
#define LIST 2

class FontSelectionDialog;

class Widget {
    public:
        Widget(FontSelectionDialog *mediator, const char *name) {
            this->mediator = mediator;
            this->name = name;
        }

        virtual void changed();
        virtual void update_widget() = 0;

        virtual void flip(int type) = 0;

    protected:
        const char *name;

    private:
        FontSelectionDialog *mediator;
};

class Button : public Widget {
    public:
        Button(FontSelectionDialog *mediator, const char *name) : Widget(mediator, name) {}

        void flip(int type) {
            this->on = !this->on;
        }

        void update_widget() {
            flip(0);

            std::cout << this->name << " : ";
            std::cout << std::boolalpha;
            std::cout << this->on << std::endl;
        }

    private:
        bool on;
};

class List : public Widget {
    private:
        bool bold = 0;
        bool italic = 0;
    public:
        List(FontSelectionDialog *mediator, const char *name) : Widget(mediator, name) {}

        void update_widget() {
            std::cout << "List showing ";

            if (bold)
                std::cout << "BOLD ";

            if (italic)
                std::cout << "ITALIC ";


            std::cout << "fonts" << std::endl;
        }

        void flip(int type) {
            if (type == BOLD)
                this->bold = !this->bold;
            if (type == ITALIC)
                this->italic = !this->italic;
        }
};

class FontSelectionDialog {
    private:
        Widget *component[4];

    public:
        enum Widgets {
            Bold, Italic, FontList
        };

        FontSelectionDialog() {
            component[Bold] = new Button(this, "Bold");
            component[Italic] = new Button(this, "Italic");
            component[FontList] = new List(this, "List");
        }

        virtual ~FontSelectionDialog();

        void handle_event(int which) {
            component[which]->changed();
        }

        virtual void widget_changed(Widget *widget) {
            if (widget == component[Bold]) {
                component[Bold]->update_widget();

                component[FontList]->flip(BOLD);
            } else if (widget == component[Italic]) {
                component[Italic]->update_widget();

                component[FontList]->flip(ITALIC);
            } else if (widget == component[FontList])
                component[FontList]->update_widget();
        }
};

void Widget::changed() {
    this->mediator->widget_changed(this);
}

FontSelectionDialog::~FontSelectionDialog() {
    for (int i = 0; i < 3; i++)
        delete this->component[i];
}

int main() {
    FontSelectionDialog font_screen;

    font_screen.handle_event(BOLD);

    font_screen.handle_event(ITALIC);

    font_screen.handle_event(LIST);

    return 0;
}
