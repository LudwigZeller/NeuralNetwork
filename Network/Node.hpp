//
// Created by Ludwig Zeller on 03.05.2022.
//
#pragma once
#ifndef NODENETWORK_NODE_HPP
#define NODENETWORK_NODE_HPP

#include <vector>
#include <cstdint>
#include <cmath>
#include <iostream>

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
    struct LastMutation {
        float s_weight = 0;
        int s_index = -1; // -1 = Undefined; -2 = Bias Mutation
        int s_bias = 0;
    } m_last_mutation;
    int m_connections;
    std::vector<Connection> *m_previous_nodes;
    int m_bias;
    uint8_t m_activation;

public:
    /**
     * Constructs the shell of a node
     */
    Node();

    ~Node();

    /**
     * Connects this node with the node supplied
     * @param node Reference to the node: Node &
     * @param weight A weight associated with the connection: float
     */
    void connect(Node &node, float weight);

    /**
     * Gets the number of connections
     * @return The number of connections: unsigned int
     */
    [[nodiscard]] unsigned int get_connections() const;

    /**
     * Sets the bias of the node: int
     * @param bias The new bias value: int
     */
    void set_bias(int bias);

    /**
     * Returns the bias of the node
     * @return Bias of the node: int
     */
    [[nodiscard]] int get_bias() const;

    /**
     * Sets the weight of a single connection
     * @param node The index of the node: int
     * @param weight The new weight: float
     */
    void set_weight(int node, float weight);


    /**
     * Returns the wight of given node
     * @param node The index of the node: int
     * @return The weight of the node: float
     */
    [[nodiscard]] float get_weight(int node) const;


    /**
     * Sets the activation of the node
     * @param activation The activation value: uint8_t
     * @warning Only use with input nodes
     */
    void set_activation(uint8_t activation);


    /**
     * Calculates the activation of a single node
     * @return The activation of the node: int
     */
    uint8_t get_activation();

    /**
     * Randomizes all connection and the bias, thus mutating the node
     */
    void mutate();

    /**
     * Rolls the node back to the state before the last mutation
     */
    void rollback();

    /**
     * A helper function to keep the activation in a 0 to 100 range
     * @param t
     * @return A value in range 0 to 100: int
     */
    static int sigmoid(int node);

};


#endif //NODENETWORK_NODE_HPP
