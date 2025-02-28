/******************************************************************/
/*!
	@file	IO.h
	@brief	Defined I/O objects
	@note
	@todo
	@bug	

	@author	Naoto Nakamura
	@date	Apl. 1, 2009
*/
/******************************************************************/


#ifndef S3D_FOUNDATION_IO_H
#define S3D_FOUNDATION_IO_H

#include "S3D/Common.h"

#include <iostream>

namespace S3D{
    //////////////////////////////////////////////////////
    //				forward declarations				//
    //////////////////////////////////////////////////////
    //implemented
    class IO;

    //////////////////////////////////////////////////////
    //				const declarations					//
    //////////////////////////////////////////////////////

    //////////////////////////////////////////////////////
    //				class declarations					//
    //////////////////////////////////////////////////////
    /****************************************/
    /*!
        @class	IO
        @brief	Abstract object for input output
        @note	
        @author	Naoto Nakamura
        @date	Apl. 1, 2009
    */
    /****************************************/
    class IO
    {
    public:
        IO(): mOpenMode(0){}

        enum{
            READ = std::ios::in,
            WRITE = std::ios::out,
            APPEND  = std::ios::app,
            BINARY = std::ios::binary,
        };
        
        enum{
            BEGIN = std::ios::beg,
            CURRENT = std::ios::cur,
            END  = std::ios::end,
        };

    public:
        virtual bool isOpened() = 0;

        virtual bool open(int mode){mOpenMode = mode; return TRUE;}
        virtual void close() = 0;

        int getOpenMode() const {return mOpenMode;}

        virtual size_t read(void *buffer, const size_t size) = 0;
        virtual bool read(char &c) = 0;
        virtual bool read(unsigned char &c) = 0;
        virtual bool read(int &i) = 0;
        virtual bool read(unsigned int &i) = 0;
        virtual bool read(float &f) = 0;

        virtual bool write(const std::string &buffer) = 0;
        virtual bool write(const char *buffer) = 0;
        virtual bool write(const char c) = 0;
        virtual bool write(const unsigned char c) = 0;
        virtual bool write(const int i) = 0;
        virtual bool write(const unsigned int i) = 0;
        virtual bool write(const float f) = 0;
        
        virtual bool seekGet(const size_t offset, const size_t origin) = 0;
        virtual bool seekPut(const size_t offset, const size_t origin) = 0;
        
        virtual size_t tellGet() = 0;
        virtual size_t tellPut() = 0;
        
        virtual bool peek(unsigned char &c) = 0;
        
        virtual bool end() = 0;

    protected:
        int mOpenMode;
    };
    
    /****************************************/
    /*!
        @class	StandardInput
        @brief
        @note
        @author	Naoto Nakamura
        @date	Apl. 1, 2009
        */
    /****************************************/
    class Input
    {
    public:
        Input(){}
        
    public:
        virtual bool open() = 0;
        
        virtual void close() = 0;
        
        virtual bool isOpened() = 0;
        
        virtual size_t read(void *buffer, const size_t size) = 0;
        virtual bool read(char &c) = 0;
        virtual bool read(unsigned char &c) = 0;
        virtual bool read(int &i) = 0;
        virtual bool read(unsigned int &i) = 0;
        virtual bool read(float &f) = 0;
        
        virtual bool seek(const size_t offset, const size_t origin) = 0;
        virtual size_t tell() = 0;
        
        virtual bool peek(unsigned char &c) = 0;
        
        virtual bool end() = 0;
    };
    
    
    /****************************************/
    /*!
        @class	StandardOutput
        @brief
        @note
        @author	Naoto Nakamura
        @date	Apr. 1, 2009
        */
    /****************************************/
    class Output
    {
    public:
        Output(){}
        
    public:
        virtual bool open() = 0;
        virtual void close() = 0;
        
        virtual bool isOpened() = 0;
        
        virtual bool write(const std::string &buffer) = 0;
        virtual bool write(const char *buffer) = 0;
        virtual bool write(const char c) = 0;
        virtual bool write(const unsigned char c) = 0;
        virtual bool write(const int i) = 0;
        virtual bool write(const unsigned int i) = 0;
        virtual bool write(const float f) = 0;
        
        virtual bool seek(const size_t offset, const size_t origin) = 0;
        virtual size_t tell() = 0;
    };

    
};	//namespace S3D

#endif //S3D_FOUNDATION_IO_H
