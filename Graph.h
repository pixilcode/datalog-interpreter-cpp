#ifndef PROJECT_5_GRAPH_H
#define PROJECT_5_GRAPH_H

#include <algorithm>
#include <map>
#include <string>
#include <set>
#include <vector>

using namespace std;

template<typename Id>
class Graph {
private:
    map<Id, set<Id>> adjList;

    pair<vector<Id>, map<Id, bool>> doStuff(Id curr, const map<Id, bool> &visited);

public:
    explicit Graph(set<pair<Id, Id>> edges) : adjList(edges) {}

    [[nodiscard]] Graph reverse() const {
        set<pair<Id, Id>> newEdges;
        for (const auto &[from, edges]: adjList) {
            for (const auto &to: edges) {
                newEdges.push_back({to, from});
            }
        }

        return Graph(newEdges);
    }

    [[nodiscard]] vector<Id> postorder(vector<Id> order) const;
};


#endif //PROJECT_5_GRAPH_H
