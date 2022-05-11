//
// Created by Ludwig Zeller on 06.05.2022.
//
#pragma once
#ifndef NODENETWORK_NETWORK_HPP
#define NODENETWORK_NETWORK_HPP

#include "Layer.hpp"
#include "chrono"
#include <string>
#include <array>
#include <thread>
#include <iostream>

//template<int hidden_layers, int input_nodes, int output_nodes, int nodes_per_layer, std::vector<int> custom_nodes_per_layer = nullptr>
class Network {
private:
    int m_layers;
    int m_input_nodes;
    int m_output_nodes;
    std::vector<Layer *> *m_layer;

    std::thread *m_async_status_thread = nullptr;
    struct TrainingData {
        int s_mutations = 0;
        int s_wasted = 0;
        int s_undo = 0;
        int s_gains = 0;
        float s_avg = 100.0f;
        bool s_finished = false;
    } m_training_data;

    void connect();

    void async_status();

    float get_difference(const std::vector<std::vector<int>> &dataset);

public:
    /**
     * Generates a network from ground up
     * @param hidden_layers The number of hidden Layers
     * @param nodes_per_layer The number of Nodes per Layer
     * @param input_nodes The number of input Nodes
     * @param output_nodes The number of output Nodes
     */
    Network(int hidden_layers, int nodes_per_layer, int input_nodes, int output_nodes);

    /**
     * Generates a network from ground up with custom nodes per Layer
     * @param hidden_layers The amount of hidden Layers
     * @param nodes_per_layer The Array of amounts of Nodes per Layer
     * @param input_nodes The amount of input Nodes
     * @param output_nodes  The amount of output Nodes
     */
    Network(int hidden_layers, int *nodes_per_layer, int input_nodes, int output_nodes);

    ~Network();

    void activate_async_status();

    /**
     * Sets the input Layer of the network
     * @param values The array of values
     * @warning Does expect the right amount of values
     */
    void set_input_layer(int *values);

    /**
     * Gets the current values of the input Layer
     * @return The vector of values
     */
    [[nodiscard]] std::vector<int> get_input_layer() const;

    /**
     * Calculates the output of the network
     * @return The vector of output values
     */
    [[nodiscard]] std::vector<int> get_output_layer() const;


    void train(bool (*fitness_function)(int *));

    void train(float difference, const std::vector<std::vector<int>> &dataset, int mutations_per_cycle = 1);
    // TODO: Add save to json/csv
    // void safe_to_cvs(std::string path);
    // void safe_to_json(std::string path);
    // TODO: Add load from json/csv
    // void load_from_cvs(std::string path);
    // void load_from_json(std::string path);
};


#endif //NODENETWORK_NETWORK_HPP
