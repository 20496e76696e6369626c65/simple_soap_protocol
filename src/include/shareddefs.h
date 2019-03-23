#ifndef SHAREDDEFS_H_
#define SHAREDDEFS_H_

class QByteArray;
class soap;
class xsd__base64Binary;

void initBase64( const QByteArray& ba, soap* parent, xsd__base64Binary* base64 ) {
    base64->__ptr = static_cast< uchar* >( soap_malloc( parent, ba.size() ) );
    if( base64->__ptr )
    {
        std::copy( ba.begin(), ba.end(), base64->__ptr );
        base64->__size = ba.size();
    }
}

#endif // SHAREDDEFS_H_
