#include "Asset.hpp"
#include <emscripten.h>

#include <fstream>
#include <iostream>
#include <streambuf>

Engine::iAsset::iAsset() {

}

Engine::iAsset::iAsset(const char* path) : Engine::iAsset() {
    Open(path);
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

    // If Asset is not embedded
    emscripten_async_wget_data(path, (void*)&m_assetStatus,
      [](void* arg, void* d, int s) {
        AssetRequest* req = (AssetRequest*)arg;
        req->data = new unsigned char[s];
        memcpy((void*)req->data, d, s);
        req->size = s;
        req->req_state = 2;
      }, nullptr);
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