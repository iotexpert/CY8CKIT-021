/*******************************************************************************
* File Name: therm.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "therm.h"

static therm_BACKUP_STRUCT  therm_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: therm_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet therm_SUT.c usage_therm_Sleep_Wakeup
*******************************************************************************/
void therm_Sleep(void)
{
    #if defined(therm__PC)
        therm_backup.pcState = therm_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            therm_backup.usbState = therm_CR1_REG;
            therm_USB_POWER_REG |= therm_USBIO_ENTER_SLEEP;
            therm_CR1_REG &= therm_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(therm__SIO)
        therm_backup.sioState = therm_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        therm_SIO_REG &= (uint32)(~therm_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: therm_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to therm_Sleep() for an example usage.
*******************************************************************************/
void therm_Wakeup(void)
{
    #if defined(therm__PC)
        therm_PC = therm_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            therm_USB_POWER_REG &= therm_USBIO_EXIT_SLEEP_PH1;
            therm_CR1_REG = therm_backup.usbState;
            therm_USB_POWER_REG &= therm_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(therm__SIO)
        therm_SIO_REG = therm_backup.sioState;
    #endif
}


/* [] END OF FILE */
