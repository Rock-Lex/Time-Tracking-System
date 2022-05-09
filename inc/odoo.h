
// C Library

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// CURL
#include <curl/curl.h>

struct MemoryStruct 
{
  char *memory;
  size_t size;
};

char csrf[41];
char *CLIENT_CERT = "../cert.p12";

// ERP
char *ODOO_URL = "ERP_SYSTEM_URL";
char *HTTP_AUTH = "ERP_SYSTEM_AUTH";   
char *ODOO_LOGIN = "ERP_SYSTEM_LOGIN";
char *ODOO_PASSWORD = "ERP_SYSTEM_PASS";

