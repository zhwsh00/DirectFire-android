#include "moveLabel.h"



MoveLabel::MoveLabel()
{

	m_pStr = NULL;
	m_pLabel = NULL;
	m_fontSize = 20;

	m_pTarget = NULL;
	m_pLabel = NULL;

	m_pStr = NULL;
	m_dimensions = CCSizeMake(0,0);
	m_hAlignment = kCCTextAlignmentLeft;
	m_fontName = NULL;
	m_fontSize = 20;


	m_v = ccp(0,0);
	m_a = ccp(0,0);
}
MoveLabel::~MoveLabel()
{
	if(m_pLabel)
	{
		m_pLabel->release();
		m_pLabel = NULL;
	}
	if(m_pTarget)
	{
	    m_pTarget->release();
	    m_pTarget = NULL;
	}
	
}



void MoveLabel::init(int x,int y,int width,int height)
{
	if(m_pTarget)
	{
		removeChild(m_pTarget,false);
		m_pTarget->release();
	}

	m_rect.setRect(x,y,width,height);
	m_pTarget = CCRenderTexture::create(width, height, kCCTexture2DPixelFormat_RGBA8888);	
	m_pTarget->retain();
	m_pTarget->setPosition(ccp(x, y));
	addChild(m_pTarget,0);

}
void MoveLabel::initStr(char * pStr,CCSize dimensions,CCTextAlignment hAlignment,char* fontName,int fontSize)
{
	if(m_pLabel)
	{
		m_pLabel->release();
	}
	m_pStr = pStr;
	m_dimensions = dimensions;
	m_hAlignment = hAlignment;
	m_fontName = fontName;
	m_fontSize = fontSize;

	int lines = getStrLines();

	m_pLabel = CCLabelTTF::labelWithString(pStr,CCSizeMake(dimensions.width,(lines)*m_fontSize),
		hAlignment,fontName, m_fontSize);

	m_pLabel->setPosition(ccp(0,0));
	m_pLabel->setColor(ccRED);
	m_pLabel->retain();

   m_dimensions.height = (lines)*m_fontSize;

   m_p.x =  m_rect.size.width/2 ;
   m_p.y =  m_rect.size.height-m_dimensions.height/2;

   m_upBorder = m_p.y;
   m_downBorder = m_p.y + m_dimensions.height - m_rect.size.height+2*m_fontSize;
 //  addChild(m_pLabel);
}


void MoveLabel::touchDown(int x,int y)
{

	if(!m_rect.containsPoint(ccp(x+m_rect.size.width/2,y+m_rect.size.height/2)) || !this->isVisible())
	{
		return;
	}
	m_bTouch = true;
	m_down.x = x;
	m_down.y = y;
    m_pre = m_cur = m_down;
	m_count = 0;
	m_v = ccp(0,0);
	m_a = ccp(0,0);
}
void MoveLabel::touchMove(int x,int y)
{

if(!m_bTouch)
{
	return ;
}

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	//m_pLabel->setScaleY(0.8);
	//m_p.y = s.height - y  - (m_pTarget->getPositionY() -  m_rect.size.height/2 ) -m_dimensions.height/2;
	int dy = m_cur.y - m_pre.y;
	m_pre = m_cur;
	m_cur = ccp(x,y);
	m_p.y -= dy;
	m_count++;
}
void MoveLabel::touchUp(int x,int y)
{
	if(!m_bTouch)
  {
	  return ;
  }

	m_bTouch = false;
	m_up.x = x;
	m_up.y = y;
	//m_count = 0;
}





void MoveLabel::setStr(char *pStr)
{
}
char *MoveLabel::getStr()
{
	return m_pStr;
}
int MoveLabel::getStrHeight()
{
	return 0;
}

void MoveLabel::run()
{
	update();
	drawStr();
}

void MoveLabel::update()
{

	if(!m_bTouch)
	{
		if(m_count)
		{
			int len = m_up.y - m_down.y;
			int dy = len/m_count;
			if(dy > 10)
			{
				
				m_v.y = -40;
				m_a.y = 2;
			}
			else if(dy < -10)
			{
				m_v.y = 40;
				m_a.y = -2;


			}
			m_count = 0;
		}
	}

	m_v.y = m_v.y + m_a.y;

	if(m_v.y < 3 && m_v.y > -3)
	{
		m_v.y = 0;
	}
	m_p.y = m_p.y + m_v.y;




	if(m_p.y >=  m_upBorder && m_p.y <= m_downBorder)
	{
    	//m_pLabel->setPosition(m_p);
	}
	else if(m_p.y <  m_upBorder)
	{
		m_p.y =  m_upBorder;
	}
	else 
	{
		m_p.y  = m_downBorder;
	}
	if(m_upBorder > m_downBorder)
	{
		m_p.y =  m_upBorder;
	}
	m_pLabel->setPosition(m_p);
}




void MoveLabel::drawStr()
{
	if(m_pTarget)
	{
	  m_pTarget->clear(0,0,0,1);//清理成黑色，前3个参数为颜色，后一个为透明度。
	  m_pTarget->begin();
	  m_pLabel->visit();
	  m_pTarget->end();
	}
}


int GetUtf8ByteNumByFirstWord(unsigned char firstCh,int &numAsc, int &numCh);
int  MoveLabel::getStrLines()
{
	int i,num = 0,lines = 0;
	char *utf_str = m_pStr;
	int str_bytes = strlen(utf_str);
	int numAsc = 0;
	int numCh  = 0;
	for(i = 0;i<str_bytes ;)
	{
		if(utf_str[i] == 10)
		{
			int len,line;
			len = numAsc*m_fontSize/2 +numCh*m_fontSize;
			line = len/m_dimensions.width;
			if(len - line*m_dimensions.width > 0.01)
			{
				line++;
			}
			if(0 == line)
			{
				line++;
			}
			lines += line;
			numAsc = 0;
			numCh = 0;
		}
		num = GetUtf8ByteNumByFirstWord(utf_str[i],numAsc, numCh);

		i += num;
	}
	lines += (numAsc*m_fontSize/2 +numCh*m_fontSize+m_dimensions.width)/m_dimensions.width ;
	return lines;		
}


int GetUtf8ByteNumByFirstWord(unsigned char firstCh,int &numAsc, int &numCh)
{
	unsigned char temp = 0x80;
	int num = 0;


	if(firstCh < 0x80)//ascii code.(0-127)
	{
		numAsc++;
		return 1;
	}		
	while(temp & firstCh)
	{
		num++;
		temp = (temp >> 1);
	}

	numCh++;
	return num;
}


int GetUTF8LogicStrLen( char* utf_str,int str_bytes,int &numAsc, int &numCh)
{
	int i,num,len = 0;
	numAsc = 0;
	numCh = 0;
	for(i = 0;i<str_bytes;)
	{
		num = GetUtf8ByteNumByFirstWord(utf_str[i],numAsc, numCh);
		len++;
		i += num;
	}
	
	return len;		
}


//Get select char's bytes length by char ID.(根据输入的第几个字符，获取该字符前全部的字节长度)
int GetUTF8BytesByCharID( char* utf_str,int charID)
{
	int i,num,len;
	int numAsc,numCh;
	len = strlen(utf_str);
	if((len < charID)||(charID <0))
		return -1;
	for(i = 0;charID>0;)
	{
		num = GetUtf8ByteNumByFirstWord(utf_str[i],numAsc,numCh);
		i += num;
		charID--;
	}
	
	return i;
}