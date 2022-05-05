//
// Created by Ludwig Zeller on 05.05.2022.
//
#pragma once
#ifndef NODENETWORK_LAYER_HPP
#define NODENETWORK_LAYER_HPP

#include <vector>
#include "Node.hpp"

class Layer {
private:
    std::vector<Node> *m_nodes;

public:
    explicit Layer(int);

    ~Layer();

    void connect(const Layer &);

    void connect_layer_to_node(Node &);

    void connect_node_to_layer(Node &);

    Node &get_node(int);

    unsigned int get_size();

    void scramble();
};


#endif //NODENETWORK_LAYER_HPP
