#include <iostream>
#include <fstream>



/*
class Printable
{
public:
    virtual ~Printable() = default;
    virtual std::string print() const = 0;
};

class C_HTML : public Printable {
public:
    C_HTML(std::string data) : data_(std::move(data)) {}
    C_HTML() {}

    std::string print() const override {
        return "<html>" + data_ + "<html/>";
    }
private:
    std::string data_;
    //Data html =  Data::Format::kHTML;
    
};

class C_TEXT : public Printable {
public:
    C_TEXT(std::string data) : data_(std::move(data)) {}
    C_TEXT() {}
    std::string print() const override {
        return data_;
    }
private:
    std::string data_;
    //Data c_text = { Data::Format::kText };
};

class C_JSON : public Printable {
public:
    C_JSON(std::string data) : data_(std::move(data)) {}
    C_JSON() {}
    std::string print() const override {
        return "{ \"data\": \"" + data_ + "\"}";
    }
private:
    std::string data_;
    //Data json = { Data::Format::kJSON };
};

class Data : public C_HTML, public C_TEXT, public C_JSON
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };
    
    Data(Format format) :  format_(format) {}
    
private:
    Format format_;
};

void saveTo(std::ofstream& file, const Printable& printable)
{
    file << printable.print() <<std::endl;
}


int main()
{
    std::ofstream file("save_file.txt");
    C_HTML chtml("This is html string");
    C_TEXT ctext("This is text string");
    C_JSON cjson("This is json string");
    saveTo(file, chtml);
    saveTo(file, ctext);
    saveTo(file, cjson);
    
}
*/

class Printable
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };

    virtual ~Printable() = default;
    virtual std::string print() const = 0;
};

class HtmlData : public Printable {
public:
    HtmlData(std::string const& data) : data_(data) {}

    std::string print() const override {
        return "<html>" + data_ + "<html/>";
    }
private:
    std::string data_;
    Format format = Format::kHTML;

};

class TextData : public Printable {
public:
    TextData(std::string const& data) : data_(data) {}

    std::string print() const override {
        return data_;
    }
private:
    std::string data_;
    Format format_ = Format::kText;
};

class JsonData : public Printable {
public:
    JsonData(std::string const& data) : data_(data) {}

    std::string print() const override {
        return "{ \"data\": \"" + data_ + "\"}";
    }
private:
    std::string data_;
    Format format = Format::kJSON;
};

void saveTo(std::ofstream& file, const Printable& printable)
{
    file << printable.print() << std::endl;
}

int main()
{
    std::ofstream file("save_file.txt");
    HtmlData html("This is html string");
    TextData text("This is text string");
    JsonData json("This is json string");
    saveTo(file, html);
    saveTo(file, text);
    saveTo(file, json);
}