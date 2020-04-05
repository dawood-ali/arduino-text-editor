#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "wdigraph.h"
#include "heap.h"
#include <utility>
#include <unordered_map>

using namespace std;

// for brevity
// typedef introduces a synonym (alias)
// for the type specified
typedef pair<int, long long> PIL;

// again, for brevity
// used to store a vertex v and its predecessor pair (u,d) on the search
// where u is the node prior to v on a path to v of cost d
// eg. PIPIL x;
// x.first is "v", x.second.first is "u" and x.second.second is "d" from this
typedef pair<int, PIL> PIPIL;

// NOTE: you are not required to use PIPIL in your solution if you would prefer
// to implement Dijkstra's algorithm differently, this is here simply because
// it was used in the lecture for the slower version of Dijkstra's algorithm.


/*
    Heap Implmenetion of the dijkstra's shortest path algorithim.
*/
void dijkstra(const WDigraph &graph, int startVertex, unordered_map<int, PIL>& tree) {

    //Creating a heap item that can be used to store temporary heaps
    HeapItem<pair<int,int>,long long> heap_item;

    //Creating the binary tree to run through
    BinaryHeap<pair<int,int>,long long> events;

    pair<int,int> node_local;
    node_local.first= startVertex;
    node_local.second=startVertex;

    events.insert(node_local,0);

    while( events.size() > 0) {
        heap_item= events.min();
        events.popMin();

        unordered_map<int,PIL>::iterator got= tree.find((heap_item.item).second);

        if(got==tree.end()) {

            PIL node_cost;
            node_cost.first= (heap_item.item).first;
            node_cost.second = heap_item.key;

            tree[(heap_item.item).second]=node_cost;

            for (unordered_set<int>::const_iterator yeet= graph.neighbours((heap_item.item).second);
                    yeet!= graph.endIterator((heap_item.item).second); yeet++) {

                node_local.first= (heap_item.item).second;
                node_local.second= *yeet;
                long long cost_new= heap_item.key + graph.getCost((heap_item.item).second,*yeet);

                events.insert(node_local,cost_new);
            }

         } 
    }

}
#endif
