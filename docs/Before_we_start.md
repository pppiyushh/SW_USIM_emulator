# What Are We Actually Emulating?

> **Purpose:** Define the scope of this project and clarify what a commercial USIM consists of compared to what is implemented by this emulator.

---

# Introduction

A common misconception is that a **USIM** is simply a memory chip containing subscriber information.

In reality, a commercial USIM is a complete embedded computing system consisting of:

* A microcontroller
* Bootloader
* Smart Card Operating System
* Cryptographic libraries
* One or more applications (USIM, ISIM, etc.)

This project **does not attempt to emulate the entire smart card**.

Instead, it focuses on implementing the **USIM application layer** using publicly available standards.

---

# Architecture of a Commercial USIM

```text
                    Commercial UICC
+------------------------------------------------------+
|                USIM Application                      |
|------------------------------------------------------|
| • APDU Command Handlers                              |
| • File System                                        |
| • Authentication Procedures                          |
| • PIN Verification                                   |
| • Subscriber Data                                    |
+------------------------------------------------------+
|              Smart Card Operating System             |
|------------------------------------------------------|
| • ISO/IEC 7816 Communication                         |
| • Memory Management                                  |
| • Security Services                                  |
| • Logical Channels                                   |
| • Application Management                             |
+------------------------------------------------------+
|          Hardware Abstraction Layer (HAL)            |
+------------------------------------------------------+
|            Cryptographic Library                     |
|------------------------------------------------------|
| • AES                                                |
| • SHA                                                |
| • ECC                                                |
| • AKA / Milenage                                     |
+------------------------------------------------------+
|                   Bootloader                         |
+------------------------------------------------------+
|            Smart Card Microcontroller                |
|------------------------------------------------------|
| • CPU                                                |
| • RAM                                                |
| • EEPROM / Flash                                     |
| • Random Number Generator                            |
| • Crypto Accelerators                                |
+------------------------------------------------------+
```

---

# Layer Description

## 1. Smart Card Microcontroller

The foundation of the UICC is a low-power embedded microcontroller.

Typical components include:

* CPU
* RAM
* ROM
* EEPROM or Flash
* Hardware Random Number Generator (TRNG)
* Cryptographic accelerators

Commercial UICCs may use proprietary architectures or processors such as ARM SC000, 8051 derivatives, RISC-V, or vendor-specific cores.

---

## 2. Bootloader

The bootloader executes immediately after power-on.

Typical responsibilities:

* Initialize hardware
* Verify firmware integrity
* Configure memory
* Start the Smart Card Operating System

---

## 3. Cryptographic Library

Provides reusable cryptographic services for applications.

Examples include:

* AES
* SHA
* Elliptic Curve Cryptography (ECC)
* AKA algorithms
* Random number generation

The USIM application uses these services instead of implementing cryptographic algorithms itself.

---

## 4. Hardware Abstraction Layer (HAL)

The HAL provides a hardware-independent interface between the operating system and the physical device.

Typical responsibilities:

* EEPROM access
* Timers
* ISO/IEC 7816 I/O
* Interrupt handling
* Clock management

---

## 5. Smart Card Operating System

The Smart Card OS manages common platform functionality shared by all applications.

Responsibilities include:

* ISO/IEC 7816 communication
* APDU transport
* Memory management
* Application management
* Access control
* Logical channel management

Examples of commercial Smart Card Operating Systems include Java Card OS and MULTOS, while many vendors also develop proprietary operating systems.

---

## 6. USIM Application

The USIM application is responsible for implementing subscriber-specific functionality.

Typical responsibilities:

* APDU command processing
* USIM file system
* PIN verification
* Authentication procedures
* Subscriber information storage
* Service configuration

This is the primary focus of this repository.

---

# What This Project Implements

The Software USIM Emulator focuses on software behavior defined by public standards.

## Implemented

* APDU parser
* APDU command dispatcher
* Virtual USIM file system
* APDU response generation
* PIN verification (planned)
* USIM state machine
* Subscriber data management

---

# What This Project Does NOT Implement

The following components are intentionally outside the scope of this repository:

* Physical smart card hardware
* Smart Card Operating System
* Bootloader
* Hardware cryptographic accelerators
* EEPROM controllers
* Electrical signaling
* ISO/IEC 7816 physical layer
* Proprietary vendor implementations

---

# Project Scope

```text
Commercial UICC

Microcontroller               ❌
Bootloader                    ❌
Hardware Drivers              ❌
Hardware Crypto               ❌
Smart Card OS                 ❌

USIM Application              ✅
APDU Processing               ✅
Virtual File System           ✅
PIN Management                ✅
State Machine                 ✅
Authentication Flow           ✅ (Educational)
```

---

# Why This Approach?

Implementing the complete smart card stack would require proprietary hardware, operating systems, and vendor-specific documentation.

By focusing on the USIM application layer, the project remains:

* Educational
* Standards-oriented
* Portable
* Easy to understand
* Suitable for experimentation and learning

This approach also allows engineers to understand how a modem communicates with a USIM without requiring physical smart card hardware.

---

# Relevant Standards

The following standards define the behavior implemented by this project:

* **ISO/IEC 7816-3** – Electrical Interface and Reset
* **ISO/IEC 7816-4** – APDU Commands and Responses
* **ETSI TS 102 221** – UICC Characteristics and File System
* **3GPP TS 31.101** – UICC-Application Interface
* **3GPP TS 31.102** – USIM Application

---

# Repository Mapping

| Documentation       | Implementation    |
| ------------------- | ----------------- |
| APDU                | `src/apdu/`       |
| Command Dispatcher  | `src/dispatcher/` |
| Virtual File System | `src/filesystem/` |
| USIM State Machine  | `src/usim/`       |
| APDU Responses      | `src/response/`   |

---

# Summary

The goal of this repository is **not** to emulate an entire commercial UICC.

Instead, it provides a standards-based implementation of the **USIM application layer**, enabling engineers, students, and researchers to study modem-to-USIM communication, APDU processing, and subscriber data management in a portable software environment.
