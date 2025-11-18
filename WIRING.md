# LED Strip Wiring Guide

## Hardware Components

- **NodeMCU v2** (ESP8266)
- **BTF-LIGHTING 2835SMD WS2811 IC RGB LED Strip**
  - DC24V, 108LED/m, 18Pixels/m
  - 16.4FT length (~90 pixels total)
- **24V Power Supply** (external)

## Wiring Diagram

```
NodeMCU (3.3V/5V)          24V Power Supply
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

## Connection Details

### NodeMCU Connections
- **D4 (GPIO2)** → LED strip Data line
- **GND** → Common ground (shared with 24V power supply)

### LED Strip Connections
- **Data** ← From NodeMCU D4
- **GND** ← From 24V power supply ground
- **V+** ← From 24V power supply positive

## Safety Notes

1. **Never connect 24V to NodeMCU** - The NodeMCU operates at 3.3V/5V. Only the LED strip gets 24V power.

2. **Common ground is required** - The ground connection between NodeMCU and power supply is safe and necessary for proper data signal communication.

3. **Data signal voltage** - NodeMCU outputs 3.3V logic levels. WS2811 chips typically work with 3.3V data signals, but if you experience issues, consider adding a logic level shifter (3.3V → 5V).

4. **Power supply sizing** - Ensure your 24V power supply can handle the current draw:
   - Each pixel can draw up to ~60mA at full white brightness
   - 90 pixels × 60mA = 5.4A maximum
   - Recommended: 24V power supply rated for at least 6-7A

5. **Wire gauge** - Use appropriately sized wires for the 24V power lines:
   - For high current applications, use at least 18-20 AWG wire
   - Keep power wires as short as practical

6. **Capacitor** (optional but recommended) - Add a 1000µF capacitor across the LED strip power lines (V+ and GND) to smooth voltage spikes.

## Configuration Settings

See `src/main.cpp` for current configuration:
- **LED_PIN**: D4 (GPIO2)
- **NUM_LEDS**: 90
- **BRIGHTNESS**: 128 (50% - adjustable 0-255)
