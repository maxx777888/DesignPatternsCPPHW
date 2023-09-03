#include <iostream>
#include <fstream>

//1. метод saveTo(std::ofstream& file, const Printable& printable, Data::Format format) -> нарушает
//прицип открытости/закрытости. В данном случае лучше вместо switch развести все форматы отдельно.

//2. Методы saveToAsHTML, saveToAsJSON, saveToAsText -> нарушают принцип подстановки Барбары Лисков
// Они все принимают объект класса Printable и задают формат, но в классе Data конструктор уже 
//присваивает формат, что может выкинуть исключение и неправильному поведению. 

//3. В классе Printable методы printAsHTML, printAsText, printAsJSON -> нарушают принцим разделения
//интерфейсов, потому что лучше сделать один виртуальный метод print и разнести по классам
//другие методы, что сущности не зависили от интерфейсов, которые они не используют. 

class Printable //Нарушие 3
{
public:
    virtual ~Printable() = default;

    virtual std::string printAsHTML() const = 0;
    virtual std::string printAsText() const = 0;
    virtual std::string printAsJSON() const = 0;
};

class Data : public Printable
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };

    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {}

    std::string printAsHTML() const override
    {
        if (format_ != Format::kHTML) {
            throw std::runtime_error("Invalid format!");
        }
        return "<html>" + data_ + "<html/>";
    }
    std::string printAsText() const override
    {
        if (format_ != Format::kText) {
            throw std::runtime_error("Invalid format!");
        }
        return data_;
    }
    std::string printAsJSON() const override
    {
        if (format_ != Format::kJSON) {
            throw std::runtime_error("Invalid format!");
        }
        return "{ \"data\": \"" + data_ + "\"}";
    }

private:
    std::string data_;
    Format format_;
};

//Нарушение 1
void saveTo(std::ofstream& file, const Printable& printable, Data::Format format)
{
    switch (format)
    {
    case Data::Format::kText:
        file << printable.printAsText();
        break;
    case Data::Format::kJSON:
        file << printable.printAsJSON();
        break;
    case Data::Format::kHTML:
        file << printable.printAsHTML();
        break;
    }
}
//Нарушение 2
void saveToAsHTML(std::ofstream& file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kHTML);
}

void saveToAsJSON(std::ofstream& file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kJSON);
}

void saveToAsText(std::ofstream& file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kText);
}

int main()
{
    std::cout << "Hello World!\n";
}

