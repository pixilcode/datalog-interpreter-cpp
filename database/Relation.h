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

    Relation selectConstant(size_t index, const string& constant);
    Relation selectCompare(size_t indexA, size_t indexB);
    Relation project(vector<size_t> indices);
    Relation rename(vector<string> attributes);
};


#endif //PROJECT_2_RELATION_H
