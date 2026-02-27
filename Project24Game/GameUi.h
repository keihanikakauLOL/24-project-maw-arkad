#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string Fontloc = "C:/Windows/Fonts/arial.ttf";
float windowSize_x = 800;
float WindowSize_y = 800;
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
    sf::FloatRect boundTitle = Title_24.getLocalBounds();
    Title_24.setOrigin({boundTitle.position.x+boundTitle.size.x/2,TittleGameSize-boundTitle.position.y});
    Title_24.setPosition({windowSize_x/2,150});
    return Title_24;
};



sf::RectangleShape buttonBuild::builtButton(){
    sf::RectangleShape button({buttonSize_x,buttonSize_y}); //Create button variable with size
    button.setPosition({posBox_x,posBox_y}); 
    button.setOrigin(button.getGeometricCenter());
    button.setFillColor(ColorBox);
    return button;
};


sf:: Text buttonBuild::txtBox(sf::Vector2f buttonCenter){
    sf::Text Text(font,name,FontSize); 
    sf::FloatRect bounds = Text.getLocalBounds();
    Text.setOrigin({bounds.position.x+bounds.size.x/2,FontSize-bounds.position.y});
    Text.setPosition({posBox_x,posBox_y}); 
    return Text;
}

class Screen{
    string strData = "";
    public:
        void add(char);
        sf::Text printData();
        sf::RectangleShape BoxScreen();
        string Get_Data();
        void pop();
};

void Screen::pop(){
    strData.pop_back();
}

void Screen::add(char inputNumber){
    strData+=inputNumber;
}

sf::Text Screen::printData(){
    sf::Text Data(font,strData,100);
    sf::FloatRect boundScreen = Data.getLocalBounds();
    Data.setOrigin({boundScreen.position.x+boundScreen.size.x/2,100-boundScreen.position.y});
    Data.setPosition({windowSize_x/2,150});
    return Data;
}

sf::RectangleShape Screen::BoxScreen(){
    sf::RectangleShape Box({windowSize_x*80/100,WindowSize_y*20/100}); //Create button variable with size
    Box.setPosition({windowSize_x/2,150}); 
    Box.setOrigin(Box.getGeometricCenter());
    Box.setFillColor(sf::Color(128,128,128));
    return Box;
}

string Screen::Get_Data(){
    return strData;
}

void Bar_Chart(sf::RenderWindow& window, int data[], int data_n)
{
    
    int data_max = *max_element(data, data + data_n);
    // size of window
        float window_w = static_cast<float>(window.getSize().x);
        float window_h = static_cast<float>(window.getSize().y);
    //parameter
        float space = window_w / data_n;
        float size = 0.6f * space;
        float scale = 0.9f * window_h / data_max;


    sf::RectangleShape bar;
    bar.setOrigin({size/2.f, 0.f});
    bar.setScale({1.f, -1.f});
    bar.setFillColor(sf::Color(128,128,128));

    for (int i = 0; i < data_n; i++)
    {
        bar.setSize({size, data[i] * scale});
        bar.setPosition({(i + 0.5f) * space, window_h});
        window.draw(bar);
    }
}

class Circle_buttonBuild{
    public:
        float posBox_x;
        float posBox_y;
        float FontSize;
        float Radius;
        float PointinCircle;
        float X;
        float Y;
        string name;
        sf::Color ColorBox;
        sf::CircleShape Circle_builtButton(); 
        sf::Text Circle_txtBox(sf::Vector2f);
};

sf::CircleShape Circle_buttonBuild::Circle_builtButton(){
    sf::CircleShape Circle(Radius, PointinCircle);
    Circle.setOrigin(Circle.getGeometricCenter());
    Circle.setPosition({posBox_x,posBox_y});
    Circle.setFillColor(ColorBox);
    return Circle;
}

sf::Text Circle_buttonBuild::Circle_txtBox(sf::Vector2f buttonCenter){
    sf::Text Text(font,name,FontSize); 
    sf::FloatRect bounds = Text.getLocalBounds();
    Text.setOrigin({bounds.position.x+bounds.size.x/2,FontSize-bounds.position.y});
    Text.setPosition(buttonCenter); 
    return Text;
}





