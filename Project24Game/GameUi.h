#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <unistd.h>

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
    Title_24.setOutlineColor(sf::Color::Black);
    Title_24.setOutlineThickness(2.f);
    return Title_24;
};



sf::RectangleShape buttonBuild::builtButton(){
    sf::RectangleShape button({buttonSize_x,buttonSize_y}); //Create button variable with size
    button.setPosition({posBox_x,posBox_y}); 
    button.setOrigin(button.getGeometricCenter());
    button.setFillColor(ColorBox);
    return button;
};


sf::Text buttonBuild::txtBox(sf::Vector2f buttonCenter){
    sf::Text Text(font,name,FontSize); 
    sf::FloatRect bounds = Text.getLocalBounds();
    Text.setOrigin({bounds.position.x+bounds.size.x/2,FontSize-bounds.position.y});
    Text.setPosition({posBox_x,posBox_y});
    Text.setOutlineColor(sf::Color::Black);
    Text.setOutlineThickness(2.f);
    return Text;
}


/// ////////////////////////////////
class Pause{
    string word;
    int FontSize;
    float posX;
    float posY;
    public:
        Pause(string,int,float,float);
        sf::Text showText();
};

Pause::Pause(string w,int i,float x ,float y){
    word = w;
    FontSize = i;
    posX = x;
    posY = y;
}

sf::Text Pause::showText(){
    sf::Text TextPause(font,word,FontSize);
    sf::FloatRect bounds = TextPause.getLocalBounds();
    TextPause.setOrigin({bounds.position.x+bounds.size.x/2,FontSize-bounds.position.y});
    TextPause.setPosition({posX,posY});
    TextPause.setOutlineColor(sf::Color::Black);
    TextPause.setOutlineThickness(2.f);
    return TextPause;
}
class BoxName{
    public:
        string name = "";
        sf::Text NameShow();
};

sf::Text BoxName::NameShow(){
    sf::Text Text(font,name,60); 
    sf::FloatRect bounds = Text.getLocalBounds();
    Text.setOrigin({bounds.position.x+bounds.size.x/2,60-bounds.position.y});
    Text.setPosition({windowSize_x/2,WindowSize_y/2});
    Text.setOutlineColor(sf::Color::Black);
    Text.setOutlineThickness(2.f);
    return Text;
}

class Screen{
    vector<double> Data;
    char OpRn;
    public: 
        vector<int>Order;
        string newDataStr;
        double newData;
        int indexMustChage;
        bool NumAllowed = 1;
        void add(char);
        void add(double,int);
        sf::Text printData(int);
        sf::RectangleShape BoxScreen();
        void dataReset();
        void DeleDataLast();
        void Calculate();
        void AllClear();
        void OrderClear();
        sf::Text ShowGoal(double);
    };

void Screen::AllClear(){
    Data.clear();
    Order.clear();
    newData = 0;
    indexMustChage = 0;
    NumAllowed = 1;
}

sf::Text Screen::ShowGoal(double goal){
    stringstream c;
    c << fixed << setprecision(0) << goal;
    sf::Text Text(font,"GOAL : "+c.str(),60); 
    sf::FloatRect bounds = Text.getLocalBounds();
    Text.setOrigin({bounds.position.x+bounds.size.x/2,60-bounds.position.y});
    Text.setPosition({windowSize_x*37/100,WindowSize_y*40/100});
    Text.setOutlineColor(sf::Color::Black);
    Text.setOutlineThickness(2.f);
    return Text;
}

void Screen::DeleDataLast(){
    Data.pop_back();
}

void Screen::OrderClear(){
    Order.clear();
    Data.clear();
}

void Screen::Calculate(){
    if (Data.size() == 2){
        if (OpRn == '+'){
           Data[0] = Data[0]+Data[1];
        }
        if (OpRn == '-'){
           Data[0] = Data[0]-Data[1];
        }
        if (OpRn == 'x'){
           Data[0] = Data[0]*Data[1];
        }
        if (OpRn == '/'){
           Data[0] = Data[0]/Data[1];
        }
        
        stringstream c;
        c << fixed << setprecision(2) << Data[0];
        indexMustChage = Order[1];
        newData = Data[0];
        newDataStr = c.str();
    }
}

void Screen::dataReset(){
    Data.clear();
    NumAllowed = 1;
}

void Screen::add(double inputNumber,int index){
    Data.push_back(inputNumber);
    Order.push_back(index);
}

void Screen::add(char inputNumber){
    OpRn = inputNumber;
}


sf::Text Screen::printData(int time){
    sf::Text Datas(font, to_string(time),100);
    sf::FloatRect boundScreen = Datas.getLocalBounds();
    Datas.setOrigin({boundScreen.position.x+boundScreen.size.x/2,100-boundScreen.position.y});
    Datas.setPosition({windowSize_x - 300.f,150});
    Datas.setOutlineColor(sf::Color::Black);
    Datas.setOutlineThickness(2.f);
    if(time <= 5){
        Datas.setFillColor(sf::Color(255,0,0));
    }
    else if (time <= 10){
        Datas.setFillColor(sf::Color(255,153,51));
    }
    else{
        Datas.setFillColor(sf::Color(255,255,153));
    }
    return Datas;
}

sf::RectangleShape Screen::BoxScreen(){
    sf::RectangleShape Box({windowSize_x*80/100,WindowSize_y*20/100}); //Create button variable with size
    Box.setPosition({windowSize_x/2,150}); 
    Box.setOrigin(Box.getGeometricCenter());
    Box.setFillColor(sf::Color(128,128,128));
    return Box;
}

class AnswerModule{
    string allAnswer = "";
    public:
        void AddallAnswer(vector<string>);
        sf::Text CreateAnsBox(); 
};

void AnswerModule::AddallAnswer(vector<string> setAnswer){  
   for (unsigned int  i = 0; i < setAnswer.size(); i ++){
        allAnswer += setAnswer[i]+" , ";
   }
}

sf::Text  AnswerModule::CreateAnsBox(){
    sf::Text Ans(font,allAnswer,100);
    sf::FloatRect boundScreen = Ans.getLocalBounds();
    Ans.setOrigin({boundScreen.position.x+boundScreen.size.x/2,100-boundScreen.position.y});
    Ans.setPosition({windowSize_x - 300.f,150});
    Ans.setOutlineColor(sf::Color::Black);
    Ans.setOutlineThickness(2.f);
    return Ans;
}



void Bar_Chart(sf::RenderWindow& window, const map<string, int>& data)
{
    vector<pair<string,int>> sortedData(data.begin(), data.end());
    sort(sortedData.begin(), sortedData.end(),[](const auto& a, const auto& b)
     {
         return a.second > b.second; // มากไปน้อย
     });
    int Top_THREE = min(3, (int)sortedData.size());
    if (sortedData.empty())return;

    int data_max = sortedData[0].second;
    // size of window
        float window_w = static_cast<float>(window.getSize().x);
        float window_h = static_cast<float>(window.getSize().y);
    //parameter
        float baseY = 750.f;              // ยกฐานขึ้นจากขอบล่าง
        float space = window_w / 3.f;     // แบ่ง 3 ช่อง
        float barWidth = 160.f;
        float scale = (data_max > 0) ? 320.f / data_max : 1.f;   // scale พอดีจอ
        float No_1_barWidth = 200.f; // แท่งที่ 1 ใหญ่กว่า


    // podium
    vector<int> podiumOrder; // (2,1,3)
    if (sortedData.size() == 1)
        podiumOrder = {0};
    else if (sortedData.size() == 2)
        podiumOrder = {1,0};
    else
        podiumOrder = {1,0,2};

    for (int i = 0; i < Top_THREE; i++)
    {
        int dataIndex = podiumOrder[i];
        if (dataIndex >= sortedData.size())continue;
        auto& [name, point] = sortedData[dataIndex];
        float barHeight = point * scale;

        // ทำ podium effect (แท่งกลางสูงกว่า)
        if (dataIndex == 0) barHeight += 40.f;
        float width = (dataIndex == 0) ? No_1_barWidth : barWidth;
        float posX = (i + 0.5f) * space;
        float posY = baseY - barHeight;

        // BAR
        sf::RectangleShape bar({width, barHeight});
        bar.setOrigin({width/2.f, 0.f});
        bar.setPosition({posX, baseY});
        bar.setScale({1.f, -1.f});
        if (dataIndex == 0)
            bar.setFillColor(sf::Color(0,0,102));
        else
            bar.setFillColor(sf::Color(0,76,153));
        window.draw(bar);

       
        // SCORE (กลางแท่ง)
        sf::Text scoreText(font, to_string(point));
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setOutlineColor(sf::Color::Black);
        scoreText.setOutlineThickness(2.f);

        sf::FloatRect scoreBounds = scoreText.getLocalBounds();
        scoreText.setOrigin({scoreBounds.position.x + scoreBounds.size.x / 2.f,scoreBounds.position.y + scoreBounds.size.y / 2.f});
        scoreText.setPosition({posX, baseY - barHeight/2.f});
        window.draw(scoreText);

        
        // NAME (บนแท่ง)
        sf::Text nameText(font, name);
        nameText.setCharacterSize(26);
        nameText.setFillColor(sf::Color::White);
        nameText.setOutlineColor(sf::Color::Black);
        nameText.setOutlineThickness(2.f);

        sf::FloatRect nameBounds = nameText.getLocalBounds();
        nameText.setOrigin({nameBounds.position.x + nameBounds.size.x / 2.f,nameBounds.position.y + nameBounds.size.y / 2.f});
        nameText.setPosition({posX, posY - 50.f});
        window.draw(nameText);

        // STREAK 6️⃣7️⃣
        //sf::Text streakText(font, "streak :" + to_string(stat.getMaxStreak())); // รอใส่ getMaxStreak() 🤡🤡🤡🤡
        //streakText.setCharacterSize(26);
        //streakText.setFillColor(sf::Color::White);
        //streakText.setOutlineColor(sf::Color::Black);
        //streakText.setOutlineThickness(2.f);

        //sf::FloatRect streakBounds = streakText.getLocalBounds();
        //streakText.setOrigin({streakBounds.position.x + streakBounds.size.x / 2.f,streakBounds.position.y + streakBounds.size.y / 2.f});
        //streakText.setPosition({posX, posY - 20.f});
        //window.draw(streakText);

        // RANK CIRCLE
        sf::CircleShape circle(28.f);
        circle.setOrigin({28.f, 28.f});
        circle.setPosition({posX, posY - 100.f});
        if (dataIndex == 0)
            circle.setFillColor(sf::Color(255,215,0));
        else if (dataIndex == 1)
            circle.setFillColor(sf::Color(192,192,192));
        else
            circle.setFillColor(sf::Color(205,127,50));
        window.draw(circle);

        sf::Text rankText(font, to_string(dataIndex+1));
        rankText.setCharacterSize(22);
        rankText.setFillColor(sf::Color::White);
        rankText.setOutlineColor(sf::Color::Black);
        rankText.setOutlineThickness(2.f);

        sf::FloatRect rankBounds = rankText.getLocalBounds();
        rankText.setOrigin({rankBounds.position.x + rankBounds.size.x / 2.f,rankBounds.position.y + rankBounds.size.y / 2.f});
        rankText.setPosition(circle.getPosition());
        window.draw(rankText);
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
    Text.setOrigin({(bounds.position.x+bounds.size.x/2)+X,(FontSize-bounds.position.y)+Y});
    Text.setPosition(buttonCenter); 
    return Text;
}

void drawBackArrow(sf::RenderWindow& window, sf::Vector2f position, float scale = 1.0f, sf::Color color = sf::Color::White){
    sf::ConvexShape arrow;
    float bodyLength = 15.f;
    float bodyHeight = 8.f;
    float headLength = 15.f;
    float headHeight = 20.f;

    // Body (Rectangle) 
    sf::RectangleShape body;
    body.setSize({bodyLength, bodyHeight});
    body.setFillColor(color);
    body.setOrigin({0.f, bodyHeight / 2.f});
    body.setPosition(position);
    body.setOutlineColor(sf::Color::Black);
    body.setOutlineThickness(2.f);

    // Head (Triangle)
    sf::ConvexShape head;
    head.setPointCount(3);
    head.setPoint(0, {-headLength,                  0});         
    head.setPoint(1, {0          , -headHeight / 2.f});
    head.setPoint(2, {0          ,  headHeight / 2.f});
    head.setFillColor(color);
    head.setOrigin({0.f, 0.f});
    head.setPosition(position);
    head.setOutlineColor(sf::Color::Black);
    head.setOutlineThickness(2.f);

    // scale ทั้ง body และ head
    body.setScale({scale, scale});
    head.setScale({scale, scale});
    window.draw(body);
    window.draw(head);
}

class Animation
{
private:
    std::vector<sf::Texture> frames;
    std::optional<sf::Sprite> sprite;
    int currentFrame = 0;
    float frameTime = 0.1f;
    sf::Clock clock;

public:
    Animation() {}
    Animation(const std::string& folder,
              const std::string& baseName,
              const std::string& extension,
              int totalFrames)
    {
        load(folder, baseName, extension, totalFrames);
    }

    bool load(const std::string& folder,
              const std::string& baseName,
              const std::string& extension,
              int totalFrames)
    {
        for (int i = 0; i < totalFrames; i++){
            sf::Texture texture;
            std::string path =
                folder + "/" + baseName +
                std::to_string(i) + "." + extension;
            if (!texture.loadFromFile(path))
                return false;
            frames.push_back(texture);
        }
        if (!frames.empty())
            sprite.emplace(frames[0]);  
            sprite->setPosition({0, 0});
            sprite->setScale({800.f / frames[0].getSize().x, 800.f / frames[0].getSize().y});
        return true;
    }
    void update()
    {
        if (!sprite) return;
        if (clock.getElapsedTime().asSeconds() > frameTime){
            currentFrame++;
            if (currentFrame >= frames.size())
                currentFrame = 0;

            sprite->setTexture(frames[currentFrame]);
            clock.restart();
        }
    }
    void draw(sf::RenderWindow& window){
        if (sprite)
            window.draw(*sprite);
    }
    void setFrameTime(float t){
        frameTime = t;
    }
};

void ScoreStreak_inPause(sf::RenderWindow& window, int point, float posX, float posY){
    sf::Text scoreText(font, to_string(point));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setOutlineThickness(2.f);

    sf::CircleShape scoreCircle(50.f);
    scoreCircle.setOrigin(scoreCircle.getGeometricCenter());
    scoreCircle.setPosition({posX, posY});
    scoreCircle.setFillColor(sf::Color(255,0,0));
    window.draw(scoreCircle);

    sf::FloatRect scoreBounds = scoreText.getLocalBounds();
    scoreText.setOrigin({scoreBounds.position.x + scoreBounds.size.x / 2.f,scoreBounds.position.y + scoreBounds.size.y / 2.f});
    scoreText.setPosition(scoreCircle.getPosition());
    window.draw(scoreText);
    
}

void GradiantBackground_Pause(sf::RenderWindow& window){
    sf::VertexArray gradient(sf::PrimitiveType::TriangleStrip, 4);
    gradient[0].position = {0.f, 0.f};
    gradient[1].position = {800.f, 0.f};
    gradient[2].position = {0.f, 800.f};
    gradient[3].position = {800.f, 800.f};

    // ไล่สี บน → ล่าง
    gradient[0].color = sf::Color(80, 0, 150);
    gradient[1].color = sf::Color(40, 0, 70);
    gradient[2].color = sf::Color(10, 0, 20);
    gradient[3].color = sf::Color(0, 0, 0);
    window.draw(gradient);
}

void GradiantBackground_Game24(sf::RenderWindow& window){
    sf::VertexArray gradient24(sf::PrimitiveType::TriangleStrip, 4);
    gradient24[0].position = {0.f, 0.f};
    gradient24[1].position = {800.f, 0.f};
    gradient24[2].position = {0.f, 800.f};
    gradient24[3].position = {800.f, 800.f};

    // ไล่สี บน → ล่าง
    gradient24[0].color = sf::Color(10,10,30);
    gradient24[1].color = sf::Color(10,10,30);
    gradient24[2].color = sf::Color(40,0,80);
    gradient24[3].color = sf::Color(40,0,80);
    window.draw(gradient24);
}

void DrawKumWa_Time(sf::RenderWindow& window){ // คำว่า Time: เฉยๆ แยกออกจากกัน กูอยากเปลี่ยนสีเฉพาะตัวเลข
    sf::Text TimeText(font,"Time :",100);
    sf::FloatRect boundScreen = TimeText.getLocalBounds();
    TimeText.setOrigin({boundScreen.position.x+boundScreen.size.x/2,100-boundScreen.position.y});
    TimeText.setPosition({windowSize_x/3,150});
    TimeText.setOutlineColor(sf::Color::Black);
    TimeText.setOutlineThickness(2.f);
    window.draw(TimeText);
}

void DrawTronGrid(sf::RenderWindow& window, float offset)
{
    int spacing = 40;
    // เส้นแนวนอน 
    for(int y = -800; y < 800; y += spacing)
    {
        float pos = y + offset;

        sf::Vertex line[2];

        line[0].position = sf::Vector2f(0.f, pos);
        line[0].color = sf::Color(0,255,255,30);

        line[1].position = sf::Vector2f(800.f, pos);
        line[1].color = sf::Color(0,255,255,30);

        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

void GameOver_Text(sf::RenderWindow& window){
    sf::Text gameOverText(font, "GAME OVER!!");
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(2.f);

    sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin({gameOverBounds.position.x + gameOverBounds.size.x / 2.f,gameOverBounds.position.y + gameOverBounds.size.y / 2.f});
    gameOverText.setPosition({windowSize_x/2, 300});
    window.draw(gameOverText);
}

void EnterName_Text(sf::RenderWindow& window){
    sf::Text EnterName(font, "- - ENTER YOUR NAME - -");
    EnterName.setCharacterSize(50);
    EnterName.setFillColor(sf::Color::White);
    EnterName.setOutlineColor(sf::Color::Black);
    EnterName.setOutlineThickness(2.f);

    sf::FloatRect EnterNameBounds = EnterName.getLocalBounds();
    EnterName.setOrigin({EnterNameBounds.position.x + EnterNameBounds.size.x / 2.f,EnterNameBounds.position.y + EnterNameBounds.size.y / 2.f});
    EnterName.setPosition({windowSize_x/2, 200});
    window.draw(EnterName);
}