# LPC2129-Based-Calculator
This project simulates a calculator using LPC2129 ARM7 microcontroller. Input expression comes from UART and output is displayed on LCD and UART

## Features
- Supports +, -, *, / operations with precedence  
- Input via UART terminal  
- Output on 16×2 LCD (4-bit mode) and UART  
- Works on Keil + Proteus simulation

## Hardware / Pins (Proteus setup)
- MCU: LPC2138 / LPC2129  
- UART0: P0.0 (Tx), P0.1 (Rx)  
- LCD data: P0.20–P0.23, RS/RW/EN as per schematic  
- LEDs: if used (optional)  

## Build Instructions
1. Open Keil project  
2. Compile → generate `.hex`  

## Simulation (Proteus)
1. Load `.hex` in MCU  
2. Add Virtual Terminal (9600-8-N-1)  
3. Connect MCU TX→Terminal RX, Rx→Tx  
4. Run Simulation  

