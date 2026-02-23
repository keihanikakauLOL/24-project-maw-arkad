#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

const double verysmall = 1e-9;

bool Check(double problem[], string expression[], int n) {
    if(n == 1) {
        if (abs(problem[0] - 24) < verysmall) {
            cout << "Solution: " << expression[0] << " = 24" << endl;
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
            if (Check(NumStorage, ExprsStorage, count + 1)) {
                return true;
            }

            // -

            NumStorage[count] = a - b;
            ExprsStorage[count] = "(" + ea + "-" + eb + ")";
            if (Check(NumStorage, ExprsStorage, count + 1)) {
                return true;
            }

            // *

            NumStorage[count] = a * b;
            ExprsStorage[count] = "(" + ea + "*" + eb + ")";
            if (Check(NumStorage, ExprsStorage, count + 1)) {
                return true;
            }

            // /

            //เช็กกับ verysmall ดีกว่า abs(b) != 0
            if(abs(b) > verysmall) {
                NumStorage[count] = a / b;
                ExprsStorage[count] = "(" + ea + "/" + eb + ")";
                if (Check(NumStorage, ExprsStorage, count + 1)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Solve24game(double problem[]) {
    string exprs[4];

    sort(problem, problem + 4);

    do {

        for(int i = 0; i < 4; i++) {
        // Convert initial numbers to strings
        exprs[i] = to_string((int)problem[i]);
    }

        if(Check(problem, exprs, 4)) {
            return true;
        }
    } while(next_permutation(problem, problem + 4));
    
    return false;
}

int main() {
    //test case
    double arr1[4] = {1,2,3,4};

    if (!Solve24game(arr1)) {
        cout << "This problem is not solvable" << endl;
    }
}