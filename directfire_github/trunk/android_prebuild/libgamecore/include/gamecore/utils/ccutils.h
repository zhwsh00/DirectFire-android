#ifndef _ccutils_h_
#define _ccutils_h_
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
long getCCMilliSecond();
void getWorldRect(CCNode *sprite,CCRect &rect);
bool getIntersectRect(const CCRect &r1,const CCRect &r2,CCRect &rect);
void getMergeRect(const CCRect &r1,const CCRect &r2,CCRect &rect);
void getSystemResourceRatio(std::string &ratio);
bool careClickPoint(CCNode *sprite,const CCPoint &p);
bool hasColorInAreaForImage(unsigned char *_data,int width,int height,int x,int y,int w,int h,int alpha);
bool hasColorInCircleForImage(unsigned char *_data,int width,int height,const CCPoint &center,int radius,int alpha
		,CCPoint &cpos);
bool hasColorInRectForImage(unsigned char *_data,int width,int hegiht,int x,int y,int w,int h,int _alpha
		,CCPoint &cpos);
bool hasColorInRotateRectForImage(unsigned char *_data,int width,int height,
		int ox,int oy,int ow,int oh,
		int rx,int ry,int rw,int rh,
		float radian,
		int _alpha
		,CCPoint &cpos);
void getSpriteWorldBoundingRect(CCSprite *sprite,CCRect &rect);
void getSpriteWorldBoundingRect(float rotation,const CCPoint &pos,const CCPoint &anchor,const std::string &name,CCRect &rect,int frameAt);
void getCCRectBounding(float radian,const CCRect &rect,CCRect &rrect);
void getRectBounding(float radian,float ox,float oy,float ow,float oh,
		float &rx,float &ry,float &rw,float &rh);
bool containPoint(float sx,float sy,float w,float h,float x,float y);
bool containPointWithRotate(float sx,float sy,float w,float h,float x,float y,float radian);
bool isCircleOverlap(const CCPoint &c1,float radius1,const CCPoint &c2,float radius2,float &distance);
float getCoverResourceScale();
float getAdaptResourceScale();
float getHorAdaptResourceScale();
float getVerAdaptResourceScale();
float getWholeScaleRate();
#endif
