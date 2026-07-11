# Software USIM Emulator -- Development Plan

> **Temporary planning document.** This file is intended for local
> development and may be removed before publishing the repository.

------------------------------------------------------------------------

# Vision

Build an educational Software USIM Emulator that implements the publicly
documented behavior of a USIM/UICC according to ISO/IEC, ETSI, and 3GPP
specifications.

The project is intended to help engineers understand how a modem
communicates with a USIM, prototype APDU flows, and test software
without requiring physical SIM hardware.

------------------------------------------------------------------------

# Goals

-   Learn the USIM communication stack from first principles.
-   Implement standards incrementally.
-   Keep every feature traceable to a specification.
-   Provide a clean reference implementation.
-   Build reusable components for future telecom projects.

------------------------------------------------------------------------

# Target Audience

-   Telecom engineers
-   Modem developers
-   Embedded software engineers
-   Students
-   SDR enthusiasts

------------------------------------------------------------------------

# Out of Scope

This project will **not** attempt to:

-   Clone SIM cards
-   Recover secret keys
-   Bypass authentication
-   Emulate operator-specific proprietary behavior

Only publicly documented standards are implemented.

------------------------------------------------------------------------

# Standards Roadmap

## Phase 1 --- ISO/IEC 7816-4 (APDU Layer)

### Objectives

-   APDU parser
-   APDU encoder
-   Command dispatcher
-   Response APDU generator

Deliverables

-   Parse command APDUs
-   Generate response APDUs
-   Unit tests

------------------------------------------------------------------------

## Phase 2 --- ETSI TS 102 221 (UICC File System)

### Objectives

Implement the virtual file system.

Files

-   MF
-   DF
-   EF

Commands

-   SELECT FILE
-   READ BINARY
-   GET RESPONSE

Deliverables

-   Virtual file hierarchy
-   File navigation
-   Status word handling

------------------------------------------------------------------------

## Phase 3 --- ISO/IEC 7816-3 (Card Behaviour)

### Objectives

-   ATR generation
-   Reset handling
-   Basic card lifecycle
-   Optional PPS negotiation

Deliverables

-   Configurable ATR
-   Card state machine

------------------------------------------------------------------------

## Phase 4 --- 3GPP TS 31.101 / TS 31.102 (USIM Application)

Implement commonly used elementary files.

Examples

-   EF_ICCID
-   EF_IMSI
-   EF_AD
-   EF_SPN
-   EF_UST
-   EF_PLMN
-   EF_LOCI

Deliverables

-   Standards-compliant virtual USIM
-   Example subscriber profiles

------------------------------------------------------------------------

## Phase 5 --- Access Control

Implement

-   PIN verification
-   Access conditions
-   Administrative states

Deliverables

-   Session management
-   Permission checks

------------------------------------------------------------------------

## Phase 6 --- Developer Tooling

### CLI

-   Send APDUs
-   Inspect files
-   Trace commands

### Logging

-   APDU trace
-   Timing
-   State transitions

### Future GUI

-   File explorer
-   APDU console
-   Hex viewer

------------------------------------------------------------------------

# Architecture

Host Application

↓

APDU Parser

↓

Command Dispatcher

↓

USIM State Machine

↓

Virtual File System

↓

Response APDU

------------------------------------------------------------------------

# Why This Project Matters

This project can be used to:

-   Understand modem ↔ USIM communication
-   Prototype APDU exchanges
-   Test software before hardware is available
-   Unit-test USIM client libraries
-   Learn telecom standards through code
-   Build educational demonstrations

------------------------------------------------------------------------

# Coding Principles

-   Standards-first implementation
-   Small independent modules
-   Extensive unit testing
-   Clear documentation
-   Clause references in source files

------------------------------------------------------------------------

# Future Extensions

-   T=1 protocol support
-   Logical channels
-   Secure messaging (educational)
-   APDU fuzz testing
-   PC/SC integration
-   Wireshark-compatible trace export
-   Web-based protocol explorer

------------------------------------------------------------------------

# Repository Structure (Planned)

``` text
software-usim-emulator/
├── README.md
├── PLAN.md
├── docs/
├── src/
├── tests/
├── examples/
└── scripts/
```

------------------------------------------------------------------------

# Success Criteria

-   Standards-compliant APDU processing
-   Virtual USIM file system
-   Clear architecture documentation
-   High test coverage
-   Useful as both a learning resource and a development aid
