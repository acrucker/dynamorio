/* **********************************************************
 * Copyright (c) 2014-2015 Google, Inc.  All rights reserved.
 * **********************************************************/

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of VMware, Inc. nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL VMWARE, INC. OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

/* file "opcode.h" -- opcode definitions and utilities */

#ifndef _OPCODE_H_
#define _OPCODE_H_ 1

/* DR_API EXPORT TOFILE dr_ir_opcodes_arm.h */
/* DR_API EXPORT BEGIN */

/****************************************************************************
 * OPCODES
 */
/**
 * @file dr_ir_opcodes_arm.h
 * @brief Instruction opcode constants for ARM.
 */
#ifdef AVOID_API_EXPORT
/*
 * This enum corresponds with the arrays in table_*.c.
 * They must be kept consistent, using tools/x86opnums.pl (pass -arm).
 * The list in table_a32_encode.c should be edited first and then
 * tools/x86opnums.pl used (with -arm option) to generate the list here.
 * When adding new instructions, be sure to update all of these places:
 *   1) table_* op_instr arrays
 *   2) table_* decoding table entries
 *   3) OP_ enum (here) via x86opnums.pl
 *   4) update OP_LAST at end of enum here
 *   5) instr_create macros
 *   6) suite/tests/api/ir* tests
 */
#endif
/** Opcode constants for use in the instr_t data structure. */
enum {
/*   0 */     OP_INVALID,  /* NULL, */ /**< INVALID opcode */
/*   1 */     OP_UNDECODED,  /* NULL, */ /**< UNDECODED opcode */
/*   2 */     OP_CONTD,    /* NULL, */ /**< CONTD opcode */
/*   3 */     OP_LABEL,    /* NULL, */ /**< LABEL opcode */

/*   4 */     OP_adc,                /**< ARM adc opcode. */
/*   5 */     OP_adcs,               /**< ARM adcs opcode. */
/*   6 */     OP_add,                /**< ARM add opcode. */
/*   7 */     OP_adds,               /**< ARM adds opcode. */
/*   8 */     OP_aesd_8,             /**< ARM aesd_8 opcode. */
/*   9 */     OP_aese_8,             /**< ARM aese_8 opcode. */
/*  10 */     OP_aesimc_8,           /**< ARM aesimc_8 opcode. */
/*  11 */     OP_aesmc_8,            /**< ARM aesmc_8 opcode. */
/*  12 */     OP_and,                /**< ARM and opcode. */
/*  13 */     OP_ands,               /**< ARM ands opcode. */
/*  14 */     OP_asr,                /**< ARM asr opcode. */
/*  15 */     OP_asrs,               /**< ARM asrs opcode. */
/*  16 */     OP_b,                  /**< ARM b opcode. */
/*  17 */     OP_b_short,            /**< ARM b_short opcode. */
/*  18 */     OP_bfc,                /**< ARM bfc opcode. */
/*  19 */     OP_bfi,                /**< ARM bfi opcode. */
/*  20 */     OP_bic,                /**< ARM bic opcode. */
/*  21 */     OP_bics,               /**< ARM bics opcode. */
/*  22 */     OP_bkpt,               /**< ARM bkpt opcode. */
/*  23 */     OP_bl,                 /**< ARM bl opcode. */
/*  24 */     OP_blx,                /**< ARM blx opcode. */
/*  25 */     OP_blx_ind,            /**< ARM blx_ind opcode. */
/*  26 */     OP_bx,                 /**< ARM bx opcode. */
/*  27 */     OP_bxj,                /**< ARM bxj opcode. */
/*  28 */     OP_cbnz,               /**< ARM cbnz opcode. */
/*  29 */     OP_cbz,                /**< ARM cbz opcode. */
/*  30 */     OP_cdp,                /**< ARM cdp opcode. */
/*  31 */     OP_cdp2,               /**< ARM cdp2 opcode. */
/*  32 */     OP_clrex,              /**< ARM clrex opcode. */
/*  33 */     OP_clz,                /**< ARM clz opcode. */
/*  34 */     OP_cmn,                /**< ARM cmn opcode. */
/*  35 */     OP_cmp,                /**< ARM cmp opcode. */
/*  36 */     OP_cps,                /**< ARM cps opcode. */
/*  37 */     OP_cpsid,              /**< ARM cpsid opcode. */
/*  38 */     OP_cpsie,              /**< ARM cpsie opcode. */
/*  39 */     OP_crc32b,             /**< ARM crc32b opcode. */
/*  40 */     OP_crc32cb,            /**< ARM crc32cb opcode. */
/*  41 */     OP_crc32h,             /**< ARM crc32h opcode. */
/*  42 */     OP_crc32ch,            /**< ARM crc32ch opcode. */
/*  43 */     OP_crc32w,             /**< ARM crc32w opcode. */
/*  44 */     OP_crc32cw,            /**< ARM crc32cw opcode. */
/*  45 */     OP_dbg,                /**< ARM dbg opcode. */
/*  46 */     OP_dcps1,              /**< ARM dcps1 opcode. */
/*  47 */     OP_dcps2,              /**< ARM dcps2 opcode. */
/*  48 */     OP_dcps3,              /**< ARM dcps3 opcode. */
/*  49 */     OP_dmb,                /**< ARM dmb opcode. */
/*  50 */     OP_dsb,                /**< ARM dsb opcode. */
/*  51 */     OP_eor,                /**< ARM eor opcode. */
/*  52 */     OP_eors,               /**< ARM eors opcode. */
/*  53 */     OP_eret,               /**< ARM eret opcode. */
/*  54 */     OP_hlt,                /**< ARM hlt opcode. */
/*  55 */     OP_hvc,                /**< ARM hvc opcode. */
/*  56 */     OP_isb,                /**< ARM isb opcode. */
/*  57 */     OP_it,                 /**< ARM it opcode. */
/*  58 */     OP_lda,                /**< ARM lda opcode. */
/*  59 */     OP_ldab,               /**< ARM ldab opcode. */
/*  60 */     OP_ldaex,              /**< ARM ldaex opcode. */
/*  61 */     OP_ldaexb,             /**< ARM ldaexb opcode. */
/*  62 */     OP_ldaexd,             /**< ARM ldaexd opcode. */
/*  63 */     OP_ldaexh,             /**< ARM ldaexh opcode. */
/*  64 */     OP_ldah,               /**< ARM ldah opcode. */
/*  65 */     OP_ldc,                /**< ARM ldc opcode. */
/*  66 */     OP_ldc2,               /**< ARM ldc2 opcode. */
/*  67 */     OP_ldc2l,              /**< ARM ldc2l opcode. */
/*  68 */     OP_ldcl,               /**< ARM ldcl opcode. */
/*  69 */     OP_ldm,                /**< ARM ldm opcode. */
/*  70 */     OP_ldm_priv,           /**< ARM ldm_priv opcode. */
/*  71 */     OP_ldmda,              /**< ARM ldmda opcode. */
/*  72 */     OP_ldmda_priv,         /**< ARM ldmda_priv opcode. */
/*  73 */     OP_ldmdb,              /**< ARM ldmdb opcode. */
/*  74 */     OP_ldmdb_priv,         /**< ARM ldmdb_priv opcode. */
/*  75 */     OP_ldmib,              /**< ARM ldmib opcode. */
/*  76 */     OP_ldmib_priv,         /**< ARM ldmib_priv opcode. */
/*  77 */     OP_ldr,                /**< ARM ldr opcode. */
/*  78 */     OP_ldrb,               /**< ARM ldrb opcode. */
/*  79 */     OP_ldrbt,              /**< ARM ldrbt opcode. */
/*  80 */     OP_ldrd,               /**< ARM ldrd opcode. */
/*  81 */     OP_ldrex,              /**< ARM ldrex opcode. */
/*  82 */     OP_ldrexb,             /**< ARM ldrexb opcode. */
/*  83 */     OP_ldrexd,             /**< ARM ldrexd opcode. */
/*  84 */     OP_ldrexh,             /**< ARM ldrexh opcode. */
/*  85 */     OP_ldrh,               /**< ARM ldrh opcode. */
/*  86 */     OP_ldrht,              /**< ARM ldrht opcode. */
/*  87 */     OP_ldrsb,              /**< ARM ldrsb opcode. */
/*  88 */     OP_ldrsbt,             /**< ARM ldrsbt opcode. */
/*  89 */     OP_ldrsh,              /**< ARM ldrsh opcode. */
/*  90 */     OP_ldrsht,             /**< ARM ldrsht opcode. */
/*  91 */     OP_ldrt,               /**< ARM ldrt opcode. */
/*  92 */     OP_lsl,                /**< ARM lsl opcode. */
/*  93 */     OP_lsls,               /**< ARM lsls opcode. */
/*  94 */     OP_lsr,                /**< ARM lsr opcode. */
/*  95 */     OP_lsrs,               /**< ARM lsrs opcode. */
/*  96 */     OP_mcr,                /**< ARM mcr opcode. */
/*  97 */     OP_mcr2,               /**< ARM mcr2 opcode. */
/*  98 */     OP_mcrr,               /**< ARM mcrr opcode. */
/*  99 */     OP_mcrr2,              /**< ARM mcrr2 opcode. */
/* 100 */     OP_mla,                /**< ARM mla opcode. */
/* 101 */     OP_mlas,               /**< ARM mlas opcode. */
/* 102 */     OP_mls,                /**< ARM mls opcode. */
/* 103 */     OP_mov,                /**< ARM mov opcode. */
/* 104 */     OP_movs,               /**< ARM movs opcode. */
/* 105 */     OP_movt,               /**< ARM movt opcode. */
/* 106 */     OP_movw,               /**< ARM movw opcode. */
/* 107 */     OP_mrc,                /**< ARM mrc opcode. */
/* 108 */     OP_mrc2,               /**< ARM mrc2 opcode. */
/* 109 */     OP_mrrc,               /**< ARM mrrc opcode. */
/* 110 */     OP_mrrc2,              /**< ARM mrrc2 opcode. */
/* 111 */     OP_mrs,                /**< ARM mrs opcode. */
/* 112 */     OP_mrs_priv,           /**< ARM mrs_priv opcode. */
/* 113 */     OP_msr,                /**< ARM msr opcode. */
/* 114 */     OP_msr_priv,           /**< ARM msr_priv opcode. */
/* 115 */     OP_mul,                /**< ARM mul opcode. */
/* 116 */     OP_muls,               /**< ARM muls opcode. */
/* 117 */     OP_mvn,                /**< ARM mvn opcode. */
/* 118 */     OP_mvns,               /**< ARM mvns opcode. */
/* 119 */     OP_nop,                /**< ARM nop opcode. */
/* 120 */     OP_orn,                /**< ARM orn opcode. */
/* 121 */     OP_orr,                /**< ARM orr opcode. */
/* 122 */     OP_orrs,               /**< ARM orrs opcode. */
/* 123 */     OP_pkhbt,              /**< ARM pkhbt opcode. */
/* 124 */     OP_pkhtb,              /**< ARM pkhtb opcode. */
/* 125 */     OP_pld,                /**< ARM pld opcode. */
/* 126 */     OP_pldw,               /**< ARM pldw opcode. */
/* 127 */     OP_pli,                /**< ARM pli opcode. */
/* 128 */     OP_qadd,               /**< ARM qadd opcode. */
/* 129 */     OP_qadd16,             /**< ARM qadd16 opcode. */
/* 130 */     OP_qadd8,              /**< ARM qadd8 opcode. */
/* 131 */     OP_qasx,               /**< ARM qasx opcode. */
/* 132 */     OP_qdadd,              /**< ARM qdadd opcode. */
/* 133 */     OP_qdsub,              /**< ARM qdsub opcode. */
/* 134 */     OP_qsax,               /**< ARM qsax opcode. */
/* 135 */     OP_qsub,               /**< ARM qsub opcode. */
/* 136 */     OP_qsub16,             /**< ARM qsub16 opcode. */
/* 137 */     OP_qsub8,              /**< ARM qsub8 opcode. */
/* 138 */     OP_rbit,               /**< ARM rbit opcode. */
/* 139 */     OP_rev,                /**< ARM rev opcode. */
/* 140 */     OP_rev16,              /**< ARM rev16 opcode. */
/* 141 */     OP_revsh,              /**< ARM revsh opcode. */
/* 142 */     OP_rfeda,              /**< ARM rfeda opcode. */
/* 143 */     OP_rfedb,              /**< ARM rfedb opcode. */
/* 144 */     OP_rfeia,              /**< ARM rfeia opcode. */
/* 145 */     OP_rfeib,              /**< ARM rfeib opcode. */
/* 146 */     OP_ror,                /**< ARM ror opcode. */
/* 147 */     OP_rors,               /**< ARM rors opcode. */
/* 148 */     OP_rrx,                /**< ARM rrx opcode. */
/* 149 */     OP_rrxs,               /**< ARM rrxs opcode. */
/* 150 */     OP_rsb,                /**< ARM rsb opcode. */
/* 151 */     OP_rsbs,               /**< ARM rsbs opcode. */
/* 152 */     OP_rsc,                /**< ARM rsc opcode. */
/* 153 */     OP_rscs,               /**< ARM rscs opcode. */
/* 154 */     OP_sadd16,             /**< ARM sadd16 opcode. */
/* 155 */     OP_sadd8,              /**< ARM sadd8 opcode. */
/* 156 */     OP_sasx,               /**< ARM sasx opcode. */
/* 157 */     OP_sbc,                /**< ARM sbc opcode. */
/* 158 */     OP_sbcs,               /**< ARM sbcs opcode. */
/* 159 */     OP_sbfx,               /**< ARM sbfx opcode. */
/* 160 */     OP_sdiv,               /**< ARM sdiv opcode. */
/* 161 */     OP_sel,                /**< ARM sel opcode. */
/* 162 */     OP_setend,             /**< ARM setend opcode. */
/* 163 */     OP_sev,                /**< ARM sev opcode. */
/* 164 */     OP_sevl,               /**< ARM sevl opcode. */
/* 165 */     OP_sha1c_32,           /**< ARM sha1c_32 opcode. */
/* 166 */     OP_sha1h_32,           /**< ARM sha1h_32 opcode. */
/* 167 */     OP_sha1m_32,           /**< ARM sha1m_32 opcode. */
/* 168 */     OP_sha1p_32,           /**< ARM sha1p_32 opcode. */
/* 169 */     OP_sha1su0_32,         /**< ARM sha1su0_32 opcode. */
/* 170 */     OP_sha1su1_32,         /**< ARM sha1su1_32 opcode. */
/* 171 */     OP_sha256h2_32,        /**< ARM sha256h2_32 opcode. */
/* 172 */     OP_sha256h_32,         /**< ARM sha256h_32 opcode. */
/* 173 */     OP_sha256su0_32,       /**< ARM sha256su0_32 opcode. */
/* 174 */     OP_sha256su1_32,       /**< ARM sha256su1_32 opcode. */
/* 175 */     OP_shadd16,            /**< ARM shadd16 opcode. */
/* 176 */     OP_shadd8,             /**< ARM shadd8 opcode. */
/* 177 */     OP_shasx,              /**< ARM shasx opcode. */
/* 178 */     OP_shsax,              /**< ARM shsax opcode. */
/* 179 */     OP_shsub16,            /**< ARM shsub16 opcode. */
/* 180 */     OP_shsub8,             /**< ARM shsub8 opcode. */
/* 181 */     OP_smc,                /**< ARM smc opcode. */
/* 182 */     OP_smlabb,             /**< ARM smlabb opcode. */
/* 183 */     OP_smlabt,             /**< ARM smlabt opcode. */
/* 184 */     OP_smlad,              /**< ARM smlad opcode. */
/* 185 */     OP_smladx,             /**< ARM smladx opcode. */
/* 186 */     OP_smlal,              /**< ARM smlal opcode. */
/* 187 */     OP_smlalbb,            /**< ARM smlalbb opcode. */
/* 188 */     OP_smlalbt,            /**< ARM smlalbt opcode. */
/* 189 */     OP_smlald,             /**< ARM smlald opcode. */
/* 190 */     OP_smlaldx,            /**< ARM smlaldx opcode. */
/* 191 */     OP_smlals,             /**< ARM smlals opcode. */
/* 192 */     OP_smlaltb,            /**< ARM smlaltb opcode. */
/* 193 */     OP_smlaltt,            /**< ARM smlaltt opcode. */
/* 194 */     OP_smlatb,             /**< ARM smlatb opcode. */
/* 195 */     OP_smlatt,             /**< ARM smlatt opcode. */
/* 196 */     OP_smlawb,             /**< ARM smlawb opcode. */
/* 197 */     OP_smlawt,             /**< ARM smlawt opcode. */
/* 198 */     OP_smlsd,              /**< ARM smlsd opcode. */
/* 199 */     OP_smlsdx,             /**< ARM smlsdx opcode. */
/* 200 */     OP_smlsld,             /**< ARM smlsld opcode. */
/* 201 */     OP_smlsldx,            /**< ARM smlsldx opcode. */
/* 202 */     OP_smmla,              /**< ARM smmla opcode. */
/* 203 */     OP_smmlar,             /**< ARM smmlar opcode. */
/* 204 */     OP_smmls,              /**< ARM smmls opcode. */
/* 205 */     OP_smmlsr,             /**< ARM smmlsr opcode. */
/* 206 */     OP_smulbb,             /**< ARM smulbb opcode. */
/* 207 */     OP_smulbt,             /**< ARM smulbt opcode. */
/* 208 */     OP_smull,              /**< ARM smull opcode. */
/* 209 */     OP_smulls,             /**< ARM smulls opcode. */
/* 210 */     OP_smultb,             /**< ARM smultb opcode. */
/* 211 */     OP_smultt,             /**< ARM smultt opcode. */
/* 212 */     OP_smulwb,             /**< ARM smulwb opcode. */
/* 213 */     OP_smulwt,             /**< ARM smulwt opcode. */
/* 214 */     OP_srsda,              /**< ARM srsda opcode. */
/* 215 */     OP_srsdb,              /**< ARM srsdb opcode. */
/* 216 */     OP_srsia,              /**< ARM srsia opcode. */
/* 217 */     OP_srsib,              /**< ARM srsib opcode. */
/* 218 */     OP_ssat,               /**< ARM ssat opcode. */
/* 219 */     OP_ssat16,             /**< ARM ssat16 opcode. */
/* 220 */     OP_ssax,               /**< ARM ssax opcode. */
/* 221 */     OP_ssub16,             /**< ARM ssub16 opcode. */
/* 222 */     OP_ssub8,              /**< ARM ssub8 opcode. */
/* 223 */     OP_stc,                /**< ARM stc opcode. */
/* 224 */     OP_stc2,               /**< ARM stc2 opcode. */
/* 225 */     OP_stc2l,              /**< ARM stc2l opcode. */
/* 226 */     OP_stcl,               /**< ARM stcl opcode. */
/* 227 */     OP_stl,                /**< ARM stl opcode. */
/* 228 */     OP_stlb,               /**< ARM stlb opcode. */
/* 229 */     OP_stlex,              /**< ARM stlex opcode. */
/* 230 */     OP_stlexb,             /**< ARM stlexb opcode. */
/* 231 */     OP_stlexd,             /**< ARM stlexd opcode. */
/* 232 */     OP_stlexh,             /**< ARM stlexh opcode. */
/* 233 */     OP_stlh,               /**< ARM stlh opcode. */
/* 234 */     OP_stm,                /**< ARM stm opcode. */
/* 235 */     OP_stm_priv,           /**< ARM stm_priv opcode. */
/* 236 */     OP_stmda,              /**< ARM stmda opcode. */
/* 237 */     OP_stmda_priv,         /**< ARM stmda_priv opcode. */
/* 238 */     OP_stmdb,              /**< ARM stmdb opcode. */
/* 239 */     OP_stmdb_priv,         /**< ARM stmdb_priv opcode. */
/* 240 */     OP_stmib,              /**< ARM stmib opcode. */
/* 241 */     OP_stmib_priv,         /**< ARM stmib_priv opcode. */
/* 242 */     OP_str,                /**< ARM str opcode. */
/* 243 */     OP_strb,               /**< ARM strb opcode. */
/* 244 */     OP_strbt,              /**< ARM strbt opcode. */
/* 245 */     OP_strd,               /**< ARM strd opcode. */
/* 246 */     OP_strex,              /**< ARM strex opcode. */
/* 247 */     OP_strexb,             /**< ARM strexb opcode. */
/* 248 */     OP_strexd,             /**< ARM strexd opcode. */
/* 249 */     OP_strexh,             /**< ARM strexh opcode. */
/* 250 */     OP_strh,               /**< ARM strh opcode. */
/* 251 */     OP_strht,              /**< ARM strht opcode. */
/* 252 */     OP_strt,               /**< ARM strt opcode. */
/* 253 */     OP_sub,                /**< ARM sub opcode. */
/* 254 */     OP_subs,               /**< ARM subs opcode. */
/* 255 */     OP_svc,                /**< ARM svc opcode. */
/* 256 */     OP_sxtab,              /**< ARM sxtab opcode. */
/* 257 */     OP_sxtab16,            /**< ARM sxtab16 opcode. */
/* 258 */     OP_sxtah,              /**< ARM sxtah opcode. */
/* 259 */     OP_tbb,                /**< ARM tbb opcode. */
/* 260 */     OP_tbh,                /**< ARM tbh opcode. */
/* 261 */     OP_teq,                /**< ARM teq opcode. */
/* 262 */     OP_tst,                /**< ARM tst opcode. */
/* 263 */     OP_uadd16,             /**< ARM uadd16 opcode. */
/* 264 */     OP_uadd8,              /**< ARM uadd8 opcode. */
/* 265 */     OP_uasx,               /**< ARM uasx opcode. */
/* 266 */     OP_ubfx,               /**< ARM ubfx opcode. */
/* 267 */     OP_udf,                /**< ARM udf opcode. */
/* 268 */     OP_udiv,               /**< ARM udiv opcode. */
/* 269 */     OP_uhadd16,            /**< ARM uhadd16 opcode. */
/* 270 */     OP_uhadd8,             /**< ARM uhadd8 opcode. */
/* 271 */     OP_uhasx,              /**< ARM uhasx opcode. */
/* 272 */     OP_uhsax,              /**< ARM uhsax opcode. */
/* 273 */     OP_uhsub16,            /**< ARM uhsub16 opcode. */
/* 274 */     OP_uhsub8,             /**< ARM uhsub8 opcode. */
/* 275 */     OP_umaal,              /**< ARM umaal opcode. */
/* 276 */     OP_umlal,              /**< ARM umlal opcode. */
/* 277 */     OP_umlals,             /**< ARM umlals opcode. */
/* 278 */     OP_umull,              /**< ARM umull opcode. */
/* 279 */     OP_umulls,             /**< ARM umulls opcode. */
/* 280 */     OP_uqadd16,            /**< ARM uqadd16 opcode. */
/* 281 */     OP_uqadd8,             /**< ARM uqadd8 opcode. */
/* 282 */     OP_uqasx,              /**< ARM uqasx opcode. */
/* 283 */     OP_uqsax,              /**< ARM uqsax opcode. */
/* 284 */     OP_uqsub16,            /**< ARM uqsub16 opcode. */
/* 285 */     OP_uqsub8,             /**< ARM uqsub8 opcode. */
/* 286 */     OP_usada8,             /**< ARM usada8 opcode. */
/* 287 */     OP_usat,               /**< ARM usat opcode. */
/* 288 */     OP_usat16,             /**< ARM usat16 opcode. */
/* 289 */     OP_usax,               /**< ARM usax opcode. */
/* 290 */     OP_usub16,             /**< ARM usub16 opcode. */
/* 291 */     OP_usub8,              /**< ARM usub8 opcode. */
/* 292 */     OP_uxtab,              /**< ARM uxtab opcode. */
/* 293 */     OP_uxtab16,            /**< ARM uxtab16 opcode. */
/* 294 */     OP_uxtah,              /**< ARM uxtah opcode. */
/* 295 */     OP_vaba_s16,           /**< ARM vaba_s16 opcode. */
/* 296 */     OP_vaba_s32,           /**< ARM vaba_s32 opcode. */
/* 297 */     OP_vaba_s8,            /**< ARM vaba_s8 opcode. */
/* 298 */     OP_vaba_u16,           /**< ARM vaba_u16 opcode. */
/* 299 */     OP_vaba_u32,           /**< ARM vaba_u32 opcode. */
/* 300 */     OP_vaba_u8,            /**< ARM vaba_u8 opcode. */
/* 301 */     OP_vabal_s16,          /**< ARM vabal_s16 opcode. */
/* 302 */     OP_vabal_s32,          /**< ARM vabal_s32 opcode. */
/* 303 */     OP_vabal_s8,           /**< ARM vabal_s8 opcode. */
/* 304 */     OP_vabal_u16,          /**< ARM vabal_u16 opcode. */
/* 305 */     OP_vabal_u32,          /**< ARM vabal_u32 opcode. */
/* 306 */     OP_vabal_u8,           /**< ARM vabal_u8 opcode. */
/* 307 */     OP_vabd_s16,           /**< ARM vabd_s16 opcode. */
/* 308 */     OP_vabd_s32,           /**< ARM vabd_s32 opcode. */
/* 309 */     OP_vabd_s8,            /**< ARM vabd_s8 opcode. */
/* 310 */     OP_vabd_u16,           /**< ARM vabd_u16 opcode. */
/* 311 */     OP_vabd_u32,           /**< ARM vabd_u32 opcode. */
/* 312 */     OP_vabd_u8,            /**< ARM vabd_u8 opcode. */
/* 313 */     OP_vabdl_s16,          /**< ARM vabdl_s16 opcode. */
/* 314 */     OP_vabdl_s32,          /**< ARM vabdl_s32 opcode. */
/* 315 */     OP_vabdl_s8,           /**< ARM vabdl_s8 opcode. */
/* 316 */     OP_vabdl_u16,          /**< ARM vabdl_u16 opcode. */
/* 317 */     OP_vabdl_u32,          /**< ARM vabdl_u32 opcode. */
/* 318 */     OP_vabdl_u8,           /**< ARM vabdl_u8 opcode. */
/* 319 */     OP_vabs_f32,           /**< ARM vabs_f32 opcode. */
/* 320 */     OP_vabs_f64,           /**< ARM vabs_f64 opcode. */
/* 321 */     OP_vabs_s16,           /**< ARM vabs_s16 opcode. */
/* 322 */     OP_vabs_s32,           /**< ARM vabs_s32 opcode. */
/* 323 */     OP_vabs_s8,            /**< ARM vabs_s8 opcode. */
/* 324 */     OP_vacge_f32,          /**< ARM vacge_f32 opcode. */
/* 325 */     OP_vacgt_f32,          /**< ARM vacgt_f32 opcode. */
/* 326 */     OP_vadd_f32,           /**< ARM vadd_f32 opcode. */
/* 327 */     OP_vadd_f64,           /**< ARM vadd_f64 opcode. */
/* 328 */     OP_vadd_i16,           /**< ARM vadd_i16 opcode. */
/* 329 */     OP_vadd_i32,           /**< ARM vadd_i32 opcode. */
/* 330 */     OP_vadd_i64,           /**< ARM vadd_i64 opcode. */
/* 331 */     OP_vadd_i8,            /**< ARM vadd_i8 opcode. */
/* 332 */     OP_vaddhn_i16,         /**< ARM vaddhn_i16 opcode. */
/* 333 */     OP_vaddhn_i32,         /**< ARM vaddhn_i32 opcode. */
/* 334 */     OP_vaddhn_i64,         /**< ARM vaddhn_i64 opcode. */
/* 335 */     OP_vaddl_s16,          /**< ARM vaddl_s16 opcode. */
/* 336 */     OP_vaddl_s32,          /**< ARM vaddl_s32 opcode. */
/* 337 */     OP_vaddl_s8,           /**< ARM vaddl_s8 opcode. */
/* 338 */     OP_vaddl_u16,          /**< ARM vaddl_u16 opcode. */
/* 339 */     OP_vaddl_u32,          /**< ARM vaddl_u32 opcode. */
/* 340 */     OP_vaddl_u8,           /**< ARM vaddl_u8 opcode. */
/* 341 */     OP_vaddw_s16,          /**< ARM vaddw_s16 opcode. */
/* 342 */     OP_vaddw_s32,          /**< ARM vaddw_s32 opcode. */
/* 343 */     OP_vaddw_s8,           /**< ARM vaddw_s8 opcode. */
/* 344 */     OP_vaddw_u16,          /**< ARM vaddw_u16 opcode. */
/* 345 */     OP_vaddw_u32,          /**< ARM vaddw_u32 opcode. */
/* 346 */     OP_vaddw_u8,           /**< ARM vaddw_u8 opcode. */
/* 347 */     OP_vand,               /**< ARM vand opcode. */
/* 348 */     OP_vbic,               /**< ARM vbic opcode. */
/* 349 */     OP_vbic_i16,           /**< ARM vbic_i16 opcode. */
/* 350 */     OP_vbic_i32,           /**< ARM vbic_i32 opcode. */
/* 351 */     OP_vbif,               /**< ARM vbif opcode. */
/* 352 */     OP_vbit,               /**< ARM vbit opcode. */
/* 353 */     OP_vbsl,               /**< ARM vbsl opcode. */
/* 354 */     OP_vceq_f32,           /**< ARM vceq_f32 opcode. */
/* 355 */     OP_vceq_i16,           /**< ARM vceq_i16 opcode. */
/* 356 */     OP_vceq_i32,           /**< ARM vceq_i32 opcode. */
/* 357 */     OP_vceq_i8,            /**< ARM vceq_i8 opcode. */
/* 358 */     OP_vcge_f32,           /**< ARM vcge_f32 opcode. */
/* 359 */     OP_vcge_s16,           /**< ARM vcge_s16 opcode. */
/* 360 */     OP_vcge_s32,           /**< ARM vcge_s32 opcode. */
/* 361 */     OP_vcge_s8,            /**< ARM vcge_s8 opcode. */
/* 362 */     OP_vcge_u16,           /**< ARM vcge_u16 opcode. */
/* 363 */     OP_vcge_u32,           /**< ARM vcge_u32 opcode. */
/* 364 */     OP_vcge_u8,            /**< ARM vcge_u8 opcode. */
/* 365 */     OP_vcgt_f32,           /**< ARM vcgt_f32 opcode. */
/* 366 */     OP_vcgt_s16,           /**< ARM vcgt_s16 opcode. */
/* 367 */     OP_vcgt_s32,           /**< ARM vcgt_s32 opcode. */
/* 368 */     OP_vcgt_s8,            /**< ARM vcgt_s8 opcode. */
/* 369 */     OP_vcgt_u16,           /**< ARM vcgt_u16 opcode. */
/* 370 */     OP_vcgt_u32,           /**< ARM vcgt_u32 opcode. */
/* 371 */     OP_vcgt_u8,            /**< ARM vcgt_u8 opcode. */
/* 372 */     OP_vcle_f32,           /**< ARM vcle_f32 opcode. */
/* 373 */     OP_vcle_s16,           /**< ARM vcle_s16 opcode. */
/* 374 */     OP_vcle_s32,           /**< ARM vcle_s32 opcode. */
/* 375 */     OP_vcle_s8,            /**< ARM vcle_s8 opcode. */
/* 376 */     OP_vcls_s16,           /**< ARM vcls_s16 opcode. */
/* 377 */     OP_vcls_s32,           /**< ARM vcls_s32 opcode. */
/* 378 */     OP_vcls_s8,            /**< ARM vcls_s8 opcode. */
/* 379 */     OP_vclt_f32,           /**< ARM vclt_f32 opcode. */
/* 380 */     OP_vclt_s16,           /**< ARM vclt_s16 opcode. */
/* 381 */     OP_vclt_s32,           /**< ARM vclt_s32 opcode. */
/* 382 */     OP_vclt_s8,            /**< ARM vclt_s8 opcode. */
/* 383 */     OP_vclz_i16,           /**< ARM vclz_i16 opcode. */
/* 384 */     OP_vclz_i32,           /**< ARM vclz_i32 opcode. */
/* 385 */     OP_vclz_i8,            /**< ARM vclz_i8 opcode. */
/* 386 */     OP_vcmp_f32,           /**< ARM vcmp_f32 opcode. */
/* 387 */     OP_vcmp_f64,           /**< ARM vcmp_f64 opcode. */
/* 388 */     OP_vcmpe_f32,          /**< ARM vcmpe_f32 opcode. */
/* 389 */     OP_vcmpe_f64,          /**< ARM vcmpe_f64 opcode. */
/* 390 */     OP_vcnt_8,             /**< ARM vcnt_8 opcode. */
/* 391 */     OP_vcvt_f16_f32,       /**< ARM vcvt_f16_f32 opcode. */
/* 392 */     OP_vcvt_f32_f16,       /**< ARM vcvt_f32_f16 opcode. */
/* 393 */     OP_vcvt_f32_f64,       /**< ARM vcvt_f32_f64 opcode. */
/* 394 */     OP_vcvt_f32_s16,       /**< ARM vcvt_f32_s16 opcode. */
/* 395 */     OP_vcvt_f32_s32,       /**< ARM vcvt_f32_s32 opcode. */
/* 396 */     OP_vcvt_f32_u16,       /**< ARM vcvt_f32_u16 opcode. */
/* 397 */     OP_vcvt_f32_u32,       /**< ARM vcvt_f32_u32 opcode. */
/* 398 */     OP_vcvt_f64_f32,       /**< ARM vcvt_f64_f32 opcode. */
/* 399 */     OP_vcvt_f64_s16,       /**< ARM vcvt_f64_s16 opcode. */
/* 400 */     OP_vcvt_f64_s32,       /**< ARM vcvt_f64_s32 opcode. */
/* 401 */     OP_vcvt_f64_u16,       /**< ARM vcvt_f64_u16 opcode. */
/* 402 */     OP_vcvt_f64_u32,       /**< ARM vcvt_f64_u32 opcode. */
/* 403 */     OP_vcvt_s16_f32,       /**< ARM vcvt_s16_f32 opcode. */
/* 404 */     OP_vcvt_s16_f64,       /**< ARM vcvt_s16_f64 opcode. */
/* 405 */     OP_vcvt_s32_f32,       /**< ARM vcvt_s32_f32 opcode. */
/* 406 */     OP_vcvt_s32_f64,       /**< ARM vcvt_s32_f64 opcode. */
/* 407 */     OP_vcvt_u16_f32,       /**< ARM vcvt_u16_f32 opcode. */
/* 408 */     OP_vcvt_u16_f64,       /**< ARM vcvt_u16_f64 opcode. */
/* 409 */     OP_vcvt_u32_f32,       /**< ARM vcvt_u32_f32 opcode. */
/* 410 */     OP_vcvt_u32_f64,       /**< ARM vcvt_u32_f64 opcode. */
/* 411 */     OP_vcvta_s32_f32,      /**< ARM vcvta_s32_f32 opcode. */
/* 412 */     OP_vcvta_s32_f64,      /**< ARM vcvta_s32_f64 opcode. */
/* 413 */     OP_vcvta_u32_f32,      /**< ARM vcvta_u32_f32 opcode. */
/* 414 */     OP_vcvta_u32_f64,      /**< ARM vcvta_u32_f64 opcode. */
/* 415 */     OP_vcvtb_f16_f32,      /**< ARM vcvtb_f16_f32 opcode. */
/* 416 */     OP_vcvtb_f16_f64,      /**< ARM vcvtb_f16_f64 opcode. */
/* 417 */     OP_vcvtb_f32_f16,      /**< ARM vcvtb_f32_f16 opcode. */
/* 418 */     OP_vcvtb_f64_f16,      /**< ARM vcvtb_f64_f16 opcode. */
/* 419 */     OP_vcvtm_s32_f32,      /**< ARM vcvtm_s32_f32 opcode. */
/* 420 */     OP_vcvtm_s32_f64,      /**< ARM vcvtm_s32_f64 opcode. */
/* 421 */     OP_vcvtm_u32_f32,      /**< ARM vcvtm_u32_f32 opcode. */
/* 422 */     OP_vcvtm_u32_f64,      /**< ARM vcvtm_u32_f64 opcode. */
/* 423 */     OP_vcvtn_s32_f32,      /**< ARM vcvtn_s32_f32 opcode. */
/* 424 */     OP_vcvtn_s32_f64,      /**< ARM vcvtn_s32_f64 opcode. */
/* 425 */     OP_vcvtn_u32_f32,      /**< ARM vcvtn_u32_f32 opcode. */
/* 426 */     OP_vcvtn_u32_f64,      /**< ARM vcvtn_u32_f64 opcode. */
/* 427 */     OP_vcvtp_s32_f32,      /**< ARM vcvtp_s32_f32 opcode. */
/* 428 */     OP_vcvtp_s32_f64,      /**< ARM vcvtp_s32_f64 opcode. */
/* 429 */     OP_vcvtp_u32_f32,      /**< ARM vcvtp_u32_f32 opcode. */
/* 430 */     OP_vcvtp_u32_f64,      /**< ARM vcvtp_u32_f64 opcode. */
/* 431 */     OP_vcvtr_s32_f32,      /**< ARM vcvtr_s32_f32 opcode. */
/* 432 */     OP_vcvtr_s32_f64,      /**< ARM vcvtr_s32_f64 opcode. */
/* 433 */     OP_vcvtr_u32_f32,      /**< ARM vcvtr_u32_f32 opcode. */
/* 434 */     OP_vcvtr_u32_f64,      /**< ARM vcvtr_u32_f64 opcode. */
/* 435 */     OP_vcvtt_f16_f32,      /**< ARM vcvtt_f16_f32 opcode. */
/* 436 */     OP_vcvtt_f16_f64,      /**< ARM vcvtt_f16_f64 opcode. */
/* 437 */     OP_vcvtt_f32_f16,      /**< ARM vcvtt_f32_f16 opcode. */
/* 438 */     OP_vcvtt_f64_f16,      /**< ARM vcvtt_f64_f16 opcode. */
/* 439 */     OP_vdiv_f32,           /**< ARM vdiv_f32 opcode. */
/* 440 */     OP_vdiv_f64,           /**< ARM vdiv_f64 opcode. */
/* 441 */     OP_vdup_16,            /**< ARM vdup_16 opcode. */
/* 442 */     OP_vdup_32,            /**< ARM vdup_32 opcode. */
/* 443 */     OP_vdup_8,             /**< ARM vdup_8 opcode. */
/* 444 */     OP_veor,               /**< ARM veor opcode. */
/* 445 */     OP_vext,               /**< ARM vext opcode. */
/* 446 */     OP_vfma_f32,           /**< ARM vfma_f32 opcode. */
/* 447 */     OP_vfma_f64,           /**< ARM vfma_f64 opcode. */
/* 448 */     OP_vfms_f32,           /**< ARM vfms_f32 opcode. */
/* 449 */     OP_vfms_f64,           /**< ARM vfms_f64 opcode. */
/* 450 */     OP_vfnma_f32,          /**< ARM vfnma_f32 opcode. */
/* 451 */     OP_vfnma_f64,          /**< ARM vfnma_f64 opcode. */
/* 452 */     OP_vfnms_f32,          /**< ARM vfnms_f32 opcode. */
/* 453 */     OP_vfnms_f64,          /**< ARM vfnms_f64 opcode. */
/* 454 */     OP_vhadd_s16,          /**< ARM vhadd_s16 opcode. */
/* 455 */     OP_vhadd_s32,          /**< ARM vhadd_s32 opcode. */
/* 456 */     OP_vhadd_s8,           /**< ARM vhadd_s8 opcode. */
/* 457 */     OP_vhadd_u16,          /**< ARM vhadd_u16 opcode. */
/* 458 */     OP_vhadd_u32,          /**< ARM vhadd_u32 opcode. */
/* 459 */     OP_vhadd_u8,           /**< ARM vhadd_u8 opcode. */
/* 460 */     OP_vhsub_s16,          /**< ARM vhsub_s16 opcode. */
/* 461 */     OP_vhsub_s32,          /**< ARM vhsub_s32 opcode. */
/* 462 */     OP_vhsub_s8,           /**< ARM vhsub_s8 opcode. */
/* 463 */     OP_vhsub_u16,          /**< ARM vhsub_u16 opcode. */
/* 464 */     OP_vhsub_u32,          /**< ARM vhsub_u32 opcode. */
/* 465 */     OP_vhsub_u8,           /**< ARM vhsub_u8 opcode. */
/* 466 */     OP_vld1_16,            /**< ARM vld1_16 opcode. */
/* 467 */     OP_vld1_32,            /**< ARM vld1_32 opcode. */
/* 468 */     OP_vld1_64,            /**< ARM vld1_64 opcode. */
/* 469 */     OP_vld1_8,             /**< ARM vld1_8 opcode. */
/* 470 */     OP_vld1_dup_16,        /**< ARM vld1_dup_16 opcode. */
/* 471 */     OP_vld1_dup_32,        /**< ARM vld1_dup_32 opcode. */
/* 472 */     OP_vld1_dup_8,         /**< ARM vld1_dup_8 opcode. */
/* 473 */     OP_vld1_lane_16,       /**< ARM vld1_lane_16 opcode. */
/* 474 */     OP_vld1_lane_32,       /**< ARM vld1_lane_32 opcode. */
/* 475 */     OP_vld1_lane_8,        /**< ARM vld1_lane_8 opcode. */
/* 476 */     OP_vld2_16,            /**< ARM vld2_16 opcode. */
/* 477 */     OP_vld2_32,            /**< ARM vld2_32 opcode. */
/* 478 */     OP_vld2_8,             /**< ARM vld2_8 opcode. */
/* 479 */     OP_vld2_dup_16,        /**< ARM vld2_dup_16 opcode. */
/* 480 */     OP_vld2_dup_32,        /**< ARM vld2_dup_32 opcode. */
/* 481 */     OP_vld2_dup_8,         /**< ARM vld2_dup_8 opcode. */
/* 482 */     OP_vld2_lane_16,       /**< ARM vld2_lane_16 opcode. */
/* 483 */     OP_vld2_lane_32,       /**< ARM vld2_lane_32 opcode. */
/* 484 */     OP_vld2_lane_8,        /**< ARM vld2_lane_8 opcode. */
/* 485 */     OP_vld3_16,            /**< ARM vld3_16 opcode. */
/* 486 */     OP_vld3_32,            /**< ARM vld3_32 opcode. */
/* 487 */     OP_vld3_8,             /**< ARM vld3_8 opcode. */
/* 488 */     OP_vld3_dup_16,        /**< ARM vld3_dup_16 opcode. */
/* 489 */     OP_vld3_dup_32,        /**< ARM vld3_dup_32 opcode. */
/* 490 */     OP_vld3_dup_8,         /**< ARM vld3_dup_8 opcode. */
/* 491 */     OP_vld3_lane_16,       /**< ARM vld3_lane_16 opcode. */
/* 492 */     OP_vld3_lane_32,       /**< ARM vld3_lane_32 opcode. */
/* 493 */     OP_vld3_lane_8,        /**< ARM vld3_lane_8 opcode. */
/* 494 */     OP_vld4_16,            /**< ARM vld4_16 opcode. */
/* 495 */     OP_vld4_32,            /**< ARM vld4_32 opcode. */
/* 496 */     OP_vld4_8,             /**< ARM vld4_8 opcode. */
/* 497 */     OP_vld4_dup_16,        /**< ARM vld4_dup_16 opcode. */
/* 498 */     OP_vld4_dup_32,        /**< ARM vld4_dup_32 opcode. */
/* 499 */     OP_vld4_dup_8,         /**< ARM vld4_dup_8 opcode. */
/* 500 */     OP_vld4_lane_16,       /**< ARM vld4_lane_16 opcode. */
/* 501 */     OP_vld4_lane_32,       /**< ARM vld4_lane_32 opcode. */
/* 502 */     OP_vld4_lane_8,        /**< ARM vld4_lane_8 opcode. */
/* 503 */     OP_vldmdb,             /**< ARM vldmdb opcode. */
/* 504 */     OP_vldmia,             /**< ARM vldmia opcode. */
/* 505 */     OP_vldr,               /**< ARM vldr opcode. */
/* 506 */     OP_vmax_f32,           /**< ARM vmax_f32 opcode. */
/* 507 */     OP_vmax_s16,           /**< ARM vmax_s16 opcode. */
/* 508 */     OP_vmax_s32,           /**< ARM vmax_s32 opcode. */
/* 509 */     OP_vmax_s8,            /**< ARM vmax_s8 opcode. */
/* 510 */     OP_vmax_u16,           /**< ARM vmax_u16 opcode. */
/* 511 */     OP_vmax_u32,           /**< ARM vmax_u32 opcode. */
/* 512 */     OP_vmax_u8,            /**< ARM vmax_u8 opcode. */
/* 513 */     OP_vmaxnm_f32,         /**< ARM vmaxnm_f32 opcode. */
/* 514 */     OP_vmaxnm_f64,         /**< ARM vmaxnm_f64 opcode. */
/* 515 */     OP_vmin_f32,           /**< ARM vmin_f32 opcode. */
/* 516 */     OP_vmin_s16,           /**< ARM vmin_s16 opcode. */
/* 517 */     OP_vmin_s32,           /**< ARM vmin_s32 opcode. */
/* 518 */     OP_vmin_s8,            /**< ARM vmin_s8 opcode. */
/* 519 */     OP_vmin_u16,           /**< ARM vmin_u16 opcode. */
/* 520 */     OP_vmin_u32,           /**< ARM vmin_u32 opcode. */
/* 521 */     OP_vmin_u8,            /**< ARM vmin_u8 opcode. */
/* 522 */     OP_vminnm_f32,         /**< ARM vminnm_f32 opcode. */
/* 523 */     OP_vminnm_f64,         /**< ARM vminnm_f64 opcode. */
/* 524 */     OP_vmla_f32,           /**< ARM vmla_f32 opcode. */
/* 525 */     OP_vmla_f64,           /**< ARM vmla_f64 opcode. */
/* 526 */     OP_vmla_i16,           /**< ARM vmla_i16 opcode. */
/* 527 */     OP_vmla_i32,           /**< ARM vmla_i32 opcode. */
/* 528 */     OP_vmla_i8,            /**< ARM vmla_i8 opcode. */
/* 529 */     OP_vmlal_s16,          /**< ARM vmlal_s16 opcode. */
/* 530 */     OP_vmlal_s32,          /**< ARM vmlal_s32 opcode. */
/* 531 */     OP_vmlal_s8,           /**< ARM vmlal_s8 opcode. */
/* 532 */     OP_vmlal_u16,          /**< ARM vmlal_u16 opcode. */
/* 533 */     OP_vmlal_u32,          /**< ARM vmlal_u32 opcode. */
/* 534 */     OP_vmlal_u8,           /**< ARM vmlal_u8 opcode. */
/* 535 */     OP_vmls_f32,           /**< ARM vmls_f32 opcode. */
/* 536 */     OP_vmls_f64,           /**< ARM vmls_f64 opcode. */
/* 537 */     OP_vmls_i16,           /**< ARM vmls_i16 opcode. */
/* 538 */     OP_vmls_i32,           /**< ARM vmls_i32 opcode. */
/* 539 */     OP_vmls_i8,            /**< ARM vmls_i8 opcode. */
/* 540 */     OP_vmlsl_s16,          /**< ARM vmlsl_s16 opcode. */
/* 541 */     OP_vmlsl_s32,          /**< ARM vmlsl_s32 opcode. */
/* 542 */     OP_vmlsl_s8,           /**< ARM vmlsl_s8 opcode. */
/* 543 */     OP_vmlsl_u16,          /**< ARM vmlsl_u16 opcode. */
/* 544 */     OP_vmlsl_u32,          /**< ARM vmlsl_u32 opcode. */
/* 545 */     OP_vmlsl_u8,           /**< ARM vmlsl_u8 opcode. */
/* 546 */     OP_vmov,               /**< ARM vmov opcode. */
/* 547 */     OP_vmov_16,            /**< ARM vmov_16 opcode. */
/* 548 */     OP_vmov_32,            /**< ARM vmov_32 opcode. */
/* 549 */     OP_vmov_8,             /**< ARM vmov_8 opcode. */
/* 550 */     OP_vmov_f32,           /**< ARM vmov_f32 opcode. */
/* 551 */     OP_vmov_f64,           /**< ARM vmov_f64 opcode. */
/* 552 */     OP_vmov_i16,           /**< ARM vmov_i16 opcode. */
/* 553 */     OP_vmov_i32,           /**< ARM vmov_i32 opcode. */
/* 554 */     OP_vmov_i64,           /**< ARM vmov_i64 opcode. */
/* 555 */     OP_vmov_i8,            /**< ARM vmov_i8 opcode. */
/* 556 */     OP_vmov_s16,           /**< ARM vmov_s16 opcode. */
/* 557 */     OP_vmov_s8,            /**< ARM vmov_s8 opcode. */
/* 558 */     OP_vmov_u16,           /**< ARM vmov_u16 opcode. */
/* 559 */     OP_vmov_u8,            /**< ARM vmov_u8 opcode. */
/* 560 */     OP_vmovl_s16,          /**< ARM vmovl_s16 opcode. */
/* 561 */     OP_vmovl_s32,          /**< ARM vmovl_s32 opcode. */
/* 562 */     OP_vmovl_s8,           /**< ARM vmovl_s8 opcode. */
/* 563 */     OP_vmovl_u16,          /**< ARM vmovl_u16 opcode. */
/* 564 */     OP_vmovl_u32,          /**< ARM vmovl_u32 opcode. */
/* 565 */     OP_vmovl_u8,           /**< ARM vmovl_u8 opcode. */
/* 566 */     OP_vmovn_i16,          /**< ARM vmovn_i16 opcode. */
/* 567 */     OP_vmovn_i32,          /**< ARM vmovn_i32 opcode. */
/* 568 */     OP_vmovn_i64,          /**< ARM vmovn_i64 opcode. */
/* 569 */     OP_vmrs,               /**< ARM vmrs opcode. */
/* 570 */     OP_vmsr,               /**< ARM vmsr opcode. */
/* 571 */     OP_vmul_f32,           /**< ARM vmul_f32 opcode. */
/* 572 */     OP_vmul_f64,           /**< ARM vmul_f64 opcode. */
/* 573 */     OP_vmul_i16,           /**< ARM vmul_i16 opcode. */
/* 574 */     OP_vmul_i32,           /**< ARM vmul_i32 opcode. */
/* 575 */     OP_vmul_i8,            /**< ARM vmul_i8 opcode. */
/* 576 */     OP_vmul_p32,           /**< ARM vmul_p32 opcode. */
/* 577 */     OP_vmul_p8,            /**< ARM vmul_p8 opcode. */
/* 578 */     OP_vmull_p32,          /**< ARM vmull_p32 opcode. */
/* 579 */     OP_vmull_p8,           /**< ARM vmull_p8 opcode. */
/* 580 */     OP_vmull_s16,          /**< ARM vmull_s16 opcode. */
/* 581 */     OP_vmull_s32,          /**< ARM vmull_s32 opcode. */
/* 582 */     OP_vmull_s8,           /**< ARM vmull_s8 opcode. */
/* 583 */     OP_vmull_u16,          /**< ARM vmull_u16 opcode. */
/* 584 */     OP_vmull_u32,          /**< ARM vmull_u32 opcode. */
/* 585 */     OP_vmull_u8,           /**< ARM vmull_u8 opcode. */
/* 586 */     OP_vmvn,               /**< ARM vmvn opcode. */
/* 587 */     OP_vmvn_i16,           /**< ARM vmvn_i16 opcode. */
/* 588 */     OP_vmvn_i32,           /**< ARM vmvn_i32 opcode. */
/* 589 */     OP_vneg_f32,           /**< ARM vneg_f32 opcode. */
/* 590 */     OP_vneg_f64,           /**< ARM vneg_f64 opcode. */
/* 591 */     OP_vneg_s16,           /**< ARM vneg_s16 opcode. */
/* 592 */     OP_vneg_s32,           /**< ARM vneg_s32 opcode. */
/* 593 */     OP_vneg_s8,            /**< ARM vneg_s8 opcode. */
/* 594 */     OP_vnmla_f32,          /**< ARM vnmla_f32 opcode. */
/* 595 */     OP_vnmla_f64,          /**< ARM vnmla_f64 opcode. */
/* 596 */     OP_vnmls_f32,          /**< ARM vnmls_f32 opcode. */
/* 597 */     OP_vnmls_f64,          /**< ARM vnmls_f64 opcode. */
/* 598 */     OP_vnmul_f32,          /**< ARM vnmul_f32 opcode. */
/* 599 */     OP_vnmul_f64,          /**< ARM vnmul_f64 opcode. */
/* 600 */     OP_vorn,               /**< ARM vorn opcode. */
/* 601 */     OP_vorr,               /**< ARM vorr opcode. */
/* 602 */     OP_vorr_i16,           /**< ARM vorr_i16 opcode. */
/* 603 */     OP_vorr_i32,           /**< ARM vorr_i32 opcode. */
/* 604 */     OP_vpadal_s16,         /**< ARM vpadal_s16 opcode. */
/* 605 */     OP_vpadal_s32,         /**< ARM vpadal_s32 opcode. */
/* 606 */     OP_vpadal_s8,          /**< ARM vpadal_s8 opcode. */
/* 607 */     OP_vpadal_u16,         /**< ARM vpadal_u16 opcode. */
/* 608 */     OP_vpadal_u32,         /**< ARM vpadal_u32 opcode. */
/* 609 */     OP_vpadal_u8,          /**< ARM vpadal_u8 opcode. */
/* 610 */     OP_vpadd_f32,          /**< ARM vpadd_f32 opcode. */
/* 611 */     OP_vpadd_i16,          /**< ARM vpadd_i16 opcode. */
/* 612 */     OP_vpadd_i32,          /**< ARM vpadd_i32 opcode. */
/* 613 */     OP_vpadd_i8,           /**< ARM vpadd_i8 opcode. */
/* 614 */     OP_vpaddl_s16,         /**< ARM vpaddl_s16 opcode. */
/* 615 */     OP_vpaddl_s32,         /**< ARM vpaddl_s32 opcode. */
/* 616 */     OP_vpaddl_s8,          /**< ARM vpaddl_s8 opcode. */
/* 617 */     OP_vpaddl_u16,         /**< ARM vpaddl_u16 opcode. */
/* 618 */     OP_vpaddl_u32,         /**< ARM vpaddl_u32 opcode. */
/* 619 */     OP_vpaddl_u8,          /**< ARM vpaddl_u8 opcode. */
/* 620 */     OP_vpmax_f32,          /**< ARM vpmax_f32 opcode. */
/* 621 */     OP_vpmax_s16,          /**< ARM vpmax_s16 opcode. */
/* 622 */     OP_vpmax_s32,          /**< ARM vpmax_s32 opcode. */
/* 623 */     OP_vpmax_s8,           /**< ARM vpmax_s8 opcode. */
/* 624 */     OP_vpmax_u16,          /**< ARM vpmax_u16 opcode. */
/* 625 */     OP_vpmax_u32,          /**< ARM vpmax_u32 opcode. */
/* 626 */     OP_vpmax_u8,           /**< ARM vpmax_u8 opcode. */
/* 627 */     OP_vpmin_f32,          /**< ARM vpmin_f32 opcode. */
/* 628 */     OP_vpmin_s16,          /**< ARM vpmin_s16 opcode. */
/* 629 */     OP_vpmin_s32,          /**< ARM vpmin_s32 opcode. */
/* 630 */     OP_vpmin_s8,           /**< ARM vpmin_s8 opcode. */
/* 631 */     OP_vpmin_u16,          /**< ARM vpmin_u16 opcode. */
/* 632 */     OP_vpmin_u32,          /**< ARM vpmin_u32 opcode. */
/* 633 */     OP_vpmin_u8,           /**< ARM vpmin_u8 opcode. */
/* 634 */     OP_vqabs_s16,          /**< ARM vqabs_s16 opcode. */
/* 635 */     OP_vqabs_s32,          /**< ARM vqabs_s32 opcode. */
/* 636 */     OP_vqabs_s8,           /**< ARM vqabs_s8 opcode. */
/* 637 */     OP_vqadd_s16,          /**< ARM vqadd_s16 opcode. */
/* 638 */     OP_vqadd_s32,          /**< ARM vqadd_s32 opcode. */
/* 639 */     OP_vqadd_s64,          /**< ARM vqadd_s64 opcode. */
/* 640 */     OP_vqadd_s8,           /**< ARM vqadd_s8 opcode. */
/* 641 */     OP_vqadd_u16,          /**< ARM vqadd_u16 opcode. */
/* 642 */     OP_vqadd_u32,          /**< ARM vqadd_u32 opcode. */
/* 643 */     OP_vqadd_u64,          /**< ARM vqadd_u64 opcode. */
/* 644 */     OP_vqadd_u8,           /**< ARM vqadd_u8 opcode. */
/* 645 */     OP_vqdmlal_s16,        /**< ARM vqdmlal_s16 opcode. */
/* 646 */     OP_vqdmlal_s32,        /**< ARM vqdmlal_s32 opcode. */
/* 647 */     OP_vqdmlsl_s16,        /**< ARM vqdmlsl_s16 opcode. */
/* 648 */     OP_vqdmlsl_s32,        /**< ARM vqdmlsl_s32 opcode. */
/* 649 */     OP_vqdmulh_s16,        /**< ARM vqdmulh_s16 opcode. */
/* 650 */     OP_vqdmulh_s32,        /**< ARM vqdmulh_s32 opcode. */
/* 651 */     OP_vqdmull_s16,        /**< ARM vqdmull_s16 opcode. */
/* 652 */     OP_vqdmull_s32,        /**< ARM vqdmull_s32 opcode. */
/* 653 */     OP_vqmovn_s16,         /**< ARM vqmovn_s16 opcode. */
/* 654 */     OP_vqmovn_s32,         /**< ARM vqmovn_s32 opcode. */
/* 655 */     OP_vqmovn_s64,         /**< ARM vqmovn_s64 opcode. */
/* 656 */     OP_vqmovn_u16,         /**< ARM vqmovn_u16 opcode. */
/* 657 */     OP_vqmovn_u32,         /**< ARM vqmovn_u32 opcode. */
/* 658 */     OP_vqmovn_u64,         /**< ARM vqmovn_u64 opcode. */
/* 659 */     OP_vqmovun_s16,        /**< ARM vqmovun_s16 opcode. */
/* 660 */     OP_vqmovun_s32,        /**< ARM vqmovun_s32 opcode. */
/* 661 */     OP_vqmovun_s64,        /**< ARM vqmovun_s64 opcode. */
/* 662 */     OP_vqneg_s16,          /**< ARM vqneg_s16 opcode. */
/* 663 */     OP_vqneg_s32,          /**< ARM vqneg_s32 opcode. */
/* 664 */     OP_vqneg_s8,           /**< ARM vqneg_s8 opcode. */
/* 665 */     OP_vqrdmulh_s16,       /**< ARM vqrdmulh_s16 opcode. */
/* 666 */     OP_vqrdmulh_s32,       /**< ARM vqrdmulh_s32 opcode. */
/* 667 */     OP_vqrshl_s16,         /**< ARM vqrshl_s16 opcode. */
/* 668 */     OP_vqrshl_s32,         /**< ARM vqrshl_s32 opcode. */
/* 669 */     OP_vqrshl_s64,         /**< ARM vqrshl_s64 opcode. */
/* 670 */     OP_vqrshl_s8,          /**< ARM vqrshl_s8 opcode. */
/* 671 */     OP_vqrshl_u16,         /**< ARM vqrshl_u16 opcode. */
/* 672 */     OP_vqrshl_u32,         /**< ARM vqrshl_u32 opcode. */
/* 673 */     OP_vqrshl_u64,         /**< ARM vqrshl_u64 opcode. */
/* 674 */     OP_vqrshl_u8,          /**< ARM vqrshl_u8 opcode. */
/* 675 */     OP_vqrshrn_s16,        /**< ARM vqrshrn_s16 opcode. */
/* 676 */     OP_vqrshrn_s32,        /**< ARM vqrshrn_s32 opcode. */
/* 677 */     OP_vqrshrn_s64,        /**< ARM vqrshrn_s64 opcode. */
/* 678 */     OP_vqrshrn_u16,        /**< ARM vqrshrn_u16 opcode. */
/* 679 */     OP_vqrshrn_u32,        /**< ARM vqrshrn_u32 opcode. */
/* 680 */     OP_vqrshrn_u64,        /**< ARM vqrshrn_u64 opcode. */
/* 681 */     OP_vqrshrun_s16,       /**< ARM vqrshrun_s16 opcode. */
/* 682 */     OP_vqrshrun_s32,       /**< ARM vqrshrun_s32 opcode. */
/* 683 */     OP_vqrshrun_s64,       /**< ARM vqrshrun_s64 opcode. */
/* 684 */     OP_vqshl_s16,          /**< ARM vqshl_s16 opcode. */
/* 685 */     OP_vqshl_s32,          /**< ARM vqshl_s32 opcode. */
/* 686 */     OP_vqshl_s64,          /**< ARM vqshl_s64 opcode. */
/* 687 */     OP_vqshl_s8,           /**< ARM vqshl_s8 opcode. */
/* 688 */     OP_vqshl_u16,          /**< ARM vqshl_u16 opcode. */
/* 689 */     OP_vqshl_u32,          /**< ARM vqshl_u32 opcode. */
/* 690 */     OP_vqshl_u64,          /**< ARM vqshl_u64 opcode. */
/* 691 */     OP_vqshl_u8,           /**< ARM vqshl_u8 opcode. */
/* 692 */     OP_vqshlu_s16,         /**< ARM vqshlu_s16 opcode. */
/* 693 */     OP_vqshlu_s32,         /**< ARM vqshlu_s32 opcode. */
/* 694 */     OP_vqshlu_s64,         /**< ARM vqshlu_s64 opcode. */
/* 695 */     OP_vqshlu_s8,          /**< ARM vqshlu_s8 opcode. */
/* 696 */     OP_vqshrn_s16,         /**< ARM vqshrn_s16 opcode. */
/* 697 */     OP_vqshrn_s32,         /**< ARM vqshrn_s32 opcode. */
/* 698 */     OP_vqshrn_s64,         /**< ARM vqshrn_s64 opcode. */
/* 699 */     OP_vqshrn_u16,         /**< ARM vqshrn_u16 opcode. */
/* 700 */     OP_vqshrn_u32,         /**< ARM vqshrn_u32 opcode. */
/* 701 */     OP_vqshrn_u64,         /**< ARM vqshrn_u64 opcode. */
/* 702 */     OP_vqshrun_s16,        /**< ARM vqshrun_s16 opcode. */
/* 703 */     OP_vqshrun_s32,        /**< ARM vqshrun_s32 opcode. */
/* 704 */     OP_vqshrun_s64,        /**< ARM vqshrun_s64 opcode. */
/* 705 */     OP_vqsub_s16,          /**< ARM vqsub_s16 opcode. */
/* 706 */     OP_vqsub_s32,          /**< ARM vqsub_s32 opcode. */
/* 707 */     OP_vqsub_s64,          /**< ARM vqsub_s64 opcode. */
/* 708 */     OP_vqsub_s8,           /**< ARM vqsub_s8 opcode. */
/* 709 */     OP_vqsub_u16,          /**< ARM vqsub_u16 opcode. */
/* 710 */     OP_vqsub_u32,          /**< ARM vqsub_u32 opcode. */
/* 711 */     OP_vqsub_u64,          /**< ARM vqsub_u64 opcode. */
/* 712 */     OP_vqsub_u8,           /**< ARM vqsub_u8 opcode. */
/* 713 */     OP_vraddhn_i16,        /**< ARM vraddhn_i16 opcode. */
/* 714 */     OP_vraddhn_i32,        /**< ARM vraddhn_i32 opcode. */
/* 715 */     OP_vraddhn_i64,        /**< ARM vraddhn_i64 opcode. */
/* 716 */     OP_vrecpe_f32,         /**< ARM vrecpe_f32 opcode. */
/* 717 */     OP_vrecpe_u32,         /**< ARM vrecpe_u32 opcode. */
/* 718 */     OP_vrecps_f32,         /**< ARM vrecps_f32 opcode. */
/* 719 */     OP_vrev16_16,          /**< ARM vrev16_16 opcode. */
/* 720 */     OP_vrev16_8,           /**< ARM vrev16_8 opcode. */
/* 721 */     OP_vrev32_16,          /**< ARM vrev32_16 opcode. */
/* 722 */     OP_vrev32_32,          /**< ARM vrev32_32 opcode. */
/* 723 */     OP_vrev32_8,           /**< ARM vrev32_8 opcode. */
/* 724 */     OP_vrev64_16,          /**< ARM vrev64_16 opcode. */
/* 725 */     OP_vrev64_32,          /**< ARM vrev64_32 opcode. */
/* 726 */     OP_vrev64_8,           /**< ARM vrev64_8 opcode. */
/* 727 */     OP_vrhadd_s16,         /**< ARM vrhadd_s16 opcode. */
/* 728 */     OP_vrhadd_s32,         /**< ARM vrhadd_s32 opcode. */
/* 729 */     OP_vrhadd_s8,          /**< ARM vrhadd_s8 opcode. */
/* 730 */     OP_vrhadd_u16,         /**< ARM vrhadd_u16 opcode. */
/* 731 */     OP_vrhadd_u32,         /**< ARM vrhadd_u32 opcode. */
/* 732 */     OP_vrhadd_u8,          /**< ARM vrhadd_u8 opcode. */
/* 733 */     OP_vrinta_f32_f32,     /**< ARM vrinta_f32_f32 opcode. */
/* 734 */     OP_vrinta_f64_f64,     /**< ARM vrinta_f64_f64 opcode. */
/* 735 */     OP_vrintm_f32_f32,     /**< ARM vrintm_f32_f32 opcode. */
/* 736 */     OP_vrintm_f64_f64,     /**< ARM vrintm_f64_f64 opcode. */
/* 737 */     OP_vrintn_f32_f32,     /**< ARM vrintn_f32_f32 opcode. */
/* 738 */     OP_vrintn_f64_f64,     /**< ARM vrintn_f64_f64 opcode. */
/* 739 */     OP_vrintp_f32_f32,     /**< ARM vrintp_f32_f32 opcode. */
/* 740 */     OP_vrintp_f64_f64,     /**< ARM vrintp_f64_f64 opcode. */
/* 741 */     OP_vrintr_f32,         /**< ARM vrintr_f32 opcode. */
/* 742 */     OP_vrintr_f64,         /**< ARM vrintr_f64 opcode. */
/* 743 */     OP_vrintx_f32,         /**< ARM vrintx_f32 opcode. */
/* 744 */     OP_vrintx_f32_f32,     /**< ARM vrintx_f32_f32 opcode. */
/* 745 */     OP_vrintx_f64,         /**< ARM vrintx_f64 opcode. */
/* 746 */     OP_vrintz_f32,         /**< ARM vrintz_f32 opcode. */
/* 747 */     OP_vrintz_f32_f32,     /**< ARM vrintz_f32_f32 opcode. */
/* 748 */     OP_vrintz_f64,         /**< ARM vrintz_f64 opcode. */
/* 749 */     OP_vrshl_s16,          /**< ARM vrshl_s16 opcode. */
/* 750 */     OP_vrshl_s32,          /**< ARM vrshl_s32 opcode. */
/* 751 */     OP_vrshl_s64,          /**< ARM vrshl_s64 opcode. */
/* 752 */     OP_vrshl_s8,           /**< ARM vrshl_s8 opcode. */
/* 753 */     OP_vrshl_u16,          /**< ARM vrshl_u16 opcode. */
/* 754 */     OP_vrshl_u32,          /**< ARM vrshl_u32 opcode. */
/* 755 */     OP_vrshl_u64,          /**< ARM vrshl_u64 opcode. */
/* 756 */     OP_vrshl_u8,           /**< ARM vrshl_u8 opcode. */
/* 757 */     OP_vrshr_s16,          /**< ARM vrshr_s16 opcode. */
/* 758 */     OP_vrshr_s32,          /**< ARM vrshr_s32 opcode. */
/* 759 */     OP_vrshr_s64,          /**< ARM vrshr_s64 opcode. */
/* 760 */     OP_vrshr_s8,           /**< ARM vrshr_s8 opcode. */
/* 761 */     OP_vrshr_u16,          /**< ARM vrshr_u16 opcode. */
/* 762 */     OP_vrshr_u32,          /**< ARM vrshr_u32 opcode. */
/* 763 */     OP_vrshr_u64,          /**< ARM vrshr_u64 opcode. */
/* 764 */     OP_vrshr_u8,           /**< ARM vrshr_u8 opcode. */
/* 765 */     OP_vrshrn_i16,         /**< ARM vrshrn_i16 opcode. */
/* 766 */     OP_vrshrn_i32,         /**< ARM vrshrn_i32 opcode. */
/* 767 */     OP_vrshrn_i8,          /**< ARM vrshrn_i8 opcode. */
/* 768 */     OP_vrsqrte_f32,        /**< ARM vrsqrte_f32 opcode. */
/* 769 */     OP_vrsqrte_u32,        /**< ARM vrsqrte_u32 opcode. */
/* 770 */     OP_vrsqrts_f32,        /**< ARM vrsqrts_f32 opcode. */
/* 771 */     OP_vrsra_s16,          /**< ARM vrsra_s16 opcode. */
/* 772 */     OP_vrsra_s32,          /**< ARM vrsra_s32 opcode. */
/* 773 */     OP_vrsra_s64,          /**< ARM vrsra_s64 opcode. */
/* 774 */     OP_vrsra_s8,           /**< ARM vrsra_s8 opcode. */
/* 775 */     OP_vrsra_u16,          /**< ARM vrsra_u16 opcode. */
/* 776 */     OP_vrsra_u32,          /**< ARM vrsra_u32 opcode. */
/* 777 */     OP_vrsra_u64,          /**< ARM vrsra_u64 opcode. */
/* 778 */     OP_vrsra_u8,           /**< ARM vrsra_u8 opcode. */
/* 779 */     OP_vrsubhn_i16,        /**< ARM vrsubhn_i16 opcode. */
/* 780 */     OP_vrsubhn_i32,        /**< ARM vrsubhn_i32 opcode. */
/* 781 */     OP_vrsubhn_i64,        /**< ARM vrsubhn_i64 opcode. */
/* 782 */     OP_vsel_eq_f32,        /**< ARM vsel_eq_f32 opcode. */
/* 783 */     OP_vsel_eq_f64,        /**< ARM vsel_eq_f64 opcode. */
/* 784 */     OP_vsel_ge_f32,        /**< ARM vsel_ge_f32 opcode. */
/* 785 */     OP_vsel_ge_f64,        /**< ARM vsel_ge_f64 opcode. */
/* 786 */     OP_vsel_gt_f32,        /**< ARM vsel_gt_f32 opcode. */
/* 787 */     OP_vsel_gt_f64,        /**< ARM vsel_gt_f64 opcode. */
/* 788 */     OP_vsel_vs_f32,        /**< ARM vsel_vs_f32 opcode. */
/* 789 */     OP_vsel_vs_f64,        /**< ARM vsel_vs_f64 opcode. */
/* 790 */     OP_vshl_i16,           /**< ARM vshl_i16 opcode. */
/* 791 */     OP_vshl_i32,           /**< ARM vshl_i32 opcode. */
/* 792 */     OP_vshl_i64,           /**< ARM vshl_i64 opcode. */
/* 793 */     OP_vshl_i8,            /**< ARM vshl_i8 opcode. */
/* 794 */     OP_vshl_s16,           /**< ARM vshl_s16 opcode. */
/* 795 */     OP_vshl_s32,           /**< ARM vshl_s32 opcode. */
/* 796 */     OP_vshl_s64,           /**< ARM vshl_s64 opcode. */
/* 797 */     OP_vshl_s8,            /**< ARM vshl_s8 opcode. */
/* 798 */     OP_vshl_u16,           /**< ARM vshl_u16 opcode. */
/* 799 */     OP_vshl_u32,           /**< ARM vshl_u32 opcode. */
/* 800 */     OP_vshl_u64,           /**< ARM vshl_u64 opcode. */
/* 801 */     OP_vshl_u8,            /**< ARM vshl_u8 opcode. */
/* 802 */     OP_vshll_i16,          /**< ARM vshll_i16 opcode. */
/* 803 */     OP_vshll_i32,          /**< ARM vshll_i32 opcode. */
/* 804 */     OP_vshll_i8,           /**< ARM vshll_i8 opcode. */
/* 805 */     OP_vshll_s16,          /**< ARM vshll_s16 opcode. */
/* 806 */     OP_vshll_s32,          /**< ARM vshll_s32 opcode. */
/* 807 */     OP_vshll_s8,           /**< ARM vshll_s8 opcode. */
/* 808 */     OP_vshll_u16,          /**< ARM vshll_u16 opcode. */
/* 809 */     OP_vshll_u32,          /**< ARM vshll_u32 opcode. */
/* 810 */     OP_vshll_u8,           /**< ARM vshll_u8 opcode. */
/* 811 */     OP_vshr_s16,           /**< ARM vshr_s16 opcode. */
/* 812 */     OP_vshr_s32,           /**< ARM vshr_s32 opcode. */
/* 813 */     OP_vshr_s64,           /**< ARM vshr_s64 opcode. */
/* 814 */     OP_vshr_s8,            /**< ARM vshr_s8 opcode. */
/* 815 */     OP_vshr_u16,           /**< ARM vshr_u16 opcode. */
/* 816 */     OP_vshr_u32,           /**< ARM vshr_u32 opcode. */
/* 817 */     OP_vshr_u64,           /**< ARM vshr_u64 opcode. */
/* 818 */     OP_vshr_u8,            /**< ARM vshr_u8 opcode. */
/* 819 */     OP_vshrn_i16,          /**< ARM vshrn_i16 opcode. */
/* 820 */     OP_vshrn_i32,          /**< ARM vshrn_i32 opcode. */
/* 821 */     OP_vshrn_i8,           /**< ARM vshrn_i8 opcode. */
/* 822 */     OP_vsli_16,            /**< ARM vsli_16 opcode. */
/* 823 */     OP_vsli_32,            /**< ARM vsli_32 opcode. */
/* 824 */     OP_vsli_64,            /**< ARM vsli_64 opcode. */
/* 825 */     OP_vsli_8,             /**< ARM vsli_8 opcode. */
/* 826 */     OP_vsqrt_f32,          /**< ARM vsqrt_f32 opcode. */
/* 827 */     OP_vsqrt_f64,          /**< ARM vsqrt_f64 opcode. */
/* 828 */     OP_vsra_s16,           /**< ARM vsra_s16 opcode. */
/* 829 */     OP_vsra_s32,           /**< ARM vsra_s32 opcode. */
/* 830 */     OP_vsra_s64,           /**< ARM vsra_s64 opcode. */
/* 831 */     OP_vsra_s8,            /**< ARM vsra_s8 opcode. */
/* 832 */     OP_vsra_u16,           /**< ARM vsra_u16 opcode. */
/* 833 */     OP_vsra_u32,           /**< ARM vsra_u32 opcode. */
/* 834 */     OP_vsra_u64,           /**< ARM vsra_u64 opcode. */
/* 835 */     OP_vsra_u8,            /**< ARM vsra_u8 opcode. */
/* 836 */     OP_vsri_16,            /**< ARM vsri_16 opcode. */
/* 837 */     OP_vsri_32,            /**< ARM vsri_32 opcode. */
/* 838 */     OP_vsri_64,            /**< ARM vsri_64 opcode. */
/* 839 */     OP_vsri_8,             /**< ARM vsri_8 opcode. */
/* 840 */     OP_vst1_16,            /**< ARM vst1_16 opcode. */
/* 841 */     OP_vst1_32,            /**< ARM vst1_32 opcode. */
/* 842 */     OP_vst1_64,            /**< ARM vst1_64 opcode. */
/* 843 */     OP_vst1_8,             /**< ARM vst1_8 opcode. */
/* 844 */     OP_vst1_lane_16,       /**< ARM vst1_lane_16 opcode. */
/* 845 */     OP_vst1_lane_32,       /**< ARM vst1_lane_32 opcode. */
/* 846 */     OP_vst1_lane_8,        /**< ARM vst1_lane_8 opcode. */
/* 847 */     OP_vst2_16,            /**< ARM vst2_16 opcode. */
/* 848 */     OP_vst2_32,            /**< ARM vst2_32 opcode. */
/* 849 */     OP_vst2_8,             /**< ARM vst2_8 opcode. */
/* 850 */     OP_vst2_lane_16,       /**< ARM vst2_lane_16 opcode. */
/* 851 */     OP_vst2_lane_32,       /**< ARM vst2_lane_32 opcode. */
/* 852 */     OP_vst2_lane_8,        /**< ARM vst2_lane_8 opcode. */
/* 853 */     OP_vst3_16,            /**< ARM vst3_16 opcode. */
/* 854 */     OP_vst3_32,            /**< ARM vst3_32 opcode. */
/* 855 */     OP_vst3_8,             /**< ARM vst3_8 opcode. */
/* 856 */     OP_vst3_lane_16,       /**< ARM vst3_lane_16 opcode. */
/* 857 */     OP_vst3_lane_32,       /**< ARM vst3_lane_32 opcode. */
/* 858 */     OP_vst3_lane_8,        /**< ARM vst3_lane_8 opcode. */
/* 859 */     OP_vst4_16,            /**< ARM vst4_16 opcode. */
/* 860 */     OP_vst4_32,            /**< ARM vst4_32 opcode. */
/* 861 */     OP_vst4_8,             /**< ARM vst4_8 opcode. */
/* 862 */     OP_vst4_lane_16,       /**< ARM vst4_lane_16 opcode. */
/* 863 */     OP_vst4_lane_32,       /**< ARM vst4_lane_32 opcode. */
/* 864 */     OP_vst4_lane_8,        /**< ARM vst4_lane_8 opcode. */
/* 865 */     OP_vstmdb,             /**< ARM vstmdb opcode. */
/* 866 */     OP_vstmia,             /**< ARM vstmia opcode. */
/* 867 */     OP_vstr,               /**< ARM vstr opcode. */
/* 868 */     OP_vsub_f32,           /**< ARM vsub_f32 opcode. */
/* 869 */     OP_vsub_f64,           /**< ARM vsub_f64 opcode. */
/* 870 */     OP_vsub_i16,           /**< ARM vsub_i16 opcode. */
/* 871 */     OP_vsub_i32,           /**< ARM vsub_i32 opcode. */
/* 872 */     OP_vsub_i64,           /**< ARM vsub_i64 opcode. */
/* 873 */     OP_vsub_i8,            /**< ARM vsub_i8 opcode. */
/* 874 */     OP_vsubhn_i16,         /**< ARM vsubhn_i16 opcode. */
/* 875 */     OP_vsubhn_i32,         /**< ARM vsubhn_i32 opcode. */
/* 876 */     OP_vsubhn_i64,         /**< ARM vsubhn_i64 opcode. */
/* 877 */     OP_vsubl_s16,          /**< ARM vsubl_s16 opcode. */
/* 878 */     OP_vsubl_s32,          /**< ARM vsubl_s32 opcode. */
/* 879 */     OP_vsubl_s8,           /**< ARM vsubl_s8 opcode. */
/* 880 */     OP_vsubl_u16,          /**< ARM vsubl_u16 opcode. */
/* 881 */     OP_vsubl_u32,          /**< ARM vsubl_u32 opcode. */
/* 882 */     OP_vsubl_u8,           /**< ARM vsubl_u8 opcode. */
/* 883 */     OP_vsubw_s16,          /**< ARM vsubw_s16 opcode. */
/* 884 */     OP_vsubw_s32,          /**< ARM vsubw_s32 opcode. */
/* 885 */     OP_vsubw_s8,           /**< ARM vsubw_s8 opcode. */
/* 886 */     OP_vsubw_u16,          /**< ARM vsubw_u16 opcode. */
/* 887 */     OP_vsubw_u32,          /**< ARM vsubw_u32 opcode. */
/* 888 */     OP_vsubw_u8,           /**< ARM vsubw_u8 opcode. */
/* 889 */     OP_vswp,               /**< ARM vswp opcode. */
/* 890 */     OP_vtbl_8,             /**< ARM vtbl_8 opcode. */
/* 891 */     OP_vtbx_8,             /**< ARM vtbx_8 opcode. */
/* 892 */     OP_vtrn_16,            /**< ARM vtrn_16 opcode. */
/* 893 */     OP_vtrn_32,            /**< ARM vtrn_32 opcode. */
/* 894 */     OP_vtrn_8,             /**< ARM vtrn_8 opcode. */
/* 895 */     OP_vtst_16,            /**< ARM vtst_16 opcode. */
/* 896 */     OP_vtst_32,            /**< ARM vtst_32 opcode. */
/* 897 */     OP_vtst_8,             /**< ARM vtst_8 opcode. */
/* 898 */     OP_vuzp_16,            /**< ARM vuzp_16 opcode. */
/* 899 */     OP_vuzp_32,            /**< ARM vuzp_32 opcode. */
/* 900 */     OP_vuzp_8,             /**< ARM vuzp_8 opcode. */
/* 901 */     OP_vzip_16,            /**< ARM vzip_16 opcode. */
/* 902 */     OP_vzip_32,            /**< ARM vzip_32 opcode. */
/* 903 */     OP_vzip_8,             /**< ARM vzip_8 opcode. */
/* 904 */     OP_wfe,                /**< ARM wfe opcode. */
/* 905 */     OP_wfi,                /**< ARM wfi opcode. */
/* 906 */     OP_yield,              /**< ARM yield opcode. */

    OP_AFTER_LAST,
    OP_FIRST = OP_adc,            /**< First real opcode. */
    OP_LAST  = OP_AFTER_LAST - 1, /**< Last real opcode. */
};

/* alternative names */
#define OP_pop       OP_ldr    /**< Alternative opcode name for ldr. */
#define OP_push      OP_stmdb  /**< Alternative opcode name for stmdb. */
#define OP_vpop      OP_vldmia /**< Alternative opcode name for vldmia. */
#define OP_vpush     OP_vstmdb /**< Alternative opcode name for vstmdb. */
#define OP_adr       OP_sub    /**< Alternative opcode name for sub. */
#define OP_neg       OP_rsbs   /**< Alternative opcode name for rsbs. */
#define OP_cpy       OP_mov    /**< Alternative opcode name for reg-reg mov. */
#define OP_smmul     OP_smmla  /**< Alternative opcode name for smmla on pc. */
#define OP_smmulr    OP_smmlar /**< Alternative opcode name for smmlar on pc. */
#define OP_smuad     OP_smlad  /**< Alternative opcode name for smlad on pc. */
#define OP_smuadx    OP_smladx /**< Alternative opcode name for smladx on pc. */
#define OP_smusd     OP_smlsd  /**< Alternative opcode name for smlsd on pc. */
#define OP_smusdx    OP_smlsdx /**< Alternative opcode name for smlsdx on pc. */
#define OP_sxtb      OP_sxtab  /**< Alternative opcode name for sxtab on pc. */
#define OP_sxtb16    OP_sxtab16 /**< Alternative opcode name for sxtab16 on pc. */
#define OP_sxth      OP_sxtah  /**< Alternative opcode name for sxtah on pc. */
#define OP_usad8     OP_usada8 /**< Alternative opcode name for usada8 on pc. */
#define OP_uxtb      OP_uxtab  /**< Alternative opcode name for uxtab on pc. */
#define OP_uxtb16    OP_uxtab16 /**< Alternative opcode name for uxtab16 on pc. */
#define OP_uxth      OP_uxtah  /**< Alternative opcode name for uxtah on pc. */

#define OP_jmp       OP_b      /**< Platform-independent opcode name for jump. */
#define OP_load      OP_ldr    /**< Platform-independent opcode name for load. */
#define OP_store     OP_str    /**< Platform-independent opcode name for store. */

/****************************************************************************/
/* DR_API EXPORT END */

#endif /* _OPCODE_H_ */
