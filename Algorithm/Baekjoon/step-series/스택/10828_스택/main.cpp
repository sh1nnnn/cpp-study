#include <iostream>
#include <stack>
#include <map>

using namespace std;

#define PUSH 1
#define POP 2
#define SIZE 3
#define EMPTY 4
#define TOP 5

int main() {
    int N;
    stack<int> stack;
    map<string, int> option;

    option["push"] = PUSH;
    option["pop"] = POP;
    option["size"] = SIZE;
    option["empty"] = EMPTY;
    option["top"] = TOP;

    cin >> N;
    for(int tc = 0; tc < N; ++tc) {
        string cmd;
        cin >> cmd;

        switch (option[cmd])
        {
        case PUSH:
            int element;
            cin >> element;
            stack.push(element);
            break;
        
        case POP:
            if(stack.empty())
            {
                cout << -1 << endl;
            }
            else
            {
                cout << stack.top() << endl;
                stack.pop();
            }
            break;

        case SIZE:
            cout << stack.size() << endl;
            break;

        case EMPTY:
            if(stack.empty())
            {
                cout << 1 << endl;
            }
            else
            {
                cout << 0 << endl;
            }
            break;

        case TOP:
            if(stack.empty())
            {
                cout << -1 << endl;
            }
            else
            {
                cout << stack.top() << endl;
            }
            break;

        default:
            break;
        }
    }
}
