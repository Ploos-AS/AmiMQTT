# AmiMQTT

Lightweight MQTT client infrastructure for classic Amiga systems.

AmiMQTT targets AmigaOS 2.04+ and Motorola 68000-class systems first, with a deliberately small footprint and MQTT 3.1.1 as the initial protocol target. The project is intended both as a standalone command-line client and as reusable infrastructure for ARexx-enabled Amiga applications, Home Assistant, BBS software, monitoring tools, and other network-aware software.

## Current status

M0 foundation is complete. M1 now provides a minimal MQTT 3.1.1 protocol core with CONNECT encoding, CONNACK parsing, QoS 0 PUBLISH encoding, host packet-vector tests, a transport abstraction, and a native 68000 build target. Visible FS-UAE runtime qualification remains pending before M1 is considered fully qualified.

## Baseline

- AmigaOS 2.04+
- Motorola 68000
- Bebbo `m68k-amigaos-gcc`
- MQTT 3.1.1
- QoS 0 first

## M1 commands

The current native CLI exposes packet generation for qualification and debugging:

```text
AmiMQTT encode-connect <client-id> [keepalive]
AmiMQTT encode-publish <topic> <payload>
```

Network lifecycle wiring through Amiga `bsdsocket.library` remains part of M1 runtime completion and must be qualified on the target environment.

## Design principles

1. **Classic-first** — 68000 and AmigaOS 2.04+ remain first-class constraints.
2. **Small protocol core** — implement only the MQTT features needed by each milestone.
3. **Transport separation** — MQTT packet handling does not depend on a single TCP/IP stack implementation.
4. **ARexx-friendly** — ARexx integration is a first-class roadmap item.
5. **Safe inbound control** — remote commands will be opt-in and allowlisted. Arbitrary ARexx execution over MQTT will never be the default.
6. **Home Assistant friendly** — MQTT Discovery support is planned after the core protocol is proven.

## Repository layout

```text
include/amimqtt/     public headers
src/                 implementation
src/protocol/        MQTT wire protocol
src/transport/       network transport abstraction
tests/               host-side tests
tools/               repository checks
docs/                design and qualification documents
```

## Build and checks

```sh
make clean
make check
```

Native 68000 build:

```sh
make amiga
```

See `docs/M1_STATUS.md` for qualification status.

## Roadmap

See [ROADMAP.md](ROADMAP.md).

## License

MIT. See [LICENSE](LICENSE).
