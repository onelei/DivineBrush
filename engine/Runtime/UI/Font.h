//
// Created by onelei on 2024/3/20.
//

#ifndef ENGINE_FONT_H
#define ENGINE_FONT_H

#include <string>
#include <unordered_map>
#include "freetype/ftglyph.h"
#include "Texture2d.h"

namespace DivineBrush {

    class Font {
    public:
        Font();

        ~Font();

        static Font *Load(const std::string &fontPath, unsigned short fontSize);

        void LoadCharacter(char ch);

        Texture2d *GetFontTexture() { return font_texture; }

        struct Character {
            float left_top_x;
            float left_top_y;
            float right_bottom_x;
            float right_bottom_y;
            Character(float left_top_x, float left_top_y, float right_bottom_x, float right_bottom_y) {
                this->left_top_x = left_top_x;
                this->left_top_y = left_top_y;
                this->right_bottom_x = right_bottom_x;
                this->right_bottom_y = right_bottom_y;
            }
        };

        std::vector<Character*> LoadString(std::string str);

    private:
        unsigned short font_size = 20;//默认字体大小
        char *font_file_buffer = nullptr;//ttf字体文件加载到内存
        FT_Library ft_library;
        FT_Face ft_face;
        Texture2d *font_texture;
        unsigned short font_texture_size = 1024;
        unsigned short font_texture_fill_x=0;//当前行的起始点
        unsigned short font_texture_fill_y=0;//新的一行的纵向起始点
        std::unordered_map<char,Character*> character_map;//已经生成bitmap的字符

        static std::unordered_map<std::string, Font *> font_map;
    };

} // DivineBrush

#endif //ENGINE_FONT_H
