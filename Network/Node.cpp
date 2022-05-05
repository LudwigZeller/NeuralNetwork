//
// Created by Ludwig Zeller on 03.05.2022.
//

#include "Node.hpp"

/**
 * Constructs the shell of a node
 */
Node::Node() : m_activation(0.0f), m_connections(0), m_bias(0) {
    m_previous_nodes = new std::vector<Connection>;
}

Node::~Node() {
    delete m_previous_nodes;
}

/**
 * Connects this node with the node supplied
 * @param node Reference to the node: Node &
 * @param weight A weight associated with the connection: float
 */
void Node::connect(Node &node, float weight) {
    m_connections++;
    m_previous_nodes->emplace_back(Connection{&node, weight});
}

/**
 * Sets the bias of the node: int
 * @param bias
 */
void Node::set_bias(int bias) {
    m_bias = bias;
}

/**
 * Returns the bias of the node
 * @return Bias of the node: int
 */
int Node::get_bias() const {
    return m_bias;
}

/**
 * Sets the weight of a single connection
 * @param node The index of the node: int
 * @param weight The new weight: float
 */
void Node::set_weight(int node, float weight) {
    m_previous_nodes->at(node).s_weight = weight;
}

/**
 * Returns the wight of given node
 * @param node The index of the node: int
 * @return The weight of the node: float
 */
float Node::get_weight(int node) {
    return m_previous_nodes->at(node).s_weight;
}

/**
 * @warning Only use with input nodes
 * Sets the activation of the node
 * @param activation
 */
void Node::set_activation(uint8_t activation) {
    m_activation = activation;
}

/**
 * Calculates the activation of a single node
 * @return The activation of the node: int
 */
uint8_t Node::get_activation() {
    if (m_connections == 0) return m_activation;
    int sum = 0;
    for (int i = 0; i < m_connections; ++i) {
        Connection &temp_connect = m_previous_nodes->at(i);
        sum += (int) ((float) temp_connect.s_node->get_activation() * temp_connect.s_weight);
    }
    m_activation = sigmoid(sum + m_bias);
    return m_activation;
}

/**
 * A helper function to keep the activation in a 0 to 100 range
 * @param t
 * @return A value in range 0 to 100: int
 */
int Node::sigmoid(int t) {
    return (int8_t) (100.0f / (1 + (float) pow(M_E, -(float) t / 100.0f)));
}

