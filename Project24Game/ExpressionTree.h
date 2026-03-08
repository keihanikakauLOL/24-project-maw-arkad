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

    //ดึงตัวประกอบทั้งหมดของเครื่องหมายเดียวกันออกมา
    void collect(string op, vector<string>& parts) {
        if (value == op) {
            if (left) {
                left->collect(op, parts);
            }

            if (right) {
                right->collect(op, parts);
            }
        } else {
            // ถ้าเป็นเครื่องหมายอื่น หรือเป็นตัวเลข ให้เรียก cummulative() ของตัวมันเอง
            parts.push_back(cummulative());
        }
    }

    string cummulative() {
        if (!left && !right) return value;

        // ถ้าเป็นเครื่องหมายที่สลับที่และจัดหมู่ได้ (+ หรือ *)
        if (value == "+" || value == "*") {
            vector<string> parts;
            collect(value, parts); // ยุบกิ่งเอามาใส่ vector
            sort(parts.begin(), parts.end()); // เรียงลำดับ

            string result = "(";
            for (size_t i = 0; i < parts.size(); i++) {
                result += parts[i];
                if (i < parts.size() - 1) result += value;
            }
            result += ")";
            return result;
        }

        // สำหรับ - และ / ให้ทำงานแบบเดิม (สลับที่ไม่ได้)
        return "(" + left->cummulative() + value + right->cummulative() + ")";
    }
};

void buildSubBinarytree(stack<Node*>& nodes, stack<char>& op) {
    Node* right = nodes.top();
    nodes.pop();

    Node* left = nodes.top();
    nodes.pop();

    char charOp = op.top();
    op.pop();

    //build a new sub tree
    Node* newNode = new Node(string(1, charOp));
    newNode->left = left;
    newNode->right = right;
    nodes.push(newNode);
}

Node* buildTree(string exp) {
    stack<Node*> nodes;
    stack<char> ops;

    for (int i = 0; i < exp.length(); i++) {
        //number
        if (isdigit(exp[i])) {
            string val = "";
            while (i < exp.length() && isdigit(exp[i])) {
                val += exp[i++];
            }
            nodes.push(new Node(val));
            i--; 
        } 
        else if (exp[i] == '(') {
            //starting point
            ops.push('(');
        } 
        else if (exp[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                buildSubBinarytree(nodes, ops);
            }
            if (!ops.empty()) ops.pop(); // เอา ( ออก
        } 
        else {
            //+, -, *, /
            ops.push(exp[i]);
        }
    }
    
    // กันเหนียว
    while (!ops.empty()) {
        buildSubBinarytree(nodes, ops);
    }
    
    return nodes.top();
}