#include <iostream>
#include <array>
#include <time.h>
#include "Network/Node.hpp"
#include "Network/Layer.hpp"
#include "Network/Network.hpp"

int main() {
    srand(time(nullptr) % 123 + 321);
    using namespace std;


    int data[] = {
            0, 0, 0,
            0, 1, 0,
            1, 0, 0,
            1, 1, 0
    };

    Network::Dataset<2, 1, 4> dataset{
            0, 0, 0,
            0, 100, 0,
            100, 0, 0,
            100, 100, 0
    };


    int activation[2] = {50, 0};
    Network network{2, 8, 2, 1};
    network.set_input_layer(activation);
    network.train(20, data);
    int *a = network.get_output_layer();
    cout << a[0] << endl;

//    Node input_0;
//    Node input_1;
//    Layer layer_0{8};
//    layer_0.connect_layer_to_node(input_0);
//    layer_0.connect_layer_to_node(input_1);
//    Layer layer_1{8};
//    layer_1.connect(layer_0);
//    Node output;
//    layer_1.connect_node_to_layer(output);
//
//    input_0.set_activation(50);
//    input_1.set_activation(50);
//
//    for (int i = 0; i < layer_0.get_size(); ++i) {
//        layer_0.mutate(i);
//    }
//    for (int i = 0; i < layer_1.get_size(); ++i) {
//        layer_1.mutate(i);
//    }
//    output.set_bias(0);
//    for (int i = 0; i < output.get_connections(); ++i) {
//        output.set_weight(i, 1 / (float) output.get_connections());
//    }
//
//    int old = output.get_activation();
//    int mutations = 0;
//    int difference_old = 0;
//    int difference = 0;
//    int value = 50;
//    while (old != value) {
//        mutations++;
//        difference_old = old - value;
//        for (int i = 0; i < layer_0.get_size(); ++i) {
//            layer_0.mutate(i);
//            difference = output.get_activation() - value;
//            if (difference_old < difference)
//                layer_0.rollback(i);
//        }
//        for (int i = 0; i < layer_1.get_size(); ++i) {
//            layer_1.mutate(i);
//            difference = output.get_activation() - value;
//            if (difference_old < difference)
//                layer_1.rollback(i);
//        }
//        output.mutate();
//        difference = output.get_activation() - value;
//        if (difference_old < difference)
//            output.rollback();
//
//        old = output.get_activation();
//        cout << old << endl;
//    }
//    cout << "---------------------------\n" << "Mutations: " << mutations << "\n---------------------------\n" << endl;
//    while (true) {
//        cout << "Input 1:";
//        int temp = 0;
//        cin >> temp;
//        if (temp == -1) break;
//        input_0.set_activation(temp);
//        cout << "Input 2:";
//        temp = 0;
//        cin >> temp;
//        if (temp == -1) break;
//        input_1.set_activation(temp);
//        cout << (int) output.get_activation() << endl;
//    }
    return 0;
}
