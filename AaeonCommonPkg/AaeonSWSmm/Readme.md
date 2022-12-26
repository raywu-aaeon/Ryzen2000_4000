# Aaeon SW SMI Simple Template

This module create and register one SwSmi.

## Porting Guide

1. Enable master token in AaeonSWSmm.sdl
2. Set the register number "SwSMI_RegNum" in SDL file , default is 0xAE here
3. Add code to implement in AaeonSwSmiCallback,  default is output 0xAE 80 port

## Validation

* Boot into shell or OS, write registed number (default 0xAE) to IO Port 0xB2, you will see show 0xAE in 80 port, which mean SW SMI is triggered succefully.