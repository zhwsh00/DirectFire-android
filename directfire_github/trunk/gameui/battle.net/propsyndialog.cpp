#include "propsyndialog.h"

PropSynDialog::PropSynDialog(CCNode *parent,const ccColor4B &color)
    : BasShowDialog(parent,color)
{

}
PropSynDialog::~PropSynDialog()
{

}
void PropSynDialog::exec()
{
    finish();
    BasShowDialog::exec();
}
void PropSynDialog::finish()
{

}
