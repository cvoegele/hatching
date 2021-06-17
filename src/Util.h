//
// Created by Christoph Vögele on 16/03/2021.
//

#ifndef TEST_UTIL_H
#define TEST_UTIL_H


#include <string>
#include <memory>



class Util {
public:

    static std::string readFile2(const std::string &fileName);


    static std::string paramName(std::string const &key, int imguicounter) {
        return key + std::to_string(imguicounter);
    }
};


#endif //TEST_UTIL_H
