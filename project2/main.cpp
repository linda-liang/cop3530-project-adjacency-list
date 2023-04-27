#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

vector<double> calculate_pagerank(const vector<vector<int>>& graph, int num_iterations) {
    int num_nodes = graph.size();

    // Initialize PageRank scores
    vector<double> pagerank_scores(num_nodes, 1.0 / num_nodes);
    vector<vector<int>> in_neighbors(num_nodes);
    // Create vector of incoming links for each node
    for (int node = 0; node < num_nodes; node++) {
        for (int neighbor : graph[node]) {
            in_neighbors[neighbor].push_back(node);
        }
    }

    // Perform iterations
    for (int iteration = 1; iteration < num_iterations; iteration++) {
        vector<double> new_pagerank_scores(num_nodes, 0);
        for (int node = 0; node < num_nodes; node++) {
            for (int in_neighbor : in_neighbors[node]) {
                if (graph[in_neighbor].size() > 0) {
                    new_pagerank_scores[node] += pagerank_scores[in_neighbor] / graph[in_neighbor].size();
                }
            }
        }
        pagerank_scores = new_pagerank_scores;
    }
    return pagerank_scores;
}


int main() {
    int num_lines, num_iterations;
    cin >> num_lines >> num_iterations;
    // Map to store integer ids for each website
    map<string, int> node_map;
    // Adjacency list to represent the graph
    vector<vector<int>> adj_list;

    // Build graph
    for (int i = 0; i < num_lines; i++) {
        string from, to;
        cin >> from >> to;

        // Assign unique integer id to each node
        if (node_map.count(from) == 0) {
            // Add empty vector for new node
            node_map[from] = node_map.size();
            adj_list.emplace_back();
        }
        if (node_map.count(to) == 0) {
            // Add empty vector for new node
            node_map[to] = node_map.size();
            adj_list.emplace_back();
        }

        // Add edge to graph
        int from_id = node_map[from], to_id = node_map[to];
        adj_list[from_id].push_back(to_id);
    }

    // Calculate PageRank scores
    vector<double> pagerank_scores = calculate_pagerank(adj_list, num_iterations);

    // Create an ordered map of website names and PageRank scores
    map<string, double> pagerank_map;
    for (auto mapping : node_map) {
        string website_name = mapping.first;
        int node_id = mapping.second;
        pagerank_map[website_name] = pagerank_scores[node_id];
    }
    // Print the map
    for (auto mapping : pagerank_map) {
        string website_name = mapping.first;
        double pagerank_score = mapping.second;
        cout << website_name << " " << fixed << setprecision(2) << pagerank_score << "\n";
    }


    return 0;
}
