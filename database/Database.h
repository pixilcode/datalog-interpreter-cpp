#ifndef PROJECT_2_DATABASE_H
#define PROJECT_2_DATABASE_H

#include <map>
#include <utility>
#include "Relation.h"

class Database {
private:
    map<string, Relation> relations;

public:
    explicit Database(map<string, Relation> relations): relations(std::move(relations)) {}
    void addRelation(const string& name, const Relation& relation) {
        relations.insert_or_assign(name, relation);
    }
    void addTuple(const string& relationName, const Tuple& tuple) {
        Relation newRelation = relations.at(relationName).addTuple(tuple);
        relations.insert_or_assign(relationName, newRelation);
    }
    [[nodiscard]] Relation getRelation(const string& name) const {
        return relations.at(name);
    }
};


#endif //PROJECT_2_DATABASE_H
