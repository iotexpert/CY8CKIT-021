/*******************************************************************************
* File Name: therm.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_therm_H) /* Pins therm_H */
#define CY_PINS_therm_H

#include "cytypes.h"
#include "cyfitter.h"
#include "therm_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} therm_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   therm_Read(void);
void    therm_Write(uint8 value);
uint8   therm_ReadDataReg(void);
#if defined(therm__PC) || (CY_PSOC4_4200L) 
    void    therm_SetDriveMode(uint8 mode);
#endif
void    therm_SetInterruptMode(uint16 position, uint16 mode);
uint8   therm_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void therm_Sleep(void); 
void therm_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(therm__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define therm_DRIVE_MODE_BITS        (3)
    #define therm_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - therm_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the therm_SetDriveMode() function.
         *  @{
         */
        #define therm_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define therm_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define therm_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define therm_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define therm_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define therm_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define therm_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define therm_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define therm_MASK               therm__MASK
#define therm_SHIFT              therm__SHIFT
#define therm_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in therm_SetInterruptMode() function.
     *  @{
     */
        #define therm_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define therm_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define therm_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define therm_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(therm__SIO)
    #define therm_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(therm__PC) && (CY_PSOC4_4200L)
    #define therm_USBIO_ENABLE               ((uint32)0x80000000u)
    #define therm_USBIO_DISABLE              ((uint32)(~therm_USBIO_ENABLE))
    #define therm_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define therm_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define therm_USBIO_ENTER_SLEEP          ((uint32)((1u << therm_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << therm_USBIO_SUSPEND_DEL_SHIFT)))
    #define therm_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << therm_USBIO_SUSPEND_SHIFT)))
    #define therm_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << therm_USBIO_SUSPEND_DEL_SHIFT)))
    #define therm_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(therm__PC)
    /* Port Configuration */
    #define therm_PC                 (* (reg32 *) therm__PC)
#endif
/* Pin State */
#define therm_PS                     (* (reg32 *) therm__PS)
/* Data Register */
#define therm_DR                     (* (reg32 *) therm__DR)
/* Input Buffer Disable Override */
#define therm_INP_DIS                (* (reg32 *) therm__PC2)

/* Interrupt configuration Registers */
#define therm_INTCFG                 (* (reg32 *) therm__INTCFG)
#define therm_INTSTAT                (* (reg32 *) therm__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define therm_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(therm__SIO)
    #define therm_SIO_REG            (* (reg32 *) therm__SIO)
#endif /* (therm__SIO_CFG) */

/* USBIO registers */
#if !defined(therm__PC) && (CY_PSOC4_4200L)
    #define therm_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define therm_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define therm_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define therm_DRIVE_MODE_SHIFT       (0x00u)
#define therm_DRIVE_MODE_MASK        (0x07u << therm_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins therm_H */


/* [] END OF FILE */
