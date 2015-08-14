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
 * hcsr04.c: Ultrasonic HC-SR04 driver
 */
#define DEBUG_MODULE "DRV_HCSR04"

// ST lib includes
#include "stm32fxxx.h"

#include "FreeRTOS.h"
#include "task.h"

#include "debug.h"
#include "ultrasonic.h"


static GPIO_InitTypeDef GPIO_InitStructure;


void hcsr04Init()
{
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;

    // Configure the regulator enable pin
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC, GPIO_Pin_12);

    // Configure trigger pin
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_8); // trigger high

    // Configure echo pin
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;  // Done by module directly
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    DEBUG_PRINT("Initialized HC-SR04 sensor\n");
    GPIO_SetBits(GPIOC, GPIO_Pin_12); // regulator high
}


void hcsr04RequestMeasurement()
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);
    vTaskDelay(M2T(1));
    GPIO_SetBits(GPIOB, GPIO_Pin_8);
}
