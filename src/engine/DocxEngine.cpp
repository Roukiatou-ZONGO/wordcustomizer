#include "DocxEngine.h"
#include <zip.h>
#include <pugixml.hpp>
#include <iostream>
#include <vector>

DocxEngine::DocxEngine() : m_isLoaded(false) {
    std::cout << "DocxEngine initialisé." << std::endl;
}

DocxEngine::~DocxEngine() {}

bool DocxEngine::open(const std::string& filePath) {
    m_filePath = filePath;

    int err = 0;
    zip_t* archive = zip_open(filePath.c_str(), ZIP_RDONLY, &err);

    if (!archive) {
        std::cerr << "Erreur : impossible d'ouvrir " << filePath << std::endl;
        return false;
    }

    // Lire word/styles.xml
    zip_file_t* stylesFile = zip_fopen(archive, "word/styles.xml", 0);
    if (stylesFile) {
        std::vector<char> buffer(65536);
        zip_int64_t bytesRead = zip_fread(stylesFile, buffer.data(), buffer.size());
        if (bytesRead > 0) {
            m_xmlContent = std::string(buffer.data(), bytesRead);
            std::cout << "styles.xml lu : "
                      << bytesRead << " octets" << std::endl;
            parseStyles();
        }
        zip_fclose(stylesFile);
    }

    zip_close(archive);
    m_isLoaded = true;
    return true;
}

void DocxEngine::parseStyles() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(m_xmlContent.c_str());

    if (!result) {
        std::cerr << "Erreur XML : " << result.description() << std::endl;
        return;
    }

    m_styles.clear();
    auto stylesNode = doc.child("w:styles");
    for (auto styleNode : stylesNode.children("w:style")) {
        DocxStyle style;
        style.name = styleNode.child("w:name")
                              .attribute("w:val").as_string();
        auto rPr = styleNode.child("w:rPr");
        style.fontFamily = rPr.child("w:rFonts")
                              .attribute("w:ascii").as_string("Default");
        style.fontSize   = rPr.child("w:sz")
                              .attribute("w:val").as_int(24) / 2;
        style.color      = rPr.child("w:color")
                              .attribute("w:val").as_string("000000");
        if (!style.name.empty()) {
            m_styles.push_back(style);
            std::cout << "Style trouvé : " << style.name
                      << " | Police : " << style.fontFamily
                      << " | Taille : " << style.fontSize << "pt"
                      << std::endl;
        }
    }
}

bool DocxEngine::save(const std::string& filePath) {
    if (!m_isLoaded) return false;
    std::cout << "Sauvegarde vers : " << filePath << std::endl;
    return true;
}

bool DocxEngine::applyStyle(const DocxStyle& style) {
    if (!m_isLoaded) return false;
    std::cout << "Application du style : " << style.name << std::endl;
    return true;
}

std::vector<DocxStyle> DocxEngine::getStyles() {
    return m_styles;
}