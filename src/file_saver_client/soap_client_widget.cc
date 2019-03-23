#include "soap_client_widget.h"

#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

#include "FileSaver.nsmap"
#include "soapFileSaverProxy.h"
#include "../include/shareddefs.h"

const char* const kEndPoint = "127.0.0.1:8085";

SoapClientWidget::SoapClientWidget(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout* main_layout = new QVBoxLayout;
    view_ = new QLabel;
    view_->setAlignment(Qt::AlignCenter);
    main_layout->addWidget(view_);

    QLayout* panel_layout = new QHBoxLayout;
    main_layout->addLayout(panel_layout);

    edit_ = new QLineEdit;
    panel_layout->addWidget(edit_);

    status_ = new QLabel;
    panel_layout->addWidget(status_);

    QPushButton* btn_save = new QPushButton("SAVE");
    connect(btn_save, SIGNAL(clicked()), SLOT(Save()));
    panel_layout->addWidget(btn_save);

    QPushButton* btn_load = new QPushButton("LOAD");
    connect(btn_load, SIGNAL(clicked()), SLOT(Load()));
    panel_layout->addWidget(btn_load);

    setLayout(main_layout);

    resize(800,600);
}

SoapClientWidget::~SoapClientWidget()
{

}

void SoapClientWidget::Save()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Open Image",
                                                     ".", "Image Files (*.png *.jpg *.bmp)" );
       if( file_path.isEmpty() )
       {
           return;
       }

       QString file_name = QFileInfo( file_path ).fileName();
       QFile in( file_path );
       if( !in.open( QIODevice::ReadOnly ) )
       {
           return;
       }

       edit_->setText( file_name );

       FileSaverProxy proxy;
       proxy.soap_endpoint = kEndPoint;

       xsd__base64Binary file_data;
       initBase64( in.readAll(), &proxy, &file_data );
       ns__ErrorCode error_code;
       if( proxy.saveFile( file_name.toStdWString(), file_data, &error_code ) == SOAP_OK ) {
           ShowErrorCode( error_code );
       } else {
           status_->setText( "SOAP_ERROR" );
       }
}

void SoapClientWidget::Load()
{
    QString file_name = edit_->text();
        if( file_name.isEmpty() )
        {
            return;
        }

        FileSaverProxy proxy;
        proxy.soap_endpoint = kEndPoint;

        ns__loadFileResponse res;
        if( proxy.loadFile( file_name.toStdWString(), &res ) == SOAP_OK )
        {
            ShowErrorCode( res.errorCode );
            if( res.errorCode == ns__NO_ERROR )
            {
                QPixmap pix;
                if( pix.loadFromData( res.fileData.__ptr, res.fileData.__size ) )
                {
                    view_->setPixmap( pix );
                }
            }
        }
        else
        {
            status_->setText( "SOAP_ERROR" );
        }
}

void SoapClientWidget::ShowErrorCode(int error_code)
{
    status_->setText( "0x" + QString::number( error_code, 16 ) );
}
