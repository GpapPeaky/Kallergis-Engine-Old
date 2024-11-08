#include "KENG_Parser.hpp"

/* The country regions are only there for ownership, the values of each region is updated in the global region vector 
the same is true for the provinces */

std::vector<reg> regions;

int KENG_ProvinceToRegion(const std::string fname){
    
    std::ifstream file(fname);
    if(!file.is_open()){
        std::printf("Failed to open regions map data file %s\n", fname);
        return FAIL;
    }

    std::string line;
    /* REGEX PATTERN */
    std::regex pattern("\"([^\"]+)\"\\s*:\\s*\\{\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*\\}\\s*:\\s*(\\d+)\\s*:\\s*(\\d+)\\s*:\\s*(COAL|IRON|STEEL|FABRIC|WOOD|ARMS|OIL|RUBBER|GUNPOWDER|GOLD|COPPER|LEATHER|FISH|GLASS|GEMS|STONE|PAPER|FOOD)\\s*:\\s*\\{\\s*(\\d+)\\s*,\\s*(\\d+)\\s*,\\s*(\\d+)\\s*\\}\\s*:\\s*(\\d+)");

    int i = 0;
    int line_n = 0;

    while(std::getline(file, line)){
        line_n++;

        if(line.empty() || line[0] == '#'){
            continue;
        }

        std::smatch matches;
        if(std::regex_search(line, matches, pattern)){
            i++;
            std::string prov_name = matches[1];
            int R = std::stoi(matches[2].str());
            int G = std::stoi(matches[3].str());
            int B = std::stoi(matches[4].str());
            int region_id = std::stoi(matches[5].str());
            Uint population = std::stoul(matches[6].str());
            std::string good_produced_str = matches[7].str();
            Uint admn_dev = std::stoul(matches[8].str());
            Uint mil_dev = std::stoul(matches[9].str());
            Uint prod_dev = std::stoul(matches[10].str());
            Uint infra_level = std::stoul(matches[11].str());

            /* Create a new province by allocating memory */

            prov* new_prov = new prov; /* HUH?: Malloc doesn't work ??? */
            // prov* new_prov = (prov*)malloc(sizeof(prov));

            if(!new_prov){
                std::printf("Memory allocation failed\n");
                file.close();
                return FAIL;
            }

            auto it = product_map.find(good_produced_str);
            product good_produced = it->second;

            new_prov->prov_name = prov_name;
            new_prov->prov_colour.a = ALPHA;
            new_prov->prov_colour.r = R;
            new_prov->prov_colour.g = G;
            new_prov->prov_colour.b = B;
            new_prov->prov_id = i; /* Unique id for each province */
            new_prov->region = region_id;
            new_prov->province_economy.development.admin = admn_dev;
            new_prov->province_economy.development.mil = mil_dev;
            new_prov->province_economy.development.prod = prod_dev;
            new_prov->province_economy.local_goods.population = population;
            new_prov->province_economy.local_goods.good = good_produced;
            new_prov->province_economy.infrastructure = infra_level;
            new_prov->next = NULL;

            provinces.push_back(new_prov);

            if(region_id >= regions.size()){
                regions.resize(region_id + 1);
            }

            /* Each province is also saved here, and in the regions vector */
            regions[region_id].pops += new_prov->province_economy.local_goods.population;
            regions[region_id].reg_provs.push_back(*new_prov); /* Regions will remain in vectors for now... */
        }else{
            std::printf("Failed to parse line: %s\n", line);
            file.close();
            return FAIL;
        }
    }

    file.close();
    return SUCCESS;
}

int KENG_CreateRegionNames(const std::string fname){
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

int KENG_RegionsToCountry(const std::string fname){
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

/* TODO: Move this somewhere else */
SDL_Surface* SDL2_ResizeBitmap(SDL_Surface* map_surface, float w, float h){
    SDL_Surface* resized_map_surface = SDL_CreateRGBSurface(0, static_cast<int>(w), static_cast<int>(h), map_surface->format->BitsPerPixel, 
                                                    map_surface->format->Rmask, map_surface->format->Gmask, 
                                                    map_surface->format->Bmask, map_surface->format->Amask);

    SDL_Rect stretched_rect = {0, 0, static_cast<int>(w), static_cast<int>(h)};
    SDL_BlitScaled(map_surface, NULL, resized_map_surface, &stretched_rect); /* Fast copy it onto the resized surface */

    return resized_map_surface;
}

void KENG_PrintRegions(void){
    for(const auto& reg : regions){
        std::printf("REG: %s ID - %d - POP: %d\n", reg.reg_name.c_str(), reg.reg_id, reg.pops);
        for (const auto& prov : reg.reg_provs){
            std::printf("   PROV: %s,\tRGB, <%d,%d,%d>,\tID: %d\n", prov.prov_name.c_str(), prov.prov_colour.r, prov.prov_colour.b, prov.prov_colour.g, prov.prov_id);
        }
        std::printf("\n");
    }

    return;
}

void KENG_PrintCountries(void){
    for(const auto& cou : countries){
        std::printf("COU: %s, TAG %s, RGB: %d %d %d\n", cou.country_name.c_str(), cou.tag.c_str(), cou.country_rgb.r, cou.country_rgb.g, cou.country_rgb.b);
        for(const auto& creg : cou.country_regs){
            std::printf("   REG: %s, ID: %d\n",creg.reg_name.c_str(), creg.reg_id);
            for(const auto& prov : creg.reg_provs){
                std::printf("       PROV: %s,\tRGB, <%d,%d,%d>,\tID: %d\n", prov.prov_name.c_str(), prov.prov_colour.r, prov.prov_colour.b, prov.prov_colour.g, prov.prov_id);
            }
        }
    }

    return;
}

void KENG_PrintProvinces(void){
    for(auto prov : provinces){
        printf(" -PROV: %s,\tRGB <%d,%d,%d>,\tID %d\n",prov->prov_name.c_str(), prov->prov_colour.r, prov->prov_colour.g, prov->prov_colour.b, prov->prov_id);
        printf("ECO: adm: %d mil: %d prd: %d | pops: %d| infr: %d -> Income: %.2f, Local Production: %s %.2f\n", prov->province_economy.development.admin, prov->province_economy.development.mil, prov->province_economy.development.prod,
        prov->province_economy.local_goods.population, prov->province_economy.infrastructure, I(prov->province_economy), goods_names[prov->province_economy.local_goods.good], GP(prov->province_economy));
        printf("___________________________________________________________________________________________\n");
    }

    return;
}
