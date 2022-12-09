#include "Graph.h"

#include <sstream>

pair<vector<Id>, map<Id, bool>> Graph::postorderTraverse(const Id curr, const map<Id, bool> &visited) const {
    // If it's visited, return an empty vector
    if (visited.find(curr) != visited.end() && visited.at(curr)) {
        return {{}, visited};
    }

    vector<Id> result;
    map<Id, bool> visitedResult(visited);

    // Mark the current node as visited
    visitedResult.emplace(curr, true);

    // For each node that is adjacent...
    for (const auto &id: adjList.at(curr)) {
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

pair<set<Id>, map<Id, bool>> Graph::sccTraverse(const Id curr, const map<Id, bool> &visited) const {
    // If it's visited, return an empty vector
    if (visited.find(curr) != visited.end() && visited.at(curr)) {
        return {{}, visited};
    }

    set<Id> result;
    map<Id, bool> visitedResult(visited);

    // Mark the current node as visited
    visitedResult.emplace(curr, true);

    // For each node that is adjacent...
    for (const auto &id: adjList.at(curr)) {
        // Visit it with the visited list
        auto [postList, newVisited] = postorderTraverse(id, visitedResult);

        // Add the results
        result.insert(postList.begin(), postList.end());
        visitedResult = newVisited;
    }

    // Push the current node
    result.emplace(curr);

    return {result, visitedResult};
}

vector<Id> Graph::postorder(const vector<Id> &order) const {
    vector<Id> result;
    map<Id, bool> visited;

    for (const auto &id: order) {
        if (visited.find(id) == visited.end() || !visited.at(id)) {
            // Visit it with the visited list
            auto [postList, newVisited] = postorderTraverse(id, visited);

            // Add the results
            result.insert(result.end(), postList.begin(), postList.end());
            visited = newVisited;
        }
    }

    return result;
}

vector<set<Id>> Graph::scc(const vector<Id> &order) const {
    vector<set<Id>> result;
    map<Id, bool> visited;

    for (const auto &id: order) {
        if (visited.find(id) == visited.end() || !visited.at(id)) {
            // Visit it with the visited list
            auto [scc, newVisited] = sccTraverse(id, visited);

            // Add the results
            result.push_back(scc);
            visited = newVisited;
        }
    }

    return result;
}

string Graph::toString() const {
    ostringstream result;
    for (const auto &[from, tos]: adjList) {
        result << "R" << from << ":";
        size_t i = 0;
        for (const auto &to: tos) {
            result << "R" << to;
            if (i++ < tos.size() - 1) result << ",";
        }
        result << "\n";
    }
    return result.str();
}

bool Graph::hasIdLoop(const Id &node) const {
    return adjList.at(node).find(node) != adjList.at(node).end();
}
