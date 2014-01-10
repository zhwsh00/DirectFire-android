#ifndef _mysrand_h_
#define _mysrand_h_

/* RAND_MAX assumed to be 32767 */
extern int myrand(void);
extern void mysrand(unsigned seed);

class ClientSrandGen
{
public:
    ClientSrandGen(unsigned seed = 0);
    virtual ~ClientSrandGen();
    void setSeed(unsigned seed);
    int mapRand();
    int shootRand();
    int unorderRand();
    int mapApplyed() { return m_mapApplyed;}
    int shootApplyed() { return m_shootApplyed;}
    int unorderApplyed() { return m_unorderApplyed;}
protected:
    unsigned long m_mapSeed;
    unsigned long m_shootSeed;
    unsigned long m_unorderSeed;
protected:
    //Stat.
    int m_mapApplyed;
    int m_shootApplyed;
    int m_unorderApplyed;
};

#endif
