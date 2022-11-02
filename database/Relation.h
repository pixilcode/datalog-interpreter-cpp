#ifndef PROJECT_2_RELATION_H
#define PROJECT_2_RELATION_H

#include <set>
#include <utility>
#include "Header.h"
#include "Tuple.h"

class Relation {
private:
    string name;
    Header header;
    set<Tuple> tuples;

public:
    Relation(string name, Header header, set<Tuple> tuples):
        name(std::move(name)),
        header(std::move(header)),
        tuples(std::move(tuples)) {}

    [[nodiscard]] Relation addTuple(const Tuple& tuple) const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] bool hasAttributes() const;

    [[nodiscard]] Relation selectConstant(size_t index, const string& constant) const;
    [[nodiscard]] Relation selectCompare(size_t indexA, size_t indexB) const;
    [[nodiscard]] Relation project(const vector<size_t>& indices) const;
    [[nodiscard]] Relation rename(const vector<string>& attributes) const;

    [[nodiscard]] Header getHeader() const {
        return header;
    }

    [[nodiscard]] set<Tuple> getTuples() const {
        return tuples;
    }
};

template<typename T>
vector<T> pickIndices(const vector<size_t>& indices, const vector<T>& source);

#endif //PROJECT_2_RELATION_H
