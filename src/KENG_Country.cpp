#include "KENG_Country.hpp"

std::vector<KENG_country> KENG_globalCountries;

int KENG_CreateCountries(const std::string countries_file, const std::string tags, const std::string leadersFile){
    std::ifstream tags_file(tags);
    if(!tags_file.is_open()){
        std::printf("Failed to load tags.cdf\n");
        return FAIL;
    }

    std::ifstream cou_file(countries_file);
    if(!cou_file.is_open()){
        std::printf("Failed to load cou.ndf\n");
        return FAIL;
    }

    std::ifstream leaderFile(leadersFile);
    if(!leaderFile.is_open()){
        std::printf("Failed to load leaders.cdf\n");
        return FAIL;
    }

    std::map<std::string, std::string> tag_map; /* key - value map */

    std::string tags_line;
    std::regex tags_pattern("\\s*(\\w+)\\s*=\\s*\"([^\"]+)\"");
    while(std::getline(tags_file, tags_line)){
        if(tags_line.empty() || tags_line[0] == '#'){
            continue;
        }

        std::smatch tags_matches;
        if(std::regex_match(tags_line, tags_matches, tags_pattern)){
            std::string tag = tags_matches[1];
            std::string country_name = tags_matches[2];
            tag_map[tag] = country_name;
        }else{
            printf("Failed to parse tags\n");
            return FAIL;
        }
    }
    
    tags_file.close();

    std::string cou_line;
    std::regex cou_pattern("\\s*\"(\\w+)\"\\s*:\\s*\\{\\s*(\\d+),\\s*(\\d+),\\s*(\\d+)\\s*\\}");
    while(std::getline(cou_file, cou_line)){
        if(cou_line.empty() || cou_line[0] == '#'){
            continue;
        }

        std::smatch cou_matches;
        if(regex_match(cou_line, cou_matches, cou_pattern)){
            std::string tag = cou_matches[1];
            int R = std::stoi(cou_matches[2]);
            int G = std::stoi(cou_matches[3]);
            int B = std::stoi(cou_matches[4]);

            KENG_country newCountry;
            newCountry.tag = tag;
            newCountry.country_name = tag_map[tag];
            newCountry.country_rgb.r = R;
            newCountry.country_rgb.g = G;
            newCountry.country_rgb.b = B;
            newCountry.units_num = 0; /* No units at first */

            newCountry.balance = 0.0f;
            newCountry.manpower = 0.0f;
            newCountry.stab = 0;

            KENG_globalCountries.push_back(newCountry); /* Add to countries vector */
        }else{
            std::printf("Failed to parse countries\n");
            return FAIL;
        }
    }

    cou_file.close();

    std::string leaderLine;
    std::regex leaderPattern("\\s*\"(\\w+)\"\\s*:\\s*\"([^\"]+)\"\\s*:\\s*(\\S+)");
    while(std::getline(leaderFile, leaderLine)){
        if(leaderLine.empty() || leaderLine[0] == '#'){
            continue; /* Comments */
        }

        std::smatch leaderMatches;
        if(regex_match(leaderLine, leaderMatches, leaderPattern)){
            std::string tag = leaderMatches[1];
            std::string name = leaderMatches[2];
            std::string leaderIconName = leaderMatches[3];

            KENG_leader* newLeader = new KENG_leader;

            newLeader = KENG_CreateCountryLeader(name, leaderIconName, renderer);

            for(auto& country : KENG_globalCountries){
                if(strcmp(country.tag.c_str(), tag.c_str()) == 0){
                    country.countryLeader = newLeader;
                }
            }
        }else{
            std::printf("Failed to parse country leaders\n");
            return FAIL;
        }
    }

    leaderFile.close();

    return SUCCESS;
}

KENG_country* KENG_GetCountry(std::string tag){
    for(auto& cou : KENG_globalCountries){
        if(strcmp(cou.tag.c_str(), tag.c_str()) == 0){
            return &cou;
        }
    }
}

void SDL2_RenderCountryLeader(KENG_country* country, SDL_Renderer* renderer){
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);

    SDL_Rect leaderRect = {w - 189 + 5, 5, COUNTRY_LEADER_SIZE, COUNTRY_LEADER_SIZE};

    SDL_RenderCopy(renderer, country->countryLeader->leaderIcon, NULL, &leaderRect);
    
    return;
}
