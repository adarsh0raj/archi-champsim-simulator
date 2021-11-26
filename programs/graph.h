#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Graph {
    public:

        int **adj_list;
        int n_nodes;
        int n_edges;
        bool is_pool;

        void init() {
            adj_list = new int*[n_nodes];
            for (int i = 0; i < n_nodes; i++) {
                adj_list[i] = new int[n_nodes];
                for (int j = 0; j < n_nodes; j++) {
                    adj_list[i][j] = 0;
                }
            }
        }

        Graph(int n, int e) {
            n_nodes = n;
            n_edges = e;
        }

        // Add an edge from u to v
        void add_edge(int u, int v) {
            adj_list[u][v] = 1;
        }

        // Print the adjacency list
        void print_adj_list() {
            for (int i = 0; i < n_nodes; i++) {
                for (int j = 0; j < n_nodes; j++) {
                    cout << adj_list[i][j] << " ";
                }
                cout << endl;
            }
        }

        // create randomly edges
        void create_random_edges() {
            for (int i = 0; i < n_edges; i++) {
                int u = rand() % n_nodes;
                int v = rand() % n_nodes;
                add_edge(u, v);
            }
        }
};