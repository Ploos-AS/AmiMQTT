#include "protocol.h"

#include <string.h>

static int encode_remaining_length(uint8_t *out, size_t cap, size_t value, size_t *used) {
    size_t i = 0;
    do {
        uint8_t byte;
        if (i >= cap || i >= 4) return -1;
        byte = (uint8_t)(value % 128u);
        value /= 128u;
        if (value) byte |= 0x80u;
        out[i++] = byte;
    } while (value);
    *used = i;
    return 0;
}

static int put_utf8(uint8_t *out, size_t cap, size_t *pos, const char *s) {
    size_t n = strlen(s);
    if (n > 65535u || *pos + 2u + n > cap) return -1;
    out[(*pos)++] = (uint8_t)((n >> 8) & 0xffu);
    out[(*pos)++] = (uint8_t)(n & 0xffu);
    memcpy(out + *pos, s, n);
    *pos += n;
    return 0;
}

int amimqtt_encode_connect(uint8_t *out, size_t cap, size_t *out_len,
                           const char *client_id, uint16_t keepalive_seconds,
                           int clean_session) {
    uint8_t body[512];
    size_t body_len = 0, rem_len_bytes = 0;
    uint8_t rem[4];

    if (!out || !out_len || !client_id) return -1;
    if (put_utf8(body, sizeof(body), &body_len, "MQTT") != 0) return -1;
    if (body_len + 4u > sizeof(body)) return -1;
    body[body_len++] = 4; /* MQTT 3.1.1 */
    body[body_len++] = clean_session ? 0x02u : 0x00u;
    body[body_len++] = (uint8_t)(keepalive_seconds >> 8);
    body[body_len++] = (uint8_t)(keepalive_seconds & 0xffu);
    if (put_utf8(body, sizeof(body), &body_len, client_id) != 0) return -1;

    if (encode_remaining_length(rem, sizeof(rem), body_len, &rem_len_bytes) != 0) return -1;
    if (1u + rem_len_bytes + body_len > cap) return -1;
    out[0] = 0x10u;
    memcpy(out + 1u, rem, rem_len_bytes);
    memcpy(out + 1u + rem_len_bytes, body, body_len);
    *out_len = 1u + rem_len_bytes + body_len;
    return 0;
}

int amimqtt_parse_connack(const uint8_t *packet, size_t len, uint8_t *return_code) {
    if (!packet || len != 4u || packet[0] != 0x20u || packet[1] != 0x02u) return -1;
    if ((packet[2] & 0xfeu) != 0u || packet[3] > 5u) return -1;
    if (return_code) *return_code = packet[3];
    return 0;
}

int amimqtt_encode_publish_qos0(uint8_t *out, size_t cap, size_t *out_len,
                                const char *topic, const uint8_t *payload,
                                size_t payload_len, int retain) {
    size_t topic_len, remaining, rem_len_bytes, pos;
    uint8_t rem[4];

    if (!out || !out_len || !topic || (!payload && payload_len)) return -1;
    topic_len = strlen(topic);
    if (topic_len == 0u || topic_len > 65535u) return -1;
    remaining = 2u + topic_len + payload_len;
    if (encode_remaining_length(rem, sizeof(rem), remaining, &rem_len_bytes) != 0) return -1;
    if (1u + rem_len_bytes + remaining > cap) return -1;

    out[0] = (uint8_t)(0x30u | (retain ? 0x01u : 0x00u));
    memcpy(out + 1u, rem, rem_len_bytes);
    pos = 1u + rem_len_bytes;
    out[pos++] = (uint8_t)(topic_len >> 8);
    out[pos++] = (uint8_t)(topic_len & 0xffu);
    memcpy(out + pos, topic, topic_len);
    pos += topic_len;
    if (payload_len) memcpy(out + pos, payload, payload_len);
    pos += payload_len;
    *out_len = pos;
    return 0;
}
