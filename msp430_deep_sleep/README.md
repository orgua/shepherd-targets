# MSP430 Deep Sleep

This firmware puts the MCU in the lowest possible sleep state with no extra functionality. LMP4.5 with no SVS should only consume ~45 nA, see infos below.

LPM4: 600nA (SVS), 400nA (no SVS), wakeup time <10us
LPM4.5: 250nA (SVS), 45 nA (no SVS), wakeup time 250us (SVS), 400us (no SVS)

Steps to enter LPMx.5 -> described in slau367p chapter 1.4.3.1
