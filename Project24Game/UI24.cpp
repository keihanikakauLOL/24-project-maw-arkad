#include "GameUi.h"

void GameSystem24(string);
void Menu();

sf::RenderWindow window(sf::VideoMode({800,800}), "GAME24"); //Create window variable with size and tittle name'

enum GameState { // state of game to process more easily
    MENU,
    GAME24,
    RANDOM_MODE
};
GameState state = MENU;

int main()
{    
    
    while (window.isOpen())
    {
        if (state == MENU){Menu();}
        if (state == GAME24){GameSystem24("1234");}
    }
    
}

void Menu(){
    // Build Windows Frame
    
    Title tilte;

    // button24
    buttonBuild button24 = buttonBuild{
        .posBox_x = windowSize_x*1/4,
        .posBox_y = WindowSize_y/2.f, // 2.5 when no float was assian as double type
        .FontSize = 50,
        .buttonSize_x = 225,
        .buttonSize_y = 100,
        .X = 5,
        .Y = 0,
        .name = "Game24",
        .ColorBox = sf::Color(255,0,0)
    };

    // buttonN
    buttonBuild buttonN = buttonBuild{
        .posBox_x = windowSize_x*3/4,
        .posBox_y = WindowSize_y/(2.f), // 2.5 when no float was assian as double type
        .FontSize = 50,
        .buttonSize_x = 225,
        .buttonSize_y = 100,
        .X = 5,
        .Y = 0,
        .name = "Random",
        .ColorBox = sf::Color(0,250,0)
    };
    
    sf:: RectangleShape button_24 = button24.builtButton();
    sf:: RectangleShape button_N = buttonN.builtButton();

    // for check mouse is over button or not and click button or not so we process more easily
    bool isOver_24 = false;
    bool isOver_N = false;
    
    
    // GameOn
    while (state == MENU) // using to make window always open 
    {        
        window.clear();
        while (const std::optional event = window.pollEvent()) // Closing windows functions
        {
            if (event->is<sf::Event::Closed>()) window.close();// "close requested" event: we close the window 
            auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
            if (button_24.getGlobalBounds().contains(mouse_pos)) // check button is coline with mouse : augmentNeedtoCheck.getGlobalBound().contains(whatIscheckwith); >> getGlobalBound() = check coline
            {
                button_24.setFillColor(sf::Color(0,75,22)); // we can create animated or click to process
                isOver_24 = true;
            }else{
                button_24.setFillColor(button24.ColorBox); // reset went not set
                isOver_24 = false;
            }
            if (button_N.getGlobalBounds().contains(mouse_pos)) // check button is coline with mouse : augmentNeedtoCheck.getGlobalBound().contains(whatIscheckwith); >> getGlobalBound() = check coline
            {
                button_N.setFillColor(sf::Color(0,75,22)); // we can create animated or click to process
                isOver_N = true;
            }else{
                button_N.setFillColor(buttonN.ColorBox); // reset went not set
                isOver_N = false;
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) // clicked 
            {   
                if(isOver_24){ // clicked happen on button_24 or not 
                    state = GAME24;
                }
            } 
            // windown.draw is order by line to line upper = under
            window.draw(tilte.TitleName());
            window.draw(button_24);
            window.draw(button_N);
            window.draw(button24.txtBox(button24.builtButton().getGeometricCenter()));
            window.draw(buttonN.txtBox(buttonN.builtButton().getGeometricCenter())); 
            window.display(); 
        }    
    }  
}

void GameSystem24(string setNumber){
    Screen Display;
    bool gateway[] = {0,0,0,0};
    buttonBuild number1 = {
        .posBox_x = windowSize_x*25/100,
        .posBox_y = WindowSize_y*50/100, // 2.5 when no float was assian as double type
        .FontSize = 75,
        .buttonSize_x = 150,
        .buttonSize_y = 150,
        .X = 0,
        .Y = 0,
        .name = to_string(setNumber[0]-48),
            .ColorBox = sf::Color(255,20,52)
        };
    buttonBuild number2 = {
            .posBox_x = windowSize_x*50/100,
            .posBox_y = WindowSize_y*50/100, // 2.5 when no float was assian as double type
            .FontSize = 75,
            .buttonSize_x = 150,
            .buttonSize_y = 150,
            .X = 0,
            .Y = 0,
            .name = to_string(setNumber[1]-48),
            .ColorBox = sf::Color(255,20,52)
        };
    buttonBuild number3 = {
            .posBox_x = windowSize_x*25/100,
            .posBox_y = WindowSize_y*75/100, // 2.5 when no float was assian as double type
            .FontSize = 75,
            .buttonSize_x = 150,
            .buttonSize_y = 150,
            .X = 0,
            .Y = 0,
            .name = to_string(setNumber[2]-48),
            .ColorBox = sf::Color(255,20,52)
        };
    buttonBuild number4 = {
            .posBox_x = windowSize_x*50/100,
            .posBox_y = WindowSize_y*75/100, // 2.5 when no float was assian as double type
            .FontSize = 75,
            .buttonSize_x = 150,
            .buttonSize_y = 150,
            .X = 0,
            .Y = 0,
            .name = to_string(setNumber[3]-48),
            .ColorBox = sf::Color(255,20,52)
        };
    sf::RectangleShape number_1 = number1.builtButton();
    sf::RectangleShape number_2 = number2.builtButton();
    sf::RectangleShape number_3 = number3.builtButton();
    sf::RectangleShape number_4 = number4.builtButton();
    while (state == GAME24){
        window.clear(); 
        window.draw(number_1);
        window.draw(number1.txtBox(number_1.getPosition()));
        window.draw(number_2);
        window.draw(number2.txtBox(number_2.getPosition()));
        window.draw(number_3);
        window.draw(number3.txtBox(number_3.getPosition()));
        window.draw(number_4);
        window.draw(number4.txtBox(number_4.getPosition()));
        while (const std::optional event = window.pollEvent()) // Closing windows functions
        {
            if (event->is<sf::Event::Closed>()) window.close();
            auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));// "close requested" event: we close the window 
            if (number_1.getGlobalBounds().contains(mouse_pos)) 
            {
                number_1.setFillColor(sf::Color(44,75,22)); 
                if (gateway[0] == 0 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    gateway[0] = 1;
                    Display.add(setNumber[0]);
                }
            }else{
                number_1.setFillColor(number1.ColorBox); 
            }
            if (number_2.getGlobalBounds().contains(mouse_pos))
            {
                number_2.setFillColor(sf::Color(44,75,22)); 
                if (gateway[1] == 0 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    gateway[1] = 1;
                    Display.add(setNumber[1]);
                }
            }else{
                number_2.setFillColor(number2.ColorBox);
            }
            if (number_3.getGlobalBounds().contains(mouse_pos)) 
            {
                number_3.setFillColor(sf::Color(44,75,22)); 
                if (gateway[2] == 0 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    gateway[2] = 1;
                    Display.add(setNumber[2]);
                }
            }else{
                number_3.setFillColor(number3.ColorBox); 
            }
            if (number_4.getGlobalBounds().contains(mouse_pos)){
                number_4.setFillColor(sf::Color(44,75,22));
                if (gateway[3] == 0 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    gateway[3] = 1;
                    Display.add(setNumber[3]);
                }
            }else{
                number_4.setFillColor(number4.ColorBox); 
            }
        }
        window.draw(Display.BoxScreen());
        window.draw(Display.printData());
        window.display();
    }   
}