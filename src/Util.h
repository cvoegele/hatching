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

    static unsigned char * readImage(const std::string &imagePath);
};


#endif //TEST_UTIL_H
