# M1 Status — MQTT 3.1.1 CONNECT + PUBLISH

## Implemented

- MQTT 3.1.1 CONNECT encoder
- CONNACK parser
- QoS 0 PUBLISH encoder
- MQTT Remaining Length encoding
- transport interface boundary
- native CLI packet-generation shell
- host packet-vector tests
- `-m68000` native build target

## Current qualification status

Host/static implementation: READY FOR QUALIFICATION.

Native Amiga/FS-UAE runtime qualification: **PENDING**.

M1 must not be marked fully qualified until a visible AmigaOS 2.04+ / 68000-class FS-UAE run has demonstrated the native binary and the agreed runtime path. The initial CLI intentionally exposes packet generation while socket lifecycle wiring is completed and qualified against the Amiga transport layer.

## Expected host qualification

```sh
make clean
make check
```

Expected result:

```text
PASS: CONNECT vector
PASS: PUBLISH QoS0 vector
PASS: CONNACK parse
M1 STATIC PASS
...
M1 RUNTIME: PENDING
```

## Native build

```sh
make amiga
```

Expected artifact:

```text
build/AmiMQTT
```

The native build baseline remains AmigaOS 2.04+ and Motorola 68000.
