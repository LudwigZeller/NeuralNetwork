//
// Created by Ludwig Zeller on 05.05.2022.
//

#include "Layer.hpp"

/**
 * Constructs a layer of nodes
 * @param nodes The amount of nodes inside the layer
 */
Layer::Layer(int nodes) {
    m_nodes = new std::vector<Node>;
    for (int i = 0; i < nodes; ++i) {
        m_nodes->emplace_back(Node{});
    }
}

Layer::~Layer() {
    delete m_nodes;
}

/**
 * Connects the layer with a previous Layer
 * @param previous_layer
 */
void Layer::connect(const Layer &previous_layer) {
    for (auto &previous_node: *previous_layer.m_nodes) {
        for (auto &m_node: *m_nodes) {
            m_node.connect(previous_node, 1.0f);
        }
    }
}

/**
 * @warning Only used to connect to input nodes
 * Connects the layer to a single node
 * @param node The node to connect to: Node &
 */
void Layer::connect_layer_to_node(Node &node) {
    for (auto &m_node: *m_nodes) {
        m_node.connect(node, 1.0f);
    }
}

/**
 * @warning Only used to connect a output node to the layer
 * Connects a node to the layer
 * @param node The node the layer gets connected to: Node &
 */
void Layer::connect_node_to_layer(Node &node) {
    for (auto &m_node: *m_nodes) {
        node.connect(m_node, 1.0f);
    }
}

/**
 * Gets the reference of a node
 * @param node The index of the node: int
 * @return A reference to the node: Node &
 */
Node &Layer::get_node(int node) {
    return m_nodes->at(node);
}

unsigned int Layer::get_size() {
    return m_nodes->size();
}

void Layer::scramble() {

}
