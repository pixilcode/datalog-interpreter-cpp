#ifndef PROJECT_2_RELATION_H
#define PROJECT_2_RELATION_H

#include <set>
#include <utility>
#include <variant>
#include "Header.h"
#include "Tuple.h"

class Relation {
private:
    string name;
    Header header;
    set<Tuple> tuples;

public:
    Relation(string name, Header header, set<Tuple> tuples) :
            name(std::move(name)),
            header(std::move(header)),
            tuples(std::move(tuples)) {}

    [[nodiscard]] Relation addTuple(const Tuple &tuple) const;

    [[nodiscard]] size_t size() const;

    [[nodiscard]] bool empty() const;

    [[nodiscard]] bool hasAttributes() const;

    // RELATIONAL OPERATORS

    [[nodiscard]] Relation selectConstant(size_t index, const string &constant) const;

    [[nodiscard]] Relation selectCompare(size_t indexA, size_t indexB) const;

    [[nodiscard]] Relation project(const vector<size_t> &indices) const;

    [[nodiscard]] Relation rename(const vector<string> &attributes) const;

    [[nodiscard]] Relation union_(const Relation &other) const;

    [[nodiscard]] Relation naturalJoin(const Relation &other) const;

    // GETTERS

    [[nodiscard]] Header getHeader() const {
        return header;
    }

    [[nodiscard]] set<Tuple> getTuples() const {
        return tuples;
    }
};

template<typename T>
vector<T> pickIndices(const vector<size_t> &indices, const vector<T> &source);

bool commonHeadersMatch(const Tuple &tupleA, const Tuple &tupleB, const set<pair<size_t, size_t>> &sharedHeaders);

Tuple makeNewTuple(const Tuple &tupleA, const Tuple &tupleB, const vector<variant<size_t, size_t>> &headerLoc);

#endif //PROJECT_2_RELATION_H
