#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>

using namespace std;

struct Node {
    string value;
    Node *left = nullptr;
    Node *right = nullptr;

    //Constructor
    Node(string v) {
        value = v;
    }

    //Cummulative Property
    string cummulative() {
        if(!left && !right) {
            return value;
        }

        string leftString = left->cummulative();
        string rightString = right->cummulative();

        //swap
        if(value == "+" || value == "*") {
            if (leftString > rightString) {
                swap(leftString, rightString);
            }
        }

        return "(" + leftString + value + rightString + ")";
    }
};