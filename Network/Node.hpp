//
// Created by Ludwig Zeller on 03.05.2022.
//
#pragma once
#ifndef NODENETWORK_NODE_HPP
#define NODENETWORK_NODE_HPP

#include <vector>
#include <cstdint>
#include <cmath>

/**
 * A Class to represent a singe Node in a network
 * @property m_bias: A integer added to the sum of activation*weight of the previous nodes; int [-int; +int]
 * @property m_activation: A integer with represents the value of then node; uint8_t [0; 100]
 * @property s_weight: The weight attributed to a single connection float ]0; float]
 */
class Node {
private:
    struct Connection {
        Node *s_node = nullptr;
        float s_weight = 0.0f;
    };

    int m_connections;
    std::vector<Connection> *m_previous_nodes;
    int m_bias;
    uint8_t m_activation;
public:
    Node();

    ~Node();

    void connect(Node &, float);

    void set_bias(int);

    [[nodiscard]] int get_bias() const;

    void set_weight(int, float);

    [[nodiscard]] float get_weight(int);

    void set_activation(uint8_t);

    [[nodiscard("Requires large amounts of calculation")]] uint8_t get_activation();

    [[nodiscard]] static int sigmoid(int);
};


#endif //NODENETWORK_NODE_HPP
