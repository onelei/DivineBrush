//
// Created by onelei on 2024/3/20.
//

#include "Font.h"
#include "freetype/ftbitmap.h"
#include "../application.h"
#include <fstream>
#include "../../depends/debug/debug.h"
#include "../../depends/template/ObjectPool.h"
#include "../RenderPipeline/Handler/UpdateTextureSubImage2DHandler.h"
#include "../RenderPipeline/RenderPipeline.h"

namespace DivineBrush {
    std::unordered_map<std::string, Font *> Font::font_map;

    Font::Font() {
        //FT_Init_FreeType(&ft_library_);
    }

    Font::~Font() {
        //FT_Done_FreeType(ft_library_);
    }

    Font *Font::Load(const std::string &fontPath, unsigned short fontSize) {
        auto font = font_map[fontPath];
        if (font != nullptr) {
            return font;
        }
        //读取 ttf 字体文件
        std::ifstream fileStream(Application::GetDataPath() + fontPath, std::ios::in | std::ios::binary);
        fileStream.seekg(0, std::ios::end);
        int len = fileStream.tellg();
        fileStream.seekg(0, std::ios::beg);
        char *font_file_buffer = new char[len];
        fileStream.read(font_file_buffer, len);
        //将ttf 传入FreeType解析
        FT_Library ft_library = nullptr;
        FT_Face ft_face = nullptr;
        FT_Init_FreeType(&ft_library);//FreeType初始化;
        FT_Error error = FT_New_Memory_Face(ft_library, (const FT_Byte *) font_file_buffer, len, 0, &ft_face);
        if (error != 0) {
            DEBUG_LOG_ERROR("FT_New_Memory_Face return error {}!", error);
            return nullptr;
        }
        FT_Select_Charmap(ft_face, FT_ENCODING_UNICODE);
        FT_F26Dot6 ft_size = (FT_F26Dot6) (fontSize * (1 << 6));
        FT_Set_Char_Size(ft_face, ft_size, 0, 72, 72);
        if (ft_face == nullptr) {
            DEBUG_LOG_ERROR("FT_Set_Char_Size error!");
            return nullptr;
        }
        //创建Font实例，保存Freetype解析字体结果。
        font = new Font();
        font->font_size = fontSize;
        font->font_file_buffer = font_file_buffer;
        font->ft_library = ft_library;
        font->ft_face = ft_face;
        font_map[fontPath] = font;
        //创建空白的、仅Alpha通道纹理，用于生成文字。
        auto *pixels = (unsigned char *) malloc(font->font_texture_size * font->font_texture_size);
        memset(pixels, 0, font->font_texture_size * font->font_texture_size);
        font->font_texture = Texture2d::Create(font->font_texture_size, font->font_texture_size, GL_RED, GL_RED,
                                               GL_UNSIGNED_BYTE, pixels);
        delete pixels;
        return font;
    }

    void Font::LoadCharacter(char ch) {
        if (character_map[ch] != nullptr) {
            return;
        }
        //加载这个字的字形,加载到 m_FTFace上面去;Glyph：字形，图形字符 [glif];
        FT_Load_Glyph(ft_face, FT_Get_Char_Index(ft_face, ch), FT_LOAD_DEFAULT);
        //从 FTFace上面读取这个字形  到 ft_glyph 变量;
        FT_Glyph ft_glyph;
        FT_Get_Glyph(ft_face->glyph, &ft_glyph);
        //渲染为256级灰度图
        FT_Glyph_To_Bitmap(&ft_glyph, ft_render_mode_normal, 0, 1);
        auto ft_bitmap_glyph = (FT_BitmapGlyph) ft_glyph;
        FT_Bitmap &ft_bitmap = ft_bitmap_glyph->bitmap;

        if (font_texture_fill_x + ft_bitmap.width > font_texture_size) {
            font_texture_fill_x = 0;
            font_texture_fill_y += font_size;
        }
        if (font_texture_fill_y + font_size >= font_texture_size) {
            DEBUG_LOG_ERROR("font texture size is too small!");
            return;
        }
        //glTexSubImage2D
        glBindTexture(GL_TEXTURE_2D, font_texture->gl_texture_id);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexSubImage2D(GL_TEXTURE_2D, 0, font_texture_fill_x, font_texture_fill_y, ft_bitmap.width, ft_bitmap.rows,
                        GL_RED, GL_UNSIGNED_BYTE,
                        ft_bitmap.buffer);
        auto handler = ObjectPool<UpdateTextureSubImage2DHandler>::Get();
        handler->textureHandle = font_texture->textureHandle;
        handler->x = font_texture_fill_x;
        handler->y = font_texture_fill_y;
        handler->width = ft_bitmap.width;
        handler->height = ft_bitmap.rows;
        handler->format = GL_RED;
        handler->type = GL_UNSIGNED_BYTE;
        handler->data = ft_bitmap.buffer;
        handler->dataSize = ft_bitmap.width * ft_bitmap.rows * sizeof(GL_UNSIGNED_BYTE);
        RenderPipeline::GetInstance().AddRenderCommandHandler(handler);

        character_map[ch] = new Character(font_texture_fill_x * 1.0f / font_texture_size,
                                          font_texture_fill_y * 1.0f / font_texture_size,
                                          (font_texture_fill_x + ft_bitmap.width) * 1.0f / font_texture_size,
                                          (font_texture_fill_y + ft_bitmap.rows) * 1.0f / font_texture_size);
        font_texture_fill_x += ft_bitmap.width;
    }

    std::vector<Font::Character *> Font::LoadString(std::string str) {
        for (auto ch: str) {
            LoadCharacter(ch);
        }
        std::vector<Font::Character *> characters;
        for (auto ch: str) {
            auto character = character_map[ch];
            if (character == nullptr) {
                DEBUG_LOG_ERROR("character {} not found!", ch);
                continue;
            }
            characters.push_back(character);
        }
        return characters;
    }
} // DivineBrush