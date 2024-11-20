#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"
#include "shared.h"

int main(void)
{
    const char *key   = "FOO";
    const char *value = "BAR";

    String_Builder content = {0};

    sb_append_cstr(&content, "# this is a comment\n");
    sb_append_cstr(&content, "\n");
    sb_append_cstr(&content, temp_sprintf("%s=%s\n", key, value));

    const char *dotenv_file_path = BUILD_FOLDER"nob_dotenv_env";

    if (!write_entire_file(dotenv_file_path, content.items, content.count)) return 1;
    if (!dotenv(dotenv_file_path, 1)) return 1;

    char *result = getenv(key);
    if (result == NULL) {
        nob_log(ERROR, "Could not set environment variable");
        return 1;
    }

    if (strcmp(result, value) != 0) {
        nob_log(ERROR, "Unexpected environment variable value: %s", result);
        return 1;
    }

    nob_log(INFO, "OK");
    return 0;
}
