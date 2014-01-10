/**
 * @module cocos2dx
 */
var cc = cc = cc || {};

/**
 * @class CCAction
 */
cc.CCAction = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method setOriginalTarget
 * @param {cocos2d::CCNode*}
 */
setOriginalTarget : function () {},

/**
 * @method setTarget
 * @param {cocos2d::CCNode*}
 */
setTarget : function () {},

/**
 * @method getOriginalTarget
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
getOriginalTarget : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getTarget
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
getTarget : function () {},

/**
 * @method step
 * @param {float}
 */
step : function () {},

/**
 * @method setTag
 * @param {int}
 */
setTag : function () {},

/**
 * @method getTag
 * @return A value converted from C/C++ "int"
 */
getTag : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::CCAction*"
 */
action : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCAction*"
 */
create : function () {},

/**
 * @method CCAction
 * @constructor
 */
CCAction : function () {},

};

/**
 * @class CCFiniteTimeAction
 */
cc.CCFiniteTimeAction = {

/**
 * @method setDuration
 * @param {float}
 */
setDuration : function () {},

/**
 * @method getDuration
 * @return A value converted from C/C++ "float"
 */
getDuration : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCFiniteTimeAction*"
 */
reverse : function () {},

/**
 * @method CCFiniteTimeAction
 * @constructor
 */
CCFiniteTimeAction : function () {},

};

/**
 * @class CCSpeed
 */
cc.CCSpeed = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method setInnerAction
 * @param {cocos2d::CCActionInterval*}
 */
setInnerAction : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method step
 * @param {float}
 */
step : function () {},

/**
 * @method setSpeed
 * @param {float}
 */
setSpeed : function () {},

/**
 * @method initWithAction
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
initWithAction : function () {},

/**
 * @method getInnerAction
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
getInnerAction : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method getSpeed
 * @return A value converted from C/C++ "float"
 */
getSpeed : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCSpeed*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCSpeed*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
actionWithAction : function () {},

/**
 * @method CCSpeed
 * @constructor
 */
CCSpeed : function () {},

};

/**
 * @class CCFollow
 */
cc.CCFollow = {

/**
 * @method initWithTarget
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCNode*}
 * @param {cocos2d::CCRect}
 */
initWithTarget : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method setBoudarySet
 * @param {bool}
 */
setBoudarySet : function () {},

/**
 * @method step
 * @param {float}
 */
step : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method isBoundarySet
 * @return A value converted from C/C++ "bool"
 */
isBoundarySet : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCFollow*"
 * @param {cocos2d::CCNode*}
 * @param {cocos2d::CCRect}
 */
create : function () {},

/**
 * @method actionWithTarget
 * @return A value converted from C/C++ "cocos2d::CCFollow*"
 * @param {cocos2d::CCNode*}
 * @param {cocos2d::CCRect}
 */
actionWithTarget : function () {},

/**
 * @method CCFollow
 * @constructor
 */
CCFollow : function () {},

};

/**
 * @class CCTouch
 */
cc.CCTouch = {

/**
 * @method getPreviousLocationInView
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getPreviousLocationInView : function () {},

/**
 * @method getLocation
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getLocation : function () {},

/**
 * @method getDelta
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getDelta : function () {},

/**
 * @method setTouchInfo
 * @param {int}
 * @param {float}
 * @param {float}
 */
setTouchInfo : function () {},

/**
 * @method getID
 * @return A value converted from C/C++ "int"
 */
getID : function () {},

/**
 * @method getLocationInView
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getLocationInView : function () {},

/**
 * @method locationInView
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
locationInView : function () {},

/**
 * @method previousLocationInView
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
previousLocationInView : function () {},

/**
 * @method getPreviousLocation
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getPreviousLocation : function () {},

/**
 * @method CCTouch
 * @constructor
 */
CCTouch : function () {},

};

/**
 * @class CCSet
 */
cc.CCSet = {

/**
 * @method count
 * @return A value converted from C/C++ "int"
 */
count : function () {},

/**
 * @method addObject
 * @param {cocos2d::CCObject*}
 */
addObject : function () {},

/**
 * @method mutableCopy
 * @return A value converted from C/C++ "cocos2d::CCSet*"
 */
mutableCopy : function () {},

/**
 * @method anyObject
 * @return A value converted from C/C++ "cocos2d::CCObject*"
 */
anyObject : function () {},

/**
 * @method removeObject
 * @param {cocos2d::CCObject*}
 */
removeObject : function () {},

/**
 * @method copy
 * @return A value converted from C/C++ "cocos2d::CCSet*"
 */
copy : function () {},

/**
 * @method containsObject
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCObject*}
 */
containsObject : function () {},

};

/**
 * @class CCNode
 */
cc.CCNode = {

/**
 * @method setAnchorPoint
 * @param {cocos2d::CCPoint}
 */
setAnchorPoint : function () {},

/**
 * @method getScriptHandler
 * @return A value converted from C/C++ "int"
 */
getScriptHandler : function () {},

/**
 * @method convertToWorldSpaceAR
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 * @param {cocos2d::CCPoint}
 */
convertToWorldSpaceAR : function () {},

/**
 * @method isIgnoreAnchorPointForPosition
 * @return A value converted from C/C++ "bool"
 */
isIgnoreAnchorPointForPosition : function () {},

/**
 * @method setRotation
 * @param {float}
 */
setRotation : function () {},

/**
 * @method setZOrder
 * @param {int}
 */
setZOrder : function () {},

/**
 * @method setScaleY
 * @param {float}
 */
setScaleY : function () {},

/**
 * @method setScaleX
 * @param {float}
 */
setScaleX : function () {},

/**
 * @method scheduleUpdateWithPriority
 * @param {int}
 */
scheduleUpdateWithPriority : function () {},

/**
 * @method unregisterScriptHandler
 */
unregisterScriptHandler : function () {},

/**
 * @method getTag
 * @return A value converted from C/C++ "int"
 */
getTag : function () {},

/**
 * @method convertToWorldSpace
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 * @param {cocos2d::CCPoint}
 */
convertToWorldSpace : function () {},

/**
 * @method setSkewX
 * @param {float}
 */
setSkewX : function () {},

/**
 * @method setSkewY
 * @param {float}
 */
setSkewY : function () {},

/**
 * @method convertTouchToNodeSpace
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 * @param {cocos2d::CCTouch*}
 */
convertTouchToNodeSpace : function () {},

/**
 * @method getRotationX
 * @return A value converted from C/C++ "float"
 */
getRotationX : function () {},

/**
 * @method getRotationY
 * @return A value converted from C/C++ "float"
 */
getRotationY : function () {},

/**
 * @method setUserObject
 * @param {cocos2d::CCObject*}
 */
setUserObject : function () {},

/**
 * @method unscheduleUpdate
 */
unscheduleUpdate : function () {},

/**
 * @method setParent
 * @param {cocos2d::CCNode*}
 */
setParent : function () {},

/**
 * @method numberOfRunningActions
 * @return A value converted from C/C++ "unsigned int"
 */
numberOfRunningActions : function () {},

/**
 * @method stopActionByTag
 * @param {int}
 */
stopActionByTag : function () {},

/**
 * @method reorderChild
 * @param {cocos2d::CCNode*}
 * @param {int}
 */
reorderChild : function () {},

/**
 * @method getAnchorPoint
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getAnchorPoint : function () {},

/**
 * @method convertToNodeSpaceAR
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 * @param {cocos2d::CCPoint}
 */
convertToNodeSpaceAR : function () {},

/**
 * @method visit
 */
visit : function () {},

/**
 * @method setShaderProgram
 * @param {cocos2d::CCGLProgram*}
 */
setShaderProgram : function () {},

/**
 * @method getRotation
 * @return A value converted from C/C++ "float"
 */
getRotation : function () {},

/**
 * @method resumeSchedulerAndActions
 */
resumeSchedulerAndActions : function () {},

/**
 * @method getZOrder
 * @return A value converted from C/C++ "int"
 */
getZOrder : function () {},

/**
 * @method getAnchorPointInPoints
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getAnchorPointInPoints : function () {},

/**
 * @method getPositionLua
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getPositionLua : function () {},

/**
 * @method runAction
 * @return A value converted from C/C++ "cocos2d::CCAction*"
 * @param {cocos2d::CCAction*}
 */
runAction : function () {},

/**
 * @method transform
 */
transform : function () {},

/**
 * @method setVertexZ
 * @param {float}
 */
setVertexZ : function () {},

/**
 * @method setScheduler
 * @param {cocos2d::CCScheduler*}
 */
setScheduler : function () {},

/**
 * @method stopAllActions
 */
stopAllActions : function () {},

/**
 * @method getSkewX
 * @return A value converted from C/C++ "float"
 */
getSkewX : function () {},

/**
 * @method getSkewY
 * @return A value converted from C/C++ "float"
 */
getSkewY : function () {},

/**
 * @method ignoreAnchorPointForPosition
 * @param {bool}
 */
ignoreAnchorPointForPosition : function () {},

/**
 * @method getActionByTag
 * @return A value converted from C/C++ "cocos2d::CCAction*"
 * @param {int}
 */
getActionByTag : function () {},

/**
 * @method setRotationX
 * @param {float}
 */
setRotationX : function () {},

/**
 * @method setRotationY
 * @param {float}
 */
setRotationY : function () {},

/**
 * @method getScheduler
 * @return A value converted from C/C++ "cocos2d::CCScheduler*"
 */
getScheduler : function () {},

/**
 * @method getOrderOfArrival
 * @return A value converted from C/C++ "unsigned int"
 */
getOrderOfArrival : function () {},

/**
 * @method setContentSize
 * @param {cocos2d::CCSize}
 */
setContentSize : function () {},

/**
 * @method setActionManager
 * @param {cocos2d::CCActionManager*}
 */
setActionManager : function () {},

/**
 * @method isRunning
 * @return A value converted from C/C++ "bool"
 */
isRunning : function () {},

/**
 * @method getParent
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
getParent : function () {},

/**
 * @method getPositionY
 * @return A value converted from C/C++ "float"
 */
getPositionY : function () {},

/**
 * @method getPositionX
 * @return A value converted from C/C++ "float"
 */
getPositionX : function () {},

/**
 * @method setVisible
 * @param {bool}
 */
setVisible : function () {},

/**
 * @method pauseSchedulerAndActions
 */
pauseSchedulerAndActions : function () {},

/**
 * @method getVertexZ
 * @return A value converted from C/C++ "float"
 */
getVertexZ : function () {},

/**
 * @method _setZOrder
 * @param {int}
 */
_setZOrder : function () {},

/**
 * @method setScale
 * @param {float}
 */
setScale : function () {},

/**
 * @method getChildByTag
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 * @param {int}
 */
getChildByTag : function () {},

/**
 * @method setOrderOfArrival
 * @param {unsigned int}
 */
setOrderOfArrival : function () {},

/**
 * @method getScaleY
 * @return A value converted from C/C++ "float"
 */
getScaleY : function () {},

/**
 * @method getScaleX
 * @return A value converted from C/C++ "float"
 */
getScaleX : function () {},

/**
 * @method cleanup
 */
cleanup : function () {},

/**
 * @method getContentSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getContentSize : function () {},

/**
 * @method setGrid
 * @param {cocos2d::CCGridBase*}
 */
setGrid : function () {},

/**
 * @method boundingBox
 * @return A value converted from C/C++ "cocos2d::CCRect"
 */
boundingBox : function () {},

/**
 * @method draw
 */
draw : function () {},

/**
 * @method transformAncestors
 */
transformAncestors : function () {},

/**
 * @method registerScriptHandler
 * @param {int}
 */
registerScriptHandler : function () {},

/**
 * @method convertTouchToNodeSpaceAR
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 * @param {cocos2d::CCTouch*}
 */
convertTouchToNodeSpaceAR : function () {},

/**
 * @method isVisible
 * @return A value converted from C/C++ "bool"
 */
isVisible : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method sortAllChildren
 */
sortAllChildren : function () {},

/**
 * @method convertToNodeSpace
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 * @param {cocos2d::CCPoint}
 */
convertToNodeSpace : function () {},

/**
 * @method getScale
 * @return A value converted from C/C++ "float"
 */
getScale : function () {},

/**
 * @method getCamera
 * @return A value converted from C/C++ "cocos2d::CCCamera*"
 */
getCamera : function () {},

/**
 * @method setTag
 * @param {int}
 */
setTag : function () {},

/**
 * @method scheduleUpdate
 */
scheduleUpdate : function () {},

/**
 * @method stopAction
 * @param {cocos2d::CCAction*}
 */
stopAction : function () {},

/**
 * @method getActionManager
 * @return A value converted from C/C++ "cocos2d::CCActionManager*"
 */
getActionManager : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
create : function () {},

/**
 * @method CCNode
 * @constructor
 */
CCNode : function () {},

};

/**
 * @class CCTexture2D
 */
cc.CCTexture2D = {

/**
 * @method getShaderProgram
 * @return A value converted from C/C++ "cocos2d::CCGLProgram*"
 */
getShaderProgram : function () {},

/**
 * @method getMaxT
 * @return A value converted from C/C++ "float"
 */
getMaxT : function () {},

/**
 * @method stringForFormat
 * @return A value converted from C/C++ "const char*"
 */
stringForFormat : function () {},

/**
 * @method initWithImage
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCImage*}
 */
initWithImage : function () {},

/**
 * @method setShaderProgram
 * @param {cocos2d::CCGLProgram*}
 */
setShaderProgram : function () {},

/**
 * @method getMaxS
 * @return A value converted from C/C++ "float"
 */
getMaxS : function () {},

/**
 * @method hasPremultipliedAlpha
 * @return A value converted from C/C++ "bool"
 */
hasPremultipliedAlpha : function () {},

/**
 * @method getPixelsHigh
 * @return A value converted from C/C++ "unsigned int"
 */
getPixelsHigh : function () {},

/**
 * @method getName
 * @return A value converted from C/C++ "unsigned int"
 */
getName : function () {},

/**
 * @method setMaxT
 * @param {float}
 */
setMaxT : function () {},

/**
 * @method drawInRect
 * @param {cocos2d::CCRect}
 */
drawInRect : function () {},

/**
 * @method getContentSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getContentSize : function () {},

/**
 * @method setAliasTexParameters
 */
setAliasTexParameters : function () {},

/**
 * @method setAntiAliasTexParameters
 */
setAntiAliasTexParameters : function () {},

/**
 * @method generateMipmap
 */
generateMipmap : function () {},

/**
 * @method getPixelFormat
 * @return A value converted from C/C++ "cocos2d::CCTexture2DPixelFormat"
 */
getPixelFormat : function () {},

/**
 * @method getContentSizeInPixels
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getContentSizeInPixels : function () {},

/**
 * @method getPixelsWide
 * @return A value converted from C/C++ "unsigned int"
 */
getPixelsWide : function () {},

/**
 * @method drawAtPoint
 * @param {cocos2d::CCPoint}
 */
drawAtPoint : function () {},

/**
 * @method hasMipmaps
 * @return A value converted from C/C++ "bool"
 */
hasMipmaps : function () {},

/**
 * @method initWithPVRFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
initWithPVRFile : function () {},

/**
 * @method setMaxS
 * @param {float}
 */
setMaxS : function () {},

/**
 * @method setDefaultAlphaPixelFormat
 * @param {cocos2d::CCTexture2DPixelFormat}
 */
setDefaultAlphaPixelFormat : function () {},

/**
 * @method defaultAlphaPixelFormat
 * @return A value converted from C/C++ "cocos2d::CCTexture2DPixelFormat"
 */
defaultAlphaPixelFormat : function () {},

/**
 * @method PVRImagesHavePremultipliedAlpha
 * @param {bool}
 */
PVRImagesHavePremultipliedAlpha : function () {},

/**
 * @method CCTexture2D
 * @constructor
 */
CCTexture2D : function () {},

};

/**
 * @class CCSpriteFrame
 */
cc.CCSpriteFrame = {

/**
 * @method setRotated
 * @param {bool}
 */
setRotated : function () {},

/**
 * @method setTexture
 * @param {cocos2d::CCTexture2D*}
 */
setTexture : function () {},

/**
 * @method getOffset
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getOffset : function () {},

/**
 * @method setRectInPixels
 * @param {cocos2d::CCRect}
 */
setRectInPixels : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::CCTexture2D*"
 */
getTexture : function () {},

/**
 * @method getRect
 * @return A value converted from C/C++ "cocos2d::CCRect"
 */
getRect : function () {},

/**
 * @method setOffsetInPixels
 * @param {cocos2d::CCPoint}
 */
setOffsetInPixels : function () {},

/**
 * @method getRectInPixels
 * @return A value converted from C/C++ "cocos2d::CCRect"
 */
getRectInPixels : function () {},

/**
 * @method setOriginalSize
 * @param {cocos2d::CCSize}
 */
setOriginalSize : function () {},

/**
 * @method getOriginalSizeInPixels
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getOriginalSizeInPixels : function () {},

/**
 * @method setOriginalSizeInPixels
 * @param {cocos2d::CCSize}
 */
setOriginalSizeInPixels : function () {},

/**
 * @method setOffset
 * @param {cocos2d::CCPoint}
 */
setOffset : function () {},

/**
 * @method isRotated
 * @return A value converted from C/C++ "bool"
 */
isRotated : function () {},

/**
 * @method setRect
 * @param {cocos2d::CCRect}
 */
setRect : function () {},

/**
 * @method getOffsetInPixels
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getOffsetInPixels : function () {},

/**
 * @method getOriginalSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getOriginalSize : function () {},

};

/**
 * @class CCAnimationFrame
 */
cc.CCAnimationFrame = {

/**
 * @method setSpriteFrame
 * @param {cocos2d::CCSpriteFrame*}
 */
setSpriteFrame : function () {},

/**
 * @method getUserInfo
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 */
getUserInfo : function () {},

/**
 * @method setDelayUnits
 * @param {float}
 */
setDelayUnits : function () {},

/**
 * @method getSpriteFrame
 * @return A value converted from C/C++ "cocos2d::CCSpriteFrame*"
 */
getSpriteFrame : function () {},

/**
 * @method getDelayUnits
 * @return A value converted from C/C++ "float"
 */
getDelayUnits : function () {},

/**
 * @method setUserInfo
 * @param {cocos2d::CCDictionary*}
 */
setUserInfo : function () {},

/**
 * @method initWithSpriteFrame
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCSpriteFrame*}
 * @param {float}
 * @param {cocos2d::CCDictionary*}
 */
initWithSpriteFrame : function () {},

/**
 * @method CCAnimationFrame
 * @constructor
 */
CCAnimationFrame : function () {},

};

/**
 * @class CCAnimation
 */
cc.CCAnimation = {

/**
 * @method getLoops
 * @return A value converted from C/C++ "unsigned int"
 */
getLoops : function () {},

/**
 * @method setFrames
 * @param {cocos2d::CCArray*}
 */
setFrames : function () {},

/**
 * @method getFrames
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getFrames : function () {},

/**
 * @method addSpriteFrame
 * @param {cocos2d::CCSpriteFrame*}
 */
addSpriteFrame : function () {},

/**
 * @method setRestoreOriginalFrame
 * @param {bool}
 */
setRestoreOriginalFrame : function () {},

/**
 * @method setDelayPerUnit
 * @param {float}
 */
setDelayPerUnit : function () {},

/**
 * @method initWithAnimationFrames
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCArray*}
 * @param {float}
 * @param {unsigned int}
 */
initWithAnimationFrames : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithSpriteFrames
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCArray*}
 * @param {float}
 */
initWithSpriteFrames : function () {},

/**
 * @method setLoops
 * @param {unsigned int}
 */
setLoops : function () {},

/**
 * @method addSpriteFrameWithFileName
 * @param {const char*}
 */
addSpriteFrameWithFileName : function () {},

/**
 * @method getTotalDelayUnits
 * @return A value converted from C/C++ "float"
 */
getTotalDelayUnits : function () {},

/**
 * @method getDelayPerUnit
 * @return A value converted from C/C++ "float"
 */
getDelayPerUnit : function () {},

/**
 * @method getRestoreOriginalFrame
 * @return A value converted from C/C++ "bool"
 */
getRestoreOriginalFrame : function () {},

/**
 * @method getDuration
 * @return A value converted from C/C++ "float"
 */
getDuration : function () {},

/**
 * @method addSpriteFrameWithTexture
 * @param {cocos2d::CCTexture2D*}
 * @param {cocos2d::CCRect}
 */
addSpriteFrameWithTexture : function () {},

/**
 * @method animationWithSpriteFrames
 * @return A value converted from C/C++ "cocos2d::CCAnimation*"
 * @param {cocos2d::CCArray*}
 * @param {float}
 */
animationWithSpriteFrames : function () {},

/**
 * @method animation
 * @return A value converted from C/C++ "cocos2d::CCAnimation*"
 */
animation : function () {},

/**
 * @method animationWithAnimationFrames
 * @return A value converted from C/C++ "cocos2d::CCAnimation*"
 * @param {cocos2d::CCArray*}
 * @param {float}
 * @param {unsigned int}
 */
animationWithAnimationFrames : function () {},

/**
 * @method CCAnimation
 * @constructor
 */
CCAnimation : function () {},

};

/**
 * @class CCActionInterval
 */
cc.CCActionInterval = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method setAmplitudeRate
 * @param {float}
 */
setAmplitudeRate : function () {},

/**
 * @method getAmplitudeRate
 * @return A value converted from C/C++ "float"
 */
getAmplitudeRate : function () {},

/**
 * @method step
 * @param {float}
 */
step : function () {},

/**
 * @method getElapsed
 * @return A value converted from C/C++ "float"
 */
getElapsed : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {float}
 */
actionWithDuration : function () {},

};

/**
 * @class CCSequence
 */
cc.CCSequence = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithTwoActions
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCFiniteTimeAction*}
 * @param {cocos2d::CCFiniteTimeAction*}
 */
initWithTwoActions : function () {},

/**
 * @method actionWithArray
 * @return A value converted from C/C++ "cocos2d::CCFiniteTimeAction*"
 * @param {cocos2d::CCArray*}
 */
actionWithArray : function () {},

/**
 * @method actionOneTwo
 * @return A value converted from C/C++ "cocos2d::CCSequence*"
 * @param {cocos2d::CCFiniteTimeAction*}
 * @param {cocos2d::CCFiniteTimeAction*}
 */
actionOneTwo : function () {},

};

/**
 * @class CCRepeat
 */
cc.CCRepeat = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method setInnerAction
 * @param {cocos2d::CCFiniteTimeAction*}
 */
setInnerAction : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithAction
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCFiniteTimeAction*}
 * @param {unsigned int}
 */
initWithAction : function () {},

/**
 * @method getInnerAction
 * @return A value converted from C/C++ "cocos2d::CCFiniteTimeAction*"
 */
getInnerAction : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCRepeat*"
 * @param {cocos2d::CCFiniteTimeAction*}
 * @param {unsigned int}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCRepeat*"
 * @param {cocos2d::CCFiniteTimeAction*}
 * @param {unsigned int}
 */
actionWithAction : function () {},

};

/**
 * @class CCRepeatForever
 */
cc.CCRepeatForever = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method setInnerAction
 * @param {cocos2d::CCActionInterval*}
 */
setInnerAction : function () {},

/**
 * @method step
 * @param {float}
 */
step : function () {},

/**
 * @method initWithAction
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCActionInterval*}
 */
initWithAction : function () {},

/**
 * @method getInnerAction
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
getInnerAction : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCRepeatForever*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCRepeatForever*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

/**
 * @method CCRepeatForever
 * @constructor
 */
CCRepeatForever : function () {},

};

/**
 * @class CCSpawn
 */
cc.CCSpawn = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithTwoActions
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCFiniteTimeAction*}
 * @param {cocos2d::CCFiniteTimeAction*}
 */
initWithTwoActions : function () {},

/**
 * @method actionWithArray
 * @return A value converted from C/C++ "cocos2d::CCFiniteTimeAction*"
 * @param {cocos2d::CCArray*}
 */
actionWithArray : function () {},

/**
 * @method actionOneTwo
 * @return A value converted from C/C++ "cocos2d::CCSpawn*"
 * @param {cocos2d::CCFiniteTimeAction*}
 * @param {cocos2d::CCFiniteTimeAction*}
 */
actionOneTwo : function () {},

};

/**
 * @class CCRotateTo
 */
cc.CCRotateTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCRotateTo*"
 * @param {float}
 * @param {float}
 */
actionWithDuration : function () {},

};

/**
 * @class CCRotateBy
 */
cc.CCRotateBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCRotateBy*"
 * @param {float}
 * @param {float}
 */
actionWithDuration : function () {},

};

/**
 * @class CCMoveTo
 */
cc.CCMoveTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::CCPoint}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCMoveTo*"
 * @param {float}
 * @param {cocos2d::CCPoint}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCMoveTo*"
 * @param {float}
 * @param {cocos2d::CCPoint}
 */
actionWithDuration : function () {},

};

/**
 * @class CCMoveBy
 */
cc.CCMoveBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::CCPoint}
 */
initWithDuration : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCMoveBy*"
 * @param {float}
 * @param {cocos2d::CCPoint}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCMoveBy*"
 * @param {float}
 * @param {cocos2d::CCPoint}
 */
actionWithDuration : function () {},

};

/**
 * @class CCSkewTo
 */
cc.CCSkewTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {float}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCSkewTo*"
 * @param {float}
 * @param {float}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCSkewTo*"
 * @param {float}
 * @param {float}
 * @param {float}
 */
actionWithDuration : function () {},

/**
 * @method CCSkewTo
 * @constructor
 */
CCSkewTo : function () {},

};

/**
 * @class CCSkewBy
 */
cc.CCSkewBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {float}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCSkewBy*"
 * @param {float}
 * @param {float}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCSkewBy*"
 * @param {float}
 * @param {float}
 * @param {float}
 */
actionWithDuration : function () {},

};

/**
 * @class CCJumpBy
 */
cc.CCJumpBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::CCPoint}
 * @param {float}
 * @param {unsigned int}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCJumpBy*"
 * @param {float}
 * @param {cocos2d::CCPoint}
 * @param {float}
 * @param {unsigned int}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCJumpBy*"
 * @param {float}
 * @param {cocos2d::CCPoint}
 * @param {float}
 * @param {unsigned int}
 */
actionWithDuration : function () {},

};

/**
 * @class CCJumpTo
 */
cc.CCJumpTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCJumpTo*"
 * @param {float}
 * @param {cocos2d::CCPoint}
 * @param {float}
 * @param {int}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCJumpTo*"
 * @param {float}
 * @param {cocos2d::CCPoint}
 * @param {float}
 * @param {int}
 */
actionWithDuration : function () {},

};

/**
 * @class CCBezierBy
 */
cc.CCBezierBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::ccBezierConfig}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

};

/**
 * @class CCBezierTo
 */
cc.CCBezierTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::ccBezierConfig}
 */
initWithDuration : function () {},

};

/**
 * @class CCScaleTo
 */
cc.CCScaleTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

};

/**
 * @class CCScaleBy
 */
cc.CCScaleBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

};

/**
 * @class CCBlink
 */
cc.CCBlink = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {unsigned int}
 */
initWithDuration : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCBlink*"
 * @param {float}
 * @param {unsigned int}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCBlink*"
 * @param {float}
 * @param {unsigned int}
 */
actionWithDuration : function () {},

};

/**
 * @class CCFadeIn
 */
cc.CCFadeIn = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCFadeIn*"
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCFadeIn*"
 * @param {float}
 */
actionWithDuration : function () {},

};

/**
 * @class CCFadeOut
 */
cc.CCFadeOut = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCFadeOut*"
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCFadeOut*"
 * @param {float}
 */
actionWithDuration : function () {},

};

/**
 * @class CCFadeTo
 */
cc.CCFadeTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {unsigned char}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCFadeTo*"
 * @param {float}
 * @param {unsigned char}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCFadeTo*"
 * @param {float}
 * @param {unsigned char}
 */
actionWithDuration : function () {},

};

/**
 * @class CCTintTo
 */
cc.CCTintTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {unsigned char}
 * @param {unsigned char}
 * @param {unsigned char}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTintTo*"
 * @param {float}
 * @param {unsigned char}
 * @param {unsigned char}
 * @param {unsigned char}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTintTo*"
 * @param {float}
 * @param {unsigned char}
 * @param {unsigned char}
 * @param {unsigned char}
 */
actionWithDuration : function () {},

};

/**
 * @class CCTintBy
 */
cc.CCTintBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {short}
 * @param {short}
 * @param {short}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTintBy*"
 * @param {float}
 * @param {short}
 * @param {short}
 * @param {short}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTintBy*"
 * @param {float}
 * @param {short}
 * @param {short}
 * @param {short}
 */
actionWithDuration : function () {},

};

/**
 * @class CCDelayTime
 */
cc.CCDelayTime = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCDelayTime*"
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCDelayTime*"
 * @param {float}
 */
actionWithDuration : function () {},

};

/**
 * @class CCAnimate
 */
cc.CCAnimate = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method getAnimation
 * @return A value converted from C/C++ "cocos2d::CCAnimation*"
 */
getAnimation : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithAnimation
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCAnimation*}
 */
initWithAnimation : function () {},

/**
 * @method setAnimation
 * @param {cocos2d::CCAnimation*}
 */
setAnimation : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCAnimate*"
 * @param {cocos2d::CCAnimation*}
 */
create : function () {},

/**
 * @method actionWithAnimation
 * @return A value converted from C/C++ "cocos2d::CCAnimate*"
 * @param {cocos2d::CCAnimation*}
 */
actionWithAnimation : function () {},

/**
 * @method CCAnimate
 * @constructor
 */
CCAnimate : function () {},

};

/**
 * @class CCTargetedAction
 */
cc.CCTargetedAction = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method setForcedTarget
 * @param {cocos2d::CCNode*}
 */
setForcedTarget : function () {},

/**
 * @method initWithTarget
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCNode*}
 * @param {cocos2d::CCFiniteTimeAction*}
 */
initWithTarget : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getForcedTarget
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
getForcedTarget : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTargetedAction*"
 * @param {cocos2d::CCNode*}
 * @param {cocos2d::CCFiniteTimeAction*}
 */
create : function () {},

/**
 * @method actionWithTarget
 * @return A value converted from C/C++ "cocos2d::CCTargetedAction*"
 * @param {cocos2d::CCNode*}
 * @param {cocos2d::CCFiniteTimeAction*}
 */
actionWithTarget : function () {},

/**
 * @method CCTargetedAction
 * @constructor
 */
CCTargetedAction : function () {},

};

/**
 * @class CCActionCamera
 */
cc.CCActionCamera = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method CCActionCamera
 * @constructor
 */
CCActionCamera : function () {},

};

/**
 * @class CCOrbitCamera
 */
cc.CCOrbitCamera = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method sphericalRadius
 * @param {float*}
 * @param {float*}
 * @param {float*}
 */
sphericalRadius : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCOrbitCamera*"
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCOrbitCamera*"
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 */
actionWithDuration : function () {},

/**
 * @method CCOrbitCamera
 * @constructor
 */
CCOrbitCamera : function () {},

};

/**
 * @class CCActionManager
 */
cc.CCActionManager = {

/**
 * @method getActionByTag
 * @return A value converted from C/C++ "cocos2d::CCAction*"
 * @param {unsigned int}
 * @param {cocos2d::CCObject*}
 */
getActionByTag : function () {},

/**
 * @method removeActionByTag
 * @param {unsigned int}
 * @param {cocos2d::CCObject*}
 */
removeActionByTag : function () {},

/**
 * @method removeAllActions
 */
removeAllActions : function () {},

/**
 * @method addAction
 * @param {cocos2d::CCAction*}
 * @param {cocos2d::CCNode*}
 * @param {bool}
 */
addAction : function () {},

/**
 * @method resumeTarget
 * @param {cocos2d::CCObject*}
 */
resumeTarget : function () {},

/**
 * @method pauseTarget
 * @param {cocos2d::CCObject*}
 */
pauseTarget : function () {},

/**
 * @method removeAllActionsFromTarget
 * @param {cocos2d::CCObject*}
 */
removeAllActionsFromTarget : function () {},

/**
 * @method resumeTargets
 * @param {cocos2d::CCSet*}
 */
resumeTargets : function () {},

/**
 * @method removeAction
 * @param {cocos2d::CCAction*}
 */
removeAction : function () {},

/**
 * @method numberOfRunningActionsInTarget
 * @return A value converted from C/C++ "unsigned int"
 * @param {cocos2d::CCObject*}
 */
numberOfRunningActionsInTarget : function () {},

/**
 * @method pauseAllRunningActions
 * @return A value converted from C/C++ "cocos2d::CCSet*"
 */
pauseAllRunningActions : function () {},

/**
 * @method CCActionManager
 * @constructor
 */
CCActionManager : function () {},

};

/**
 * @class CCActionEase
 */
cc.CCActionEase = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithAction
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCActionInterval*}
 */
initWithAction : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCActionEase*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCActionEase*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseRateAction
 */
cc.CCEaseRateAction = {

/**
 * @method setRate
 * @param {float}
 */
setRate : function () {},

/**
 * @method initWithAction
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
initWithAction : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method getRate
 * @return A value converted from C/C++ "float"
 */
getRate : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseRateAction*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseRateAction*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseIn
 */
cc.CCEaseIn = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseIn*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseIn*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseOut
 */
cc.CCEaseOut = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseOut*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseOut*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseInOut
 */
cc.CCEaseInOut = {

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseInOut*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseInOut*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseExponentialIn
 */
cc.CCEaseExponentialIn = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseExponentialIn*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseExponentialIn*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseExponentialOut
 */
cc.CCEaseExponentialOut = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseExponentialOut*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseExponentialOut*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseExponentialInOut
 */
cc.CCEaseExponentialInOut = {

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseExponentialInOut*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseExponentialInOut*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseSineIn
 */
cc.CCEaseSineIn = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseSineIn*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseSineIn*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseSineOut
 */
cc.CCEaseSineOut = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseSineOut*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseSineOut*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseSineInOut
 */
cc.CCEaseSineInOut = {

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseSineInOut*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseSineInOut*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseElastic
 */
cc.CCEaseElastic = {

/**
 * @method setPeriod
 * @param {float}
 */
setPeriod : function () {},

/**
 * @method initWithAction
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
initWithAction : function () {},

/**
 * @method getPeriod
 * @return A value converted from C/C++ "float"
 */
getPeriod : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseElastic*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseElasticIn
 */
cc.CCEaseElasticIn = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseElasticIn*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseElasticOut
 */
cc.CCEaseElasticOut = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseElasticOut*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseElasticInOut
 */
cc.CCEaseElasticInOut = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseElasticInOut*"
 * @param {cocos2d::CCActionInterval*}
 * @param {float}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseBounce
 */
cc.CCEaseBounce = {

/**
 * @method bounceTime
 * @return A value converted from C/C++ "float"
 * @param {float}
 */
bounceTime : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseBounce*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseBounce*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseBounceIn
 */
cc.CCEaseBounceIn = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseBounceIn*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseBounceIn*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseBounceOut
 */
cc.CCEaseBounceOut = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseBounceOut*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseBounceOut*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseBounceInOut
 */
cc.CCEaseBounceInOut = {

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseBounceInOut*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseBounceInOut*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseBackIn
 */
cc.CCEaseBackIn = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseBackIn*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseBackIn*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseBackOut
 */
cc.CCEaseBackOut = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseBackOut*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseBackOut*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCEaseBackInOut
 */
cc.CCEaseBackInOut = {

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCEaseBackInOut*"
 * @param {cocos2d::CCActionInterval*}
 */
create : function () {},

/**
 * @method actionWithAction
 * @return A value converted from C/C++ "cocos2d::CCEaseBackInOut*"
 * @param {cocos2d::CCActionInterval*}
 */
actionWithAction : function () {},

};

/**
 * @class CCActionInstant
 */
cc.CCActionInstant = {

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCFiniteTimeAction*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method step
 * @param {float}
 */
step : function () {},

/**
 * @method isDone
 * @return A value converted from C/C++ "bool"
 */
isDone : function () {},

/**
 * @method CCActionInstant
 * @constructor
 */
CCActionInstant : function () {},

};

/**
 * @class CCShow
 */
cc.CCShow = {

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCFiniteTimeAction*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::CCShow*"
 */
action : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCShow*"
 */
create : function () {},

/**
 * @method CCShow
 * @constructor
 */
CCShow : function () {},

};

/**
 * @class CCHide
 */
cc.CCHide = {

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCFiniteTimeAction*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::CCHide*"
 */
action : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCHide*"
 */
create : function () {},

/**
 * @method CCHide
 * @constructor
 */
CCHide : function () {},

};

/**
 * @class CCToggleVisibility
 */
cc.CCToggleVisibility = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::CCToggleVisibility*"
 */
action : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCToggleVisibility*"
 */
create : function () {},

/**
 * @method CCToggleVisibility
 * @constructor
 */
CCToggleVisibility : function () {},

};

/**
 * @class CCFlipX
 */
cc.CCFlipX = {

/**
 * @method initWithFlipX
 * @return A value converted from C/C++ "bool"
 * @param {bool}
 */
initWithFlipX : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCFiniteTimeAction*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method actionWithFlipX
 * @return A value converted from C/C++ "cocos2d::CCFlipX*"
 * @param {bool}
 */
actionWithFlipX : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCFlipX*"
 * @param {bool}
 */
create : function () {},

/**
 * @method CCFlipX
 * @constructor
 */
CCFlipX : function () {},

};

/**
 * @class CCFlipY
 */
cc.CCFlipY = {

/**
 * @method initWithFlipY
 * @return A value converted from C/C++ "bool"
 * @param {bool}
 */
initWithFlipY : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCFiniteTimeAction*"
 */
reverse : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCFlipY*"
 * @param {bool}
 */
create : function () {},

/**
 * @method actionWithFlipY
 * @return A value converted from C/C++ "cocos2d::CCFlipY*"
 * @param {bool}
 */
actionWithFlipY : function () {},

/**
 * @method CCFlipY
 * @constructor
 */
CCFlipY : function () {},

};

/**
 * @class CCPlace
 */
cc.CCPlace = {

/**
 * @method initWithPosition
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCPoint}
 */
initWithPosition : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method actionWithPosition
 * @return A value converted from C/C++ "cocos2d::CCPlace*"
 * @param {cocos2d::CCPoint}
 */
actionWithPosition : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCPlace*"
 * @param {cocos2d::CCPoint}
 */
create : function () {},

/**
 * @method CCPlace
 * @constructor
 */
CCPlace : function () {},

};

/**
 * @class CCCallFunc
 */
cc.CCCallFunc = {

/**
 * @method execute
 */
execute : function () {},

/**
 * @method initWithTarget
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCObject*}
 */
initWithTarget : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getTargetCallback
 * @return A value converted from C/C++ "cocos2d::CCObject*"
 */
getTargetCallback : function () {},

/**
 * @method getScriptHandler
 * @return A value converted from C/C++ "int"
 */
getScriptHandler : function () {},

/**
 * @method setTargetCallback
 * @param {cocos2d::CCObject*}
 */
setTargetCallback : function () {},

/**
 * @method CCCallFunc
 * @constructor
 */
CCCallFunc : function () {},

};

/**
 * @class CCGridAction
 */
cc.CCGridAction = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method initWithSize
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
initWithSize : function () {},

/**
 * @method getGrid
 * @return A value converted from C/C++ "cocos2d::CCGridBase*"
 */
getGrid : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCGridAction*"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::CCGridAction*"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
actionWithSize : function () {},

};

/**
 * @class CCGrid3DAction
 */
cc.CCGrid3DAction = {

/**
 * @method setVertex
 * @param {cocos2d::ccGridSize}
 * @param {cocos2d::ccVertex3F}
 */
setVertex : function () {},

/**
 * @method getGrid
 * @return A value converted from C/C++ "cocos2d::CCGridBase*"
 */
getGrid : function () {},

/**
 * @method vertex
 * @return A value converted from C/C++ "ccVertex3F"
 * @param {cocos2d::ccGridSize}
 */
vertex : function () {},

/**
 * @method originalVertex
 * @return A value converted from C/C++ "ccVertex3F"
 * @param {cocos2d::ccGridSize}
 */
originalVertex : function () {},

};

/**
 * @class CCTiledGrid3DAction
 */
cc.CCTiledGrid3DAction = {

/**
 * @method tile
 * @return A value converted from C/C++ "ccQuad3"
 * @param {cocos2d::ccGridSize}
 */
tile : function () {},

/**
 * @method setTile
 * @param {cocos2d::ccGridSize}
 * @param {cocos2d::ccQuad3}
 */
setTile : function () {},

/**
 * @method originalTile
 * @return A value converted from C/C++ "ccQuad3"
 * @param {cocos2d::ccGridSize}
 */
originalTile : function () {},

/**
 * @method getGrid
 * @return A value converted from C/C++ "cocos2d::CCGridBase*"
 */
getGrid : function () {},

};

/**
 * @class CCWaves3D
 */
cc.CCWaves3D = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getAmplitudeRate
 * @return A value converted from C/C++ "float"
 */
getAmplitudeRate : function () {},

/**
 * @method setAmplitude
 * @param {float}
 */
setAmplitude : function () {},

/**
 * @method getAmplitude
 * @return A value converted from C/C++ "float"
 */
getAmplitude : function () {},

/**
 * @method initWithWaves
 * @return A value converted from C/C++ "bool"
 * @param {int}
 * @param {float}
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
initWithWaves : function () {},

/**
 * @method setAmplitudeRate
 * @param {float}
 */
setAmplitudeRate : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCWaves3D*"
 * @param {int}
 * @param {float}
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithWaves
 * @return A value converted from C/C++ "cocos2d::CCWaves3D*"
 * @param {int}
 * @param {float}
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
actionWithWaves : function () {},

};

/**
 * @class CCFlipX3D
 */
cc.CCFlipX3D = {

/**
 * @method initWithSize
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
initWithSize : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCFlipX3D*"
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCFlipX3D*"
 * @param {float}
 */
actionWithDuration : function () {},

};

/**
 * @class CCFlipY3D
 */
cc.CCFlipY3D = {

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCFlipY3D*"
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCFlipY3D*"
 * @param {float}
 */
actionWithDuration : function () {},

};

/**
 * @class CCShaky3D
 */
cc.CCShaky3D = {

/**
 * @method initWithRange
 * @return A value converted from C/C++ "bool"
 * @param {int}
 * @param {bool}
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
initWithRange : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCShaky3D*"
 * @param {int}
 * @param {bool}
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithRange
 * @return A value converted from C/C++ "cocos2d::CCShaky3D*"
 * @param {int}
 * @param {bool}
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
actionWithRange : function () {},

};

/**
 * @class CCProgressTo
 */
cc.CCProgressTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCProgressTo*"
 * @param {float}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCProgressTo*"
 * @param {float}
 * @param {float}
 */
actionWithDuration : function () {},

};

/**
 * @class CCProgressFromTo
 */
cc.CCProgressFromTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {float}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCProgressFromTo*"
 * @param {float}
 * @param {float}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCProgressFromTo*"
 * @param {float}
 * @param {float}
 * @param {float}
 */
actionWithDuration : function () {},

};

/**
 * @class CCFadeOutTRTiles
 */
cc.CCFadeOutTRTiles = {

/**
 * @method turnOnTile
 * @param {cocos2d::ccGridSize}
 */
turnOnTile : function () {},

/**
 * @method turnOffTile
 * @param {cocos2d::ccGridSize}
 */
turnOffTile : function () {},

/**
 * @method transformTile
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
transformTile : function () {},

/**
 * @method testFunc
 * @return A value converted from C/C++ "float"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
testFunc : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCFadeOutTRTiles*"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::CCFadeOutTRTiles*"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
actionWithSize : function () {},

};

/**
 * @class CCFadeOutBLTiles
 */
cc.CCFadeOutBLTiles = {

/**
 * @method testFunc
 * @return A value converted from C/C++ "float"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
testFunc : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCFadeOutBLTiles*"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::CCFadeOutBLTiles*"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
actionWithSize : function () {},

};

/**
 * @class CCFadeOutUpTiles
 */
cc.CCFadeOutUpTiles = {

/**
 * @method transformTile
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
transformTile : function () {},

/**
 * @method testFunc
 * @return A value converted from C/C++ "float"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
testFunc : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCFadeOutUpTiles*"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::CCFadeOutUpTiles*"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
actionWithSize : function () {},

};

/**
 * @class CCFadeOutDownTiles
 */
cc.CCFadeOutDownTiles = {

/**
 * @method testFunc
 * @return A value converted from C/C++ "float"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
testFunc : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCFadeOutDownTiles*"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::CCFadeOutDownTiles*"
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
actionWithSize : function () {},

};

/**
 * @class CCJumpTiles3D
 */
cc.CCJumpTiles3D = {

/**
 * @method setAmplitudeRate
 * @param {float}
 */
setAmplitudeRate : function () {},

/**
 * @method initWithJumps
 * @return A value converted from C/C++ "bool"
 * @param {int}
 * @param {float}
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
initWithJumps : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getAmplitudeRate
 * @return A value converted from C/C++ "float"
 */
getAmplitudeRate : function () {},

/**
 * @method setAmplitude
 * @param {float}
 */
setAmplitude : function () {},

/**
 * @method getAmplitude
 * @return A value converted from C/C++ "float"
 */
getAmplitude : function () {},

/**
 * @method actionWithJumps
 * @return A value converted from C/C++ "cocos2d::CCJumpTiles3D*"
 * @param {int}
 * @param {float}
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
actionWithJumps : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCJumpTiles3D*"
 * @param {int}
 * @param {float}
 * @param {cocos2d::ccGridSize}
 * @param {float}
 */
create : function () {},

};

/**
 * @class CCActionTween
 */
cc.CCActionTween = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {const char*}
 * @param {float}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCActionTween*"
 * @param {float}
 * @param {const char*}
 * @param {float}
 * @param {float}
 */
create : function () {},

/**
 * @method actionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCActionTween*"
 * @param {float}
 * @param {const char*}
 * @param {float}
 * @param {float}
 */
actionWithDuration : function () {},

};

/**
 * @class CCPointArray
 */
cc.CCPointArray = {

/**
 * @method count
 * @return A value converted from C/C++ "unsigned int"
 */
count : function () {},

/**
 * @method insertControlPoint
 * @param {cocos2d::CCPoint}
 * @param {unsigned int}
 */
insertControlPoint : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCPointArray*"
 */
reverse : function () {},

/**
 * @method initWithCapacity
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithCapacity : function () {},

/**
 * @method removeControlPointAtIndex
 * @param {unsigned int}
 */
removeControlPointAtIndex : function () {},

/**
 * @method setControlPoints
 * @param {cocos2d::CCArray*}
 */
setControlPoints : function () {},

/**
 * @method replaceControlPoint
 * @param {cocos2d::CCPoint}
 * @param {unsigned int}
 */
replaceControlPoint : function () {},

/**
 * @method addControlPoint
 * @param {cocos2d::CCPoint}
 */
addControlPoint : function () {},

/**
 * @method getControlPointAtIndex
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 * @param {unsigned int}
 */
getControlPointAtIndex : function () {},

/**
 * @method reverseInline
 */
reverseInline : function () {},

/**
 * @method getControlPoints
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getControlPoints : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCPointArray*"
 * @param {unsigned int}
 */
create : function () {},

/**
 * @method arrayWithCapacity
 * @return A value converted from C/C++ "cocos2d::CCPointArray*"
 * @param {unsigned int}
 */
arrayWithCapacity : function () {},

/**
 * @method CCPointArray
 * @constructor
 */
CCPointArray : function () {},

};

/**
 * @class CCCardinalSplineTo
 */
cc.CCCardinalSplineTo = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::CCPointArray*}
 * @param {float}
 */
initWithDuration : function () {},

/**
 * @method getPoints
 * @return A value converted from C/C++ "cocos2d::CCPointArray*"
 */
getPoints : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method updatePosition
 * @param {cocos2d::CCPoint}
 */
updatePosition : function () {},

/**
 * @method CCCardinalSplineTo
 * @constructor
 */
CCCardinalSplineTo : function () {},

};

/**
 * @class CCCardinalSplineBy
 */
cc.CCCardinalSplineBy = {

/**
 * @method startWithTarget
 * @param {cocos2d::CCNode*}
 */
startWithTarget : function () {},

/**
 * @method updatePosition
 * @param {cocos2d::CCPoint}
 */
updatePosition : function () {},

/**
 * @method reverse
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
reverse : function () {},

/**
 * @method CCCardinalSplineBy
 * @constructor
 */
CCCardinalSplineBy : function () {},

};

/**
 * @class CCCatmullRomTo
 */
cc.CCCatmullRomTo = {

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::CCPointArray*}
 */
initWithDuration : function () {},

};

/**
 * @class CCCatmullRomBy
 */
cc.CCCatmullRomBy = {

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::CCPointArray*}
 */
initWithDuration : function () {},

};

/**
 * @class CCAtlasNode
 */
cc.CCAtlasNode = {

/**
 * @method setTexture
 * @param {cocos2d::CCTexture2D*}
 */
setTexture : function () {},

/**
 * @method draw
 */
draw : function () {},

/**
 * @method setColor
 * @param {cocos2d::ccColor3B}
 */
setColor : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::CCTexture2D*"
 */
getTexture : function () {},

/**
 * @method setTextureAtlas
 * @param {cocos2d::CCTextureAtlas*}
 */
setTextureAtlas : function () {},

/**
 * @method getTextureAtlas
 * @return A value converted from C/C++ "cocos2d::CCTextureAtlas*"
 */
getTextureAtlas : function () {},

/**
 * @method getQuadsToDraw
 * @return A value converted from C/C++ "unsigned int"
 */
getQuadsToDraw : function () {},

/**
 * @method updateAtlasValues
 */
updateAtlasValues : function () {},

/**
 * @method initWithTileFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {unsigned int}
 * @param {unsigned int}
 * @param {unsigned int}
 */
initWithTileFile : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getColor : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method setQuadsToDraw
 * @param {unsigned int}
 */
setQuadsToDraw : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCAtlasNode*"
 * @param {const char*}
 * @param {unsigned int}
 * @param {unsigned int}
 * @param {unsigned int}
 */
create : function () {},

/**
 * @method atlasWithTileFile
 * @return A value converted from C/C++ "cocos2d::CCAtlasNode*"
 * @param {const char*}
 * @param {unsigned int}
 * @param {unsigned int}
 * @param {unsigned int}
 */
atlasWithTileFile : function () {},

/**
 * @method CCAtlasNode
 * @constructor
 */
CCAtlasNode : function () {},

};

/**
 * @class CCDrawNode
 */
cc.CCDrawNode = {

/**
 * @method draw
 */
draw : function () {},

/**
 * @method clear
 */
clear : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method drawDot
 * @param {cocos2d::CCPoint}
 * @param {float}
 * @param {cocos2d::ccColor4F}
 */
drawDot : function () {},

/**
 * @method drawSegment
 * @param {cocos2d::CCPoint}
 * @param {cocos2d::CCPoint}
 * @param {float}
 * @param {cocos2d::ccColor4F}
 */
drawSegment : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCDrawNode*"
 */
create : function () {},

/**
 * @method CCDrawNode
 * @constructor
 */
CCDrawNode : function () {},

};

/**
 * @class CCCamera
 */
cc.CCCamera = {

/**
 * @method locate
 */
locate : function () {},

/**
 * @method restore
 */
restore : function () {},

/**
 * @method setUpXYZ
 * @param {float}
 * @param {float}
 * @param {float}
 */
setUpXYZ : function () {},

/**
 * @method setCenterXYZ
 * @param {float}
 * @param {float}
 * @param {float}
 */
setCenterXYZ : function () {},

/**
 * @method setEyeXYZ
 * @param {float}
 * @param {float}
 * @param {float}
 */
setEyeXYZ : function () {},

/**
 * @method getCenterXYZ
 * @param {float*}
 * @param {float*}
 * @param {float*}
 */
getCenterXYZ : function () {},

/**
 * @method getEyeXYZ
 * @param {float*}
 * @param {float*}
 * @param {float*}
 */
getEyeXYZ : function () {},

/**
 * @method isDirty
 * @return A value converted from C/C++ "bool"
 */
isDirty : function () {},

/**
 * @method init
 */
init : function () {},

/**
 * @method getUpXYZ
 * @param {float*}
 * @param {float*}
 * @param {float*}
 */
getUpXYZ : function () {},

/**
 * @method setDirty
 * @param {bool}
 */
setDirty : function () {},

/**
 * @method getZEye
 * @return A value converted from C/C++ "float"
 */
getZEye : function () {},

/**
 * @method CCCamera
 * @constructor
 */
CCCamera : function () {},

};

/**
 * @class CCSprite
 */
cc.CCSprite = {

/**
 * @method setDirtyRecursively
 * @param {bool}
 */
setDirtyRecursively : function () {},

/**
 * @method setTexture
 * @param {cocos2d::CCTexture2D*}
 */
setTexture : function () {},

/**
 * @method setAnchorPoint
 * @param {cocos2d::CCPoint}
 */
setAnchorPoint : function () {},

/**
 * @method setScaleX
 * @param {float}
 */
setScaleX : function () {},

/**
 * @method setRotationX
 * @param {float}
 */
setRotationX : function () {},

/**
 * @method setScale
 * @param {float}
 */
setScale : function () {},

/**
 * @method setDisplayFrameWithAnimationName
 * @param {const char*}
 * @param {int}
 */
setDisplayFrameWithAnimationName : function () {},

/**
 * @method setRotationY
 * @param {float}
 */
setRotationY : function () {},

/**
 * @method getBatchNode
 * @return A value converted from C/C++ "cocos2d::CCSpriteBatchNode*"
 */
getBatchNode : function () {},

/**
 * @method getOffsetPosition
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getOffsetPosition : function () {},

/**
 * @method setScaleY
 * @param {float}
 */
setScaleY : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::CCTexture2D*"
 */
getTexture : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method setVertexZ
 * @param {float}
 */
setVertexZ : function () {},

/**
 * @method reorderChild
 * @param {cocos2d::CCNode*}
 * @param {int}
 */
reorderChild : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method isFrameDisplayed
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCSpriteFrame*}
 */
isFrameDisplayed : function () {},

/**
 * @method getAtlasIndex
 * @return A value converted from C/C++ "unsigned int"
 */
getAtlasIndex : function () {},

/**
 * @method setTextureAtlas
 * @param {cocos2d::CCTextureAtlas*}
 */
setTextureAtlas : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method setDisplayFrame
 * @param {cocos2d::CCSpriteFrame*}
 */
setDisplayFrame : function () {},

/**
 * @method setBatchNode
 * @param {cocos2d::CCSpriteBatchNode*}
 */
setBatchNode : function () {},

/**
 * @method initWithSpriteFrameName
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
initWithSpriteFrameName : function () {},

/**
 * @method draw
 */
draw : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getColor : function () {},

/**
 * @method setFlipY
 * @param {bool}
 */
setFlipY : function () {},

/**
 * @method removeAllChildrenWithCleanup
 * @param {bool}
 */
removeAllChildrenWithCleanup : function () {},

/**
 * @method isDirty
 * @return A value converted from C/C++ "bool"
 */
isDirty : function () {},

/**
 * @method setAtlasIndex
 * @param {unsigned int}
 */
setAtlasIndex : function () {},

/**
 * @method setRotation
 * @param {float}
 */
setRotation : function () {},

/**
 * @method setDirty
 * @param {bool}
 */
setDirty : function () {},

/**
 * @method isTextureRectRotated
 * @return A value converted from C/C++ "bool"
 */
isTextureRectRotated : function () {},

/**
 * @method sortAllChildren
 */
sortAllChildren : function () {},

/**
 * @method getTextureRect
 * @return A value converted from C/C++ "cocos2d::CCRect"
 */
getTextureRect : function () {},

/**
 * @method ignoreAnchorPointForPosition
 * @param {bool}
 */
ignoreAnchorPointForPosition : function () {},

/**
 * @method setColor
 * @param {cocos2d::ccColor3B}
 */
setColor : function () {},

/**
 * @method updateTransform
 */
updateTransform : function () {},

/**
 * @method setFlipX
 * @param {bool}
 */
setFlipX : function () {},

/**
 * @method updateColor
 */
updateColor : function () {},

/**
 * @method getTextureAtlas
 * @return A value converted from C/C++ "cocos2d::CCTextureAtlas*"
 */
getTextureAtlas : function () {},

/**
 * @method initWithSpriteFrame
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCSpriteFrame*}
 */
initWithSpriteFrame : function () {},

/**
 * @method removeChild
 * @param {cocos2d::CCNode*}
 * @param {bool}
 */
removeChild : function () {},

/**
 * @method isFlipX
 * @return A value converted from C/C++ "bool"
 */
isFlipX : function () {},

/**
 * @method isFlipY
 * @return A value converted from C/C++ "bool"
 */
isFlipY : function () {},

/**
 * @method setVertexRect
 * @param {cocos2d::CCRect}
 */
setVertexRect : function () {},

/**
 * @method setSkewX
 * @param {float}
 */
setSkewX : function () {},

/**
 * @method setSkewY
 * @param {float}
 */
setSkewY : function () {},

/**
 * @method setVisible
 * @param {bool}
 */
setVisible : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCSprite*"
 */
node : function () {},

/**
 * @method spriteWithSpriteFrame
 * @return A value converted from C/C++ "cocos2d::CCSprite*"
 * @param {cocos2d::CCSpriteFrame*}
 */
spriteWithSpriteFrame : function () {},

/**
 * @method spriteWithSpriteFrameName
 * @return A value converted from C/C++ "cocos2d::CCSprite*"
 * @param {const char*}
 */
spriteWithSpriteFrameName : function () {},

/**
 * @method createWithSpriteFrameName
 * @return A value converted from C/C++ "cocos2d::CCSprite*"
 * @param {const char*}
 */
createWithSpriteFrameName : function () {},

/**
 * @method createWithSpriteFrame
 * @return A value converted from C/C++ "cocos2d::CCSprite*"
 * @param {cocos2d::CCSpriteFrame*}
 */
createWithSpriteFrame : function () {},

/**
 * @method CCSprite
 * @constructor
 */
CCSprite : function () {},

};

/**
 * @class CCLabelTTF
 */
cc.CCLabelTTF = {

/**
 * @method setFontName
 * @param {const char*}
 */
setFontName : function () {},

/**
 * @method setDimensions
 * @param {cocos2d::CCSize}
 */
setDimensions : function () {},

/**
 * @method getFontSize
 * @return A value converted from C/C++ "float"
 */
getFontSize : function () {},

/**
 * @method getString
 * @return A value converted from C/C++ "const char*"
 */
getString : function () {},

/**
 * @method setVerticalAlignment
 * @param {cocos2d::CCVerticalTextAlignment}
 */
setVerticalAlignment : function () {},

/**
 * @method getFontName
 * @return A value converted from C/C++ "const char*"
 */
getFontName : function () {},

/**
 * @method setString
 * @param {const char*}
 */
setString : function () {},

/**
 * @method getDimensions
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getDimensions : function () {},

/**
 * @method setFontSize
 * @param {float}
 */
setFontSize : function () {},

/**
 * @method setHorizontalAlignment
 * @param {cocos2d::CCTextAlignment}
 */
setHorizontalAlignment : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method getVerticalAlignment
 * @return A value converted from C/C++ "cocos2d::CCVerticalTextAlignment"
 */
getVerticalAlignment : function () {},

/**
 * @method getHorizontalAlignment
 * @return A value converted from C/C++ "cocos2d::CCTextAlignment"
 */
getHorizontalAlignment : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCLabelTTF*"
 */
node : function () {},

/**
 * @method CCLabelTTF
 * @constructor
 */
CCLabelTTF : function () {},

};

/**
 * @class CCDirector
 */
cc.CCDirector = {

/**
 * @method pause
 */
pause : function () {},

/**
 * @method setDelegate
 * @param {cocos2d::CCDirectorDelegate*}
 */
setDelegate : function () {},

/**
 * @method setContentScaleFactor
 * @param {float}
 */
setContentScaleFactor : function () {},

/**
 * @method getContentScaleFactor
 * @return A value converted from C/C++ "float"
 */
getContentScaleFactor : function () {},

/**
 * @method getWinSizeInPixels
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getWinSizeInPixels : function () {},

/**
 * @method setKeypadDispatcher
 * @param {cocos2d::CCKeypadDispatcher*}
 */
setKeypadDispatcher : function () {},

/**
 * @method setActionManager
 * @param {cocos2d::CCActionManager*}
 */
setActionManager : function () {},

/**
 * @method setAlphaBlending
 * @param {bool}
 */
setAlphaBlending : function () {},

/**
 * @method popToRootScene
 */
popToRootScene : function () {},

/**
 * @method getNotificationNode
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
getNotificationNode : function () {},

/**
 * @method getWinSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getWinSize : function () {},

/**
 * @method end
 */
end : function () {},

/**
 * @method isSendCleanupToScene
 * @return A value converted from C/C++ "bool"
 */
isSendCleanupToScene : function () {},

/**
 * @method getVisibleOrigin
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getVisibleOrigin : function () {},

/**
 * @method mainLoop
 */
mainLoop : function () {},

/**
 * @method setDepthTest
 * @param {bool}
 */
setDepthTest : function () {},

/**
 * @method getSecondsPerFrame
 * @return A value converted from C/C++ "float"
 */
getSecondsPerFrame : function () {},

/**
 * @method convertToUI
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 * @param {cocos2d::CCPoint}
 */
convertToUI : function () {},

/**
 * @method setAccelerometer
 * @param {cocos2d::CCAccelerometer*}
 */
setAccelerometer : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setScheduler
 * @param {cocos2d::CCScheduler*}
 */
setScheduler : function () {},

/**
 * @method startAnimation
 */
startAnimation : function () {},

/**
 * @method getRunningScene
 * @return A value converted from C/C++ "cocos2d::CCScene*"
 */
getRunningScene : function () {},

/**
 * @method stopAnimation
 */
stopAnimation : function () {},

/**
 * @method setGLDefaultValues
 */
setGLDefaultValues : function () {},

/**
 * @method resume
 */
resume : function () {},

/**
 * @method setTouchDispatcher
 * @param {cocos2d::CCTouchDispatcher*}
 */
setTouchDispatcher : function () {},

/**
 * @method isNextDeltaTimeZero
 * @return A value converted from C/C++ "bool"
 */
isNextDeltaTimeZero : function () {},

/**
 * @method getDelegate
 * @return A value converted from C/C++ "cocos2d::CCDirectorDelegate*"
 */
getDelegate : function () {},

/**
 * @method setOpenGLView
 * @param {cocos2d::CCEGLView*}
 */
setOpenGLView : function () {},

/**
 * @method convertToGL
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 * @param {cocos2d::CCPoint}
 */
convertToGL : function () {},

/**
 * @method purgeCachedData
 */
purgeCachedData : function () {},

/**
 * @method getTotalFrames
 * @return A value converted from C/C++ "unsigned int"
 */
getTotalFrames : function () {},

/**
 * @method runWithScene
 * @param {cocos2d::CCScene*}
 */
runWithScene : function () {},

/**
 * @method setNotificationNode
 * @param {cocos2d::CCNode*}
 */
setNotificationNode : function () {},

/**
 * @method drawScene
 */
drawScene : function () {},

/**
 * @method popScene
 */
popScene : function () {},

/**
 * @method isDisplayStats
 * @return A value converted from C/C++ "bool"
 */
isDisplayStats : function () {},

/**
 * @method setProjection
 * @param {cocos2d::ccDirectorProjection}
 */
setProjection : function () {},

/**
 * @method getZEye
 * @return A value converted from C/C++ "float"
 */
getZEye : function () {},

/**
 * @method setNextDeltaTimeZero
 * @param {bool}
 */
setNextDeltaTimeZero : function () {},

/**
 * @method getVisibleSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getVisibleSize : function () {},

/**
 * @method getScheduler
 * @return A value converted from C/C++ "cocos2d::CCScheduler*"
 */
getScheduler : function () {},

/**
 * @method pushScene
 * @param {cocos2d::CCScene*}
 */
pushScene : function () {},

/**
 * @method getClassTypeInfo
 * @return A value converted from C/C++ "long"
 */
getClassTypeInfo : function () {},

/**
 * @method getAnimationInterval
 * @return A value converted from C/C++ "double"
 */
getAnimationInterval : function () {},

/**
 * @method isPaused
 * @return A value converted from C/C++ "bool"
 */
isPaused : function () {},

/**
 * @method setDisplayStats
 * @param {bool}
 */
setDisplayStats : function () {},

/**
 * @method replaceScene
 * @param {cocos2d::CCScene*}
 */
replaceScene : function () {},

/**
 * @method setAnimationInterval
 * @param {double}
 */
setAnimationInterval : function () {},

/**
 * @method getActionManager
 * @return A value converted from C/C++ "cocos2d::CCActionManager*"
 */
getActionManager : function () {},

/**
 * @method sharedDirector
 * @return A value converted from C/C++ "cocos2d::CCDirector*"
 */
sharedDirector : function () {},

};

/**
 * @class CCLabelAtlas
 */
cc.CCLabelAtlas = {

/**
 * @method setString
 * @param {const char*}
 */
setString : function () {},

/**
 * @method updateAtlasValues
 */
updateAtlasValues : function () {},

/**
 * @method getString
 * @return A value converted from C/C++ "const char*"
 */
getString : function () {},

/**
 * @method CCLabelAtlas
 * @constructor
 */
CCLabelAtlas : function () {},

};

/**
 * @class CCSpriteBatchNode
 */
cc.CCSpriteBatchNode = {

/**
 * @method appendChild
 * @param {cocos2d::CCSprite*}
 */
appendChild : function () {},

/**
 * @method reorderBatch
 * @param {bool}
 */
reorderBatch : function () {},

/**
 * @method visit
 */
visit : function () {},

/**
 * @method setTexture
 * @param {cocos2d::CCTexture2D*}
 */
setTexture : function () {},

/**
 * @method removeChildAtIndex
 * @param {unsigned int}
 * @param {bool}
 */
removeChildAtIndex : function () {},

/**
 * @method removeSpriteFromAtlas
 * @param {cocos2d::CCSprite*}
 */
removeSpriteFromAtlas : function () {},

/**
 * @method atlasIndexForChild
 * @return A value converted from C/C++ "unsigned int"
 * @param {cocos2d::CCSprite*}
 * @param {int}
 */
atlasIndexForChild : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::CCTexture2D*"
 */
getTexture : function () {},

/**
 * @method increaseAtlasCapacity
 */
increaseAtlasCapacity : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method insertChild
 * @param {cocos2d::CCSprite*}
 * @param {unsigned int}
 */
insertChild : function () {},

/**
 * @method lowestAtlasIndexInChild
 * @return A value converted from C/C++ "unsigned int"
 * @param {cocos2d::CCSprite*}
 */
lowestAtlasIndexInChild : function () {},

/**
 * @method draw
 */
draw : function () {},

/**
 * @method initWithTexture
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCTexture2D*}
 * @param {unsigned int}
 */
initWithTexture : function () {},

/**
 * @method setTextureAtlas
 * @param {cocos2d::CCTextureAtlas*}
 */
setTextureAtlas : function () {},

/**
 * @method removeAllChildrenWithCleanup
 * @param {bool}
 */
removeAllChildrenWithCleanup : function () {},

/**
 * @method sortAllChildren
 */
sortAllChildren : function () {},

/**
 * @method reorderChild
 * @param {cocos2d::CCNode*}
 * @param {int}
 */
reorderChild : function () {},

/**
 * @method initWithFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {unsigned int}
 */
initWithFile : function () {},

/**
 * @method rebuildIndexInOrder
 * @return A value converted from C/C++ "unsigned int"
 * @param {cocos2d::CCSprite*}
 * @param {unsigned int}
 */
rebuildIndexInOrder : function () {},

/**
 * @method getTextureAtlas
 * @return A value converted from C/C++ "cocos2d::CCTextureAtlas*"
 */
getTextureAtlas : function () {},

/**
 * @method getDescendants
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getDescendants : function () {},

/**
 * @method removeChild
 * @param {cocos2d::CCNode*}
 * @param {bool}
 */
removeChild : function () {},

/**
 * @method highestAtlasIndexInChild
 * @return A value converted from C/C++ "unsigned int"
 * @param {cocos2d::CCSprite*}
 */
highestAtlasIndexInChild : function () {},

/**
 * @method batchNodeWithTexture
 * @return A value converted from C/C++ "cocos2d::CCSpriteBatchNode*"
 * @param {cocos2d::CCTexture2D*}
 * @param {unsigned int}
 */
batchNodeWithTexture : function () {},

/**
 * @method batchNodeWithFile
 * @return A value converted from C/C++ "cocos2d::CCSpriteBatchNode*"
 * @param {const char*}
 * @param {unsigned int}
 */
batchNodeWithFile : function () {},

};

/**
 * @class CCLabelBMFont
 */
cc.CCLabelBMFont = {

/**
 * @method setAnchorPoint
 * @param {cocos2d::CCPoint}
 */
setAnchorPoint : function () {},

/**
 * @method createFontChars
 */
createFontChars : function () {},

/**
 * @method getString
 * @return A value converted from C/C++ "const char*"
 */
getString : function () {},

/**
 * @method setScale
 * @param {float}
 */
setScale : function () {},

/**
 * @method getFntFile
 * @return A value converted from C/C++ "const char*"
 */
getFntFile : function () {},

/**
 * @method updateLabel
 */
updateLabel : function () {},

/**
 * @method setWidth
 * @param {float}
 */
setWidth : function () {},

/**
 * @method initWithString
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {const char*}
 * @param {float}
 * @param {cocos2d::CCTextAlignment}
 * @param {cocos2d::CCPoint}
 */
initWithString : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setFntFile
 * @param {const char*}
 */
setFntFile : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method setLineBreakWithoutSpace
 * @param {bool}
 */
setLineBreakWithoutSpace : function () {},

/**
 * @method setScaleY
 * @param {float}
 */
setScaleY : function () {},

/**
 * @method setScaleX
 * @param {float}
 */
setScaleX : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getColor : function () {},

/**
 * @method updateString
 * @param {bool}
 */
updateString : function () {},

/**
 * @method setColor
 * @param {cocos2d::ccColor3B}
 */
setColor : function () {},

/**
 * @method setCString
 * @param {const char*}
 */
setCString : function () {},

/**
 * @method setAlignment
 * @param {cocos2d::CCTextAlignment}
 */
setAlignment : function () {},

/**
 * @method purgeCachedData
 */
purgeCachedData : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCLabelBMFont*"
 */
node : function () {},

/**
 * @method labelWithString
 * @return A value converted from C/C++ "cocos2d::CCLabelBMFont*"
 * @param {const char*}
 * @param {const char*}
 * @param {float}
 * @param {cocos2d::CCTextAlignment}
 * @param {cocos2d::CCPoint}
 */
labelWithString : function () {},

/**
 * @method CCLabelBMFont
 * @constructor
 */
CCLabelBMFont : function () {},

};

/**
 * @class CCLayer
 */
cc.CCLayer = {

/**
 * @method unregisterScriptTouchHandler
 */
unregisterScriptTouchHandler : function () {},

/**
 * @method keyBackClicked
 */
keyBackClicked : function () {},

/**
 * @method ccTouchBegan
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCTouch*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchBegan : function () {},

/**
 * @method setAccelerometerInterval
 * @param {double}
 */
setAccelerometerInterval : function () {},

/**
 * @method ccTouchesCancelled
 * @param {cocos2d::CCSet*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchesCancelled : function () {},

/**
 * @method unregisterScriptAccelerateHandler
 */
unregisterScriptAccelerateHandler : function () {},

/**
 * @method ccTouchesMoved
 * @param {cocos2d::CCSet*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchesMoved : function () {},

/**
 * @method registerScriptAccelerateHandler
 * @param {int}
 */
registerScriptAccelerateHandler : function () {},

/**
 * @method getTouchMode
 * @return A value converted from C/C++ "int"
 */
getTouchMode : function () {},

/**
 * @method setAccelerometerEnabled
 * @param {bool}
 */
setAccelerometerEnabled : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method isTouchEnabled
 * @return A value converted from C/C++ "bool"
 */
isTouchEnabled : function () {},

/**
 * @method getScriptAccelerateHandlerEntry
 * @return A value converted from C/C++ "cocos2d::CCScriptHandlerEntry*"
 */
getScriptAccelerateHandlerEntry : function () {},

/**
 * @method getScriptKeypadHandlerEntry
 * @return A value converted from C/C++ "cocos2d::CCScriptHandlerEntry*"
 */
getScriptKeypadHandlerEntry : function () {},

/**
 * @method ccTouchMoved
 * @param {cocos2d::CCTouch*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchMoved : function () {},

/**
 * @method setTouchEnabled
 * @param {bool}
 */
setTouchEnabled : function () {},

/**
 * @method unregisterScriptKeypadHandler
 */
unregisterScriptKeypadHandler : function () {},

/**
 * @method isKeypadEnabled
 * @return A value converted from C/C++ "bool"
 */
isKeypadEnabled : function () {},

/**
 * @method ccTouchesEnded
 * @param {cocos2d::CCSet*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchesEnded : function () {},

/**
 * @method setTouchMode
 * @param {cocos2d::ccTouchesMode}
 */
setTouchMode : function () {},

/**
 * @method isAccelerometerEnabled
 * @return A value converted from C/C++ "bool"
 */
isAccelerometerEnabled : function () {},

/**
 * @method ccTouchEnded
 * @param {cocos2d::CCTouch*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchEnded : function () {},

/**
 * @method registerScriptTouchHandler
 * @param {int}
 * @param {bool}
 * @param {int}
 * @param {bool}
 */
registerScriptTouchHandler : function () {},

/**
 * @method ccTouchCancelled
 * @param {cocos2d::CCTouch*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchCancelled : function () {},

/**
 * @method getScriptTouchHandlerEntry
 * @return A value converted from C/C++ "cocos2d::CCTouchScriptHandlerEntry*"
 */
getScriptTouchHandlerEntry : function () {},

/**
 * @method ccTouchesBegan
 * @param {cocos2d::CCSet*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchesBegan : function () {},

/**
 * @method setTouchPriority
 * @param {int}
 */
setTouchPriority : function () {},

/**
 * @method getTouchPriority
 * @return A value converted from C/C++ "int"
 */
getTouchPriority : function () {},

/**
 * @method setKeypadEnabled
 * @param {bool}
 */
setKeypadEnabled : function () {},

/**
 * @method registerWithTouchDispatcher
 */
registerWithTouchDispatcher : function () {},

/**
 * @method keyMenuClicked
 */
keyMenuClicked : function () {},

/**
 * @method registerScriptKeypadHandler
 * @param {int}
 */
registerScriptKeypadHandler : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCLayer*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCLayer*"
 */
create : function () {},

/**
 * @method CCLayer
 * @constructor
 */
CCLayer : function () {},

};

/**
 * @class CCLayerColor
 */
cc.CCLayerColor = {

/**
 * @method draw
 */
draw : function () {},

/**
 * @method setColor
 * @param {cocos2d::ccColor3B}
 */
setColor : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getColor : function () {},

/**
 * @method changeWidthAndHeight
 * @param {float}
 * @param {float}
 */
changeWidthAndHeight : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method changeWidth
 * @param {float}
 */
changeWidth : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method setContentSize
 * @param {cocos2d::CCSize}
 */
setContentSize : function () {},

/**
 * @method changeHeight
 * @param {float}
 */
changeHeight : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCLayerColor*"
 */
node : function () {},

/**
 * @method CCLayerColor
 * @constructor
 */
CCLayerColor : function () {},

};

/**
 * @class CCLayerGradient
 */
cc.CCLayerGradient = {

/**
 * @method getStartColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getStartColor : function () {},

/**
 * @method isCompressedInterpolation
 * @return A value converted from C/C++ "bool"
 */
isCompressedInterpolation : function () {},

/**
 * @method getStartOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getStartOpacity : function () {},

/**
 * @method setVector
 * @param {cocos2d::CCPoint}
 */
setVector : function () {},

/**
 * @method setStartOpacity
 * @param {unsigned char}
 */
setStartOpacity : function () {},

/**
 * @method setCompressedInterpolation
 * @param {bool}
 */
setCompressedInterpolation : function () {},

/**
 * @method setEndOpacity
 * @param {unsigned char}
 */
setEndOpacity : function () {},

/**
 * @method getVector
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getVector : function () {},

/**
 * @method setEndColor
 * @param {cocos2d::ccColor3B}
 */
setEndColor : function () {},

/**
 * @method getEndColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getEndColor : function () {},

/**
 * @method getEndOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getEndOpacity : function () {},

/**
 * @method setStartColor
 * @param {cocos2d::ccColor3B}
 */
setStartColor : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCLayerGradient*"
 */
node : function () {},

};

/**
 * @class CCLayerMultiplex
 */
cc.CCLayerMultiplex = {

/**
 * @method initWithArray
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCArray*}
 */
initWithArray : function () {},

/**
 * @method switchToAndReleaseMe
 * @param {unsigned int}
 */
switchToAndReleaseMe : function () {},

/**
 * @method addLayer
 * @param {cocos2d::CCLayer*}
 */
addLayer : function () {},

/**
 * @method switchTo
 * @param {unsigned int}
 */
switchTo : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCLayerMultiplex*"
 */
node : function () {},

/**
 * @method CCLayerMultiplex
 * @constructor
 */
CCLayerMultiplex : function () {},

};

/**
 * @class CCScene
 */
cc.CCScene = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCScene*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCScene*"
 */
create : function () {},

/**
 * @method CCScene
 * @constructor
 */
CCScene : function () {},

};

/**
 * @class CCTransitionEaseScene
 */
cc.CCTransitionEaseScene = {

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {cocos2d::CCActionInterval*}
 */
easeActionWithAction : function () {},

};

/**
 * @class CCTransitionScene
 */
cc.CCTransitionScene = {

/**
 * @method draw
 */
draw : function () {},

/**
 * @method finish
 */
finish : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
initWithDuration : function () {},

/**
 * @method cleanup
 */
cleanup : function () {},

/**
 * @method hideOutShowIn
 */
hideOutShowIn : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionScene*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionScene*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionScene
 * @constructor
 */
CCTransitionScene : function () {},

};

/**
 * @class CCTransitionSceneOriented
 */
cc.CCTransitionSceneOriented = {

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::CCScene*}
 * @param {cocos2d::tOrientation}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionSceneOriented*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 * @param {cocos2d::tOrientation}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionSceneOriented*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 * @param {cocos2d::tOrientation}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionSceneOriented
 * @constructor
 */
CCTransitionSceneOriented : function () {},

};

/**
 * @class CCTransitionRotoZoom
 */
cc.CCTransitionRotoZoom = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionRotoZoom*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionRotoZoom*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionRotoZoom
 * @constructor
 */
CCTransitionRotoZoom : function () {},

};

/**
 * @class CCTransitionJumpZoom
 */
cc.CCTransitionJumpZoom = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionJumpZoom*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionJumpZoom*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionJumpZoom
 * @constructor
 */
CCTransitionJumpZoom : function () {},

};

/**
 * @class CCTransitionMoveInL
 */
cc.CCTransitionMoveInL = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
action : function () {},

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {cocos2d::CCActionInterval*}
 */
easeActionWithAction : function () {},

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionMoveInL*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionMoveInL*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionMoveInL
 * @constructor
 */
CCTransitionMoveInL : function () {},

};

/**
 * @class CCTransitionMoveInR
 */
cc.CCTransitionMoveInR = {

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionMoveInR*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionMoveInR*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionMoveInR
 * @constructor
 */
CCTransitionMoveInR : function () {},

};

/**
 * @class CCTransitionMoveInT
 */
cc.CCTransitionMoveInT = {

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionMoveInT*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionMoveInT*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionMoveInT
 * @constructor
 */
CCTransitionMoveInT : function () {},

};

/**
 * @class CCTransitionMoveInB
 */
cc.CCTransitionMoveInB = {

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionMoveInB*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionMoveInB*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionMoveInB
 * @constructor
 */
CCTransitionMoveInB : function () {},

};

/**
 * @class CCTransitionSlideInL
 */
cc.CCTransitionSlideInL = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
action : function () {},

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {cocos2d::CCActionInterval*}
 */
easeActionWithAction : function () {},

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionSlideInL*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionSlideInL*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionSlideInL
 * @constructor
 */
CCTransitionSlideInL : function () {},

};

/**
 * @class CCTransitionSlideInR
 */
cc.CCTransitionSlideInR = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
action : function () {},

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionSlideInR*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionSlideInR*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionSlideInR
 * @constructor
 */
CCTransitionSlideInR : function () {},

};

/**
 * @class CCTransitionSlideInB
 */
cc.CCTransitionSlideInB = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
action : function () {},

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionSlideInB*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionSlideInB*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionSlideInB
 * @constructor
 */
CCTransitionSlideInB : function () {},

};

/**
 * @class CCTransitionSlideInT
 */
cc.CCTransitionSlideInT = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
action : function () {},

/**
 * @method initScenes
 */
initScenes : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionSlideInT*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionSlideInT*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionSlideInT
 * @constructor
 */
CCTransitionSlideInT : function () {},

};

/**
 * @class CCTransitionShrinkGrow
 */
cc.CCTransitionShrinkGrow = {

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {cocos2d::CCActionInterval*}
 */
easeActionWithAction : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionShrinkGrow*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionShrinkGrow*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionShrinkGrow
 * @constructor
 */
CCTransitionShrinkGrow : function () {},

};

/**
 * @class CCTransitionFlipX
 */
cc.CCTransitionFlipX = {

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionFlipX*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 * @param {cocos2d::tOrientation}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionFlipX
 * @constructor
 */
CCTransitionFlipX : function () {},

};

/**
 * @class CCTransitionFlipY
 */
cc.CCTransitionFlipY = {

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionFlipY*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 * @param {cocos2d::tOrientation}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionFlipY
 * @constructor
 */
CCTransitionFlipY : function () {},

};

/**
 * @class CCTransitionFlipAngular
 */
cc.CCTransitionFlipAngular = {

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionFlipAngular*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 * @param {cocos2d::tOrientation}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionFlipAngular
 * @constructor
 */
CCTransitionFlipAngular : function () {},

};

/**
 * @class CCTransitionZoomFlipX
 */
cc.CCTransitionZoomFlipX = {

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionZoomFlipX*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 * @param {cocos2d::tOrientation}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionZoomFlipX
 * @constructor
 */
CCTransitionZoomFlipX : function () {},

};

/**
 * @class CCTransitionZoomFlipY
 */
cc.CCTransitionZoomFlipY = {

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionZoomFlipY*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 * @param {cocos2d::tOrientation}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionZoomFlipY
 * @constructor
 */
CCTransitionZoomFlipY : function () {},

};

/**
 * @class CCTransitionZoomFlipAngular
 */
cc.CCTransitionZoomFlipAngular = {

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionZoomFlipAngular*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 * @param {cocos2d::tOrientation}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionZoomFlipAngular
 * @constructor
 */
CCTransitionZoomFlipAngular : function () {},

};

/**
 * @class CCTransitionFade
 */
cc.CCTransitionFade = {

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionFade*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 * @param {cocos2d::ccColor3B}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionFade
 * @constructor
 */
CCTransitionFade : function () {},

};

/**
 * @class CCTransitionCrossFade
 */
cc.CCTransitionCrossFade = {

/**
 * @method draw
 */
draw : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionCrossFade*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionCrossFade*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionCrossFade
 * @constructor
 */
CCTransitionCrossFade : function () {},

};

/**
 * @class CCTransitionTurnOffTiles
 */
cc.CCTransitionTurnOffTiles = {

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {cocos2d::CCActionInterval*}
 */
easeActionWithAction : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionTurnOffTiles*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionTurnOffTiles*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionTurnOffTiles
 * @constructor
 */
CCTransitionTurnOffTiles : function () {},

};

/**
 * @class CCTransitionSplitCols
 */
cc.CCTransitionSplitCols = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
action : function () {},

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {cocos2d::CCActionInterval*}
 */
easeActionWithAction : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionSplitCols*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionSplitCols*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionSplitCols
 * @constructor
 */
CCTransitionSplitCols : function () {},

};

/**
 * @class CCTransitionSplitRows
 */
cc.CCTransitionSplitRows = {

/**
 * @method action
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 */
action : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionSplitRows*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionSplitRows*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionSplitRows
 * @constructor
 */
CCTransitionSplitRows : function () {},

};

/**
 * @class CCTransitionFadeTR
 */
cc.CCTransitionFadeTR = {

/**
 * @method easeActionWithAction
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {cocos2d::CCActionInterval*}
 */
easeActionWithAction : function () {},

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {cocos2d::ccGridSize}
 */
actionWithSize : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionFadeTR*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionFadeTR*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionFadeTR
 * @constructor
 */
CCTransitionFadeTR : function () {},

};

/**
 * @class CCTransitionFadeBL
 */
cc.CCTransitionFadeBL = {

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {cocos2d::ccGridSize}
 */
actionWithSize : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionFadeBL*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionFadeBL*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionFadeBL
 * @constructor
 */
CCTransitionFadeBL : function () {},

};

/**
 * @class CCTransitionFadeUp
 */
cc.CCTransitionFadeUp = {

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {cocos2d::ccGridSize}
 */
actionWithSize : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionFadeUp*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionFadeUp*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionFadeUp
 * @constructor
 */
CCTransitionFadeUp : function () {},

};

/**
 * @class CCTransitionFadeDown
 */
cc.CCTransitionFadeDown = {

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {cocos2d::ccGridSize}
 */
actionWithSize : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionFadeDown*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionFadeDown*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionFadeDown
 * @constructor
 */
CCTransitionFadeDown : function () {},

};

/**
 * @class CCTransitionPageTurn
 */
cc.CCTransitionPageTurn = {

/**
 * @method actionWithSize
 * @return A value converted from C/C++ "cocos2d::CCActionInterval*"
 * @param {cocos2d::ccGridSize}
 */
actionWithSize : function () {},

/**
 * @method initWithDuration
 * @return A value converted from C/C++ "bool"
 * @param {float}
 * @param {cocos2d::CCScene*}
 * @param {bool}
 */
initWithDuration : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionPageTurn*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 * @param {bool}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionPageTurn*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 * @param {bool}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionPageTurn
 * @constructor
 */
CCTransitionPageTurn : function () {},

};

/**
 * @class CCTransitionProgress
 */
cc.CCTransitionProgress = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgress*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgress*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

/**
 * @method CCTransitionProgress
 * @constructor
 */
CCTransitionProgress : function () {},

};

/**
 * @class CCTransitionProgressRadialCCW
 */
cc.CCTransitionProgressRadialCCW = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgressRadialCCW*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgressRadialCCW*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

};

/**
 * @class CCTransitionProgressRadialCW
 */
cc.CCTransitionProgressRadialCW = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgressRadialCW*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgressRadialCW*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

};

/**
 * @class CCTransitionProgressHorizontal
 */
cc.CCTransitionProgressHorizontal = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgressHorizontal*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgressHorizontal*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

};

/**
 * @class CCTransitionProgressVertical
 */
cc.CCTransitionProgressVertical = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgressVertical*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgressVertical*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

};

/**
 * @class CCTransitionProgressInOut
 */
cc.CCTransitionProgressInOut = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgressInOut*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgressInOut*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

};

/**
 * @class CCTransitionProgressOutIn
 */
cc.CCTransitionProgressOutIn = {

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgressOutIn*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
create : function () {},

/**
 * @method transitionWithDuration
 * @return A value converted from C/C++ "cocos2d::CCTransitionProgressOutIn*"
 * @param {float}
 * @param {cocos2d::CCScene*}
 */
transitionWithDuration : function () {},

};

/**
 * @class CCMenuItem
 */
cc.CCMenuItem = {

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method activate
 */
activate : function () {},

/**
 * @method unregisterScriptTapHandler
 */
unregisterScriptTapHandler : function () {},

/**
 * @method isEnabled
 * @return A value converted from C/C++ "bool"
 */
isEnabled : function () {},

/**
 * @method selected
 */
selected : function () {},

/**
 * @method getScriptTapHandler
 * @return A value converted from C/C++ "int"
 */
getScriptTapHandler : function () {},

/**
 * @method isSelected
 * @return A value converted from C/C++ "bool"
 */
isSelected : function () {},

/**
 * @method registerScriptTapHandler
 * @param {int}
 */
registerScriptTapHandler : function () {},

/**
 * @method unselected
 */
unselected : function () {},

/**
 * @method rect
 * @return A value converted from C/C++ "cocos2d::CCRect"
 */
rect : function () {},

/**
 * @method CCMenuItem
 * @constructor
 */
CCMenuItem : function () {},

};

/**
 * @class CCMenuItemLabel
 */
cc.CCMenuItemLabel = {

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method setLabel
 * @param {cocos2d::CCNode*}
 */
setLabel : function () {},

/**
 * @method activate
 */
activate : function () {},

/**
 * @method setColor
 * @param {cocos2d::ccColor3B}
 */
setColor : function () {},

/**
 * @method getDisabledColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getDisabledColor : function () {},

/**
 * @method setString
 * @param {const char*}
 */
setString : function () {},

/**
 * @method selected
 */
selected : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method setDisabledColor
 * @param {cocos2d::ccColor3B}
 */
setDisabledColor : function () {},

/**
 * @method getLabel
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
getLabel : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getColor : function () {},

/**
 * @method unselected
 */
unselected : function () {},

/**
 * @method itemWithLabel
 * @return A value converted from C/C++ "cocos2d::CCMenuItemLabel*"
 * @param {cocos2d::CCNode*}
 */
itemWithLabel : function () {},

/**
 * @method CCMenuItemLabel
 * @constructor
 */
CCMenuItemLabel : function () {},

};

/**
 * @class CCMenuItemAtlasFont
 */
cc.CCMenuItemAtlasFont = {

/**
 * @method itemWithString
 * @return A value converted from C/C++ "cocos2d::CCMenuItemAtlasFont*"
 * @param {const char*}
 * @param {const char*}
 * @param {int}
 * @param {int}
 * @param {char}
 */
itemWithString : function () {},

/**
 * @method CCMenuItemAtlasFont
 * @constructor
 */
CCMenuItemAtlasFont : function () {},

};

/**
 * @class CCMenuItemFont
 */
cc.CCMenuItemFont = {

/**
 * @method setFontNameObj
 * @param {const char*}
 */
setFontNameObj : function () {},

/**
 * @method fontNameObj
 * @return A value converted from C/C++ "const char*"
 */
fontNameObj : function () {},

/**
 * @method setFontSizeObj
 * @param {unsigned int}
 */
setFontSizeObj : function () {},

/**
 * @method fontSizeObj
 * @return A value converted from C/C++ "unsigned int"
 */
fontSizeObj : function () {},

/**
 * @method setFontName
 * @param {const char*}
 */
setFontName : function () {},

/**
 * @method fontName
 * @return A value converted from C/C++ "const char*"
 */
fontName : function () {},

/**
 * @method fontSize
 * @return A value converted from C/C++ "unsigned int"
 */
fontSize : function () {},

/**
 * @method setFontSize
 * @param {unsigned int}
 */
setFontSize : function () {},

/**
 * @method itemWithString
 * @return A value converted from C/C++ "cocos2d::CCMenuItemFont*"
 * @param {const char*}
 */
itemWithString : function () {},

/**
 * @method CCMenuItemFont
 * @constructor
 */
CCMenuItemFont : function () {},

};

/**
 * @class CCMenuItemSprite
 */
cc.CCMenuItemSprite = {

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method selected
 */
selected : function () {},

/**
 * @method setColor
 * @param {cocos2d::ccColor3B}
 */
setColor : function () {},

/**
 * @method setNormalImage
 * @param {cocos2d::CCNode*}
 */
setNormalImage : function () {},

/**
 * @method setDisabledImage
 * @param {cocos2d::CCNode*}
 */
setDisabledImage : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getColor : function () {},

/**
 * @method setSelectedImage
 * @param {cocos2d::CCNode*}
 */
setSelectedImage : function () {},

/**
 * @method getDisabledImage
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
getDisabledImage : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method getSelectedImage
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
getSelectedImage : function () {},

/**
 * @method getNormalImage
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
getNormalImage : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method unselected
 */
unselected : function () {},

/**
 * @method itemWithNormalSprite
 * @return A value converted from C/C++ "cocos2d::CCMenuItemSprite*"
 * @param {cocos2d::CCNode*}
 * @param {cocos2d::CCNode*}
 * @param {cocos2d::CCNode*}
 */
itemWithNormalSprite : function () {},

/**
 * @method CCMenuItemSprite
 * @constructor
 */
CCMenuItemSprite : function () {},

};

/**
 * @class CCMenuItemImage
 */
cc.CCMenuItemImage = {

/**
 * @method setDisabledSpriteFrame
 * @param {cocos2d::CCSpriteFrame*}
 */
setDisabledSpriteFrame : function () {},

/**
 * @method setSelectedSpriteFrame
 * @param {cocos2d::CCSpriteFrame*}
 */
setSelectedSpriteFrame : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setNormalSpriteFrame
 * @param {cocos2d::CCSpriteFrame*}
 */
setNormalSpriteFrame : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCMenuItemImage*"
 */
node : function () {},

/**
 * @method CCMenuItemImage
 * @constructor
 */
CCMenuItemImage : function () {},

};

/**
 * @class CCMenuItemToggle
 */
cc.CCMenuItemToggle = {

/**
 * @method setSubItems
 * @param {cocos2d::CCArray*}
 */
setSubItems : function () {},

/**
 * @method initWithItem
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCMenuItem*}
 */
initWithItem : function () {},

/**
 * @method setSelectedIndex
 * @param {unsigned int}
 */
setSelectedIndex : function () {},

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method getSelectedIndex
 * @return A value converted from C/C++ "unsigned int"
 */
getSelectedIndex : function () {},

/**
 * @method addSubItem
 * @param {cocos2d::CCMenuItem*}
 */
addSubItem : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method activate
 */
activate : function () {},

/**
 * @method selected
 */
selected : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getColor : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method unselected
 */
unselected : function () {},

/**
 * @method selectedItem
 * @return A value converted from C/C++ "cocos2d::CCMenuItem*"
 */
selectedItem : function () {},

/**
 * @method setColor
 * @param {cocos2d::ccColor3B}
 */
setColor : function () {},

/**
 * @method itemWithItem
 * @return A value converted from C/C++ "cocos2d::CCMenuItemToggle*"
 * @param {cocos2d::CCMenuItem*}
 */
itemWithItem : function () {},

/**
 * @method CCMenuItemToggle
 * @constructor
 */
CCMenuItemToggle : function () {},

};

/**
 * @class CCMenu
 */
cc.CCMenu = {

/**
 * @method initWithArray
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCArray*}
 */
initWithArray : function () {},

/**
 * @method alignItemsVertically
 */
alignItemsVertically : function () {},

/**
 * @method ccTouchBegan
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCTouch*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchBegan : function () {},

/**
 * @method ccTouchEnded
 * @param {cocos2d::CCTouch*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchEnded : function () {},

/**
 * @method isEnabled
 * @return A value converted from C/C++ "bool"
 */
isEnabled : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method setHandlerPriority
 * @param {int}
 */
setHandlerPriority : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method alignItemsHorizontallyWithPadding
 * @param {float}
 */
alignItemsHorizontallyWithPadding : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method alignItemsHorizontally
 */
alignItemsHorizontally : function () {},

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getColor : function () {},

/**
 * @method ccTouchMoved
 * @param {cocos2d::CCTouch*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchMoved : function () {},

/**
 * @method setColor
 * @param {cocos2d::ccColor3B}
 */
setColor : function () {},

/**
 * @method ccTouchCancelled
 * @param {cocos2d::CCTouch*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchCancelled : function () {},

/**
 * @method alignItemsVerticallyWithPadding
 * @param {float}
 */
alignItemsVerticallyWithPadding : function () {},

/**
 * @method registerWithTouchDispatcher
 */
registerWithTouchDispatcher : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCMenu*"
 */
node : function () {},

/**
 * @method menuWithArray
 * @return A value converted from C/C++ "cocos2d::CCMenu*"
 * @param {cocos2d::CCArray*}
 */
menuWithArray : function () {},

/**
 * @method menuWithItem
 * @return A value converted from C/C++ "cocos2d::CCMenu*"
 * @param {cocos2d::CCMenuItem*}
 */
menuWithItem : function () {},

/**
 * @method CCMenu
 * @constructor
 */
CCMenu : function () {},

};

/**
 * @class CCProgressTimer
 */
cc.CCProgressTimer = {

/**
 * @method setAnchorPoint
 * @param {cocos2d::CCPoint}
 */
setAnchorPoint : function () {},

/**
 * @method setBarChangeRate
 * @param {cocos2d::CCPoint}
 */
setBarChangeRate : function () {},

/**
 * @method setPercentage
 * @param {float}
 */
setPercentage : function () {},

/**
 * @method setType
 * @param {cocos2d::CCProgressTimerType}
 */
setType : function () {},

/**
 * @method getPercentage
 * @return A value converted from C/C++ "float"
 */
getPercentage : function () {},

/**
 * @method setSprite
 * @param {cocos2d::CCSprite*}
 */
setSprite : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method getSprite
 * @return A value converted from C/C++ "cocos2d::CCSprite*"
 */
getSprite : function () {},

/**
 * @method setMidpoint
 * @param {cocos2d::CCPoint}
 */
setMidpoint : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method getMidpoint
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getMidpoint : function () {},

/**
 * @method draw
 */
draw : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getColor : function () {},

/**
 * @method getType
 * @return A value converted from C/C++ "cocos2d::CCProgressTimerType"
 */
getType : function () {},

/**
 * @method isReverseDirection
 * @return A value converted from C/C++ "bool"
 */
isReverseDirection : function () {},

/**
 * @method setColor
 * @param {cocos2d::ccColor3B}
 */
setColor : function () {},

/**
 * @method getBarChangeRate
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getBarChangeRate : function () {},

/**
 * @method initWithSprite
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCSprite*}
 */
initWithSprite : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCProgressTimer*"
 * @param {cocos2d::CCSprite*}
 */
create : function () {},

/**
 * @method progressWithSprite
 * @return A value converted from C/C++ "cocos2d::CCProgressTimer*"
 * @param {cocos2d::CCSprite*}
 */
progressWithSprite : function () {},

/**
 * @method CCProgressTimer
 * @constructor
 */
CCProgressTimer : function () {},

};

/**
 * @class CCRenderTexture
 */
cc.CCRenderTexture = {

/**
 * @method clearStencil
 * @param {int}
 */
clearStencil : function () {},

/**
 * @method begin
 */
begin : function () {},

/**
 * @method getClearDepth
 * @return A value converted from C/C++ "float"
 */
getClearDepth : function () {},

/**
 * @method getClearStencil
 * @return A value converted from C/C++ "int"
 */
getClearStencil : function () {},

/**
 * @method end
 */
end : function () {},

/**
 * @method setClearStencil
 * @param {float}
 */
setClearStencil : function () {},

/**
 * @method visit
 */
visit : function () {},

/**
 * @method getSprite
 * @return A value converted from C/C++ "cocos2d::CCSprite*"
 */
getSprite : function () {},

/**
 * @method isAutoDraw
 * @return A value converted from C/C++ "bool"
 */
isAutoDraw : function () {},

/**
 * @method setClearFlags
 * @param {unsigned int}
 */
setClearFlags : function () {},

/**
 * @method draw
 */
draw : function () {},

/**
 * @method setAutoDraw
 * @param {bool}
 */
setAutoDraw : function () {},

/**
 * @method setClearColor
 * @param {cocos2d::ccColor4F}
 */
setClearColor : function () {},

/**
 * @method endToLua
 */
endToLua : function () {},

/**
 * @method clearDepth
 * @param {float}
 */
clearDepth : function () {},

/**
 * @method getClearColor
 * @return A value converted from C/C++ "cocos2d::ccColor4F"
 */
getClearColor : function () {},

/**
 * @method listenToBackground
 * @param {cocos2d::CCObject*}
 */
listenToBackground : function () {},

/**
 * @method clear
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {float}
 */
clear : function () {},

/**
 * @method getClearFlags
 * @return A value converted from C/C++ "unsigned int"
 */
getClearFlags : function () {},

/**
 * @method newCCImage
 * @return A value converted from C/C++ "cocos2d::CCImage*"
 */
newCCImage : function () {},

/**
 * @method setClearDepth
 * @param {float}
 */
setClearDepth : function () {},

/**
 * @method setSprite
 * @param {cocos2d::CCSprite*}
 */
setSprite : function () {},

/**
 * @method CCRenderTexture
 * @constructor
 */
CCRenderTexture : function () {},

};

/**
 * @class CCParticleBatchNode
 */
cc.CCParticleBatchNode = {

/**
 * @method removeChildAtIndex
 * @param {unsigned int}
 * @param {bool}
 */
removeChildAtIndex : function () {},

/**
 * @method draw
 */
draw : function () {},

/**
 * @method setTexture
 * @param {cocos2d::CCTexture2D*}
 */
setTexture : function () {},

/**
 * @method initWithFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {unsigned int}
 */
initWithFile : function () {},

/**
 * @method disableParticle
 * @param {unsigned int}
 */
disableParticle : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::CCTexture2D*"
 */
getTexture : function () {},

/**
 * @method visit
 */
visit : function () {},

/**
 * @method removeAllChildrenWithCleanup
 * @param {bool}
 */
removeAllChildrenWithCleanup : function () {},

/**
 * @method getTextureAtlas
 * @return A value converted from C/C++ "cocos2d::CCTextureAtlas*"
 */
getTextureAtlas : function () {},

/**
 * @method removeChild
 * @param {cocos2d::CCNode*}
 * @param {bool}
 */
removeChild : function () {},

/**
 * @method insertChild
 * @param {cocos2d::CCParticleSystem*}
 * @param {unsigned int}
 */
insertChild : function () {},

/**
 * @method initWithTexture
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCTexture2D*}
 * @param {unsigned int}
 */
initWithTexture : function () {},

/**
 * @method reorderChild
 * @param {cocos2d::CCNode*}
 * @param {int}
 */
reorderChild : function () {},

/**
 * @method setTextureAtlas
 * @param {cocos2d::CCTextureAtlas*}
 */
setTextureAtlas : function () {},

/**
 * @method batchNodeWithTexture
 * @return A value converted from C/C++ "cocos2d::CCParticleBatchNode*"
 * @param {cocos2d::CCTexture2D*}
 * @param {unsigned int}
 */
batchNodeWithTexture : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParticleBatchNode*"
 * @param {const char*}
 * @param {unsigned int}
 */
create : function () {},

/**
 * @method createWithTexture
 * @return A value converted from C/C++ "cocos2d::CCParticleBatchNode*"
 * @param {cocos2d::CCTexture2D*}
 * @param {unsigned int}
 */
createWithTexture : function () {},

/**
 * @method batchNodeWithFile
 * @return A value converted from C/C++ "cocos2d::CCParticleBatchNode*"
 * @param {const char*}
 * @param {unsigned int}
 */
batchNodeWithFile : function () {},

/**
 * @method CCParticleBatchNode
 * @constructor
 */
CCParticleBatchNode : function () {},

};

/**
 * @class CCParticleSystem
 */
cc.CCParticleSystem = {

/**
 * @method getStartSizeVar
 * @return A value converted from C/C++ "float"
 */
getStartSizeVar : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::CCTexture2D*"
 */
getTexture : function () {},

/**
 * @method isFull
 * @return A value converted from C/C++ "bool"
 */
isFull : function () {},

/**
 * @method getBatchNode
 * @return A value converted from C/C++ "cocos2d::CCParticleBatchNode*"
 */
getBatchNode : function () {},

/**
 * @method getStartColor
 * @return A value converted from C/C++ "ccColor4F"
 */
getStartColor : function () {},

/**
 * @method getPositionType
 * @return A value converted from C/C++ "cocos2d::tCCPositionType"
 */
getPositionType : function () {},

/**
 * @method setPosVar
 * @param {cocos2d::CCPoint}
 */
setPosVar : function () {},

/**
 * @method getEndSpin
 * @return A value converted from C/C++ "float"
 */
getEndSpin : function () {},

/**
 * @method setRotatePerSecondVar
 * @param {float}
 */
setRotatePerSecondVar : function () {},

/**
 * @method getStartSpinVar
 * @return A value converted from C/C++ "float"
 */
getStartSpinVar : function () {},

/**
 * @method getEndSpinVar
 * @return A value converted from C/C++ "float"
 */
getEndSpinVar : function () {},

/**
 * @method stopSystem
 */
stopSystem : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method getEndSizeVar
 * @return A value converted from C/C++ "float"
 */
getEndSizeVar : function () {},

/**
 * @method setRotation
 * @param {float}
 */
setRotation : function () {},

/**
 * @method setTangentialAccel
 * @param {float}
 */
setTangentialAccel : function () {},

/**
 * @method setScaleY
 * @param {float}
 */
setScaleY : function () {},

/**
 * @method setScaleX
 * @param {float}
 */
setScaleX : function () {},

/**
 * @method getRadialAccel
 * @return A value converted from C/C++ "float"
 */
getRadialAccel : function () {},

/**
 * @method setStartRadius
 * @param {float}
 */
setStartRadius : function () {},

/**
 * @method setRotatePerSecond
 * @param {float}
 */
setRotatePerSecond : function () {},

/**
 * @method setEndSize
 * @param {float}
 */
setEndSize : function () {},

/**
 * @method getGravity
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getGravity : function () {},

/**
 * @method getTangentialAccel
 * @return A value converted from C/C++ "float"
 */
getTangentialAccel : function () {},

/**
 * @method setEndRadius
 * @param {float}
 */
setEndRadius : function () {},

/**
 * @method getAngle
 * @return A value converted from C/C++ "float"
 */
getAngle : function () {},

/**
 * @method getSpeed
 * @return A value converted from C/C++ "float"
 */
getSpeed : function () {},

/**
 * @method setEndColor
 * @param {cocos2d::ccColor4F}
 */
setEndColor : function () {},

/**
 * @method setStartSpin
 * @param {float}
 */
setStartSpin : function () {},

/**
 * @method setDuration
 * @param {float}
 */
setDuration : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method setTexture
 * @param {cocos2d::CCTexture2D*}
 */
setTexture : function () {},

/**
 * @method getPosVar
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getPosVar : function () {},

/**
 * @method updateWithNoTime
 */
updateWithNoTime : function () {},

/**
 * @method isBlendAdditive
 * @return A value converted from C/C++ "bool"
 */
isBlendAdditive : function () {},

/**
 * @method getAngleVar
 * @return A value converted from C/C++ "float"
 */
getAngleVar : function () {},

/**
 * @method setPositionType
 * @param {cocos2d::tCCPositionType}
 */
setPositionType : function () {},

/**
 * @method getEndRadius
 * @return A value converted from C/C++ "float"
 */
getEndRadius : function () {},

/**
 * @method getSourcePosition
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getSourcePosition : function () {},

/**
 * @method setLifeVar
 * @param {float}
 */
setLifeVar : function () {},

/**
 * @method setTotalParticles
 * @param {unsigned int}
 */
setTotalParticles : function () {},

/**
 * @method setEndColorVar
 * @param {cocos2d::ccColor4F}
 */
setEndColorVar : function () {},

/**
 * @method updateQuadWithParticle
 * @param {tCCParticle*}
 * @param {cocos2d::CCPoint}
 */
updateQuadWithParticle : function () {},

/**
 * @method getAtlasIndex
 * @return A value converted from C/C++ "unsigned int"
 */
getAtlasIndex : function () {},

/**
 * @method getStartSize
 * @return A value converted from C/C++ "float"
 */
getStartSize : function () {},

/**
 * @method setStartSpinVar
 * @param {float}
 */
setStartSpinVar : function () {},

/**
 * @method resetSystem
 */
resetSystem : function () {},

/**
 * @method setAtlasIndex
 * @param {unsigned int}
 */
setAtlasIndex : function () {},

/**
 * @method setTangentialAccelVar
 * @param {float}
 */
setTangentialAccelVar : function () {},

/**
 * @method setEndRadiusVar
 * @param {float}
 */
setEndRadiusVar : function () {},

/**
 * @method isActive
 * @return A value converted from C/C++ "bool"
 */
isActive : function () {},

/**
 * @method setRadialAccelVar
 * @param {float}
 */
setRadialAccelVar : function () {},

/**
 * @method setStartSize
 * @param {float}
 */
setStartSize : function () {},

/**
 * @method setSpeed
 * @param {float}
 */
setSpeed : function () {},

/**
 * @method getStartSpin
 * @return A value converted from C/C++ "float"
 */
getStartSpin : function () {},

/**
 * @method getRotatePerSecond
 * @return A value converted from C/C++ "float"
 */
getRotatePerSecond : function () {},

/**
 * @method initParticle
 * @param {tCCParticle*}
 */
initParticle : function () {},

/**
 * @method setEmitterMode
 * @param {int}
 */
setEmitterMode : function () {},

/**
 * @method getDuration
 * @return A value converted from C/C++ "float"
 */
getDuration : function () {},

/**
 * @method setSourcePosition
 * @param {cocos2d::CCPoint}
 */
setSourcePosition : function () {},

/**
 * @method getRadialAccelVar
 * @return A value converted from C/C++ "float"
 */
getRadialAccelVar : function () {},

/**
 * @method setBlendAdditive
 * @param {bool}
 */
setBlendAdditive : function () {},

/**
 * @method setLife
 * @param {float}
 */
setLife : function () {},

/**
 * @method setAngleVar
 * @param {float}
 */
setAngleVar : function () {},

/**
 * @method setEndSizeVar
 * @param {float}
 */
setEndSizeVar : function () {},

/**
 * @method setAngle
 * @param {float}
 */
setAngle : function () {},

/**
 * @method setBatchNode
 * @param {cocos2d::CCParticleBatchNode*}
 */
setBatchNode : function () {},

/**
 * @method getTangentialAccelVar
 * @return A value converted from C/C++ "float"
 */
getTangentialAccelVar : function () {},

/**
 * @method getEmitterMode
 * @return A value converted from C/C++ "int"
 */
getEmitterMode : function () {},

/**
 * @method setEndSpinVar
 * @param {float}
 */
setEndSpinVar : function () {},

/**
 * @method initWithFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
initWithFile : function () {},

/**
 * @method getSpeedVar
 * @return A value converted from C/C++ "float"
 */
getSpeedVar : function () {},

/**
 * @method setStartColor
 * @param {cocos2d::ccColor4F}
 */
setStartColor : function () {},

/**
 * @method getRotatePerSecondVar
 * @return A value converted from C/C++ "float"
 */
getRotatePerSecondVar : function () {},

/**
 * @method getEndSize
 * @return A value converted from C/C++ "float"
 */
getEndSize : function () {},

/**
 * @method getLife
 * @return A value converted from C/C++ "float"
 */
getLife : function () {},

/**
 * @method setSpeedVar
 * @param {float}
 */
setSpeedVar : function () {},

/**
 * @method setAutoRemoveOnFinish
 * @param {bool}
 */
setAutoRemoveOnFinish : function () {},

/**
 * @method setGravity
 * @param {cocos2d::CCPoint}
 */
setGravity : function () {},

/**
 * @method postStep
 */
postStep : function () {},

/**
 * @method setEmissionRate
 * @param {float}
 */
setEmissionRate : function () {},

/**
 * @method getEndColorVar
 * @return A value converted from C/C++ "ccColor4F"
 */
getEndColorVar : function () {},

/**
 * @method setScale
 * @param {float}
 */
setScale : function () {},

/**
 * @method getEmissionRate
 * @return A value converted from C/C++ "float"
 */
getEmissionRate : function () {},

/**
 * @method getEndColor
 * @return A value converted from C/C++ "ccColor4F"
 */
getEndColor : function () {},

/**
 * @method getLifeVar
 * @return A value converted from C/C++ "float"
 */
getLifeVar : function () {},

/**
 * @method setStartSizeVar
 * @param {float}
 */
setStartSizeVar : function () {},

/**
 * @method addParticle
 * @return A value converted from C/C++ "bool"
 */
addParticle : function () {},

/**
 * @method getStartRadius
 * @return A value converted from C/C++ "float"
 */
getStartRadius : function () {},

/**
 * @method getParticleCount
 * @return A value converted from C/C++ "unsigned int"
 */
getParticleCount : function () {},

/**
 * @method getStartRadiusVar
 * @return A value converted from C/C++ "float"
 */
getStartRadiusVar : function () {},

/**
 * @method setStartColorVar
 * @param {cocos2d::ccColor4F}
 */
setStartColorVar : function () {},

/**
 * @method setEndSpin
 * @param {float}
 */
setEndSpin : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method setRadialAccel
 * @param {float}
 */
setRadialAccel : function () {},

/**
 * @method isAutoRemoveOnFinish
 * @return A value converted from C/C++ "bool"
 */
isAutoRemoveOnFinish : function () {},

/**
 * @method getTotalParticles
 * @return A value converted from C/C++ "unsigned int"
 */
getTotalParticles : function () {},

/**
 * @method setStartRadiusVar
 * @param {float}
 */
setStartRadiusVar : function () {},

/**
 * @method getEndRadiusVar
 * @return A value converted from C/C++ "float"
 */
getEndRadiusVar : function () {},

/**
 * @method getStartColorVar
 * @return A value converted from C/C++ "ccColor4F"
 */
getStartColorVar : function () {},

/**
 * @method particleWithFile
 * @return A value converted from C/C++ "cocos2d::CCParticleSystem*"
 * @param {const char*}
 */
particleWithFile : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParticleSystem*"
 * @param {const char*}
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::CCParticleSystem*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method CCParticleSystem
 * @constructor
 */
CCParticleSystem : function () {},

};

/**
 * @class CCParticleSystemQuad
 */
cc.CCParticleSystemQuad = {

/**
 * @method initTexCoordsWithRect
 * @param {cocos2d::CCRect}
 */
initTexCoordsWithRect : function () {},

/**
 * @method setTextureWithRect
 * @param {cocos2d::CCTexture2D*}
 * @param {cocos2d::CCRect}
 */
setTextureWithRect : function () {},

/**
 * @method setDisplayFrame
 * @param {cocos2d::CCSpriteFrame*}
 */
setDisplayFrame : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::CCParticleSystemQuad*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method CCParticleSystemQuad
 * @constructor
 */
CCParticleSystemQuad : function () {},

};

/**
 * @class CCParticleFire
 */
cc.CCParticleFire = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCParticleFire*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParticleFire*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::CCParticleFire*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method CCParticleFire
 * @constructor
 */
CCParticleFire : function () {},

};

/**
 * @class CCParticleFireworks
 */
cc.CCParticleFireworks = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCParticleFireworks*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParticleFireworks*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::CCParticleFireworks*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method CCParticleFireworks
 * @constructor
 */
CCParticleFireworks : function () {},

};

/**
 * @class CCParticleSun
 */
cc.CCParticleSun = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCParticleSun*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParticleSun*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::CCParticleSun*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method CCParticleSun
 * @constructor
 */
CCParticleSun : function () {},

};

/**
 * @class CCParticleGalaxy
 */
cc.CCParticleGalaxy = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCParticleGalaxy*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParticleGalaxy*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::CCParticleGalaxy*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method CCParticleGalaxy
 * @constructor
 */
CCParticleGalaxy : function () {},

};

/**
 * @class CCParticleFlower
 */
cc.CCParticleFlower = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCParticleFlower*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParticleFlower*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::CCParticleFlower*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method CCParticleFlower
 * @constructor
 */
CCParticleFlower : function () {},

};

/**
 * @class CCParticleMeteor
 */
cc.CCParticleMeteor = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCParticleMeteor*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParticleMeteor*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::CCParticleMeteor*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method CCParticleMeteor
 * @constructor
 */
CCParticleMeteor : function () {},

};

/**
 * @class CCParticleSpiral
 */
cc.CCParticleSpiral = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCParticleSpiral*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParticleSpiral*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::CCParticleSpiral*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method CCParticleSpiral
 * @constructor
 */
CCParticleSpiral : function () {},

};

/**
 * @class CCParticleExplosion
 */
cc.CCParticleExplosion = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCParticleExplosion*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParticleExplosion*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::CCParticleExplosion*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method CCParticleExplosion
 * @constructor
 */
CCParticleExplosion : function () {},

};

/**
 * @class CCParticleSmoke
 */
cc.CCParticleSmoke = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCParticleSmoke*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParticleSmoke*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::CCParticleSmoke*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method CCParticleSmoke
 * @constructor
 */
CCParticleSmoke : function () {},

};

/**
 * @class CCParticleSnow
 */
cc.CCParticleSnow = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCParticleSnow*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParticleSnow*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::CCParticleSnow*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method CCParticleSnow
 * @constructor
 */
CCParticleSnow : function () {},

};

/**
 * @class CCParticleRain
 */
cc.CCParticleRain = {

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method initWithTotalParticles
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
initWithTotalParticles : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCParticleRain*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParticleRain*"
 */
create : function () {},

/**
 * @method createWithTotalParticles
 * @return A value converted from C/C++ "cocos2d::CCParticleRain*"
 * @param {unsigned int}
 */
createWithTotalParticles : function () {},

/**
 * @method CCParticleRain
 * @constructor
 */
CCParticleRain : function () {},

};

/**
 * @class CCAnimationCache
 */
cc.CCAnimationCache = {

/**
 * @method animationByName
 * @return A value converted from C/C++ "cocos2d::CCAnimation*"
 * @param {const char*}
 */
animationByName : function () {},

/**
 * @method addAnimationsWithFile
 * @param {const char*}
 */
addAnimationsWithFile : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method addAnimationsWithDictionary
 * @param {cocos2d::CCDictionary*}
 */
addAnimationsWithDictionary : function () {},

/**
 * @method removeAnimationByName
 * @param {const char*}
 */
removeAnimationByName : function () {},

/**
 * @method addAnimation
 * @param {cocos2d::CCAnimation*}
 * @param {const char*}
 */
addAnimation : function () {},

/**
 * @method purgeSharedAnimationCache
 */
purgeSharedAnimationCache : function () {},

/**
 * @method sharedAnimationCache
 * @return A value converted from C/C++ "cocos2d::CCAnimationCache*"
 */
sharedAnimationCache : function () {},

/**
 * @method CCAnimationCache
 * @constructor
 */
CCAnimationCache : function () {},

};

/**
 * @class CCSpriteFrameCache
 */
cc.CCSpriteFrameCache = {

/**
 * @method addSpriteFrame
 * @param {cocos2d::CCSpriteFrame*}
 * @param {const char*}
 */
addSpriteFrame : function () {},

/**
 * @method removeUnusedSpriteFrames
 */
removeUnusedSpriteFrames : function () {},

/**
 * @method spriteFrameByName
 * @return A value converted from C/C++ "cocos2d::CCSpriteFrame*"
 * @param {const char*}
 */
spriteFrameByName : function () {},

/**
 * @method removeSpriteFramesFromFile
 * @param {const char*}
 */
removeSpriteFramesFromFile : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method removeSpriteFrames
 */
removeSpriteFrames : function () {},

/**
 * @method removeSpriteFramesFromTexture
 * @param {cocos2d::CCTexture2D*}
 */
removeSpriteFramesFromTexture : function () {},

/**
 * @method removeSpriteFrameByName
 * @param {const char*}
 */
removeSpriteFrameByName : function () {},

/**
 * @method purgeSharedSpriteFrameCache
 */
purgeSharedSpriteFrameCache : function () {},

/**
 * @method sharedSpriteFrameCache
 * @return A value converted from C/C++ "cocos2d::CCSpriteFrameCache*"
 */
sharedSpriteFrameCache : function () {},

};

/**
 * @class CCTextureCache
 */
cc.CCTextureCache = {

/**
 * @method dumpCachedTextureInfo
 */
dumpCachedTextureInfo : function () {},

/**
 * @method addUIImage
 * @return A value converted from C/C++ "cocos2d::CCTexture2D*"
 * @param {cocos2d::CCImage*}
 * @param {const char*}
 */
addUIImage : function () {},

/**
 * @method removeTextureForKey
 * @param {const char*}
 */
removeTextureForKey : function () {},

/**
 * @method textureForKey
 * @return A value converted from C/C++ "cocos2d::CCTexture2D*"
 * @param {const char*}
 */
textureForKey : function () {},

/**
 * @method snapshotTextures
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 */
snapshotTextures : function () {},

/**
 * @method addPVRImage
 * @return A value converted from C/C++ "cocos2d::CCTexture2D*"
 * @param {const char*}
 */
addPVRImage : function () {},

/**
 * @method addImage
 * @return A value converted from C/C++ "cocos2d::CCTexture2D*"
 * @param {const char*}
 */
addImage : function () {},

/**
 * @method removeAllTextures
 */
removeAllTextures : function () {},

/**
 * @method removeUnusedTextures
 */
removeUnusedTextures : function () {},

/**
 * @method removeTexture
 * @param {cocos2d::CCTexture2D*}
 */
removeTexture : function () {},

/**
 * @method purgeSharedTextureCache
 */
purgeSharedTextureCache : function () {},

/**
 * @method reloadAllTextures
 */
reloadAllTextures : function () {},

/**
 * @method sharedTextureCache
 * @return A value converted from C/C++ "cocos2d::CCTextureCache*"
 */
sharedTextureCache : function () {},

/**
 * @method CCTextureCache
 * @constructor
 */
CCTextureCache : function () {},

};

/**
 * @class CCParallaxNode
 */
cc.CCParallaxNode = {

/**
 * @method visit
 */
visit : function () {},

/**
 * @method removeAllChildrenWithCleanup
 * @param {bool}
 */
removeAllChildrenWithCleanup : function () {},

/**
 * @method removeChild
 * @param {cocos2d::CCNode*}
 * @param {bool}
 */
removeChild : function () {},

/**
 * @method getParallaxArray
 * @return A value converted from C/C++ "_ccArray*"
 */
getParallaxArray : function () {},

/**
 * @method setParallaxArray
 * @param {_ccArray*}
 */
setParallaxArray : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::CCParallaxNode*"
 */
node : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCParallaxNode*"
 */
create : function () {},

/**
 * @method CCParallaxNode
 * @constructor
 */
CCParallaxNode : function () {},

};

/**
 * @class CCTMXObjectGroup
 */
cc.CCTMXObjectGroup = {

/**
 * @method setPositionOffset
 * @param {cocos2d::CCPoint}
 */
setPositionOffset : function () {},

/**
 * @method objectNamed
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 * @param {const char*}
 */
objectNamed : function () {},

/**
 * @method getPositionOffset
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getPositionOffset : function () {},

/**
 * @method getObjects
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getObjects : function () {},

/**
 * @method setGroupName
 * @param {const char*}
 */
setGroupName : function () {},

/**
 * @method getProperties
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 */
getProperties : function () {},

/**
 * @method getGroupName
 * @return A value converted from C/C++ "const char*"
 */
getGroupName : function () {},

/**
 * @method setProperties
 * @param {cocos2d::CCDictionary*}
 */
setProperties : function () {},

/**
 * @method propertyNamed
 * @return A value converted from C/C++ "cocos2d::CCString*"
 * @param {const char*}
 */
propertyNamed : function () {},

/**
 * @method setObjects
 * @param {cocos2d::CCArray*}
 */
setObjects : function () {},

/**
 * @method CCTMXObjectGroup
 * @constructor
 */
CCTMXObjectGroup : function () {},

};

/**
 * @class CCTMXLayerInfo
 */
cc.CCTMXLayerInfo = {

/**
 * @method setProperties
 * @param {cocos2d::CCDictionary*}
 */
setProperties : function () {},

/**
 * @method getProperties
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 */
getProperties : function () {},

/**
 * @method CCTMXLayerInfo
 * @constructor
 */
CCTMXLayerInfo : function () {},

};

/**
 * @class CCTMXTilesetInfo
 */
cc.CCTMXTilesetInfo = {

/**
 * @method rectForGID
 * @return A value converted from C/C++ "cocos2d::CCRect"
 * @param {unsigned int}
 */
rectForGID : function () {},

/**
 * @method CCTMXTilesetInfo
 * @constructor
 */
CCTMXTilesetInfo : function () {},

};

/**
 * @class CCTMXMapInfo
 */
cc.CCTMXMapInfo = {

/**
 * @method getTileProperties
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 */
getTileProperties : function () {},

/**
 * @method setObjectGroups
 * @param {cocos2d::CCArray*}
 */
setObjectGroups : function () {},

/**
 * @method setTileSize
 * @param {cocos2d::CCSize}
 */
setTileSize : function () {},

/**
 * @method initWithTMXFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
initWithTMXFile : function () {},

/**
 * @method getOrientation
 * @return A value converted from C/C++ "int"
 */
getOrientation : function () {},

/**
 * @method setTMXFileName
 * @param {const char*}
 */
setTMXFileName : function () {},

/**
 * @method setLayers
 * @param {cocos2d::CCArray*}
 */
setLayers : function () {},

/**
 * @method setStoringCharacters
 * @param {bool}
 */
setStoringCharacters : function () {},

/**
 * @method getStoringCharacters
 * @return A value converted from C/C++ "bool"
 */
getStoringCharacters : function () {},

/**
 * @method getParentElement
 * @return A value converted from C/C++ "int"
 */
getParentElement : function () {},

/**
 * @method getLayerAttribs
 * @return A value converted from C/C++ "int"
 */
getLayerAttribs : function () {},

/**
 * @method getLayers
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getLayers : function () {},

/**
 * @method getTilesets
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getTilesets : function () {},

/**
 * @method getParentGID
 * @return A value converted from C/C++ "unsigned int"
 */
getParentGID : function () {},

/**
 * @method setParentElement
 * @param {int}
 */
setParentElement : function () {},

/**
 * @method setProperties
 * @param {cocos2d::CCDictionary*}
 */
setProperties : function () {},

/**
 * @method setParentGID
 * @param {unsigned int}
 */
setParentGID : function () {},

/**
 * @method parseXMLString
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
parseXMLString : function () {},

/**
 * @method getTileSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getTileSize : function () {},

/**
 * @method getObjectGroups
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getObjectGroups : function () {},

/**
 * @method setLayerAttribs
 * @param {int}
 */
setLayerAttribs : function () {},

/**
 * @method getTMXFileName
 * @return A value converted from C/C++ "const char*"
 */
getTMXFileName : function () {},

/**
 * @method setCurrentString
 * @param {const char*}
 */
setCurrentString : function () {},

/**
 * @method initWithXML
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {const char*}
 */
initWithXML : function () {},

/**
 * @method setOrientation
 * @param {int}
 */
setOrientation : function () {},

/**
 * @method setTileProperties
 * @param {cocos2d::CCDictionary*}
 */
setTileProperties : function () {},

/**
 * @method setMapSize
 * @param {cocos2d::CCSize}
 */
setMapSize : function () {},

/**
 * @method parseXMLFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
parseXMLFile : function () {},

/**
 * @method getMapSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getMapSize : function () {},

/**
 * @method setTilesets
 * @param {cocos2d::CCArray*}
 */
setTilesets : function () {},

/**
 * @method getProperties
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 */
getProperties : function () {},

/**
 * @method getCurrentString
 * @return A value converted from C/C++ "const char*"
 */
getCurrentString : function () {},

/**
 * @method formatWithTMXFile
 * @return A value converted from C/C++ "cocos2d::CCTMXMapInfo*"
 * @param {const char*}
 */
formatWithTMXFile : function () {},

/**
 * @method formatWithXML
 * @return A value converted from C/C++ "cocos2d::CCTMXMapInfo*"
 * @param {const char*}
 * @param {const char*}
 */
formatWithXML : function () {},

/**
 * @method CCTMXMapInfo
 * @constructor
 */
CCTMXMapInfo : function () {},

};

/**
 * @class CCTMXLayer
 */
cc.CCTMXLayer = {

/**
 * @method addChild
 * @param {cocos2d::CCNode*}
 * @param {int}
 * @param {int}
 */
addChild : function () {},

/**
 * @method positionAt
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 * @param {cocos2d::CCPoint}
 */
positionAt : function () {},

/**
 * @method setLayerOrientation
 * @param {unsigned int}
 */
setLayerOrientation : function () {},

/**
 * @method getTiles
 * @return A value converted from C/C++ "unsigned int*"
 */
getTiles : function () {},

/**
 * @method releaseMap
 */
releaseMap : function () {},

/**
 * @method setTiles
 * @param {unsigned int*}
 */
setTiles : function () {},

/**
 * @method getLayerSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getLayerSize : function () {},

/**
 * @method setMapTileSize
 * @param {cocos2d::CCSize}
 */
setMapTileSize : function () {},

/**
 * @method getLayerOrientation
 * @return A value converted from C/C++ "unsigned int"
 */
getLayerOrientation : function () {},

/**
 * @method setProperties
 * @param {cocos2d::CCDictionary*}
 */
setProperties : function () {},

/**
 * @method setLayerName
 * @param {const char*}
 */
setLayerName : function () {},

/**
 * @method removeTileAt
 * @param {cocos2d::CCPoint}
 */
removeTileAt : function () {},

/**
 * @method initWithTilesetInfo
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCTMXTilesetInfo*}
 * @param {cocos2d::CCTMXLayerInfo*}
 * @param {cocos2d::CCTMXMapInfo*}
 */
initWithTilesetInfo : function () {},

/**
 * @method setupTiles
 */
setupTiles : function () {},

/**
 * @method getMapTileSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getMapTileSize : function () {},

/**
 * @method propertyNamed
 * @return A value converted from C/C++ "cocos2d::CCString*"
 * @param {const char*}
 */
propertyNamed : function () {},

/**
 * @method setLayerSize
 * @param {cocos2d::CCSize}
 */
setLayerSize : function () {},

/**
 * @method getLayerName
 * @return A value converted from C/C++ "const char*"
 */
getLayerName : function () {},

/**
 * @method setTileSet
 * @param {cocos2d::CCTMXTilesetInfo*}
 */
setTileSet : function () {},

/**
 * @method removeChild
 * @param {cocos2d::CCNode*}
 * @param {bool}
 */
removeChild : function () {},

/**
 * @method getTileSet
 * @return A value converted from C/C++ "cocos2d::CCTMXTilesetInfo*"
 */
getTileSet : function () {},

/**
 * @method getProperties
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 */
getProperties : function () {},

/**
 * @method tileAt
 * @return A value converted from C/C++ "cocos2d::CCSprite*"
 * @param {cocos2d::CCPoint}
 */
tileAt : function () {},

/**
 * @method layerWithTilesetInfo
 * @return A value converted from C/C++ "cocos2d::CCTMXLayer*"
 * @param {cocos2d::CCTMXTilesetInfo*}
 * @param {cocos2d::CCTMXLayerInfo*}
 * @param {cocos2d::CCTMXMapInfo*}
 */
layerWithTilesetInfo : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTMXLayer*"
 * @param {cocos2d::CCTMXTilesetInfo*}
 * @param {cocos2d::CCTMXLayerInfo*}
 * @param {cocos2d::CCTMXMapInfo*}
 */
create : function () {},

/**
 * @method CCTMXLayer
 * @constructor
 */
CCTMXLayer : function () {},

};

/**
 * @class CCTMXTiledMap
 */
cc.CCTMXTiledMap = {

/**
 * @method propertiesForGID
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 * @param {int}
 */
propertiesForGID : function () {},

/**
 * @method setObjectGroups
 * @param {cocos2d::CCArray*}
 */
setObjectGroups : function () {},

/**
 * @method setTileSize
 * @param {cocos2d::CCSize}
 */
setTileSize : function () {},

/**
 * @method setMapSize
 * @param {cocos2d::CCSize}
 */
setMapSize : function () {},

/**
 * @method getTileSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getTileSize : function () {},

/**
 * @method getObjectGroups
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getObjectGroups : function () {},

/**
 * @method initWithXML
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {const char*}
 */
initWithXML : function () {},

/**
 * @method initWithTMXFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
initWithTMXFile : function () {},

/**
 * @method objectGroupNamed
 * @return A value converted from C/C++ "cocos2d::CCTMXObjectGroup*"
 * @param {const char*}
 */
objectGroupNamed : function () {},

/**
 * @method getMapSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getMapSize : function () {},

/**
 * @method getProperties
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 */
getProperties : function () {},

/**
 * @method setMapOrientation
 * @param {int}
 */
setMapOrientation : function () {},

/**
 * @method setProperties
 * @param {cocos2d::CCDictionary*}
 */
setProperties : function () {},

/**
 * @method layerNamed
 * @return A value converted from C/C++ "cocos2d::CCTMXLayer*"
 * @param {const char*}
 */
layerNamed : function () {},

/**
 * @method getMapOrientation
 * @return A value converted from C/C++ "int"
 */
getMapOrientation : function () {},

/**
 * @method propertyNamed
 * @return A value converted from C/C++ "cocos2d::CCString*"
 * @param {const char*}
 */
propertyNamed : function () {},

/**
 * @method tiledMapWithTMXFile
 * @return A value converted from C/C++ "cocos2d::CCTMXTiledMap*"
 * @param {const char*}
 */
tiledMapWithTMXFile : function () {},

/**
 * @method tiledMapWithXML
 * @return A value converted from C/C++ "cocos2d::CCTMXTiledMap*"
 * @param {const char*}
 * @param {const char*}
 */
tiledMapWithXML : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTMXTiledMap*"
 * @param {const char*}
 */
create : function () {},

/**
 * @method createWithXML
 * @return A value converted from C/C++ "cocos2d::CCTMXTiledMap*"
 * @param {const char*}
 * @param {const char*}
 */
createWithXML : function () {},

/**
 * @method CCTMXTiledMap
 * @constructor
 */
CCTMXTiledMap : function () {},

};

/**
 * @class CCTileMapAtlas
 */
cc.CCTileMapAtlas = {

/**
 * @method initWithTileFile
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 * @param {const char*}
 * @param {int}
 * @param {int}
 */
initWithTileFile : function () {},

/**
 * @method releaseMap
 */
releaseMap : function () {},

/**
 * @method getTGAInfo
 * @return A value converted from C/C++ "sImageTGA*"
 */
getTGAInfo : function () {},

/**
 * @method tileAt
 * @return A value converted from C/C++ "ccColor3B"
 * @param {cocos2d::ccGridSize}
 */
tileAt : function () {},

/**
 * @method setTile
 * @param {cocos2d::ccColor3B}
 * @param {cocos2d::ccGridSize}
 */
setTile : function () {},

/**
 * @method setTGAInfo
 * @param {sImageTGA*}
 */
setTGAInfo : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocos2d::CCTileMapAtlas*"
 * @param {const char*}
 * @param {const char*}
 * @param {int}
 * @param {int}
 */
create : function () {},

/**
 * @method tileMapAtlasWithTileFile
 * @return A value converted from C/C++ "cocos2d::CCTileMapAtlas*"
 * @param {const char*}
 * @param {const char*}
 * @param {int}
 * @param {int}
 */
tileMapAtlasWithTileFile : function () {},

/**
 * @method CCTileMapAtlas
 * @constructor
 */
CCTileMapAtlas : function () {},

};

/**
 * @class CCTimer
 */
cc.CCTimer = {

/**
 * @method getInterval
 * @return A value converted from C/C++ "float"
 */
getInterval : function () {},

/**
 * @method setInterval
 * @param {float}
 */
setInterval : function () {},

/**
 * @method initWithScriptHandler
 * @return A value converted from C/C++ "bool"
 * @param {int}
 * @param {float}
 */
initWithScriptHandler : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getScriptHandler
 * @return A value converted from C/C++ "int"
 */
getScriptHandler : function () {},

/**
 * @method timerWithScriptHandler
 * @return A value converted from C/C++ "cocos2d::CCTimer*"
 * @param {int}
 * @param {float}
 */
timerWithScriptHandler : function () {},

/**
 * @method CCTimer
 * @constructor
 */
CCTimer : function () {},

};

/**
 * @class CCScheduler
 */
cc.CCScheduler = {

/**
 * @method setTimeScale
 * @param {float}
 */
setTimeScale : function () {},

/**
 * @method unscheduleUpdateForTarget
 * @param {cocos2d::CCObject*}
 */
unscheduleUpdateForTarget : function () {},

/**
 * @method scheduleUpdateForTarget
 * @param {cocos2d::CCObject*}
 * @param {int}
 * @param {bool}
 */
scheduleUpdateForTarget : function () {},

/**
 * @method unscheduleAll
 */
unscheduleAll : function () {},

/**
 * @method unscheduleAllWithMinPriority
 * @param {int}
 */
unscheduleAllWithMinPriority : function () {},

/**
 * @method isTargetPaused
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCObject*}
 */
isTargetPaused : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method unscheduleScriptEntry
 * @param {unsigned int}
 */
unscheduleScriptEntry : function () {},

/**
 * @method unscheduleAllForTarget
 * @param {cocos2d::CCObject*}
 */
unscheduleAllForTarget : function () {},

/**
 * @method scheduleScriptFunc
 * @return A value converted from C/C++ "unsigned int"
 * @param {unsigned int}
 * @param {float}
 * @param {bool}
 */
scheduleScriptFunc : function () {},

/**
 * @method getTimeScale
 * @return A value converted from C/C++ "float"
 */
getTimeScale : function () {},

/**
 * @method CCScheduler
 * @constructor
 */
CCScheduler : function () {},

};

/**
 * @class SimpleAudioEngine
 */
cc.SimpleAudioEngine = {

/**
 * @method stopAllEffects
 */
stopAllEffects : function () {},

/**
 * @method getBackgroundMusicVolume
 * @return A value converted from C/C++ "float"
 */
getBackgroundMusicVolume : function () {},

/**
 * @method isBackgroundMusicPlaying
 * @return A value converted from C/C++ "bool"
 */
isBackgroundMusicPlaying : function () {},

/**
 * @method getEffectsVolume
 * @return A value converted from C/C++ "float"
 */
getEffectsVolume : function () {},

/**
 * @method setBackgroundMusicVolume
 * @param {float}
 */
setBackgroundMusicVolume : function () {},

/**
 * @method stopEffect
 * @param {unsigned int}
 */
stopEffect : function () {},

/**
 * @method pauseAllEffects
 */
pauseAllEffects : function () {},

/**
 * @method preloadBackgroundMusic
 * @param {const char*}
 */
preloadBackgroundMusic : function () {},

/**
 * @method resumeBackgroundMusic
 */
resumeBackgroundMusic : function () {},

/**
 * @method rewindBackgroundMusic
 */
rewindBackgroundMusic : function () {},

/**
 * @method willPlayBackgroundMusic
 * @return A value converted from C/C++ "bool"
 */
willPlayBackgroundMusic : function () {},

/**
 * @method unloadEffect
 * @param {const char*}
 */
unloadEffect : function () {},

/**
 * @method preloadEffect
 * @param {const char*}
 */
preloadEffect : function () {},

/**
 * @method setEffectsVolume
 * @param {float}
 */
setEffectsVolume : function () {},

/**
 * @method pauseEffect
 * @param {unsigned int}
 */
pauseEffect : function () {},

/**
 * @method getClassTypeInfo
 * @return A value converted from C/C++ "long"
 */
getClassTypeInfo : function () {},

/**
 * @method resumeAllEffects
 */
resumeAllEffects : function () {},

/**
 * @method pauseBackgroundMusic
 */
pauseBackgroundMusic : function () {},

/**
 * @method resumeEffect
 * @param {unsigned int}
 */
resumeEffect : function () {},

/**
 * @method end
 */
end : function () {},

/**
 * @method sharedEngine
 * @return A value converted from C/C++ "CocosDenshion::SimpleAudioEngine*"
 */
sharedEngine : function () {},

};

/**
 * @class CCBReader
 */
cc.CCBReader = {

/**
 * @method getOwnerCallbackNames
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getOwnerCallbackNames : function () {},

/**
 * @method setCCBRootPath
 * @param {const char*}
 */
setCCBRootPath : function () {},

/**
 * @method getOwnerCallbackNodes
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getOwnerCallbackNodes : function () {},

/**
 * @method getOwnerOutletNames
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getOwnerOutletNames : function () {},

/**
 * @method getCCBRootPath
 * @return A value converted from C/C++ "std::string"
 */
getCCBRootPath : function () {},

/**
 * @method getOwnerOutletNodes
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getOwnerOutletNodes : function () {},

/**
 * @method readUTF8
 * @return A value converted from C/C++ "std::string"
 */
readUTF8 : function () {},

/**
 * @method setAnimationManager
 * @param {cocos2d::extension::CCBAnimationManager*}
 */
setAnimationManager : function () {},

/**
 * @method getAnimationManagersForNodes
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getAnimationManagersForNodes : function () {},

/**
 * @method getNodesWithAnimationManagers
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getNodesWithAnimationManagers : function () {},

/**
 * @method getAnimationManager
 * @return A value converted from C/C++ "cocos2d::extension::CCBAnimationManager*"
 */
getAnimationManager : function () {},

};

/**
 * @class CCScale9Sprite
 */
cc.CCScale9Sprite = {

/**
 * @method getCapInsets
 * @return A value converted from C/C++ "cocos2d::CCRect"
 */
getCapInsets : function () {},

/**
 * @method updateWithBatchNode
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCSpriteBatchNode*}
 * @param {cocos2d::CCRect}
 * @param {bool}
 * @param {cocos2d::CCRect}
 */
updateWithBatchNode : function () {},

/**
 * @method setInsetBottom
 * @param {float}
 */
setInsetBottom : function () {},

/**
 * @method visit
 */
visit : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method setInsetTop
 * @param {float}
 */
setInsetTop : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setPreferredSize
 * @param {cocos2d::CCSize}
 */
setPreferredSize : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method setSpriteFrame
 * @param {cocos2d::CCSpriteFrame*}
 */
setSpriteFrame : function () {},

/**
 * @method getColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getColor : function () {},

/**
 * @method getInsetBottom
 * @return A value converted from C/C++ "float"
 */
getInsetBottom : function () {},

/**
 * @method resizableSpriteWithCapInsets
 * @return A value converted from C/C++ "cocos2d::extension::CCScale9Sprite*"
 * @param {cocos2d::CCRect}
 */
resizableSpriteWithCapInsets : function () {},

/**
 * @method setContentSize
 * @param {cocos2d::CCSize}
 */
setContentSize : function () {},

/**
 * @method getInsetRight
 * @return A value converted from C/C++ "float"
 */
getInsetRight : function () {},

/**
 * @method getOriginalSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getOriginalSize : function () {},

/**
 * @method setColor
 * @param {cocos2d::ccColor3B}
 */
setColor : function () {},

/**
 * @method getInsetTop
 * @return A value converted from C/C++ "float"
 */
getInsetTop : function () {},

/**
 * @method setInsetLeft
 * @param {float}
 */
setInsetLeft : function () {},

/**
 * @method getPreferredSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getPreferredSize : function () {},

/**
 * @method setCapInsets
 * @param {cocos2d::CCRect}
 */
setCapInsets : function () {},

/**
 * @method getInsetLeft
 * @return A value converted from C/C++ "float"
 */
getInsetLeft : function () {},

/**
 * @method setInsetRight
 * @param {float}
 */
setInsetRight : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::extension::CCScale9Sprite*"
 */
node : function () {},

/**
 * @method CCScale9Sprite
 * @constructor
 */
CCScale9Sprite : function () {},

};

/**
 * @class CCControlButton
 */
cc.CCControlButton = {

/**
 * @method setTitleColorDispatchTable
 * @param {cocos2d::CCDictionary*}
 */
setTitleColorDispatchTable : function () {},

/**
 * @method isPushed
 * @return A value converted from C/C++ "bool"
 */
isPushed : function () {},

/**
 * @method setSelected
 * @param {bool}
 */
setSelected : function () {},

/**
 * @method setTitleLabel
 * @param {cocos2d::CCNode*}
 */
setTitleLabel : function () {},

/**
 * @method ccTouchBegan
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCTouch*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchBegan : function () {},

/**
 * @method setTitleTTFSizeForState
 * @param {float}
 * @param {unsigned int}
 */
setTitleTTFSizeForState : function () {},

/**
 * @method setAdjustBackgroundImage
 * @param {bool}
 */
setAdjustBackgroundImage : function () {},

/**
 * @method ccTouchEnded
 * @param {cocos2d::CCTouch*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchEnded : function () {},

/**
 * @method setHighlighted
 * @param {bool}
 */
setHighlighted : function () {},

/**
 * @method setBackgroundSpriteDispatchTable
 * @param {cocos2d::CCDictionary*}
 */
setBackgroundSpriteDispatchTable : function () {},

/**
 * @method setZoomOnTouchDown
 * @param {bool}
 */
setZoomOnTouchDown : function () {},

/**
 * @method getTitleDispatchTable
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 */
getTitleDispatchTable : function () {},

/**
 * @method setLabelAnchorPoint
 * @param {cocos2d::CCPoint}
 */
setLabelAnchorPoint : function () {},

/**
 * @method ccTouchCancelled
 * @param {cocos2d::CCTouch*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchCancelled : function () {},

/**
 * @method getLabelAnchorPoint
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getLabelAnchorPoint : function () {},

/**
 * @method initWithBackgroundSprite
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::extension::CCScale9Sprite*}
 */
initWithBackgroundSprite : function () {},

/**
 * @method getTitleTTFSizeForState
 * @return A value converted from C/C++ "float"
 * @param {unsigned int}
 */
getTitleTTFSizeForState : function () {},

/**
 * @method setTitleDispatchTable
 * @param {cocos2d::CCDictionary*}
 */
setTitleDispatchTable : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setTitleTTFForState
 * @param {const char*}
 * @param {unsigned int}
 */
setTitleTTFForState : function () {},

/**
 * @method setPreferredSize
 * @param {cocos2d::CCSize}
 */
setPreferredSize : function () {},

/**
 * @method setTitleLabelForState
 * @param {cocos2d::CCNode*}
 * @param {unsigned int}
 */
setTitleLabelForState : function () {},

/**
 * @method ccTouchMoved
 * @param {cocos2d::CCTouch*}
 * @param {cocos2d::CCEvent*}
 */
ccTouchMoved : function () {},

/**
 * @method getOpacity
 * @return A value converted from C/C++ "unsigned char"
 */
getOpacity : function () {},

/**
 * @method getCurrentTitleColor
 * @return A value converted from C/C++ "ccColor3B"
 */
getCurrentTitleColor : function () {},

/**
 * @method getTitleColorDispatchTable
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 */
getTitleColorDispatchTable : function () {},

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method getBackgroundSpriteForState
 * @return A value converted from C/C++ "cocos2d::extension::CCScale9Sprite*"
 * @param {unsigned int}
 */
getBackgroundSpriteForState : function () {},

/**
 * @method getHorizontalOrigin
 * @return A value converted from C/C++ "int"
 */
getHorizontalOrigin : function () {},

/**
 * @method setMargins
 * @param {int}
 * @param {int}
 */
setMargins : function () {},

/**
 * @method needsLayout
 */
needsLayout : function () {},

/**
 * @method initWithTitleAndFontNameAndFontSize
 * @return A value converted from C/C++ "bool"
 * @param {std::string}
 * @param {const char*}
 * @param {float}
 */
initWithTitleAndFontNameAndFontSize : function () {},

/**
 * @method setTitleBMFontForState
 * @param {const char*}
 * @param {unsigned int}
 */
setTitleBMFontForState : function () {},

/**
 * @method getTitleTTFForState
 * @return A value converted from C/C++ "const char*"
 * @param {unsigned int}
 */
getTitleTTFForState : function () {},

/**
 * @method getBackgroundSprite
 * @return A value converted from C/C++ "cocos2d::extension::CCScale9Sprite*"
 */
getBackgroundSprite : function () {},

/**
 * @method getTitleColorForState
 * @return A value converted from C/C++ "const ccColor3B"
 * @param {unsigned int}
 */
getTitleColorForState : function () {},

/**
 * @method setTitleColorForState
 * @param {ccColor3B}
 * @param {unsigned int}
 */
setTitleColorForState : function () {},

/**
 * @method doesAdjustBackgroundImage
 * @return A value converted from C/C++ "bool"
 */
doesAdjustBackgroundImage : function () {},

/**
 * @method setBackgroundSpriteFrameForState
 * @param {cocos2d::CCSpriteFrame*}
 * @param {unsigned int}
 */
setBackgroundSpriteFrameForState : function () {},

/**
 * @method setBackgroundSpriteForState
 * @param {cocos2d::extension::CCScale9Sprite*}
 * @param {unsigned int}
 */
setBackgroundSpriteForState : function () {},

/**
 * @method getTitleLabelDispatchTable
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 */
getTitleLabelDispatchTable : function () {},

/**
 * @method initWithLabelAndBackgroundSprite
 * @return A value converted from C/C++ "bool"
 * @param {cocos2d::CCNode*}
 * @param {cocos2d::extension::CCScale9Sprite*}
 */
initWithLabelAndBackgroundSprite : function () {},

/**
 * @method setTitleLabelDispatchTable
 * @param {cocos2d::CCDictionary*}
 */
setTitleLabelDispatchTable : function () {},

/**
 * @method getTitleLabel
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
getTitleLabel : function () {},

/**
 * @method getPreferredSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getPreferredSize : function () {},

/**
 * @method getVerticalMargin
 * @return A value converted from C/C++ "int"
 */
getVerticalMargin : function () {},

/**
 * @method getBackgroundSpriteDispatchTable
 * @return A value converted from C/C++ "cocos2d::CCDictionary*"
 */
getBackgroundSpriteDispatchTable : function () {},

/**
 * @method getTitleLabelForState
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 * @param {unsigned int}
 */
getTitleLabelForState : function () {},

/**
 * @method getCurrentTitle
 * @return A value converted from C/C++ "cocos2d::CCString*"
 */
getCurrentTitle : function () {},

/**
 * @method getTitleBMFontForState
 * @return A value converted from C/C++ "const char*"
 * @param {unsigned int}
 */
getTitleBMFontForState : function () {},

/**
 * @method setTitleForState
 * @param {cocos2d::CCString*}
 * @param {unsigned int}
 */
setTitleForState : function () {},

/**
 * @method setBackgroundSprite
 * @param {cocos2d::extension::CCScale9Sprite*}
 */
setBackgroundSprite : function () {},

/**
 * @method getZoomOnTouchDown
 * @return A value converted from C/C++ "bool"
 */
getZoomOnTouchDown : function () {},

/**
 * @method getTitleForState
 * @return A value converted from C/C++ "cocos2d::CCString*"
 * @param {unsigned int}
 */
getTitleForState : function () {},

/**
 * @method buttonWithLabelAndBackgroundSprite
 * @return A value converted from C/C++ "cocos2d::extension::CCControlButton*"
 * @param {cocos2d::CCNode*}
 * @param {cocos2d::extension::CCScale9Sprite*}
 */
buttonWithLabelAndBackgroundSprite : function () {},

/**
 * @method buttonWithBackgroundSprite
 * @return A value converted from C/C++ "cocos2d::extension::CCControlButton*"
 * @param {cocos2d::extension::CCScale9Sprite*}
 */
buttonWithBackgroundSprite : function () {},

/**
 * @method buttonWithTitleAndFontNameAndFontSize
 * @return A value converted from C/C++ "cocos2d::extension::CCControlButton*"
 * @param {std::string}
 * @param {const char*}
 * @param {float}
 */
buttonWithTitleAndFontNameAndFontSize : function () {},

/**
 * @method node
 * @return A value converted from C/C++ "cocos2d::extension::CCControlButton*"
 */
node : function () {},

/**
 * @method CCControlButton
 * @constructor
 */
CCControlButton : function () {},

};

/**
 * @class CCBAnimationManager
 */
cc.CCBAnimationManager = {

/**
 * @method moveAnimationsFromNode
 * @param {cocos2d::CCNode*}
 * @param {cocos2d::CCNode*}
 */
moveAnimationsFromNode : function () {},

/**
 * @method setAutoPlaySequenceId
 * @param {int}
 */
setAutoPlaySequenceId : function () {},

/**
 * @method getDocumentCallbackNames
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getDocumentCallbackNames : function () {},

/**
 * @method setBaseValue
 * @param {cocos2d::CCObject*}
 * @param {cocos2d::CCNode*}
 * @param {const char*}
 */
setBaseValue : function () {},

/**
 * @method getDocumentOutletNodes
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getDocumentOutletNodes : function () {},

/**
 * @method addNode
 * @param {cocos2d::CCNode*}
 * @param {cocos2d::CCDictionary*}
 */
addNode : function () {},

/**
 * @method getLastCompletedSequenceName
 * @return A value converted from C/C++ "std::string"
 */
getLastCompletedSequenceName : function () {},

/**
 * @method setRootNode
 * @param {cocos2d::CCNode*}
 */
setRootNode : function () {},

/**
 * @method addDocumentOutletName
 * @param {std::string}
 */
addDocumentOutletName : function () {},

/**
 * @method getSequences
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getSequences : function () {},

/**
 * @method getRootContainerSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getRootContainerSize : function () {},

/**
 * @method setDocumentControllerName
 * @param {std::string}
 */
setDocumentControllerName : function () {},

/**
 * @method getContainerSize
 * @return A value converted from C/C++ "cocos2d::CCSize"
 * @param {cocos2d::CCNode*}
 */
getContainerSize : function () {},

/**
 * @method getDocumentOutletNames
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getDocumentOutletNames : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method runAnimationsForSequenceNamedTweenDuration
 * @param {const char*}
 * @param {float}
 */
runAnimationsForSequenceNamedTweenDuration : function () {},

/**
 * @method setRootContainerSize
 * @param {cocos2d::CCSize}
 */
setRootContainerSize : function () {},

/**
 * @method runAnimationsForSequenceIdTweenDuration
 * @param {int}
 * @param {float}
 */
runAnimationsForSequenceIdTweenDuration : function () {},

/**
 * @method getRunningSequenceName
 * @return A value converted from C/C++ "const char*"
 */
getRunningSequenceName : function () {},

/**
 * @method getAutoPlaySequenceId
 * @return A value converted from C/C++ "int"
 */
getAutoPlaySequenceId : function () {},

/**
 * @method addDocumentCallbackName
 * @param {std::string}
 */
addDocumentCallbackName : function () {},

/**
 * @method getRootNode
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
getRootNode : function () {},

/**
 * @method addDocumentOutletNode
 * @param {cocos2d::CCNode*}
 */
addDocumentOutletNode : function () {},

/**
 * @method setDelegate
 * @param {cocos2d::extension::CCBAnimationManagerDelegate*}
 */
setDelegate : function () {},

/**
 * @method addDocumentCallbackNode
 * @param {cocos2d::CCNode*}
 */
addDocumentCallbackNode : function () {},

/**
 * @method getDelegate
 * @return A value converted from C/C++ "cocos2d::extension::CCBAnimationManagerDelegate*"
 */
getDelegate : function () {},

/**
 * @method runAnimationsForSequenceNamed
 * @param {const char*}
 */
runAnimationsForSequenceNamed : function () {},

/**
 * @method getDocumentCallbackNodes
 * @return A value converted from C/C++ "cocos2d::CCArray*"
 */
getDocumentCallbackNodes : function () {},

/**
 * @method setSequences
 * @param {cocos2d::CCArray*}
 */
setSequences : function () {},

/**
 * @method debug
 */
debug : function () {},

/**
 * @method getDocumentControllerName
 * @return A value converted from C/C++ "std::string"
 */
getDocumentControllerName : function () {},

/**
 * @method CCBAnimationManager
 * @constructor
 */
CCBAnimationManager : function () {},

};
