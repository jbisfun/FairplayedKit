#include <assert.h>
#include <string.h>
#include "extension_path.h"

int main(void) {
    const char *root = "PlugIns/Widget.appex";
    assert(fp_extension_path_length("PlugIns/Widget.appex/Widget") == strlen(root));
    assert(fp_extension_path_length("PlugIns/Widget.appex/Frameworks/lib.dylib") == strlen(root));
    assert(fp_extension_path_length("App") == 0);
    assert(fp_extension_path_length("Frameworks/Library.framework/Library") == 0);
    assert(fp_extension_path_length("PlugIns/.appex/X") == 0);
    assert(fp_extension_path_length("PlugIns/Widget.appex") == 0);
    assert(fp_extension_path_length("PlugIns/Widget.appex/../App") == 0);
    assert(fp_extension_path_length("PlugIns/Widget.appex/Frameworks/../../App") == 0);
    assert(fp_extension_path_length("PlugIns/Widget.appex2/Widget") == 0);
}
