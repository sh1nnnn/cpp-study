// CPP code to illustrate Queue in
// Standard Template Library (STL)
#include <iostream>
#include <queue>

// Print the queue
void showQueueElements(std::queue<int> queue) {
	std::queue<int> queueTemp = queue;
	while (!queueTemp.empty()) {
		std::cout << '\t' << queueTemp.front();
		queueTemp.pop();
	}
	std::cout << std::endl;
}

// Driver Code
int main() {
    int items[] = {10, 20, 30, 40, 50, 60};
    std::queue<int> queue;

    std::cout << "sizeof(items)/sizeof(int) : " << sizeof(items)/sizeof(int) << std::endl;

    for(int i = 0; i < sizeof(items)/sizeof(int); i++) {
        std::cout << "items[i] : " << items[i] << std::endl;
        queue.push(items[i]);
    }

    std::cout << "queue.size() : " << queue.size() << std::endl;
    std::cout << "queue.front() : " << queue.front() << std::endl;
    std::cout << "queue.back() : " << queue.back() << std::endl;

    queue.pop();
    std::cout << "queue.pop()" << std::endl;
    std::cout << "queue.front() : " << queue.front() << std::endl;
    std::cout << "queue.back() : " << queue.back() << std::endl;

    showQueueElements(queue);

    return 0;
}