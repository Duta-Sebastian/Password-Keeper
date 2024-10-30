#ifndef ENVIRONMENTREADER_H
#define ENVIRONMENTREADER_H

#include <string>

class EnvironmentReader {
    std::string filePath = "../.env";

    EnvironmentReader();

public:
    EnvironmentReader(const EnvironmentReader &) = delete;

    EnvironmentReader &operator=(const EnvironmentReader &) = delete;

    EnvironmentReader(EnvironmentReader &&) = delete;

    EnvironmentReader &operator=(EnvironmentReader &&) = delete;

    static EnvironmentReader &getEnvReader();

    static std::string getConnString();
};


#endif //ENVIRONMENTREADER_H
