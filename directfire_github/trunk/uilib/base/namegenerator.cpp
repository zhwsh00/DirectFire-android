#include "namegenerator.h"

namespace uilib
{
NameGenerator *NameGenerator::m_instance = 0;
NameGenerator::NameGenerator()
{
    m_prefix = "n";
    m_usedIndex = 1;
}
NameGenerator::~NameGenerator()
{

}
const std::string &NameGenerator::getUnusedName()
{
    if(m_instance == 0)
        m_instance = new NameGenerator;
    std::stringstream ss;
    ss << m_instance->m_prefix << m_instance->m_usedIndex++;
    m_instance->m_currName = ss.str();
    return m_instance->m_currName;
}

}
