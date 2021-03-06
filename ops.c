#include "ops.h"

const unsigned char instruction_ticks[256] = {
        2, 6, 4, 4, 2, 2, 4, 4, 10, 4, 4, 4, 2, 2, 4, 4, // 0x0_
        2, 6, 4, 4, 2, 2, 4, 4,  4, 4, 4, 4, 2, 2, 4, 4, // 0x1_
        0, 6, 4, 4, 2, 2, 4, 2,  0, 4, 4, 4, 2, 2, 4, 2, // 0x2_
        4, 6, 4, 4, 6, 6, 6, 2,  0, 4, 4, 4, 2, 2, 4, 2, // 0x3_
        2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0x4_
        2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0x5_
        2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0x6_
        4, 4, 4, 4, 4, 4, 2, 4,  2, 2, 2, 2, 2, 2, 4, 2, // 0x7_
        2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0x8_
        2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0x9_
        2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0xa_
        2, 2, 2, 2, 2, 2, 4, 2,  2, 2, 2, 2, 2, 2, 4, 2, // 0xb_
        0, 6, 0, 6, 0, 8, 4, 8,  0, 2, 0, 0, 0, 6, 4, 8, // 0xc_
        0, 6, 0, 0, 0, 8, 4, 8,  0, 8, 0, 0, 0, 0, 4, 8, // 0xd_
        6, 6, 4, 0, 0, 8, 4, 8,  8, 2, 8, 0, 0, 0, 4, 8, // 0xe_
        6, 6, 4, 2, 0, 8, 4, 8,  6, 4, 8, 2, 0, 0, 4, 8  // 0xf_
};

const struct instruction instructions[256] = {
	{ "NOP", 0, nop },                           // 0x00
	{ "LD BC, 0x%04X", 2, ld_bc_nn },            // 0x01
	{ "LD (BC), A", 0, ld_bcp_a },               // 0x02
	{ "INC BC", 0, inc_bc },                     // 0x03
	{ "INC B", 0, inc_b },                       // 0x04
	{ "DEC B", 0, dec_b },                       // 0x05
	{ "LD B, 0x%02X", 1, ld_b_n },               // 0x06
	{ "RLCA", 0, rlca },                         // 0x07
	{ "LD (0x%04X), SP", 2, ld_nnp_sp },         // 0x08
	{ "ADD HL, BC", 0, add_hl_bc },              // 0x09
	{ "LD A, (BC)", 0, ld_a_bcp },               // 0x0a
	{ "DEC BC", 0, dec_bc },                     // 0x0b
	{ "INC C", 0, inc_c },                       // 0x0c
	{ "DEC C", 0, dec_c },                       // 0x0d
	{ "LD C, 0x%02X", 1, ld_c_n },               // 0x0e
	{ "RRCA", 0, rrca },                         // 0x0f
	{ "STOP", 1, stop },                         // 0x10
	{ "LD DE, 0x%04X", 2, ld_de_nn },            // 0x11
	{ "LD (DE), A", 0, ld_dep_a },               // 0x12
	{ "INC DE", 0, inc_de },                     // 0x13
	{ "INC D", 0, inc_d },                       // 0x14
	{ "DEC D", 0, dec_d },                       // 0x15
	{ "LD D, 0x%02X", 1, ld_d_n },               // 0x16
	{ "RLA", 0, rla },                           // 0x17
	{ "JR 0x%02X", 1, jr_n },                    // 0x18
	{ "ADD HL, DE", 0, add_hl_de },              // 0x19
	{ "LD A, (DE)", 0, ld_a_dep },               // 0x1a
	{ "DEC DE", 0, dec_de },                     // 0x1b
	{ "INC E", 0, inc_e },                       // 0x1c
	{ "DEC E", 0, dec_e },                       // 0x1d
	{ "LD E, 0x%02X", 1, ld_e_n },               // 0x1e
	{ "RRA", 0, rra },                           // 0x1f
	{ "JR NZ, 0x%02X", 1, jr_nz_n },             // 0x20
	{ "LD HL, 0x%04X", 2, ld_hl_nn },            // 0x21
	{ "LDI (HL), A", 0, ldi_hlp_a },             // 0x22
	{ "INC HL", 0, inc_hl },                     // 0x23
	{ "INC H", 0, inc_h },                       // 0x24
	{ "DEC H", 0, dec_h },                       // 0x25
	{ "LD H, 0x%02X", 1, ld_h_n },               // 0x26
	{ "DAA", 0, daa },                           // 0x27
	{ "JR Z, 0x%02X", 1, jr_z_n },               // 0x28
	{ "ADD HL, HL", 0, add_hl_hl },              // 0x29
	{ "LDI A, (HL)", 0, ldi_a_hlp },             // 0x2a
	{ "DEC HL", 0, dec_hl },                     // 0x2b
	{ "INC L", 0, inc_l },                       // 0x2c
	{ "DEC L", 0, dec_l },                       // 0x2d
	{ "LD L, 0x%02X", 1, ld_l_n },               // 0x2e
	{ "CPL", 0, cpl },                           // 0x2f
	{ "JR NC, 0x%02X", 1, jr_nc_n },             // 0x30
	{ "LD SP, 0x%04X", 2, ld_sp_nn },            // 0x31
	{ "LDD (HL), A", 0, ldd_hlp_a },             // 0x32
	{ "INC SP", 0, inc_sp },                     // 0x33
	{ "INC (HL)", 0, inc_hlp },                  // 0x34
	{ "DEC (HL)", 0, dec_hlp },                  // 0x35
	{ "LD (HL), 0x%02X", 1, ld_hlp_n },          // 0x36
	{ "SCF", 0, scf },                           // 0x37
	{ "JR C, 0x%02X", 1, jr_c_n },               // 0x38
	{ "ADD HL, SP", 0, add_hl_sp },              // 0x39
	{ "LDD A, (HL)", 0, ldd_a_hlp },             // 0x3a
	{ "DEC SP", 0, dec_sp },                     // 0x3b
	{ "INC A", 0, inc_a },                       // 0x3c
	{ "DEC A", 0, dec_a },                       // 0x3d
	{ "LD A, 0x%02X", 1, ld_a_n },               // 0x3e
	{ "CCF", 0, ccf },                           // 0x3f
	{ "LD B, B", 0, nop },                       // 0x40
	{ "LD B, C", 0, ld_b_c },                    // 0x41
	{ "LD B, D", 0, ld_b_d },                    // 0x42
	{ "LD B, E", 0, ld_b_e },                    // 0x43
	{ "LD B, H", 0, ld_b_h },                    // 0x44
	{ "LD B, L", 0, ld_b_l },                    // 0x45
	{ "LD B, (HL)", 0, ld_b_hlp },               // 0x46
	{ "LD B, A", 0, ld_b_a },                    // 0x47
	{ "LD C, B", 0, ld_c_b },                    // 0x48
	{ "LD C, C", 0, nop },                       // 0x49
	{ "LD C, D", 0, ld_c_d },                    // 0x4a
	{ "LD C, E", 0, ld_c_e },                    // 0x4b
	{ "LD C, H", 0, ld_c_h },                    // 0x4c
	{ "LD C, L", 0, ld_c_l },                    // 0x4d
	{ "LD C, (HL)", 0, ld_c_hlp },               // 0x4e
	{ "LD C, A", 0, ld_c_a },                    // 0x4f
	{ "LD D, B", 0, ld_d_b },                    // 0x50
	{ "LD D, C", 0, ld_d_c },                    // 0x51
	{ "LD D, D", 0, nop },                       // 0x52
	{ "LD D, E", 0, ld_d_e },                    // 0x53
	{ "LD D, H", 0, ld_d_h },                    // 0x54
	{ "LD D, L", 0, ld_d_l },                    // 0x55
	{ "LD D, (HL)", 0, ld_d_hlp },               // 0x56
	{ "LD D, A", 0, ld_d_a },                    // 0x57
	{ "LD E, B", 0, ld_e_b },                    // 0x58
	{ "LD E, C", 0, ld_e_c },                    // 0x59
	{ "LD E, D", 0, ld_e_d },                    // 0x5a
	{ "LD E, E", 0, nop },                       // 0x5b
	{ "LD E, H", 0, ld_e_h },                    // 0x5c
	{ "LD E, L", 0, ld_e_l },                    // 0x5d
	{ "LD E, (HL)", 0, ld_e_hlp },               // 0x5e
	{ "LD E, A", 0, ld_e_a },                    // 0x5f
	{ "LD H, B", 0, ld_h_b },                    // 0x60
	{ "LD H, C", 0, ld_h_c },                    // 0x61
	{ "LD H, D", 0, ld_h_d },                    // 0x62
	{ "LD H, E", 0, ld_h_e },                    // 0x63
	{ "LD H, H", 0, nop },                       // 0x64
	{ "LD H, L", 0, ld_h_l },                    // 0x65
	{ "LD H, (HL)", 0, ld_h_hlp },               // 0x66
	{ "LD H, A", 0, ld_h_a },                    // 0x67
	{ "LD L, B", 0, ld_l_b },                    // 0x68
	{ "LD L, C", 0, ld_l_c },                    // 0x69
	{ "LD L, D", 0, ld_l_d },                    // 0x6a
	{ "LD L, E", 0, ld_l_e },                    // 0x6b
	{ "LD L, H", 0, ld_l_h },                    // 0x6c
	{ "LD L, L", 0, nop },                       // 0x6d
	{ "LD L, (HL)", 0, ld_l_hlp },               // 0x6e
	{ "LD L, A", 0, ld_l_a },                    // 0x6f
	{ "LD (HL), B", 0, ld_hlp_b },               // 0x70
	{ "LD (HL), C", 0, ld_hlp_c },               // 0x71
	{ "LD (HL), D", 0, ld_hlp_d },               // 0x72
	{ "LD (HL), E", 0, ld_hlp_e },               // 0x73
	{ "LD (HL), H", 0, ld_hlp_h },               // 0x74
	{ "LD (HL), L", 0, ld_hlp_l },               // 0x75
	{ "HALT", 0, halt },                         // 0x76
	{ "LD (HL), A", 0, ld_hlp_a },               // 0x77
	{ "LD A, B", 0, ld_a_b },                    // 0x78
	{ "LD A, C", 0, ld_a_c },                    // 0x79
	{ "LD A, D", 0, ld_a_d },                    // 0x7a
	{ "LD A, E", 0, ld_a_e },                    // 0x7b
	{ "LD A, H", 0, ld_a_h },                    // 0x7c
	{ "LD A, L", 0, ld_a_l },                    // 0x7d
	{ "LD A, (HL)", 0, ld_a_hlp },               // 0x7e
	{ "LD A, A", 0, nop },                       // 0x7f
	{ "ADD A, B", 0, add_a_b },                  // 0x80
	{ "ADD A, C", 0, add_a_c },                  // 0x81
	{ "ADD A, D", 0, add_a_d },                  // 0x82
	{ "ADD A, E", 0, add_a_e },                  // 0x83
	{ "ADD A, H", 0, add_a_h },                  // 0x84
	{ "ADD A, L", 0, add_a_l },                  // 0x85
	{ "ADD A, (HL)", 0, add_a_hlp },             // 0x86
	{ "ADD A", 0, add_a_a },                     // 0x87
	{ "ADC B", 0, adc_b },                       // 0x88
	{ "ADC C", 0, adc_c },                       // 0x89
	{ "ADC D", 0, adc_d },                       // 0x8a
	{ "ADC E", 0, adc_e },                       // 0x8b
	{ "ADC H", 0, adc_h },                       // 0x8c
	{ "ADC L", 0, adc_l },                       // 0x8d
	{ "ADC (HL)", 0, adc_hlp },                  // 0x8e
	{ "ADC A", 0, adc_a },                       // 0x8f
	{ "SUB B", 0, sub_b },                       // 0x90
	{ "SUB C", 0, sub_c },                       // 0x91
	{ "SUB D", 0, sub_d },                       // 0x92
	{ "SUB E", 0, sub_e },                       // 0x93
	{ "SUB H", 0, sub_h },                       // 0x94
	{ "SUB L", 0, sub_l },                       // 0x95
	{ "SUB (HL)", 0, sub_hlp },                  // 0x96
	{ "SUB A", 0, sub_a },                       // 0x97
	{ "SBC B", 0, sbc_b },                       // 0x98
	{ "SBC C", 0, sbc_c },                       // 0x99
	{ "SBC D", 0, sbc_d },                       // 0x9a
	{ "SBC E", 0, sbc_e },                       // 0x9b
	{ "SBC H", 0, sbc_h },                       // 0x9c
	{ "SBC L", 0, sbc_l },                       // 0x9d
	{ "SBC (HL)", 0, sbc_hlp },                  // 0x9e
	{ "SBC A", 0, sbc_a },                       // 0x9f
	{ "AND B", 0, and_b },                       // 0xa0
	{ "AND C", 0, and_c },                       // 0xa1
	{ "AND D", 0, and_d },                       // 0xa2
	{ "AND E", 0, and_e },                       // 0xa3
	{ "AND H", 0, and_h },                       // 0xa4
	{ "AND L", 0, and_l },                       // 0xa5
	{ "AND (HL)", 0, and_hlp },                  // 0xa6
	{ "AND A", 0, and_a },                       // 0xa7
	{ "XOR B", 0, xor_b },                       // 0xa8
	{ "XOR C", 0, xor_c },                       // 0xa9
	{ "XOR D", 0, xor_d },                       // 0xaa
	{ "XOR E", 0, xor_e },                       // 0xab
	{ "XOR H", 0, xor_h },                       // 0xac
	{ "XOR L", 0, xor_l },                       // 0xad
	{ "XOR (HL)", 0, xor_hlp },                  // 0xae
	{ "XOR A", 0, xor_a },                       // 0xaf
	{ "OR B", 0, or_b },                         // 0xb0
	{ "OR C", 0, or_c },                         // 0xb1
	{ "OR D", 0, or_d },                         // 0xb2
	{ "OR E", 0, or_e },                         // 0xb3
	{ "OR H", 0, or_h },                         // 0xb4
	{ "OR L", 0, or_l },                         // 0xb5
	{ "OR (HL)", 0, or_hlp },                    // 0xb6
	{ "OR A", 0, or_a },                         // 0xb7
	{ "CP B", 0, cp_b },                         // 0xb8
	{ "CP C", 0, cp_c },                         // 0xb9
	{ "CP D", 0, cp_d },                         // 0xba
	{ "CP E", 0, cp_e },                         // 0xbb
	{ "CP H", 0, cp_h },                         // 0xbc
	{ "CP L", 0, cp_l },                         // 0xbd
	{ "CP (HL)", 0, cp_hlp },                    // 0xbe
	{ "CP A", 0, cp_a },                         // 0xbf
	{ "RET NZ", 0, ret_nz },                     // 0xc0
	{ "POP BC", 0, pop_bc },                     // 0xc1
	{ "JP NZ, 0x%04X", 2, jp_nz_nn },            // 0xc2
	{ "JP 0x%04X", 2, jp_nn },                   // 0xc3
	{ "CALL NZ, 0x%04X", 2, call_nz_nn },        // 0xc4
	{ "PUSH BC", 0, push_bc },                   // 0xc5
	{ "ADD A, 0x%02X", 1, add_a_n },             // 0xc6
	{ "RST 0x00", 0, rst_0 },                    // 0xc7
	{ "RET Z", 0, ret_z },                       // 0xc8
	{ "RET", 0, ret },                           // 0xc9
	{ "JP Z, 0x%04X", 2, jp_z_nn },              // 0xca
	//{ "CB %02X", 1, cb_n },                      // 0xcb
	{ "CALL Z, 0x%04X", 2, call_z_nn },          // 0xcc
	{ "CALL 0x%04X", 2, call_nn },               // 0xcd
	{ "ADC 0x%02X", 1, adc_n },                  // 0xce
	{ "RST 0x08", 0, rst_08 },                   // 0xcf
	{ "RET NC", 0, ret_nc },                     // 0xd0
	{ "POP DE", 0, pop_de },                     // 0xd1
	{ "JP NC, 0x%04X", 2, jp_nc_nn },            // 0xd2
	{ "UNKNOWN", 0, undefined },                 // 0xd3
	{ "CALL NC, 0x%04X", 2, call_nc_nn },        // 0xd4
	{ "PUSH DE", 0, push_de },                   // 0xd5
	{ "SUB 0x%02X", 1, sub_n },                  // 0xd6
	{ "RST 0x10", 0, rst_10 },                   // 0xd7
	{ "RET C", 0, ret_c },                       // 0xd8
	//{ "RETI", 0, return_from_interrupt },        // 0xd9
	{ "JP C, 0x%04X", 2, jp_c_nn },              // 0xda
	{ "UNKNOWN", 0, undefined },                 // 0xdb
	{ "CALL C, 0x%04X", 2, call_c_nn },          // 0xdc
	{ "UNKNOWN", 0, undefined },                 // 0xdd
	{ "SBC 0x%02X", 1, sbc_n },                  // 0xde
	{ "RST 0x18", 0, rst_18 },                   // 0xdf
	{ "LD (0xFF00 + 0x%02X), A", 1, ld_ff_n_ap },// 0xe0
	{ "POP HL", 0, pop_hl },                     // 0xe1
	{ "LD (0xFF00 + C), A", 0, ld_ff_c_a },      // 0xe2
	{ "UNKNOWN", 0, undefined },                 // 0xe3
	{ "UNKNOWN", 0, undefined },                 // 0xe4
	{ "PUSH HL", 0, push_hl },                   // 0xe5
	{ "AND 0x%02X", 1, and_n },                  // 0xe6
	{ "RST 0x20", 0, rst_20 },                   // 0xe7
	{ "ADD SP,0x%02X", 1, add_sp_n },            // 0xe8
	{ "JP HL", 0, jp_hl },                       // 0xe9
	{ "LD (0x%04X), A", 2, ld_nnp_a },           // 0xea
	{ "UNKNOWN", 0, undefined },                 // 0xeb
	{ "UNKNOWN", 0, undefined },                 // 0xec
	{ "UNKNOWN", 0, undefined },                 // 0xed
	{ "XOR 0x%02X", 1, xor_n },                  // 0xee
	{ "RST 0x28", 0, rst_28 },                   // 0xef
	{ "LD A, (0xFF00 + 0x%02X)", 1, ld_ff_ap_n },// 0xf0
	{ "POP AF", 0, pop_af },                     // 0xf1
	{ "LD A, (0xFF00 + C)", 0, ld_a_ff_c },      // 0xf2
	{ "DI", 0, di_inst },                        // 0xf3
	{ "UNKNOWN", 0, undefined },                 // 0xf4
	{ "PUSH AF", 0, push_af },                   // 0xf5
	{ "OR 0x%02X", 1, or_n },                    // 0xf6
	{ "RST 0x30", 0, rst_30 },                   // 0xf7
	{ "LD HL, SP+0x%02X", 1, ld_hl_sp_n },       // 0xf8
	{ "LD SP, HL", 0, ld_sp_hl },                // 0xf9
	{ "LD A, (0x%04X)", 2, ld_a_nnp },           // 0xfa
	{ "EI", 0, ei },                             // 0xfb
	{ "UNKNOWN", 0, undefined },                 // 0xfc
	{ "UNKNOWN", 0, undefined },                 // 0xfd
	{ "CP 0x%02X", 1, cp_n },                    // 0xfe
	{ "RST 0x38", 0, rst_38 }                   // 0xff
};


void undefined(z80_t * z80){}
void nop(z80_t * z80){}// 0x00
void ld_bc_nn(z80_t * z80, uint16_t operand){
	z80->registers[REG_B] = (operand & 0xff00) >> 8;
	z80->registers[REG_C] = (operand & 0x00ff);
}// 0x01
void ld_bcp_a(z80_t * z80){
	write_8bit_z80(z80, (z80->registers[REG_B] << 8) + z80->registers[REG_C], z80->registers[REG_A]);
}// 0x02
void inc_bc(z80_t * z80){}// 0x03
void inc_b(z80_t * z80){}// 0x04
void dec_b(z80_t * z80){}// 0x05
void ld_b_n(z80_t * z80, unsigned char operand){
	z80->registers[REG_B] = operand;
}// 0x06
void rlca(z80_t * z80){}// 0x07
void ld_nnp_sp(z80_t * z80, uint16_t operand){
	write_16bit_z80(z80, operand, z80->sp);
}// 0x08
void add_hl_bc(z80_t * z80){}// 0x09
void ld_a_bcp(z80_t * z80){
	z80->registers[REG_A] = read_8bit_z80( z80, (z80->registers[REG_B] << 8) + z80->registers[REG_C] );
}// 0x0a
void dec_bc(z80_t * z80){}// 0x0b
void inc_c(z80_t * z80){}// 0x0c
void dec_c(z80_t * z80){}// 0x0d
void ld_c_n(z80_t * z80, unsigned char operand){
	z80->registers[REG_C] = operand;
}// 0x0e
void rrca(z80_t * z80){}// 0x0f
void stop(z80_t * z80, unsigned char operand){}// 0x10
void ld_de_nn(z80_t * z80, uint16_t operand){
	z80->registers[REG_D] = (operand & 0xff00) >> 8;
	z80->registers[REG_E] = (operand & 0x00ff);
}// 0x11
void ld_dep_a(z80_t * z80){
	write_8bit_z80(z80, (z80->registers[REG_D] << 8) + z80->registers[REG_E], z80->registers[REG_A]);
}// 0x12
void inc_de(z80_t * z80){}
void inc_d(z80_t * z80){}
void dec_d(z80_t * z80){}
void ld_d_n(z80_t * z80, unsigned char operand){
	z80->registers[REG_D] = operand;
}// 0x16
void rla(z80_t * z80){}
void jr_n(z80_t * z80, unsigned char operand){}
void add_hl_de(z80_t * z80){}
void ld_a_dep(z80_t * z80){
	z80->registers[REG_A] = read_8bit_z80( z80, (z80->registers[REG_D] << 8) + z80->registers[REG_E] );
}// 0x1a
void dec_de(z80_t * z80){}
void inc_e(z80_t * z80){}
void dec_e(z80_t * z80){}
void ld_e_n(z80_t * z80, unsigned char operand){
	z80->registers[REG_E] = operand;
}// 0x1e
void rra(z80_t * z80){}
void jr_nz_n(z80_t * z80, unsigned char operand){}
void ld_hl_nn(z80_t * z80, uint16_t operand){
	z80->registers[REG_H] = (operand & 0xff00) >> 8;
	z80->registers[REG_L] = (operand & 0x00ff);
}// 0x21
void ldi_hlp_a(z80_t * z80){
	uint16_t address;
	address = (z80->registers[REG_H] << 8) + z80->registers[REG_L];
	write_8bit_z80(z80, address, z80->registers[REG_A]);
	address++;
	z80->registers[REG_H] = (address & 0xff00) >> 8;
	z80->registers[REG_L] = (address & 0x00ff);
}// 0x22
void inc_hl(z80_t * z80){}// 0x23
void inc_h(z80_t * z80){}// 0x24
void dec_h(z80_t * z80){}// 0x25
void ld_h_n(z80_t * z80, unsigned char operand){
	z80->registers[REG_H] = operand;
}// 0x26
void daa(z80_t * z80){}// 0x27
void jr_z_n(z80_t * z80, unsigned char operand){}// 0x28
void add_hl_hl(z80_t * z80){}// 0x29
void ldi_a_hlp(z80_t * z80){
	uint16_t address;
	address = (z80->registers[REG_H] << 8) + z80->registers[REG_L];
	z80->registers[REG_A] = read_8bit_z80(z80, address);
	address++;
	z80->registers[REG_H] = (address & 0xff00) >> 8;
	z80->registers[REG_L] = (address & 0x00ff);
}// 0x2a
void dec_hl(z80_t * z80){}
void inc_l(z80_t * z80){}
void dec_l(z80_t * z80){}
void ld_l_n(z80_t * z80, unsigned char operand){
	z80->registers[REG_L] = operand;
}// 0x2e
void cpl(z80_t * z80){}
void jr_nc_n(char operand){}// 0x30
void ld_sp_nn(z80_t * z80, uint16_t operand){
	z80->sp = operand;
}// 0x31
void ldd_hlp_a(z80_t * z80){
	uint16_t address;
	address = (z80->registers[REG_H] << 8) + z80->registers[REG_L];
	write_8bit_z80(z80, address, z80->registers[REG_A]);
	address--;
	z80->registers[REG_H] = (address & 0xff00) >> 8;
	z80->registers[REG_L] = (address & 0x00ff);
}// 0x32
void inc_sp(z80_t * z80){}
void inc_hlp(z80_t * z80){}
void dec_hlp(z80_t * z80){}
void ld_hlp_n(z80_t * z80, unsigned char operand){
	write_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L], operand);
}// 0x36
void scf(z80_t * z80){}
void jr_c_n(char operand){}
void add_hl_sp(z80_t * z80){}
void ldd_a_hlp(z80_t * z80){
	uint16_t address;
	address = (z80->registers[REG_H] << 8) + z80->registers[REG_L];
	z80->registers[REG_A] = read_8bit_z80(z80, address);
	address--;
	z80->registers[REG_H] = (address & 0xff00) >> 8;
	z80->registers[REG_L] = (address & 0x00ff);
}// 0x3a
void dec_sp(z80_t * z80){}
void inc_a(z80_t * z80){}
void dec_a(z80_t * z80){}
void ld_a_n(z80_t * z80, unsigned char operand){
	z80->registers[REG_A] = operand;
}// 0x3e
void ccf(z80_t * z80){}
void ld_b_c(z80_t * z80){
	z80->registers[REG_B] = z80->registers[REG_C];
}// 0x41
void ld_b_d(z80_t * z80){
	z80->registers[REG_B] = z80->registers[REG_D];
}// 0x42
void ld_b_e(z80_t * z80){
	z80->registers[REG_B] = z80->registers[REG_E];
}// 0x43
void ld_b_h(z80_t * z80){
	z80->registers[REG_B] = z80->registers[REG_H];
}// 0x44
void ld_b_l(z80_t * z80){
	z80->registers[REG_B] = z80->registers[REG_L];
}// 0x45
void ld_b_hlp(z80_t * z80){
	z80->registers[REG_B] = read_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L]);
}// 0x46
void ld_b_a(z80_t * z80){
	z80->registers[REG_B] = z80->registers[REG_A];
}// 0x47
void ld_c_b(z80_t * z80){
	z80->registers[REG_C] = z80->registers[REG_B];
}// 0x48
void ld_c_d(z80_t * z80){
	z80->registers[REG_C] = z80->registers[REG_D];
}// 0x4a
void ld_c_e(z80_t * z80){
	z80->registers[REG_C] = z80->registers[REG_E];
}// 0x4b
void ld_c_h(z80_t * z80){ 
	z80->registers[REG_C] = z80->registers[REG_H];
}// 0x4c
void ld_c_l(z80_t * z80){
	z80->registers[REG_C] = z80->registers[REG_L];
}// 0x4d
void ld_c_hlp(z80_t * z80){	
	z80->registers[REG_C] = read_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L]);
}// 0x4e
void ld_c_a(z80_t * z80){
	z80->registers[REG_C] = z80->registers[REG_A];
}// 0x4f
void ld_d_b(z80_t * z80){
	z80->registers[REG_D] = z80->registers[REG_B];
}// 0x50
void ld_d_c(z80_t * z80){
	z80->registers[REG_D] = z80->registers[REG_C];
}// 0x51
void ld_d_e(z80_t * z80){
	z80->registers[REG_D] = z80->registers[REG_E];
}// 0x53
void ld_d_h(z80_t * z80){
	z80->registers[REG_D] = z80->registers[REG_H];
}// 0x54
void ld_d_l(z80_t * z80){
	z80->registers[REG_D] = z80->registers[REG_L];
}// 0x55
void ld_d_hlp(z80_t * z80){	
	z80->registers[REG_D] = read_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L]);
}// 0x56
void ld_d_a(z80_t * z80){
	z80->registers[REG_D] = z80->registers[REG_A];
}// 0x57
void ld_e_b(z80_t * z80){
	z80->registers[REG_E] = z80->registers[REG_B];
}// 0x58
void ld_e_c(z80_t * z80){
	z80->registers[REG_E] = z80->registers[REG_C];
}// 0x59
void ld_e_d(z80_t * z80){
	z80->registers[REG_E] = z80->registers[REG_D];
}// 0x5a
void ld_e_h(z80_t * z80){
	z80->registers[REG_E] = z80->registers[REG_H];
}// 0x5c
void ld_e_l(z80_t * z80){
	z80->registers[REG_E] = z80->registers[REG_L];
}// 0x5d
void ld_e_hlp(z80_t * z80){
	z80->registers[REG_E] = read_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L]);
}// 0x5e
void ld_e_a(z80_t * z80){
	z80->registers[REG_E] = z80->registers[REG_A];
}// 0x5f
void ld_h_b(z80_t * z80){
	z80->registers[REG_H] = z80->registers[REG_B];
}// 0x60
void ld_h_c(z80_t * z80){
	z80->registers[REG_H] = z80->registers[REG_C];
}// 0x61
void ld_h_d(z80_t * z80){
	z80->registers[REG_H] = z80->registers[REG_D];
}// 0x62
void ld_h_e(z80_t * z80){
	z80->registers[REG_H] = z80->registers[REG_E];
}// 0x63
void ld_h_l(z80_t * z80){
	z80->registers[REG_H] = z80->registers[REG_L];
}// 0x65
void ld_h_hlp(z80_t * z80){
	z80->registers[REG_H] = read_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L]);
}// 0x66
void ld_h_a(z80_t * z80){
	z80->registers[REG_H] = z80->registers[REG_A];
}// 0x67
void ld_l_b(z80_t * z80){
	z80->registers[REG_L] = z80->registers[REG_B];
}// 0x68
void ld_l_c(z80_t * z80){
	z80->registers[REG_L] = z80->registers[REG_C];
}// 0x69
void ld_l_d(z80_t * z80){
	z80->registers[REG_L] = z80->registers[REG_D];
}// 0x6a
void ld_l_e(z80_t * z80){
	z80->registers[REG_L] = z80->registers[REG_E];
}// 0x6b
void ld_l_h(z80_t * z80){
	z80->registers[REG_L] = z80->registers[REG_H];
}// 0x6c
void ld_l_hlp(z80_t * z80){
	z80->registers[REG_L] = read_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L]);
}// 0x6e
void ld_l_a(z80_t * z80){
	z80->registers[REG_L] = z80->registers[REG_A];
}// 0x6f
void ld_hlp_b(z80_t * z80){
	write_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L], z80->registers[REG_B]);
}// 0x70
void ld_hlp_c(z80_t * z80){
	write_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L], z80->registers[REG_C]);
}// 0x71
void ld_hlp_d(z80_t * z80){
	write_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L], z80->registers[REG_D]);
}// 0x72
void ld_hlp_e(z80_t * z80){
	write_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L], z80->registers[REG_E]);
}// 0x73
void ld_hlp_h(z80_t * z80){
	write_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L], z80->registers[REG_H]);
}// 0x74
void ld_hlp_l(z80_t * z80){
	write_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L], z80->registers[REG_L]);
}// 0x75
void halt(z80_t * z80){}// 0x76
void ld_hlp_a(z80_t * z80){
	write_8bit_z80(z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L], z80->registers[REG_A]);
}// 0x77
void ld_a_b(z80_t * z80){
	z80->registers[REG_A] = z80->registers[REG_B];
}// 0x78
void ld_a_c(z80_t * z80){
	z80->registers[REG_A] = z80->registers[REG_C];
}// 0x79
void ld_a_d(z80_t * z80){
	z80->registers[REG_A] = z80->registers[REG_D];
}// 0x7a
void ld_a_e(z80_t * z80){
	z80->registers[REG_A] = z80->registers[REG_E];
}// 0x7b
void ld_a_h(z80_t * z80){
	z80->registers[REG_A] = z80->registers[REG_H];
}// 0x7c
void ld_a_l(z80_t * z80){
	z80->registers[REG_A] = z80->registers[REG_L];
}// 0x7d
void ld_a_hlp(z80_t * z80){
	z80->registers[REG_A] = read_8bit_z80( z80, (z80->registers[REG_H] << 8) + z80->registers[REG_L] );
}// 0x7e
void add_a_b(z80_t * z80){}
void add_a_c(z80_t * z80){}
void add_a_d(z80_t * z80){}
void add_a_e(z80_t * z80){}
void add_a_h(z80_t * z80){}
void add_a_l(z80_t * z80){}
void add_a_hlp(z80_t * z80){}
void add_a_a(z80_t * z80){}
void adc_b(z80_t * z80){}
void adc_c(z80_t * z80){}
void adc_d(z80_t * z80){}
void adc_e(z80_t * z80){}
void adc_h(z80_t * z80){}
void adc_l(z80_t * z80){}
void adc_hlp(z80_t * z80){}
void adc_a(z80_t * z80){}
void sub_b(z80_t * z80){}
void sub_c(z80_t * z80){}
void sub_d(z80_t * z80){}
void sub_e(z80_t * z80){}
void sub_h(z80_t * z80){}
void sub_l(z80_t * z80){}
void sub_hlp(z80_t * z80){}
void sub_a(z80_t * z80){}
void sbc_b(z80_t * z80){}
void sbc_c(z80_t * z80){}
void sbc_d(z80_t * z80){}
void sbc_e(z80_t * z80){}
void sbc_h(z80_t * z80){}
void sbc_l(z80_t * z80){}
void sbc_hlp(z80_t * z80){}
void sbc_a(z80_t * z80){}
void and_b(z80_t * z80){}
void and_c(z80_t * z80){}
void and_d(z80_t * z80){}
void and_e(z80_t * z80){}
void and_h(z80_t * z80){}
void and_l(z80_t * z80){}
void and_hlp(z80_t * z80){}
void and_a(z80_t * z80){}
void xor_b(z80_t * z80){}
void xor_c(z80_t * z80){}
void xor_d(z80_t * z80){}
void xor_e(z80_t * z80){}
void xor_h(z80_t * z80){}
void xor_l(z80_t * z80){}
void xor_hlp(z80_t * z80){}
void xor_a(z80_t * z80){}
void or_b(z80_t * z80){}
void or_c(z80_t * z80){}
void or_d(z80_t * z80){}
void or_e(z80_t * z80){}
void or_h(z80_t * z80){}
void or_l(z80_t * z80){}
void or_hlp(z80_t * z80){}
void or_a(z80_t * z80){}
void cp_b(z80_t * z80){}
void cp_c(z80_t * z80){}
void cp_d(z80_t * z80){}
void cp_e(z80_t * z80){}
void cp_h(z80_t * z80){}
void cp_l(z80_t * z80){}
void cp_hlp(z80_t * z80){}
void cp_a(z80_t * z80){}
void ret_nz(z80_t * z80){}
void pop_bc(z80_t * z80){
	z80->registers[REG_C] = read_8bit_z80(z80, z80->sp++);
	z80->registers[REG_B] = read_8bit_z80(z80, z80->sp++);
}//0xc1
void jp_nz_nn(z80_t * z80, uint16_t operand){}
void jp_nn(z80_t * z80, uint16_t operand){}
void call_nz_nn(z80_t * z80, uint16_t operand){}
void push_bc(z80_t * z80){
	write_8bit_z80(z80, --z80->sp, z80->registers[REG_B]);
	write_8bit_z80(z80, --z80->sp, z80->registers[REG_C]);
}// 0xc5
void add_a_n(z80_t * z80, unsigned char operand){}
void rst_0(z80_t * z80){}
void ret_z(z80_t * z80){}
void ret(z80_t * z80){}
void jp_z_nn(z80_t * z80, uint16_t operand){}
void call_z_nn(z80_t * z80, uint16_t operand){}
void call_nn(z80_t * z80, uint16_t operand){}
void adc_n(z80_t * z80, unsigned char operand){}
void rst_08(z80_t * z80){}
void ret_nc(z80_t * z80){}
void pop_de(z80_t * z80){
	z80->registers[REG_E] = read_8bit_z80(z80, z80->sp++);
	z80->registers[REG_D] = read_8bit_z80(z80, z80->sp++);
}// 0xd1
void jp_nc_nn(z80_t * z80, uint16_t operand){}
void call_nc_nn(z80_t * z80, uint16_t operand){}
void push_de(z80_t * z80){
	write_8bit_z80(z80, --z80->sp, z80->registers[REG_D]);
	write_8bit_z80(z80, --z80->sp, z80->registers[REG_E]);
}// 0xd5
void sub_n(z80_t * z80, unsigned char operand){}
void rst_10(z80_t * z80){}
void ret_c(z80_t * z80){}
void jp_c_nn(z80_t * z80, uint16_t operand){}
void call_c_nn(z80_t * z80, uint16_t operand){}
void sbc_n(z80_t * z80, unsigned char operand){}
void rst_18(z80_t * z80){}
void ld_ff_n_ap(z80_t * z80, unsigned char operand){
	write_8bit_z80(z80, 0xff00 + operand, z80->registers[REG_A]);
}// 0xe0
void pop_hl(z80_t * z80){
	z80->registers[REG_L] = read_8bit_z80(z80, z80->sp++);
	z80->registers[REG_H] = read_8bit_z80(z80, z80->sp++);
}// 0xe1
void ld_ff_c_a(z80_t * z80){
	write_8bit_z80(z80, z80->registers[REG_C] + 0xff00, z80->registers[REG_A]);
}// 0xe2
void push_hl(z80_t * z80){
	write_8bit_z80(z80, --z80->sp, z80->registers[REG_H]);
	write_8bit_z80(z80, --z80->sp, z80->registers[REG_L]);
}// 0xe5
void and_n(z80_t * z80, unsigned char operand){}
void rst_20(z80_t * z80){}
void add_sp_n(char operand){}
void jp_hl(z80_t * z80){}
void ld_nnp_a(z80_t * z80, uint16_t operand){
	write_8bit_z80(z80, operand, z80->registers[REG_A]);
}// 0xea
void xor_n(z80_t * z80, unsigned char operand){}
void rst_28(z80_t * z80){}
void ld_ff_ap_n(z80_t * z80, unsigned char operand){
	z80->registers[REG_A] = read_8bit_z80(z80, 0xff00 + operand);
}// 0xf0
void pop_af(z80_t * z80){
	z80->registers[REG_F] = read_8bit_z80(z80, z80->sp++);
	z80->registers[REG_A] = read_8bit_z80(z80, z80->sp++);
}// 0xf1
void ld_a_ff_c(z80_t * z80){
	z80->registers[REG_A] = read_8bit_z80(z80, z80->registers[REG_C] + 0xff00);
}// 0xf2
void di_inst(z80_t * z80){}// 0xf3
void push_af(z80_t * z80){
	write_8bit_z80(z80, --z80->sp, z80->registers[REG_A]);
	write_8bit_z80(z80, --z80->sp, z80->registers[REG_F]);
}// 0xf5
void or_n(z80_t * z80, unsigned char operand){}// 0xf6
void rst_30(z80_t * z80){}// 0xf7
void ld_hl_sp_n(z80_t * z80, unsigned char operand){
	int result;

	result = z80->sp + (signed char) operand;
	
	//set carry flag
	if(result & 0xffff0000){
		z80->registers[REG_F] |= (1 << FLAG_CARRY);
	}else{
		z80->registers[REG_F] &= ~(1 << FLAG_CARRY);
	}
	
	//set half carry flag
	if( (z80->sp & 0x0f) + (operand & 0x0f) > 0x0f ){
		z80->registers[REG_F] |= (1 << FLAG_HALF_CARRY);
	}else{
		z80->registers[REG_F] &= ~(1 << FLAG_HALF_CARRY);
	}

	//clear zero and subtract flags
	z80->registers[REG_F] &= ~(1 << FLAG_ZERO);
	z80->registers[REG_F] &= ~(1 << FLAG_SUB);

	//set (HL) to result
	z80->registers[REG_H] = (result & 0x0000ff00) >> 8;
	z80->registers[REG_L] = (result & 0x000000ff);
}// 0xf8
void ld_sp_hl(z80_t * z80){
	z80->sp = (z80->registers[REG_H] << 8) + z80->registers[REG_L];
}// 0xf9
void ld_a_nnp(z80_t * z80, uint16_t operand){
}// 0xfa
void ei(z80_t * z80){}
void cp_n(z80_t * z80, unsigned char operand){}
void rst_38(z80_t * z80){}
