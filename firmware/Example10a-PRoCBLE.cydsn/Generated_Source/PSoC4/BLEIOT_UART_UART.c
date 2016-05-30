/***************************************************************************//**
* \file BLEIOT_UART_UART.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BLEIOT_UART_PVT.h"
#include "BLEIOT_UART_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (BLEIOT_UART_UART_WAKE_ENABLE_CONST && BLEIOT_UART_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when BLEIOT_UART_Sleep() function is called:
    * 0 – disable, other values – enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 BLEIOT_UART_skipStart = 1u;
    /** \} globals */
#endif /* (BLEIOT_UART_UART_WAKE_ENABLE_CONST && BLEIOT_UART_UART_RX_WAKEUP_IRQ) */

#if(BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const BLEIOT_UART_UART_INIT_STRUCT BLEIOT_UART_configUart =
    {
        BLEIOT_UART_UART_SUB_MODE,
        BLEIOT_UART_UART_DIRECTION,
        BLEIOT_UART_UART_DATA_BITS_NUM,
        BLEIOT_UART_UART_PARITY_TYPE,
        BLEIOT_UART_UART_STOP_BITS_NUM,
        BLEIOT_UART_UART_OVS_FACTOR,
        BLEIOT_UART_UART_IRDA_LOW_POWER,
        BLEIOT_UART_UART_MEDIAN_FILTER_ENABLE,
        BLEIOT_UART_UART_RETRY_ON_NACK,
        BLEIOT_UART_UART_IRDA_POLARITY,
        BLEIOT_UART_UART_DROP_ON_PARITY_ERR,
        BLEIOT_UART_UART_DROP_ON_FRAME_ERR,
        BLEIOT_UART_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        BLEIOT_UART_UART_MP_MODE_ENABLE,
        BLEIOT_UART_UART_MP_ACCEPT_ADDRESS,
        BLEIOT_UART_UART_MP_RX_ADDRESS,
        BLEIOT_UART_UART_MP_RX_ADDRESS_MASK,
        (uint32) BLEIOT_UART_SCB_IRQ_INTERNAL,
        BLEIOT_UART_UART_INTR_RX_MASK,
        BLEIOT_UART_UART_RX_TRIGGER_LEVEL,
        BLEIOT_UART_UART_INTR_TX_MASK,
        BLEIOT_UART_UART_TX_TRIGGER_LEVEL,
        (uint8) BLEIOT_UART_UART_BYTE_MODE_ENABLE,
        (uint8) BLEIOT_UART_UART_CTS_ENABLE,
        (uint8) BLEIOT_UART_UART_CTS_POLARITY,
        (uint8) BLEIOT_UART_UART_RTS_POLARITY,
        (uint8) BLEIOT_UART_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: BLEIOT_UART_UartInit
    ****************************************************************************//**
    *
    *  Configures the BLEIOT_UART for UART operation.
    *
    *  This function is intended specifically to be used when the BLEIOT_UART
    *  configuration is set to “Unconfigured BLEIOT_UART” in the customizer.
    *  After initializing the BLEIOT_UART in UART mode using this function,
    *  the component can be enabled using the BLEIOT_UART_Start() or
    * BLEIOT_UART_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration
    *  settings. This structure contains the same information that would otherwise
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of
    *   fields. These fields match the selections available in the customizer.
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void BLEIOT_UART_UartInit(const BLEIOT_UART_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (BLEIOT_UART_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (BLEIOT_UART_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1) */

            /* Configure pins */
            BLEIOT_UART_SetPins(BLEIOT_UART_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            BLEIOT_UART_scbMode       = (uint8) BLEIOT_UART_SCB_MODE_UART;
            BLEIOT_UART_scbEnableWake = (uint8) config->enableWake;
            BLEIOT_UART_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            BLEIOT_UART_rxBuffer      =         config->rxBuffer;
            BLEIOT_UART_rxDataBits    = (uint8) config->dataBits;
            BLEIOT_UART_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            BLEIOT_UART_txBuffer      =         config->txBuffer;
            BLEIOT_UART_txDataBits    = (uint8) config->dataBits;
            BLEIOT_UART_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(BLEIOT_UART_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                BLEIOT_UART_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (BLEIOT_UART_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (BLEIOT_UART_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                BLEIOT_UART_CTRL_REG  = BLEIOT_UART_GET_CTRL_OVS(config->oversample);
            }

            BLEIOT_UART_CTRL_REG     |= BLEIOT_UART_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             BLEIOT_UART_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             BLEIOT_UART_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            BLEIOT_UART_UART_CTRL_REG = BLEIOT_UART_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            BLEIOT_UART_UART_RX_CTRL_REG = BLEIOT_UART_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        BLEIOT_UART_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        BLEIOT_UART_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        BLEIOT_UART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        BLEIOT_UART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(BLEIOT_UART_UART_PARITY_NONE != config->parity)
            {
               BLEIOT_UART_UART_RX_CTRL_REG |= BLEIOT_UART_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    BLEIOT_UART_UART_RX_CTRL_PARITY_ENABLED;
            }

            BLEIOT_UART_RX_CTRL_REG      = BLEIOT_UART_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                BLEIOT_UART_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                BLEIOT_UART_GET_UART_RX_CTRL_ENABLED(config->direction);

            BLEIOT_UART_RX_FIFO_CTRL_REG = BLEIOT_UART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            BLEIOT_UART_RX_MATCH_REG     = BLEIOT_UART_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                BLEIOT_UART_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            BLEIOT_UART_UART_TX_CTRL_REG = BLEIOT_UART_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                BLEIOT_UART_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(BLEIOT_UART_UART_PARITY_NONE != config->parity)
            {
               BLEIOT_UART_UART_TX_CTRL_REG |= BLEIOT_UART_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    BLEIOT_UART_UART_TX_CTRL_PARITY_ENABLED;
            }

            BLEIOT_UART_TX_CTRL_REG      = BLEIOT_UART_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                BLEIOT_UART_GET_UART_TX_CTRL_ENABLED(config->direction);

            BLEIOT_UART_TX_FIFO_CTRL_REG = BLEIOT_UART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1)
            BLEIOT_UART_UART_FLOW_CTRL_REG = BLEIOT_UART_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            BLEIOT_UART_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            BLEIOT_UART_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            BLEIOT_UART_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (BLEIOT_UART_ISR_NUMBER);
            CyIntSetPriority(BLEIOT_UART_ISR_NUMBER, BLEIOT_UART_ISR_PRIORITY);
            (void) CyIntSetVector(BLEIOT_UART_ISR_NUMBER, &BLEIOT_UART_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(BLEIOT_UART_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (BLEIOT_UART_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(BLEIOT_UART_RX_WAKE_ISR_NUMBER, BLEIOT_UART_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(BLEIOT_UART_RX_WAKE_ISR_NUMBER, &BLEIOT_UART_UART_WAKEUP_ISR);
        #endif /* (BLEIOT_UART_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            BLEIOT_UART_INTR_I2C_EC_MASK_REG = BLEIOT_UART_NO_INTR_SOURCES;
            BLEIOT_UART_INTR_SPI_EC_MASK_REG = BLEIOT_UART_NO_INTR_SOURCES;
            BLEIOT_UART_INTR_SLAVE_MASK_REG  = BLEIOT_UART_NO_INTR_SOURCES;
            BLEIOT_UART_INTR_MASTER_MASK_REG = BLEIOT_UART_NO_INTR_SOURCES;
            BLEIOT_UART_INTR_RX_MASK_REG     = config->rxInterruptMask;
            BLEIOT_UART_INTR_TX_MASK_REG     = config->txInterruptMask;
        
            /* Configure TX interrupt sources to restore. */
            BLEIOT_UART_IntrTxMask = LO16(BLEIOT_UART_INTR_TX_MASK_REG);

            /* Clear RX buffer indexes */
            BLEIOT_UART_rxBufferHead     = 0u;
            BLEIOT_UART_rxBufferTail     = 0u;
            BLEIOT_UART_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            BLEIOT_UART_txBufferHead = 0u;
            BLEIOT_UART_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: BLEIOT_UART_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void BLEIOT_UART_UartInit(void)
    {
        /* Configure UART interface */
        BLEIOT_UART_CTRL_REG = BLEIOT_UART_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        BLEIOT_UART_UART_CTRL_REG = BLEIOT_UART_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        BLEIOT_UART_UART_RX_CTRL_REG = BLEIOT_UART_UART_DEFAULT_UART_RX_CTRL;
        BLEIOT_UART_RX_CTRL_REG      = BLEIOT_UART_UART_DEFAULT_RX_CTRL;
        BLEIOT_UART_RX_FIFO_CTRL_REG = BLEIOT_UART_UART_DEFAULT_RX_FIFO_CTRL;
        BLEIOT_UART_RX_MATCH_REG     = BLEIOT_UART_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        BLEIOT_UART_UART_TX_CTRL_REG = BLEIOT_UART_UART_DEFAULT_UART_TX_CTRL;
        BLEIOT_UART_TX_CTRL_REG      = BLEIOT_UART_UART_DEFAULT_TX_CTRL;
        BLEIOT_UART_TX_FIFO_CTRL_REG = BLEIOT_UART_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1)
        BLEIOT_UART_UART_FLOW_CTRL_REG = BLEIOT_UART_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(BLEIOT_UART_SCB_IRQ_INTERNAL)
        CyIntDisable    (BLEIOT_UART_ISR_NUMBER);
        CyIntSetPriority(BLEIOT_UART_ISR_NUMBER, BLEIOT_UART_ISR_PRIORITY);
        (void) CyIntSetVector(BLEIOT_UART_ISR_NUMBER, &BLEIOT_UART_SPI_UART_ISR);
    #endif /* (BLEIOT_UART_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(BLEIOT_UART_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (BLEIOT_UART_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(BLEIOT_UART_RX_WAKE_ISR_NUMBER, BLEIOT_UART_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(BLEIOT_UART_RX_WAKE_ISR_NUMBER, &BLEIOT_UART_UART_WAKEUP_ISR);
    #endif /* (BLEIOT_UART_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        BLEIOT_UART_INTR_I2C_EC_MASK_REG = BLEIOT_UART_UART_DEFAULT_INTR_I2C_EC_MASK;
        BLEIOT_UART_INTR_SPI_EC_MASK_REG = BLEIOT_UART_UART_DEFAULT_INTR_SPI_EC_MASK;
        BLEIOT_UART_INTR_SLAVE_MASK_REG  = BLEIOT_UART_UART_DEFAULT_INTR_SLAVE_MASK;
        BLEIOT_UART_INTR_MASTER_MASK_REG = BLEIOT_UART_UART_DEFAULT_INTR_MASTER_MASK;
        BLEIOT_UART_INTR_RX_MASK_REG     = BLEIOT_UART_UART_DEFAULT_INTR_RX_MASK;
        BLEIOT_UART_INTR_TX_MASK_REG     = BLEIOT_UART_UART_DEFAULT_INTR_TX_MASK;
    
        /* Configure TX interrupt sources to restore. */
        BLEIOT_UART_IntrTxMask = LO16(BLEIOT_UART_INTR_TX_MASK_REG);

    #if(BLEIOT_UART_INTERNAL_RX_SW_BUFFER_CONST)
        BLEIOT_UART_rxBufferHead     = 0u;
        BLEIOT_UART_rxBufferTail     = 0u;
        BLEIOT_UART_rxBufferOverflow = 0u;
    #endif /* (BLEIOT_UART_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(BLEIOT_UART_INTERNAL_TX_SW_BUFFER_CONST)
        BLEIOT_UART_txBufferHead = 0u;
        BLEIOT_UART_txBufferTail = 0u;
    #endif /* (BLEIOT_UART_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: BLEIOT_UART_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void BLEIOT_UART_UartPostEnable(void)
{
#if (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (BLEIOT_UART_TX_SCL_MISO_PIN)
        if (BLEIOT_UART_CHECK_TX_SCL_MISO_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            BLEIOT_UART_SET_HSIOM_SEL(BLEIOT_UART_TX_SCL_MISO_HSIOM_REG, BLEIOT_UART_TX_SCL_MISO_HSIOM_MASK,
                                           BLEIOT_UART_TX_SCL_MISO_HSIOM_POS, BLEIOT_UART_TX_SCL_MISO_HSIOM_SEL_UART);
        }
    #endif /* (BLEIOT_UART_TX_SCL_MISO_PIN_PIN) */

    #if !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1)
        #if (BLEIOT_UART_RTS_SS0_PIN)
            if (BLEIOT_UART_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                BLEIOT_UART_SET_HSIOM_SEL(BLEIOT_UART_RTS_SS0_HSIOM_REG, BLEIOT_UART_RTS_SS0_HSIOM_MASK,
                                               BLEIOT_UART_RTS_SS0_HSIOM_POS, BLEIOT_UART_RTS_SS0_HSIOM_SEL_UART);
            }
        #endif /* (BLEIOT_UART_RTS_SS0_PIN) */
    #endif /* !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1) */

#else
    #if (BLEIOT_UART_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        BLEIOT_UART_SET_HSIOM_SEL(BLEIOT_UART_TX_HSIOM_REG, BLEIOT_UART_TX_HSIOM_MASK,
                                       BLEIOT_UART_TX_HSIOM_POS, BLEIOT_UART_TX_HSIOM_SEL_UART);
    #endif /* (BLEIOT_UART_UART_TX_PIN) */

    #if (BLEIOT_UART_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        BLEIOT_UART_SET_HSIOM_SEL(BLEIOT_UART_RTS_HSIOM_REG, BLEIOT_UART_RTS_HSIOM_MASK,
                                       BLEIOT_UART_RTS_HSIOM_POS, BLEIOT_UART_RTS_HSIOM_SEL_UART);
    #endif /* (BLEIOT_UART_UART_RTS_PIN) */
#endif /* (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    BLEIOT_UART_SetTxInterruptMode(BLEIOT_UART_IntrTxMask);
}


/*******************************************************************************
* Function Name: BLEIOT_UART_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void BLEIOT_UART_UartStop(void)
{
#if(BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (BLEIOT_UART_TX_SCL_MISO_PIN)
        if (BLEIOT_UART_CHECK_TX_SCL_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            BLEIOT_UART_SET_HSIOM_SEL(BLEIOT_UART_TX_SCL_MISO_HSIOM_REG, BLEIOT_UART_TX_SCL_MISO_HSIOM_MASK,
                                           BLEIOT_UART_TX_SCL_MISO_HSIOM_POS, BLEIOT_UART_TX_SCL_MISO_HSIOM_SEL_GPIO);
        }
    #endif /* (BLEIOT_UART_TX_SCL_MISO_PIN_PIN) */

    #if !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1)
        #if (BLEIOT_UART_RTS_SS0_PIN)
            if (BLEIOT_UART_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                BLEIOT_UART_uart_rts_spi_ss0_Write(BLEIOT_UART_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                BLEIOT_UART_SET_HSIOM_SEL(BLEIOT_UART_RTS_SS0_HSIOM_REG, BLEIOT_UART_RTS_SS0_HSIOM_MASK,
                                               BLEIOT_UART_RTS_SS0_HSIOM_POS, BLEIOT_UART_RTS_SS0_HSIOM_SEL_GPIO);
            }
        #endif /* (BLEIOT_UART_RTS_SS0_PIN) */
    #endif /* !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1) */

#else
    #if (BLEIOT_UART_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        BLEIOT_UART_SET_HSIOM_SEL(BLEIOT_UART_TX_HSIOM_REG, BLEIOT_UART_TX_HSIOM_MASK,
                                       BLEIOT_UART_TX_HSIOM_POS, BLEIOT_UART_TX_HSIOM_SEL_GPIO);
    #endif /* (BLEIOT_UART_UART_TX_PIN) */

    #if (BLEIOT_UART_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        BLEIOT_UART_rts_Write(BLEIOT_UART_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        BLEIOT_UART_SET_HSIOM_SEL(BLEIOT_UART_RTS_HSIOM_REG, BLEIOT_UART_RTS_HSIOM_MASK,
                                       BLEIOT_UART_RTS_HSIOM_POS, BLEIOT_UART_RTS_HSIOM_SEL_GPIO);
    #endif /* (BLEIOT_UART_UART_RTS_PIN) */

#endif /* (BLEIOT_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (BLEIOT_UART_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    BLEIOT_UART_UART_RX_CTRL_REG &= (uint32) ~BLEIOT_UART_UART_RX_CTRL_SKIP_START;
#endif /* (BLEIOT_UART_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    BLEIOT_UART_IntrTxMask = LO16(BLEIOT_UART_GetTxInterruptMode() & BLEIOT_UART_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: BLEIOT_UART_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void BLEIOT_UART_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = BLEIOT_UART_RX_MATCH_REG;

    matchReg &= ((uint32) ~BLEIOT_UART_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & BLEIOT_UART_RX_MATCH_ADDR_MASK)); /* Set address  */

    BLEIOT_UART_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: BLEIOT_UART_UartSetRxAddressMask
****************************************************************************//**
*
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
*  \param addressMask: Address mask.
*   - Bit value 0 – excludes bit from address comparison.
*   - Bit value 1 – the bit needs to match with the corresponding bit
*     of the address.
*
*******************************************************************************/
void BLEIOT_UART_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = BLEIOT_UART_RX_MATCH_REG;

    matchReg &= ((uint32) ~BLEIOT_UART_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << BLEIOT_UART_RX_MATCH_MASK_POS));

    BLEIOT_UART_RX_MATCH_REG = matchReg;
}


#if(BLEIOT_UART_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: BLEIOT_UART_UartGetChar
    ****************************************************************************//**
    *
    *  Retrieves next data element from receive buffer.
    *  This function is designed for ASCII characters and returns a char where
    *  1 to 255 are valid characters and 0 indicates an error occurred or no data
    *  is present.
    *  - RX software buffer is disabled: Returns data element retrieved from RX
    *    FIFO.
    *  - RX software buffer is enabled: Returns data element from the software
    *    receive buffer.
    *
    *  \return
    *   Next data element from the receive buffer. ASCII character values from
    *   1 to 255 are valid. A returned zero signifies an error condition or no
    *   data available.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check BLEIOT_UART_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 BLEIOT_UART_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != BLEIOT_UART_SpiUartGetRxBufferSize())
        {
            rxData = BLEIOT_UART_SpiUartReadRxData();
        }

        if (BLEIOT_UART_CHECK_INTR_RX(BLEIOT_UART_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            BLEIOT_UART_ClearRxInterruptSource(BLEIOT_UART_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: BLEIOT_UART_UartGetByte
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    *  \return
    *   Bits 7-0 contain the next data element from the receive buffer and
    *   other bits contain the error condition.
    *   - BLEIOT_UART_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - BLEIOT_UART_UART_RX_UNDERFLOW	Attempt to read from an empty
    *     receiver FIFO.
    *   - BLEIOT_UART_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - BLEIOT_UART_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check BLEIOT_UART_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 BLEIOT_UART_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (BLEIOT_UART_CHECK_RX_SW_BUFFER)
        {
            BLEIOT_UART_DisableInt();
        }
        #endif

        if (0u != BLEIOT_UART_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (BLEIOT_UART_CHECK_RX_SW_BUFFER)
            {
                BLEIOT_UART_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = BLEIOT_UART_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = BLEIOT_UART_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            #if (BLEIOT_UART_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                BLEIOT_UART_ClearRxInterruptSource(BLEIOT_UART_INTR_RX_NOT_EMPTY);

                BLEIOT_UART_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (BLEIOT_UART_GetRxInterruptSource() & BLEIOT_UART_INTR_RX_ERR);
        BLEIOT_UART_ClearRxInterruptSource(BLEIOT_UART_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: BLEIOT_UART_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - BLEIOT_UART_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - BLEIOT_UART_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void BLEIOT_UART_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                BLEIOT_UART_UART_FLOW_CTRL_REG |= (uint32)  BLEIOT_UART_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                BLEIOT_UART_UART_FLOW_CTRL_REG &= (uint32) ~BLEIOT_UART_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: BLEIOT_UART_UartSetRtsFifoLevel
        ****************************************************************************//**
        *
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param level: Level in the RX FIFO for RTS signal activation.
        *   The range of valid level values is between 0 and RX FIFO depth - 1.
        *   Setting level value to 0 disables RTS signal activation.
        *
        *******************************************************************************/
        void BLEIOT_UART_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = BLEIOT_UART_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~BLEIOT_UART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (BLEIOT_UART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            BLEIOT_UART_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1) */

#endif /* (BLEIOT_UART_UART_RX_DIRECTION) */


#if(BLEIOT_UART_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: BLEIOT_UART_UartPutString
    ****************************************************************************//**
    *
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is a space available to put
    *  requested data in transmit buffer.
    *
    *  \param string: pointer to the null terminated string array to be placed in the
    *   transmit buffer.
    *
    *******************************************************************************/
    void BLEIOT_UART_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            BLEIOT_UART_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: BLEIOT_UART_UartPutCRLF
    ****************************************************************************//**
    *
    *  Places byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) in the transmit buffer.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *
    *******************************************************************************/
    void BLEIOT_UART_UartPutCRLF(uint32 txDataByte)
    {
        BLEIOT_UART_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        BLEIOT_UART_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        BLEIOT_UART_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: BLEIOT_UARTSCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void BLEIOT_UART_UartEnableCts(void)
        {
            BLEIOT_UART_UART_FLOW_CTRL_REG |= (uint32)  BLEIOT_UART_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: BLEIOT_UART_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void BLEIOT_UART_UartDisableCts(void)
        {
            BLEIOT_UART_UART_FLOW_CTRL_REG &= (uint32) ~BLEIOT_UART_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: BLEIOT_UART_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of CTS output signal.
        *   - BLEIOT_UART_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - BLEIOT_UART_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void BLEIOT_UART_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                BLEIOT_UART_UART_FLOW_CTRL_REG |= (uint32)  BLEIOT_UART_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                BLEIOT_UART_UART_FLOW_CTRL_REG &= (uint32) ~BLEIOT_UART_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(BLEIOT_UART_CY_SCBIP_V0 || BLEIOT_UART_CY_SCBIP_V1) */

#endif /* (BLEIOT_UART_UART_TX_DIRECTION) */


#if (BLEIOT_UART_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: BLEIOT_UART_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be 
    *  cleared by this API.
    *
    *******************************************************************************/
    void BLEIOT_UART_UartSaveConfig(void)
    {
    #if (BLEIOT_UART_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != BLEIOT_UART_skipStart)
        {
            BLEIOT_UART_UART_RX_CTRL_REG |= (uint32)  BLEIOT_UART_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            BLEIOT_UART_UART_RX_CTRL_REG &= (uint32) ~BLEIOT_UART_UART_RX_CTRL_SKIP_START;
        }
        
        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        BLEIOT_UART_CLEAR_UART_RX_WAKE_INTR;
        BLEIOT_UART_RxWakeClearPendingInt();
        BLEIOT_UART_RxWakeEnableInt();
    #endif /* (BLEIOT_UART_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: BLEIOT_UART_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void BLEIOT_UART_UartRestoreConfig(void)
    {
    #if (BLEIOT_UART_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        BLEIOT_UART_RxWakeDisableInt();
    #endif /* (BLEIOT_UART_UART_RX_WAKEUP_IRQ) */
    }


    #if (BLEIOT_UART_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: BLEIOT_UART_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(BLEIOT_UART_UART_WAKEUP_ISR)
        {
        #ifdef BLEIOT_UART_UART_WAKEUP_ISR_ENTRY_CALLBACK
            BLEIOT_UART_UART_WAKEUP_ISR_EntryCallback();
        #endif /* BLEIOT_UART_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            BLEIOT_UART_CLEAR_UART_RX_WAKE_INTR;

        #ifdef BLEIOT_UART_UART_WAKEUP_ISR_EXIT_CALLBACK
            BLEIOT_UART_UART_WAKEUP_ISR_ExitCallback();
        #endif /* BLEIOT_UART_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (BLEIOT_UART_UART_RX_WAKEUP_IRQ) */
#endif /* (BLEIOT_UART_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
