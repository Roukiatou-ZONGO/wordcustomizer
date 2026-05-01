#include "DocxEngine.h"
#include <iostream>
#include <fstream>

DocxEngine::DocxEngine() : m_isLoaded(false) {
    std::cout << "DocxEngine initialisé." << std::endl;
}

DocxEngine::~DocxEngine() {}

bool DocxEngine::open(const std::string& filePath) {
    m_filePath = filePath;
    std::cout << "Ouverture du fichier : " << filePath << std::endl;
    m_isLoaded = extractDocx(filePath);
    return m_isLoaded;
}

bool DocxEngine::save(const std::string& filePath) {
    if (!m_isLoaded) return false;
    return writeDocx(filePath);
}

bool DocxEngine::extractDocx(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.good()) {
        std::cerr << "Erreur : fichier introuvable." << std::endl;
        return false;
    }
    std::cout << "Fichier .docx lu avec succès." << std::endl;
    return true;
}

bool DocxEngine::writeDocx(const std::string& path) {
    std::cout << "Sauvegarde vers : " << path << std::endl;
    return true;
}

bool DocxEngine::applyStyle(const DocxStyle& style) {
    if (!m_isLoaded) return false;
    std::cout << "Application du style : " << style.name << std::endl;
    return true;
}

std::vector<DocxStyle> DocxEngine::getStyles() {
    return {};
}