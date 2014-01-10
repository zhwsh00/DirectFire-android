#ifndef _ballutils_h_
#define _ballutils_h_
#include "absball.h"
#include "cocos2d.h"
using namespace cocos2d;

bool isCircleConflict(const CCPoint &p1,const CCPoint &p2,float len,float &distance);
bool isCircleConflictFast(const CCPoint &p1,const CCPoint &p2,float r1,float r2);
void getCenterPoint(int count,BasBall *start,CCPoint &center);
void getCenterBoundingRect(int count,BasBall *start,CCRect &rect);
void getBallBoundingRect(int count,BasBall *start,CCRect &rect);
#endif
