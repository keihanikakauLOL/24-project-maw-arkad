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

void createList (int target = 24) {
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

string getfile() {
    static vector<int> index;
    static size_t current = 0;
    static bool is_loaded = false;

    const string list = "list.txt";
    const string num = "num.txt";

    // 2. โหลด Index เข้า Vector (ทำแค่ครั้งแรกที่เรียกฟังก์ชัน)
    if (!is_loaded) {
        ifstream idxFile(list);
        string val;
        while (getline(idxFile, val)) {
            index.push_back(stoi(val));
        }
        is_loaded = true;
    }


    // 4. อ่านไฟล์ข้อมูลตาม Index ปัจจุบัน
    ifstream file(num);
    string line;
    int target = index[current];
    int line_num = 0;
    bool found = false;
    string result;

    current++;
    
    while (getline(file, line)) {
        line_num++;
        if (line_num == target) {
            result = line;
            found = true;
            break;
        }
    }
    return result;
}

int main() {
    for (int i = 0; i < 217; i++) {
        cout << getfile() << endl;
    }
}