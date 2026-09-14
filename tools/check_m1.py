#!/usr/bin/env python3
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
required = [
    "README.md",
    "ROADMAP.md",
    "Makefile",
    "include/amimqtt/amimqtt.h",
    "src/main.c",
    "src/protocol/protocol.h",
    "src/protocol/protocol.c",
    "src/transport/transport.h",
    "tests/test_protocol.c",
    "docs/M1_STATUS.md",
]

missing = [p for p in required if not (ROOT / p).exists()]
if missing:
    print("M1 FAIL: missing required paths:")
    for path in missing:
        print("  - " + path)
    sys.exit(1)

roadmap = (ROOT / "ROADMAP.md").read_text(encoding="utf-8")
status = (ROOT / "docs/M1_STATUS.md").read_text(encoding="utf-8")
protocol = (ROOT / "src/protocol/protocol.c").read_text(encoding="utf-8")
makefile = (ROOT / "Makefile").read_text(encoding="utf-8")

checks = {
    "CONNECT encoder present": "amimqtt_encode_connect" in protocol,
    "CONNACK parser present": "amimqtt_parse_connack" in protocol,
    "PUBLISH QoS0 encoder present": "amimqtt_encode_publish_qos0" in protocol,
    "68000 compiler flag present": "-m68000" in makefile,
    "M1 runtime status explicit": "PENDING" in status,
    "roadmap still requires FS-UAE": "visible FS-UAE runtime qualification" in roadmap,
}

failed = [name for name, ok in checks.items() if not ok]
if failed:
    print("M1 FAIL:")
    for name in failed:
        print("  - " + name)
    sys.exit(1)

print("M1 STATIC PASS")
for name in checks:
    print("  PASS: " + name)
print("M1 RUNTIME: PENDING")
