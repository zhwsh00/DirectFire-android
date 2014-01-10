#ifndef PROPDEF_H
#define PROPDEF_H

#include <string>
#include <iostream>
#include <map>

using namespace std;

class PropDef
{
public:
    PropDef();
    ~PropDef();

    enum VirtualProps{
        Props_Coin = 0,
        Props_Gold,
        //this props releated with social spell
        Props_Clover,
        Props_Rose,
        Props_Staff,
        //below props just used to show
        Props_CrownL1,
        Props_CrownL2,
        Props_CrownL3,
        Props_Crystal1,
        Props_Crystal2,
        Props_Crystal3,
        Props_Gem1,
        Props_Gem2,
        Props_Gem3,
        Props_Vill1,
        Props_Vill2,
        Props_Vill3,
        Props_Heart1,
        Props_Heart2,
        Props_Heart3,
        Props_BlueRose1,
        Props_BlueRose2,
        Props_BlueRose3,
        Props_Cake1,
        Props_Cake2,
        Props_Cake3
    };
    static void getVirtualPropsName(int id,string &name);
    static int getVirtualPropsId(const string &name);

    enum PropRulesType {
        PropRuleType_special = 0,
        PropRuleType_fixed10to1,
        PropRuleType_fixed20to1
    };
    static int getRuleTypeId(const string &name);
    static int propLevelUpId(int id);
    static bool propCanLevelUp(int id);
    static bool propCanUseAble(int id);
    static bool propCanPresentAble(int id);
private:
    static const std::map<string,int> gVirtualPropsMap;
    static std::map<string,int> createPropMap();

    static const std::map<string,int> gRuleTypeMap;
    static std::map<string,int> createRuleTypeMap();
    void doDummy(){}
};

#endif // PROPDEF_H
