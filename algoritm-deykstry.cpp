#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    char inFileName[140] = { "graph.txt" };
    Graph graph;
    graph.makeGraph(inFileName);

    cout << "Создан граф:" << endl;
    for (auto i : graph.nodes)
        for (int j = 0; j != i->neighbours.size(); j++) {
            cout << i->getName() << " " << i->neighbours[j]->getName() << " " << i->getNeighbourPrice(j) << endl;
        }

    Deykstry deykstry(graph, "1", "9", vector<string>());
    cout << endl << "Самый короткий путь: " << endl;
    deykstry.write();
}