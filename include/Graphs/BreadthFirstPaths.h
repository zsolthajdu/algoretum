#ifndef BREADTHFIRSTPATHS_H
#define BREADTHFIRSTPATHS_H

#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <map>

#include "Graph.h"


namespace algoretum {

/**
 * @brief The BreadthFirstPaths class
 * Breadth-first search based path finding implementation.
 * Ideal to find shortest path between two selected nodes.
 *
 * Template parameter is the integer type that will be used to represent nodes.
 *
 * Description
 * https://en.wikipedia.org/wiki/Breadth-first_search
 *
 */

template< typename T>
class BreadthFirstPaths
{
    std::map< T, bool>  _discovered;
    std::map< T, T>  _edgeTo;   // Last vertex on known path to this vertex
    T		_startNode;   // All paths will start at this node

    void bfs( Graph<T> & G, T s )
	{
        std::queue< T > q;
		_discovered[s] = true;
		q.push( s );
		while( !q.empty() ) {
            T v = q.front();
			q.pop();
			for( auto & w : G.getAdjList( v ) ) {
				if( !_discovered[w] ) {
					_edgeTo[w] = v;
					_discovered[w] = true;
					q.push(w);
				}
			}
		}
	}

public:

    bool hasPathTo( const T & v )
    {
        auto i = _discovered.find( v );

        return i==_discovered.end() ? false : _discovered[v];
    }

    bool pathTo( const T& v, std::vector<T> & outPath )
    {
        if( !hasPathTo( v ) )
            return false;

        for( T i=v ; i!=_startNode ; i = _edgeTo[i] )
                outPath.push_back(i);
        outPath.push_back( _startNode );
        reverse( outPath.begin(), outPath.end() );

        return true;
    }

    BreadthFirstPaths( Graph<T> & g, T & start ) : _startNode(start)
    {
        bfs( g,start );
    }

};

}

#endif // BREADTHFIRSTPATHS_H
