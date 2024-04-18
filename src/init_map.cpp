#include "init_map.h"

std::vector<reg>  regions;

err_capable read_mdf(const std::string fname){
    
    std::ifstream file(fname);
    if(!file.is_open()){
        std::printf("Failed to open regions map data file %s\n", fname);
        return FAIL;
    }

    std::string line;
    std::regex pattern("\"([^\"]+)\"\\s*:\\s*\\{\\s*(\\d+),\\s*(\\d+),\\s*(\\d+)\\s*\\}\\s*:\\s*(\\d+)");

    while(std::getline(file, line)){

        if(line.empty()){
            continue;
        }

        if(line[0] == '#'){
            continue;
        }

        std::smatch matches;
        if(std::regex_search(line, matches, pattern)){
            std::string prov_name = matches[1];
            int R = std::stoi(matches[2]);
            int G = std::stoi(matches[3]);
            int B = std::stoi(matches[4]);
            int region_id = std::stoi(matches[5]);


            /* Create a new province */

            prov new_prov;
            new_prov.prov_colour.a = ALPHA;
            new_prov.prov_colour.r = R;
            new_prov.prov_colour.g = G;
            new_prov.prov_colour.b = B;

            if(region_id >= regions.size()){
                regions.resize(region_id + 1);
            }

            new_prov.prov_id = regions[region_id].reg_provs.size(); /* Unique id for each province */
            new_prov.region = region_id;

            std::printf("PROV: %s - RGB: %d,%d,%d - REG: %d", prov_name.c_str(), R, G, B, region_id);

            regions[region_id].reg_provs.push_back(new_prov);

        }else{
            std::printf("Failed to parse line: %s", line);
        }
    }

    file.close();
}
