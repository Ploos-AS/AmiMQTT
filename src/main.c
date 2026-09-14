#include "amimqtt/amimqtt.h"
#include "protocol/protocol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void usage(void) {
    puts("AmiMQTT M1\n"
         "Usage:\n"
         "  AmiMQTT encode-connect <client-id> [keepalive]\n"
         "  AmiMQTT encode-publish <topic> <payload>\n"
         "\n"
         "Network CONNECT/PUBLISH wiring is completed against the Amiga bsdsocket transport\n"
         "after native runtime qualification. M1 host packet generation is available now.");
}

static void dump_hex(const unsigned char *p, size_t n) {
    size_t i;
    for (i = 0; i < n; ++i) printf("%02X%s", p[i], i + 1u == n ? "\n" : " ");
}

int main(int argc, char **argv) {
    unsigned char packet[1024];
    size_t len = 0;

    if (argc < 2) { usage(); return 2; }
    if (strcmp(argv[1], "encode-connect") == 0) {
        unsigned long keepalive = 60;
        if (argc < 3 || argc > 4) { usage(); return 2; }
        if (argc == 4) keepalive = strtoul(argv[3], 0, 10);
        if (keepalive > 65535ul || amimqtt_encode_connect(packet, sizeof(packet), &len, argv[2], (unsigned short)keepalive, 1) != 0) return 1;
        dump_hex(packet, len);
        return 0;
    }
    if (strcmp(argv[1], "encode-publish") == 0) {
        if (argc != 4) { usage(); return 2; }
        if (amimqtt_encode_publish_qos0(packet, sizeof(packet), &len, argv[2], (const unsigned char *)argv[3], strlen(argv[3]), 0) != 0) return 1;
        dump_hex(packet, len);
        return 0;
    }
    usage();
    return 2;
}
