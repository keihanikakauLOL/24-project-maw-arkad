#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
using namespace std;
int main(){

    //create window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Title");

    // create shape of button
    sf::RectangleShape shape({200.f, 100.f});
    shape.setOrigin(shape.getGeometricCenter());
    shape.setPosition({400.f, 300.f});

    // state of button
    bool isOver = false;
    bool isMousePressed = false;
    bool isPressedInsided = false;

    //inf.loop window while window still open
    while(window.isOpen())
    {
        //handle events
        while(std::optional event = window.pollEvent())
        {
            // when close button is clicked
            if(event -> is <sf::Event::Closed>())
            {
                // close window 
                window.close();
            }
            // when window is resized
            else if (event-> is <sf::Event::Resized>())
            {
                cout << "Window " << window.getSize().x << ", " << window.getSize().y << endl;
                cout << "View " << window.getView().getSize().x << ", " << window.getView().getSize().y << endl;
            }


        }
        // fill window with color
        window.clear(sf::Color(64,64,64));

        //----------------get mouse position----------------------
        //sf::Vector2i position = sf::Mouse::getPosition(window);
        //cout << "x = " << position.x;
        //cout << ", y = " << position.y;

        // mouse position
        auto mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

        // state of mouse 
        bool onMousePress = false;
        bool onMouseRelease = false;
        

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if(not isMousePressed)
            {   onMousePress = true;}
            isMousePressed = true;
        }
        else // not clicked
        {
            if(isMousePressed)
            {   onMouseRelease = true;}
            isMousePressed = false;
        }



        //when mouse is over button
        if (shape.getGlobalBounds().contains(mouse_position))
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {shape.setFillColor(sf::Color::Yellow);}
            else{shape.setFillColor(sf::Color(0, 170, 255));}
            

            //on mouse enter
            if (not isOver)
            {   cout << "Enter\n";}
            // set state button
            isOver = true;

            // on mouse press
            if  (onMousePress)
            {       
                cout << "Pressed\n";
                // set pressed inside
                isPressedInsided = true;
            }

            if  (onMouseRelease and isPressedInsided)
            {       cout << "Release\n";}
        }
        else
        {
            shape.setFillColor(sf::Color::White);

            if (isOver)
            {   cout << "Leave\n";}
            //reset start button
            isOver = false;
        }
        // reset pressed inside
        if (not isMousePressed) // isMousePressed = false if we didnt click.
            isPressedInsided = false;


        //draw button
        window.draw(shape);

        
        //------------------------------------------------------------


        // size of window
        float window_w = window.getView().getSize().x;
        float window_h = window.getView().getSize().y;
        float window_min = (window_w < window_h ) ? window_w : window_h;
        
        //display
        window.display();
    }
    return 0;
}