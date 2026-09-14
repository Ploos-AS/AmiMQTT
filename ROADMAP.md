# AmiMQTT Roadmap

## M0 — Foundation

Status: implemented repository foundation.

- project scope and constraints
- AmigaOS 2.04+ / Motorola 68000 baseline
- Bebbo GCC toolchain policy
- source/include/test/docs layout
- public API skeleton
- protocol/transport separation
- host-side repository checks
- security model documented

Exit criterion: repository structure and M0 checks are present and internally consistent.

## M1 — MQTT 3.1.1 CONNECT + PUBLISH

- native `AmiMQTT` executable
- minimal MQTT 3.1.1 encoder
- CONNECT / CONNACK
- QoS 0 PUBLISH
- configurable broker host and port
- TCP transport abstraction with first Amiga bsdsocket implementation
- host packet-vector tests
- native 68000 build
- visible FS-UAE runtime qualification

## M2 — SUBSCRIBE + receive loop

- SUBSCRIBE / SUBACK
- QoS 0 incoming PUBLISH
- keepalive / PINGREQ / PINGRESP
- clean disconnect
- reconnect behavior

## M3 — ARexx

- `AMIMQTT` ARexx port
- connect, publish, subscribe, status commands
- received-message event/queue mechanism
- documented scripting examples
- no arbitrary remote ARexx execution by default

## M4 — Reliability and authentication

- username/password support
- Last Will and Testament
- retained publications
- reconnect/backoff
- bounded buffers and malformed-packet handling
- credential handling documentation

TLS is expected to integrate through a transport layer (for example AmTLS) rather than coupling the MQTT protocol core to one TLS implementation.

## M5 — Home Assistant MQTT Discovery

- device metadata
- sensors
- binary sensors
- buttons/switches where safe
- availability topic
- discovery payload generator
- example Home Assistant deployment

## M6 — AmiHA bridge/tooling

- reusable Amiga telemetry conventions
- system metrics publisher
- safe command allowlist
- application adapters
- examples for BBS/security/monitoring software

## M7 — AmiHome

- native Workbench dashboard/control application
- subscribe-driven UI state
- configurable widgets/actions
- classic-machine-friendly resource budget

## Later candidates

- MQTT QoS 1
- MQTT 5 feasibility study (not a baseline goal)
- shared library/device form if real applications justify it
- Node-RED examples
- Prometheus/InfluxDB bridge conventions through external MQTT consumers
