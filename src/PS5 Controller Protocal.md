Copy of deleted topic: https://www.reddit.com/r/gamedev/comments/jumvi5/dualsense_haptics_leds_and_more_hid_output_report/

---

outputReport[0]  = 0x02; // report type

outputReport[1]  = 0xff; // flags determiing what changes this packet will perform
    // 0x01 set the main motors (also requires flag 0x02); setting this by itself will allow rumble to gracefully terminate and then re-enable audio haptics, whereas not setting it will kill the rumble instantly and re-enable audio haptics.
    // 0x02 set the main motors (also requires flag 0x01; without bit 0x01 motors are allowed to time out without re-enabling audio haptics)
    // 0x04 set the right trigger motor
    // 0x08 set the left trigger motor
    // 0x10 modification of audio volume
    // 0x20 toggling of internal speaker while headset is connected
    // 0x40 modification of microphone volume
    // 0x80 toggling of internal mic or external speaker while headset is connected
outputReport[2]  = 0xff; // further flags determining what changes this packet will perform
    // 0x01 toggling microphone LED
    // 0x02 toggling audio/mic mute
    // 0x04 toggling LED strips on the sides of the touchpad
    // 0x08 will actively turn all LEDs off? Convenience flag? (if so, third parties might not support it properly)
    // 0x10 toggling white player indicator LEDs below touchpad
    // 0x20 ???
    // 0x40 adjustment of overall motor/effect power (index 37 - read note on triggers)
    // 0x80 ???

// main motors
outputReport[3]  = 0xff; // right motor 0-255
outputReport[4]  = 0xff; // left motor 0-255

// audio settings requiring volume control flags
outputReport[5]  = 0xff; // audio volume of connected headphones (maxes out at about 0x7f)
outputReport[6]  = 0xff; // volume of internal speaker (0-255) (ties in with index 38?!? PS5 appears to only use the range 0x3d-0x64)
outputReport[7]  = 0xff; // internal microphone volume (not at all linear; 0-255, maxes out at 0x40, all values above are treated like 0x40; 0 is not fully muted, use audio mute flag instead!)
outputReport[8]  = 0x0c; // audio flags (switching between mic settings causes up to 1s of silence)
    // 0x01 = force use of internal controller mic (if neither 0x01 and 0x02 are set, an attached headset will take precedence)
    // 0x02 = force use of mic attached to the controller (headset)
        // 0x04 = pads left channel of external mic (~1/3rd of the volume? maybe the amount can be controlled?)
    // 0x08 = pads left channel of internal mic (~1/3rd of the volume? maybe the amount can be controlled?)
    // 0x10 = disable attached headphones (only if 0x20 to enable internal speakers is provided as well)
    // 0x20 = enable audio on internal speaker (in addition to a connected headset; headset will use a stereo upmix of the left channel, internal speaker will play the right channel)

// audio related LEDs requiring according LED toggle flags
outputReport[9]  = 0x01; // microphone LED (1 = on, 2 = pulsating / neither does affect the mic)

// audio settings requiring mute toggling flags
outputReport[10] = 0x00; // 0x10 microphone mute, 0x40 audio mute

// trigger motors (see below for details)
outputReport[11..21] right trigger effect (mode byte + up to 10 parameters)
outputReport[22..32] left trigger effect (mode byte + up to 10 parameters)

outputReport[33] = 0x00; // value is copied to input report at offset 43
outputReport[34] = 0x00; // value is copied to input report at offset 44
outputReport[35] = 0x00; // value is copied to input report at offset 45
outputReport[36] = 0x00; // value is copied to input report at offset 46

outputReport[37] = 0x00; // (lower nibble: main motor; upper nibble trigger effects) 0x00 to 0x07 - reduce overall power of the respective motors/effects by 12.5% per increment (this does not affect the regular trigger motor settings, just the automatically repeating trigger effects)
outputReport[38] = 0x07; // volume of internal speaker (0-7; ties in with index 6 - the PS5 default for this appears to be 4)

// LED section (requires LED setting flag)
outputReport[39] = 2; // flags 0x01 = set player led brightness (value in index 43), 0x02 = uninterruptable blue LED pulse (action in index 42)
outputReport[42] = 2; // pulse option
        1 = slowly (2s) fade to blue (scheduled to when the regular LED settings are active)
        2 = slowly (2s) fade out (scheduled after fade-in completion) with eventual switch back to configured LED color; only a fade-out can cancel the pulse (neither index 2, 0x08, nor turning this off will cancel it!)
outputReport[43] = 0x02; // 0x00 = high brightness, 0x01 = medium brightness, 0x02 = low brightness (requires flag from index 39)
outputReport[44] = 0x04; // 5 white player indicator LEDs below the touchpad (bitmask 00-1f from left to right with 0x04 being the center LED; bit 0x20 to set the brightness immediately and not fade in;)
outputReport[45] = 0x1f; // Red value of light bars left and right from touchpad
outputReport[46] = 0xff; // Green value of light bars left and right from touchpad
outputReport[47] = 0x1f; // Blue value of light bars left and right from touchpad


Trigger effects:

The mode is the first byte in the 11 byte sequence describing a trigger effect. I am calling the remaining 10 parameters P0 to P9. Not every mode uses all of these. Unused parameters should be set to 0 to remain compatible with potential future firmware changes.

Resistance effects do show an approximately 30 step ramp to fully engage. While changes are usually applied according to the value submitted, changes to the direction the actuator last moved will require 5-7 increments difference for the actuator to actually reverse directions.

For all frequency parameters, keep details of Edit 12 in mind.

Parameters that aren't explicitly mentioned in the mode descriptions have no effect (at least not in the initial controller firmware release).

Mode 0x00:
    Stop the current currently programmed effect but (as opposed to 0x05), do not
    withdraw the actuator. Every unused mode has this effect, but 0x00 is least
    likely to change in the future.

Mode 0x01:
    Uniform resistance with programmable starting position.
    P0: start of resistance (0=released state; 238 fully pressed)
        Trigger input report value range 0-255 corresponds to p0 values 30-172.
    P1: Resistance force (0-255)
        This cannot be used to completely disable the effect as 0 represents a
        low force.

Mode 0x02:
    Resistance section; after overcoming the resistance section, it will be
    re-engaged when reaching the configured resistance start P0.
    P0: resistance starting position (0=released state; 238 fully pressed)
        Trigger input report value 0-255 corresponds to P0 values 30-167.
        If starting position (P0) is higher than the end position (P1), only a
        brief impulse event is observed at P1, which is unaffected by the force
        parameter (P2), but rather by how fast the trigger is pressed.
    P1: resistance end position (0=released state; 238 fully pressed)
        Trigger input report value 0-255 corresponds to p1 values 30-167.
    P2: Resistance force (0-255)

Mode 0x05:
    Used to fully disengage the effect AND withdraw the actuator.

Mode 0x06:
    Vibration after entering high resistance region
    P0: Vibration frequency in Hz (see Edit 12 below)
    P1: Vibration strength (0-63 with 0 being off)
    P2: Effect starting point (0=released; 137=resistance ramp starts at trigger
        value 0xd1 (209). This is also the highest value that still allows the
        vibration section to be reached.
        Trigger value range 0-255 corresponds to 26-168 for resistance.
        With a P2 value of 0, vibration section starts at trigger value of ~0x10.
        At a P2 value of 255 the resistance ramp can still be felt.

Mode 0x21: (work in progress / poorly understood)
    Resistance with slow recovery and optional resistance bumps
    P0: bit 1 = resistance; bit masks used up to 31?
    P1: bit 1 to enable resistance bumps, bit 2 something else (can be combined)
    P2: resistance buildup speed (0=slow; 255=fast)
        Only used when at least two bits are set in P0
    P3: bit 1 adds two additional, smaller bumps before the one at ~80%
    P4: some "snappiness" characteristic in the lower 6 bits, at least when
        everything else is 255.
    P5: bits 1-3 force of resistance bumps (some other bits do also have some
        effect); bits 4-6 changes tactile feel for p1 bit 2

Mode 0x22:
    Resistance section with "snap back"
    P0+P1: Resistance start (lower bit) and snap back point (higher bit),
           These together build one value with the two lower bits of P2
           representing bit 9 and 10 of the value. The two extreme set bits
           define the effect section.
           Bit to trigger value formula: max((x-1)*0x20, 0x10); subtract 0x20 for
           resistance starting point.
           With the highest bit set, no snap back occurs because 0x120 is not
           reachable (not even internally).
    P2: Resistance and snap back force
        6 bit value of which the lower 3 bit represent the snap back force, and
        the higher 3 bit the constant resistance force.

Mode 0x23: (work in progress / poorly understood)
    ???
    P0+P1: two extreme bits for vibration range; two additional bits in p2 = 10
           bit (corresponding bit to trigger formula: max((x-1)*0x20, 0x10))
    P2: 6 bits encoding resistance force (higher 3 bits) and pattern (lower 3
        bits); having trouble to describe the patterns; some are very similar and
        only show marginal timing differences.

Mode 0x25: (work in progress / poorly understood)
    ???
    P0: first effect observed at a value of 12
    P1: ???
    P2: 6 bit strength; lower 3 bit resistance, higher 3 bit bump strength

Mode 0x26: (work in progress / poorly understood)
    ???
    P0: ???
    P1: ???
    P2: ???
    P3: ???
    P4: 4,8,16 combinations for vibration strength
    P5: contains frequency that is pulsed at the p8 frequency
    P6: frequency
    P7: ???
    P8: pulse frequency

Mode 0x27:
    Fixed resistance with vibration section including amplitude cycling.
    P0+P1: Two extreme bits for vibration range (see 0x22 for details.
           Corresponding bit to trigger value formula: max((x-1)*0x20, 0x10)
    P2: Minimum and maximum force amplitudes that are cycled through (6 bits;
        with the higher 3 bit being the minimum and cycle starting value, the
        lower 3 bit the maximum / cycle peak).
        During the wave period (P4) all the power levels (3 bit) from minimum to
        maximum and back to minimum are cycled through for equally long periods.
    P3: Vibration frequency in Hz
    P4: Wave period in 100ms steps
        The wave period position appears to be advanced as soon as the trigger is
        engaged. This means there is little to no control over the timing.

---------------------------------------------------------------------------------

Mode 0xFC, 0xFD, 0xFE:
    These modes do not appear to use parameters and have no traditional effect.
    They behave like a calibration that requires user input to complete (trigger
    must be fully engaged (sometimes multiple times) for the sequence to start).
    Executing them can cause the entire spectrum of modes to misbehave until
    the controller is restarted (led to misidentification of possible modes).

I hope this will save some of you time implementing support for the DualSense controller yourself.
If you have additions regarding the unknown flags/bytes or know what is going on with the oddly split internal speaker volume, be kind and share your findings.
It was annoying enough trying to figure all of this out without having an actual PlayStation or access to one.

NOTE:

The DualSense controller appears to use a fixed 1kHz clock with an integer divisor for the trigger effects.
That's why frequency values have increasingly spotty granularity when exceeding 36Hz.
As an example, these are the values when a switch to the next higher frequency occurs on the upper spectrum:
251 = 333Hz 0.003s, 201 = 250Hz 0.004s, 167 = 200Hz 0.005s, 143 = 166Hz 0.006s;
250Hz is producible, as soon as we give the controller a frequency of 251, the next smaller divisor will be 3, resulting in a reproduced frequency of 333Hz.
For convenience - the values causing changes beyond 36 are as follows: 38, 39, 41, 42, 44, 46, 48, 51, 53, 56, 59, 63, 67, 72, 77, 84, 91, 101, 112, 126, 143, 167, 201, 251

---
