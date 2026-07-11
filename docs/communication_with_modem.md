# End-to-End Modem to USIM Communication Flow

> **Objective:** Provide a high-level overview of how a mobile device communicates with the UICC/USIM from power-on until successful network registration.

---

# Introduction

When a mobile phone powers on, a sequence of events occurs before it can register with the cellular network.

Although users only see a signal icon appear, the modem, UICC, and network perform numerous protocol exchanges behind the scenes.

This document serves as the roadmap for the Software USIM Emulator documentation.

Each step described here is covered in detail in subsequent chapters.

---

# Complete Communication Flow

```text
                  Smartphone Power On
                           │
                           ▼
                 Baseband Modem Boot
                           │
                           ▼
                Initialize SIM Interface
                           │
                           ▼
                 Power On the UICC
                           │
                           ▼
                  Reset the UICC
                           │
                           ▼
          Receive ATR (Answer To Reset)
                           │
                           ▼
          Configure Communication Protocol
                    (T=0 / T=1)
                           │
                           ▼
          Begin APDU Communication
                           │
                           ▼
          Select Master File (MF)
                           │
                           ▼
          Discover Available Applications
                           │
                           ▼
          Select the USIM Application
                           │
                           ▼
          Read Subscriber Information
              • ICCID
              • IMSI
              • UST
              • PLMN
              • Other EFs
                           │
                           ▼
          Verify PIN (if required)
                           │
                           ▼
          Authentication with the Network
                           │
                           ▼
          Security Context Established
                           │
                           ▼
          Network Registration
                           │
                           ▼
          Device Ready for Service
```

---

# Step 1 — Smartphone Power-On

The device begins executing firmware.

Major components initialize independently:

* Application Processor
* Baseband Modem
* Power Management IC
* Memory Subsystem

The USIM is not yet active.

---

# Step 2 — Baseband Modem Boot

The modem firmware initializes:

* Protocol stack
* SIM interface
* RF hardware
* Internal memory
* Timers

Only after the modem is operational does it begin communicating with the UICC.

---

# Step 3 — UICC Power-Up

The modem applies power to the UICC through the ISO/IEC 7816 interface.

Typical signals include:

* VCC
* CLK
* RST
* I/O
* GND

This process is defined by ISO/IEC 7816-3.

---

# Step 4 — Card Reset

The modem resets the UICC.

The card performs internal initialization and prepares for communication.

---

# Step 5 — ATR (Answer To Reset)

Immediately after reset, the UICC transmits the ATR.

The ATR informs the modem about:

* Supported protocols
* Timing parameters
* Historical bytes
* Communication capabilities

Only after the ATR has been successfully received can APDU communication begin.

---

# Step 6 — APDU Communication

The modem and the UICC exchange Application Protocol Data Units (APDUs).

Typical commands include:

* SELECT FILE
* READ BINARY
* VERIFY
* GET RESPONSE

The APDU protocol forms the foundation of all higher-level interactions.

---

# Step 7 — File System Navigation

The modem navigates the UICC file system.

Typical operations include:

* Selecting the Master File (MF)
* Selecting Dedicated Files (DF)
* Selecting Elementary Files (EF)

The modem reads subscriber information required for network access.

---

# Step 8 — USIM Application Selection

Modern UICCs may contain multiple applications.

Examples include:

* USIM
* ISIM
* CSIM

The modem selects the USIM application before accessing subscriber data.

---

# Step 9 — Reading Subscriber Information

The modem retrieves information stored in Elementary Files.

Examples include:

* ICCID
* IMSI
* Administrative Data
* Service Table
* Preferred PLMN List

This information determines subscriber identity and available services.

---

# Step 10 — PIN Verification

If enabled, the modem requests PIN verification.

Until the PIN is successfully verified, access to protected files may be restricted.

---

# Step 11 — Network Authentication

The modem exchanges authentication messages with the cellular network.

The USIM performs secure cryptographic operations internally and returns the required responses.

Secret keys never leave the UICC.

---

# Step 12 — Security Context Establishment

After successful authentication:

* Ciphering keys are derived.
* Integrity protection is established.
* Secure communication becomes possible.

---

# Step 13 — Network Registration

The modem completes the registration procedure with the network.

At this point the device can:

* Place voice calls
* Send SMS
* Use packet data
* Access network services

---

# How This Repository Maps to the Flow

| Step                  | Documentation | Emulator |
| --------------------- | ------------- | -------- |
| Power-On              | Architecture  | ❌        |
| UICC Reset            | ATR           | 🚧       |
| ATR                   | Communication | 🚧       |
| APDU                  | APDU Parser   | ✅        |
| File System           | File System   | 🚧       |
| Application Selection | USIM          | 🚧       |
| PIN                   | Security      | 🚧       |
| Authentication        | Security      | 🚧       |
| Registration          | Informational | ❌        |

---

# Project Scope

The Software USIM Emulator focuses on the highlighted stages:

✅ APDU Processing

✅ File System

✅ USIM Application

✅ PIN Verification

✅ Authentication Flow (Educational)

The following are outside the scope of this project:

* Baseband firmware
* RF communication
* Physical signaling
* Cellular protocol stack
* Network-side infrastructure

---

# Learning Roadmap

The recommended reading order is:

1. History of Subscriber Identity
2. UICC Architecture
3. ISO/IEC 7816
4. ATR
5. APDU Communication
6. UICC File System
7. USIM Application
8. Elementary Files
9. Security
10. Authentication
11. Emulator Implementation

By following this sequence, readers will gain both the theoretical understanding and the practical knowledge required to follow the implementation of the Software USIM Emulator.
