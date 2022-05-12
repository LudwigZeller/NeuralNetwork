#include <iostream>
#include <array>
#include <ctime>
#include <thread>
#include "Network/Node.hpp"
#include "Network/Layer.hpp"
#include "Network/Network.hpp"

int main() {
    srand(time(nullptr) % 123 + 321);
    using namespace std;
    using namespace std::literals::chrono_literals;

    std::vector<std::vector<int>> dataset{
            {0,   0,   0},
            {0,   0,   0},
            {0,   100, 100},
            {0,   100, 100},
            {100, 0,   100},
            {100, 0,   100},
            {100, 100, 0},
            {100, 100, 0},
            {50,  50,  0},
            {25,  25,  0},
            {75,  75,  0}
    };
    Network network{2, 8, 2, 1};
    network.activate_async_status();
    network.train(2.0f, dataset);
    int data[2];
    cout << "Test Mode - Enter '-1' to quit" << endl;
    while (true) {
        cout << "Input 1:" << flush;
        cin >> data[0];
//        data[0] *= 100;
        if (data[0] == -1) break;
        cout << "Input 2:" << flush;
        cin >> data[1];
//        data[1] *= 100;
        if (data[1] == -1) break;
        network.set_input_layer(data);
        cout << "Output:";
        for (auto elem: network.get_output_layer())
            cout << elem << " ";
        cout << endl;
    }
    return 0;
}
