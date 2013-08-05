//
//  PhatText.h
//  PhatEngine
//
//  Created by Plus Pingya on 8/3/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#ifndef PHATTEXT_H_INCLUDED
#define PHATTEXT_H_INCLUDED

#include <wchar.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <phat/PhatContext.h>
#include <phat/PhatPlane.h>

#define USE_CHARACTERS L"กขฃคฅฆงจฉชซฌญฎฏฐฑฒณดตถทธนบปผฝพฟภมยรลวศษสหฬอฮะัาิีึืุูแโฤฦำใไabcdefghifklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890 .,+-*/=!@#$%^&*()_"

struct GlyphData {
    int Code;
    FT_Face Face;
};

class GlyphTree {
private:
    struct GlyphNode {
        GlyphData   Data;
        GlyphNode   *Left;
        GlyphNode   *Right;
        GlyphNode(GlyphData data) {
            Data = data;
            Left = NULL;
            Right = NULL;
        }
    };
    int m_Num;
    GlyphNode *m_rootNode;
    
    bool addNode(GlyphNode **node, GlyphData data) {
        if (*node==NULL) {
            *node = new GlyphNode(data);
            m_Num++;
            //NSLog(@"add glyphnode [%d]", m_Num);
            return true;
        }else {
            if (data.Code < (*node)->Data.Code) {
                return addNode(&((*node)->Left), data);
            }else if(data.Code > (*node)->Data.Code) {
                return addNode(&((*node)->Right), data);
            }
        }
        return false;
    }
    
    void removeAllNodes(GlyphNode *node) {
        if (node!=NULL) {
            if (m_Num>0) {
                removeAllNodes(node->Left);
                removeAllNodes(node->Right);
                FT_Done_Face(node->Data.Face);
                delete node;
                node = NULL;
                m_Num--;
                //NSLog(@"remove glyphnode [%d]", m_Num);
            }
        }
    }
    
    GlyphData *getGlyphByCode(GlyphNode *node, int code) {
        GlyphData *r = NULL;
        if (node!=NULL) {
            r = getGlyphByCode(node->Left, code);
            if (r!=NULL) {
                return r;
            }
            r = getGlyphByCode(node->Right, code);
            if (r!=NULL) {
                return r;
            }
            if (node->Data.Code == code) {
                return &node->Data;
            }
        }
        return NULL;
    }
    
public:
    
    GlyphTree() {
        m_rootNode = NULL;
        m_Num = 0;
    }
    
    ~GlyphTree() {
        removeAllNodes();
    }
    
    bool addNode(GlyphData data) {
        return addNode(&m_rootNode, data);
    }
    
    void removeAllNodes() {
        removeAllNodes(m_rootNode);
    }
    
    GlyphData *getGlyphByCode(int code) {
        return getGlyphByCode(m_rootNode, code);
    }
    
};

class PhatText {
private:
    
	FT_Library          _ft;
    int                 _fontSize;
	float               _fontScale;
    OBJ3D_PIVOT_TYPE    _fontPivot;
    
	PhatPlane	*_plane;
	GlyphTree	*_glyphTree;
    
    void _initialize();
    void _release();
    
public:
    
	wchar_t TextBuffer[256];
    col4f Colour;
    
	PhatText(const char *filename, int pixelSize);
	~PhatText();
    
    void DrawText(PhatContext *context, wchar_t *text, vec2f _position);
	void SetFontScale(float _scale);
    void SetPivotType(OBJ3D_PIVOT_TYPE type);
    
};



#endif  //PHATTEXT_H_INCLUDED
