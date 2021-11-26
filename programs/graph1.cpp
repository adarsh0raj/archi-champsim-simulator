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

#include "graph.h"

using namespace std;

/* =============================================================== */
#define N_NODES  (1 << 10)      /* The number of nodes in the tree */
/* =============================================================== */

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
    g.is_pool = false;

    PIN_RegisterGraph(g, false);

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
    
    // Push execution for the given graph kernel
    for (int i = 0; i < N_NODES; i++) {
        for (int j = 0; j < N_NODES; j++) {
            if(g.adj_list[i][j] == 1) {
                srcData[i] += dstData[j];
            }
        }
    }

    PIN_Stop();

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
