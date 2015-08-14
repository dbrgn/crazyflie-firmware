/**
 * Ultrasonic HC-SR04 expansion board
 *
 * Copyright (C) 2015 Danilo Bargen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ultrasonic.c: Ultrasonic expansion board
 */
#define DEBUG_MODULE "EXP_ULTRASONIC"
#define TRIGGER_DELAY 50

#include "ultrasonic.h"

#include "hcsr04.h"

#include "FreeRTOS.h"
#include "timers.h"

#include "debug.h"


static void ultrasonicTimer(xTimerHandle timer)
{
    hcsr04RequestMeasurement();
}

void ultrasonicInit(void)
{
    DEBUG_PRINT("Initializing ultrasonic expansion board\n");
    hcsr04Init();

    // Register timer for ultrasonic trigger
    xTimerHandle timer = xTimerCreate((const signed char *)"ultrasonicTimer",
                            M2T(TRIGGER_DELAY),
                            pdTRUE, NULL, ultrasonicTimer);
    xTimerStart(timer, 100);
}
