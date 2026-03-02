#include "GameUi.h"

void GameSystem24(string);
void ScoreBoard(int data[], int data_n);
void Menu();

sf::Texture texture("Images/Background.jpg");
sf::Sprite sprite(texture);
sf::RenderWindow window(sf::VideoMode({800,800}), "GAME24"); //Create window variable with size and tittle name'

enum GameState { // state of game to process more easily
    MENU,
    GAME24,
    RANDOM_MODE,
    SCORE_BOARD
};
GameState state = MENU;

int main()
{    
    texture.setSmooth(true);
    if (!texture.loadFromFile("Images/Background.jpg"))
    {
    return -1;
    }
    // Optional: Set the position to (0, 0) (default) and scale the sprite to the window size if needed
    sprite.setPosition({0, 0});
    sprite.setScale({800.f / texture.getSize().x, 800.f / texture.getSize().y});
    window.setFramerateLimit(90);

    while (window.isOpen())
    {
        if (state == MENU){Menu();}
        if (state == GAME24){GameSystem24("9423");}
        if (state == SCORE_BOARD){
            int data[] = {10, 20, 15, 5}; // Example data for the bar chart
            ScoreBoard(data, 4);
        }
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
        .ColorBox = sf::Color(0,51,102)
    };

    // buttonN
    buttonBuild buttonN = buttonBuild{
        .posBox_x = windowSize_x*3/4,
        .posBox_y = WindowSize_y/(2.f), // 2.5 when dno float was assian as double type
        .FontSize = 50,
        .buttonSize_x = 225,
        .buttonSize_y = 100,
        .X = 5,
        .Y = 0,
        .name = "Random",
        .ColorBox = sf::Color(0,51,102)
    };

    // buttonN
    buttonBuild buttonScore = buttonBuild{
        .posBox_x = windowSize_x*0.5f,
        .posBox_y = WindowSize_y*0.75f, // 2.5 when no float was assian as double type
        .FontSize = 50,
        .buttonSize_x = 150,
        .buttonSize_y = 75,
        .X = 5,
        .Y = 0,
        .name = "Score",
        .ColorBox = sf::Color(0,51,102)
    };
    
    sf:: RectangleShape button_24 = button24.builtButton();
    sf:: RectangleShape button_N = buttonN.builtButton();
    sf:: RectangleShape button_Score = buttonScore.builtButton();


    // for check mouse is over button or not and click button or not so we process more easily
    bool isOver_24 = false;
    bool isOver_N = false;
    bool isOver_Score = false;
    
    
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
            if (button_Score.getGlobalBounds().contains(mouse_pos)) // check button is coline with mouse : augmentNeedtoCheck.getGlobalBound().contains(whatIscheckwith); >> getGlobalBound() = check coline
            {
                button_Score.setFillColor(sf::Color(0,75,22)); // we can create animated or click to process
                isOver_Score = true;
            }else{
                button_Score.setFillColor(buttonScore.ColorBox); // reset went not set
                isOver_Score = false;
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) // clicked 
            {   
                if(isOver_24){ // clicked happen on button_24 or not 
                    state = GAME24;
                }
                if(isOver_Score){
                    state = SCORE_BOARD;
                }
            } 
            // windown.draw is order by line to line upper = under
            window.draw(sprite);
            window.draw(tilte.TitleName());
            window.draw(button_24);
            window.draw(button_N);
            window.draw(button_Score);
            window.draw(button24.txtBox(button24.builtButton().getGeometricCenter()));
            window.draw(buttonN.txtBox(buttonN.builtButton().getGeometricCenter())); 
            window.draw(buttonScore.txtBox(buttonScore.builtButton().getGeometricCenter()));
            window.display(); 
        }    
    }  
}

void GameSystem24(string setNumber){
    Screen Display;
    bool gateway[] = {0,0,0,0};
    bool hasDel = 0;
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
    Circle_buttonBuild plus = { //cic
            .posBox_x = windowSize_x*75/100,
            .posBox_y = WindowSize_y*40/100, // 2.5 when no float was assian as double type
            .FontSize = 50,
            .Radius = 50,
            .PointinCircle = 100,
            .X = 0,
            .Y = 5,
            .name = "+",
            .ColorBox = sf::Color(255,20,52)
        };
    Circle_buttonBuild minu = { //cic
            .posBox_x = windowSize_x*75/100,
            .posBox_y = WindowSize_y*55/100, // 2.5 when no float was assian as double type
            .FontSize = 50,
            .Radius = 50,
            .PointinCircle = 100,
            .X = 0,
            .Y = 20,
            .name = "-",
            .ColorBox = sf::Color(255,20,52)
        };
    Circle_buttonBuild mul = { //cic
            .posBox_x = windowSize_x*75/100,
            .posBox_y = WindowSize_y*70/100, // 2.5 when no float was assian as double type
            .FontSize = 50,
            .Radius = 50,
            .PointinCircle = 100,
            .X = 0,
            .Y = 15,
            .name = "x",
            .ColorBox = sf::Color(255,20,52)
        };
    Circle_buttonBuild div = { // cic
            .posBox_x = windowSize_x*75/100,
            .posBox_y = WindowSize_y*85/100, // 2.5 when no float was assian as double type
            .FontSize = 50,
            .Radius = 50,
            .PointinCircle = 100,
            .X = 0,
            .Y = 0,
            .name = "/",
            .ColorBox = sf::Color(255,20,52)
        };
    Circle_buttonBuild del = { // cic
            .posBox_x = windowSize_x*90/100,
            .posBox_y = WindowSize_y*35/100, // 2.5 when no float was assian as double type
            .FontSize = 25,
            .Radius = 25,
            .PointinCircle = 100,
            .X = 0,
            .Y = 0,
            .name = "BS",
            .ColorBox = sf::Color(255,20,52)
        };   
    Circle_buttonBuild GetBack = { // cic
            .posBox_x = 25,
            .posBox_y = 25, // 2.5 when no float was assian as double type
            .FontSize = 20,
            .Radius = 25,
            .PointinCircle = 100,
            .X = 0,
            .Y = 0,
            .name = "Icon",
            .ColorBox = sf::Color(255,20,52)
        };
    sf::RectangleShape number_1 = number1.builtButton();
    sf::RectangleShape number_2 = number2.builtButton();
    sf::RectangleShape number_3 = number3.builtButton();
    sf::RectangleShape number_4 = number4.builtButton();
    sf::CircleShape Plus = plus.Circle_builtButton(); //cic
    sf::CircleShape Minu = minu.Circle_builtButton(); // cic
    sf::CircleShape Mul = mul.Circle_builtButton(); // cic
    sf::CircleShape Div = div.Circle_builtButton(); // cic
    sf::CircleShape Get_Back = GetBack.Circle_builtButton(); //cic
    sf::CircleShape dele = del.Circle_builtButton(); //cic
    while (state == GAME24){
        window.clear(); 
        window.draw(number_1);
        window.draw(number1.txtBox(number_1.getPosition()));
        //
        window.draw(number_2);
        window.draw(number2.txtBox(number_2.getPosition()));
        //
        window.draw(number_3);
        window.draw(number3.txtBox(number_3.getPosition()));
        //
        window.draw(number_4);
        window.draw(number4.txtBox(number_4.getPosition()));
        //
        window.draw(Get_Back);
        window.draw(GetBack.Circle_txtBox(Get_Back.getPosition()));
        //
        window.draw(dele);
        window.draw(del.Circle_txtBox(dele.getPosition()));
        //
        window.draw(Plus);
        window.draw(plus.Circle_txtBox(Plus.getPosition()));
        //
        window.draw(Minu);
        window.draw(minu.Circle_txtBox(Minu.getPosition()));
        //
        window.draw(Mul);
        window.draw(mul.Circle_txtBox(Mul.getPosition()));
        //
        window.draw(Div);
        window.draw(div.Circle_txtBox(Div.getPosition()));
        
        ////
        window.draw(Display.BoxScreen());
        window.draw(Display.printData());
        while (const std::optional event = window.pollEvent()) // Closing windows functions
        {

            if (event->is<sf::Event::Closed>()) window.close();
            auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));// "close requested" event: we close the window 

            ///////////////// NumPad 
            if (Display.NumAllowed == 1)
            {
                if (number_1.getGlobalBounds().contains(mouse_pos)) 
                {
                    number_1.setFillColor(sf::Color(44,75,22)); 
                    if (gateway[0] == 0 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        gateway[0] = 1;
                        Display.add(setNumber[0]);
                        Display.NumAllowed = 0;
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
                       Display.NumAllowed = 0;
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
                        Display.NumAllowed = 0;
                    }
                }else{
                    number_3.setFillColor(number3.ColorBox); 
                }
                if (number_4.getGlobalBounds().contains(mouse_pos)){
                    number_4.setFillColor(sf::Color(44,75,22));
                    if (gateway[3] == 0 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        gateway[3] = 1;
                        Display.add(setNumber[3]);
                        Display.NumAllowed = 0;
                    }
                }else{
                    number_4.setFillColor(number4.ColorBox); 
                }
            }
            else{
                if (Plus.getGlobalBounds().contains(mouse_pos)){
                    Plus.setFillColor(sf::Color(44,75,22));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        Display.add('+');
                        Display.NumAllowed = 1;
                    }
                }else{
                    Plus.setFillColor(plus.ColorBox);
                }
                if (Minu.getGlobalBounds().contains(mouse_pos)){
                    Minu.setFillColor(sf::Color(44,75,22));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        Display.add('-');
                        Display.NumAllowed = 1;
                    }
                }else{
                    Minu.setFillColor(minu.ColorBox);
                }
                if (Mul.getGlobalBounds().contains(mouse_pos)){
                    Mul.setFillColor(sf::Color(44,75,22));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        Display.add('x');
                        Display.NumAllowed = 1;
                    }
                }else{
                    Mul.setFillColor(mul.ColorBox);
                }
                if (Div.getGlobalBounds().contains(mouse_pos)){
                    Div.setFillColor(sf::Color(44,75,22));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        Display.add('/');
                        Display.NumAllowed = 1;
                    }
                }else{
                    Div.setFillColor(div.ColorBox);
                }
            }




            ///////////////////

            /////////////////// del - getback
            if (dele.getGlobalBounds().contains(mouse_pos)){
                dele.setFillColor(sf::Color(44,75,22));
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && hasDel == 0){
                    Display.dataReset();
                    for(int l = 0 ; l < 4; l++) gateway[l] = 0;
                    hasDel = 1;
                }else{hasDel = 0;}
            }else{
                dele.setFillColor(number4.ColorBox); 
            }
            if (Get_Back.getGlobalBounds().contains(mouse_pos)) 
            {
                Get_Back.setFillColor(sf::Color(44,75,22)); 
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    window.clear();
                    state = MENU;
                        
                }
            }
            ////////////////////////////////////////////////
            Display.Calculate();
        }
        window.display();
    }   
}

void ScoreBoard(int data[], int data_n){
    Screen Display;
    Circle_buttonBuild GetBack = { // cic
            .posBox_x = 25,
            .posBox_y = 25, // 2.5 when no float was assian as double type
            .FontSize = 20,
            .Radius = 25,
            .PointinCircle = 100,
            .X = 0,
            .Y = 0,
            .name = "Icon",
            .ColorBox = sf::Color(255,20,52)
        };
    sf::CircleShape Back_Button_Rect = GetBack.Circle_builtButton();
        while (state == SCORE_BOARD){
            window.clear();
            Bar_Chart(window, data, data_n);
            window.draw(Back_Button_Rect);
           
            while (const std::optional event = window.pollEvent()) // Closing windows functions
            {
                if (event->is<sf::Event::Closed>()) window.close();
                auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));// "close requested" event: we close the window 
                if (Back_Button_Rect.getGlobalBounds().contains(mouse_pos)) 
                {
                    Back_Button_Rect.setFillColor(sf::Color(44,75,22)); 
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        window.clear();
                        state = MENU;
                    }
                }else{
                    Back_Button_Rect.setFillColor(GetBack.ColorBox); 
                }
            }
             window.display();
        }
}