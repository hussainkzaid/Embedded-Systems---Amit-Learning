# Embedded Systems — Amit Learning

This repository contains my work from the **Embedded Systems** course at **Amit Learning**. Throughout the course I built a number of projects covering embedded C, layered driver architectures (MCAL/HAL), data structures in C, and AVR microcontroller programming. Below are the most important ones.

**Author:** Hussain Zaid

---

## 📌 Featured Projects

### 1. 🎓 [Graduation Project — Smart Home System](./Graduation_Project)
The **capstone project** of the diploma: a fully layered AVR embedded system with dual interfaces (keypad+LCD and UART terminal), role-based access (Admin/User), EEPROM-backed user database, temperature-driven AC control, dimmable lighting, servo-controlled door, and an alarm system with watchdog reset on repeated failed logins.

- Strict layered architecture: `main.c` (26 lines, zero logic) → Application (AppManager FSM, UIManager, Login, DeviceControl, TempManager, CommHandler, AlarmManager) → HAL → MCAL
- Dual login channels: local keypad/LCD and remote UART terminal, sharing one user database in EEPROM
- Admin can add/remove/permit/block users in real time over UART
- LM35-based automatic AC control by temperature thresholds
- 5 lamps + 1 dimmer (PWM), servo-controlled door, DC motor–driven AC
- 3 failed login attempts trigger an alarm and a watchdog-timer MCU reset

📄 See the [full project documentation](./Graduation_Project/README.md) for the complete architecture, module APIs, pin mapping, and UART command reference.

---

### 2. [Smart Home Automation System](./Smart_Home_Automation_System)
An AVR (ATmega32-family) embedded C project implementing a keypad + LCD secured door/servo access system, built on a layered driver architecture (MCAL / HAL / UTILS).

- 4x4 keypad + 16x2 LCD user interface
- Password-protected access control with limited retry attempts and lockout alarm
- Servo-driven door lock, LED status indicators
- Modular MCAL/HAL driver structure (DIO, PWM, KPD, LCD, SRVM, etc.)

📄 See the [project README](./Smart_Home_Automation_System/README.md) for full details.

---

### 3. [Student Database Management System](./Student_Database_Management_System)
A Student Database Management System implemented in C using **singly linked lists** for dynamic storage.

- Add, delete, and search student records (ID, year, courses, grades)
- Display all student IDs and check for duplicates
- Capacity-limited database with modular `.c`/`.h` design

📄 See the [project README](./Student_Database_Management_System/README.md) for full details.

---

## 🎓 About the Course

These projects were developed as part of the **Embedded Systems Diploma** at **AMIT**, covering:
- Introduction to Embedded Systems
- Embedded Systems Tooling
- Automotive Bus Technology
- AUTOSAR Standard
- C Programming & Data Structures
- Interfacing with Microcontroller (AVR)
- RTOS

## 🏆 Certification

I completed the **Embedded Systems Diploma** at AMIT — a **172-hour** course — with a grade of **95%**.

📄 [View Certificate](./Hussain_Kamel_Refaat.pdf)

## 📂 Repository Structure

```
Embedded-Systems---Amit-Learning/
├── Graduation_Project/
│   └── README.md
├── Smart_Home_Automation_System/
│   └── README.md
├── Student_Database_Management_System/
│   └── README.md
├── Hussain_Kamel_Refaat.pdf
└── README.md   (this file)
```

---

⭐ More projects from the course may be added here over time.
