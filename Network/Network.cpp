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
    delete m_async_status_thread;
}

void Network::connect() {
    for (int i = 1; i < m_layers; ++i) {
        m_layer->at(i)->connect(*m_layer->at(i - 1));
    }
}

void Network::async_status() {
    std::cout << "Started separate status thread" << std::endl;
    std::string input;
    while (!m_training_data.s_finished) {
        std::getline(std::cin, input);
        std::chrono::duration<float> duration = std::chrono::system_clock::now() - m_training_data.s_start;
        if (input == "exit" || input == "e") {
            std::cout << "Exited through user input" << std::endl;
            exit(1);
        } else if (input == "status" || input == "s") {
            std::cout << "-----------------------------------"
                      << "\nNetwork:\t\t" << m_layer->at(0)->get_size();
            for (int i = 1; i < m_layers; ++i)
                std::cout << "-" << m_layer->at(i)->get_size();
            std::cout << "\nMutations:\t\t" << m_training_data.s_mutations
                      << "\nGain-Mutations:\t\t" << m_training_data.s_gains
                      << "\nNo-Change-Mutations:\t" << m_training_data.s_wasted
                      << "\nUNDOs:\t\t\t" << m_training_data.s_undo
                      << "\nFitness:\t\t" << ((float) ((int) ((100 - m_training_data.s_avg) * 100)) / 100.0f) << "%"
                      << "\nAverage Difference: \t" << m_training_data.s_avg
                      << "\nTraining Time:\t\t" << (float) (int) (duration.count() * 100) / 100.0f << "s"
                      << "\n-----------------------------------" << std::endl;
        } else {
            if (!input.empty())
                std::cout << "Unknown instruction: " << input << std::endl;
        }
    }
}

float Network::get_difference(const std::vector<std::vector<int>> &dataset) {
    auto active_set = new int[m_input_nodes];
    std::vector<int> output{};
    int sum = 0;
    for (auto &data: dataset) {
        for (int i = 0; i < m_input_nodes; ++i) {
            active_set[i] = data.at(i);
        }
        set_input_layer(active_set);
        output = get_output_layer();
        for (int i = 0; i < output.size(); ++i) {
            sum += abs(output.at(i) - data.at(m_input_nodes + i));
        }
    }
    return (float) sum / (float) (m_output_nodes * dataset.size());
}

void Network::activate_async_status() {
    if (m_async_status_thread != nullptr) return;
    m_async_status_thread = new std::thread(&Network::async_status, this);
}

void Network::set_input_layer(int *values) {
    for (int i = 0; i < m_input_nodes; ++i) {
        m_layer->at(0)->get_node(i).set_activation(values[i]);
    }
}

std::vector<int> Network::get_input_layer() const {
    std::vector<int> layer;
    for (int i = 0; i < m_input_nodes; ++i) {
        layer.emplace_back(m_layer->at(0)->get_node(i).get_activation());
    }
    return layer;
}

std::vector<int> Network::get_output_layer() const {
    std::vector<int> layer;
    for (int i = 0; i < m_output_nodes; ++i) {
        layer.emplace_back(m_layer->at(m_layer->size() - 1)->get_node(i).get_activation());
    }
    return layer;
}

void Network::train(bool (*fitness_function)(int *)) {
    // Work in progress
}

void Network::train(float tolerance, const std::vector<std::vector<int>> &dataset) {
    m_training_data.s_finished = false;
    int mutations_per_cycle = 10;
    float difference = 100.0f;
    float difference_old = 100.0f;
    std::vector<std::vector<int>> mutations;
    int mutation_layer;
    int mutation_node;
    m_training_data.s_start = std::chrono::system_clock::now();
    while (difference > tolerance) {
        for (int i = 0; i < mutations_per_cycle; ++i) {
            mutation_layer = 1 + (int) rand() % (m_layers - 1); // So the input layer doesn't mutate
            mutation_node = rand() % m_layer->at(mutation_layer)->get_size();
            m_layer->at(mutation_layer)->mutate(mutation_node);
            mutations.emplace_back(std::vector<int>{mutation_layer, mutation_node});
        }


        difference = get_difference(dataset);
        if (difference_old == difference)
            m_training_data.s_wasted++;
        else if (difference_old < difference) {
            for (auto &item: mutations) {
                m_layer->at(item[0])->rollback(item[1]);
            }
            m_training_data.s_undo++;
        } else {
            if (difference <= 1.0f) mutations_per_cycle = 1;
            else if (difference <= 5.0f) mutations_per_cycle = 3;
            else if (difference <= 15.0f) mutations_per_cycle = 6;

            difference_old = difference;
            m_training_data.s_avg = difference;
            m_training_data.s_gains++;
        }
        m_training_data.s_mutations++;
    }
    auto stop = std::chrono::system_clock::now();
    std::chrono::duration<float> duration = stop - m_training_data.s_start;
    m_training_data.s_finished = true;
    std::cout << "Finished Training in " << (float) (int) (duration.count() * 100) / 100.0f << "s" << std::endl;
    if (m_async_status_thread != nullptr) {
        std::cout << "Please press enter to stop the status thread and continue the program"
                  << std::endl;
        m_async_status_thread->join();
    }
}
