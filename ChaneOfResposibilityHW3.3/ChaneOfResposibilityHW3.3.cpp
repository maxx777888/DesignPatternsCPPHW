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

    Type type() const;
    const std::string& message() const;
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



    // Usage example
    //LogMessage* message = { Type::UNKNOWN, "Error occurred" };
    LogMessage message; //= { Type::UNKNOWN, "Error occurred" };

    unknown_handler.handle(message);


    /*message.type() = Type::WARNING;
    message.message() = "Warning message";*/


    /*auto error_handler = std::make_unique<ErrorHandler>(std::move(fatal_handler));
    auto warning_handler = std::make_unique<WarningHandler>(std::move(error_handler));
    auto unknown_handler = std::make_unique<UnknownHandler>(std::move(warning_handler));*/

    unknown_handler.handle(message);
    /*try {
        unknown_handler->handle(message);
        unknown_handler->handle(message);
        unknown_handler->handle(message);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }*/


    return 0;
}
