#include "GameUi.h"


int main()
{   
    // Build Windows Frame
    sf::RenderWindow window(sf::VideoMode({1600,900}), "GAME24"); //Create window variable with size and tittle name'
    Title tilte;


    // button24
    buttonBuild button24 = {
        .posBox_x = windowSize_x*1/5,
        .posBox_y = WindowSize_y/(float)2, // 2.5 when no float was assian as double type
        .FontSize = 75,
        .buttonSize_x = 300,
        .buttonSize_y = 100,
        .X = 5,
        .Y = 0,
        .name = "Game24",
        .ColorBox = sf::Color(255,0,0)
    };

    // buttonN
    buttonBuild buttonN = {
        .posBox_x = windowSize_x*4/5,
        .posBox_y = WindowSize_y/(float)2, // 2.5 when no float was assian as double type
        .FontSize = 75,
        .buttonSize_x = 300,
        .buttonSize_y = 100,
        .X = 5,
        .Y = 0,
        .name = "Random",
        .ColorBox = sf::Color(0,250,0)
    };
    
    sf:: RectangleShape button_24 = button24.builtButton();
    sf:: RectangleShape button_N = buttonN.builtButton();
    
    // GameOn
    while (window.isOpen()) // using to make window always open 
    {
        while (const std::optional event = window.pollEvent()) // Closing windows functions
        {
            if (event->is<sf::Event::Closed>()) window.close(); // "close requested" event: we close the window 
        }// 
        auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
        if (button_24.getGlobalBounds().contains(mouse_pos)) // check button is coline with mouse : augmentNeedtoCheck.getGlobalBound().contains(whatIscheckwith); >> getGlobalBound() = check coline
        {
            button_24.setFillColor(sf::Color(0,75,22)); // we can create animated or click to process
        }else{
            button_24.setFillColor(button24.ColorBox); // reset went not set
        }
        if (button_N.getGlobalBounds().contains(mouse_pos)) // check button is coline with mouse : augmentNeedtoCheck.getGlobalBound().contains(whatIscheckwith); >> getGlobalBound() = check coline
        {
            button_N.setFillColor(sf::Color(0,75,22)); // we can create animated or click to process
        }else{
            button_N.setFillColor(buttonN.ColorBox); // reset went not set
        }

        
        // windown.draw is order by line to line upper = under
        window.clear(sf::Color::Black);
        window.draw(tilte.TitleName());
        window.draw(button_24);
        window.draw(button_N);
        window.draw(button24.txtBox(button24.builtButton().getGeometricCenter()));
        window.draw(buttonN.txtBox(buttonN.builtButton().getGeometricCenter()));    


        
        // end the current frame
        window.display();
    }

}
