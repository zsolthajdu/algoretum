#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>

namespace algoretum {

// Helper alias template
template<typename T>
using GraphAdjacencyStore = std::unordered_map< T, std::vector<T> >;

/**
 * @brief The Graph class
 * Base undirected, weightless graph iplementation, using adjacency lists to store
 * edge information between nodes.
 *
 * Template parameter is the type that represents a node. Usually int or string.
 *
 * Introduction:
 * http://algs4.cs.princeton.edu/41graph/
 */

template< typename T>
class Graph {

	int		_V;
	int		_E;

	// Adjacency lists for all vertices
	GraphAdjacencyStore<T>	_adj;

	 // To support iterating through nodes in the Graph
	typename GraphAdjacencyStore<T>::iterator _it;

	void addEdge( T v, T w )
	{
		_adj[v].push_back( w );
		_adj[w].push_back( v );
	}

public:

	size_t	getVertCount() { return _V; }
	size_t	getEdgeCount() { return _E; }

    std::vector<T> & getAdjList( T node ) { return _adj.at( node ); }

    // Caller can call begin() to start iterating through nodes.
    // Then call next() to proceed to other elements.
    const T * begin()
    {
        if( _adj.empty() )
            return nullptr;
        _it = _adj.begin();
        return & _it->first;
    }

    const T * next()
    {
        if( _it == _adj.end() )
            return nullptr;

        ++_it;
        return ( _it == _adj.end() ? nullptr :  &_it->first );
    }

	Graph( int v ) : _V(v+1), _E(0), _adj(v+1)
	{
		
	}

	Graph( std::ifstream &ifs )
	{
        // File has to start with node count and edge count
		ifs >> _V >> _E;

		for( int e=0 ; e<_E ; e++ ) {
			T v, w;
			ifs >> v >> w;
			addEdge( v, w );
		}
	}

};

}

#endif

