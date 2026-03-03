#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <string>
using namespace std;

class Game {
private:
    std::atomic<int> timeLeft{20};
    std::atomic<int> score{0};
    std::atomic<int> streak{1};
    std::atomic<bool> running{true};
    std::atomic<bool> runaway{true};
    std::atomic<bool> paused{false};
    std::atomic<bool> answeredCorrect{false};
    std::atomic<bool> timeout{false};
    std::atomic<bool> restartFlag{false};

    std::thread t1, t2, t3;

    inline void timer() {
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

    inline void pointSystem() {
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

    inline void endGame() {
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

    inline void resetGame() {
        timeLeft = 20;
        score = 0;
        streak = 1;
        paused = false;
        running = true;
        std::cout << "\nGame Restarted!\n";
    }

public:
    inline void pauseTimer() {
        if (!paused && running) {
            paused = true;
            std::cout << "\nPaused\n";
        }
    }

    inline void resumeTimer() {
        if (paused && running) {
            paused = false;
            std::cout << "\nResumed\n";
        }
    }

    inline void addPoint() {
        if (running)
            answeredCorrect = true;
    }

    inline void restart() {
        restartFlag = true;
    }

    inline void quit() {
        runaway = false;
        running = false;
    }

    inline void start() {

        std::cout << "Game Started!\n";
        std::cout << "Commands: correct | pause | resume | restart | quit\n";

        t1 = std::thread(&Game::timer, this);
        t2 = std::thread(&Game::pointSystem, this);
        t3 = std::thread(&Game::endGame, this);

        std::string cmd;

        while (runaway) {

            std::cin >> cmd;

            if (cmd == "correct") addPoint();
            else if (cmd == "pause") pauseTimer();
            else if (cmd == "resume") resumeTimer();
            else if (cmd == "restart") restart();
            else if (cmd == "quit") quit();
        }

        t1.join();
        t2.join();
        t3.join();

        std::cout << "\nFinal Score: " << score << "\n";
    }
};

#endif