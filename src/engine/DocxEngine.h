#pragma once
#include <string>
#include <vector>

struct DocxStyle {
    std::string name;
    std::string fontFamily;
    int         fontSize;
    std::string color;
};

class DocxEngine {
public:
    DocxEngine();
    ~DocxEngine();

    bool open(const std::string& filePath);
    bool save(const std::string& filePath);
    bool applyStyle(const DocxStyle& style);
    std::vector<DocxStyle> getStyles();

private:
    std::string            m_filePath;
    std::string            m_xmlContent;
    bool                   m_isLoaded;
    std::vector<DocxStyle> m_styles;

    void parseStyles();
    bool writeDocx(const std::string& path);
};