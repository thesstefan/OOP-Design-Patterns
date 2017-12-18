#include <iostream>
#include <vector>

class CommandInterface {
    public:
        virtual void execute() = 0;
};

class Remote {
    private:
        std::vector<CommandInterface *> command_history;

    public:
        void store_and_execute(CommandInterface *command) {
            if (command) {
                command_history.push_back(command);
                command->execute();
            }
        }
};

class TV {
    private:
        int current_channel = 0;
        bool state = 0;

    public:
        bool get_state() {
            return this->state;
        }

        int get_channel() {
            return this->current_channel;
        }

        void set_channel(int number) {
            this->current_channel = number;

            std::cout << "Changed channel to " << number << std::endl;
        }

        void turn_on() {
            this->state = 1;

            std::cout << "TV opened" << std::endl;
        }

        void turn_off() {
            this->state = 0;

            std::cout << "TV closed" << std::endl;
        }
};

class TurnOnCommand : public CommandInterface {
    private:
        TV *tv;

    public:
        TurnOnCommand(TV *tv) {
            this->tv = tv;
        }

        void execute() {
            if (tv->get_state() == 0)
                tv->turn_on();
            else
                std::cout << "The TV is already opened" << std::endl;
        }
};

class TurnOffCommand : public CommandInterface {
    private:
        TV *tv;

    public:
        TurnOffCommand(TV *tv) {
            this->tv = tv;
        }

        void execute() {
            if(tv->get_state() == 1)
                tv->turn_off();
            else
                std::cout << "The TV is already closed" << std::endl;
        }
};

class NextChannelCommand : public CommandInterface {
    private:
        TV *tv;

    public:
        NextChannelCommand(TV *tv) {
            this->tv = tv;
        }

        void execute() {
            tv->set_channel(tv->get_channel() + 1);
        }
};

class PreviousChannelCommand : public CommandInterface {
    private:
        TV *tv;

    public:
        PreviousChannelCommand(TV *tv) {
            this->tv = tv;
        }

        void execute() {
            tv->set_channel(tv->get_channel() - 1);
        }
};

int main() {
    TV *tv = new TV();

    CommandInterface *turn_on = new TurnOnCommand(tv);
    CommandInterface *turn_off = new TurnOffCommand(tv);
    CommandInterface *next = new NextChannelCommand(tv);
    CommandInterface *previous = new PreviousChannelCommand(tv);

    Remote *remote = new Remote();

    remote->store_and_execute(turn_on);
    remote->store_and_execute(turn_off);
    remote->store_and_execute(next);
    remote->store_and_execute(next);
    remote->store_and_execute(next);
    remote->store_and_execute(turn_off);
    remote->store_and_execute(turn_off);
    remote->store_and_execute(turn_on);
    remote->store_and_execute(turn_on);
    remote->store_and_execute(next);
    remote->store_and_execute(next);
    remote->store_and_execute(previous);

    return 0;
}
