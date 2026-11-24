#if defined _HONEYGUI_SIMULATOR_
extern unsigned char *resource_root;

#define   PROJECT_JSON                             (void *)(resource_root + 0x00000078)
#define   RECORDER2_BIN                            (void *)(resource_root + 0x00000238)
#define   SWITCH2_BIN                              (void *)(resource_root + 0x000159f8)
#define   RECORDER_UIMAIN_XML                      (void *)(resource_root + 0x0002eb78)

#else
#define   PROJECT_JSON                             (void *)(0x704d1078)
#define   RECORDER2_BIN                            (void *)(0x704d1238)
#define   SWITCH2_BIN                              (void *)(0x704e69f8)
#define   RECORDER_UIMAIN_XML                      (void *)(0x704ffb78)

#endif
