#include "fsizenulldelegate.h"

namespace uilib {

FSizeNullDelegate::FSizeNullDelegate(const CCSize &size)
{
    m_size = size;
    setWidth(m_size.width);
    setHeight(m_size.height);
    setFixedSize(m_size);
}
FSizeNullDelegate::~FSizeNullDelegate()
{

}
void FSizeNullDelegate::getFixedSize(CCSize &size)
{
    size = m_size;
}

}

