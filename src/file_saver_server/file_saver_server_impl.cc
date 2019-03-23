#include "file_saver_server_impl.h"
#include "FileSaver.nsmap"
#include <QFile>
#include <QString>
#include "../include/shareddefs.h"

FileSaverServiceImpl::FileSaverServiceImpl()
{

}

FileSaverServiceImpl::FileSaverServiceImpl(const FileSaverServiceImpl &tmp) : FileSaverService(tmp)
{

}

FileSaverServiceImpl* FileSaverServiceImpl::copy()
{
    return new FileSaverServiceImpl( *this );
}

int FileSaverServiceImpl::saveFile(const std::wstring &file_name, const xsd__base64Binary &file_data, ns__ErrorCode *error_code)
{
    QFile out( QString::fromStdWString( file_name ) );
    if( !out.open( QIODevice::WriteOnly ) )
    {
        *error_code = ns__COULD_NOT_OPEN_FILE;
        return SOAP_OK;
    }

    QByteArray ba( reinterpret_cast< char* >( file_data.__ptr ), file_data.__size );
    if( !out.write( ba ) )
    {
        *error_code = ns__COULD_NOT_SAVE_FILE;
        return SOAP_OK;
    }

    *error_code = ns__NO_ERROR;
    return SOAP_OK;
}

int FileSaverServiceImpl::loadFile(const std::wstring &file_name, ns__loadFileResponse *response)
{
    QFile in( QString::fromStdWString( file_name ) );
    if( !in.open( QIODevice::ReadOnly ) )
    {
        response->errorCode = ns__COULD_NOT_OPEN_FILE;
        return SOAP_OK;
    }

    QByteArray ba = in.readAll();
    if( ba.isEmpty() )
    {
        response->errorCode = ns__COULD_NOT_LOAD_FILE;
        return SOAP_OK;
    }

    initBase64( ba, this, &response->fileData );

    response->errorCode = ns__NO_ERROR;
    return SOAP_OK;
}

