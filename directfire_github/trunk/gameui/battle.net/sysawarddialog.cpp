#include "sysawarddialog.h"

SysAwardDialog::SysAwardDialog(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{

}
SysAwardDialog::~SysAwardDialog()
{

}
void SysAwardDialog::exec()
{
    finished();
    BasShowDialog::exec();
}
void SysAwardDialog::finished()
{

}
