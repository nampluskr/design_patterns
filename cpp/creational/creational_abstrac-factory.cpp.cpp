// https://medium.com/cp-massive-programming/abstract-factory-cheat-sheet-e97ed1b2ab61
#include <iostream>
#include <string>
using namespace std;

// Products (Fonts)
struct AbstractFont {
    virtual ~AbstractFont() {};
    virtual string getFontName() = 0;
};

struct DarkThemeFont : AbstractFont {
    string getFontName() override { return "Arial Black"; }
};

struct LightThemeFont : AbstractFont {
    string getFontName() override { return "Comic Sans MS"; }
};

// Products (Styles)
struct AbstractStyle {
    virtual ~AbstractStyle() {};
    virtual string getStyleName() = 0;
};

struct DarkThemeStyle : AbstractStyle {
    string getStyleName() override { return "dark"; }
};

struct LightThemeStyle : AbstractStyle {
    string getStyleName() override { return "light"; }
};


// Builders
struct AbstractFactory {
    virtual ~AbstractFactory() {};
    virtual AbstractFont* createFont() = 0;
    virtual AbstractStyle* createStyle() = 0;
};

struct DarkThemeFactory : AbstractFactory {
    AbstractFont* createFont() override { return new DarkThemeFont(); }
    AbstractStyle* createStyle() override { return new DarkThemeStyle(); }
};

struct LightThemeFactory : AbstractFactory {
    AbstractFont* createFont() override { return new LightThemeFont(); }
    AbstractStyle* createStyle() override { return new LightThemeStyle(); }
};


// Client
struct Theme {
    string name;
    AbstractFont* font;
    AbstractStyle* style;

    Theme() { name = ""; font = nullptr; style = nullptr; };
    Theme(AbstractFactory* builder, const string& name) {
        this->name = name;
        this->font = builder->createFont();
        this->style = builder->createStyle();
    }
    ~Theme() { delete font; delete style; }

    string getFontName() { return font->getFontName(); }
    string getStyleName() { return style->getStyleName(); }
};

int main()
{
    Theme lightTheme = Theme(new LightThemeFactory(), "Light Theme");
    cout << lightTheme.getFontName() << endl;
    cout << lightTheme.getStyleName() << endl;

    Theme darkTheme = Theme(new DarkThemeFactory(), "Dark Theme");
    cout << darkTheme.getFontName() << endl;
    cout << darkTheme.getStyleName() << endl;

    return 0;
}
