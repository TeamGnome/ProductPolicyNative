#include "ppobject.h"
#include "list"
#include "malloc.h"
#include "memory.h"
#include "windows.h"
#include "winreg.h"

const wchar_t* const PPObject::REG_KEY = L"SYSTEM\\CurrentControlSet\\Control\\ProductOptions";
const wchar_t* const PPObject::REG_VALUE = L"ProductPolicy";

PPObject::PPObject()
{
    initialiseData();
}

void PPObject::initialiseData()
{
    std::list<PPRecord>* policies = new std::list<PPRecord>;

    HKEY keyHandle;
    DWORD bufferSize = 8192;
    DWORD dataSize = bufferSize;
    byte* registryValue = (byte*)malloc(bufferSize);

    if(RegOpenKey(HKEY_LOCAL_MACHINE, PPObject::REG_KEY, &keyHandle) == ERROR_SUCCESS)
    {
        DWORD retVal = RegQueryValueEx(keyHandle, PPObject::REG_VALUE, NULL, NULL, registryValue, &dataSize);

        while(retVal == ERROR_MORE_DATA)
        {
            bufferSize += 4096;
            dataSize = bufferSize;

            registryValue = (byte*)realloc(registryValue, bufferSize);

            retVal = RegQueryValueEx(keyHandle, PPObject::REG_VALUE, NULL, NULL, registryValue, &dataSize);
        }

        RegCloseKey(keyHandle);
    }
    else
    {
        // ERROR HANDLING HERE
        return;
    }

    memcpy(&Header, registryValue, sizeof(PPHeader));
    unsigned int position = (unsigned int)sizeof(PPHeader);

    while((dataSize - Header.EndMarker) > position)
    {
        unsigned int startPosition = position;
        PPRecord* policy = new PPRecord();

        PPValue* policyVal = (PPValue*)(registryValue + position);
        memcpy(&policy->Record, policyVal, sizeof(PPValue));
        position += sizeof(PPValue);

        wchar_t* policyName = (wchar_t*)(registryValue + position);
        policy->Name = (wchar_t*)malloc(policyVal->NameSize);
        memcpy(policy->Name, policyName, policyVal->NameSize);
        position += policyVal->NameSize;

        policy->Data = malloc(policyVal->DataSize);
        memcpy(policy->Data, (void*)(registryValue + position), policyVal->DataSize);

        position = startPosition += policyVal->Size;
        policies->push_front(*policy);
    }

    Records = *policies;
    free(registryValue);
}
