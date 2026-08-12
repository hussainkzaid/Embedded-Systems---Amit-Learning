/*
 * main.c
 *
 * Entry point for the Smart Home System.
 *
 * Responsibility: Wire up the application — call App_voidInit() once,
 *                 then run App_voidRun() in an infinite loop.
 *
 * Layer:          Entry Point (above Application Layer)
 * Depends on:     Application/AppManager
 */

#include "Application/AppManager/AppManager_interface.h"

int main(void)
{
    App_voidInit();

    while (1)
    {
        App_voidRun();
    }
}

