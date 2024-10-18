#include "country.hpp"

std::vector<cou> countries;

err_capable init_countries(const std::string countries_file, const std::string tags){

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

            cou new_country;
            new_country.tag = tag;
            new_country.country_name = tag_map[tag];
            new_country.country_rgb.r = R;
            new_country.country_rgb.g = G;
            new_country.country_rgb.b = B;
            new_country.units_num = 0; /* No units at first */

            new_country.balance = 0;
            new_country.manpower = 0;
            new_country.stab = 0;

            countries.push_back(new_country); /* Add to countries vector */
        }else{
            std::printf("Failed to parse countries\n");
            return FAIL;
        }
    }

    cou_file.close();

    return SUCCESS;
}

cou get_country(std::string tag){
    for(auto& cou : countries){
        if(strcmp(cou.tag.c_str(), tag.c_str()) == 0){
            return cou;
        }
    }
}
