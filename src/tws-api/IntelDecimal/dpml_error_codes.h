/******************************************************************************
  Copyright (c) 2007-2018, Intel Corp.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#define RESPONSE_TABLE      __dpml_response_table
static const DPML_EXCEPTION_RESPONSE RESPONSE_TABLE[] = {
    /* 0 */ {0, 1, 1, 1, 0},
    /* 1 */ {1, 1, 1, 1, 0},
    /* 2 */ {2, 1, 1, 1, 0},
    /* 3 */ {3, 1, 1, 1, 0},
    /* 4 */ {4, 1, 1, 1, 0},
    /* 5 */ {8, 1, 1, 1, 0},
    /* 6 */ {8, 3, 5, 3, 7},
    /* 7 */ {8, 3, 6, 3, 8},
    /* 8 */ {9, 1, 1, 1, 0},
    /* 9 */ {9, 1, 1, 1, 0},
    /* 10 */ {9, 4, 1, 4, 1},
    /* 11 */ {10, 1, 1, 1, 0},
    /* 12 */ {10, 1, 1, 1, 0},
    /* 13 */ {10, 4, 1, 4, 1},
    /* 14 */ {11, 3, 5, 3, 7},
    /* 15 */ {39, 1, 1, 1, 0},
    /* 16 */ {39, 3, 5, 3, 7},
    /* 17 */ {12, 1, 1, 1, 0},
    /* 18 */ {13, 1, 1, 1, 0},
    /* 19 */ {14, 3, 5, 3, 7},
    /* 20 */ {33, 4, 1, 4, 1},
    /* 21 */ {33, 3, 5, 3, 7},
    /* 22 */ {33, 3, 6, 3, 8},
    /* 23 */ {33, 1, 1, 1, 0},
    /* 24 */ {33, 2, 5, 2, 7},
    /* 25 */ {33, 2, 6, 2, 8},
    /* 26 */ {34, 4, 1, 4, 1},
    /* 27 */ {34, 3, 5, 3, 7},
    /* 28 */ {34, 3, 6, 3, 8},
    /* 29 */ {34, 1, 1, 1, 0},
    /* 30 */ {34, 2, 5, 2, 7},
    /* 31 */ {34, 2, 6, 2, 8},
    /* 32 */ {34, 2, 5, 2, 7},
    /* 33 */ {16, 3, 5, 3, 7},
    /* 34 */ {16, 4, 1, 4, 1},
    /* 35 */ {16, 3, 5, 3, 7},
    /* 36 */ {16, 4, 1, 4, 1},
    /* 37 */ {17, 3, 5, 3, 7},
    /* 38 */ {17, 0, 7, 0, 7},
    /* 39 */ {17, 0, 12, 0, 12},
    /* 40 */ {38, 3, 5, 3, 7},
    /* 41 */ {38, 3, 6, 3, 8},
    /* 42 */ {38, 4, 1, 4, 1},
    /* 43 */ {47, 3, 5, 3, 7},
    /* 44 */ {47, 3, 6, 3, 8},
    /* 45 */ {47, 4, 1, 4, 1},
    /* 46 */ {47, 3, 5, 3, 7},
    /* 47 */ {47, 3, 6, 3, 8},
    /* 48 */ {47, 4, 1, 4, 1},
    /* 49 */ {47, 1, 1, 1, 0},
    /* 50 */ {47, 1, 1, 1, 0},
    /* 51 */ {37, 2, 6, 2, 8},
    /* 52 */ {18, 1, 6, 1, 0},
    /* 53 */ {18, 3, 6, 3, 8},
    /* 54 */ {19, 1, 6, 1, 0},
    /* 55 */ {19, 3, 6, 3, 8},
    /* 56 */ {20, 1, 6, 1, 0},
    /* 57 */ {20, 3, 6, 3, 8},
    /* 58 */ {45, 1, 6, 1, 0},
    /* 59 */ {45, 3, 6, 3, 8},
    /* 60 */ {21, 4, 1, 4, 1},
    /* 61 */ {21, 1, 1, 1, 1},
    /* 62 */ {21, 1, 1, 1, 0},
    /* 63 */ {40, 3, 5, 3, 7},
    /* 64 */ {40, 3, 6, 3, 8},
    /* 65 */ {40, 4, 1, 4, 1},
    /* 66 */ {40, 4, 2, 4, 2},
    /* 67 */ {22, 3, 5, 3, 7},
    /* 68 */ {22, 3, 6, 3, 8},
    /* 69 */ {22, 4, 1, 4, 1},
    /* 70 */ {22, 1, 1, 1, 0},
    /* 71 */ {22, 2, 6, 2, 8},
    /* 72 */ {22, 1, 1, 1, 0},
    /* 73 */ {22, 1, 1, 1, 0},
    /* 74 */ {22, 3, 6, 3, 8},
    /* 75 */ {22, 1, 1, 1, 0},
    /* 76 */ {22, 0, 7, 0, 7},
    /* 77 */ {22, 0, 7, 0, 7},
    /* 78 */ {22, 0, 8, 0, 8},
    /* 79 */ {22, 3, 5, 3, 7},
    /* 80 */ {22, 0, 1, 0, 1},
    /* 81 */ {22, 4, 1, 4, 1},
    /* 82 */ {41, 3, 5, 3, 7},
    /* 83 */ {41, 3, 6, 3, 8},
    /* 84 */ {41, 4, 1, 4, 1},
    /* 85 */ {41, 4, 2, 4, 2},
    /* 86 */ {41, 1, 1, 1, 0},
    /* 87 */ {41, 2, 5, 2, 7},
    /* 88 */ {41, 2, 6, 2, 8},
    /* 89 */ {48, 3, 5, 3, 7},
    /* 90 */ {48, 1, 1, 1, 0},
    /* 91 */ {23, 4, 1, 4, 1},
    /* 92 */ {23, 1, 1, 1, 1},
    /* 93 */ {23, 1, 1, 1, 0},
    /* 94 */ {24, 1, 1, 1, 0},
    /* 95 */ {31, 1, 1, 1, 0},
    /* 96 */ {32, 1, 1, 1, 0},
    /* 97 */ {32, 4, 1, 4, 1},
    /* 98 */ {25, 1, 1, 1, 0},
    /* 99 */ {25, 4, 1, 4, 1},
    /* 100 */ {26, 3, 5, 3, 7},
    /* 101 */ {26, 3, 6, 3, 8},
    /* 102 */ {26, 4, 1, 4, 1},
    /* 103 */ {27, 1, 1, 1, 0},
    /* 104 */ {61, 2, 5, 2, 7},
    /* 105 */ {61, 2, 6, 2, 8},
    /* 106 */ {28, 1, 1, 1, 0},
    /* 107 */ {29, 4, 1, 4, 1},
    /* 108 */ {29, 3, 5, 3, 7},
    /* 109 */ {29, 1, 1, 1, 0},
    /* 110 */ {29, 2, 5, 2, 7},
    /* 111 */ {30, 3, 5, 3, 7},
    /* 112 */ {30, 4, 1, 4, 1},
    /* 113 */ {35, 1, 1, 1, 0},
    /* 114 */ {36, 1, 1, 1, 0},
    /* 115 */ {36, 4, 1, 4, 1},
    /* 116 */ {49, 0, 1, 0, 1},
    /* 117 */ {50, 0, 1, 0, 1},
    /* 118 */ {51, 0, 1, 0, 1},
    /* 119 */ {50, 4, 1, 4, 1},
    /* 120 */ {50, 4, 2, 4, 2},
    /* 121 */ {51, 4, 1, 4, 1},
    /* 122 */ {51, 4, 2, 4, 2},
    /* 123 */ {42, 0, 1, 0, 1},
    /* 124 */ {43, 0, 1, 0, 1},
    /* 125 */ {44, 0, 1, 0, 1},
    /* 126 */ {42, 1, 6, 1, 0},
    /* 127 */ {42, 2, 6, 2, 8},
    /* 128 */ {43, 1, 6, 1, 0},
    /* 129 */ {43, 2, 6, 2, 8},
    /* 130 */ {43, 3, 6, 3, 8},
    /* 131 */ {44, 1, 6, 1, 0},
    /* 132 */ {44, 2, 6, 2, 8},
    /* 133 */ {44, 3, 6, 3, 8},
    /* 134 */ {44, 3, 5, 3, 7},
    /* 135 */ {46, 3, 5, 3, 7},
    /* 136 */ {46, 0, 7, 0, 7},
    /* 137 */ {46, 1, 1, 1, 0},
    /* 138 */ {46, 2, 5, 2, 7},
    /* 139 */ {46, 2, 5, 2, 7},
    /* 140 */ {53, 4, 1, 4, 1},
    /* 141 */ {76, 0, 1, 0, 0},
    /* 142 */ {62, 3, 5, 3, 7},
    /* 143 */ {62, 4, 1, 4, 1},
    /* 144 */ {62, 0, 7, 0, 7},
    /* 145 */ {62, 0, 1, 0, 1},
    /* 146 */ {64, 3, 5, 3, 7},
    /* 147 */ {64, 3, 6, 3, 8},
    /* 148 */ {64, 4, 1, 4, 1},
    /* 149 */ {65, 3, 5, 3, 7},
    /* 150 */ {65, 3, 6, 3, 8},
    /* 151 */ {65, 4, 1, 4, 1},
    /* 152 */ {63, 3, 5, 3, 7},
    /* 153 */ {63, 3, 6, 3, 8},
    /* 154 */ {63, 0, 7, 0, 7},
    /* 155 */ {63, 1, 1, 1, 0},
    /* 156 */ {63, 2, 5, 2, 7},
    /* 157 */ {63, 2, 6, 2, 8},
    /* 158 */ {63, 2, 5, 2, 7},
    /* 159 */ {66, 1, 1, 1, 0},
    /* 160 */ {67, 1, 1, 1, 0},
    /* 161 */ {68, 1, 1, 1, 0},
    /* 162 */ {69, 1, 1, 1, 0},
    /* 163 */ {70, 4, 1, 4, 1},
    /* 164 */ {70, 0, 1, 0, 1},
    /* 165 */ {70, 1, 1, 1, 0},
    /* 166 */ {71, 3, 5, 3, 7},
    /* 167 */ {71, 3, 6, 3, 8},
    /* 168 */ {71, 4, 1, 4, 1},
    /* 169 */ {71, 4, 2, 4, 2},
    /* 170 */ {72, 3, 5, 3, 7},
    /* 171 */ {72, 4, 1, 4, 1},
    /* 172 */ {75, 4, 1, 4, 1},
    /* 173 */ {75, 4, 2, 4, 2},
    /* 174 */ {75, 3, 5, 3, 7},
    /* 175 */ {75, 3, 6, 3, 8},
    /* 176 */ {75, 1, 1, 1, 0},
    /* 177 */ {75, 1, 1, 1, 0},
    };
