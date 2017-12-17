#include <iostream>
#include <string>

class InterfaceServer {
    public:
        virtual void close() = 0;
};

class Server : public InterfaceServer {
    public:
        void close() {
            std::cout << "The server was closed" << std::endl;
        }
};

class ProxyServer : public InterfaceServer {
    private:
        InterfaceServer *real_server;
        std::string username;

    public:
        ProxyServer(std::string username) : real_server(new Server), username(username) {}

        void close() {
            if (username == "admin")
                real_server->close();
            else
                std::cout << "You're not an administrator. You can't close the server" << std::endl;
        }
};

int main() {
    InterfaceServer *server = new ProxyServer("johnny");
    server->close();
    
    server = new ProxyServer("admin");
    server->close();

    return 0;
}
