# Embedded Systems — Amit Learning

This repository contains my work from the **Embedded Systems** course at **Amit Learning**. Throughout the course I built a number of projects covering embedded C, layered driver architectures (MCAL/HAL), data structures in C, and AVR microcontroller programming. Below are the most important ones.

**Author:** Hussain Zaid

---

## 📌 Featured Projects

### 1. [Smart Home Automation System](./Smart_Home_Automation_System)
An AVR (ATmega32-family) embedded C project implementing a keypad + LCD secured door/servo access system, built on a layered driver architecture (MCAL / HAL / UTILS).

- 4x4 keypad + 16x2 LCD user interface
- Password-protected access control with limited retry attempts and lockout alarm
- Servo-driven door lock, LED status indicators
- Modular MCAL/HAL driver structure (DIO, PWM, KPD, LCD, SRVM, etc.)

📄 See the [project README](./Smart_Home_Automation_System/README.md) for full details.

---

### 2. [Student Database Management System](./Student_Database_Management_System)
A Student Database Management System implemented in C using **singly linked lists** for dynamic storage.

- Add, delete, and search student records (ID, year, courses, grades)
- Display all student IDs and check for duplicates
- Capacity-limited database with modular `.c`/`.h` design

📄 See the [project README](./Student_Database_Management_System/README.md) for full details.

---

## 🎓 About the Course

These projects were developed as part of the **Embedded Systems** track at **Amit Learning**, covering:
- Embedded C programming fundamentals
- Layered driver design (MCAL / HAL / UTILS separation)
- Peripheral interfacing (keypads, LCDs, servos, LEDs)
- Data structures in C (linked lists) for application-level logic
- AVR microcontroller development workflow (Atmel/Microchip Studio)

## 📂 Repository Structure

```
Embedded-Systems---Amit-Learning/
├── Smart_Home_Automation_System/
│   └── README.md
├── Student_Database_Management_System/
│   └── README.md
└── README.md   (this file)
```

---

⭐ More projects from the course may be added here over time.
