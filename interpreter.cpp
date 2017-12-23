#include <iostream>
#include <stack>

class Context {
    private:
        std::string input;
        int output;
    
    public:
        Context(std::string input) {
            this->input = input;
        }

        std::string get_input() {
            return input;
        }

        int get_output() {
            return output;
        }

        void set_output(int output) {
            this->output = output;
        }
};

class Expression {
    public:
        void interpret(Context *context) {
            std::stack<int> stack;

            int operand_1;
            int operand_2;

            std::string expression = context->get_input();

            for (auto it = expression.begin(); it != expression.end(); it++)
                switch (*it) {
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        stack.push(*it - 48);
                        break;
                    case '+':
                        operand_1 = stack.top();
                        stack.pop();

                        operand_2 = stack.top();
                        stack.pop();

                        stack.push(operand_2 + operand_1);

                        break;
                    case '-':
                        operand_1 = stack.top();
                        stack.pop();

                        operand_2 = stack.top();
                        stack.pop();

                        stack.push(operand_2 - operand_1);

                        break;
                    case '*':
                        operand_1 = stack.top();
                        stack.pop();

                        operand_2 = stack.top();
                        stack.pop();

                        stack.push(operand_2 * operand_1);

                        break;
                    case '/':
                        operand_1 = stack.top();
                        stack.pop();

                        operand_2 = stack.top();
                        stack.pop();

                        stack.push(operand_2 / operand_1);

                        break;
                    default:
                        std::cout << "Unknown operator" << std::endl;
                        break;
                }

            context->set_output(stack.top());
        }
};

int main(int argc, char *argv[]) {
    std::string input = argv[1];

    Context *context = new Context(input);
    Expression *expression = new Expression();

    expression->interpret(context);

    std::cout << "Result : " << context->get_output() << std::endl;
    
    return 0;
}

