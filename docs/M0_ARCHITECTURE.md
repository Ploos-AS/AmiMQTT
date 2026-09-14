# M0 Architecture

AmiMQTT is split into three conceptual layers:

1. CLI / application layer
2. MQTT protocol core
3. transport layer

The protocol core owns MQTT packet encoding/decoding and MQTT session state. It must not call Amiga socket APIs directly. The transport layer owns TCP I/O and hides stack-specific details.

## Baseline

- CPU: Motorola 68000
- OS: AmigaOS 2.04+
- compiler: Bebbo `m68k-amigaos-gcc`
- protocol target: MQTT 3.1.1
- initial QoS: QoS 0

## Security boundary

Inbound MQTT messages are data, not executable commands by default. Higher-level command integrations must define explicit operations and allowlists. ARexx support must not turn arbitrary broker payloads into unrestricted `RX`/command execution unless a user explicitly enables such a mode.

## Allocation policy

Classic systems benefit from predictable memory use. Protocol code should favor caller-provided or bounded buffers and avoid large implicit allocations.

## Compatibility policy

Features must not silently raise the minimum CPU or OS requirement. Accelerated builds may be considered later, but the baseline remains 68000 / AmigaOS 2.04+ unless the roadmap is explicitly revised.
