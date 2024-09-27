#include "Graph.h"
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <queue>
using namespace std;

void Node::addNeighbour(Node* neighbour, int edgePrice = 0) {
	for (int i = 0; i != neighbours.size(); i++)
		if (neighbours[i]->getName() == neighbour->getName()) return;
	neighbours.push_back(neighbour);
	edgePrices.push_back(edgePrice);
}

void Node::removeNeighbour(Node* neighbour) {
	int i = 0;
	for (int i = 0; i != neighbours.size(); i++)
		if (neighbours[i]->getName() == neighbour->getName()) {
			neighbours.erase(neighbours.begin() + i);
			edgePrices.erase(edgePrices.begin() + i);
			return;
		}
}

void Graph::addNode(Node* node) {
	for (set<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) if ((*it)->getName() == node->getName()) return;
	nodes.insert(node);
}
void Graph::removeNode(Node* node) {
	nodes.insert(node);
	for (auto it : nodes) it->removeNeighbour(node);
}

void Graph::addEdge(Node* begin, Node* end, int edgePrice) {
	for (set<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) if ((*it)->getName() == begin->getName()) {
		begin = *it;
		break;
	}
	for (auto it : nodes) if (it->getName() == end->getName()) {
		end = it;
		break;
	}
	begin->addNeighbour(end, edgePrice);
}

void Graph::removeEdge(Node* begin, Node* end) {
	begin->removeNeighbour(end);
	end->removeNeighbour(begin);
}

void Graph::makeGraph(char* fileName) {
	ifstream in(fileName);
	string a, b, price;
	while (!in.eof()) {
		in >> a >> b >> price;
		Node* node1 = new Node(a);
		Node* node2 = new Node(b);
		addNode(node1);
		addNode(node2);
		addEdge(node1, node2, stoi(price));
	}
	in.close();
}

void Graph::clear() {
	for (auto i : nodes) removeNode(i);
}

int Deykstry::process(const Graph graph, string nodeName, const string& finishNodeName, vector<string> n, int sum) {
	if (!nodeInGraph(graph, nodeName) || !nodeInGraph(graph, finishNodeName)) return 999999;
	for (auto i : n) if (i == nodeName) return 999999;

	n.push_back(nodeName);

	if (nodeName == finishNodeName) {

		/*for (auto i : n) cout << i << " ";
		cout << "\tsum: " << sum << " ";
		cout << (sum < min_sum) << endl;*/

		if (min_sum > sum) {
			nodes = n;
			min_sum = sum;
		}
		return min_sum;
	}

	for (set<Node*>::iterator it = graph.nodes.begin(); it != graph.nodes.end(); it++)
		if ((*it)->getName() == nodeName)
			for (int i = 0; i < (*it)->neighbours.size(); i++) {
				process(graph, (*it)->neighbours[i]->getName(), finishNodeName, n, sum + (*it)->getNeighbourPrice(i));
			}
	return min_sum;
}

void Deykstry::write() {
	for (auto i : nodes) cout << i << " ";
	cout << "\tsum: " << min_sum << endl;
}


bool nodeInGraph(const Graph start_graph, const string& nodeName) {
	for (auto it : start_graph.nodes)
		if (it->getName() == nodeName) return true;
	return false;
}

