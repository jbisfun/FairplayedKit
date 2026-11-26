#pragma once
#include <stddef.h>
#include <string.h>

// Length of the top-level extension bundle path, or zero for any other path.
static inline size_t fp_extension_path_length(const char *path) {
    const char prefix[] = "PlugIns/";
    const char suffix[] = ".appex";
    if (strncmp(path, prefix, sizeof(prefix) - 1) != 0) return 0;
    const char *name = path + sizeof(prefix) - 1;
    const char *end = strchr(name, '/');
    if (!end || end - name <= (ptrdiff_t)(sizeof(suffix) - 1) ||
        memcmp(end - (sizeof(suffix) - 1), suffix, sizeof(suffix) - 1) != 0) return 0;
    for (const char *part = end + 1; ; ) {
        size_t len = strcspn(part, "/");
        if (!len || (len == 1 && part[0] == '.') ||
            (len == 2 && part[0] == '.' && part[1] == '.')) return 0;
        if (!part[len]) break;
        part += len + 1;
    }
    return (size_t)(end - path);
}
