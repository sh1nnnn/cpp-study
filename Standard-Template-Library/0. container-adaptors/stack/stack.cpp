#include <iostream>
#include <stack>

int main() {
    int elements[] = {10, 20, 30, 40, 50};
	std::stack<int> stack;

    for(int i = 0; i < sizeof(elements) / sizeof(int); i++) {
        stack.push(elements[i]);
    }

    std::cout << "stack.top() : " << stack.top() << std::endl;
	
    std::cout << "stack.pop() Test" << std::endl;
	while (!stack.empty()) {
        std::cout << "pop()!! : " << stack.top() << std::endl;
		stack.pop();
	}
}
