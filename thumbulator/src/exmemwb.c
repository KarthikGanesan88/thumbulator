#include "thumbulator/exmemwb.h"

uint16_t insn;

void do_cflag(uint32_t a, uint32_t b, uint32_t carry)
{
  uint32_t result;

  result = (a & 0x7FFFFFFF) + (b & 0x7FFFFFFF) + carry; //carry in
  result = (result >> 31) + (a >> 31) + (b >> 31);      //carry out
  cpu_set_flag_c(result >> 1);
}

uint32_t adcs(decode_result);
uint32_t adds_i3(decode_result);
uint32_t adds_i8(decode_result);
uint32_t adds_r(decode_result);
uint32_t add_r(decode_result);
uint32_t add_sp(decode_result);
uint32_t adr(decode_result);
uint32_t subs_i3(decode_result);
uint32_t subs_i8(decode_result);
uint32_t subs(decode_result);
uint32_t sub_sp(decode_result);
uint32_t sbcs(decode_result);
uint32_t rsbs(decode_result);
uint32_t muls(decode_result);
uint32_t cmn(decode_result);
uint32_t cmp_i(decode_result);
uint32_t cmp_r(decode_result);
uint32_t tst(decode_result);
uint32_t b(decode_result);
uint32_t b_c(decode_result);
uint32_t blx(decode_result);
uint32_t bx(decode_result);
uint32_t bl(decode_result);
uint32_t ands(decode_result);
uint32_t bics(decode_result);
uint32_t eors(decode_result);
uint32_t orrs(decode_result);
uint32_t mvns(decode_result);
uint32_t asrs_i(decode_result);
uint32_t asrs_r(decode_result);
uint32_t lsls_i(decode_result);
uint32_t lsrs_i(decode_result);
uint32_t lsls_r(decode_result);
uint32_t lsrs_r(decode_result);
uint32_t rors(decode_result);
uint32_t ldm(decode_result);
uint32_t stm(decode_result);
uint32_t pop(decode_result);
uint32_t push(decode_result);
uint32_t ldr_i(decode_result);
uint32_t ldr_sp(decode_result);
uint32_t ldr_lit(decode_result);
uint32_t ldr_r(decode_result);
uint32_t ldrb_i(decode_result);
uint32_t ldrb_r(decode_result);
uint32_t ldrh_i(decode_result);
uint32_t ldrh_r(decode_result);
uint32_t ldrsb_r(decode_result);
uint32_t ldrsh_r(decode_result);
uint32_t str_i(decode_result);
uint32_t str_sp(decode_result);
uint32_t str_r(decode_result);
uint32_t strb_i(decode_result);
uint32_t strb_r(decode_result);
uint32_t strh_i(decode_result);
uint32_t strh_r(decode_result);
uint32_t movs_i(decode_result);
uint32_t mov_r(decode_result);
uint32_t movs_r(decode_result);
uint32_t sxtb(decode_result);
uint32_t sxth(decode_result);
uint32_t uxtb(decode_result);
uint32_t uxth(decode_result);
uint32_t rev(decode_result);
uint32_t rev16(decode_result);
uint32_t revsh(decode_result);
uint32_t breakpoint(decode_result);

uint32_t exmemwb_error(decode_result decoded)
{
  fprintf(stderr, "Error: Unsupported instruction: Unable to execute\n");
  terminate_simulation(1);
  return 0;
}

uint32_t exmemwb_exit_simulation(decode_result decoded)
{
  printf("Exit instruction encountered.");
  simulate = false;
  return 0;
}

// Execute functions that require more opcode bits than the first 6
uint32_t (*executeJumpTable6[2])(decode_result) = {
    adds_r, /* 060 - 067 */
    subs    /* 068 - 06F */
};

uint32_t entry6(decode_result decoded)
{
  return executeJumpTable6[(insn >> 9) & 0x1](decoded);
}

uint32_t (*executeJumpTable7[2])(decode_result) = {
    adds_i3, /* (070 - 077) */
    subs_i3  /* (078 - 07F) */
};

uint32_t entry7(decode_result decoded)
{
  return executeJumpTable7[(insn >> 9) & 0x1](decoded);
}

uint32_t (*executeJumpTable16[16])(decode_result) = {ands, eors, lsls_r, lsrs_r, asrs_r, adcs, sbcs,
    rors, tst, rsbs, cmp_r, exmemwb_error, orrs, muls, bics, mvns};

uint32_t entry16(decode_result decoded)
{
  return executeJumpTable16[(insn >> 6) & 0xF](decoded);
}

uint32_t (*executeJumpTable17[8])(decode_result) = {
    add_r,        /* (110 - 113) */
    add_r, cmp_r, /* (114 - 117) */
    cmp_r, mov_r, /* (118 - 11B) */
    mov_r, bx,    /* (11C - 11D) */
    blx           /* (11E - 11F) */
};

uint32_t entry17(decode_result decoded)
{
  return executeJumpTable17[(insn >> 7) & 0x7](decoded);
}

uint32_t (*executeJumpTable20[2])(decode_result) = {
    str_r, /* (140 - 147) */
    strh_r /* (148 - 14F) */
};

uint32_t entry20(decode_result decoded)
{
  return executeJumpTable20[(insn >> 9) & 0x1](decoded);
}

uint32_t (*executeJumpTable21[2])(decode_result) = {
    strb_r, /* (150 - 157) */
    ldrsb_r /* (158 - 15F) */
};

uint32_t entry21(decode_result decoded)
{
  return executeJumpTable21[(insn >> 9) & 0x1](decoded);
}

uint32_t (*executeJumpTable22[2])(decode_result) = {
    ldr_r, /* (160 - 167) */
    ldrh_r /* (168 - 16F) */
};

uint32_t entry22(decode_result decoded)
{
  return executeJumpTable22[(insn >> 9) & 0x1](decoded);
}

uint32_t (*executeJumpTable23[2])(decode_result) = {
    ldrb_r, /* (170 - 177) */
    ldrsh_r /* (178 - 17F) */
};

uint32_t entry23(decode_result decoded)
{
  return executeJumpTable23[(insn >> 9) & 0x1](decoded);
}

uint32_t (*executeJumpTable44[16])(decode_result) = {add_sp, /* (2C0 - 2C1) */
    add_sp, sub_sp,                                          /* (2C2 - 2C3) */
    sub_sp, exmemwb_error, exmemwb_error, exmemwb_error, exmemwb_error, sxth, sxtb, uxth, uxtb,
    exmemwb_error, exmemwb_error, exmemwb_error, exmemwb_error};

uint32_t entry44(decode_result decoded)
{
  return executeJumpTable44[(insn >> 6) & 0xF](decoded);
}

uint32_t (*executeJumpTable46[16])(decode_result) = {exmemwb_error, exmemwb_error, exmemwb_error,
    exmemwb_error, exmemwb_error, exmemwb_error, exmemwb_error, exmemwb_error, rev, rev16,
    exmemwb_error, exmemwb_error, exmemwb_error, exmemwb_error, exmemwb_error, exmemwb_error};

uint32_t entry46(decode_result decoded)
{
  return executeJumpTable46[(insn >> 6) & 0xF](decoded);
}

uint32_t (*executeJumpTable47[2])(decode_result) = {
    pop,       /* (2F0 - 2F7) */
    breakpoint /* (2F8 - 2FB) */
};

uint32_t entry47(decode_result decoded)
{
  return executeJumpTable47[(insn >> 9) & 0x1](decoded);
}

uint32_t entry55(decode_result decoded)
{
  if((insn & 0x0300) != 0x0300) {
    return b_c(decoded);
  }

  if(insn == 0xDF01) {
    return exmemwb_exit_simulation(decoded);
  }

  return exmemwb_error(decoded);
}

uint32_t (*executeJumpTable[64])(decode_result) = {lsls_i, lsls_i, lsrs_i, lsrs_i, asrs_i, asrs_i,
    entry6,                                                                    /* 6 */
    entry7,                                                                    /* 7 */
    movs_i, movs_i, cmp_i, cmp_i, adds_i8, adds_i8, subs_i8, subs_i8, entry16, /* 16 */
    entry17,                                                                   /* 17 */
    ldr_lit, ldr_lit, entry20,                                                 /* 20 */
    entry21,                                                                   /* 21 */
    entry22,                                                                   /* 22 */
    entry23,                                                                   /* 23 */
    str_i, str_i, ldr_i, ldr_i, strb_i, strb_i, ldrb_i, ldrb_i, strh_i, strh_i, ldrh_i, ldrh_i,
    str_sp, str_sp, ldr_sp, ldr_sp, adr, adr, add_sp, add_sp, entry44, /* 44 */
    push, entry46,                                                     /* 46 */
    entry47,                                                           /* 47 */
    stm, stm, ldm, ldm, b_c, b_c, b_c, entry55,                        /* 55 */
    b, b, exmemwb_error, exmemwb_error, bl,                            /* 60 ignore mrs */
    bl,                                                                /* 61 ignore udef */
    exmemwb_error, exmemwb_error};

uint32_t exwbmem(uint16_t pInsn, decode_result decoded)
{
  insn = pInsn;

  uint32_t insnTicks = executeJumpTable[pInsn >> 10](decoded);

  // Update the systick unit and look for resets
  if(systick.control & 0x1) {
    if(insnTicks >= systick.value) {
      // Ignore resets due to reads
      if(systick.value > 0)
        systick.control |= 0x00010000;

      systick.value = systick.reload - insnTicks + systick.value;
    } else
      systick.value -= insnTicks;
  }

  return  insnTicks;
}