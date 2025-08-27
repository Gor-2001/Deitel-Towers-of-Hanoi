// cross_platform_conio.h
// Header file for cross-platform console functions.

#ifndef CROSS_PLATFORM_CONIO_H
#define CROSS_PLATFORM_CONIO_H

#include <cstdlib>

void gotoxy(const int x, const int y);

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
#elif defined(__unix__)
    
#else
    #error "Unsupported platform. Cannot define SLEEP(n)."
#endif

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define SLEEP(n) Sleep(n)
#elif defined(__unix__)
    #include <unistd.h>
    #define SLEEP(n) usleep((n) * 1000)
#else
    #error "Unsupported platform. Cannot define SLEEP(n)."
#endif


#if defined(_WIN32) || defined(_WIN64)
    #define CLEAR_SCREEN() system("cls")
#elif defined(__unix__)
    #define CLEAR_SCREEN() system("clear"); 
#else
    #error "Unsupported platform. Cannot define CLEAR_SCREEN()."
#endif

#if defined(_WIN32) || defined(_WIN64)
    #define ENTER_VALUE 13
#elif defined(__unix__)
    #define ENTER_VALUE 13
#else
    #error "Unsupported platform. Cannot define values for keys."
#endif  



#endif // CROSS_PLATFORM_CONIO_H
