#ifndef PATH_H_
#define PATH_H_

#include <string>
#include <list>
#include <math.h>
#include <map>
#include <vector>
#include <iomanip>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/astar_search.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/random.hpp>
#include <boost/config.hpp>
#include "math/Vector.hpp"
#include "SharedArray.hpp"


using namespace boost;

namespace asteroids
{


class PathPlanner {
  public:

    //Define Graph
    typedef adjacency_list <listS, vecS, undirectedS, no_property, 
    property < edge_weight_t, float > > Graph;

    /**
     * @brief Initialzes tha pathfinder with a filename, which contains information about the graph
     * 
     * @param mapfile   A file containing the representation of an graph
     *                  used for navigatuib
     */
    PathPlanner (std::string mapfile);

    /**
     * @brief Calculates a shortest path with the A*-Algorithm
     * 
     * @param position Startposition of the ship
     * @param s Start of the path
     * @param e End of the path
     * 
     * @return A shortest path from s to e
     */

    std::list<Vector3f> getPath(Vector3f position, std::string s, std::string e);

    /**
     * @brief Prints the file content to stdout
     * 
     */
    void print();

  private:

    //The graph
    Graph g;

    //Number of Planets
    int m_numofindices;

    //Store tupel for faces
    std::vector<Vector2i> m_edges;

    //store vertex
    std::vector<Vector3f> m_nodes;

    //Map to match the Names to a Index
    std::map<std::string,int> m_planat_dir;




  
};

}//astorids



#endif
