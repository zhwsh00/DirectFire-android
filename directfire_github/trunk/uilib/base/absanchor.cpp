#include "absanchor.h"

namespace uilib
{

BasAnchor::BasAnchor()
{
    clearAnchor();
}
BasAnchor::~BasAnchor()
{

}
void BasAnchor::clearAnchor()
{
    m_leftName.clear();
    m_topName.clear();
    m_rightName.clear();
    m_bottomName.clear();
    m_centerInName.clear();
    m_fillName.clear();
    m_leftMargin = 0;
    m_topMargin = 0;
    m_rightMargin = 0;
    m_bottomMargin = 0;
    m_horMargin = 0;
    m_verMargin = 0;
    //
    m_x = -10000;
    m_y = -10000;
    m_width = -1;
    m_height = -1;

    m_horizontalValue = 0;
    m_verticalValue = 0;

    m_anchored = false;
    m_anchorWidth = 0;
    m_anchorHeight = 0;
    m_leftAnchored = false;
    m_rightAnchored = false;
    m_topAnchored = false;
    m_bottomAnchored = false;
}
void BasAnchor::setLeft(const std::string &name,AnchorType type)
{
    if(type != Left && type != Right){
        cout << "BasAnchor::setLeft,invalid leftType,check please!" << endl;
        return;
    }
    m_leftName = name;
    m_leftType = type;
}
void BasAnchor::setTop(const std::string &name,AnchorType type)
{
    if(type != Top && type != Bottom){
        cout << "BasAnchor::setTop,invalid topType,check please!" << endl;
        return;
    }
    m_topName = name;
    m_topType = type;
}
void BasAnchor::setRight(const std::string &name,AnchorType type)
{
    if(type != Left && type != Right){
        cout << "BasAnchor::setRight,invalid rightType,check please!" << endl;
        return;
    }
    m_rightName = name;
    m_rightType = type;
}
void BasAnchor::setBottom(const std::string &name,AnchorType type)
{
    if(type != Top && type != Bottom){
        cout << "BasAnchor::setBottom,invalid bottomType,check please!" << endl;
        return;
    }
    m_bottomName = name;
    m_bottomType = type;
}
void BasAnchor::setHorizontal(const std::string &name,float value)
{
    m_horizontalName = name;
    m_horizontalValue = value;
}
void BasAnchor::setVertical(const std::string &name,float value)
{
    m_verticalName = name;
    m_verticalValue = value;
}

void BasAnchor::setMargins(float m)
{
    m_leftMargin = m;
    m_topMargin = m;
    m_rightMargin = m;
    m_bottomMargin = m;
}
bool BasAnchor::isValidLocation()
{
    return isAbsoluteLocation() || isRelativeLocation();
}
bool BasAnchor::isRelativeLocation()
{
    if(m_leftName.size() != 0 ||
            m_topName.size() != 0 ||
            m_rightName.size() != 0 ||
            m_bottomName.size() != 0)
        return true;
    return false;
}
bool BasAnchor::isAbsoluteLocation()
{
    if(m_horizontalName.size() != 0 &&
            m_verticalName.size() != 0)
        return true;
    if(m_fillName.size() != 0)
        return true;
    if(m_centerInName.size() != 0)
        return true;
    if(m_x != -10000 && m_y != -10000)
        return true;
    return false;
}
void BasAnchor::setX(float v)
{
    m_x = v;
}
float BasAnchor::getX()
{
    return m_x;
}
void BasAnchor::setY(float v)
{
    m_y = v;
}
float BasAnchor::getY()
{
    return m_y;
}
void BasAnchor::setWidth(float v)
{
    m_width = v;
    m_anchorWidth = v;
}
float BasAnchor::getWidth()
{
    return m_width;
}
void BasAnchor::setHeight(float v)
{
    m_height = v;
    m_anchorHeight = v;
}
float BasAnchor::getHeight()
{
    return m_height;
}
void BasAnchor::setAnchored(bool anchor)
{
     m_anchored = anchor;
     if(m_anchored){
         m_leftAnchored = true;
         m_rightAnchored = true;
         m_topAnchored = true;
         m_bottomAnchored = true;
     }else{
         m_leftAnchored = false;
         m_rightAnchored = false;
         m_topAnchored = false;
         m_bottomAnchored = false;
     }
}
void BasAnchor::setAnchoredSize(float width,float height)
{
    m_anchorWidth = width;
    m_anchorHeight = height;
}
bool BasAnchor::getAnchorSize(float &width,float &height)
{
    if(m_anchorWidth >= 0 && m_anchorHeight >= 0){
        width = m_anchorWidth;
        height = m_anchorHeight;
        return true;
    }else{
        cout << "BasAnchor::getAnchorSize,can not get anchorSize!" << endl;
        return false;
    }
}

}
