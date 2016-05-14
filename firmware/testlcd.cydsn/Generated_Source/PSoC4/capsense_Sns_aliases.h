/*******************************************************************************
* File Name: capsense_Sns.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_capsense_Sns_ALIASES_H) /* Pins capsense_Sns_ALIASES_H */
#define CY_PINS_capsense_Sns_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define capsense_Sns_0			(capsense_Sns__0__PC)
#define capsense_Sns_0_PS		(capsense_Sns__0__PS)
#define capsense_Sns_0_PC		(capsense_Sns__0__PC)
#define capsense_Sns_0_DR		(capsense_Sns__0__DR)
#define capsense_Sns_0_SHIFT	(capsense_Sns__0__SHIFT)
#define capsense_Sns_0_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__0__SHIFT*2u)))

#define capsense_Sns_1			(capsense_Sns__1__PC)
#define capsense_Sns_1_PS		(capsense_Sns__1__PS)
#define capsense_Sns_1_PC		(capsense_Sns__1__PC)
#define capsense_Sns_1_DR		(capsense_Sns__1__DR)
#define capsense_Sns_1_SHIFT	(capsense_Sns__1__SHIFT)
#define capsense_Sns_1_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__1__SHIFT*2u)))

#define capsense_Sns_INTR_ALL	 ((uint16)(capsense_Sns_0_INTR| capsense_Sns_1_INTR))
#define capsense_Sns_Button0__BTN			(capsense_Sns__Button0__BTN__PC)
#define capsense_Sns_Button0__BTN_PS		(capsense_Sns__Button0__BTN__PS)
#define capsense_Sns_Button0__BTN_PC		(capsense_Sns__Button0__BTN__PC)
#define capsense_Sns_Button0__BTN_DR		(capsense_Sns__Button0__BTN__DR)
#define capsense_Sns_Button0__BTN_SHIFT	(capsense_Sns__Button0__BTN__SHIFT)
#define capsense_Sns_Button0__BTN_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__0__SHIFT*2u)))

#define capsense_Sns_Button1__BTN			(capsense_Sns__Button1__BTN__PC)
#define capsense_Sns_Button1__BTN_PS		(capsense_Sns__Button1__BTN__PS)
#define capsense_Sns_Button1__BTN_PC		(capsense_Sns__Button1__BTN__PC)
#define capsense_Sns_Button1__BTN_DR		(capsense_Sns__Button1__BTN__DR)
#define capsense_Sns_Button1__BTN_SHIFT	(capsense_Sns__Button1__BTN__SHIFT)
#define capsense_Sns_Button1__BTN_INTR	((uint16)((uint16)0x0003u << (capsense_Sns__1__SHIFT*2u)))


#endif /* End Pins capsense_Sns_ALIASES_H */


/* [] END OF FILE */
