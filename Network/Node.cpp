//
// Created by Ludwig Zeller on 03.05.2022.
//

#include "Node.hpp"


Node::Node() : m_activation(0.0f), m_connections(0), m_bias(0) {
    m_previous_nodes = new std::vector<Connection>;
}

Node::~Node() {
    delete m_previous_nodes;
}


void Node::connect(Node &node, float weight) {
    m_connections++;
    m_previous_nodes->emplace_back(Connection{&node, weight});
}

unsigned int Node::get_connections() const {
    return m_previous_nodes->size();
}


void Node::set_bias(int bias) {
    m_bias = bias;
}


int Node::get_bias() const {
    return m_bias;
}


void Node::set_weight(int node, float weight) {
    m_previous_nodes->at(node).s_weight = weight;
}


float Node::get_weight(int node) const {
    return m_previous_nodes->at(node).s_weight;
}


void Node::set_activation(uint8_t activation) {
    m_activation = activation;
}


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


void Node::mutate() {
    if (!(rand() % (m_connections + 1))) {
        m_last_mutation.s_bias = m_bias;
        m_last_mutation.s_index = -2;
        set_bias(m_bias + (rand() % 50 - 25));
        return;
    }
    // Backup
    m_last_mutation.s_index = rand() % m_connections;
    m_last_mutation.s_weight = m_previous_nodes->at(m_last_mutation.s_index).s_weight;
    float new_weight = ((float) (rand() % 100) / 100.0f) * (float) (rand() % 2 ? -1 : 1);
    set_weight(m_last_mutation.s_index, m_last_mutation.s_weight + new_weight);
}


void Node::rollback() {
    if (m_last_mutation.s_index == -1) return;
    if (m_last_mutation.s_index == -2) {
        set_bias(m_last_mutation.s_bias);
        return;
    }
    set_weight(m_last_mutation.s_index, m_last_mutation.s_weight);
}


int Node::sigmoid(int t) {
    return (int8_t) (100.0f / (1 + (float) pow(2.7182818283, -(float) t / 100.0f)));
}
