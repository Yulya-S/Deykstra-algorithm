#ifndef _GRAPH_
#define _GRAPH_

#include <set>
#include <vector>
#include <string>
using namespace std;

class Node {
private:
	string name;
	vector<int> edgePrices;
public:
	vector<Node*> neighbours;

	void addNeighbour(Node* neighbour, int edgePrice);
	void removeNeighbour(Node* neighbour);
	int getNeighbourPrice(const int idx) { return edgePrices[idx]; }
	Node(const string& text, int price = 0) { name = text; }
	const string& getName() const { return name; }
	friend class Graph;
};

typedef set<Node*>::const_iterator node_iterator;
class Graph {
public:
	set<Node*> nodes;

	void addNode(Node* node);
	void removeNode(Node* node);
	void addEdge(Node* begin, Node* end, int edgePrice = 0);
	void removeEdge(Node* begin, Node* end);
	node_iterator begin() const { return nodes.begin(); }
	node_iterator end() const { return nodes.end(); }
	void makeGraph(char* fileName);
	void clear();
};

class Deykstry {
private:
	vector<string> nodes;
	int min_sum = 999999;
public:
	Deykstry(const Graph graph, string nodeName, const string& finishNodeName, vector<string> nodes, int sum = 0) { process(graph, nodeName, finishNodeName, nodes, sum); }
	int process(const Graph graph, string nodeName, const string & finishNodeName, vector<string> nodes, int sum = 0);
	void clear() { nodes.clear(); min_sum = 999999; }
	void write();
};

bool nodeInGraph(const Graph start_graph, const string& nodeName);


#endif