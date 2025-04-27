# Bistro 92 Challenge: Smart Ordering System

## Overview

This project simulates a smart ordering device for the Bistro 92 Challenge, using an ESP32, SSD1306 OLED display, and four push buttons. It implements the process flow (menu navigation, item selection, quantity adjustment, order submission, cancellation) with an enhanced cart display feature.

## Circuit Design

- **Components**:
  - ESP32 DevKit V1
  - SSD1306 OLED Display (128x64, I2C)
  - 4x Push Buttons:
    - Button 1: Menu/Reset (GPIO 4)
    - Button 2: Select/Submit (GPIO 5)
    - Button 3: Scroll Up/Increment (GPIO 18)
    - Button 4: Scroll Down/Decrement (GPIO 19)
- **Connections**:
  - OLED: VCC to 3.3V, GND to GND, SDA to GPIO 21, SCL to GPIO 22
  - Buttons: Each to respective GPIO and GND
- **Diagram**: [bistro-92circuit.png]()

## Code

- **File**: [sketch.ino]()
- **Libraries**: `Wire`, `Adafruit_GFX`, `Adafruit_SSD1306`
- **Features**:
  - Menu navigation with scrolling (Buttons 3/4).
  - Item selection and quantity adjustment (Button 2, Buttons 3/4).
  - Cart tracking and order submission via serial output (Button 2 long press).
  - Order cancellation (Button 1).
  - **Cart Display**: Shows cart contents (e.g., “Cart: Burger x2, Pizza x1”) or “Cart: Empty” at the bottom of the OLED, with truncation for long strings.
- **Testing**:
  - Verified all process flow steps (menu access, navigation, selection, quantity, submission, cancellation).
  - Tested cart display for empty carts, single/multiple items, long strings, and reset/submission.
  - Edge cases: empty cart submission, quantity < 1, rapid button presses.

## Wokwi Simulation

- **Link**: [Insert Wokwi URL here]
- Run the simulation to test the system.

## Video Demo

- **Link**: [Insert Google Drive link here]
- Shows the circuit, button interactions, OLED output (menu, quantity, cart display, confirmations), and serial monitor (order submissions).

## Notes

- **Cloud Integration**: Simulated via serial output (e.g., “Order Submitted: Table 1, Burger x2, Pizza x1”).
- **User-Friendly Interface**: Enhanced with cart display, highlighted menu items (text size 2), and clear feedback messages.
- **Enhancements**: Cart display truncates long strings to fit the 128x64 OLED, improving user feedback.

## Quick Fixes

- **Q1**: Essential features:
  1. User-friendly interface with menu and cart display on OLED.
  2. Real-time order tracking via serial output.
  3. Robust navigation with debouncing.
- **Q2**: Design principles:
  1. Minimalistic UI: Simple menu with cart feedback.
  2. Clear feedback: Visual confirmations for cart additions and orders.

## Big Idea

- **Problem**: Customers may be indecisive about menu choices.
- **Solution**: AI-driven menu recommendations displayed on the OLED, suggesting popular items based on order history (e.g., “Popular: Burger”).
- **Tech**: Cloud-based ML model to analyze orders, integrated via API.

## Submission

Submitted for the Bistro 92 Challenge, Dept. of Mechatronics & Industrial Engineering, CUET.
