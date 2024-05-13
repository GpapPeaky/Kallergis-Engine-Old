#include "init_map.h"

std::vector<reg>  regions; /* IDEA: MIGHT BE ABLE TO BE OMITED, BY SAVING THE RELEVANT REGIONS DIRECTLY TO COUNTRY REGIONS */
std::vector<prov> provinces;
SDL_Surface* map_surface;
SDL_Texture* map_texture;

err_capable init_map(void){
    map_surface = IMG_Load("src/regions/provinces.bmp");
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

err_capable prov_to_reg(const std::string fname){
    
    std::ifstream file(fname);
    if(!file.is_open()){
        std::printf("Failed to open regions map data file %s\n", fname);
        return FAIL;
    }

    std::string line;
    std::regex pattern("\"([^\"]+)\"\\s*:\\s*\\{\\s*(\\d+),\\s*(\\d+),\\s*(\\d+)\\s*\\}\\s*:\\s*(\\d+)"); /* Regex pattern */

    int i = 0;

    while(std::getline(file, line)){

        if(line.empty()){
            continue;
        }

        if(line[0] == '#'){
            continue;
        }

        std::smatch matches;
        if(std::regex_search(line, matches, pattern)){
            i++;
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

            new_prov.prov_id = i; /* Unique id for each province */
            new_prov.region = region_id;

            provinces.push_back(new_prov);
            regions[region_id].reg_provs.push_back(new_prov);
        }else{
            std::printf("Failed to parse line: %s", line);
            return FAIL;
        }
    }

    file.close();
    return SUCCESS;
}

err_capable reg_names(const std::string fname){
    std::ifstream file(fname);
    if(!file.is_open()){
        std::printf("Failed to open regions map data file %s\n", fname);
        return FAIL;
    }

    std::string line;
    std::regex pattern("\\s*(\\d+)\\s*:\\s*\"([^\"]+)\"");

    while(std::getline(file, line)){

        if(line.empty()){
            continue;
        }

        if(line[0] == '#'){
            continue;
        }

        std::smatch matches;
        if(std::regex_match(line, matches, pattern)){
            int reg_id = std::stoi(matches[1]);
            std::string reg_n = matches[2];

            /* Create a new province */

            for(int i = 0 ; i < regions.size() ; i++){
                if(i == reg_id){
                    regions[i].reg_id = i;
                    regions[i].reg_name = reg_n;
                    break;
                }
            }

        }else{
            std::printf("Failed to parse line: %s", line);
            return FAIL;
        }
    }

    file.close();
    return SUCCESS;

}

err_capable reg_to_country(const std::string fname){
    std::ifstream file(fname);
    if(!file.is_open()){
        std::printf("Failed to open regions map data file %s\n", fname);
        return FAIL;
    }


    return SUCCESS;
}

void print_regions(void){
    for(const auto& reg : regions){
        std::printf("REG: %s ID - %d\n", reg.reg_name.c_str(), reg.reg_id);
        for (const auto& prov : reg.reg_provs){
            std::printf("   PROV: %s, RGB, %d,%d,%d, ID: %d\n", prov.prov_name.c_str(), prov.prov_colour.r, prov.prov_colour.b, prov.prov_colour.g, prov.prov_id);
        }
        std::printf("\n");
    }
}

void print_countries(void){
    for(const auto& cou : countries){
        std::printf("COU: %s, TAG %s, RGB: %d %d %d\n", cou.country_name.c_str(), cou.tag.c_str(), cou.country_rgb.r, cou.country_rgb.g, cou.country_rgb.b);
    }
    return;
}

