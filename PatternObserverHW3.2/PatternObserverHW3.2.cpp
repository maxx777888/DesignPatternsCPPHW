#include <iostream>
#include <vector>
#include <fstream>

class Observer {
public:
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

class Observable {
public:
    void addObserver(Observer* o) {
        observers.push_back(o);
    }

    void removeObserver(Observer* o) {
        observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
    }

    void warning(const std::string& message) const {
        for (auto observer : observers) {
            observer->onWarning(message);
        }
    }

    void error(const std::string& message) const {
        for (auto observer : observers) {
            observer->onError(message);
        }
    }

    void fatalError(const std::string& message) const {
        for (auto observer : observers) {
            observer->onFatalError(message);
        }
    }

private:
    std::vector<Observer*> observers;
};

class WarningObserver : public Observer {
public:
    virtual void onWarning(const std::string& message) override {
        std::cout << "Warning: " << message << std::endl;
    }
};

class ErrorObserver : public Observer {
public:
    ErrorObserver(const std::string& filePath)
        : file(filePath)
    {}

    virtual void onError(const std::string& message) override {
        file << "Error: " << message << std::endl;
    }

private:
    std::ofstream file;
};

class FatalErrorObserver : public Observer {
public:
    FatalErrorObserver(const std::string& filePath)
        : file(filePath)
    {}

    virtual void onFatalError(const std::string& message) override {
        file << "Fatal error: " << message << std::endl;
        std::cout << "Fatal error: " << message << std::endl;
    }

private:
    std::ofstream file;
};


int main()
{
    Observable observable;

    WarningObserver warningObserver;
    ErrorObserver errorObserver("error.log");
    FatalErrorObserver fatalErrorObserver("fatal_error.log");

    observable.addObserver(&warningObserver);
    observable.addObserver(&errorObserver);
    observable.addObserver(&fatalErrorObserver);

    observable.warning("This is a warning.");
    observable.error("This is an error.");
    observable.fatalError("This is a fatal error.");

    observable.removeObserver(&warningObserver);
    observable.removeObserver(&errorObserver);
    observable.removeObserver(&fatalErrorObserver);

    return 0;
}

