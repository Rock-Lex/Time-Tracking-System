#include <stdio.h>
#include <json-c/json.h>

struct result 
{
    char *display;
    double worked_hours;
};

struct result jsonParse()
{
	FILE *fp;
	char buffer[2056];
	struct json_object *parsed_json;
	struct json_object *display_name;
	struct json_object *worked_hours;

    struct result res;

	fp = fopen("../build/get3.json","r");
	fread(buffer, 2056, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "result", &parsed_json);
    json_object_object_get_ex(parsed_json, "action", &parsed_json);
    json_object_object_get_ex(parsed_json, "attendance", &parsed_json);
    json_object_object_get_ex(parsed_json, "display_name", &display_name);
    json_object_object_get_ex(parsed_json, "worked_hours", &worked_hours);


	printf("Display name: %s\n", json_object_get_string(display_name));
	printf("Worked hours: %f\n", json_object_get_double(worked_hours));

    res.display = json_object_get_string(display_name);
    res.worked_hours = json_object_get_double(worked_hours);

	fp = fopen("../build/get3.json","w");
	fclose(fp);

    return res;
}	