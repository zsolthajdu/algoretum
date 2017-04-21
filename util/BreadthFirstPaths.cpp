
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include "Graphs/BreadthFirstPaths.h"
#include "Graphs/Graph.h"

using namespace std;
using namespace algoretum;

bool useInt( char **argv )
{
    return argv[3][1] == 'i';
}

template< typename T >
void showPaths( ifstream & ifs, T & startNode )
{
    Graph<T>    graph( ifs );

    BreadthFirstPaths<T>  bfs( graph, startNode );

    // Print path from start vertex to each other one
    for( const T* node = graph.begin(); nullptr != node ; node = graph.next() ) {
        if( startNode == *node )
            continue;
        if( bfs.hasPathTo( *node ) ) {
            cout << startNode << " to " << *node << " : ";
            vector<T> path;
            bfs.pathTo( *node, path );

            for( T & v : path ) {
                if( startNode != v )
                    cout << "-";
                cout << v;
            }

            cout << endl;
        }
    }
}

//
//  Command line arguments
//  1.) graph file name.
//  2.) start node. Should be a number if graph nodes are integers.
//                OR string if nodes are strings.
//  3.) graph type : (-i) or string (-s) node descriptors
//
// For example:  BreadthFirstPaths USCities.txt Boston -s
//
int main( int argc, char **argv )
{
    if( argc == 4 && (argv[3][1] == 's' || argv[3][1] == 'i' )) {
		ifstream ifs;

		ifs.open( argv[1]);
        if( !ifs.good() ) {
            cerr << "Invalid filename !!\n";
            return 1;
        }

        if( useInt(argv ) ) {
            int startNode;
            // Have to use integer node identifier, so simply convert argument to int
            stringstream ss( argv[2] );
            ss >> startNode;
            showPaths( ifs, startNode );
        }
        else {
            // Graph uses string node identifiers. In this case the start node has to be
            // specified as a string also.
            string  startNodeName( argv[2] );
            showPaths( ifs, startNodeName );
        }
	}
    else
        cerr << "Invalid arguments !!\n";

	return 0;
}


