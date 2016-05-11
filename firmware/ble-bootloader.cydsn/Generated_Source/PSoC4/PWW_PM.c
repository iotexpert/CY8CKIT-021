/*******************************************************************************
* File Name: PWW_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWW.h"

static PWW_BACKUP_STRUCT PWW_backup;


/*******************************************************************************
* Function Name: PWW_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PWW_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWW_Sleep(void)
{
    if(0u != (PWW_BLOCK_CONTROL_REG & PWW_MASK))
    {
        PWW_backup.enableState = 1u;
    }
    else
    {
        PWW_backup.enableState = 0u;
    }

    PWW_Stop();
    PWW_SaveConfig();
}


/*******************************************************************************
* Function Name: PWW_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWW_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PWW_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWW_Wakeup(void)
{
    PWW_RestoreConfig();

    if(0u != PWW_backup.enableState)
    {
        PWW_Enable();
    }
}


/* [] END OF FILE */
