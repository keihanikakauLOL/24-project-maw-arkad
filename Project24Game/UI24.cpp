#include "GameUi.h"
#include "24GameAlgo.h"
#include "timer_point.h"

void GameSystem24();
void ScoreBoard(const map<string, int>& data);
void Menu();
void GameOver();
void Round(string,double);
void GameRandom();
void pauseScreen();
string EnterName();
Game stat;
bool inGame24 = 0;
sf::Texture texture_win("Images/Winnig.png");
sf::Sprite sprite_win(texture_win);
sf::RenderWindow window(sf::VideoMode({800,800}), "GAME24"); //Create window variable with size and tittle name' tit?
Animation anim("BG", "Menu", "jpg", 25);
Animation anim_OverBG("GameOverBG", "gameOver ", "png", 26);
sf::Clock gameClock;

enum GameState { // state of game to process more easily
    MENU,
    GAME24,
    RANDOM_MODE,
    SCORE_BOARD
};

enum Game24subState {
    NotInGame,
    InEnterName,
    InRound,
    InGameOver,
    InPause,
};

GameState state = MENU;
Game24subState gameOn = NotInGame; 
Game::GameState status = stat.ChooseYourChoice();
map<string, int> scoreData;
string Player_Name;
int Player_Score;

int main()
{    
    window.setFramerateLimit(144);
    createQuestions(); 
    srand(time(0));
    while (window.isOpen())
    {
        if (state == MENU){Menu();}
        if (state == GAME24){usleep(80000);GameSystem24();}
        if (state == RANDOM_MODE){usleep(80000);GameRandom();}
        if (state == SCORE_BOARD){
            map<string, int> scoreData = {
                {"ARM",55},
                {"MING",60},
                {"THIW",35}
            };
            usleep(80000);
            ScoreBoard(scoreData);
        }
    }
    
}

void Menu(){
    // Build Windows Frame
    stat.start();
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
    
    
    // GameOn
    while (state == MENU)
    {
        window.clear();
        anim.update();
        anim.draw(window);
        auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
        if(auto event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()) {stat.quit();window.close();return;}
        
            if (button_24.getGlobalBounds().contains(mouse_pos)) // check button is coline with mouse : augmentNeedtoCheck.getGlobalBound().contains(whatIscheckwith); >> getGlobalBound() = check coline
            {
                button_24.setFillColor(sf::Color(0,75,22)); // we can create animated or click to process
                if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                    if (mouseButtonPressed->button == sf::Mouse::Button::Left){state = GAME24;}
                }
            }else{
                button_24.setFillColor(button24.ColorBox); // reset went not set
            }
            if (button_N.getGlobalBounds().contains(mouse_pos)) // check button is coline with mouse : augmentNeedtoCheck.getGlobalBound().contains(whatIscheckwith); >> getGlobalBound() = check coline
            {
                button_N.setFillColor(sf::Color(0,75,22)); // we can create animated or click to process
                if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                    if (mouseButtonPressed->button == sf::Mouse::Button::Left){state = RANDOM_MODE;}
                }
            }else{
                button_N.setFillColor(buttonN.ColorBox); // reset went not set
            }
            if (button_Score.getGlobalBounds().contains(mouse_pos)) // check button is coline with mouse : augmentNeedtoCheck.getGlobalBound().contains(whatIscheckwith); >> getGlobalBound() = check coline
            {
                button_Score.setFillColor(sf::Color(0,75,22)); // we can create animated or click to process
                if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                    if (mouseButtonPressed->button == sf::Mouse::Button::Left){state = SCORE_BOARD;}
                }
                
            }else{
                button_Score.setFillColor(buttonScore.ColorBox); // reset went not set
            }
        }
            // windown.draw is order by line to line upper = under
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

void GameSystem24(){
    status.score = 0;
    status.streak = 0;
    Player_Score = 0;
    gameOn = InEnterName;
    Player_Name = EnterName();
    usleep(80000);
    int type_games = 24;
    double goal = (double)type_games;
    newCreateList(type_games);
    while (state == GAME24){ 
        gameOn = InRound; 
        string setNumber = newGetfile(); // random
        stat.resumeTimer();
        Round(setNumber,goal);
        status = stat.ChooseYourChoice();
        stat.pauseTimer();
        usleep(11000);
        pauseScreen();
        stat.resettimer();
    }
    // cout << status.score; //return score streak ;
    Player_Score = status.score; 
    // cout << status.streak;
    // cout << Player_Name;
}

string EnterName(){
    BoxName Player;
    buttonBuild EnterName = {
        .posBox_x = windowSize_x*50/100,
        .posBox_y = WindowSize_y*65/100, // 2.5 when no float was assian as double type
        .FontSize = 60,
        .buttonSize_x = 300,
        .buttonSize_y = 150,
        .X = 0,
        .Y = 0,
        .name = "Let's Play",
        .ColorBox = sf::Color(255,20,52)
        };
    sf::RectangleShape EnterNameButton = EnterName.builtButton();
    while (gameOn == InEnterName){
        window.clear();
        auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
        if(auto event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()) window.close();
            if (EnterNameButton.getGlobalBounds().contains(mouse_pos)) 
            {
                EnterNameButton.setFillColor(sf::Color(44,75,22)); 
                if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                    if (mouseButtonPressed->button == sf::Mouse::Button::Left){gameOn = NotInGame;}
                }
            }else{
                EnterNameButton.setFillColor(EnterName.ColorBox);
            }
            if (auto* keyPressed = event ->getIf<sf::Event::KeyPressed>()){
                string Alpahbet = sf::Keyboard::getDescription(keyPressed->scancode).toAnsiString();
                Player.name += Alpahbet;
            }
        }
        GradiantBackground_Game24(window);
        EnterName_Text(window);
        window.draw(EnterNameButton);
        window.draw(EnterName.txtBox(EnterNameButton.getGeometricCenter()));
        window.draw(Player.NameShow());
        window.display();
    }
    return Player.name;
}

void GameOver(){
    BoxName Player;
    buttonBuild ReturnMenu= {
        .posBox_x = windowSize_x*50/100,
        .posBox_y = WindowSize_y*65/100, // 2.5 when no float was assian as double type
        .FontSize = 100,
        .buttonSize_x = 300,
        .buttonSize_y = 150,
        .X = 0,
        .Y = 0,
        .name = "Exit",
        .ColorBox = sf::Color(255,20,52)
        };
    sf::RectangleShape ReturnMenuButton = ReturnMenu.builtButton();
    while (gameOn == InGameOver){
        window.clear();
        anim_OverBG.update();
        anim_OverBG.draw(window);
        auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
        if(auto event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()) window.close();
            if (ReturnMenuButton.getGlobalBounds().contains(mouse_pos)) 
            {
                ReturnMenuButton.setFillColor(sf::Color(44,75,22)); 
                if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                    if (mouseButtonPressed->button == sf::Mouse::Button::Left){state = MENU;gameOn = NotInGame;}
                }
            }else{
                ReturnMenuButton.setFillColor(ReturnMenu.ColorBox);
            }
        }
        window.draw(ReturnMenuButton);
        window.draw(ReturnMenu.txtBox(ReturnMenuButton.getGeometricCenter()));
        GameOver_Text(window);
        window.draw(Player.NameShow());
        window.display();
    }
}

void GameRandom(){
    gameOn = InEnterName;
    Player_Name = EnterName();
    while (state == RANDOM_MODE){
        int type_games = rand()%90+10;
        double goal = (double)type_games;
        clearvector();
        newCreateList(type_games);
        gameOn = InRound; 
        string setNumber = newGetfile(); 
        stat.resumeTimer();
        Round(setNumber,goal);
        status = stat.ChooseYourChoice();
        stat.pauseTimer(); 
        usleep(11000);
        pauseScreen();
        stat.resettimer();
    }
}

void Round(string setNumberString,double goal){ // time 
    double setNumber[4];
    vector<string> setNumberStr;
    for (int i = 0 ;i < setNumberString.size(); i++){
        setNumberStr.push_back(to_string(setNumberString[i]-48));
        setNumber[i] = (double)setNumberString[i]-48;
    }
    Screen Display;
    bool gateway[] = {0,0,0,0};
    bool hasDel = 0;
    buttonBuild number1 = {
        .posBox_x = windowSize_x*25/100,
        .posBox_y = WindowSize_y*60/100, // 2.5 when no float was assian as double type
        .FontSize = 50,
        .buttonSize_x = 150,
        .buttonSize_y = 150,
        .X = 0,
        .Y = 0,
        .name = setNumberStr[0],
        .ColorBox = sf::Color(255,20,52)
        };
    buttonBuild number2 = {
            .posBox_x = windowSize_x*50/100,
            .posBox_y = WindowSize_y*60/100, // 2.5 when no float was assian as double type
            .FontSize = 50,
            .buttonSize_x = 150,
            .buttonSize_y = 150,
            .X = 0,
            .Y = 0,
            .name = setNumberStr[1],
            .ColorBox = sf::Color(255,20,52)
        };
    buttonBuild number3 = {
            .posBox_x = windowSize_x*25/100,
            .posBox_y = WindowSize_y*85/100, // 2.5 when no float was assian as double type
            .FontSize = 50,
            .buttonSize_x = 150,
            .buttonSize_y = 150,
            .X = 0,
            .Y = 0,
            .name = setNumberStr[2],
            .ColorBox = sf::Color(255,20,52)
        };
    buttonBuild number4 = {
            .posBox_x = windowSize_x*50/100,
            .posBox_y = WindowSize_y*85/100, // 2.5 when no float was assian as double type
            .FontSize = 50,
            .buttonSize_x = 150,
            .buttonSize_y = 150,
            .X = 0,
            .Y = 0,
            .name = setNumberStr[3],
            .ColorBox = sf::Color(255,20,52)
        };
    sf::RectangleShape number_1 = number1.builtButton();
    sf::RectangleShape number_2 = number2.builtButton();
    sf::RectangleShape number_3 = number3.builtButton();
    sf::RectangleShape number_4 = number4.builtButton();
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
            .Radius = 30,
            .PointinCircle = 100,
            .X = 0,
            .Y = 0,
            .name = "Clear",
            .ColorBox = sf::Color(255,20,52)
        };   
    Circle_buttonBuild ret = { // cic
            .posBox_x = windowSize_x*90/100,
            .posBox_y = WindowSize_y*45/100, // 2.5 when no float was assian as double type
            .FontSize = 25,
            .Radius = 25,
            .PointinCircle = 100,
            .X = 0,
            .Y = 0,
            .name = "Re",
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
            .name = "",
            .ColorBox = sf::Color(255,20,52)
        };
    sf::CircleShape Plus = plus.Circle_builtButton(); 
    sf::CircleShape Minu = minu.Circle_builtButton(); 
    sf::CircleShape Mul = mul.Circle_builtButton(); 
    sf::CircleShape Div = div.Circle_builtButton(); 
    sf::CircleShape Get_Back = GetBack.Circle_builtButton(); 
    sf::CircleShape dele = del.Circle_builtButton(); 
    sf::CircleShape Ret = ret.Circle_builtButton(); 
    while (gameOn == InRound){
        
        number1.name = setNumberStr[0];
        number2.name = setNumberStr[1];
        number3.name = setNumberStr[2];
        number4.name = setNumberStr[3];
        if (gateway[0] == 1){number_1.setFillColor(sf::Color::Blue);}
        if (gateway[1] == 1){number_2.setFillColor(sf::Color::Blue);}
        if (gateway[2] == 1){number_3.setFillColor(sf::Color::Blue);} // need to change to invisible// 
        if (gateway[3] == 1){number_4.setFillColor(sf::Color::Blue);}
        auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));// "close requested" event: we close the window 
        window.clear();
        GradiantBackground_Game24(window);// เพ่มพื้นหลังแบบไล่สี 
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
        drawBackArrow(window, {25, 25}, 1.f, sf::Color::White); // draw back icon
        //
        window.draw(dele);
        window.draw(del.Circle_txtBox(dele.getPosition()));
        //
        window.draw(Ret);
        window.draw(ret.Circle_txtBox(Ret.getPosition()));
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
        //
        window.draw(Display.ShowGoal(goal));
        window.draw(Display.BoxScreen());
        if(auto event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){stat.quit();window.close();}

            if (Display.NumAllowed == 1)
            {
                if (number_1.getGlobalBounds().contains(mouse_pos)) 
                {
                    number_1.setFillColor(sf::Color(44,75,22));
                    if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){ 
                        if (gateway[0] == 0 && mouseButtonPressed->button == sf::Mouse::Button::Left){
                            gateway[0] = 1;
                            Display.add(setNumber[0],0);
                            Display.NumAllowed = 0;
                        }
                    }
                }else{
                    number_1.setFillColor(number1.ColorBox);
                }
                if (number_2.getGlobalBounds().contains(mouse_pos))
                {
                    number_2.setFillColor(sf::Color(44,75,22));
                    if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){ 
                        if (gateway[1] == 0 && mouseButtonPressed->button == sf::Mouse::Button::Left){
                            gateway[1] = 1;
                            Display.add(setNumber[1],1); 
                            Display.NumAllowed = 0;
                        }
                    }
                }else{
                        number_2.setFillColor(number2.ColorBox);
                    }
                    if (number_3.getGlobalBounds().contains(mouse_pos)) 
                    {
                        number_3.setFillColor(sf::Color(44,75,22)); 
                        if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                        if (gateway[2] == 0 && mouseButtonPressed->button == sf::Mouse::Button::Left){
                            gateway[2] = 1;
                            Display.add(setNumber[2],2);
                            Display.NumAllowed = 0;
                        }
                    }
                }else{
                        number_3.setFillColor(number3.ColorBox); 
                    }
                    if (number_4.getGlobalBounds().contains(mouse_pos)){
                        number_4.setFillColor(sf::Color(44,75,22));
                        if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                            if (gateway[3] == 0 && mouseButtonPressed->button == sf::Mouse::Button::Left){
                                gateway[3] = 1;
                                Display.add(setNumber[3],3);
                                Display.NumAllowed = 0;
                            }
                        }
                    }else{
                        number_4.setFillColor(number4.ColorBox); 
                    }
                }
                else{
                    if (Plus.getGlobalBounds().contains(mouse_pos)){
                        Plus.setFillColor(sf::Color(44,75,22));
                        if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                            if (mouseButtonPressed->button == sf::Mouse::Button::Left){
                                Display.add('+');
                                Display.NumAllowed = 1;
                            }
                        }
                    }else{
                        Plus.setFillColor(plus.ColorBox);
                    }
                    if (Minu.getGlobalBounds().contains(mouse_pos)){
                        Minu.setFillColor(sf::Color(44,75,22));
                        if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                            if (mouseButtonPressed->button == sf::Mouse::Button::Left){
                                Display.add('-');
                                Display.NumAllowed = 1;
                            }
                        }
                    }else{
                        Minu.setFillColor(minu.ColorBox);
                    }
                    if (Mul.getGlobalBounds().contains(mouse_pos)){
                        Mul.setFillColor(sf::Color(44,75,22));
                        if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                            if (mouseButtonPressed->button == sf::Mouse::Button::Left){
                                Display.add('x');
                                Display.NumAllowed = 1;
                            }
                        }
                    }else{
                        Mul.setFillColor(mul.ColorBox);
                    }
                    if (Div.getGlobalBounds().contains(mouse_pos)){
                        Div.setFillColor(sf::Color(44,75,22));
                        if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                            if (mouseButtonPressed->button == sf::Mouse::Button::Left){
                                Display.add('/');
                                Display.NumAllowed = 1;
                            }
                        }
                    }else{
                        Div.setFillColor(div.ColorBox);
                    }
                }
        if (dele.getGlobalBounds().contains(mouse_pos)){
            dele.setFillColor(sf::Color(44,75,22));
            if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                if (mouseButtonPressed->button == sf::Mouse::Button::Left && hasDel == 0){
                    Display.dataReset();
                    for(int l = 0 ; l < 4; l++) gateway[l] = 0;
                    setNumberStr.clear();
                    for (int i = 0 ;i < setNumberString.size(); i++){
                        setNumberStr.push_back(to_string(setNumberString[i]-48));
                        setNumber[i] = (double)setNumberString[i]-48;
                    }
                    Plus.setFillColor(plus.ColorBox);
                    Mul.setFillColor(mul.ColorBox);
                    Div.setFillColor(div.ColorBox);
                    Minu.setFillColor(minu.ColorBox);
                    hasDel = 1;
                    Display.AllClear();
                }
            }else{hasDel = 0;}
        }else{
            dele.setFillColor(number4.ColorBox); 
        }
        if (Get_Back.getGlobalBounds().contains(mouse_pos)) 
        {
            Get_Back.setFillColor(sf::Color(44,75,22));
            if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){ 
                if (mouseButtonPressed->button == sf::Mouse::Button::Left){
                    window.clear();
                    state = MENU;
                    gameOn = NotInGame;
                }
            }
        }
        if (Ret.getGlobalBounds().contains(mouse_pos)) 
        {
            Ret.setFillColor(sf::Color(44,75,22));
            if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){ 
                if (mouseButtonPressed->button == sf::Mouse::Button::Left && Display.Order.size() > 0 && Display.NumAllowed == 0){
                    gateway[Display.Order.back()] = 0;
                    Display.Order.pop_back();
                    Display.DeleDataLast();
                    Display.NumAllowed = 1;
                }
            }
            if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                if (mouseButtonPressed->button == sf::Mouse::Button::Left && Display.Order.size() > 0 && Display.NumAllowed == 1){
                    Display.NumAllowed = 0;
                    usleep(80000);
                }
            }
        }else{
            Ret.setFillColor(ret.ColorBox);
        }
    }   if (stat.getTimeLeft() == 0){
            scoreData[Player_Name] = max(scoreData[Player_Name], status.score); // ยัดลง map โดยถ้าคะแนนเก่ามากกว่าไม่อัพเดต ถ้าใหม่มากกว่าอัพเดต เหลือบันทึกลงไฟล์นอก
            gameOn = InGameOver;
            GameOver();
        } 
        Display.Calculate();
        
        if (Display.Order.size() == 2)
        {
            if (gateway[0] == 1 && gateway[1] == 1 && gateway[2] == 1 && gateway[3] == 1){ //tips
                if (true){ //abs(Display.newData-goal) < 1e-9 
                    stat.updateStreakAndScore(true);
                    gameOn = InPause; // check part
                }else (stat.updateStreakAndScore(false));
            }
            setNumber[Display.indexMustChage] = Display.newData;
            setNumberStr[Display.indexMustChage] = Display.newDataStr;
            gateway[Display.indexMustChage] = 0;
            usleep(80000);
            Display.OrderClear();
            Display.NumAllowed = 1;
        }
        window.draw(Display.printData(stat.getTimeLeft()));
        DrawKumWa_Time(window);
        window.display();
    }
}



void pauseScreen(){ // add steak  // score
    Pause TitlePause("PauseTime",100,windowSize_x/2,100);
    Pause StreakShow("Streak",60,windowSize_x*8/10,WindowSize_y*4/10);
    Pause ScoreShow("Score",60,windowSize_x*2/10,WindowSize_y*4/10);
    buttonBuild GoNext = buttonBuild{
        .posBox_x = windowSize_x*5/10,
        .posBox_y = WindowSize_y*8/10, // 2.5 when no float was assian as double type
        .FontSize = 50,
        .buttonSize_x = 225,
        .buttonSize_y = 100,
        .X = 0,
        .Y = 0,
        .name = "GoNext",
        .ColorBox = sf::Color(0,51,102)
    };
    sf::RectangleShape buttonGo = GoNext.builtButton();
    while (gameOn == InPause)
    {
        
        window.clear();
        GradiantBackground_Pause(window);
        float offset = fmod(gameClock.getElapsedTime().asSeconds()*60.f, 40.f);
        DrawTronGrid(window, offset);
        ScoreStreak_inPause(window, status.score ,windowSize_x*2/10,WindowSize_y*5/10); // score => getTolScore()
        ScoreStreak_inPause(window, status.streak  ,windowSize_x*8/10,WindowSize_y*5/10); // streak => getCurrentStreak()
        window.draw(buttonGo);
        window.draw(GoNext.txtBox(buttonGo.getGeometricCenter()));
        window.draw(TitlePause.showText());
        window.draw(StreakShow.showText());
        window.draw(ScoreShow.showText());
        auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
        if(auto event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()) window.close();
            if (buttonGo.getGlobalBounds().contains(mouse_pos)){
                buttonGo.setFillColor(sf::Color(0,75,22));
                if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                    if (mouseButtonPressed->button == sf::Mouse::Button::Left){
                        usleep(80000);
                        gameOn = InRound;
                    }
                }
            }
            else{
                buttonGo.setFillColor(GoNext.ColorBox);
            }
        }
        
        window.display();
    }
    
}


void ScoreBoard(const map<string, int>& data){
    sprite_win.setPosition({0, 0});
    sprite_win.setScale({800.f / texture_win.getSize().x, 800.f / texture_win.getSize().y});
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
            window.draw(sprite_win);
            Bar_Chart(window, data);
            window.draw(Back_Button_Rect);
            drawBackArrow(window, {25, 25}, 1.f, sf::Color::White); // draw back icon
            
            auto mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
            if(auto event = window.pollEvent()){
                if (event->is<sf::Event::Closed>()) window.close();
                if (Back_Button_Rect.getGlobalBounds().contains(mouse_pos)) 
                {
                    Back_Button_Rect.setFillColor(sf::Color(44,75,22));
                    if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){ 
                        if (mouseButtonPressed->button == sf::Mouse::Button::Left){
                            window.clear();
                            state = MENU;
                        }
                    }
                }else{
                    Back_Button_Rect.setFillColor(GetBack.ColorBox); 
                }
            }
            window.display();
        }
             
}
