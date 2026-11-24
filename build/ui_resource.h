#if defined _HONEYGUI_SIMULATOR_
extern unsigned char *resource_root;

#define   PROJECT_JSON                             (void *)(resource_root + 0x00000078)
#define   RECORDER_UIMAIN_XML                      (void *)(resource_root + 0x00000278)

#else
#define   PROJECT_JSON                             (void *)(0x704d1078)
#define   RECORDER_UIMAIN_XML                      (void *)(0x704d1278)

#endif
