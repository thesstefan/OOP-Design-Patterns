#include <iostream>

class Request {
    private:
        int amount;
        
    public:
        Request(int amount) {
            this->amount = amount;
        }

        int get_amount() {
            return this->amount;
        }

        void set_amount(int amount) {
            this->amount = amount;
        }
};

class Bill {
    private:
        Bill *successor;

    protected:
        int base = 1;
        virtual int get_value() = 0;

    public:
        void set_successor(Bill *successor) {
            this->successor = successor;
        }

        void process_request(Request *request) {
            while (request->get_amount()) {
                if (request->get_amount() < this->get_value()) {
                    successor->process_request(request);
                } else {
                    int count = request->get_amount() / this->get_value();

                    request->set_amount(request->get_amount() - count * this->get_value());

                    std::cout << "The ATM gives you " << count << "x " << "bills of " << this->get_value() << "$" << std::endl;
                }
            }
        }
};

class OneDollar : public Bill {
    protected:
        int get_value() {
            return this->base;
        }
};

class FiveDollars : public Bill {
    protected:
        int get_value() {
            return this->base * 5;
        }
};

class TenDollars : public Bill {
    protected:
        int get_value() {
            return this->base * 10;
        }
};

class HundredDollars : public Bill {
    protected:
        int get_value() {
            return this->base * 100;
        }
};

int main(int argc, char *argv[]) {
    OneDollar *one_dollar = new OneDollar();
    FiveDollars *five_dollars = new FiveDollars();
    TenDollars *ten_dollars = new TenDollars();
    HundredDollars *hundred_dollars = new HundredDollars();

    hundred_dollars->set_successor(ten_dollars);
    ten_dollars->set_successor(five_dollars);
    five_dollars->set_successor(one_dollar);

    Request *request = new Request(atoi(argv[1]));

    hundred_dollars->process_request(request);

    return 0;
}
