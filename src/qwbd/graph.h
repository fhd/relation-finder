#include <QtCore>
#include <map>

#ifdef FETCHER
#define EXTERN
#else
#define EXTERN extern
#endif

typedef std::vector<int> edges;
typedef std::map<int, edges> edge;
typedef std::map<int, int> token;

EXTERN std::map<int, edge> graph;

EXTERN int edge_count;
EXTERN int node_start;
EXTERN int node_goal;

EXTERN QReadWriteLock lock;
