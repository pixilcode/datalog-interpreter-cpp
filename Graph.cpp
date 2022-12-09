#include "Graph.h"

template<typename Id>
pair<vector<Id>, map<Id, bool>> Graph<Id>::postorderTraverse(const Id curr, const map<Id, bool> &visited) {
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
        auto [postList, newVisited] = postorderTraverse(id, visitedResult);

        // Add the results
        result.insert(result.end(), postList.begin(), postList.end());
        visitedResult = newVisited;
    }

    // Push the current node
    result.push_back(curr);

    return {result, visitedResult};
}

template<typename Id>
pair<set<Id>, map<Id, bool>> Graph<Id>::sccTraverse(const Id curr, const map<Id, bool> &visited) {
    // If it's visited, return an empty vector
    if (visited[curr]) {
        return {{}, visited};
    }

    set<Id> result;
    map<Id, bool> visitedResult(visited);

    // Mark the current node as visited
    visitedResult.emplace({curr, true});

    // For each node that is adjacent...
    for (const auto &id: adjList) {
        // Visit it with the visited list
        auto [postList, newVisited] = postorderTraverse(id, visitedResult);

        // Add the results
        result.insert(result.end(), postList.begin(), postList.end());
        visitedResult = newVisited;
    }

    // Push the current node
    result.emplace(curr);

    return {result, visitedResult};
}

template<typename Id>
vector<Id> Graph<Id>::postorder(vector<Id> order) const {
    vector<Id> result;
    map<Id, bool> visited;

    for (const auto &id: order) {
        if (find(visited.begin(), visited.end(), id) == visited.end()) {
            // Visit it with the visited list
            auto [postList, newVisited] = postorderTraverse(id, visited);

            // Add the results
            result.insert(result.end(), postList.begin(), postList.end());
            visited = newVisited;
        }
    }

    return result;
}

template<typename Id>
vector<set<Id>> Graph<Id>::scc(vector<Id> order) const {
    vector<set<Id>> result;
    map<Id, bool> visited;

    for (const auto &id: order) {
        if (find(visited.begin(), visited.end(), id) == visited.end()) {
            // Visit it with the visited list
            auto [scc, newVisited] = sccTraverse(id, visited);

            // Add the results
            result.push_back(scc);
            visited = newVisited;
        }
    }

    return result;
}
