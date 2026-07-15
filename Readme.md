# Software USIM Emulator

An educational software implementation of a 3GPP USIM card.

The goal of this project is to emulate the behavior of a telecom USIM at the APDU level so engineers, students, and embedded developers can understand how a modem communicates with a SIM card without requiring specialized hardware.

This project follows ISO/IEC 7816 and relevant ETSI/3GPP specifications where practical.

---

## Motivation
Most modem engineers understand RRC, NAS, MAC, and PHY.
Very few understand what happens before network registration:

Phone
↓
Baseband
↓
USIM
↓
Authentication
↓
Network Attach

The communication between the modem and the USIM is almost never taught outside telecom companies.
This repository aims to bridge that gap.

---

## Objectives

Implement a software USIM capable of

- Parsing APDUs
- Emulating a USIM file system
- Responding to standard commands
- Simulating card state transitions
- Providing detailed protocol logs

This project intentionally excludes cryptographic secrets used in commercial SIM cards.

---

## Scope of This Emulator

This project is **not** a full smart card emulator.

Instead, it focuses on implementing the software layers required to understand how a modem communicates with a USIM using publicly documented standards.

| Standard | Component | Status |
|----------|-----------|--------|
| ISO/IEC 7816-1 | Physical Characteristics | ❌ Not Implemented |
| ISO/IEC 7816-2 | Contact Dimensions & Pin Assignment | ❌ Not Implemented |
| ISO/IEC 7816-3 | Electrical Interface & Transport | 🚧 Partial (ATR, T=0 simulation planned) |
| ISO/IEC 7816-4 | APDU Commands & Responses | ✅ Primary Focus |
| ETSI TS 102 221 | UICC File System | ✅ Planned |
| 3GPP TS 31.101 | UICC Interface | ✅ Planned |
| 3GPP TS 31.102 | USIM Application | ✅ Primary Focus |

### Why?

Commercial UICCs consist of dedicated secure hardware, proprietary operating systems, and hardware cryptographic engines.

This project intentionally focuses on the **software behavior** defined by open standards.

The objective is to help engineers understand and experiment with:

- APDU communication
- UICC file system
- USIM application behavior
- PIN verification
- Authentication procedures
- Modem ↔ USIM interaction

The project **does not** attempt to emulate:

- Smart card electrical characteristics
- Physical contacts
- Secure hardware
- Hardware cryptographic accelerators
- Proprietary smart card operating systems

## Standards

### ISO/IEC 7816

Defines

- Electrical interface
- Card reset
- ATR
- APDU format

Implemented modules

✓ APDU Parser
✓ ATR Generator
✓ T=0 Protocol (planned)

---

### ETSI TS 102 221

Defines

- Smart card file system
- File identifiers
- Status words
- SELECT FILE
- READ BINARY

Implemented modules

✓ File System
✓ File Selection
✓ Binary Read

---

### 3GPP TS 31.101

General UICC characteristics.
Implemented where applicable.

---

### 3GPP TS 31.102

USIM Application
Planned support includes
- EF_ICCID
- EF_IMSI
- EF_AD
- EF_SPN
- EF_PLMN
- Service Table

---

## Architecture

Host
↓
APDU
↓
APDU Parser
↓
Command Dispatcher
↓
Virtual File System
↓
Response APDU

---

## Project Roadmap

Phase 1
- APDU parser

Phase 2
- Virtual File System

Phase 3
- ATR generation

Phase 4
- State Machine

Phase 5
- Authentication (dummy algorithm)

Phase 6
- Logging

Phase 7
- GUI APDU Explorer

---

## Design Philosophy

The objective is standards compliance rather than hardware emulation.
Each implemented feature references the corresponding telecom specification.
Each source file links to the clause of the standard from which it is derived.

---

## Intended Audience

- Telecom Engineers
- Embedded Engineers
- Modem Developers
- SDR Developers
- Students learning Cellular Networks
- Smart Card Developers

---

## Non-goals

This project is NOT intended to

- Clone SIM cards
- Extract authentication keys
- Emulate operator-specific secrets
- Bypass network authentication

Only publicly documented standards are implemented.

---

## License

None