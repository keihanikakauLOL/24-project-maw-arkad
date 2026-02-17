#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <string>
using namespace std;

atomic<int> timeLeft(10);
atomic<bool> running(true);
atomic<int> score(0);
atomic<int> streak(1);
atomic<bool> answeredCorrect(true);
atomic<int> difficulty(1);
atomic<bool> modetimer(true);
atomic<int> scoremax(0);

void timer_mode_normal() {
    while (running && timeLeft > 0) {

        cout << "\nTime Left: " << timeLeft << " sec" << flush;
        this_thread::sleep_for(chrono::seconds(1));

        timeLeft--;
    }

    if (timeLeft == 0) {
        cout << "\nTime's up!\n";
        running = false;
        streak = 0;
    }
}

void point_mode_normal(){
    while(answeredCorrect){
        score += 10*(difficulty/10)*(streak/10);
        if(score > scoremax){
            scoremax = score;
        }
    }
    if(!answeredCorrect){
        answeredCorrect = true;
        score -= 10*(difficulty/15)*(streak/11.0);
    }
}

int main() {
    if(modetimer){
    thread t1(timer_mode_normal);
    thread t2(point_mode_normal);
    if("ans == incorrect"){
        answeredCorrect = false;
    }
    //
        //code by arm


    //
    cout << "\nsss\n";
    t1.join();
    t2.join();
    }else{
    thread t2(point_mode_normal);
    if("ans == incorrect"){
        answeredCorrect = false;
    }


    t2.join();
    }

return 0;
}
