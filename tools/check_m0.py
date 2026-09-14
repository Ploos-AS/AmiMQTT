#!/usr/bin/env python3
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
required = [
    "README.md",
    "ROADMAP.md",
    "LICENSE",
    "Makefile",
    "docs/M0_ARCHITECTURE.md",
    "include/amimqtt/amimqtt.h",
    "src/README.md",
    "src/protocol/README.md",
    "src/transport/README.md",
]

missing = [p for p in required if not (ROOT / p).exists()]
if missing:
    print("M0 FAIL: missing required paths:")
    for path in missing:
        print(f"  - {path}")
    sys.exit(1)

readme = (ROOT / "README.md").read_text(encoding="utf-8")
roadmap = (ROOT / "ROADMAP.md").read_text(encoding="utf-8")
header = (ROOT / "include/amimqtt/amimqtt.h").read_text(encoding="utf-8")

checks = {
    "README states AmigaOS 2.04+": "AmigaOS 2.04+" in readme,
    "README states 68000 baseline": "68000" in readme,
    "roadmap has M1": "## M1" in roadmap,
    "roadmap has ARexx": "ARexx" in roadmap,
    "roadmap has Home Assistant": "Home Assistant" in roadmap,
    "header exposes version": "AMIMQTT_VERSION_MAJOR" in header,
}

failed = [name for name, ok in checks.items() if not ok]
if failed:
    print("M0 FAIL:")
    for name in failed:
        print(f"  - {name}")
    sys.exit(1)

print("M0 PASS")
for name in checks:
    print(f"  PASS: {name}")
