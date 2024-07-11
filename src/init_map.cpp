#include "init_map.h"

/* The country regions are only there for ownership, the values of each region is updated in the global region vector 
the same is true for the provinces */

std::vector<reg>  regions;
SDL_Surface* map_surface;
SDL_Surface* map;

err_capable init_map(void){

    map_surface = SDL_LoadBMP("history/map/provinces.bmp");
    if(map_surface == nullptr){
        printf("Error, cannot create map surface\n");
        return FAIL;
    }

    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    map = resize_province_bitmap(map_surface, w, h);
    #ifdef MAIN_DBG
        std::printf("Map Surface Resized\n");
    #endif

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
    int line_n = 0;

    while(std::getline(file, line)){
        line_n++;
        std::printf("++++++++\nReading line %d\n", line_n);

        if(line.empty() || line[0] == '#'){
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


            /* Create a new province by allocating memory */

            prov* new_prov = new prov; /* HUH?: Malloc doesn't work ??? */
            // prov* new_prov = (prov*)malloc(sizeof(prov));

            if(!new_prov){
                std::printf("Memory allocation failed\n");
                file.close();
                return FAIL;
            }

            new_prov->prov_name = prov_name;
            new_prov->prov_colour.a = ALPHA;
            new_prov->prov_colour.r = R;
            new_prov->prov_colour.g = G;
            new_prov->prov_colour.b = B;
            new_prov->prov_id = i; /* Unique id for each province */
            new_prov->region = region_id;
            new_prov->next = NULL;

            ulint hidx = h(new_prov->prov_id, PROV_M);

            if(hidx < 0 || hidx >= prov_hash_s){
                std::printf("!!!! Hash index %d out of bounds\n", hidx);
                delete new_prov;
                continue;
            }

            if(region_id >= regions.size()){
                regions.resize(region_id + 1);
            }

            if(provinces_h[hidx] == NULL){
                /* First Insertion */
                provinces_h[hidx] = new_prov;
                new_prov->next = NULL;
            }else{
                new_prov->next = provinces_h[hidx];
                provinces_h[hidx] = new_prov;
            }

            /* Each province is also saved here, and in the regions vector */
            regions[region_id].reg_provs.push_back(*new_prov); /* Regions will remain in vectors for now... */
        }else{
            std::printf("Failed to parse line: %s", line);
            file.close();
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

    std::string line;
    std::regex pattern(R"(\s*\"(\w+)\"\s*:\s*\{\s*([\d\s,]*)\s*\}\s*)");

    while(std::getline(file, line)){
        if(line.empty() || line[0] == '#'){
            continue;
        }

        std::smatch matches;
        if(std::regex_match(line, matches, pattern)){
            std::string tag = matches[1];
            std::string regions_str = matches[2];

            std::istringstream region_stream(regions_str);
            std::string reg_id;
            std::vector<int> region_ids;
            while(std::getline(region_stream, reg_id, ',')){
                region_ids.push_back(std::stoi(reg_id));
            }

            for(auto& cou : countries){
                if(cou.tag == tag){
                    for(const auto& id : region_ids){
                        auto it = std::find_if(regions.begin(), regions.end(), [&id](const reg& r){
                            return r.reg_id == id;
                        });
                    
                        if(it != regions.end()){
                            cou.country_regs.push_back(*it);
                        }
                    }
                    break;
                }
            }
        }
    }

    file.close();
    return SUCCESS;
}

SDL_Surface* resize_province_bitmap(SDL_Surface* map_surface, float w, float h){
    SDL_Surface* resized_map_surface = SDL_CreateRGBSurface(0, static_cast<int>(w), static_cast<int>(h), map_surface->format->BitsPerPixel, 
                                                    map_surface->format->Rmask, map_surface->format->Gmask, 
                                                    map_surface->format->Bmask, map_surface->format->Amask);

    SDL_Rect stretched_rect = {0, 0, static_cast<int>(w), static_cast<int>(h)};
    SDL_BlitScaled(map_surface, NULL, resized_map_surface, &stretched_rect); /* Fast copy it onto the resized surface */

    return resized_map_surface;
}

void print_regions(void){
    for(const auto& reg : regions){
        std::printf("REG: %s ID - %d\n", reg.reg_name.c_str(), reg.reg_id);
        for (const auto& prov : reg.reg_provs){
            std::printf("   PROV: %s, RGB, %d,%d,%d, ID: %d\n", prov.prov_name.c_str(), prov.prov_colour.r, prov.prov_colour.b, prov.prov_colour.g, prov.prov_id);
        }
        std::printf("\n");
    }

    return;
}

void print_countries(void){
    for(const auto& cou : countries){
        std::printf("COU: %s, TAG %s, RGB: %d %d %d\n", cou.country_name.c_str(), cou.tag.c_str(), cou.country_rgb.r, cou.country_rgb.g, cou.country_rgb.b);
        for(const auto& creg : cou.country_regs){
            std::printf("   REG: %s, ID: %d\n",creg.reg_name.c_str(), creg.reg_id);
            for(const auto& prov : creg.reg_provs){
                std::printf("       PROV: %s, RGB, %d,%d,%d, ID: %d\n", prov.prov_name.c_str(), prov.prov_colour.r, prov.prov_colour.b, prov.prov_colour.g, prov.prov_id);
            }
        }
    }

    return;
}

void print_provinces(void){
    for(int i = 0 ; i < prov_hash_s ; i++){
        prov* current = provinces_h[h(i, PROV_M)];
        while(current != NULL){
            printf(" -PROV: %s, RGB %d - %d - %d, ID %d, HASH_ID %d\n", current->prov_name.c_str(), current->prov_colour.r, current->prov_colour.g, current->prov_colour.b, current->prov_id, i);
            current = current->next;
        }
    }

    return;
}

