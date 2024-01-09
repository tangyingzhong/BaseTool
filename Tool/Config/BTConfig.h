///************************************************************************
/// <copyrigth>2024-2025 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Cross-Platform export configuration
///</describe>
/// <date>2024/1/8</date>
///***********************************************************************
#ifndef BTCONFIG_H
#define BTCONFIG_H

#ifdef _WIN32
    #ifdef EXPORT_CLASS
        #define BT_API __declspec(dllexport)
    #else
        #define BT_API __declspec(dllimport)
    #endif
#endif

#ifdef __APPLE__
    #if EXPORT_CLASS
       #define BT_API __attribute__ ((visibility ("default")))
    #else
        #define BT_API
    #endif
#endif

#endif // BTCONFIG_H