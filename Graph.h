#ifndef PROJECT_5_GRAPH_H
#define PROJECT_5_GRAPH_H

#include <algorithm>
#include <map>
#include <string>
#include <set>
#include <vector>

using namespace std;

typedef size_t Id;

class Graph {
private:
    set<Id> nodes;
    map<Id, set<Id>> adjList;

    [[nodiscard]] pair<vector<Id>, map<Id, bool>> postorderTraverse(Id curr, const map<Id, bool> &visited) const;

    [[nodiscard]] pair<set<Id>, map<Id, bool>> sccTraverse(Id curr, const map<Id, bool> &visited) const;

public:
    Graph(const set<Id> &nodes, const set<pair<Id, Id>> &edges) : nodes(nodes) {
        for (const auto &node: nodes) {
            adjList.emplace(node, set<Id>());
        }
        for (const auto &[from, to]: edges) {
            adjList.at(from).emplace(to);
        }
    }

    [[nodiscard]] Graph reverse() const {
        set<pair<Id, Id>> newEdges;
        for (const auto &[from, edges]: adjList) {
            for (const auto &to: edges) {
                newEdges.insert({to, from});
            }
        }

        return Graph(nodes, newEdges);
    }

    [[nodiscard]] vector<Id> postorder(const vector<Id> &order) const;

    [[nodiscard]] vector<set<Id>> scc(const vector<Id> &order) const;

    bool hasIdLoop(const Id &node) const;

    [[nodiscard]] string toString() const;
};


#endif //PROJECT_5_GRAPH_H
