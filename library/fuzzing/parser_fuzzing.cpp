//
// Created by GuustYsebie on 04/06/2023.
//

#include <cstdint>
#include <dsmr/parser.h>
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    int amount = DSMR_parse_data((char *) Data, NULL, Size);
    return 0;  // Values other than 0 and -1 are reserved for future use.
}