# Graduation Project — Smart Home System

## Full Project Documentation

**Target MCU:** ATmega32 (AVR)  
**Toolchain:** AVR GCC (Atmel Studio / Microchip Studio)  
**CPU Frequency:** 16 MHz (`F_CPU 16000000UL`)

---

## 1. Project Overview

This is an **embedded Smart Home System** that provides:

- **Dual interface:** local **keypad + LCD** and remote **UART terminal**
- **Role-based access:** Admin (terminal) and User (keypad or terminal)
- **Device control:** 5 lamps (L1–L5), 1 dimmer lamp, door (servo), AC (DC motor)
- **Temperature monitoring:** LM35 on ADC, automatic AC on/off by thresholds
- **User management:** credentials stored in EEPROM; admin can add/remove users and permit/block keypad user
- **Security:** login with ID + 4-digit password; 3 failed attempts trigger alarm (WDT reset)

---

## 2. Architecture (Layered)

```
┌─────────────────────────────────────────────────────────────────┐
│  Entry Point                                                     │
│  main.c  (init + loop only — no logic)                          │
├─────────────────────────────────────────────────────────────────┤
│  Application Layer                                               │
│  AppManager | UIManager |                                        │
│  Login | DeviceControl | TempManager | CommHandler | AlarmManager │
├─────────────────────────────────────────────────────────────────┤
│  HAL (Hardware Abstraction Layer)                                │
│  LCD | KPD | LED | SRV (Servo) | DCM (DC Motor) | SWITCH          │
├─────────────────────────────────────────────────────────────────┤
│  MCAL (Microcontroller Abstraction Layer)                         │
│  DIO | UART | TWI | EEPROM | ADC | PWM (TMR0/TMR1) | WDT | ...   │
├─────────────────────────────────────────────────────────────────┤
│  Utils: STD_TYPES.h, BIT_MATH.h                                   │
└─────────────────────────────────────────────────────────────────┘
```

- **Entry Point (`main.c`):** 26-line file — calls `App_voidInit()` once and `App_voidRun()` in a loop. No logic.
- **Application:** `AppManager` (state machine, keypad dispatch), `UIManager` (LCD rendering), plus Login, DeviceControl, TempManager, CommHandler, AlarmManager.
- **HAL:** drivers for LCD, keypad, LEDs, servo, DC motor (and switch if used).
- **MCAL:** direct register-level drivers for GPIO, UART, I2C/TWI, EEPROM, ADC, timers, WDT.

---

## 3. Directory Structure

```
Graduation-Project/
├── main.c                          # Entry point only: App_voidInit() + loop{App_voidRun()}
├── Application/
│   ├── AppManager/                 # State machine, keypad dispatch, background tasks
│   │   ├── AppManager_interface.h
│   │   └── AppManager_program.c
│   ├── UIManager/                  # All LCD screen rendering functions
│   │   ├── UIManager_interface.h
│   │   └── UIManager_program.c
│   ├── Login/                      # Authentication (EEPROM, admin/user roles)
│   ├── DeviceControl/              # Lamps, dimmer, door, AC
│   ├── TemperatureManager/         # LM35, thresholds, auto AC
│   ├── CommunicationHandler/       # UART terminal, commands, permit/block
│   └── AlarmManager/               # Failed-login alarm, WDT reset
├── HAL/
│   ├── LCD/                        # 4-bit HD44780 LCD
│   ├── KPD/                        # 3x3 matrix keypad
│   ├── LED/                        # Generic LED on/off
│   ├── SRV/                        # Servo (TMR1 PWM)
│   ├── DCM/                        # DC motor (L298 or similar, 2 channels)
│   └── SWITCH/                     # Push-button switch
├── MCAL/
│   ├── DIO/                        # Digital I/O
│   ├── UART/                       # Serial 9600 baud
│   ├── TWI/                        # I2C (for EEPROM)
│   ├── EEPROM/                     # External EEPROM over TWI
│   ├── ADC/                        # Analog (LM35)
│   ├── PWM/                        # TMR0PWM (dimmer), TMR1PWM (servo)
│   ├── TMR0/, TMR1/                # Timer drivers
│   ├── WDT/                        # Watchdog (alarm reset)
│   ├── EXTI/, GI/, SPI/, SWICU/    # Optional / future use
│   └── ...
├── Utils/
│   ├── STD_TYPES.h                 # u8, u16, u32, bool_t, NULL
│   └── BIT_MATH.h                  # SET_BIT, CLR_BIT, GET_BIT, TOG_BIT
└── System_Documentation/           # PlantUML diagrams and visual docs
    ├── README.md
    ├── architecture.puml
    ├── state_machine.puml
    └── login_sequence.puml
```

---

## 4. Application Layer (Detailed)

### 4.1 Main (`main.c`)

- **Role:** Entry point only — 26 lines total.
- **Responsibilities:** None beyond calling `App_voidInit()` once and `App_voidRun()` in an infinite loop.
- **Contains NO:** state variables, display logic, keypad handling, hardware access, or business logic.
- **Depends on:** `Application/AppManager/AppManager_interface.h` only.

---

### 4.2 Login (`Application/Login`)

**Purpose:** Authenticate users from keypad or UART; store admin + up to 5 users in EEPROM.

**Roles:**

- `LOGIN_ADMIN_ROLE` (1) — only via terminal; can add/remove users, permit/block keypad user.
- `LOGIN_USER_ROLE` (2) — keypad or terminal; control devices (subject to permit/block).
- `LOGIN_NO_ROLE` (0) — not authenticated.

**Channels:** `LOGIN_CH_KPD` (0), `LOGIN_CH_TERMINAL` (1).

**EEPROM layout:**

- Admin: start address `0x00`, 6 bytes: status(1) + ID(1) + password(4). Default admin ID `'1'`, password `"1234"` if not already set.
- Users: start `0x10`, each entry 6 bytes (status + ID + 4-byte password), `MAX_USERS = 5`.

**API (`Login_interface.h`):**

| Function                                             | Description                                                                      |
| ---------------------------------------------------- | -------------------------------------------------------------------------------- |
| `Login_voidInit(void)`                               | TWI + EEPROM init; create default admin if none                                  |
| `Login_u8Authenticate(channel, userID, password[4])` | Returns role or `LOGIN_NO_ROLE`; increments failed attempts, triggers alarm at 3 |
| `Login_voidRegisterUser(userID, password[4])`        | Add user in first free slot (admin only, via CommHandler)                        |
| `Login_voidRemoveUser(userID)`                       | Deactivate user entry (admin only)                                               |
| `Login_u8GetUser(index, *id)`                        | Get user ID by index; returns 1 if valid                                         |
| `Login_u8GetFailedAttempts(void)`                    | Current failed login count                                                       |
| `Login_u8CheckID(id)`                                | Returns 1 if ID exists (admin or user)                                           |

---

### 4.3 Device Control (`Application/DeviceControl`)

**Purpose:** Abstract control of lamps, dimmer, door (servo), and AC (DC motor).

**Device IDs:** `LAMP1`..`LAMP5` (1..5), `DIMMER_LAMP` (6).  
**States:** `LAMP_ON`/`LAMP_OFF`, `DOOR_OPEN`/`DOOR_CLOSE`, `AC_ON`/`AC_OFF`.

**Hardware mapping:**

- L1: Port B, Pin 0
- L2: Port B, Pin 4
- L3: Port B, Pin 5
- L4: Port B, Pin 6
- L5: Port B, Pin 7
- Dimmer: Timer0 PWM (OC0), Port B Pin 3
- Door: Servo (TMR1 PWM), Port D Pin 5
- AC: DC motor channel A (DCM), see DCM_config (e.g. Port C IN1/IN2/ENA)

**API (`DeviceControl_interface.h`):**

| Function                                        | Description                                          |
| ----------------------------------------------- | ---------------------------------------------------- |
| `Device_voidInit(void)`                         | Init LEDs, dimmer PWM, servo, DC motor               |
| `Device_voidSetLamp(lampID, state, brightness)` | For L1–L5: on/off; for DIMMER_LAMP: brightness 0–255 |
| `Device_voidSetDoor(state)`                     | DOOR_OPEN → 180°, DOOR_CLOSE → 90°                   |
| `Device_voidSetAC(state)`                       | AC on (CW) or off                                    |
| `Device_u8GetACStatus(void)`                    | Returns AC_ON or AC_OFF                              |

---

### 4.4 Temperature Manager (`Application/TemperatureManager`)

**Purpose:** Read LM35 on ADC channel 0; auto turn AC on above 28°C, off below 21°C.

**Formula:** `Temp = (ADC_value * 500) / 1024` (AVcc ref, LM35 10 mV/°C).

**API (`TempManager_interface.h`):**

| Function                       | Description                                       |
| ------------------------------ | ------------------------------------------------- |
| `Temp_voidInit(void)`          | ADC init (AVcc reference)                         |
| `Temp_u16GetCurrentTemp(void)` | Current temperature in °C (integer)               |
| `Temp_voidManage(void)`        | Called in main loop; sets AC on/off by thresholds |

---

### 4.5 Communication Handler (`Application/CommunicationHandler`)

**Purpose:** UART terminal at 9600 baud; login (ID + 4-digit password), menu, and device commands.

**Terminal states:** `TERM_UNAUTHENTICATED`, `TERM_WAITING_ID`, `TERM_WAITING_PASS`, `TERM_AUTHENTICATED`, `TERM_WAITING_ADD_ID`, `TERM_WAITING_ADD_PASS`, `TERM_WAITING_REMOVE_ID`.

**Behavior:**

- Admin login via terminal: keypad user is initially **blocked** until admin chooses "permit user".
- Commands: `show commands` / `1`, `logout` / `7`; admin: `add user`/`2`, `remove user`/`3`, `permit user`/`4`, `block user`/`5`, `list users`/`6`.
- Device: `L1_ON`, `L1_OFF`, … `L5_OFF`; `DOOR_OPEN`, `DOOR_CLOSE` (admin only); `DIM_XXX` (0–100).

**API (`CommHandler_interface.h`):**

| Function                          | Description                                                |
| --------------------------------- | ---------------------------------------------------------- |
| `Comm_voidInit(void)`             | UART init; prompt "Please enter ID: "                      |
| `Comm_voidSendMessage(msg)`       | Send string over UART                                      |
| `Comm_voidManage(void)`           | Non-blocking UART read; parse lines and run commands       |
| `Comm_u8IsKpdUserPermitted(void)` | 1 if keypad user may control (no admin or admin permitted) |
| `Comm_u8GetTerminalRole(void)`    | Current terminal role                                      |
| `Comm_voidSetKpdStatus(status)`   | Notify that keypad user logged in (1) or out (0)           |

---

### 4.6 Alarm Manager (`Application/AlarmManager`)

**Purpose:** On 3 failed login attempts, show "ALARM SYSTEM / TRIGGERED!" on LCD and enable WDT with 2 s timeout to reset MCU.

**API (`AlarmManager_interface.h`):**

| Function                  | Description                                               |
| ------------------------- | --------------------------------------------------------- |
| `Alarm_voidInit(void)`    | Disable WDT                                               |
| `Alarm_voidTrigger(void)` | Display message, enable WDT_2S, infinite loop until reset |

---

### 4.7 App Manager (`Application/AppManager`)

**Purpose:** Owns the top-level application state machine and keypad input dispatch. This is the only module that knows about `AppState_t` and transitions between screens.

**State Machine:**

| State              | Description                                              |
| ------------------ | -------------------------------------------------------- |
| `APP_STATE_IDLE`   | Transient startup-only state                             |
| `APP_STATE_WAIT_ID`   | Awaiting single keypad press for user ID              |
| `APP_STATE_WAIT_PASS` | Collecting 4-digit password (masked as `*`)           |
| `APP_STATE_MAIN_MENU` | Main menu: Status / Options / Logout                  |
| `APP_STATE_STATUS`    | Live temperature and AC status screen                 |
| `APP_STATE_OPTIONS`   | Device carousel (L1–L5, Dimmer)                       |
| `APP_STATE_DIMMER_CTRL` | Dimmer brightness selection (0/25/50/75/100%)       |

**Constants:**

| Constant              | Value  | Purpose                          |
| --------------------- | ------ | -------------------------------- |
| `MAX_OPTIONS`         | 6      | Number of items in device list   |
| `PASSWORD_LENGTH`     | 4      | Digits per password              |
| `DEBOUNCE_MS`         | 250 ms | Keypad software debounce delay   |
| `STARTUP_BANNER_MS`   | 500 ms | Welcome screen display time      |
| `MSG_SHORT_MS`        | 500 ms | Duration for short flash messages|
| `MSG_LONG_MS`         | 1000 ms| Duration for error flash messages|

**API (`AppManager_interface.h`):**

| Function           | Description                                                    |
| ------------------ | -------------------------------------------------------------- |
| `App_voidInit()`   | Init all HW and app modules, display banner, set WAIT_ID state |
| `App_voidRun()`    | One iteration of: background tasks + status refresh + keypad   |

**Private Handlers (static, not in interface):**

| Handler                    | State handled           |
| -------------------------- | ----------------------- |
| `App_HandleWaitID(key)`    | `APP_STATE_WAIT_ID`     |
| `App_HandleWaitPass(key)`  | `APP_STATE_WAIT_PASS`   |
| `App_HandleMainMenu(key)`  | `APP_STATE_MAIN_MENU`   |
| `App_HandleStatus(key)`    | `APP_STATE_STATUS`      |
| `App_HandleOptions(key)`   | `APP_STATE_OPTIONS`     |
| `App_HandleDimmerCtrl(key)`| `APP_STATE_DIMMER_CTRL` |

---

### 4.8 UI Manager (`Application/UIManager`)

**Purpose:** Owns all LCD screen-rendering functions. The **only** Application-layer module (apart from `AlarmManager`'s single alarm output) that calls `LCD_*` HAL APIs. Provides a clean boundary so no other Application module ever formats strings or positions the cursor directly.

**API (`UIManager_interface.h`):**

| Function                                       | Description                                                      |
| ---------------------------------------------- | ---------------------------------------------------------------- |
| `UI_voidDisplayMainMenu(void)`                  | Renders the 3-choice main menu                                   |
| `UI_voidDisplayStatus(void)`                    | Full redraw of temp/AC status screen; caches values              |
| `UI_voidRefreshStatus(void)`                    | In-place update of changed values only (no full clear)           |
| `UI_voidDisplayOptions(u8 optionIdx)`           | Renders device carousel screen for given index                   |
| `UI_voidDisplayDimmerCtrl(void)`                | Renders dimmer brightness selection screen                       |
| `UI_voidShowMessage(const u8* msg, u16 delayMs)` | Clears LCD, shows message, blocks for `delayMs` milliseconds    |

**Private State:**
- `g_u16LastTemp` / `g_u8LastACState` — cached values enabling `UI_voidRefreshStatus()` to detect changes without a full redraw.

---

## 5. HAL (Hardware Abstraction Layer)

### 5.1 LCD (`HAL/LCD`)

- **Mode:** 4-bit (`LCD_MODE = 4`).
- **Pins:** RS (Port B, Pin 1), E (Port B, Pin 2); D4–D7 (Port A, Pins 4–7).
- **API:** `LCD_voidInit`, `LCD_voidDisplayChar`, `LCD_voidDisplayString`, `LCD_voidDisplayNumber(u8 copy_u8Number)`, `LCD_voidSendCommand`, `LCD_voidClear`, `LCD_voidShift(direction)`, `LCD_voidGoToStartPosition`, `LCD_voidGoToSpecificPosition(line, pos)`. 
- **Macros:** Lines: `LCD_LINE_ONE`, `LCD_LINE_TWO`. Shift Directions: `LCD_SHIFT_LEFT`, `LCD_SHIFT_RIGHT`.

### 5.2 Keypad (`HAL/KPD`)

- **Matrix:** 3 rows × 3 columns. Rows: Port A Pins 1–3; Columns: Port D Pins 2, 3, 7.
- **Key map:** `{{'1','2','3'},{'4','5','6'},{'7','8','c'}}`. No '9'; in main, keys '1'–'6', '4'/'6' for navigation.
- **API:** `KPD_voidInit`, `KPD_voidGetValue(*key)`. Returns `KPD_NOT_PRESSED` (0xFF) when no key.

### 5.3 LED (`HAL/LED`)

- **API:** `LED_voidInit(port, pin)`, `LED_voidOn(port, pin, connection)`, `LED_voidOff(port, pin, connection)`, `LED_voidToggle(port, pin)`. Connection: `LED_FORWARD_CONNECTION` or `LED_REVERSE_CONNECTION`.

### 5.4 Servo (`HAL/SRV`)

- **Output:** Port D, Pin 5 (OC1A); TMR1 PWM, 50 Hz, duty 5%–10% for 0°–180° (e.g. 7.5% for 90°).
- **API:** `SRV_voidInit`, `SRV_voidOn(angle)`, `SRV_voidOff()`.

### 5.5 DC Motor (`HAL/DCM`)

- **Channel A (AC):** IN1 (Port C Pin 3), IN2 (Port C Pin 4), ENA (Port C Pin 5). Direction: `DCM_CW`, `DCM_CCW`.
- **Channel B:** IN3/IN4 (Port C Pins 5/6), ENB (Port D Pin 4) — configured but AC uses only channel A.
- **API (Standard):** `DCM_voidInit(channel)`, `DCM_voidOn(direction, channel)`, `DCM_voidOff(channel)`.
- **API (PWM Speed Control):** `DCM_voidInitWithCtrlSpeed(channel)`, `DCM_voidOnWithCtrlSpeed(direction, speed, channel)`, `DCM_voidOffWithCtrlSpeed(channel)`.

### 5.6 SWITCH (`HAL/SWITCH`)

- Interface present; used if any physical switch is connected; not required for core keypad/UART flow.

---

## 6. MCAL (Microcontroller Abstraction Layer)

### 6.1 DIO (`MCAL/DIO`)

- Ports: `DIO_PORTA`..`DIO_PORTD`; Pins: `DIO_PIN0`..`DIO_PIN7`; Direction: `DIO_PIN_INPUT`/`DIO_PIN_OUTPUT`; Value: `DIO_PIN_LOW`/`DIO_PIN_HIGH`.
- **API:** `DIO_voidSetPinDirection`, `DIO_voidSetPinValue`, `DIO_voidTogglePinValue`, `DIO_u8GetPinValue`, `DIO_voidGetPinValue`, `DIO_voidActivePinInternalPUR`; port equivalents.

### 6.2 UART (`MCAL/UART`)

- **Baud:** 9600 (`UBRR = 103` at 16 MHz).
- **API:** `UART_voidInit`, `UART_voidTxChar`, `UART_voidRxChar`, `UART_voidTxString`, `UART_voidRxString`, `UART_u8RecieveByteNonBlocking`.

### 6.3 TWI (`MCAL/TWI`)

- I2C for EEPROM. **API:** Master: `TWI_voidInitMaster`, `TWI_voidSendStartCond`, `TWI_voidSendRepStartCond`, `TWI_voidSendStopCond`, `TWI_voidSendSlaveAddW/R`, `TWI_voidTxMasterByte`, `TWI_voidRxMasterByteACK/NACK`. Slave APIs available.

### 6.4 EEPROM (`MCAL/EEPROM`)

- **API:** `EEPROM_voidInit`, `EEPROM_voidWriteByte(addr, data)`, `EEPROM_voidReadByte(addr, *data)`, `EEPROM_voidWritePage`, `EEPROM_voidReadPage`.

### 6.5 ADC (`MCAL/ADC`)

- **Reference:** `ADC_REFERENCE_AVCC` (used for LM35). **Channels:** `ADC_CHANNEL_0`..`ADC_CHANNEL_7`.
- **API:** `ADC_voidInit(reference)`, `ADC_voidGetDigitalValue(channel, *value)`.

### 6.6 PWM

- **TMR0 PWM (files `MCAL/PWM/TMR0PWM_*`):** Used for dimmer (OC0). Prescalers: `NO_CLK_SRC`, `NO_PRESCALING`, `_8FROM_PRESCALER`, `_64FROM_PRESCALER`, etc. **API:** `TMR0PWM_voidInit`, `TMR0PWM_voidGenerate(duty 0–255, prescaler)`, `TMR0PWM_voidStop`.
- **TMR1 PWM (files `MCAL/PWM/TMR1PWM_*`):** Used for servo. **API:** `TMR1PWM_voidInit`, `TMR1PWM_voidGenerate(freq, dutyPercent, prescaler)`, `TMR1PWM_voidStop`.

### 6.7 WDT (`MCAL/WDT`)

- **Timeouts:** e.g. `WDT_TIMEOUT_16MS` … `WDT_TIMEOUT_2S`. **API:** `WDT_voidEnable(prescale)`, `WDT_voidDisable`. Alarm uses `WDT_TIMEOUT_2S`.

---

## 7. Utils

- **STD_TYPES.h:** `u8`, `s8`, `u16`, `s16`, `u32`, `s32`, `f32`, `f64`, `bool_t` (FALSE/TRUE), `NULL`.
- **BIT_MATH.h:** `SET_BIT(REG, BIT_NUM)`, `CLR_BIT(REG, BIT_NUM)`, `GET_BIT(REG, BIT_NUM)`, `TOG_BIT(REG, BIT_NUM)`.

---

## 8. Keypad Menu (Local LCD)

| State       | Keys / Action                                                                                                            |
| ----------- | ------------------------------------------------------------------------------------------------------------------------ |
| Wait ID     | Single key = user ID; then "Pass: "                                                                                      |
| Wait Pass   | 4 keys = password; then login or "Login Failed!"                                                                         |
| Main Menu   | 1 = Status, 2 = Options, 3 = Logout                                                                                      |
| Status      | Live temp & AC; 3 = Back, 1 = Refresh                                                                                    |
| Options     | L1..L5, Dim; 4/6 = prev/next; 2 = On or Set dimmer, 3 = Off; 1 = Back. Dimmer: 2–6 = 0%, 25%, 50%, 75%, 100%; 1 = Return |
| Permissions | If keypad user blocked by admin: "Blocked By Admin" on device/dimmer action                                              |

---

## 9. UART Terminal Commands

- **Login:** Enter 1-byte ID, then 4-character password. Admin only via terminal.
- **Menu (admin):** 1 show commands, 2 add user, 3 remove user, 4 permit user, 5 block user, 6 list users, 7 logout.
- **Device:** `L1_ON`, `L1_OFF`, … `L5_OFF`; `DOOR_OPEN`, `DOOR_CLOSE` (admin); `DIM_0`..`DIM_100`.

---

## 10. Build and Flash

- **IDE:** Atmel Studio / Microchip Studio with AVR GCC; device **ATmega32**.
- **Config:** Debug/Release; include paths for Application, HAL, MCAL, Utils; `libm` linked (servo float math).
- **Output:** `.elf`, `.hex`, `.eep`, `.lss`, `.srec` in `Debug/` or `Release/`.
- **Flash:** Upload `.hex` via programmer (e.g. USBasp, Atmel-ICE). EEPROM can be preserved (`preserveEEPROM`).

---

## 11. Default Credentials and EEPROM

- **Admin:** ID `'1'` (0x31), password `"1234"` — created on first run if EEPROM admin slot not set.
- **Users:** Up to 5; added by admin via terminal "add user".

---

## 12. Summary

The project is a **strictly layered AVR application** following modular embedded C architecture:

- **Entry Point (`main.c`):** 26-line file that wires the system together. Contains zero business logic.
- **AppManager:** Owns the 7-state FSM and all keypad dispatch. Every state transition lives in one isolated handler function.
- **UIManager:** Owns all LCD rendering. No other Application module formats strings or positions the cursor — a clean rendering boundary.
- **Domain Modules:** Login, DeviceControl, TempManager, CommHandler, AlarmManager each own one concern and expose a prefix-named API.
- **HAL:** LCD, KPD, LED, Servo, DCM — hardware-level abstractions, no business logic.
- **MCAL:** DIO, UART, TWI, EEPROM, ADC, PWM, WDT — direct register-level drivers.

Two interfaces (keypad+LCD and UART terminal) share the same device control and user database. The admin can restrict the keypad user via terminal in real-time. Temperature drives AC automatically. Three consecutive failed logins trigger the alarm which enables the WDT for a full MCU reset.

---

_End of documentation._
