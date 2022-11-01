#ifndef PROJECT_2_HEADER_H
#define PROJECT_2_HEADER_H

#include <string>
#include <utility>
#include <vector>

using namespace std;

class Header {
private:
    vector<string> attributes;

public:
    explicit Header(vector<string> attributes): attributes(std::move(attributes)) {}
    [[nodiscard]] vector<string> getAttributes() const { return attributes; }
};

#endif //PROJECT_2_HEADER_H
