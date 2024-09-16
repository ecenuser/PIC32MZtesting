/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

#define ADC_VREF                (3.3f)
#define ADC_MAX_COUNT           (4095)

uint16_t adc_count;
float input_voltage;
uint8_t adcValue[2];  
float analogVoltage;
uint16_t adcResult;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
int main ( void )
{
   
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    printf("\n\r---------------------------------------------------------");
    printf("\n\r                    ADC Polled Mode Demo                 ");
    printf("\n\r---------------------------------------------------------\n\r"); 
    
    TMR3_Start();
     LATJbits.LATJ7 = 1;
    
    TRISJbits.TRISJ7 = 0;  // Set RJ7 as output (clear bit 7)
    
   // uint16_t adcValue;
    //    uint16_t txData =0x0800; //selecting in2
     //   LATCbits.LATC2 = 1;  // Bring CS low before SPI transfer
      //  SPI3_WriteRead(&txData, 2, &adcValue, 2);
       // LATBbits.LATB15 = 0;  // Bring CS high after SPI transfer
     //   adcValue = adcValue >> 4;

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
        uint16_t txData =0x08; //selecting in2
        //Cbits.LATC2 = 1;  // Bring CS low before SPI transfer
     //   SPI3_WriteRead(&txData, 1, adcValue, 2);
      
        //adcResult = (adcValue >> 4);
       // adcResult = ((adcValue[0] << 8) | adcValue[1]) >> 4;  // Shift to remove unused bits
        
       // analogVoltage = ((float)adcResult / 4095.0) * ADC_VREF;
         //analogVoltage = (float)adcResult;
     //   printf("\n\rAnalog Voltage: %.3f V\n", analogVoltage);
        if (PORTJbits.RJ4 == 0) {  // Check if SW1 is pressed (active low)
            printf("\n\rSW1 is pressed\n");
             LATJbits.LATJ7 = 0;  // Set RJ7 high (turn on LED1)
            
        } else {
            printf("\n\rSW1 is not pressed\n");
             LATJbits.LATJ7 = 1;  // Set RJ7 high (turn on LED1)
        }
        
        
        /* Wait till ADC conversion result is available */
        while(!ADCHS_ChannelResultIsReady(ADCHS_CH2))
        {

        };
       // while (ADCCON2bits.REFFLT != 0);  // Ensure no reference voltage fault

        /* Read the ADC result */
        int16_t adc_count = (int16_t)ADCHS_ChannelResultGet(ADCHS_CH2);

        //adc_count = ADCHS_ChannelResultGet(ADCHS_CH2);
        input_voltage = (float)adc_count * ADC_VREF / ADC_MAX_COUNT; //for single ended
       // input_voltage = (float)adc_count * ADC_VREF / ADC_MAX_COUNT * 2;


        printf("ADC Count = 0x%03x, ADC Input Voltage = %d.%02d V \r", adc_count, (int)input_voltage, (int)((input_voltage - (int)input_voltage)*100.0));        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

