#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <ctime>
#include <cstdlib>
#include <random>
#include <iterator>
using namespace std;

const double verysmall = 1e-9;
set<string> Allpossiblesolutions;
vector<int> list;
vector<int> shuff;
vector<string> combination;

bool check(double prob[], int n, int target) {
    if(n == 1) {
        return abs(prob[0] - target) < verysmall;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }

            double storage[4];
            int count = 0;

            for(int k = 0; k < n; k++) {
                if(k != i && k != j) {
                    storage[count] = prob[k];
                    count++;
                }
            }

            double a = prob[i];
            double b = prob[j];

            // +

            //count เป็น 2
            storage[count] = a + b;
            // count + 1 เพื่อให้เป็นเลข 3
            if (check(storage, count + 1, target)) {
                return true;
            }

            // -

            storage[count] = a - b;
            if (check(storage, count + 1, target)) {
                return true;
            }

            // *

            storage[count] = a * b;
            if (check(storage, count + 1, target)) {
                return true;
            }

            // /

            if(abs(b) != 0) {
                storage[count] = a / b;
                if (check(storage, count + 1, target)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool permutationforcheck (double prob[], int target) {
    sort(prob, prob + 4);

    do {
        if(check(prob, 4, target)) {
            return true;
        }
    } while(next_permutation(prob, prob + 4));
    return false;
}

void Checksol(double problem[], string expression[], int n, int target) {
    if(n == 1) {
        if (abs(problem[0] - target) < verysmall) {
            Allpossiblesolutions.insert(expression[0]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }

            double NumStorage[4];
            string ExprsStorage[4];
            int count = 0;

            for(int k = 0; k < n; k++) {
                if(k != i && k != j) {
                    NumStorage[count] = problem[k];
                    ExprsStorage[count] = expression[k];
                    count++;
                }
            }

            double a = problem[i];
            double b = problem[j];
            string ea = expression[i];
            string eb = expression[j];

            // +

            //count เป็น 2
            NumStorage[count] = a + b;
            ExprsStorage[count] = "(" + ea + "+" + eb + ")";
            // count + 1 เพื่อให้เป็นเลข 3
            Checksol(NumStorage, ExprsStorage, count + 1, target);

            // -
            NumStorage[count] = a - b;
            ExprsStorage[count] = "(" + ea + "-" + eb + ")";
            Checksol(NumStorage, ExprsStorage, count + 1, target);

            // *
            NumStorage[count] = a * b;
            ExprsStorage[count] = "(" + ea + "*" + eb + ")";
            Checksol(NumStorage, ExprsStorage, count + 1, target);

            // /
            //เช็กกับ verysmall ดีกว่า abs(b) != 0
            if(abs(b) > verysmall) {
                NumStorage[count] = a / b;
                ExprsStorage[count] = "(" + ea + "/" + eb + ")";
                Checksol(NumStorage, ExprsStorage, count + 1, target);
            }
        }
    }
}

void Solvethegame(double problem[], int target) {
    string exprs[4];

    sort(problem, problem + 4);

    do {

        for(int i = 0; i < 4; i++) {
        // Convert initial numbers to strings
        exprs[i] = to_string((int)problem[i]);
    }

        Checksol(problem, exprs, 4, target);

    } while(next_permutation(problem, problem + 4));

    for (const string& s : Allpossiblesolutions) {
        cout << s << endl;
    }
}

void createQuestions() {
    for (int a = 0; a <= 9; a++) {
        for (int b = a; b <= 9; b++) {
            for (int c = b; c <= 9; c++) {
                for (int d = c; d <= 9; d++) {
                    string temp = to_string(a) + to_string(b) + to_string(c) + to_string(d);
                    combination.push_back(temp);
                }
            }
        }
    }
}

void newCreateList(int target = 24) {
    double arr[4];
    for (int i = 0; i <= 714; i++) {
        for (int j = 0; j < 4; j++) {
            string temp = combination[i];
            arr[j] = (temp[j] - '0');
        }
        if (permutationforcheck(arr, target)) {
                shuff.push_back(i);
            }
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(shuff.begin(), shuff.end(), g);

}

string newGetfile() {
    static int count = -1;
    count++;
    return combination[shuff[count]];
}

void clearvector() {
    shuff.clear();
}

int closest (double problem[], int target) {
    if (target >= 100 || target <= 9) {
        return 9999;
    }
    else if (permutationforcheck(problem, target)) {
        return target;
    }
    else {
        const int temp = target;
        int up = 0;
        int low = 0;
        bool foundUp = false;
        bool foundLow = false;
        
        while (temp + up < 100) {
            up++;
            if (permutationforcheck(problem, temp + up)) {
                foundUp = true;
                break;
            }
        }
        while (temp - low > 0) {
            low++;
            if (permutationforcheck(problem, temp - low)) {
                foundLow = true;
                break;
            }
        }

        if (foundUp && foundLow) {
            if (up >= low) {
                return temp - low;
            }
            else {
                return temp + up;
            }
        }
        else if (foundUp) {
            return temp + up;
        }
        else if (foundLow) {
            return temp - low;
        }
        return 9999;
    }
}