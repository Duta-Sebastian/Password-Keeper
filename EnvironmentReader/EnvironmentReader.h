#ifndef ENVIRONMENTREADER_H
#define ENVIRONMENTREADER_H

#include <map>
#include <string>

class EnvironmentReader {
    std::string filePath = "../.env";
    std::map<std::string, std::string> envMap;

    EnvironmentReader();

public:
    EnvironmentReader(const EnvironmentReader &) = delete;

    EnvironmentReader &operator=(const EnvironmentReader &) = delete;

    static EnvironmentReader &getEnvReader();

    std::string getConnString();
};


#endif //ENVIRONMENTREADER_H
