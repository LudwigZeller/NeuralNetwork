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
    std::vector<Node *> *m_nodes;

public:
    /**
     * Constructs a layer of nodes
     * @param nodes The amount of nodes inside the layer
     */
    explicit Layer(int nodes);

    ~Layer();

    /**
     * Connects the layer with a previous Layer
     * @param previous_layer The layer to connect to
     */
    void connect(const Layer &previous_layer);

    /**
     * Connects the layer to a single node
     * @param node The node to connect to: Node &
     * @warning Only used to connect to input nodes
     */
    void connect_layer_to_node(Node &node);

    /**
     * Connects a node to the layer
     * @param node The node the layer gets connected to: Node &
     * @warning Only used to connect a output node to the layer
     */
    void connect_node_to_layer(Node &node);

    /**
     * Gets the reference of a node
     * @param node The index of the node: int
     * @return A reference to the node: Node &
     */
    Node &get_node(int node);

    /**
     * Gets the number of nodes in the layer
     * @return The number of nodes
     */
    [[nodiscard]] unsigned int get_size() const;

    /**
     * Mutates a specific node
     * @param node The node to mutate
     */
    void mutate(int node);

    /**
     * Rolls the given Node back to the state of the last mutation
     * @param node The nude to rollback
     */
    void rollback(int node);
};


#endif //NODENETWORK_LAYER_HPP
