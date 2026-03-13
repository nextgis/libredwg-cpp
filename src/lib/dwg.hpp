#pragma once

extern "C" { // for correct linkage with the non-interface part of LibreDWG

#include "bits.h"

int dwg_write_dxf(Bit_Chain *dat, Dwg_Data *dwg);
}

#include <dwg_api.h>
