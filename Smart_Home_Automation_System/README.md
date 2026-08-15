# Smart Home Automation System

An AVR (ATmega32-family) embedded C project implementing a keypad + LCD secured door/servo access system, built on a layered driver architecture (MCAL / HAL / UTILS).

**Author:** Hussain Zaid

## Overview

On boot, the system prompts the user to enter a username via a 4x4 keypad, then repeatedly prompts for a 4-digit password. A correct password grants access (green LED + servo motor opens the door for 5 seconds, then closes). An incorrect password decrements the remaining trial count on the LCD. After 3 failed trials, a "SECURITY ALERT" message is shown and the red LED is activated as a visual alarm.

## Hardware

- **MCU:** ATmega32 (or compatible AVR), running at 16 MHz (`F_CPU 16000000UL`)
- **Input:** 4x4 matrix keypad
- **Output:** 16x2 character LCD
- **Actuators:** Servo motor (door lock/unlock), 2x LEDs (Port C, Pin 0 = Red / alert, Pin 1 = Green / access granted)

## Project Structure

The project follows a layered driver architecture:

```
UTILS_LIB/   BIT_MATH.h, STD_TYPES.h              Bit manipulation & standard type macros
MCAL/        DIO, PWM1, TWI, EEPROM                Microcontroller Abstraction Layer (register-level drivers)
HAL/         LED, KPD, LCD, SRVM, BUZZER            Hardware Abstraction Layer (device drivers)
App/         main.c                                 Application entry point / state machine
             SmartHomeAutomationSystem.c/.h          Application module (login/password logic)
```

Each driver module (e.g. `DIO`, `PWM1`, `KPD`, `LCD`, `SRVM`) follows a consistent 3-file pattern:
- `*_interface.h` – public API exposed to other layers
- `*_private.h` – register addresses / internal definitions
- `*_config.h` – user-configurable options
- `*_program.c` – implementation

## Application Flow (`main.c`)

1. **Init:** Initializes keypad, LCD, servo, and both status LEDs.
2. **Username entry:** Reads keypresses into a 40-byte buffer until `#` is pressed or the buffer limit is reached; null-terminates the string.
3. **Password loop (up to `NUMBER_OF_TRIALS` = 3 attempts):**
   - Reads a 4-digit password from the keypad, masking input on the LCD with `*`.
   - Compares it against the stored password.
   - **On match:** Displays "Access Granted", turns on the green LED, opens the servo (180°) for 5 seconds, then returns it to the closed position (90°).
   - **On mismatch:** Displays remaining trials and clears the input buffer for a retry.
4. **Lockout:** If all trials are exhausted, displays "SECURITY ALERT!" and lights the red LED for 5 seconds.
5. The system waits 10 seconds, then loops back to the password prompt.

## Configuration

Defined at the top of `main.c`:

| Macro | Value | Description |
|---|---|---|
| `PASSWORD_SIZE` | `4` | Number of digits in the password |
| `ADMIN_PASSWORD` | `{'7','0','8','6'}` | Reserved admin password (currently unused in `main.c`) |
| `PRE_PASSWORD` | `{'7','0','8','5'}` | Password checked against user input |
| `NUMBER_OF_TRIALS` | `3` | Allowed password attempts before lockout |

## Building

This is an Atmel Studio / Microchip Studio AVR-GCC project (`.cproj`). To build:

1. Open `SmartHomeAutomationSystem.cproj` in Atmel Studio / Microchip Studio.
2. Ensure the target device and clock frequency match your hardware (`F_CPU`, MCU part).
3. Build the solution (`F7` or Build → Build Solution).
4. Flash the resulting `.hex` file to the target AVR using your programmer of choice (e.g. AVRISP, USBasp).

## Known Notes / Possible Improvements

- `ADMIN_PASSWORD` is defined but never used — only `PRE_PASSWORD` is checked.
- `LoginInfo.User_id` is captured but never validated or used to differentiate users.
- `SmartHomeAutomationSystem.c/.h` declare `SHAS_voidLogin()` / `SHAS_voidCheckPass()`, but the current login/password logic lives directly in `main.c` rather than in these module functions — refactoring the logic into `SmartHomeAutomationSystem.c` would better match the intended module structure.
- No debounce logic is shown beyond fixed `_delay_ms()` calls between keypad reads.
