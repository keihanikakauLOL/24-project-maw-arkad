#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

atomic<int> timeLeft(10);
atomic<int> timemin(0);
atomic<bool> running(true);
atomic<int> score(0);
atomic<int> streak(1);
atomic<bool> answeredCorrect(false);
atomic<int> difficulty(1);
atomic<int> scoremax(0);
atomic<bool> runaway(true);
atomic<bool> restart(false);
atomic<bool> timeout(true);

void timer_mode_normal() {

    while (runaway) {

        while (running && timeLeft > 0) {

            cout << "\rTime Left: " << timeLeft << " sec" << flush;
            this_thread::sleep_for(chrono::seconds(1));

            timeLeft--;
        }

        if (timeout) {
            cout << "\nTime's up!\n";
            timeout = false;
            running = false;
            streak = 0;
        }

        this_thread::sleep_for(chrono::milliseconds(50));
    }
}


void point_mode_normal() {

    while (runaway) {

        if (running && answeredCorrect.load()) {

            int addScore = 10 * difficulty.load() * streak.load();
            score += addScore;

            if (score.load() > scoremax.load()) {
                scoremax.store(score.load());
            }

            answeredCorrect = false;
            streak++;

            cout << "\nScore: " << score << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(50));
    }
}


void game_start() {

    while (runaway) {

        if (restart.load()) {

            score = 0;
            timeLeft = 10;
            streak = 1;
            running = true;

            restart = false;

            cout << "\nGame Restarted!\n";
        }

        this_thread::sleep_for(chrono::milliseconds(50));
    }
}


int main() {

    thread t1(timer_mode_normal);
    thread t2(point_mode_normal);
    thread t3(game_start);

    string cmd;

    while (true) {

        cin >> cmd;

        if (cmd == "correct") {
            answeredCorrect = true;
        }
        else if (cmd == "restart") {
            restart = true;
        }
        else if (cmd == "quit") {
            runaway = false;
            running = false;
            break;
        }
    }

    t1.join();
    t2.join();
    t3.join();

    cout << "\nFinal Score: " << score << endl;

    return 0;
}