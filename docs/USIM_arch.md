# USIM Internal Architecture

> **Objective:** Understand the software and hardware architecture of a commercial UICC and identify which components are implemented by this Software USIM Emulator.

---

# Introduction

A Universal Subscriber Identity Module (USIM) is **not** a standalone hardware device.

Instead, it is a software application that executes on a secure embedded platform known as the **Universal Integrated Circuit Card (UICC)**.

The UICC itself is a complete embedded computer consisting of hardware, firmware, an operating system, cryptographic services, and one or more applications.

Understanding this layered architecture is essential before implementing or emulating USIM functionality.

---

# High-Level Architecture

```text
                     Commercial UICC

+----------------------------------------------------------+
|                 USIM Application                         |
|----------------------------------------------------------|
| APDU Handlers                                            |
| File System                                               |
| PIN Management                                            |
| Authentication Procedures                                 |
| Subscriber Information                                    |
+----------------------------------------------------------+
|              Smart Card Operating System                 |
|----------------------------------------------------------|
| ISO/IEC 7816 Transport                                   |
| Memory Management                                        |
| Application Loader                                       |
| Access Control                                           |
| Logical Channels                                         |
+----------------------------------------------------------+
|          Hardware Abstraction Layer (HAL)                |
+----------------------------------------------------------+
|            Cryptographic Services                        |
|----------------------------------------------------------|
| AES                                                      |
| SHA                                                      |
| ECC                                                      |
| Random Number Generator                                  |
| AKA Support                                              |
+----------------------------------------------------------+
| Bootloader                                               |
+----------------------------------------------------------+
| Smart Card Microcontroller                               |
|----------------------------------------------------------|
| CPU                                                      |
| RAM                                                      |
| ROM                                                      |
| EEPROM / Flash                                           |
| Crypto Accelerators                                      |
| Timers                                                   |
+----------------------------------------------------------+
```

---

# Layer 1 — Smart Card Microcontroller

The lowest layer is the secure embedded processor.

Unlike ordinary microcontrollers, smart-card processors are specifically designed for high-security environments.

Typical hardware resources include:

* CPU core
* ROM
* RAM
* EEPROM or Flash
* Hardware cryptographic engine
* True Random Number Generator (TRNG)
* Security sensors
* Clock generation circuitry

Commercial vendors often use proprietary secure microcontrollers optimized for low power and resistance to physical attacks.

---

# Layer 2 — Bootloader

After power is applied, execution begins at the bootloader.

Typical responsibilities include:

* Hardware initialization
* Clock configuration
* Memory initialization
* Firmware integrity verification
* Starting the Smart Card Operating System

This layer is generally proprietary and invisible to application developers.

---

# Layer 3 — Cryptographic Services

Most cryptographic functionality is implemented as reusable system services.

Examples include:

* AES
* SHA
* Elliptic Curve Cryptography (ECC)
* Random number generation
* Authentication primitives

The USIM application invokes these services instead of implementing cryptographic algorithms directly.

---

# Layer 4 — Hardware Abstraction Layer

The Hardware Abstraction Layer (HAL) isolates software from hardware-specific implementation details.

Typical responsibilities include:

* EEPROM access
* Timer services
* Interrupt handling
* ISO/IEC 7816 I/O
* Clock management

This separation allows the Smart Card Operating System to be reused across different hardware platforms.

---

# Layer 5 — Smart Card Operating System

The Smart Card Operating System provides common platform functionality.

Typical services include:

* APDU transport
* Memory management
* File access
* Application management
* Access control
* Logical channel support

Examples include:

* Java Card OS
* MULTOS
* Proprietary operating systems

Most commercial implementations are proprietary.

---

# Layer 6 — USIM Application

The USIM application provides subscriber-specific functionality defined by 3GPP.

Responsibilities include:

* Processing APDU commands
* Managing the virtual file system
* Storing subscriber information
* PIN verification
* Authentication procedures
* Service configuration

This is the layer implemented by this repository.

---

# Relationship Between Phone and USIM

```text
                 Smartphone

+------------------------------------------+
| Application Processor                    |
+------------------------------------------+
| Baseband Modem                           |
+------------------------------------------+
               │
               │ ISO/IEC 7816 APDUs
               ▼
+------------------------------------------+
| UICC                                     |
|                                          |
|  Smart Card OS                           |
|        │                                 |
|        ▼                                 |
|     USIM Application                     |
+------------------------------------------+
```

The baseband modem exchanges APDUs with the USIM application. The modem is unaware of the internal operating system or hardware implementation.

---

# Emulator Scope

This project focuses exclusively on the behavior of the USIM application.

Implemented:

* APDU parsing
* Command dispatch
* Virtual file system
* Response APDUs
* PIN management (planned)
* USIM state machine
* Educational authentication flow

Not implemented:

* Physical smart-card hardware
* Smart Card Operating System
* Bootloader
* Hardware cryptographic engines
* ISO/IEC 7816 electrical signaling
* Vendor-specific firmware

---

# Design Philosophy

The objective of this emulator is to provide a standards-oriented implementation of the **USIM application layer** rather than reproducing proprietary hardware or firmware.

Each implemented feature will be traceable to the relevant ISO, ETSI, or 3GPP specification.

---

# Relevant Standards

| Standard        | Description                    |
| --------------- | ------------------------------ |
| ISO/IEC 7816-3  | Electrical Interface and Reset |
| ISO/IEC 7816-4  | APDU Commands and Responses    |
| ETSI TS 102 221 | UICC Characteristics           |
| 3GPP TS 31.101  | UICC-Application Interface     |
| 3GPP TS 31.102  | USIM Application               |

---

# Looking Ahead

The following chapters build upon this architecture:

* ISO/IEC 7816
* ATR (Answer To Reset)
* APDU Communication
* UICC File System
* USIM Elementary Files
* Authentication Procedures
* Security Architecture

By understanding this layered architecture first, the implementation of the Software USIM Emulator becomes much easier to follow.
