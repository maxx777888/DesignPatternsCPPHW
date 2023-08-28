#include <iostream>
#include <fstream>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class ConsoleLogCommand : public LogCommand {
public:
    virtual void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

class FileLogCommand : public LogCommand {
public:
    FileLogCommand(const std::string& filePath)
        : file(filePath)
    {}

    virtual void print(const std::string& message) override {
        file << message << std::endl;
    }

private:
    std::ofstream file;
};

void print(LogCommand& logCommand) {
    logCommand.print("Hello, world!");
}

int main() {
    ConsoleLogCommand consoleLogCommand;
    FileLogCommand fileLogCommand("log.txt");

    print(consoleLogCommand);
    print(fileLogCommand);

    return 0;
}
