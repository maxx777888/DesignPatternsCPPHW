#include <iostream>
#include <fstream>
#include <stdexcept>



enum class Type {

    WARNING,
    ERROR,
    FATAL_ERROR,
    UNKNOWN
};

class LogMessage {
public:
    LogMessage(Type type, std::string const &message): type_(type), message_(message){}
    Type type() const {
        return type_;
    }
    const std::string& message() const {
        return message_;
    }
private:
    Type type_;
    const std::string message_;
};

class Handler {
public:
    virtual void handle(const LogMessage& message) = 0;
};

class FatalErrorHandler : public Handler {
public:
    void handle(const LogMessage& message) override {
        throw std::runtime_error(message.message());
    }
};

class ErrorHandler : public Handler {
public:
    ErrorHandler(const std::string& path) : file_(path) {}

    void handle(const LogMessage& message) override {
        if (message.type() == Type::ERROR) {
            file_ << message.message() << std::endl;
        }
        else {
            next_->handle(message);
        }
    }

private:
    std::ofstream file_;
    Handler* next_;
};

class WarningHandler : public Handler {
public:
    void handle(const LogMessage& message) override {
        if (message.type() == Type::WARNING) {
            std::cout << message.message() << std::endl;
        }
        else {
            next_->handle(message);
        }
    }

private:
    Handler* next_;
};

class UnknownHandler : public Handler {
public:
    void handle(const LogMessage& message) override {
        if (message.type() == Type::UNKNOWN) {
            throw std::runtime_error("Unknown message type");
        }
        else {
            next_->handle(message);
        }
    }

private:
    Handler* next_;
};

int main() {
    FatalErrorHandler fatal_handler;
    ErrorHandler error_handler("error.log");
    WarningHandler warning_handler;
    UnknownHandler unknown_handler;


    LogMessage message{ Type::UNKNOWN, "Error occurred" };


    try {
        fatal_handler.handle(message);
        //error_handler.handle(message);
        //warning_handler.handle(message);
        //unknown_handler.handle(message);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }


    return 0;
}
