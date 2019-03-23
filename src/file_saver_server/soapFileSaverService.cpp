/* soapFileSaverService.cpp
   Generated by gSOAP 2.8.82 for file_saver_service.h

gSOAP XML Web services tools
Copyright (C) 2000-2018, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapFileSaverService.h"

FileSaverService::FileSaverService() : soap(SOAP_IO_DEFAULT)
{	FileSaverService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

FileSaverService::FileSaverService(const FileSaverService& rhs)
{	soap_copy_context(this, &rhs);
}

FileSaverService::FileSaverService(const struct soap &_soap) : soap(_soap)
{ }

FileSaverService::FileSaverService(soap_mode iomode) : soap(iomode)
{	FileSaverService_init(iomode, iomode);
}

FileSaverService::FileSaverService(soap_mode imode, soap_mode omode) : soap(imode, omode)
{	FileSaverService_init(imode, omode);
}

FileSaverService::~FileSaverService()
{
	this->destroy();
}

void FileSaverService::FileSaverService_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	static const struct Namespace namespaces[] = {
        { "SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL },
        { "SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL },
        { "xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL },
        { "xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL },
        { "ns", "urn:FileSaver", NULL, NULL },
        { NULL, NULL, NULL, NULL}
    };
	soap_set_namespaces(this, namespaces);
}

void FileSaverService::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void FileSaverService::reset()
{	this->destroy();
	soap_done(this);
	soap_initialize(this);
	FileSaverService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

#ifndef WITH_PURE_VIRTUAL
FileSaverService *FileSaverService::copy()
{	FileSaverService *dup = SOAP_NEW_UNMANAGED(FileSaverService(*(struct soap*)this));
	return dup;
}
#endif

FileSaverService& FileSaverService::operator=(const FileSaverService& rhs)
{	soap_done(this);
	soap_copy_context(this, &rhs);
	return *this;
}

int FileSaverService::soap_close_socket()
{	return soap_closesock(this);
}

int FileSaverService::soap_force_close_socket()
{	return soap_force_closesock(this);
}

int FileSaverService::soap_senderfault(const char *string, const char *detailXML)
{	return ::soap_sender_fault(this, string, detailXML);
}

int FileSaverService::soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_sender_fault_subcode(this, subcodeQName, string, detailXML);
}

int FileSaverService::soap_receiverfault(const char *string, const char *detailXML)
{	return ::soap_receiver_fault(this, string, detailXML);
}

int FileSaverService::soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_receiver_fault_subcode(this, subcodeQName, string, detailXML);
}

void FileSaverService::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void FileSaverService::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *FileSaverService::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

void FileSaverService::soap_noheader()
{	this->header = NULL;
}

::SOAP_ENV__Header *FileSaverService::soap_header()
{	return this->header;
}

#ifndef WITH_NOIO
int FileSaverService::run(int port, int backlog)
{	if (!soap_valid_socket(this->master) && !soap_valid_socket(this->bind(NULL, port, backlog)))
		return this->error;
	for (;;)
	{	if (!soap_valid_socket(this->accept()))
		{	if (this->errnum == 0) // timeout?
				this->error = SOAP_OK;
			break;
		}
		if (this->serve())
			break;
		this->destroy();
	}
	return this->error;
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int FileSaverService::ssl_run(int port, int backlog)
{	if (!soap_valid_socket(this->master) && !soap_valid_socket(this->bind(NULL, port, backlog)))
		return this->error;
	for (;;)
	{	if (!soap_valid_socket(this->accept()))
		{	if (this->errnum == 0) // timeout?
				this->error = SOAP_OK;
			break;
		}
		if (this->ssl_accept() || this->serve())
			break;
		this->destroy();
	}
	return this->error;
}
#endif

SOAP_SOCKET FileSaverService::bind(const char *host, int port, int backlog)
{	return soap_bind(this, host, port, backlog);
}

SOAP_SOCKET FileSaverService::accept()
{	return soap_accept(this);
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int FileSaverService::ssl_accept()
{	return soap_ssl_accept(this);
}
#endif
#endif

int FileSaverService::serve()
{
#ifndef WITH_FASTCGI
	this->keep_alive = this->max_keep_alive + 1;
#endif
	do
	{
#ifndef WITH_FASTCGI
		if (this->keep_alive > 0 && this->max_keep_alive > 0)
			this->keep_alive--;
#endif
		if (soap_begin_serve(this))
		{	if (this->error >= SOAP_STOP)
				continue;
			return this->error;
		}
		if ((dispatch() || (this->fserveloop && this->fserveloop(this))) && this->error && this->error < SOAP_STOP)
		{
#ifdef WITH_FASTCGI
			soap_send_fault(this);
#else
			return soap_send_fault(this);
#endif
		}
#ifdef WITH_FASTCGI
		soap_destroy(this);
		soap_end(this);
	} while (1);
#else
	} while (this->keep_alive);
#endif
	return SOAP_OK;
}

static int serve_ns__saveFile(FileSaverService*);
static int serve_ns__loadFile(FileSaverService*);

int FileSaverService::dispatch()
{
	soap_peek_element(this);
	if (!soap_match_tag(this, this->tag, "ns:saveFile"))
		return serve_ns__saveFile(this);
	if (!soap_match_tag(this, this->tag, "ns:loadFile"))
		return serve_ns__loadFile(this);
	return this->error = SOAP_NO_METHOD;
}

static int serve_ns__saveFile(FileSaverService *soap)
{	struct ns__saveFile soap_tmp_ns__saveFile;
	struct ns__saveFileResponse soap_tmp_ns__saveFileResponse;
	enum ns__ErrorCode soap_tmp_ns__ErrorCode;
	soap_default_ns__saveFileResponse(soap, &soap_tmp_ns__saveFileResponse);
	soap_default_ns__ErrorCode(soap, &soap_tmp_ns__ErrorCode);
	soap_tmp_ns__saveFileResponse.errorCode = &soap_tmp_ns__ErrorCode;
	soap_default_ns__saveFile(soap, &soap_tmp_ns__saveFile);
	if (!soap_get_ns__saveFile(soap, &soap_tmp_ns__saveFile, "ns:saveFile", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->saveFile(soap_tmp_ns__saveFile.fileName, soap_tmp_ns__saveFile.fileData, soap_tmp_ns__saveFileResponse.errorCode);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = ""; /* use SOAP encoding style */
	soap_serializeheader(soap);
	soap_serialize_ns__saveFileResponse(soap, &soap_tmp_ns__saveFileResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__saveFileResponse(soap, &soap_tmp_ns__saveFileResponse, "ns:saveFileResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__saveFileResponse(soap, &soap_tmp_ns__saveFileResponse, "ns:saveFileResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns__loadFile(FileSaverService *soap)
{	struct ns__loadFile soap_tmp_ns__loadFile;
	ns__loadFileResponse response;
	response.soap_default(soap);
	soap_default_ns__loadFile(soap, &soap_tmp_ns__loadFile);
	if (!soap_get_ns__loadFile(soap, &soap_tmp_ns__loadFile, "ns:loadFile", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->loadFile(soap_tmp_ns__loadFile.fileName, &response);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = ""; /* use SOAP encoding style */
	soap_serializeheader(soap);
	response.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || response.soap_put(soap, "ns:loadFileResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || response.soap_put(soap, "ns:loadFileResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
/* End of server object code */