///************************************************************************
/// <copyrigth>2024-2025 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// C Array Object And Managing it's lifecyle
///</describe>
/// <date>2024/1/8</date>
///***********************************************************************
#ifndef BUFFER_H
#define BUFFER_H

#include <memory>
#include <string.h>
#include "Config/BTConfig.h"

template<class T>
class BT_API Buffer
{
public:
    // Construct a buffer with fixed count of elem
    Buffer(std::size_t iLength) : m_iCapacity(iLength),
                            m_iUsedLen(iLength),
                            m_pData(nullptr),
                            m_bIsOnwer(true)
    {
        if (iLength > 0)
        {
            m_pData = new T[iLength];
        }
    }

    // Constrcut a buffer allocated by others
    // Consider pMem maybe nullptr,so we do not give it owner
    Buffer(T *pMem, std::size_t iLength) : m_iCapacity(iLength),
                                     m_iUsedLen(iLength),
                                     m_pData(pMem),
                                     m_bIsOnwer(false)
    {
    }

    // Constrcut a buffer allocated by others,inner will copy it to new one
    Buffer(T *pMem, std::size_t iLength) : m_iCapacity(iLength),
                                     m_iUsedLen(iLength),
                                     m_pData(pMem),
                                     m_bIsOnwer(true)
    {
        if(m_iCapacity > 0)
        {
            m_pData = new T[m_iCapacity];
            std::memcpy(m_pData, pMem, m_iUsedLen * sizeof(T));
        }
    }

    // Copy Buffer
    Buffer(const Buffer &other) : m_iCapacity(other.m_iCapacity),
                                  m_iUsedLen(other.m_iUsedLen),
                                  m_pData(nullptr),
                                  m_bIsOnwer(true)
    {
        if(m_iUsedLen)
        {
            m_pData = new T[m_iUsedLen];
            std::memcpy(m_pData, other.m_pData, m_iUsedLen * sizeof(T));
        }
    }

    // Buffer Assigment, owner transfer to another one 
    Buffer& operator=(const Buffer& other)
    {
        if (this != &other)
        {
            if(m_bIsOnwer)
            {
                delete[] m_pData;
            }

            m_iCapacity = other.m_iCapacity;
            m_iUsedLen = other.m_iUsedLen;
            m_pData = other.m_pData;
            m_bIsOnwer = other.m_bIsOnwer;

            other.m_iCapacity = 0;
            other.m_iUsedLen = 0;
            other.m_pData = nullptr;
            other.m_bIsOnwer = false;
        }
    }

    // Destruct the buffer
    ~Buffer()
    {
        if(m_bIsOnwer)
        {
            Destroy(m_pData);
        }
    }

    // Resize the buffer with a new size
    bool Resize(std::size_t iNewCapacity, bool bIsKeepOldData = true)
    {
        if(!m_bIsOnwer)
        {
            return false;
        }

        if(iNewCapacity != m_iCapacity)
        {
            T* pData = new T[iNewCapacity];
            if(pData == nullptr)
            {
                return false;
            }
            if (bIsKeepOldData)
            {
                std::size_t iCopySize = m_iUsedLen < iNewCapacity ? m_iUsedLen : iNewCapacity;
                std::memcpy(pData, m_pData, iCopySize * sizeof(T));
            }
            Destroy(m_pData);
            m_pData = pData;
            m_iCapacity = iNewCapacity;
        }

        if (iNewCapacity < m_iUsedLen)
        {
            m_iUsedLen = iNewCapacity;
        }

        return true;
    }

    // Assign an array
    void Assign(const T *pData, std::size_t iSize)
    {
        if(iSize == 0)
        {
            return;
        }

        if(m_iCapacity < iSize)
        {
            Resize(iSize,false);
        }

        std::memcpy(m_pData, pData, iSize * sizeof(T));
        m_iUsedLen = iSize;
    }
   
    // Begin of buffer
    T* Begin()
    {
        return m_pData;
    }

    // Begin of buffer
    const T* Begin()
    {
        return m_pData;
    }

    // End of buffer
    T* End()
    {
        return m_pData + m_iUsedLen;
    }

    // End of buffer
    const T* End()
    {
        return m_pData + m_iUsedLen;
    }

    // Is buffer empty
    bool IsEmpty()
    {
        return m_iUsedLen == 0;
    }

    // Clear the buffer
    void Clear()
    {
        std::memset(m_pData, 0, m_iUsedLen * sizeof(T));
    }

    // Get capacity
    std::size_t GetCapacity()
    {
        return m_iCapacity;
    }

    // Get buffer size
    std::size_t GetSize()
    {
        return m_iUsedLen;
    }

    // Get data
    T& operator[](std::size_t iIndex)
    {
        if(iIndex < m_iUsedLen)
        {
            return m_pData[iIndex];
        }

        return m_ReferData;
    }

    // Get data
    const T& operator[](std::size_t iIndex)
    {
        if(iIndex < m_iUsedLen)
        {
            return m_pData[iIndex];
        }

        return m_ReferData;
    }

    // Append data to the buffer
    void Append(const T *pData, std::size_t iSize)
    {
        if(iSize == 0)
        {
            return;
        }
        Resize(m_iUsedLen + iSize, true);
        std::memcpy(m_pData + m_iUsedLen - iSize, pData, iSize * sizeof(T));
    }

    // Append an element
    void Append(T Data)
    {
        Resize(m_iUsedLen + 1, true);
        m_pData[m_iUsedLen - 1] = Data;
    }

    // Append a buffer
    void Append(const Buffer& other)
    {
        Append(other.Begin(), other.GetSize());
    }

    // Is two buffer equaled
    bool operator==(const Buffer& other) const
    {
        if(this != &other)
        {
            if(m_iUsedLen == other.m_iUsedLen)
            {
                if (m_pData && other.m_pData && std::memcmp(m_pData, other.m_pData, m_iUsedLen * sizeof(T)) == 0)
                {
                    return true;
                }
                else
                {
                    return m_iUsedLen == 0;
                }
            }
        }

        return true;
    }

    // Is one != another
    bool operator!=(const Buffer& other) const
    {
        return !(*this == other);
    }

private:
    // Construt empty buffer is not allowed
    Buffer(){   }

    // Destroy the continous buffer
    void Destroy(T* pData)
    {
        if (pData)
        {
            delete[] pData;
        }
    }

private:
    // Capacity
    std::size_t m_iCapacity;

    // Used length
    std::size_t m_iUsedLen;

    // Data pointer
    T* m_pData;

    // Data refer
    T m_ReferData;

    // Is owner
    bool m_bIsOnwer;
};

#endif // BUFFER_H
