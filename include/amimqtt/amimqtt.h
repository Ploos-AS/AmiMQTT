#ifndef AMIMQTT_AMIMQTT_H
#define AMIMQTT_AMIMQTT_H

#ifdef __cplusplus
extern "C" {
#endif

#define AMIMQTT_VERSION_MAJOR 0
#define AMIMQTT_VERSION_MINOR 0
#define AMIMQTT_VERSION_PATCH 0

typedef enum AmiMQTTResult {
    AMIMQTT_OK = 0,
    AMIMQTT_ERR_ARGUMENT = -1,
    AMIMQTT_ERR_STATE = -2,
    AMIMQTT_ERR_TRANSPORT = -3,
    AMIMQTT_ERR_PROTOCOL = -4,
    AMIMQTT_ERR_NOMEM = -5
} AmiMQTTResult;

typedef struct AmiMQTTClient AmiMQTTClient;

#ifdef __cplusplus
}
#endif

#endif
