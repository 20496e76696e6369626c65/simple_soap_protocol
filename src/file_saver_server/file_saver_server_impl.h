#ifndef FILESAVERSERVICEIMPL_H_
#define FILESAVERSERVICEIMPL_H_

#include "soapFileSaverService.h"

class FileSaverServiceImpl : public FileSaverService
{
public:
    FileSaverServiceImpl();
    FileSaverServiceImpl( const FileSaverServiceImpl&);
    FileSaverServiceImpl* copy();

    int saveFile(const std::wstring&, const xsd__base64Binary&, enum ns__ErrorCode*);
    int loadFile(const std::wstring&, ns__loadFileResponse *);
};


#endif
