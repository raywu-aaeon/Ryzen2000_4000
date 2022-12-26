
# AAEON Running Time

This module count and show running hour in setup main page

## Module Detail

* Register power button and S5 SMI to count running Time
* Add a setup call back to show running time in BIOS main page
* Add a DXE driver to process running Time variable

## Disclaimer

* System time set to earlier than year 2017 will be treated as invalid time, and will not be counted for running time.
* CMOS battery loss or set to default will reset the running time.
* Running time will not count up when S5 and G3 state
* Running time will count up when abnormally AC loss, since BIOS has no way to know when AC is losing.
