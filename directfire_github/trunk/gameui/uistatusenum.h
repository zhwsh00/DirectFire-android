#ifndef _uistatusenum_h_
#define _uistatusenum_h_

class UiStatusEnum
{
public:
    UiStatusEnum(){}
    ~UiStatusEnum(){}
    enum UiSt_enum{
        UiSt_null = 0,
        UiSt_mainmenuinit,
        UiSt_mainmenusetting,
        UiSt_quickgame,
        UiSt_campaigngame,
        UiSt_battle,
        UiSt_showlogindialog
    };
};

#endif
