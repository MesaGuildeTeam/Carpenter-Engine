#include "Asset.hpp"
#include <emscripten.h>
#include <emscripten/val.h>

#include <fstream>
#include <iostream>
#include <streambuf>

Engine::iAsset::iAsset() {

}

Engine::iAsset::iAsset(const char* path) : Engine::iAsset() {
    Open(path);
}

Engine::iAsset::~iAsset() {
    Close();
}

void Engine::iAsset::Open(const char* path) {
    m_assetStatus.req_state = 1;

    // Try to find file first
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file.fail()) {
        std::cout << "DEBUG: Found Embedded Asset " << path << std::endl;
        std::filebuf* pbuf = file.rdbuf();
        m_assetStatus.size = pbuf->pubseekoff(0, file.end, file.in);
        pbuf->pubseekpos(0, file.in);

        m_assetStatus.data = new unsigned char[m_assetStatus.size];

        pbuf->sgetn((char*)m_assetStatus.data, m_assetStatus.size);

        file.close();

        m_assetStatus.req_state = 2;

        return;
    }

    using emscripten::val;

    // If Asset is not embedded check LocalStorage if it is saved
    bool success = EM_ASM_INT({
        game.tempItem = localStorage.getItem(UTF8ToString($0));
        if (game.tempItem == undefined) return false;
        return true;
    }, path);

    if (success) { 
        m_assetStatus.size = EM_ASM_INT({return game.tempItem.length;});
        
        m_assetStatus.data = new unsigned char[m_assetStatus.size + 1];
        EM_ASM({
            stringToUTF8(game.tempItem, $0, game.tempItem.length + 1); 
        }, m_assetStatus.data);

        m_assetStatus.req_state = 2;
        return;
    }

    // Otherwise fallback to HTTP Request
    std::cout << "DEBUG: Fetching asset " << path << std::endl;
    emscripten_async_wget_data(path, (void*)&m_assetStatus,
      [](void* arg, void* d, int s) {
        AssetRequest* req = (AssetRequest*)arg;
        req->data = new unsigned char[s];
        memcpy((void*)req->data, d, s);
        req->size = s;
        req->req_state = 2;
      }, [](void* arg) {
        AssetRequest* req = (AssetRequest*)arg;
        req->data = new unsigned char[1];
        req->data[0] = 0;
        req->size = 1;
        req->req_state = 2;
      });
}

Engine::iAsset& Engine::iAsset::Read(char* c, unsigned int n) { 
    #warning TODO
}

void Engine::iAsset::Close() {
    delete m_assetStatus.data;
}

Engine::iAsset& Engine::iAsset::operator>>(std::string& rhs) {
    #warning TODO
}

unsigned char* Engine::iAsset::GetData() {
    return m_assetStatus.data;
}

unsigned int Engine::iAsset::GetSize() {
    return m_assetStatus.size;
}

bool Engine::iAsset::IsOpen() {
    return m_assetStatus.req_state == 2;
}

bool Engine::iAsset::IsClosed() {
    return m_assetStatus.req_state == 0;
}

Engine::AssetSource Engine::iAsset::GetAssetSource() {
    return Engine::AssetSource::UNLOADED;
}

/// oAsset ///

Engine::oAsset::oAsset() {

}

Engine::oAsset::oAsset(const char* path): Engine::oAsset() {
    Open(path); 
}

Engine::oAsset::~oAsset() {
    Close();
}

void Engine::oAsset::Open(const char* path) {
    // Do a file check to make sure it's not a game asset
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file.fail()) throw std::runtime_error("ERROR: File is write only... Probably a game asset...");

    // Create the data
    m_path = path;
    m_data = std::string("");
    m_assetSource = Engine::LOCALSTORAGE;
}

void Engine::oAsset::Close() {
    EM_ASM({
        localStorage.setItem(UTF8ToString($0), UTF8ToString($1));
    }, m_path, m_data.c_str());
}

bool Engine::oAsset::IsClosed() {
    return m_assetSource == UNLOADED;
}

bool Engine::oAsset::IsOpen() {
    return m_assetSource != UNLOADED;
}

void Engine::oAsset::Put(const char c) {
    m_data = m_data + c;
}

void Engine::oAsset::Write(std::string data) { 
    m_data = m_data + data;
}