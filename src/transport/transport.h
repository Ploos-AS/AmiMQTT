#ifndef AMIMQTT_TRANSPORT_H
#define AMIMQTT_TRANSPORT_H

#include <stddef.h>
#include <stdint.h>

typedef struct AmiMQTTTransport {
    void *ctx;
    int (*connect)(void *ctx, const char *host, uint16_t port);
    int (*send)(void *ctx, const uint8_t *data, size_t len);
    int (*recv)(void *ctx, uint8_t *data, size_t cap, size_t *received);
    void (*close)(void *ctx);
} AmiMQTTTransport;

#endif
