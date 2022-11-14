4. Go through the `main.c` file and make sure you understand each line. Use **AVR® Instruction Set Manual** from Microchip [Online Technical Documentation](https://onlinedocs.microchip.com/), find the description of instructions used in `mac.S`, and complete the table.

   | **Instruction** | **Operation** | **Description** | **Cycles** |
   | :-- | :-: | :-- | :-: |
   | `add Rd, Rr` |  |  |  |
   | `mul Rd, Rr` |  |  |  |
   | `ret` |  |  |  |

5. Use manual's 16-bit Opcodes and convert used instructions to hexadecimal.

   | **Instruction** | **Binary opcode** | **Hex opcode** | **Compiler Hex opcode** |
   | :-- | :-: | :-- | :-: |
   | `add r24, r0` |  |  |  |
   | `mul r22, r20` |  |  |  |
   | `ret` |  |  |  |

1. Consider a 4-bit shift register whose input (LSB bit) is formed by an XNOR gate with taps [4, 3] and the initial value is 0000 [[5]](https://www.edn.com/tutorial-linear-feedback-shift-registers-lfsrs-part-1/). Explore LFSR algorithm within `lfsr4_fibonacci_asm` assembly function, complete Timer1 overflow handler and generate 4-bit pseudo-random seguences for different Tap positions. How many states are generated for every settings?

   | **Tap position** | **Generated values** | **Length** |
   | :-: | :-- | :-: |
   | 4, 3 |  |  |
   | 4, 2 |  |  |
   | 4, 1 |  |  |

2. (Optional) In `main.c` file, program the C function `uint8_t lfsr4_fibonacci_c(uint8_t value)`, which generates a 4-bit LFSR sequence with a maximum length. In the `.lst` file compare both functions, in assembly and your C-realization. What is the duration of both functions in CPU cycles?

   | **Function** | **Number of instructions** | **Total number of CPU cycles** |
   | :-- | :-: | :-: |
   | `lfsr4_fibonacci_asm` | | |
   | `lfsr4_fibonacci_c` | | |
