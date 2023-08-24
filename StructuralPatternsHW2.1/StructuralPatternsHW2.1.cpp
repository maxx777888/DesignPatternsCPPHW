#include <string>
#include <iostream>
#include <algorithm>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        
        std::string str = data;
        std::reverse(str.begin(), str.end());
        text_->render(str);
    }
};

class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(const std::string& href, const std::string& data) const {

        std::cout << "<a href=";
        text_->render(href);
        std::cout << ">";
        text_->render(data);
        std::cout << "</a>";
    }
};

int main() {
    /*auto text_block = new Paragraph(new BoldText(new ItalicText(new Text())));
    text_block->render("Hello world");
    std::cout << std::endl;
    std::cout << std::endl;*/

    std::cout << "Class Paragraph ----------------->" << std::endl;
    auto text_block_paragraph = new Paragraph(new Text());
    text_block_paragraph->render("Hello world");
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Class Reversed ------------------>" << std::endl;
    auto text_block_reversed = new Reversed(new Text());
    text_block_reversed->render("Hello world");
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Class Link ---------------------->" << std::endl;
    auto text_block_link = new Link(new Text());
    text_block_link->render("netology.ru", "Hello world");
    std::cout << std::endl;
    return 0;
}