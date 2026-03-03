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

    Node(string v) : value(v) {}
    ~Node() {
        delete left;
        delete right;
    }
};

class ExpressionProcess {
    public:
        set <string> Unique(const set <string>& input) {
            set <string> result;
            for (const string& expr : input) {
                result.insert(normalize(expr))
            }
        }
}