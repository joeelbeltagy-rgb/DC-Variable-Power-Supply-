# Variable DC Power Supply — Arduino + OLED + Custom Enclosure

A fully hand-built **variable DC power supply** that converts 220V AC mains into a smooth, adjustable DC output — controlled by an Arduino, displayed on an OLED screen, and housed in a custom **laser-engraved wooden enclosure**.

> **Course:** Power Electronics — Helwan National University, Robotics & Mechatronics Dept.  
> **By:** Yousef Ahmed Elbeltagy

---

## Photos

| | |
|:---:|:---:|
| ![Builder with Device](docs/photos/builder_with_device.jpeg) | ![Enclosure Design](docs/photos/enclosure_design.jpeg) |
| *Yousef with the finished build* | *Laser-engraved front panel — robot mascot + circuit schematic* |

| | |
|:---:|:---:|
| ![Front Panel](docs/photos/front_panel.jpeg) | ![Top View](docs/photos/top_view.jpeg) |
| *Front panel — OLED display, rotary knob, output terminals* | *Top panel — "DC POWER SUPPLY" laser engraving* |

![Internal Components](docs/photos/internal_components.jpeg)
*Inside the box — transformer, PCB, Arduino UNO, OLED module, and filter capacitors*

![LCD Display](docs/photos/lcd_display.webp)
*LCD showing real-time Duty Cycle (99%) and output Voltage (23.76V)*

---

## Circuit Schematic

![Circuit Schematic](docs/schematic/circuit_schematic.webp)

*Full Proteus simulation schematic — 220V AC source → transformer → bridge rectifier → filter capacitors → MOSFET (IRF740) → output stage, with Arduino UNO + TLP350 optocoupler gate driver*

---

## How It Works

The power supply follows the classic **AC → DC conversion pipeline**, enhanced with Arduino-based digital control:

```
220V AC Mains
     │
     ▼
[Step-Down Transformer]  →  24V AC
     │
     ▼
[Bridge Rectifier + Filter Capacitors]  →  Pulsating DC → Smoothed DC
     │
     ▼
[Voltage Regulator / Potentiometer]  →  Variable DC Output
     │
     ▼
[Arduino UNO]  →  Reads output voltage via ADC
     │
     ▼
[OLED Display]  →  Shows real-time voltage value
     │
     ▼
[Output Terminals]  →  Red (+) / Black (−) alligator clips
```

---

## Key Features

| Feature | Detail |
|---|---|
| **Input** | 220V AC mains |
| **Transformer** | EL-NEKHELY 220V → 24V step-down |
| **Rectification** | Full-wave bridge rectifier |
| **Filtering** | Electrolytic capacitors for ripple reduction |
| **Voltage Control** | Rotary potentiometer — smooth manual adjustment |
| **Microcontroller** | Arduino UNO — ADC voltage sensing |
| **Display** | OLED screen — real-time voltage readout |
| **Enclosure** | Custom laser-cut & engraved wooden box |
| **Output** | Variable DC via red/black alligator clip terminals |

---

## Components Used

| Component | Purpose |
|---|---|
| EL-NEKHELY Transformer (220V/24V) | Steps down mains voltage |
| Bridge Rectifier (diodes) | Converts AC to pulsating DC |
| Electrolytic Capacitors | Filters and smooths DC output |
| Rotary Potentiometer | Manual voltage adjustment |
| Arduino UNO | Voltage sensing + display control |
| OLED Display Module | Real-time voltage display |
| Custom PCB (perfboard) | Houses rectifier + filter circuit |
| Laser-cut Wooden Box | Custom enclosure with engraved design |
| Red/Black Alligator Clips | Output terminals |

---

## Enclosure Design

The enclosure was designed and laser-cut from wood with:
- **Side panel** — laser-engraved robot mascot + resistor-capacitor circuit schematic
- **Top panel** — "DC POWER SUPPLY" engraving
- **Front panel** — OLED display window + rotary knob cutout + output terminal holes
- **Finger-joint construction** — precise interlocking edges for a clean fit

---

## Arduino Code

The Arduino reads the potentiometer, drives a **PWM signal via Timer1 at ~31.25 kHz** (eliminates audible switching noise), and displays both duty cycle and output voltage on the LCD in real time.

| LCD Line | Displays | Example |
|---|---|---|
| Line 1 | Duty cycle % | `Duty: 99%` |
| Line 2 | Output voltage | `Volt: 23.76V` |

Full source: [`src/power_supply.ino`](src/power_supply.ino)

**Dependencies:**
- `LiquidCrystal_I2C` — I²C LCD driver (install via Arduino Library Manager)

---

## Project Structure

```
DC-Variable-Power-Supply/
├── src/
│   └── power_supply.ino                # Arduino source code
├── docs/
│   ├── photos/
│   │   ├── builder_with_device.jpeg    # Yousef holding the finished build
│   │   ├── enclosure_design.jpeg       # Laser-engraved front panel
│   │   ├── front_panel.jpeg            # OLED + knob + terminals
│   │   ├── top_view.jpeg               # Top panel engraving
│   │   ├── internal_components.jpeg   # Inside: PCB, Arduino, transformer
│   │   └── lcd_display.webp            # LCD showing Duty% and Voltage
│   ├── schematic/
│   │   └── circuit_schematic.webp      # Full Proteus circuit schematic
│   └── report/
│       └── DC_Power_Supply_Report.pdf  # Full project report
├── simulation/
│   └── power_circuit.pdsprj            # Proteus simulation project file
├── .gitignore
└── README.md
```

---

## Documentation

[`docs/report/DC_Power_Supply_Report.pdf`](docs/report/DC_Power_Supply_Report.pdf) — full project report covering circuit design, component selection, calculations, and results.
