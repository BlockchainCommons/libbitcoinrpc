/*
The MIT License (MIT)
Copyright (c) 2016 Marek Miller

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef BITCOINRPC_H_51fe7847_aafe_4e78_9823_eff094a30775
#define BITCOINRPC_H_51fe7847_aafe_4e78_9823_eff094a30775

#include <stdlib.h>
#include <jansson.h>


/* Name and version */
#define BITCOINRPC_LIBNAME "bitcoinrpc"
#define BITCOINRPC_VERSION "0.0.0"

/* Defalut parameters of a RPC client */
#define BITCOINRPC_USER_DEFAULT ""
#define BITCOINRPC_PASS_DEFAULT ""
#define BITCOINRPC_ADDR_DEFAULT "127.0.0.1"
#define BITCOINRPC_PORT_DEFAULT 8332

/*
Maximal length of a string that holds a client's parameter
(user name, password or address), including the terminating '\0' character.
*/
#define BITCOINRPC_PARAM_MAXLEN 257

/*
Maximal length of the server url:
"http://%s:%d" = 2*BITCOINRPC_PARAM_MAXLEN + 15
*/
#define BITCOINRPC_URL_MAXLEN 529

/* Maximal length of an error message */
#define BITCOINRPC_ERRMSG_MAXLEN 1000

/* Error codes */
typedef enum {

  BITCOINRPCE_OK,                   /* Success */
  BITCOINRPCE_CHECK,                /* see: bitcoinrpc_resp_check() */
  BITCOINRPCE_ERR,                  /* unspecific error */
  BITCOINRPCE_ALLOC,                /* cannot allocate more memory */
  BITCOINRPCE_BUG,                  /* a bug in the library (please report) */
  BITCOINRPCE_CON,                  /* connection error */
  BITCOINRPCE_CURLE,                /* libcurl returned some error */
  BITCOINRPCE_JSON,                 /* error parsing json data */
  BITCOINRPCE_PARAM                 /* wrong parameter, e.g. NULL */

} BITCOINRPCEcode;


/* RPC methods */
typedef enum {

/* Control RPC */
  BITCOINRPC_METHOD_GETINFO,            /* deprecated */
  BITCOINRPC_METHOD_HELP,
  BITCOINRPC_METHOD_STOP,

  BITCOINRPC_METHOD_GETNETWORKINFO,
  BITCOINRPC_METHOD_GETWALLETINFO,
  BITCOINRPC_METHOD_SETTXFEE

} BITCOINRPC_METHOD;

/* ---------------- bitcoinrpc_err --------------------- */
struct bitcoinrpc_err
{
  BITCOINRPCEcode code;
  char msg[BITCOINRPC_ERRMSG_MAXLEN];
};

typedef
  struct bitcoinrpc_err
bitcoinrpc_err_t;


/* --------------- bitcoinrpc_global ------------------- */
/*
The global initialisation function.
Please call this function from your main thread before any other call.
*/
BITCOINRPCEcode
bitcoinrpc_global_init (void);

/*
The global cleanup function.
Please call this function at the end of your program to collect library's
internal garbage.
*/
BITCOINRPCEcode
bitcoinrpc_global_cleanup (void);

/*
Set a memory allocating function for the library routines.
(the default is just standard malloc() ).
*/
BITCOINRPCEcode
bitcoinrpc_global_set_allocfunc ( void * (* const f) (size_t size) );

/*
Set a memory freeing function for the library routines.
(the default is just standard free() ).
*/
BITCOINRPCEcode
bitcoinrpc_global_set_freefunc ( void (* const f) (void *ptr) );


/* -------------bitcoinrpc_cl --------------------- */
struct bitcoinrpc_cl;

typedef
  struct bitcoinrpc_cl
bitcoinrpc_cl_t;

/*
Initialise a new RPC client with default values: BITCOINRPC_*_DEFAULT.
Return NULL in case of error.
*/
bitcoinrpc_cl_t*
bitcoinrpc_cl_init (void);


/*
Initialise and set some parameters (may not be NULL; in that case the
function returns NULL as well). The parameter values are copied,
so the original pointers are no longer needed. At most
BITCOINRPC_PARAM_MAXLEN chars are copied to store a parameter.
*/
bitcoinrpc_cl_t*
bitcoinrpc_cl_init_params ( const char* user, const char* pass,
                            const char* addr, const unsigned int port );


/* Free the handle. */
BITCOINRPCEcode
bitcoinrpc_cl_free (bitcoinrpc_cl_t *cl);

/*
Copy value to buf. The buffer is assumed to contain at least
BITCOINRPC_PARAM_MAXLEN chars. At most BITCOINRPC_PARAM_MAXLEN chars are copied.
*/
BITCOINRPCEcode
bitcoinrpc_cl_get_user (bitcoinrpc_cl_t *cl, char *buf);

BITCOINRPCEcode
bitcoinrpc_cl_get_pass (bitcoinrpc_cl_t *cl, char *buf);

/*
Copy value to buf. The buffer is assumed to contain at least
BITCOINRPC_URL_MAXLEN chars. At most BITCOINRPC_URL_MAXLEN chars are copied.
*/
BITCOINRPCEcode
bitcoinrpc_cl_get_url (bitcoinrpc_cl_t *cl, char *buf);

/* ------------- bitcoinrpc_method --------------------- */
struct bitcoinrpc_method;

typedef
  struct bitcoinrpc_method
bitcoinrpc_method_t;

/* Initialise a new method without params */
bitcoinrpc_method_t *
bitcoinrpc_method_init (const BITCOINRPC_METHOD m);


/*
The argument json_t params to functions below is always copied
to library internals and the original pointer is no longer needed
after the function returns.  It is the obligation of the user to free
the original pointer by decreasing its reference count (see jansson
library documentation).
*/

/*
Initialise a new method with json_t array as params.
If params == NULL, this is the same as bitcoinrpc_method_init.
 */
bitcoinrpc_method_t *
bitcoinrpc_method_init_params (const BITCOINRPC_METHOD m,
                               json_t * const params);

/* Destroy the method */
BITCOINRPCEcode
bitcoinrpc_method_free (bitcoinrpc_method_t *method);

/* Set a new json object as method parameters */
BITCOINRPCEcode
bitcoinrpc_method_set_params (bitcoinrpc_method_t *method, json_t *params);

/* Get a deepcopy of the method's parameters and store it in params */
BITCOINRPCEcode
bitcoinrpc_method_get_params (bitcoinrpc_method_t *method, json_t **params);


/* ------------- bitcoinrpc_resp --------------------- */
struct bitcoinrpc_resp;

typedef
  struct bitcoinrpc_resp
bitcoinrpc_resp_t;

bitcoinrpc_resp_t *
bitcoinrpc_resp_init (void);

BITCOINRPCEcode
bitcoinrpc_resp_free (bitcoinrpc_resp_t *resp);

/*
Get a deepcopy of the json object representing the response
from the server or NULL in case of error.
*/
json_t *
bitcoinrpc_resp_get (bitcoinrpc_resp_t *resp);

/*
Check if the resp comes as a result of calling method.
Returns BITCOINRPCE_CHECK, if not. This check is already performed by
bitcoinrpc_call()
*/
BITCOINRPCEcode
bitcoinrpc_resp_check (bitcoinrpc_resp_t *resp, bitcoinrpc_method_t *method);


/* ------------- bitcoinrpc_call --------------------- */

/*
Call the server with method. Save response in resp.
If e == NULL, it is ignored.
*/

BITCOINRPCEcode
bitcoinrpc_call (bitcoinrpc_cl_t * cl, bitcoinrpc_method_t * method,
                 bitcoinrpc_resp_t *resp, bitcoinrpc_err_t *e);



#endif  /* BITCOINRPC_H_51fe7847_aafe_4e78_9823_eff094a30775 */
