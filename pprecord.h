#include <string>

#ifndef PPRECORD_H
#define PPRECORD_H

enum class PPDataType : short
{
    None = -1,
    String = 1,
    Binary = 3,
    Integer = 4,
    MultiString = 7,
    Sum = 100
};

struct PPValue
{
    unsigned short Size;
    unsigned short NameSize;
    PPDataType DataType;
    unsigned short DataSize;
    unsigned int Unknown1;
    unsigned int Unknown2;
};

class PPRecord
{
public:
    PPValue Record;
    wchar_t* Name;
    void* Data;
    PPRecord();

    std::string GetDataTypeString();
};

#endif // PPRECORD_H
