#include <iostream>
#include <array>
#include <time.h>
#include "Network//Node.hpp"
#include "Network/Layer.hpp"

int main() {
    srand(time(nullptr) % 123 + 321);
    using namespace std;

    int dataset[4][3] = {
            {0, 0, 0},
            {0, 1, 0},
            {1, 0, 0},
            {1, 1, 1}
    };

    Node input_0;
    Node input_1;
    Layer layer_0{8};
    layer_0.connect_layer_to_node(input_0);
    layer_0.connect_layer_to_node(input_1);
    Layer layer_1{8};
    layer_1.connect(layer_0);
    Node output;
    layer_1.connect_node_to_layer(output);

    input_0.set_activation(50);
    input_1.set_activation(50);

    for (int i = 0; i < layer_0.get_size(); ++i) {
        layer_0.mutate(i);
    }
    for (int i = 0; i < layer_1.get_size(); ++i) {
        layer_1.mutate(i);
    }
    output.mutate();
    for (int i = 0; i < output.get_connections(); ++i) {
        output.mutate();
    }

    int old = output.get_activation();
    int mutations = 0;
    while (old != 50) {
        mutations++;
        for (int i = 0; i < layer_0.get_size(); ++i) {
            layer_0.mutate(i);
//            if (old < output.get_activation()) layer_0.rollback(i);
        }
        for (int i = 0; i < layer_1.get_size(); ++i) {
            layer_1.mutate(i);
//            if (old < output.get_activation()) layer_1.rollback(i);
        }
        output.mutate();
//        if (old < output.get_activation()) output.rollback();

        old = output.get_activation();
        cout << old << endl;
    }
    cout << "---------------------------\n" << "Mutations: " << mutations << "\n---------------------------\n" << endl;
    while (true) {
        cout << "Input 1:";
        int temp = 0;
        cin >> temp;
        if(temp == -1) break;
        input_0.set_activation(temp);
        cout << "Input 2:";
        temp = 0;
        cin >> temp;
        if(temp == -1) break;
        input_1.set_activation(temp);
        cout << (int) output.get_activation() << endl;
    }
    return 0;
}
