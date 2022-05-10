//
// Created by Ludwig Zeller on 05.05.2022.
//

#include "Layer.hpp"


Layer::Layer(int nodes) {
    m_nodes = new std::vector<Node *>;
    for (int i = 0; i < nodes; ++i) {
        m_nodes->emplace_back(new Node{});
    }
}

Layer::~Layer() {
    for (auto & m_node : *m_nodes) {
        delete m_node;
    }
    delete m_nodes;
}


void Layer::connect(const Layer &previous_layer) {
    for (auto &previous_node: *previous_layer.m_nodes) {
        for (auto &m_node: *m_nodes) {
            m_node->connect(*previous_node, 1.0f/(float)previous_layer.get_size());
        }
    }
}


void Layer::connect_layer_to_node(Node &node) {
    for (auto &m_node: *m_nodes) {
        m_node->connect(node, 1.0f);
    }
}


void Layer::connect_node_to_layer(Node &node) {
    for (auto &m_node: *m_nodes) {
        node.connect(*m_node, 1.0f);
    }
}


Node &Layer::get_node(int node) {
    return *m_nodes->at(node);
}


unsigned int Layer::get_size() const {
    return m_nodes->size();
}


void Layer::mutate(int node) {
    m_nodes->at(node)->mutate();
}


void Layer::rollback(int node) {
    m_nodes->at(node)->rollback();
}
