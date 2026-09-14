#ifndef AMIMQTT_PROTOCOL_H
#define AMIMQTT_PROTOCOL_H

#include <stddef.h>
#include <stdint.h>

int amimqtt_encode_connect(uint8_t *out, size_t cap, size_t *out_len,
                           const char *client_id, uint16_t keepalive_seconds,
                           int clean_session);
int amimqtt_parse_connack(const uint8_t *packet, size_t len, uint8_t *return_code);
int amimqtt_encode_publish_qos0(uint8_t *out, size_t cap, size_t *out_len,
                                const char *topic, const uint8_t *payload,
                                size_t payload_len, int retain);

#endif
