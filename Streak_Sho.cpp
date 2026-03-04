#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
void StreakTrack(bool ans){
    const int base_score = 5;
    const int streak_base = 3;
    static int curstreak=0;
    static int tolscore=0;
    static int max_streak=0;
    int received_score;
    if(ans){
        curstreak++;
        int received_score;
        if(curstreak >= streak_base){
            if(curstreak>= max_streak){
                max_streak = curstreak;
            }
            received_score = base_score * curstreak;
            cout << "Correct! Streak: " << curstreak << endl;
            cout << "Score: +" << received_score << " | Total: " << tolscore + received_score << endl;
            //ให้ HUD Display Streak หลังจากตอบถูก 3 ครั้งติดต่อกัน 
            //ละก็ Display คะแนนทุกๆครั้งด้วย
        }else {
            received_score = base_score;
            cout << "Correct!" << endl;
            cout << "Score: +" << received_score << " | Total: " << tolscore + received_score << endl;
        }
        tolscore += received_score;
    }else{
        curstreak = 0; // Display คะแนนที่มีอยู่ (ไม่รู้ว่าจะแพ้เลยมั้ย ต้องถาม The Gng)
        cout << "Wrong! Streak reset." << endl;
        cout << "Total score: " << tolscore << endl;
    }
}
int getTolScore() {
    static int tolscore = 0;  // Must match the static variable in StreakTrack
    return tolscore;
}

int getMaxStreak() {
    static int max_streak = 0;  // Must match the static variable in StreakTrack
    return max_streak;
}

int getCurrentStreak() {
    static int curstreak = 0;
    return curstreak;
}
struct User{
    string name;
    double bestTime;        //เวลา มาก/น้อย สุดที่ Userใช้ภายใน 1 ด่าน ตอนนี้เป็นมากสุด ถ้าอยากแก้ก็แก้ได้
    int highestScore;
    int highestStreak;
    User() : name(""), bestTime(0.0), highestScore(0), highestStreak(0) {}
    User(string n, double t, int score, int streak) 
        : name(n), bestTime(t), highestScore(score), highestStreak(streak) {}
};
class Scoreboard {
private:
    map<string, User> players; // key = player name, value = their data
public:
    // เพิ่ม Player ใหม่ หรือ อัพเดท คนเดิม
    void addOrUpdatePlayer(string name, double time, int score, int streak) {
        if (players.find(name) != players.end()) {
            User& player = players[name];
            
            if (time > player.bestTime) {
                player.bestTime = time;
            }
            if (score > player.highestScore) {
                player.highestScore = score;
            }
            if (streak > player.highestStreak) {
                player.highestStreak = streak;
            }
        } else {
            //เพิ่ม Player ใหม่
            players[name] = User(name, time, score, streak);
        }
    }
    // แสดงผล Player ทุกคน
    void displayAll() {
        cout << "\n========== SCOREBOARD ==========" << endl;
        cout << left << setw(15) << "Name" 
             << setw(12) << "Best Time" 
             << setw(15) << "High Score" 
             << setw(15) << "High Streak" << endl;
        cout << "======================================" << endl;
        
        for (auto& pair : players) {
            User& p = pair.second;
            cout << left << setw(15) << p.name 
                 << setw(12) << fixed << setprecision(2) << p.bestTime 
                 << setw(15) << p.highestScore 
                 << setw(15) << p.highestStreak << endl;
        }
        cout << "======================================\n" << endl;
    }
    
    void displayScores(int n = 5) {
        cout << "\n===== TOP " << n << " HIGH SCORES =====" << endl;
        
        // ดึงจาก Vector มาเรียง
        vector<User> sortedPlayers;
        for (auto& pair : players) {
            sortedPlayers.push_back(pair.second);
        }
        
        // เรียงคะแนนสูงไปต่ำ
        sort(sortedPlayers.begin(), sortedPlayers.end(), 
             [](const User& a, const User& b) {
                 return a.highestScore > b.highestScore;
             });
        
        // Display top N
        int count = min(n, (int)sortedPlayers.size());
        for (int i = 0; i < count; i++) {
            cout << i+1 << ". " << sortedPlayers[i].name 
                 << " - " << sortedPlayers[i].highestScore << " pts" << endl;
        }
        cout << "============================\n" << endl;
    }
    
    // ดึงข้อมูลของ Player
    User* getPlayer(string name) {
        if (players.find(name) != players.end()) {
            return &players[name];
        }
        return nullptr;
    }
    
    // เช็คถ้าเกิดไม่มี Player ชื่อนั้นๆ
    bool playerExists(string name) {
        return players.find(name) != players.end();
    }
};
int main() {

Scoreboard board;
    
    // Play the game
    StreakTrack(true);
    StreakTrack(true);
    StreakTrack(true);
    StreakTrack(false);
    
    // After game ends, save to scoreboard
    board.addOrUpdatePlayer("Kyle", 45.5, getTolScore(), getMaxStreak());
    
    board.displayAll();
}

