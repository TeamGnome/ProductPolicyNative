#include "pprecord.h"

PPRecord::PPRecord()
{

}

std::string PPRecord::GetDataTypeString()
{
    switch(Record.DataType)
    {
    case PPDataType::Binary:
        return std::string((const char*)"Binary");
    case PPDataType::None:
        return std::string((const char*)"None");
    case PPDataType::String:
        return std::string((const char*)"String");
    case PPDataType::Integer:
        return std::string((const char*)"Integer");
    case PPDataType::MultiString:
        return std::string((const char*)"MultiString");
    case PPDataType::Sum:
        return std::string((const char*)"Sum");
    }

    return std::string((const char*)"");
}

std::string PPRecord::GetDataString()
{
    switch(Record.DataType)
    {
    case PPDataType::String:
        return std::string((char*)Data, Record.DataSize);
    case PPDataType::Integer:
        return std::to_string(*(int*)Data);
    }

    return std::string((const char*)"");
}
