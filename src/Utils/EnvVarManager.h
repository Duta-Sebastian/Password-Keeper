#ifndef ENVVARMANAGER_H
#define ENVVARMANAGER_H

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif
#include <string>

class EnvVarManager {
    static std::string getEnv(const std::string&);
    static int setEnv(const std::string&, const std::string&);
    static int unsetEnv(const std::string&);
public:
    static std::string get(const std::string&);
    static int set(const std::string&, const std::string&);
    static int unset(const std::string&);
    friend std::ostream& operator<<(std::ofstream&, EnvVarManager&);
};



#endif //ENVVARMANAGER_H
