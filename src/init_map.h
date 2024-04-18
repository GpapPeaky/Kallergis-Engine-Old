#include "province.h"
#include "regions.h"
#include <fstream>
#include <regex>
#include <string>

#ifndef INIT_MAP
#define INIT_MAP

extern std::vector<reg>  regions; /* Contains data for each region */

/**
 * @brief parses data from mdf, to assign ma data of provinces to each region
 * 
 * @param fname file name to read from
 * 
 * @returns 1 on failure
 *                0 on success
*/
err_capable prov_to_reg(const std::string fname);

/**
 * @brief prints all regions, along with their data
*/
void print_regions(void);

#endif