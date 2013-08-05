//
//  PhatText.cpp
//  PhatEngine
//
//  Created by Plus Pingya on 8/3/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#include <phat/PhatText.h>

/////////////////////////////////////////////////////////
// Constructor - Intialize
void PhatText::_initialize() {
    SetFontScale(1.0f);
    _fontPivot = TOP_LEFT;
    _fontSize = 32;
    Colour.set(1.0f, 1.0f, 1.0f, 1.0f);
}
PhatText::PhatText(const char *filename, int pixelSize) {
    _initialize();
    _fontSize = pixelSize;
    int t_size = 0;
#ifdef ANDROID
    /*
	struct zip_stat st;
	zip_stat_init(&st);
	zip_stat(APKArchive, filename, 0, &st);
    
	FT_Byte *contents = new FT_Byte[st.size];
    
	zip_file *f = zip_fopen(APKArchive, filename, 0);
	zip_fread(f, contents, st.size);
	zip_fclose(f);
     
     t_size = st.size;
     */
#elif TARGET_OS_IPHONE || TARGET_OS_IPHONE_SIMULATOR //__APPLE__
    // Load Font File
    NSString *t_sfilename = [NSString stringWithUTF8String: filename];
    NSArray *_splitfilename = [t_sfilename componentsSeparatedByString:@"."];
	NSString *t_path = [[NSBundle mainBundle] pathForResource:[_splitfilename objectAtIndex:0] ofType:[_splitfilename objectAtIndex:1]];
	NSData *t_data = [[NSData alloc] initWithContentsOfFile:t_path];
    t_size = [t_data length];
    FT_Byte *contents = new FT_Byte[t_size];
    memcpy(contents, [t_data bytes], t_size);
    if (contents == nil) {
        NSLog(@"Do real error checking with Font %s", filename);
    }
#endif
	if(FT_Init_FreeType(&_ft)) {
		return;
	}
	_plane = new PhatPlane(vec2f(20));
	unsigned char tmp[] = {0};
	_plane->Texture = new PhatTexture(vec2d(1, 1), tmp);
	_glyphTree = new GlyphTree();
    int n = wcslen(USE_CHARACTERS);
	for(int i=0; i<n; i++) {
		FT_Face face;
#if ANDROID || TARGET_OS_IPHONE || TARGET_OS_IPHONE_SIMULATOR
        FT_New_Memory_Face(_ft, contents, t_size, 0, &face);
#else
        FT_New_Face(_ft, filename, 0, &face);
#endif
		FT_Set_Pixel_Sizes(face, 0, pixelSize);
		FT_Load_Char(face, USE_CHARACTERS[i], FT_LOAD_RENDER);
		GlyphData d;
		d.Code = (int)USE_CHARACTERS[i];
		d.Face = face;
		_glyphTree->addNode(d);
	}
}

/////////////////////////////////////////////////////////
// Destructor - Release
void PhatText::_release() {
    delete _glyphTree;
	FT_Done_FreeType(_ft);
	delete _plane;
}
PhatText::~PhatText() {
	_release();
}

/////////////////////////////////////////////////////////
// Core functions - must be called
void PhatText::DrawText(PhatContext *context, wchar_t *text, vec2f _position) {
	float start 	= _position.x;
	float baseline 	= _position.y;
	GlyphData *glyph = NULL;
	int i, j = wcslen(text), length = 0;
    for (i=0; i<j; i++) {
        glyph = _glyphTree->getGlyphByCode((int)text[i]);
		if(glyph!=NULL) {
            length += (int(glyph->Face->glyph->advance.x*_fontScale) >> 6);
        }
    }
	for(i = 0; i<j; i++) {
		glyph = _glyphTree->getGlyphByCode((int)text[i]);
		if(glyph!=NULL) {
			_plane->Texture->TexImage(vec2d(glyph->Face->glyph->bitmap.width, glyph->Face->glyph->bitmap.rows), glyph->Face->glyph->bitmap.buffer);
			rec4f dest;
			dest.w = int(glyph->Face->glyph->bitmap.width*_fontScale);
			dest.h = int(glyph->Face->glyph->bitmap.rows*_fontScale);
			dest.x = start + (int(glyph->Face->glyph->metrics.horiBearingX*_fontScale) >> 6);
			dest.y = baseline - (int(glyph->Face->glyph->metrics.horiBearingY*_fontScale) >> 6);
			_plane->Size.set(dest.w, dest.h);
			_plane->SetPivotType(TOP_LEFT);
            switch (_fontPivot) {
                default:
                case TOP_LEFT:
                    _plane->Position.set(dest.x, dest.y+_fontSize);
                    break;
                case TOP_MIDDLE:
                    _plane->Position.set(dest.x-int(length/2.0f), dest.y+_fontSize);
                    break;
                case TOP_RIGHT:
                    _plane->Position.set(dest.x-length, dest.y+_fontSize);
                    break;
                case MIDDLE_LEFT:
                    _plane->Position.set(dest.x, dest.y+int(_fontSize/2.0f));
                    break;
                case CENTRE:
                    _plane->Position.set(dest.x-int(length/2.0f), dest.y+int(_fontSize/2.0f));
                    break;
                case MIDDLE_RIGHT:
                    _plane->Position.set(dest.x-length, dest.y+int(_fontSize/2.0f));
                    break;
                case BOTTOM_LEFT:
                    _plane->Position.set(dest.x, dest.y);
                    break;
                case BOTTOM_MIDDLE:
                    _plane->Position.set(dest.x-int(length/2.0f), dest.y);
                    break;
                case BOTTOM_RIGHT:
                    _plane->Position.set(dest.x-length, dest.y);
                    break;
            }
            _plane->Colour.copy(Colour);
			_plane->Render(context);
			start += (int(glyph->Face->glyph->advance.x*_fontScale) >> 6);
		}
	}
}

/////////////////////////////////////////////////////////
// Optional functions
void PhatText::SetFontScale(float _scale) {
	_fontScale = _scale;
}
void PhatText::SetPivotType(OBJ3D_PIVOT_TYPE type) {
    _fontPivot = type;
}