#include "Graph.h"

template<typename Id>
pair<vector<Id>, map<Id, bool>> Graph<Id>::doStuff(const Id curr, const map<Id, bool> &visited) {
    // If it's visited, return an empty vector
    if (visited[curr]) {
        return {{}, visited};
    }

    vector<Id> result;
    map<Id, bool> visitedResult(visited);

    // Mark the current node as visited
    visitedResult.emplace({curr, true});

    // For each node that is adjacent...
    for (const auto &id: adjList) {
        // Visit it with the visited list
        auto [postList, newVisited] = doStuff(id, visitedResult);

        // Add the results
        result.insert(result.end(), postList.begin(), postList.end());
        visitedResult = newVisited;
    }

    // Push the current node
    result.push_back(curr);

    return {result, visitedResult};
}

template<typename Id>
vector<Id> Graph<Id>::postorder(vector<Id> order) const {
    vector<Id> result;
    map<Id, bool> visited;
    vector<Id> orderStack = reverse(order);

    for (const auto &id: order) {
        if (std::find(visited.begin(), visited.end(), id) == visited.end()) {
            // Visit it with the visited list
            auto [postList, newVisited] = doStuff(id, visited);

            // Add the results
            result.insert(result.end(), postList.begin(), postList.end());
            visited = newVisited;
        }
    }

    return visited;
}