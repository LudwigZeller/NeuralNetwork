//
// Created by Ludwig Zeller on 06.05.2022.
//

#include "Network.hpp"

Network::Network(int hidden_layers, int nodes_per_layer, int input_nodes, int output_nodes) :
        m_input_nodes(input_nodes), m_output_nodes(output_nodes), m_layers(hidden_layers + 2) {
    // Generation
    m_layer = new std::vector<Layer *>;
    m_layer->emplace_back(new Layer{input_nodes});
    for (int i = 0; i < hidden_layers; ++i) {
        m_layer->emplace_back(new Layer{nodes_per_layer});
    }
    m_layer->emplace_back(new Layer{output_nodes});
    // Connection
    connect();

}

Network::Network(int hidden_layers, int *nodes_per_layer, int input_nodes, int output_nodes) :
        m_input_nodes(input_nodes), m_output_nodes(output_nodes), m_layers(input_nodes) {
    // Generation
    m_layer = new std::vector<Layer *>;
    m_layer->emplace_back(new Layer{input_nodes});
    for (int i = 0; i < hidden_layers; ++i) {
        m_layer->emplace_back(new Layer{nodes_per_layer[i]});
    }
    m_layer->emplace_back(new Layer{output_nodes});
    // Connection
    connect();
}

Network::~Network() {
    delete m_layer;
}

void Network::connect() {
    for (int i = 1; i < m_layers; ++i) {
        m_layer->at(i)->connect(*m_layer->at(i - 1));
    }
}

void Network::set_input_layer(int *values) {
    for (int i = 0; i < m_input_nodes; ++i) {
        m_layer->at(0)->get_node(i).set_activation(values[i]);
    }
}

int *Network::get_input_layer() const {
    int *layer = new int[m_input_nodes];
    for (int i = 0; i < m_input_nodes; ++i) {
        layer[i] = m_layer->at(0)->get_node(i).get_activation();
    }
    return layer;
}

int *Network::get_output_layer() const {
    int *layer = new int[m_input_nodes];
    for (int i = 0; i < m_input_nodes; ++i) {
        layer[i] = m_layer->at(m_layer->size() - 1)->get_node(i).get_activation();
    }
    return layer;
}
