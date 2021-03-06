/* soapAmazonS3SoapBindingService.cpp
   Generated by gSOAP 2.8.9 from AmazonS3.h

Copyright(C) 2000-2012, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#include "soapAmazonS3SoapBindingService.h"

AmazonS3SoapBindingService::AmazonS3SoapBindingService()
{	this->soap = soap_new();
	this->own = true;
	AmazonS3SoapBindingService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

AmazonS3SoapBindingService::AmazonS3SoapBindingService(struct soap *_soap)
{	this->soap = _soap;
	this->own = false;
	AmazonS3SoapBindingService_init(_soap->imode, _soap->omode);
}

AmazonS3SoapBindingService::AmazonS3SoapBindingService(soap_mode iomode)
{	this->soap = soap_new();
	this->own = true;
	AmazonS3SoapBindingService_init(iomode, iomode);
}

AmazonS3SoapBindingService::AmazonS3SoapBindingService(soap_mode imode, soap_mode omode)
{	this->soap = soap_new();
	this->own = true;
	AmazonS3SoapBindingService_init(imode, omode);
}

AmazonS3SoapBindingService::~AmazonS3SoapBindingService()
{	if (this->own)
		soap_free(this->soap);
}

void AmazonS3SoapBindingService::AmazonS3SoapBindingService_init(soap_mode imode, soap_mode omode)
{	soap_imode(this->soap, imode);
	soap_omode(this->soap, omode);
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns1", "http://s3.amazonaws.com/doc/2006-03-01/", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap_set_namespaces(this->soap, namespaces);
};

void AmazonS3SoapBindingService::destroy()
{	soap_destroy(this->soap);
	soap_end(this->soap);
}

void AmazonS3SoapBindingService::reset()
{	destroy();
	soap_done(this->soap);
	soap_init(this->soap);
	AmazonS3SoapBindingService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

#ifndef WITH_PURE_VIRTUAL
AmazonS3SoapBindingService *AmazonS3SoapBindingService::copy()
{	AmazonS3SoapBindingService *dup = SOAP_NEW_COPY(AmazonS3SoapBindingService);
	if (dup)
		soap_copy_context(dup->soap, this->soap);
	return dup;
}
#endif

int AmazonS3SoapBindingService::soap_close_socket()
{	return soap_closesock(this->soap);
}

int AmazonS3SoapBindingService::soap_force_close_socket()
{	return soap_force_closesock(this->soap);
}

int AmazonS3SoapBindingService::soap_senderfault(const char *string, const char *detailXML)
{	return ::soap_sender_fault(this->soap, string, detailXML);
}

int AmazonS3SoapBindingService::soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_sender_fault_subcode(this->soap, subcodeQName, string, detailXML);
}

int AmazonS3SoapBindingService::soap_receiverfault(const char *string, const char *detailXML)
{	return ::soap_receiver_fault(this->soap, string, detailXML);
}

int AmazonS3SoapBindingService::soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_receiver_fault_subcode(this->soap, subcodeQName, string, detailXML);
}

void AmazonS3SoapBindingService::soap_print_fault(FILE *fd)
{	::soap_print_fault(this->soap, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void AmazonS3SoapBindingService::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this->soap, os);
}
#endif

char *AmazonS3SoapBindingService::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this->soap, buf, len);
}
#endif

void AmazonS3SoapBindingService::soap_noheader()
{	this->soap->header = NULL;
}

const SOAP_ENV__Header *AmazonS3SoapBindingService::soap_header()
{	return this->soap->header;
}

int AmazonS3SoapBindingService::run(int port)
{	if (soap_valid_socket(this->soap->master) || soap_valid_socket(bind(NULL, port, 100)))
	{	for (;;)
		{	if (!soap_valid_socket(accept()) || serve())
				return this->soap->error;
			soap_destroy(this->soap);
			soap_end(this->soap);
		}
	}
	else
		return this->soap->error;
	return SOAP_OK;
}

SOAP_SOCKET AmazonS3SoapBindingService::bind(const char *host, int port, int backlog)
{	return soap_bind(this->soap, host, port, backlog);
}

SOAP_SOCKET AmazonS3SoapBindingService::accept()
{	return soap_accept(this->soap);
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int AmazonS3SoapBindingService::ssl_accept()
{	return soap_ssl_accept(this->soap);
}
#endif

int AmazonS3SoapBindingService::serve()
{
#ifndef WITH_FASTCGI
	unsigned int k = this->soap->max_keep_alive;
#endif
	do
	{

#ifndef WITH_FASTCGI
		if (this->soap->max_keep_alive > 0 && !--k)
			this->soap->keep_alive = 0;
#endif

		if (soap_begin_serve(this->soap))
		{	if (this->soap->error >= SOAP_STOP)
				continue;
			return this->soap->error;
		}
		if (dispatch() || (this->soap->fserveloop && this->soap->fserveloop(this->soap)))
		{
#ifdef WITH_FASTCGI
			soap_send_fault(this->soap);
#else
			return soap_send_fault(this->soap);
#endif
		}

#ifdef WITH_FASTCGI
		soap_destroy(this->soap);
		soap_end(this->soap);
	} while (1);
#else
	} while (this->soap->keep_alive);
#endif
	return SOAP_OK;
}

static int serve___ns1__CreateBucket(AmazonS3SoapBindingService*);
static int serve___ns1__DeleteBucket(AmazonS3SoapBindingService*);
static int serve___ns1__GetObjectAccessControlPolicy(AmazonS3SoapBindingService*);
static int serve___ns1__GetBucketAccessControlPolicy(AmazonS3SoapBindingService*);
static int serve___ns1__SetObjectAccessControlPolicy(AmazonS3SoapBindingService*);
static int serve___ns1__SetBucketAccessControlPolicy(AmazonS3SoapBindingService*);
static int serve___ns1__GetObject(AmazonS3SoapBindingService*);
static int serve___ns1__GetObjectExtended(AmazonS3SoapBindingService*);
static int serve___ns1__PutObject(AmazonS3SoapBindingService*);
static int serve___ns1__PutObjectInline(AmazonS3SoapBindingService*);
static int serve___ns1__DeleteObject(AmazonS3SoapBindingService*);
static int serve___ns1__ListBucket(AmazonS3SoapBindingService*);
static int serve___ns1__ListAllMyBuckets(AmazonS3SoapBindingService*);
static int serve___ns1__SetBucketLoggingStatus(AmazonS3SoapBindingService*);
static int serve___ns1__GetBucketLoggingStatus(AmazonS3SoapBindingService*);
static int serve___ns1__CopyObject(AmazonS3SoapBindingService*);

int AmazonS3SoapBindingService::dispatch()
{	AmazonS3SoapBindingService_init(this->soap->imode, this->soap->omode);
	soap_peek_element(this->soap);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:CreateBucket"))
		return serve___ns1__CreateBucket(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:DeleteBucket"))
		return serve___ns1__DeleteBucket(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:GetObjectAccessControlPolicy"))
		return serve___ns1__GetObjectAccessControlPolicy(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:GetBucketAccessControlPolicy"))
		return serve___ns1__GetBucketAccessControlPolicy(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:SetObjectAccessControlPolicy"))
		return serve___ns1__SetObjectAccessControlPolicy(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:SetBucketAccessControlPolicy"))
		return serve___ns1__SetBucketAccessControlPolicy(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:GetObject"))
		return serve___ns1__GetObject(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:GetObjectExtended"))
		return serve___ns1__GetObjectExtended(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:PutObject"))
		return serve___ns1__PutObject(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:PutObjectInline"))
		return serve___ns1__PutObjectInline(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:DeleteObject"))
		return serve___ns1__DeleteObject(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:ListBucket"))
		return serve___ns1__ListBucket(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:ListAllMyBuckets"))
		return serve___ns1__ListAllMyBuckets(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:SetBucketLoggingStatus"))
		return serve___ns1__SetBucketLoggingStatus(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:GetBucketLoggingStatus"))
		return serve___ns1__GetBucketLoggingStatus(this);
	if (!soap_match_tag(this->soap, this->soap->tag, "ns1:CopyObject"))
		return serve___ns1__CopyObject(this);
	return this->soap->error = SOAP_NO_METHOD;
}

static int serve___ns1__CreateBucket(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__CreateBucket soap_tmp___ns1__CreateBucket;
	_ns1__CreateBucketResponse ns1__CreateBucketResponse;
	ns1__CreateBucketResponse.soap_default(soap);
	soap_default___ns1__CreateBucket(soap, &soap_tmp___ns1__CreateBucket);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__CreateBucket(soap, &soap_tmp___ns1__CreateBucket, "-ns1:CreateBucket", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->CreateBucket(soap_tmp___ns1__CreateBucket.ns1__CreateBucket, &ns1__CreateBucketResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__CreateBucketResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__CreateBucketResponse.soap_put(soap, "ns1:CreateBucketResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__CreateBucketResponse.soap_put(soap, "ns1:CreateBucketResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__DeleteBucket(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__DeleteBucket soap_tmp___ns1__DeleteBucket;
	_ns1__DeleteBucketResponse ns1__DeleteBucketResponse;
	ns1__DeleteBucketResponse.soap_default(soap);
	soap_default___ns1__DeleteBucket(soap, &soap_tmp___ns1__DeleteBucket);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__DeleteBucket(soap, &soap_tmp___ns1__DeleteBucket, "-ns1:DeleteBucket", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->DeleteBucket(soap_tmp___ns1__DeleteBucket.ns1__DeleteBucket, &ns1__DeleteBucketResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__DeleteBucketResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__DeleteBucketResponse.soap_put(soap, "ns1:DeleteBucketResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__DeleteBucketResponse.soap_put(soap, "ns1:DeleteBucketResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__GetObjectAccessControlPolicy(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__GetObjectAccessControlPolicy soap_tmp___ns1__GetObjectAccessControlPolicy;
	_ns1__GetObjectAccessControlPolicyResponse ns1__GetObjectAccessControlPolicyResponse;
	ns1__GetObjectAccessControlPolicyResponse.soap_default(soap);
	soap_default___ns1__GetObjectAccessControlPolicy(soap, &soap_tmp___ns1__GetObjectAccessControlPolicy);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__GetObjectAccessControlPolicy(soap, &soap_tmp___ns1__GetObjectAccessControlPolicy, "-ns1:GetObjectAccessControlPolicy", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->GetObjectAccessControlPolicy(soap_tmp___ns1__GetObjectAccessControlPolicy.ns1__GetObjectAccessControlPolicy, &ns1__GetObjectAccessControlPolicyResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__GetObjectAccessControlPolicyResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__GetObjectAccessControlPolicyResponse.soap_put(soap, "ns1:GetObjectAccessControlPolicyResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__GetObjectAccessControlPolicyResponse.soap_put(soap, "ns1:GetObjectAccessControlPolicyResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__GetBucketAccessControlPolicy(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__GetBucketAccessControlPolicy soap_tmp___ns1__GetBucketAccessControlPolicy;
	_ns1__GetBucketAccessControlPolicyResponse ns1__GetBucketAccessControlPolicyResponse;
	ns1__GetBucketAccessControlPolicyResponse.soap_default(soap);
	soap_default___ns1__GetBucketAccessControlPolicy(soap, &soap_tmp___ns1__GetBucketAccessControlPolicy);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__GetBucketAccessControlPolicy(soap, &soap_tmp___ns1__GetBucketAccessControlPolicy, "-ns1:GetBucketAccessControlPolicy", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->GetBucketAccessControlPolicy(soap_tmp___ns1__GetBucketAccessControlPolicy.ns1__GetBucketAccessControlPolicy, &ns1__GetBucketAccessControlPolicyResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__GetBucketAccessControlPolicyResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__GetBucketAccessControlPolicyResponse.soap_put(soap, "ns1:GetBucketAccessControlPolicyResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__GetBucketAccessControlPolicyResponse.soap_put(soap, "ns1:GetBucketAccessControlPolicyResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__SetObjectAccessControlPolicy(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__SetObjectAccessControlPolicy soap_tmp___ns1__SetObjectAccessControlPolicy;
	_ns1__SetObjectAccessControlPolicyResponse ns1__SetObjectAccessControlPolicyResponse;
	ns1__SetObjectAccessControlPolicyResponse.soap_default(soap);
	soap_default___ns1__SetObjectAccessControlPolicy(soap, &soap_tmp___ns1__SetObjectAccessControlPolicy);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__SetObjectAccessControlPolicy(soap, &soap_tmp___ns1__SetObjectAccessControlPolicy, "-ns1:SetObjectAccessControlPolicy", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->SetObjectAccessControlPolicy(soap_tmp___ns1__SetObjectAccessControlPolicy.ns1__SetObjectAccessControlPolicy, &ns1__SetObjectAccessControlPolicyResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__SetObjectAccessControlPolicyResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__SetObjectAccessControlPolicyResponse.soap_put(soap, "ns1:SetObjectAccessControlPolicyResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__SetObjectAccessControlPolicyResponse.soap_put(soap, "ns1:SetObjectAccessControlPolicyResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__SetBucketAccessControlPolicy(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__SetBucketAccessControlPolicy soap_tmp___ns1__SetBucketAccessControlPolicy;
	_ns1__SetBucketAccessControlPolicyResponse ns1__SetBucketAccessControlPolicyResponse;
	ns1__SetBucketAccessControlPolicyResponse.soap_default(soap);
	soap_default___ns1__SetBucketAccessControlPolicy(soap, &soap_tmp___ns1__SetBucketAccessControlPolicy);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__SetBucketAccessControlPolicy(soap, &soap_tmp___ns1__SetBucketAccessControlPolicy, "-ns1:SetBucketAccessControlPolicy", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->SetBucketAccessControlPolicy(soap_tmp___ns1__SetBucketAccessControlPolicy.ns1__SetBucketAccessControlPolicy, &ns1__SetBucketAccessControlPolicyResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__SetBucketAccessControlPolicyResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__SetBucketAccessControlPolicyResponse.soap_put(soap, "ns1:SetBucketAccessControlPolicyResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__SetBucketAccessControlPolicyResponse.soap_put(soap, "ns1:SetBucketAccessControlPolicyResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__GetObject(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__GetObject soap_tmp___ns1__GetObject;
	_ns1__GetObjectResponse ns1__GetObjectResponse;
	ns1__GetObjectResponse.soap_default(soap);
	soap_default___ns1__GetObject(soap, &soap_tmp___ns1__GetObject);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__GetObject(soap, &soap_tmp___ns1__GetObject, "-ns1:GetObject", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->GetObject(soap_tmp___ns1__GetObject.ns1__GetObject, &ns1__GetObjectResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__GetObjectResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__GetObjectResponse.soap_put(soap, "ns1:GetObjectResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__GetObjectResponse.soap_put(soap, "ns1:GetObjectResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__GetObjectExtended(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__GetObjectExtended soap_tmp___ns1__GetObjectExtended;
	_ns1__GetObjectExtendedResponse ns1__GetObjectExtendedResponse;
	ns1__GetObjectExtendedResponse.soap_default(soap);
	soap_default___ns1__GetObjectExtended(soap, &soap_tmp___ns1__GetObjectExtended);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__GetObjectExtended(soap, &soap_tmp___ns1__GetObjectExtended, "-ns1:GetObjectExtended", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->GetObjectExtended(soap_tmp___ns1__GetObjectExtended.ns1__GetObjectExtended, &ns1__GetObjectExtendedResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__GetObjectExtendedResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__GetObjectExtendedResponse.soap_put(soap, "ns1:GetObjectExtendedResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__GetObjectExtendedResponse.soap_put(soap, "ns1:GetObjectExtendedResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__PutObject(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__PutObject soap_tmp___ns1__PutObject;
	_ns1__PutObjectResponse ns1__PutObjectResponse;
	ns1__PutObjectResponse.soap_default(soap);
	soap_default___ns1__PutObject(soap, &soap_tmp___ns1__PutObject);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__PutObject(soap, &soap_tmp___ns1__PutObject, "-ns1:PutObject", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->PutObject(soap_tmp___ns1__PutObject.ns1__PutObject, &ns1__PutObjectResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__PutObjectResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__PutObjectResponse.soap_put(soap, "ns1:PutObjectResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__PutObjectResponse.soap_put(soap, "ns1:PutObjectResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__PutObjectInline(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__PutObjectInline soap_tmp___ns1__PutObjectInline;
	_ns1__PutObjectInlineResponse ns1__PutObjectInlineResponse;
	ns1__PutObjectInlineResponse.soap_default(soap);
	soap_default___ns1__PutObjectInline(soap, &soap_tmp___ns1__PutObjectInline);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__PutObjectInline(soap, &soap_tmp___ns1__PutObjectInline, "-ns1:PutObjectInline", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->PutObjectInline(soap_tmp___ns1__PutObjectInline.ns1__PutObjectInline, &ns1__PutObjectInlineResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__PutObjectInlineResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__PutObjectInlineResponse.soap_put(soap, "ns1:PutObjectInlineResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__PutObjectInlineResponse.soap_put(soap, "ns1:PutObjectInlineResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__DeleteObject(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__DeleteObject soap_tmp___ns1__DeleteObject;
	_ns1__DeleteObjectResponse ns1__DeleteObjectResponse;
	ns1__DeleteObjectResponse.soap_default(soap);
	soap_default___ns1__DeleteObject(soap, &soap_tmp___ns1__DeleteObject);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__DeleteObject(soap, &soap_tmp___ns1__DeleteObject, "-ns1:DeleteObject", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->DeleteObject(soap_tmp___ns1__DeleteObject.ns1__DeleteObject, &ns1__DeleteObjectResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__DeleteObjectResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__DeleteObjectResponse.soap_put(soap, "ns1:DeleteObjectResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__DeleteObjectResponse.soap_put(soap, "ns1:DeleteObjectResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__ListBucket(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__ListBucket soap_tmp___ns1__ListBucket;
	_ns1__ListBucketResponse ns1__ListBucketResponse;
	ns1__ListBucketResponse.soap_default(soap);
	soap_default___ns1__ListBucket(soap, &soap_tmp___ns1__ListBucket);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__ListBucket(soap, &soap_tmp___ns1__ListBucket, "-ns1:ListBucket", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->ListBucket(soap_tmp___ns1__ListBucket.ns1__ListBucket, &ns1__ListBucketResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__ListBucketResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__ListBucketResponse.soap_put(soap, "ns1:ListBucketResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__ListBucketResponse.soap_put(soap, "ns1:ListBucketResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__ListAllMyBuckets(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__ListAllMyBuckets soap_tmp___ns1__ListAllMyBuckets;
	_ns1__ListAllMyBucketsResponse ns1__ListAllMyBucketsResponse;
	ns1__ListAllMyBucketsResponse.soap_default(soap);
	soap_default___ns1__ListAllMyBuckets(soap, &soap_tmp___ns1__ListAllMyBuckets);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__ListAllMyBuckets(soap, &soap_tmp___ns1__ListAllMyBuckets, "-ns1:ListAllMyBuckets", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->ListAllMyBuckets(soap_tmp___ns1__ListAllMyBuckets.ns1__ListAllMyBuckets, &ns1__ListAllMyBucketsResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__ListAllMyBucketsResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__ListAllMyBucketsResponse.soap_put(soap, "ns1:ListAllMyBucketsResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__ListAllMyBucketsResponse.soap_put(soap, "ns1:ListAllMyBucketsResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__SetBucketLoggingStatus(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__SetBucketLoggingStatus soap_tmp___ns1__SetBucketLoggingStatus;
	_ns1__SetBucketLoggingStatusResponse ns1__SetBucketLoggingStatusResponse;
	ns1__SetBucketLoggingStatusResponse.soap_default(soap);
	soap_default___ns1__SetBucketLoggingStatus(soap, &soap_tmp___ns1__SetBucketLoggingStatus);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__SetBucketLoggingStatus(soap, &soap_tmp___ns1__SetBucketLoggingStatus, "-ns1:SetBucketLoggingStatus", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->SetBucketLoggingStatus(soap_tmp___ns1__SetBucketLoggingStatus.ns1__SetBucketLoggingStatus, &ns1__SetBucketLoggingStatusResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__SetBucketLoggingStatusResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__SetBucketLoggingStatusResponse.soap_put(soap, "ns1:SetBucketLoggingStatusResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__SetBucketLoggingStatusResponse.soap_put(soap, "ns1:SetBucketLoggingStatusResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__GetBucketLoggingStatus(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__GetBucketLoggingStatus soap_tmp___ns1__GetBucketLoggingStatus;
	_ns1__GetBucketLoggingStatusResponse ns1__GetBucketLoggingStatusResponse;
	ns1__GetBucketLoggingStatusResponse.soap_default(soap);
	soap_default___ns1__GetBucketLoggingStatus(soap, &soap_tmp___ns1__GetBucketLoggingStatus);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__GetBucketLoggingStatus(soap, &soap_tmp___ns1__GetBucketLoggingStatus, "-ns1:GetBucketLoggingStatus", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->GetBucketLoggingStatus(soap_tmp___ns1__GetBucketLoggingStatus.ns1__GetBucketLoggingStatus, &ns1__GetBucketLoggingStatusResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__GetBucketLoggingStatusResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__GetBucketLoggingStatusResponse.soap_put(soap, "ns1:GetBucketLoggingStatusResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__GetBucketLoggingStatusResponse.soap_put(soap, "ns1:GetBucketLoggingStatusResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__CopyObject(AmazonS3SoapBindingService *service)
{	struct soap *soap = service->soap;
	struct __ns1__CopyObject soap_tmp___ns1__CopyObject;
	_ns1__CopyObjectResponse ns1__CopyObjectResponse;
	ns1__CopyObjectResponse.soap_default(soap);
	soap_default___ns1__CopyObject(soap, &soap_tmp___ns1__CopyObject);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__CopyObject(soap, &soap_tmp___ns1__CopyObject, "-ns1:CopyObject", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->CopyObject(soap_tmp___ns1__CopyObject.ns1__CopyObject, &ns1__CopyObjectResponse);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__CopyObjectResponse.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__CopyObjectResponse.soap_put(soap, "ns1:CopyObjectResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__CopyObjectResponse.soap_put(soap, "ns1:CopyObjectResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
/* End of server object code */
