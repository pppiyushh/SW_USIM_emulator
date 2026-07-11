# Software Architecture

> **Purpose:** Describe the architectural philosophy of the Software USIM Emulator before implementation begins.

---

# Why This Architecture?

The goal of this project is **not** to build a simple APDU parser.

Instead, the objective is to build an educational implementation that resembles the architecture of a commercial UICC while remaining completely software-based and standards-oriented.

Rather than directly implementing APDU commands in a single program, the emulator is organized into multiple software layers with clear responsibilities.

This approach provides:

* Better modularity
* Easier testing
* Cleaner separation of concerns
* Extensibility
* A closer resemblance to embedded firmware architecture

---

# Design Philosophy

The architecture follows several core principles.

## 1. Layered Design

Each software layer has a well-defined responsibility.

```text
Application
      │
      ▼
Kernel
      │
      ▼
HAL
      │
      ▼
Platform
```

Higher layers may depend on lower layers.

Lower layers must never depend on higher layers.

---

## 2. Separation of Responsibilities

Every module should perform exactly one task.

Examples:

* APDU parser → Decode APDU bytes
* File System → Manage files
* USIM → Implement 3GPP behavior
* HAL → Access persistent storage
* Platform → Interface with the host operating system

---

## 3. Educational First

Commercial UICCs contain proprietary firmware and hardware.

This project implements only publicly documented behavior.

Whenever possible, implementations reference:

* ISO/IEC 7816
* ETSI TS 102 221
* 3GPP TS 31.101
* 3GPP TS 31.102

---

# Overall Architecture

```text
                     Software USIM Emulator

+-----------------------------------------------------------+
|                    Applications                           |
|-----------------------------------------------------------|
| USIM                                                      |
| (Future: ISIM, CSIM)                                      |
+-----------------------------------------------------------+
|                         Kernel                            |
|-----------------------------------------------------------|
| Event Manager                                              |
| Application Manager                                        |
| Session Manager                                            |
| APDU Routing                                               |
+-----------------------------------------------------------+
|                   File System                             |
+-----------------------------------------------------------+
|                    APDU Layer                             |
+-----------------------------------------------------------+
|              Cryptographic Services                       |
+-----------------------------------------------------------+
|           Hardware Abstraction Layer (HAL)                |
+-----------------------------------------------------------+
|                    Platform                               |
|-----------------------------------------------------------|
| Linux (initial implementation)                            |
| Future: STM32, QEMU, Mock                                 |
+-----------------------------------------------------------+
```

---

# Boot Sequence

The emulator starts in a deterministic sequence similar to an embedded system.

```text
main()

↓

Boot

↓

Platform Initialization

↓

HAL Initialization

↓

Kernel Initialization

↓

Filesystem Initialization

↓

Application Registration

↓

Ready
```

Each stage is independent and testable.

---

# Runtime Flow

Once initialized, the emulator waits for events.

```text
                Event Loop

                     │

        +------------+-------------+

        │                          │

     APDU                    Card Reset

        │                          │

        ▼                          ▼

     Kernel                  Kernel

        │

        ▼

  Application Manager

        │

        ▼

      USIM

        │

        ▼

   File System

        │

        ▼

      Response
```

The event-driven model closely resembles embedded firmware and avoids tightly coupled function calls.

---

# Layer Responsibilities

## Platform

Responsible for interacting with the host operating system.

Examples:

* File access
* Timers
* Console
* Random number source

The rest of the emulator is platform-independent.

---

## Hardware Abstraction Layer

Provides hardware-like services.

Examples:

* EEPROM interface
* Clock
* Timer
* Random number generator

The HAL hides platform-specific implementation details.

---

## Cryptographic Services

Provides reusable cryptographic functionality.

Examples:

* AES
* SHA
* AKA primitives
* Random generation

Initially, placeholder implementations may be used where appropriate.

---

## APDU Layer

Responsible for:

* Parsing APDUs
* Encoding responses
* Validating message format

The APDU layer has no knowledge of subscriber data or file contents.

---

## File System

Implements the virtual UICC file hierarchy.

Responsibilities include:

* File selection
* Reading
* Writing
* Access permissions

The file system is independent of the APDU protocol.

---

## Kernel

Acts as the central coordinator.

Responsibilities:

* Event processing
* Application registration
* Session management
* Routing requests

The Kernel does not implement telecom-specific behavior.

---

## Applications

Applications implement telecom functionality.

Initially:

* USIM

Future possibilities:

* ISIM
* CSIM

Applications interact with the rest of the emulator exclusively through defined interfaces.

---

# Design Rules

The following architectural rules should always hold:

1. Higher layers may depend on lower layers.
2. Lower layers must never depend on higher layers.
3. Every layer exposes a minimal public interface.
4. Internal implementation details remain private.
5. Global variables should be avoided.
6. Modules communicate through interfaces rather than direct implementation access.

---

# Mapping to a Commercial UICC

```text
Commercial UICC                  Emulator

USIM Application          ─────► Applications

Smart Card OS             ─────► Kernel

Hardware Drivers          ─────► HAL

Hardware                  ─────► Platform

Persistent EEPROM         ─────► Host File
```

The emulator reproduces the software architecture while replacing specialized hardware with portable software components.

---

# Long-Term Vision

The architecture is intentionally designed for future expansion.

Potential additions include:

* ISIM support
* eSIM profile simulation
* Multiple logical channels
* Secure messaging
* APDU tracing
* Graphical debugger
* STM32 port
* QEMU-based execution

These features should require minimal architectural changes because the layering has been established from the beginning.
