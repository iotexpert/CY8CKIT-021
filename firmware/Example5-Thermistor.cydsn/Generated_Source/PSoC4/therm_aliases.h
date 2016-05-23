/*******************************************************************************
* File Name: therm.h  
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

#if !defined(CY_PINS_therm_ALIASES_H) /* Pins therm_ALIASES_H */
#define CY_PINS_therm_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define therm_0			(therm__0__PC)
#define therm_0_PS		(therm__0__PS)
#define therm_0_PC		(therm__0__PC)
#define therm_0_DR		(therm__0__DR)
#define therm_0_SHIFT	(therm__0__SHIFT)
#define therm_0_INTR	((uint16)((uint16)0x0003u << (therm__0__SHIFT*2u)))

#define therm_INTR_ALL	 ((uint16)(therm_0_INTR))


#endif /* End Pins therm_ALIASES_H */


/* [] END OF FILE */
