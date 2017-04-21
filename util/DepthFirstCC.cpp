
#include <iostream>
#include <sstream>
#include <fstream>
//#include <memory>
#include <vector>

#include "Graphs/DepthFirstCC.h"
#include "Graphs/Graph.h"


using namespace std;
using namespace algoretum;


/**
 *  Function template to display connected components
 */
template< typename T >
void showComponents( ifstream & ifs )
{
    Graph<T>    graph( ifs );
    DepthFirstCC<T>  cc( graph );

    size_t  N = cc.getCount();
    cout << N << " connected component(s)." << endl;

    vector< vector<T> > components( N );
    // Sort vertices out into component groups
    for( const T* node = graph.begin(); nullptr != node ; node=graph.next() )
        components[ cc.id( *node ) ].push_back( *node );

    // Print components
    for( auto & comp : components ) {
        for( auto & n : comp )
            cout << n << ",";
         cout << endl;
    }

}

//
//  Command line arguments
//  - graph file name
//  - integer (-i) or string (-s) node descriptors
//
// For example:  DepthFirstCC USCities.txt -s
//
int main( int argc, char **argv )
{
    if( argc == 3 && (argv[2][1] == 's' || argv[2][1] == 'i' )) {
        ifstream ifs;

        ifs.open( argv[1]);
        if( ifs.good() ) {

            // Instantiate the template with a type
            if( argv[2][1] == 'i' )
                showComponents< int >( ifs );
            else  // .. otherwise assume string
                showComponents< string >( ifs );
        }
    }
    else
        cerr << "Invalid arguments !!\n";

    return 0;
}


