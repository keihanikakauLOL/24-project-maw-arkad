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

bool Checksol(double problem[], string expression[], int n, int target) {
    if(n == 1) {
        if (abs(problem[0] - target) < verysmall) {
            cout << "Solution: " << expression[0] << " = " << target <<endl;
            return true;
        }
        else {
            return false;
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
            if (Checksol(NumStorage, ExprsStorage, count + 1, target)) {
                return true;
            }

            // -

            NumStorage[count] = a - b;
            ExprsStorage[count] = "(" + ea + "-" + eb + ")";
            if (Checksol(NumStorage, ExprsStorage, count + 1, target)) {
                return true;
            }

            // *

            NumStorage[count] = a * b;
            ExprsStorage[count] = "(" + ea + "*" + eb + ")";
            if (Checksol(NumStorage, ExprsStorage, count + 1, target)) {
                return true;
            }

            // /

            //เช็กกับ verysmall ดีกว่า abs(b) != 0
            if(abs(b) > verysmall) {
                NumStorage[count] = a / b;
                ExprsStorage[count] = "(" + ea + "/" + eb + ")";
                if (Checksol(NumStorage, ExprsStorage, count + 1, target)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Solvethegame(double problem[], int target) {
    string exprs[4];

    sort(problem, problem + 4);

    do {

        for(int i = 0; i < 4; i++) {
        // Convert initial numbers to strings
        exprs[i] = to_string((int)problem[i]);
    }

        if(Checksol(problem, exprs, 4, target)) {
            return true;
        }
    } while(next_permutation(problem, problem + 4));
    
    return false;
}

void createList (int target) {
    ifstream source;
    ofstream dest("list.txt");
    source.open("num.txt");
    string n;
    vector <int> shuff;
    int count = 0;
    while(getline(source, n)) {
        count++;
        vector<double> prob;
        for (int i = 0; i < 4 ; i++) {
            prob.push_back((double)(n[i] - '0'));
        }

        double* arr = prob.data();

        if (check(arr, 4, target)) {
            shuff.push_back(count);
        }
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(shuff.begin(), shuff.end(), g);

    for (int i = 0; i < shuff.size(); i++) {
        dest << shuff[i] << endl;
    }

    source.close();
    dest.close();
}


string getfile(string num, string list, int result = 24) {
    createList(result);
    ifstream l;
    l.open(list);
    string listString;
    vector<int> line;

    while (getline(l, listString)) {
        line.push_back(stoi(listString));
    }

    int target = line[rand() % line.size()];
    int count = 0;

    ifstream q;
    q.open(num);
    string numString;

    while (getline(q, numString)) {
        count++;
        if(count == target) {
            return numString;
        }
    }
    l.close();
    q.close();
    return "";
}

int main() {
    srand(time(0));
    cout << getfile("num.txt","list.txt",24);
}