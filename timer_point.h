#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <string>

class Game {
private:
    std::atomic<int> timeLeft{30};
    std::atomic<int> score{0};
    std::atomic<int> streak{1};
    std::atomic<bool> running{true};
    std::atomic<bool> runaway{true};
    std::atomic<bool> paused{false};
    std::atomic<bool> answeredCorrect{false};
    std::atomic<bool> timeout{false};
    std::atomic<bool> restartFlag{false};

    std::thread t1, t2, t3;

    void timer() {
        while (runaway) {

            if (running && !paused && timeLeft > 0) {

                std::cout << "\rTime Left: "
                          << timeLeft << " sec   " << std::flush;

                std::this_thread::sleep_for(std::chrono::seconds(1));
                timeLeft--;

                if (timeLeft == 0)
                    timeout = true;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void pointSystem() {
        while (runaway) {

            if (running && answeredCorrect) {
                score += 10 * streak;
                streak++;
                answeredCorrect = false;

                std::cout << "\nScore: " << score << "\n";
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void endGame() {
        while (runaway) {

            if (running && timeout) {
                std::cout << "\n\nTime's up!\n";
                running = false;
                timeout = false;
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
        streak = 1;
        paused = false;
        running = true;
        std::cout << "\nGame Restarted!\n";
    }

public:
    void start() {
        t1 = std::thread(&Game::timer, this);
        t2 = std::thread(&Game::pointSystem, this);
        t3 = std::thread(&Game::endGame, this);
    }

    void choice_func(const std::int& cmd) {

        if (cmd == 0) {
            addPoint();
            Chooseyourchoicemyfriend();
        }
        else if (cmd == 1) pauseTimer();
        else if (cmd == 2) resumeTimer();
        else if (cmd == 3) restart();
        else if (cmd == 4) quit();
    }

    int Chooseyourchoicemyfriend(){
        running = false;
        return streak.load();
        return score.load();
        return timeLeft.load();
        timeLeft = 0;
    }

    void pauseTimer() {
        if (!paused && running) {
            paused = true;
            std::cout << "\nPaused\n";
        }
    }

    void resumeTimer() {
        if (paused && running) {
            paused = false;
            std::cout << "\nResumed\n";
        }
    }

    void addPoint() {
        if (running)
            answeredCorrect = true;
    }

    void restart() {
        restartFlag = true;
    }

    void quit() {
        runaway = false;
        running = false;
    }

    void wait() {
        if (t1.joinable()) t1.join();
        if (t2.joinable()) t2.join();
        if (t3.joinable()) t3.join();

        std::cout << "\nFinal Score: " << score << "\n";
    }
};

#endif