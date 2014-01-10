#ifndef _absanchor_h_
#define _absanchor_h_
#include <string>
#include <iostream>
using namespace std;

namespace uilib
{
enum AnchorType
{
    /* this for absoluteness coordinate */
    Left = 0,
    Top,
    Right,
    Bottom,
    /* this for relative corrdinate */
    CenterIn,
    Fill,
    HorizontalCenter,
    VerticalCenter
};
enum MarginType
{
    Margins = 0,
    LeftMargin,
    TopMargin,
    RightMargin,
    BottomMargin
};

class BasAnchor
{
public:
    BasAnchor();
    virtual ~BasAnchor();
    void clearAnchor();

    void setLeft(const std::string &name,AnchorType type);
    inline const std::string &leftName() { return m_leftName;}
    inline AnchorType leftType() { return m_leftType;}

    void setTop(const std::string &name,AnchorType type);
    inline const std::string &TopName() { return m_topName;}
    inline AnchorType topType() { return m_topType;}

    void setRight(const std::string &name,AnchorType type);
    inline const std::string &RightName() { return m_rightName;}
    inline AnchorType rightType() { return m_rightType;}

    void setBottom(const std::string &name,AnchorType type);
    inline const std::string &bottomName() { return m_bottomName;}
    inline AnchorType bottomType() { return m_bottomType;}

    inline void setCenterIn(const std::string &name) { m_centerInName = name;}
    inline const std::string &centerInName() { return m_centerInName;}

    inline void setFill(const std::string &name) { m_fillName = name;}
    inline const std::string &fillName() { return m_fillName;}

    inline void setLeftMargin(float m) { m_leftMargin = m;}
    inline float leftMargin() { return m_leftMargin;}

    inline void setTopMargin(float m) { m_topMargin = m;}
    inline float topMargin() { return m_topMargin;}

    inline void setRightMargin(float m) { m_rightMargin = m;}
    inline float rightMargin() { return m_rightMargin;}

    inline void setBottomMargin(float m) { m_bottomMargin = m;}
    inline float bottomMargin() { return m_bottomMargin;}

    void setMargins(float m);

    inline void setHorMargin(float m) { m_horMargin = m;}
    inline float horMargin() { return m_horMargin;}

    inline void setVerMargin(float m) { m_verMargin = m;}
    inline float verMargin() { return m_verMargin;}

    void setHorizontal(const std::string &name,float value);
    inline const std::string &horizontalName() { return m_horizontalName;}
    inline float horizontalValue() { return m_horizontalValue;}

    void setVertical(const std::string &name,float value);
    inline const std::string &verticalName() { return m_verticalName;}
    inline float verticalValue() { return m_verticalValue;}

    bool isValidLocation();
    bool isRelativeLocation();
    bool isAbsoluteLocation();

    inline bool isAnchored() { return m_anchored;}
    void setAnchored(bool anchor);
    virtual void setAnchoredSize(float width,float height);
    bool getAnchorSize(float &width,float &height);
public:
    virtual void setX(float v);
    virtual float getX();
    virtual void setY(float v);
    virtual float getY();
    virtual void setWidth(float v);
    virtual float getWidth();
    virtual void setHeight(float v);
    virtual float getHeight();
protected:
    std::string m_leftName;
    AnchorType m_leftType;
    std::string m_topName;
    AnchorType m_topType;
    std::string m_rightName;
    AnchorType m_rightType;
    std::string m_bottomName;
    AnchorType m_bottomType;
    std::string m_centerInName;
    std::string m_fillName;
    std::string m_horizontalName;
    float m_horizontalValue;
    std::string m_verticalName;
    float m_verticalValue;

    float m_leftMargin;
    float m_topMargin;
    float m_rightMargin;
    float m_bottomMargin;

    float m_horMargin;
    float m_verMargin;
protected:
    float m_x;
    float m_y;
    float m_width;
    float m_height;
    bool m_anchored;

    float m_anchorLeft;
    float m_anchorRight;
    float m_anchorTop;
    float m_anchorBottom;
    float m_anchorWidth;
    float m_anchorHeight;
    bool m_leftAnchored;
    bool m_rightAnchored;
    bool m_topAnchored;
    bool m_bottomAnchored;
};
}
#endif
