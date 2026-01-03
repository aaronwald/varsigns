# LED Strip Wiring Guide

## Hardware Components

- **NodeMCU v2** (ESP8266)
- **BTF-LIGHTING 2835SMD WS2811 IC RGB LED Strip**
  - DC24V, 108LED/m, 18Pixels/m
  - 16.4FT length (~90 pixels total)
- **24V Power Supply** (external)

## Wiring Options

### Option 1: Separate Power Supplies (Simple)

```
NodeMCU (USB powered)      24V Power Supply
┌─────────────┐            ┌──────────────┐
│             │            │              │
│  D4 (GPIO2) ├────────────┼──→ Data      │
│             │            │              │
│     GND     ├────────────┼──→ GND ──────┼──→ LED Strip GND
│             │            │              │
└─────────────┘            │   24V ───────┼──→ LED Strip V+
                           │              │
                           └──────────────┘
```

### Option 2: Single Power Supply with Buck Converter (Recommended)

```
                           24V Power Supply
                           ┌──────────────┐
                           │   24V+  GND  │
                           └───┬──────┬───┘
                               │      │
                    ┌──────────┴──┐   │
                    │             │   │
                ┌───┤ Buck Conv.  │   │
                │   │ 24V→5V      │   │
                │   │  (LM2596)   ├───┤
                │   └─────────────┘   │
                │   5V            GND │
                │   │              │  │
                │   │              │  │
           ┌────┴───┴──┐           │  │
           │    VIN    │           │  │
NodeMCU    │           │           │  │
┌──────────┤    GND    ├───────────┴──┤
│          └───────────┘              │
│                                     │
│  D4 (GPIO2) ────────────────────────┼──→ LED Strip Data
│                                     │
│     GND     ────────────────────────┼──→ LED Strip GND
│                                     │
└─────────────────────────────────────┘
                                      │
                            24V ──────┼──→ LED Strip V+
                                      │
```

### Option 3: With Logic Level Shifter (BEST for 24V LED Strips)

```
                           24V Power Supply
                           ┌──────────────┐
                           │   24V+  GND  │
                           └───┬──────┬───┘
                               │      │
                    ┌──────────┴──┐   │
                    │             │   │
                ┌───┤ Buck Conv.  │   │
                │   │ 24V→5V      │   │
                │   │  (LM2596)   ├───┤
                │   └─────────────┘   │
                │   5V            GND │
                │   │              │  │
           ┌────┴───┴──┐           │  │
           │    VIN    │           │  │
NodeMCU    │   3.3V    │           │  │
┌──────────┤    GND    ├───────────┴──┼──────┐
│          └───────────┘              │      │
│                                     │      │
│              ┌───────────────┐      │      │
│    3.3V ─────┤ VCCA     VCCB ├──────┘      │
│              │               │   5V        │
│    GND ──────┤ GND       GND ├─────────────┤
│              │   TXB0104     │             │
│  D4 ─────────┤ A1         B1 ├─────────────┼──→ LED Strip Data
│              │               │             │
│              └───────────────┘             │
│                                            │
└────────────────────────────────────────────┼──→ LED Strip GND
                                             │
                               24V ──────────┼──→ LED Strip V+
                                             │
```

## Connection Details

### Option 1: Separate Power Supplies
**NodeMCU Connections:**
- **D4 (GPIO2)** → LED strip Data line
- **GND** → Common ground (shared with 24V power supply)
- **USB** → 5V power from computer or USB power adapter

**LED Strip Connections:**
- **Data** ← From NodeMCU D4
- **GND** ← From 24V power supply ground (shared with NodeMCU)
- **V+** ← From 24V power supply positive

### Option 2: Buck Converter Setup (Recommended)
**Buck Converter Connections:**
- **IN+** ← 24V power supply positive
- **IN-** ← 24V power supply ground
- **OUT+** → NodeMCU VIN pin (5V)
- **OUT-** → NodeMCU GND pin
- **Adjust trim pot** to output exactly 5.0V (verify with multimeter before connecting NodeMCU)

**NodeMCU Connections:**
- **VIN** ← 5V from buck converter output
- **GND** ← Buck converter ground (common ground)
- **D4 (GPIO2)** → LED strip Data line

**LED Strip Connections:**
- **Data** ← From NodeMCU D4
- **GND** ← From 24V power supply ground (common ground)
- **V+** ← From 24V power supply positive (24V)

**Recommended Buck Converter:**
- LM2596-based DC-DC step-down module
- Input: 24V, Output: 5V (adjustable)
- Current rating: 2-3A minimum

### Option 3: With TXB0104 Logic Level Shifter

**TXB0104 Level Shifter Connections:**
- **VCCA** ← 3.3V from NodeMCU
- **VCCB** ← 5V from NodeMCU VIN or buck converter
- **GND** ← Common ground (shared with NodeMCU and power supply)
- **A1** ← NodeMCU D4 (GPIO2) - 3.3V side
- **B1** → LED strip Data line - 5V side
- **A2, A3, A4** ← Leave unconnected (not needed)

**NodeMCU Connections:**
- **VIN** ← 5V from buck converter or USB
- **3.3V** → TXB0104 VCCA
- **GND** ← Common ground
- **D4 (GPIO2)** → TXB0104 A1 input

**LED Strip Connections:**
- **Data** ← From TXB0104 B1 output
- **GND** ← Common ground
- **V+** ← 24V from power supply

**Note:** The TXB0104 is bidirectional and auto-detects signal direction. You only need one of its 4 channels for the data line.

## Safety Notes

1. **Never connect 24V directly to NodeMCU** - The NodeMCU operates at 3.3V/5V. Only the LED strip gets 24V power. If using a buck converter, always verify the output voltage is 5V before connecting to the NodeMCU.

2. **Buck converter setup (if using Option 2)**:
   - **CRITICAL**: Adjust the buck converter output to exactly 5.0V using a multimeter BEFORE connecting the NodeMCU
   - Turn the trim pot clockwise to increase voltage, counter-clockwise to decrease
   - Connect a dummy load (resistor) or leave unloaded while adjusting
   - Acceptable range: 4.8V - 5.2V (ideal: 5.0V)
   - Exceeding 5.5V may damage the NodeMCU

3. **Common ground is required** - The ground connection between NodeMCU and power supply is safe and necessary for proper data signal communication.

4. **Logic Level Shifter REQUIRED** - The NodeMCU outputs 3.3V logic levels, but the WS2811 running on 24V needs a clean 5V data signal for reliable operation. Without a level shifter, you may experience incorrect colors (especially on the first LED) or intermittent issues.
   - **Recommended**: 74HCT245 or similar 3.3V→5V logic level shifter
   - **Alternative**: SN74AHCT125N single-gate buffer
   - Connect: NodeMCU D4 → Level Shifter Input, Level Shifter Output → LED Data, 5V → Shifter VCC
   - The 5V can come from NodeMCU VIN or a separate 5V source

5. **Power supply sizing** - Ensure your 24V power supply can handle the current draw:
   - Each pixel can draw up to ~60mA at full white brightness
   - 90 pixels × 60mA = 5.4A maximum
   - Recommended: 24V power supply rated for at least 6-7A
   - Add ~0.5A headroom if using buck converter for NodeMCU

6. **Wire gauge** - Use appropriately sized wires for the 24V power lines:
   - For high current applications, use at least 18-20 AWG wire
   - Keep power wires as short as practical

7. **Capacitor** (optional but recommended) - Add a 1000µF capacitor across the LED strip power lines (V+ and GND) to smooth voltage spikes.

## Configuration Settings

See `src/main.cpp` for current configuration:
- **LED_PIN**: D4 (GPIO2)
- **NUM_LEDS**: 90
- **BRIGHTNESS**: 128 (50% - adjustable 0-255)
