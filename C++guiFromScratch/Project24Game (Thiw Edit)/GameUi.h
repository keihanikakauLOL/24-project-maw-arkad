#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

string Fontloc = "C:/Windows/Fonts/arial.ttf";
float windowSize_x = 1600;
float WindowSize_y = 900;
sf::Font font(Fontloc); //import font_style variable (pull form location)  

class buttonBuild{
    public:
        float posBox_x;
        float posBox_y;
        float FontSize;
        float buttonSize_x;
        float buttonSize_y;
        float X;
        float Y;
        string name;
        sf::Color ColorBox;
        sf::RectangleShape builtButton(); 
        sf::Text txtBox(sf::Vector2f);
};

class Title{
    string Title_string = "Game24";
    float TittleGameSize = 100;
    public:
        sf::Text TitleName();
};


sf::Text Title::TitleName(){
    sf::Text Title_24(font,Title_string,TittleGameSize);
    Title_24.setPosition({windowSize_x*(2.5/5)-TittleGameSize-50,50});
    return Title_24;
};



sf::RectangleShape buttonBuild::builtButton(){
    sf::RectangleShape button({buttonSize_x,buttonSize_y}); //Create button variable with size
    button.setOrigin(button.getGeometricCenter());
    button.setPosition({posBox_x,posBox_y}); 
    button.setFillColor(ColorBox);
    return button;
};

sf:: Text buttonBuild::txtBox(sf::Vector2f buttonCenter){
    sf::Text Text(font,name,FontSize);
    Text.setOrigin(buttonCenter);
    Text.setPosition({posBox_x+X,posBox_y+Y});
    return Text;
}

