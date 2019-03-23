#include <QCoreApplication>
#include <QSharedPointer>

#include "SOAPServiceController.h"
#include "file_saver_server_impl.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc,argv);

    QSharedPointer< FileSaverServiceImpl > service( new FileSaverServiceImpl() );
#ifdef Q_OS_WIN32
    service->bind_flags = SO_REUSEADDR;
#elif Q_OS_LINUX
    service->bind_flags = SO_REUSEPORT;
#endif
    SOAP_SOCKET m = service->bind( "0.0.0.0", 8085, 100 );
    if( !soap_valid_socket( m ) ) {
        return 1;
    }

    SOAPServiceController::Controller< FileSaverServiceImpl > controller( service );
    if( !controller.start() ) {
        return 2;
    }


    return a.exec();
}
