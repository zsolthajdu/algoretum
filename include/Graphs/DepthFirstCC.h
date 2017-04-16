#ifndef _DEPTH_FIRST_CC
#define _DEPTH_FIRST_CC

#include <vector>
#include <iostream>
#include <map>

#include "Graphs/Graph.h"

namespace algoretum {

/**
 * Connected component finder class template, based on
 * depth-first search algorithm.
 *
 */
template< typename T>
class DepthFirstCC {

    std::map< T, bool>  _discovered;  // Has dfs run to this vertex ?

    std::map< T, int >	_id;		// id[v] = id of connected component containing v
    std::vector< size_t> _size;		// size[id] = number of vertices in given component
	size_t		        _count;		// number of connected components

    void dfs( Graph<T> & g,const  T & v )
	{
        _discovered[v] = true;
		_id[v] = _count;
		_size[_count]++;
		for( auto & w : g.getAdjList( v ) ) {
            if( !_discovered[ w ] )
				dfs( g, w );
		}
	}

public:
	
    // Number of connected components in the graph
	size_t getCount()  { return _count; }

    // Are the two parameters connected ?
    bool connected( T & a, T & b )
    {
        return _id[a] == _id[b];
    }

    // Return component ID of vertex identified by parameter.
    int id( const T& a )
    {
        return _id[a];
    }

    DepthFirstCC( Graph<T> & graph ) :// _discovered( g.getVertCount(),false ),_id(g.getVertCount()),
        _size(graph.getVertCount(), 0 ), _count(0)
	{
        for( const T* node = graph.begin(); nullptr != node ; node=graph.next() ) {
            auto it = _discovered.find( *node );
            if( it == _discovered.end() || it->second == false ) {
                dfs( graph, *node);
				_count++;
			}
		}
	}

};

}

#endif

