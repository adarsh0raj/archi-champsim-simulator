/**
 * graph1.cpp -- Simple program that accesses data in a graph through PULL and PUSH execuution
 *               for P-OPT algorithm
 * 
 * NOTE: Increase the N_NODES value for more computations.
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
#include <parallel/algorithm>
#include <omp.h>
using namespace std;

/* =============================================================== */
#define N_NODES  (1 << 10)      /* The number of nodes in the tree */
/* =============================================================== */

// Make a class to represent graph
class Graph {
    public:

        int **adj_list;
        int n_nodes;
        int n_edges;

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

/* dummy functions used by pin */
void __attribute__((noinline)) __attribute__((optimize("O0"))) PIN_Start()
{
    //assert(false); //on successful replacement - this shouldnt be executed
    asm("");
}

void __attribute__((noinline)) __attribute__((optimize("O0"))) PIN_Stop()
{
    //assert(false);
    asm("");
}

void __attribute__((noinline)) __attribute__((optimize("O0"))) PIN_Init()
{
    //assert(false); //on successful replacement - this shouldnt be executed
    asm("");
}

void __attribute__((noinline)) __attribute__((optimize("O0"))) PIN_RegisterGraph(Graph& g, bool isPull)
{
    asm("");
}

int main() {
    Graph g(N_NODES, (int)(N_NODES*(N_NODES-1)/5));
    g.adj_list = new int*[N_NODES];

    for (int i = 0; i < N_NODES; i++) {
        g.adj_list[i] = new int[N_NODES];
        for (int j = 0; j < N_NODES; j++) {
            g.adj_list[i][j] = 0;
        }
    }

    PIN_Init();
    g.create_random_edges();

    int dstData[N_NODES] = {0};
    //random initialize dstdata with values
    for (int i = 0; i < N_NODES; i++) {
        dstData[i] = rand() % N_NODES;
    }
    
    int srcData[N_NODES] = {0};
    //random initialize srcdata with values
    for (int i = 0; i < N_NODES; i++) {
        srcData[i] = rand() % N_NODES;
    }

    PIN_Start();
    // Pull execution for the given graph kernel
    for (int i = 0; i < N_NODES; i++) {
        for (int j = 0; j < N_NODES; j++) {
            if(g.adj_list[j][i] == 1) {
                dstData[i] += srcData[j];
            }
        }
    }

    PIN_Stop();
    
    PIN_RegisterGraph(g, true);


    // Print the adjacency list
    // g.print_adj_list();

    // cout<<endl;
    // for(int i=0; i<N_NODES; i++) {
    //     cout << dstData[i] << endl;
    // }
    // for(int i=0; i<N_NODES; i++) {
    //     cout << srcData[i] << endl;
    // }

    return 0;
}
