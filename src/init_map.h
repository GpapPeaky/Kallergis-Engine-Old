#include "province.h"
#include "regions.h"
#include <fstream>
#include <regex>
#include <string>

#ifndef INIT_MAP
#define INIT_MAP

extern std::vector<reg>  regions; /* Contains data for each region */

/**
 * @brief parses data from mdf
 * 
 * @param fname file name to read from
 * 
 * @returns 1 on failure
 *                0 on success
*/
err_capable read_mdf(const std::string fname);

#endif