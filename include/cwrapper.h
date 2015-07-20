#ifndef __CWRAPPER_H__
#define __CWRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct Core Core;

Core* NewCore(void);

void Core_Init(Core *c, const char *shaderPath, const char *imagePath);

void Core_Run(Core *c);

void DeleteCore(Core *c);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif  // __CWRAPPER_H__
