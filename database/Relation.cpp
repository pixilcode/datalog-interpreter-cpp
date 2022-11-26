#include "Relation.h"

#include <algorithm>
#include <stdexcept>
#include <map>

Relation Relation::selectConstant(size_t index, const std::string &constant) const {
    set<Tuple> filteredTuples;

    for (const Tuple &tuple: tuples) {
        if (tuple.get(index) == constant)
            filteredTuples.insert(tuple);
    }

    return {name, header, filteredTuples};
}

Relation Relation::selectCompare(size_t indexA, size_t indexB) const {
    set<Tuple> filteredTuples;

    for (const Tuple &tuple: tuples) {
        if (tuple.get(indexA) == tuple.get(indexB))
            filteredTuples.insert(tuple);
    }

    return {name, header, filteredTuples};
}

Relation Relation::project(const vector<size_t> &indices) const {
    Header newHeader = Header(pickIndices(indices, header.getAttributes()));
    set<Tuple> newTuples;

    for (const Tuple &tuple: tuples) {
        newTuples.insert(Tuple(pickIndices(indices, tuple.getValues())));
    }

    return {name, newHeader, newTuples};
}

Relation Relation::rename(const vector<string> &attributes) const {
    if (attributes.size() != header.getAttributes().size())
        throw runtime_error("Rename must have same number of headers as original");
    return {name, Header(attributes), tuples};
}

Relation Relation::union_(const Relation &other) const {
    if (header.getAttributes() != other.header.getAttributes())
        throw runtime_error("Union must be between two relations with the same headers");
    set<Tuple> newTuples(tuples);
    newTuples.insert(other.tuples.begin(), other.tuples.end());
    return {name, header, newTuples};
}

Relation Relation::naturalJoin(const Relation &other) const {
    vector<string> thisAttributes(header.getAttributes());
    vector<string> otherAttributes(other.header.getAttributes());

    vector<string> allHeaders;
    set<pair<size_t, size_t>> sharedHeaders;

    // Keep track of the location of the header location in the new index
    vector<variant<size_t, size_t>> headerLoc;

    for (size_t i = 0; i < thisAttributes.size(); i++) {
        const auto &attribute = thisAttributes.at(i);
        const auto otherLoc = find(otherAttributes.begin(), otherAttributes.end(), attribute);
        if (otherLoc != otherAttributes.end()) {
            const auto otherLocIdx = otherLoc - otherAttributes.begin();
            sharedHeaders.emplace(pair<size_t, size_t>(i, otherLocIdx));
        } else {
            allHeaders.push_back(attribute);
            headerLoc.emplace_back(in_place_index<0>, i);
        }
    }

    for (size_t i = 0; i < otherAttributes.size(); i++) {
        allHeaders.push_back(otherAttributes.at(i));
        headerLoc.emplace_back(in_place_index<1>, i);
    }

    set<Tuple> newTuples;

    for (const auto &thisTuple: tuples) {
        for (const auto &otherTuple: other.tuples) {
            if (commonHeadersMatch(thisTuple, otherTuple, sharedHeaders)) {
                auto newTuple = makeNewTuple(thisTuple, otherTuple, headerLoc);
                newTuples.emplace(newTuple);
            }
        }
    }

    return {name + "/" + other.name, Header(allHeaders), newTuples};
}

Relation Relation::addTuple(const Tuple &tuple) const {
    set<Tuple> newTuples(tuples);
    newTuples.insert(tuple);
    return {name, header, newTuples};
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

bool commonHeadersMatch(const Tuple &tupleA, const Tuple &tupleB, const set<pair<size_t, size_t>> &sharedHeaders) {
    return all_of(
            sharedHeaders.begin(),
            sharedHeaders.end(),
            [tupleA, tupleB](auto shared) { return tupleA.get(shared.first) == tupleB.get(shared.second); }
    );
}

Tuple makeNewTuple(const Tuple &tupleA, const Tuple &tupleB, const vector<variant<size_t, size_t>> &headerLoc) {
    vector<string> newTuple;
    for (auto header: headerLoc) {
        if (header.index() == 0) {
            newTuple.push_back(tupleA.get(get<0>(header)));
        } else {
            newTuple.push_back(tupleB.get(get<1>(header)));
        }
    }

    return Tuple(newTuple);
}

template<typename T>
vector<T> pickIndices(const vector<size_t> &indices, const vector<T> &source) {
    vector<T> result;

    for (size_t index: indices) {
        result.push_back(source.at(index));
    }

    return result;
}
