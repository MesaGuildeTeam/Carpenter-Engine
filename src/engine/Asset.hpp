#ifndef ENGINE_ASSET
#define ENGINE_ASSET

#include <string>

#include "Utils.hpp"

namespace Engine {

    enum AssetSource {
        UNLOADED,
        GAMEFILE,
        LOCALSTORAGE,
    };

    /** 
     * @brief a file you can load from within Carpenter Engine
     *
     * Similar to std::ifstream, this class reads game files as needed
     *
     * This class looks for files in the following:
     *
     * - Check if the file is embedded into the project
     * - Check if the data is saved in the localStorage API
     * - Performs an HTTP GET Request for the file
     *
     */
    class iAsset {
        private:
        
        AssetRequest m_assetStatus;
        AssetSource m_assetSource;
        std::string m_dataAsString;

        unsigned int m_index{0};

        public:

        iAsset();

        iAsset(const char* path);

        ~iAsset();

        void Open(const char* path);

        /**
         * @brief writes the next n bits into c
         * 
         * @param c the reference to the string pointer
         * @param n the number of bits required
         */
        iAsset& Read(char* c, unsigned int n);

        void Close();

        iAsset& operator>>(std::string& rhs);

        /**
         * @brief returns all of the data in the file 
         * 
         * @return a pointer to all the data 
         */
        unsigned char* GetData();

        /**
         * @brief returns the number of bytes remaining
         * 
         * @return number of bytes remaining 
         */
        unsigned int GetSize();

        /**
         * @brief Returns if the file is open or not
         *
         * @warning If you called `Open()` and this still returns false, you
         * may need to wait some more time. This can happen if the file was
         * obtained with an HTTP request.
         * 
         * @return true if the file is both open and ready
         */
        bool IsOpen();

        /**
         * @brief returns if the file is closed and not opening
         *
         * if the `Open()' is called, then this will return 
         * 
         * @return true if the file is closed and not opening
         */
        bool IsClosed();

        /**
         * @brief Get the source of the file
         *
         * Some files are statically defined while others are from the users's
         * device. Use this to keep track of the origin of the file 
         * 
         * @return the origin of the asset
         */
        AssetSource GetAssetSource();
    };

    /**
     * @brief loads a file to write to
     *
     * The engine will search for the file through the following process: 
     * - Ensure the file does not exist as a static asset 
     * - Pick the file in the browser's localStorage
     */
    class oAsset {
        private:

        std::string m_data;
        const char* m_path;
        AssetSource m_assetSource;

        public:

        oAsset();

        ~oAsset();

        oAsset(const char* path);

        void Open(const char* path);

        /**
         * @brief Saves and closes the file
         * 
         */
        void Close();

        bool IsOpen();

        bool IsClosed();

        void Put(const char c);

        void Write(std::string data);
    };

    typedef iAsset Asset;
}

#endif