

#ifndef _DEPTH_FIRST_PATHS
#define _DEPTH_FIRST_PATHS

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

#include "Graph.h"

namespace algoretum {

/**
 * Depth-first search based path finding implementation.
 *
 *
 */
template< typename T>
class DepthFirstPaths {

    std::map< T, bool>  _discovered;
    std::map< T, T>  _edgeTo;   // Last vertex on known path to this vertex
    T		_startNode;   // All paths will start at this node

    void dfs( Graph<T> & g, T & v )
	{
		_discovered[v] = true;
		for( auto & w : g.getAdjList( v ) ) {
			if( !_discovered[ w ] ) {
				_edgeTo[w] = v;
				dfs( g, w );
			}
		}
	}

public:

    bool hasPathTo( const T & v )
    {
        auto i = _discovered.find( v );

        return i==_discovered.end() ? false : _discovered[v];
    }

    bool pathTo( T v, std::vector<T> & outPath )
	{
		if( !hasPathTo( v ) )
			return false;

        for( T i=v ; i!=_startNode ; i = _edgeTo[i] )
			outPath.push_back(i);
        outPath.push_back( _startNode );
		std::reverse( outPath.begin(), outPath.end() );

		return true;
	}

    DepthFirstPaths( Graph<T> & g, T & start ) :  _startNode(start)
	{
		dfs( g,start );
	}

};

}

#endif

