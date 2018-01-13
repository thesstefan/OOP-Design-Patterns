class Exception {
    private:
        const char *message;

    public:
        Exception();
        Exception(const char *message);

        Exception(const Exception &exception);
        Exception& operator=(const Exception &exception);

        virtual const char *what() const;
};

class OutOfRange : public Exception {
    public:
        OutOfRange(const char *message);
};

class BadAlloc : public Exception {
    public:
        BadAlloc(const char *message);
};

class Error : public Exception {
    public:
        Error(const char *message);
};
