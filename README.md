# AmiMQTT

Lightweight MQTT client infrastructure for classic Amiga systems.

AmiMQTT targets AmigaOS 2.04+ and Motorola 68000-class systems first, with a deliberately small footprint and MQTT 3.1.1 as the initial protocol target. The project is intended both as a standalone command-line client and as reusable infrastructure for ARexx-enabled Amiga applications, Home Assistant, BBS software, monitoring tools, and other network-aware software.

## M0 goals

M0 establishes the project foundation only. It does not claim working MQTT networking yet.

- AmigaOS 2.04+ baseline
- Motorola 68000 baseline
- Bebbo `m68k-amigaos-gcc` toolchain
- repository/build/test skeleton
- public C API boundary
- protocol and transport separation
- documented MQTT 3.1.1 roadmap
- ARexx and Home Assistant integration planned, not yet implemented
- conservative security model for inbound control

## Planned command-line shape

Future milestones are expected to grow toward commands such as:

```text
AmiMQTT CONNECT broker.example 1883
AmiMQTT PUB amiga/a1200/status online
AmiMQTT SUB amiga/a1200/command
```

The exact CLI is not frozen at M0.

## Design principles

1. **Classic-first** — 68000 and AmigaOS 2.04+ remain first-class constraints.
2. **Small protocol core** — implement only the MQTT features needed by each milestone.
3. **Transport separation** — MQTT packet handling should not depend on a single TCP/IP stack implementation.
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

## Build

M0 includes a host-side foundation check:

```sh
make check
```

The native Amiga build target is intentionally introduced once executable source exists in M1.

## Roadmap

See [ROADMAP.md](ROADMAP.md).

## License

MIT. See [LICENSE](LICENSE).
