#ifndef SOAPSERVICECONTROLLER_H_
#define SOAPSERVICECONTROLLER_H_

#include <QSharedPointer>
#include <QThreadPool>
#include <QDebug>

#include "soapStub.h"

namespace SOAPServiceController {

// ********************************************************************************
template< typename Service >
class ServeTask : public QRunnable {
public:
    ServeTask( QSharedPointer< Service > service );

    void run();

private:
    QSharedPointer< Service > service_;

};

template< typename Service >
ServeTask< Service >::ServeTask( QSharedPointer< Service > service ) : service_( service ) {
}

template< typename Service >
void ServeTask< Service >::run() {
    if( !service_ ) {
        return;
    }

    service_->serve();
}

// ********************************************************************************
template< typename Service >
class AcceptTask : public QRunnable {
public:
    AcceptTask( QSharedPointer< Service > service, QThreadPool* thread_pool );

    void run();

private:
    QSharedPointer< Service > service_;
    QThreadPool* thread_pool_;

};

template< typename Service >
AcceptTask< Service >::AcceptTask( QSharedPointer< Service > service, QThreadPool* thread_pool ) :
    service_( service ), thread_pool_( thread_pool ) {
}

template< typename Service >
void AcceptTask< Service >::run() {
    if( !service_ || !thread_pool_ ) {
        return;
    }

    forever {
        SOAP_SOCKET s = service_->accept();
        if( !soap_valid_socket( s ) ) {
            continue;
        }

        QString ip = QString( "%1.%2.%3.%4" ).
                arg( ( service_->ip >> 24 ) & 0xFF ).
                arg( ( service_->ip >> 16 ) & 0xFF ).
                arg( ( service_->ip >> 8  ) & 0xFF ).
                arg( ( service_->ip       ) & 0xFF );

        QSharedPointer< Service > service_copy( service_->copy() );
        thread_pool_->start( new ServeTask< Service >( service_copy ) );
    }
}

// ********************************************************************************
template< typename Service >
class Controller {
public:
    Controller( QSharedPointer< Service > service );
    ~Controller();

    bool start();

private:
    QSharedPointer< Service > service_;
    QThreadPool thread_pool_;

};

template< typename Service >
Controller< Service >::Controller( QSharedPointer< Service > service ) :
    service_( service ) {
}

template< typename Service >
Controller< Service >::~Controller() {
}

template< typename Service >
bool Controller< Service >::start() {
    if( !service_ ) {
        return false;
    }

    thread_pool_.start( new AcceptTask< Service >( service_, &thread_pool_ ) );
    return true;
}

}

#endif // SOAPSERVICECONTROLLER_H_
