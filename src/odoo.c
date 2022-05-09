#include "../inc/odoo.h"

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);

    if(!ptr) 
    {
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

int writeInfoToFile(char *info, char* path)
{
   FILE *fptr;
   fptr = fopen(path,"wb");

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   fprintf(fptr,"%s", info);
   fclose(fptr);

   return 0;
}

int interractWithUser(char * employeeIDscan)
{   
    printf("%s\n", "Successful scan attempt");
    printf("Employee ID is: %s\n", employeeIDscan);

    CURL* curl;
    CURLcode response;

    struct curl_slist *headers = NULL;
    struct MemoryStruct chunk;
    struct MemoryStruct chunk2;
    struct MemoryStruct chunk3;

    char post[194] = "csrf_token=";

    // 1. Request
    chunk.memory = malloc(1);  
    chunk.size = 0;    
    // 2. Request
    chunk2.memory = malloc(1); 
    chunk2.size = 0; 
    // 3. Request
    chunk3.memory = malloc(1); 
    chunk3.size = 0; 

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl)
    {   
        //////////////////////////////////////////////
        // 1. Request Settings
        //////////////////////////////////////////////
        curl_easy_setopt(curl, CURLOPT_URL, ODOO_URL);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);        // Debug
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);  


        curl_easy_setopt(curl, CURLOPT_SSLCERT, CLIENT_CERT);
        curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "P12");
        curl_easy_setopt(curl, CURLOPT_SSLKEYPASSWD, "");
        curl_easy_setopt(curl, CURLOPT_KEYPASSWD, "");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSLCERTPASSWD, "");


        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, HTTP_AUTH);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        /////////////////////////////////////////////
        
        response = curl_easy_perform(curl);                       // 1. Request

        if (response != CURLE_OK)
        {
            fprintf(stderr, "CURL: %s\n", curl_easy_strerror(response));
        }
        else
        {
            char *csrf_token = "";
            printf("CURL: We got %d bytes \n", (int)chunk.size);
            csrf_token = strstr(chunk.memory, "csrf_token");

            if (!csrf_token)
            {
                printf("CURL: CSRF token is not found \n");
                writeInfoToFile(chunk.memory, "../build/get1.txt");
            }
            else
            {
                printf("CURL: Found csrf_token at index %d\n", (csrf_token - chunk.memory));
                strncpy(csrf, &chunk.memory[csrf_token - chunk.memory + 13], 41);
                csrf[41] = '\0';
                printf("CURL: csrf_token: %s\n", csrf);

                strncat(post, csrf, 41);
                strcat(post, "&login=");
                strcat(post, ODOO_LOGIN);
                strcat(post, "&password=");
                strcat(post, ODOO_PASSWORD);
                strcat(post, "&redirect=ERP_ATTEMP_SCAN_LINK");
                strcat(post, "&{\"jsonrpc\":\"2.0\",\"method\":\"call\",\"params\":{\"model\":\"hr.employee\",\"method\":\"attendance_scan\",\"args\":[\"XXXXXXXXXXXX\"],\"kwargs\":{}},\"id\":XXXXXXXXXX}");

                writeInfoToFile(chunk.memory, "../build/get1.txt");

                printf("CURL: 1. Postdata:  %s\n", post);

                if (response != CURLE_OK)
                {
                    fprintf(stderr, "CURL: %s\n", curl_easy_strerror(response));
                    writeInfoToFile(curl_easy_strerror(response), "../build/fehler.txt");
                }
                else
                {
                    //////////////////////////////////////////////
                    // 2. Request Settings
                    //////////////////////////////////////////////
                    curl_easy_setopt(curl, CURLOPT_URL, "ERP/LOGIN_LINK");
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk2);
                    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);                          // Debug        
                    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);  // ??

                    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
                    curl_easy_setopt(curl, CURLOPT_USERPWD, HTTP_AUTH);
                    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
                    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");
                    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
                    curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1L);
                    curl_easy_setopt(curl, CURLOPT_REFERER, ODOO_URL);
                    curl_easy_setopt(curl, CURLOPT_POST, 1L);
                    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);
                    /////////////////////////////////////////////

                    response = curl_easy_perform(curl);                 // 2. Request

                    if(response != CURLE_OK)
                    {
                        fprintf(stderr, "CURL error while 2.Request: %s\n", curl_easy_strerror(response));
                        writeInfoToFile(curl_easy_strerror(response), "../build/fehler.txt");
                    }
                    else
                    {
                        writeInfoToFile(chunk2.memory, "../build/get2.txt");

                        char post2[194] = "{\"jsonrpc\":\"2.0\",\"method\":\"call\",\"params\":{\"args\":[\""; 
                        printf("%s\n", post2);
                        strncat(post, employeeIDscan, 14);
                        strcat(post, "\"],\"model\":\"hr.employee\",\"method\":\"attendance_scan\",\"kwargs\":{}},\"id\":XXXXXXXXX}");

                        printf("CURL: %s\n", post2);
                        
                        //////////////////////////////////////////////
                        // 3. Request Settings
                        //////////////////////////////////////////////
                        curl_slist_append(headers, "Content-Type: application/json");
                        headers = curl_slist_append(headers, "Content-Type: application/json");

                        curl_easy_setopt(curl, CURLOPT_URL, "ERP/SCAN_ATTEMPT_LINK");
                        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
                        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");   
                        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);                          //Debug
                        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk3);
                        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post2);
                        /////////////////////////////////////////////

                        response = curl_easy_perform(curl);                     // 3. Request

                        if (response != CURLE_OK)
                        {
                            fprintf(stderr, "CURL error while 3.Request: %s\n", curl_easy_strerror(response));
                            writeInfoToFile(curl_easy_strerror(response), "../build/fehler.txt");
                        }
                        else
                        {
                            writeInfoToFile(chunk3.memory, "../build/get3.json");
                        }
                    }
                }
            }
        }
    }
    else
    {
        printf("CURL: %s\n", "Error while CURL init");
    }

    curl_global_cleanup();
    curl_easy_cleanup(curl);

    return 0;
}