#include "list"
#include "pprecord.h"

#ifndef PPOBJECT_H
#define PPOBJECT_H

struct PPHeader
{
    unsigned int Size;
    unsigned int DataSize;
    unsigned int EndMarker;
    unsigned int Unknown1;
    unsigned int Unknown2;
};

class PPObject
{
private:
    static const wchar_t* const REG_KEY;
    static const wchar_t* const REG_VALUE;

    void initialiseData();
public:
    PPHeader Header;
    std::list<PPRecord> Records;

    PPObject();
};

#endif // PPOBJECT_H
