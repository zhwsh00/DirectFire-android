#ifndef _namegenerator_h_
#define _namegenerator_h_
#include <string>
#include <sstream>
using namespace std;
namespace uilib
{

class NameGenerator
{
private:
    NameGenerator();
    ~NameGenerator();
public:
    static const std::string &getUnusedName();
protected:
    static NameGenerator *m_instance;
    std::string m_prefix;
    std::string m_currName;
    int m_usedIndex;
};
}
#endif
