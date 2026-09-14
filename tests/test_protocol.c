#include "../src/protocol/protocol.h"

#include <stdio.h>
#include <string.h>

static int check(const unsigned char *got, size_t got_len,
                 const unsigned char *want, size_t want_len,
                 const char *name) {
    if (got_len != want_len || memcmp(got, want, want_len) != 0) {
        fprintf(stderr, "FAIL: %s\n", name);
        return 1;
    }
    printf("PASS: %s\n", name);
    return 0;
}

int main(void) {
    unsigned char out[512];
    size_t len = 0;
    unsigned char rc = 255;
    int failed = 0;

    static const unsigned char connect_expected[] = {
        0x10,0x10,0x00,0x04,'M','Q','T','T',0x04,0x02,0x00,0x3c,
        0x00,0x04,'t','e','s','t'
    };
    static const unsigned char publish_expected[] = {
        0x30,0x0a,0x00,0x03,'a','/','b','h','e','l','l','o'
    };
    static const unsigned char connack_ok[] = {0x20,0x02,0x00,0x00};

    if (amimqtt_encode_connect(out, sizeof(out), &len, "test", 60, 1) != 0) return 1;
    failed |= check(out, len, connect_expected, sizeof(connect_expected), "CONNECT vector");

    if (amimqtt_encode_publish_qos0(out, sizeof(out), &len, "a/b",
                                    (const unsigned char *)"hello", 5, 0) != 0) return 1;
    failed |= check(out, len, publish_expected, sizeof(publish_expected), "PUBLISH QoS0 vector");

    if (amimqtt_parse_connack(connack_ok, sizeof(connack_ok), &rc) != 0 || rc != 0) {
        fprintf(stderr, "FAIL: CONNACK parse\n"); failed = 1;
    } else puts("PASS: CONNACK parse");

    return failed ? 1 : 0;
}
