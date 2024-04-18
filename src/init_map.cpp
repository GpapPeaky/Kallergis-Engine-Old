#include "init_map.h"

std::vector<reg>  regions;
SDL_Surface* map_surface;
SDL_Texture* map_texture;

err_capable prov_to_reg(const std::string fname){
    
    std::ifstream file(fname);
    if(!file.is_open()){
        std::printf("Failed to open regions map data file %s\n", fname);
        return FAIL;
    }

    std::string line;
    std::regex pattern("\"([^\"]+)\"\\s*:\\s*\\{\\s*(\\d+),\\s*(\\d+),\\s*(\\d+)\\s*\\}\\s*:\\s*(\\d+)"); /* Regex pattern */

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
            new_prov.prov_name = prov_name;
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
            return FAIL;
        }
    }

    file.close();
    return SUCCESS;
}

err_capable scan_png_map(const std::string fname){
    map_surface = IMG_Load("src/regions/regions.png");
    if(map_surface == nullptr){
        printf("Error, cannot create map surface\n");
        return FAIL;
    }
    map_texture = SDL_CreateTextureFromSurface(renderer, map_surface);
    if(map_texture == nullptr){
        printf("Error, cannot create map texture\n");
        return FAIL;
    }

    return SUCCESS;
}

void print_regions(void){
    for(const auto& reg : regions){
        std::printf("REG: %s\n", reg.reg_name.c_str());
        for (const auto& prov : reg.reg_provs){
            std::printf("   PROV: %s, RGB, %d,%d,%d, ID: %d\n", prov.prov_name.c_str(), prov.prov_colour.r, prov.prov_colour.b, prov.prov_colour.g, prov.prov_id);
        }
        std::printf("\n");
    }
}

