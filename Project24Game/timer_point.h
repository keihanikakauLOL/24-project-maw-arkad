#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <string>
#include <map>
#include <iomanip>
#include <vector>
#include <algorithm>

struct User {
    std::string name;
    double bestTime;
    int highestScore;
    int highestStreak;
    
    User() : name(""), bestTime(0.0), highestScore(0), highestStreak(0) {}
    User(std::string n, double t, int score, int streak) 
        : name(n), bestTime(t), highestScore(score), highestStreak(streak) {}
};

class Scoreboard {
private:
    std::map<std::string, User> players;
    
public:
    void addOrUpdatePlayer(std::string name, double time, int score, int streak) {
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
            players[name] = User(name, time, score, streak);
        }
    }
    
    void displayAll() {
        std::cout << "\n========== SCOREBOARD ==========" << std::endl;
        std::cout << std::left << std::setw(15) << "Name" 
                  << std::setw(12) << "Best Time" 
                  << std::setw(15) << "High Score" 
                  << std::setw(15) << "High Streak" << std::endl;
        std::cout << "======================================" << std::endl;
        
        for (auto& pair : players) {
            User& p = pair.second;
            std::cout << std::left << std::setw(15) << p.name 
                      << std::setw(12) << std::fixed << std::setprecision(2) << p.bestTime 
                      << std::setw(15) << p.highestScore 
                      << std::setw(15) << p.highestStreak << std::endl;
        }
        std::cout << "======================================\n" << std::endl;
    }
    
    void displayScores(int n = 5) {
        std::cout << "\n===== TOP " << n << " HIGH SCORES =====" << std::endl;
        
        std::vector<User> sortedPlayers;
        for (auto& pair : players) {
            sortedPlayers.push_back(pair.second);
        }
        
        std::sort(sortedPlayers.begin(), sortedPlayers.end(), 
                  [](const User& a, const User& b) {
                      return a.highestScore > b.highestScore;
                  });
        
        int count = std::min(n, (int)sortedPlayers.size());
        for (int i = 0; i < count; i++) {
            std::cout << i+1 << ". " << sortedPlayers[i].name 
                      << " - " << sortedPlayers[i].highestScore << " pts" << std::endl;
        }
        std::cout << "============================\n" << std::endl;
    }
    
    User* getPlayer(std::string name) {
        if (players.find(name) != players.end()) {
            return &players[name];
        }
        return nullptr;
    }
    
    bool playerExists(std::string name) {
        return players.find(name) != players.end();
    }
};

class Game {
public:
    struct GameState {
        int score;
        int streak;
        int timeLeft;
    };
    
    void updateStreakAndScore(bool isCorrect) {
        if (!running) return;

        if (isCorrect) {
            streak++;
            if (streak >= streak_base) {
                if (streak > streakmax.load()) {
                    streakmax.store(streak.load());
                }
                received_score = base_score + (base_score * (streak / 4));
                std::cout << "\nCorrect! Streak: " << streak << std::endl;
                std::cout << "Score: +" << received_score << " | Total: " << score + received_score << std::endl;
            } else {
                received_score = base_score;
                std::cout << "\nCorrect!" << std::endl;
                std::cout << "Score: +" << received_score << " | Total: " << score + received_score << std::endl;
            }
            
            score += received_score;
            if (score.load() > scoremax.load()) {
                scoremax.store(score.load());
            }
            //
        } else {
            streak = 0;
            std::cout << "\nWrong! Streak reset." << std::endl;
            std::cout << "Total score: " << score << std::endl;
        }
    }

private:
    std::atomic<int> timeLeft{30};
    std::atomic<int> score{0};
    std::atomic<int> scoremax{0};
    std::atomic<int> streak{0};
    std::atomic<int> streakmax{0};
    std::atomic<bool> running{true};
    std::atomic<bool> runaway{true};
    std::atomic<bool> paused{false};
    std::atomic<bool> timeout{false};
    std::atomic<bool> restartFlag{false};

    std::atomic<int> received_score{0};

    const int base_score = 5;
    const int streak_base = 3;
    std::string playerName;  
    double maxTimeThisLevel{0.0};  
    std::thread t1, t3;

    void timer() {
        while (runaway) {
            if (running && !paused && timeLeft > 0) {
                std::cout << "\r[Time Left: " << timeLeft << "s] " << std::flush;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                timeLeft--;

                if (timeLeft <= 0) {
                    timeLeft = 0;
                    timerout();
                    timeout = true;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void endGame() {
        while (runaway) {
            if (running && timeout) {
                std::cout << "\n\n--- TIME'S UP! ---";
                std::cout << "\nFinal Score: " << score << "\n";
                running = false;
                timeout = false;
                streak = 0;
            }

            if (restartFlag) {
                resetGame();
                restartFlag = false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void resetGame() {
        timeLeft = 30;
        score = 0;
        streak = 0;
        paused = false;
        running = true;
        std::cout << "\n--- Game Restarted! ---\n";
    }

public:
    void start() {
        t1 = std::thread(&Game::timer, this);
        t3 = std::thread(&Game::endGame, this);
        paused = true;
    }

    void setPlayerName(std::string name) {
        playerName = name;
    }

    void updateQuestionTime(double timeTaken) {
        if (timeTaken > maxTimeThisLevel) {
            maxTimeThisLevel = timeTaken;
        }
    }

    User getUserData() const {
        return User(playerName, maxTimeThisLevel, scoremax.load(), streakmax.load());
    }

    GameState ChooseYourChoice() {
        paused = true;
        GameState state;
        state.score = score.load();
        state.streak = streak.load();
        state.timeLeft = timeLeft.load();
        return state;
    }

    GameState choice_func(int cmd) {
        if (cmd == 0) {
            addPoint(); 
            return ChooseYourChoice(); 
        }
        else if (cmd == 1) pauseTimer();
        else if (cmd == 2) resumeTimer();
        else if (cmd == 3) restart();
        else if (cmd == 4) quit();

        GameState current;
        current.score = score.load();
        current.streak = streak.load();
        current.timeLeft = timeLeft.load();
        return current;
    }

    int getTimeLeft() const {
        return timeLeft.load();
    }

    void pauseTimer() {
        if (!paused && running) {
            paused = true;
            std::cout << "\n[Game Paused]\n";
        }
    }

    void resumeTimer() {
        if (paused && running) {
            paused = false;
            std::cout << "\n[Game Resumed]\n";
        }
    }

    void addPoint() {
        if (running && !paused) {
            updateStreakAndScore(true);
        }
    }
    
    void wrongAnswer() {
        if (running && !paused) {
            updateStreakAndScore(false);
        }
    }

    void resettimer(){
        timeLeft = 30;
    }
    
    void restart() {
        restartFlag = true;
    }

    bool timerout(){
        return true;
    }

    void quit() {
        runaway = false;
        running = false;
    }

    void wait() {
        if (t1.joinable()) t1.join();
        if (t3.joinable()) t3.join();
    }
    
    bool isRunning() const {
        return running;
    }
};

#endif
