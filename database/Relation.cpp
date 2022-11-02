#include "Relation.h"

#include <algorithm>

Relation Relation::selectConstant(size_t index, const std::string &constant) const {
    set<Tuple> filteredTuples;

    for (const Tuple& tuple : tuples) {
        if (tuple.get(index) == constant)
            filteredTuples.insert(tuple);
    }

    return { name, header, filteredTuples };
}

Relation Relation::selectCompare(size_t indexA, size_t indexB) const {
    set<Tuple> filteredTuples;

    for (const Tuple& tuple : tuples) {
        if (tuple.get(indexA) == tuple.get(indexB))
            filteredTuples.insert(tuple);
    }

    return { name, header, filteredTuples };
}

Relation Relation::project(const vector<size_t> &indices) const {
    Header newHeader = Header(pickIndices(indices, header.getAttributes()));
    set<Tuple> newTuples;

    for (const Tuple& tuple : tuples) {
        newTuples.insert(Tuple(pickIndices(indices, tuple.getValues())));
    }

    return { name, newHeader, newTuples };
}

Relation Relation::rename(const vector<string> &attributes) const {
    return { name, Header(attributes), tuples };
}

Relation Relation::addTuple(const Tuple& tuple) const {
    set<Tuple> newTuples(tuples);
    newTuples.insert(tuple);
    return { name, header, newTuples };
}

bool Relation::empty() const {
    return tuples.empty();
}

bool Relation::hasAttributes() const {
    return !header.getAttributes().empty();
}

size_t Relation::size() const {
    return tuples.size();
}

template<typename T>
vector<T> pickIndices(const vector<size_t>& indices, const vector<T>& source) {
    vector<T> result(indices.size());

    for(size_t index : indices) {
        result.push_back(source.at(index));
    }

    return result;
}
