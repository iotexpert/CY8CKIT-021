#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include "cydevice_trm.h"

/* led0 */
#define led0__0__DR CYREG_GPIO_PRT3_DR
#define led0__0__DR_CLR CYREG_GPIO_PRT3_DR_CLR
#define led0__0__DR_INV CYREG_GPIO_PRT3_DR_INV
#define led0__0__DR_SET CYREG_GPIO_PRT3_DR_SET
#define led0__0__HSIOM CYREG_HSIOM_PORT_SEL3
#define led0__0__HSIOM_MASK 0x000000F0u
#define led0__0__HSIOM_SHIFT 4u
#define led0__0__INTCFG CYREG_GPIO_PRT3_INTR_CFG
#define led0__0__INTR CYREG_GPIO_PRT3_INTR
#define led0__0__INTR_CFG CYREG_GPIO_PRT3_INTR_CFG
#define led0__0__INTSTAT CYREG_GPIO_PRT3_INTR
#define led0__0__MASK 0x02u
#define led0__0__PA__CFG0 CYREG_UDB_PA3_CFG0
#define led0__0__PA__CFG1 CYREG_UDB_PA3_CFG1
#define led0__0__PA__CFG10 CYREG_UDB_PA3_CFG10
#define led0__0__PA__CFG11 CYREG_UDB_PA3_CFG11
#define led0__0__PA__CFG12 CYREG_UDB_PA3_CFG12
#define led0__0__PA__CFG13 CYREG_UDB_PA3_CFG13
#define led0__0__PA__CFG14 CYREG_UDB_PA3_CFG14
#define led0__0__PA__CFG2 CYREG_UDB_PA3_CFG2
#define led0__0__PA__CFG3 CYREG_UDB_PA3_CFG3
#define led0__0__PA__CFG4 CYREG_UDB_PA3_CFG4
#define led0__0__PA__CFG5 CYREG_UDB_PA3_CFG5
#define led0__0__PA__CFG6 CYREG_UDB_PA3_CFG6
#define led0__0__PA__CFG7 CYREG_UDB_PA3_CFG7
#define led0__0__PA__CFG8 CYREG_UDB_PA3_CFG8
#define led0__0__PA__CFG9 CYREG_UDB_PA3_CFG9
#define led0__0__PC CYREG_GPIO_PRT3_PC
#define led0__0__PC2 CYREG_GPIO_PRT3_PC2
#define led0__0__PORT 3u
#define led0__0__PS CYREG_GPIO_PRT3_PS
#define led0__0__SHIFT 1u
#define led0__DR CYREG_GPIO_PRT3_DR
#define led0__DR_CLR CYREG_GPIO_PRT3_DR_CLR
#define led0__DR_INV CYREG_GPIO_PRT3_DR_INV
#define led0__DR_SET CYREG_GPIO_PRT3_DR_SET
#define led0__INTCFG CYREG_GPIO_PRT3_INTR_CFG
#define led0__INTR CYREG_GPIO_PRT3_INTR
#define led0__INTR_CFG CYREG_GPIO_PRT3_INTR_CFG
#define led0__INTSTAT CYREG_GPIO_PRT3_INTR
#define led0__MASK 0x02u
#define led0__PA__CFG0 CYREG_UDB_PA3_CFG0
#define led0__PA__CFG1 CYREG_UDB_PA3_CFG1
#define led0__PA__CFG10 CYREG_UDB_PA3_CFG10
#define led0__PA__CFG11 CYREG_UDB_PA3_CFG11
#define led0__PA__CFG12 CYREG_UDB_PA3_CFG12
#define led0__PA__CFG13 CYREG_UDB_PA3_CFG13
#define led0__PA__CFG14 CYREG_UDB_PA3_CFG14
#define led0__PA__CFG2 CYREG_UDB_PA3_CFG2
#define led0__PA__CFG3 CYREG_UDB_PA3_CFG3
#define led0__PA__CFG4 CYREG_UDB_PA3_CFG4
#define led0__PA__CFG5 CYREG_UDB_PA3_CFG5
#define led0__PA__CFG6 CYREG_UDB_PA3_CFG6
#define led0__PA__CFG7 CYREG_UDB_PA3_CFG7
#define led0__PA__CFG8 CYREG_UDB_PA3_CFG8
#define led0__PA__CFG9 CYREG_UDB_PA3_CFG9
#define led0__PC CYREG_GPIO_PRT3_PC
#define led0__PC2 CYREG_GPIO_PRT3_PC2
#define led0__PORT 3u
#define led0__PS CYREG_GPIO_PRT3_PS
#define led0__SHIFT 1u

/* BLEIOT_UART_rx */
#define BLEIOT_UART_rx__0__DR CYREG_GPIO_PRT6_DR
#define BLEIOT_UART_rx__0__DR_CLR CYREG_GPIO_PRT6_DR_CLR
#define BLEIOT_UART_rx__0__DR_INV CYREG_GPIO_PRT6_DR_INV
#define BLEIOT_UART_rx__0__DR_SET CYREG_GPIO_PRT6_DR_SET
#define BLEIOT_UART_rx__0__HSIOM CYREG_HSIOM_PORT_SEL6
#define BLEIOT_UART_rx__0__HSIOM_GPIO 0u
#define BLEIOT_UART_rx__0__HSIOM_I2C 14u
#define BLEIOT_UART_rx__0__HSIOM_I2C_SCL 14u
#define BLEIOT_UART_rx__0__HSIOM_MASK 0x0000000Fu
#define BLEIOT_UART_rx__0__HSIOM_SHIFT 0u
#define BLEIOT_UART_rx__0__HSIOM_SPI 15u
#define BLEIOT_UART_rx__0__HSIOM_SPI_MOSI 15u
#define BLEIOT_UART_rx__0__HSIOM_UART 9u
#define BLEIOT_UART_rx__0__HSIOM_UART_RX 9u
#define BLEIOT_UART_rx__0__INTCFG CYREG_GPIO_PRT6_INTR_CFG
#define BLEIOT_UART_rx__0__INTR CYREG_GPIO_PRT6_INTR
#define BLEIOT_UART_rx__0__INTR_CFG CYREG_GPIO_PRT6_INTR_CFG
#define BLEIOT_UART_rx__0__INTSTAT CYREG_GPIO_PRT6_INTR
#define BLEIOT_UART_rx__0__MASK 0x01u
#define BLEIOT_UART_rx__0__PC CYREG_GPIO_PRT6_PC
#define BLEIOT_UART_rx__0__PC2 CYREG_GPIO_PRT6_PC2
#define BLEIOT_UART_rx__0__PORT 6u
#define BLEIOT_UART_rx__0__PS CYREG_GPIO_PRT6_PS
#define BLEIOT_UART_rx__0__SHIFT 0u
#define BLEIOT_UART_rx__DR CYREG_GPIO_PRT6_DR
#define BLEIOT_UART_rx__DR_CLR CYREG_GPIO_PRT6_DR_CLR
#define BLEIOT_UART_rx__DR_INV CYREG_GPIO_PRT6_DR_INV
#define BLEIOT_UART_rx__DR_SET CYREG_GPIO_PRT6_DR_SET
#define BLEIOT_UART_rx__INTCFG CYREG_GPIO_PRT6_INTR_CFG
#define BLEIOT_UART_rx__INTR CYREG_GPIO_PRT6_INTR
#define BLEIOT_UART_rx__INTR_CFG CYREG_GPIO_PRT6_INTR_CFG
#define BLEIOT_UART_rx__INTSTAT CYREG_GPIO_PRT6_INTR
#define BLEIOT_UART_rx__MASK 0x01u
#define BLEIOT_UART_rx__PC CYREG_GPIO_PRT6_PC
#define BLEIOT_UART_rx__PC2 CYREG_GPIO_PRT6_PC2
#define BLEIOT_UART_rx__PORT 6u
#define BLEIOT_UART_rx__PS CYREG_GPIO_PRT6_PS
#define BLEIOT_UART_rx__SHIFT 0u

/* BLEIOT_UART_SCB */
#define BLEIOT_UART_SCB__CTRL CYREG_SCB3_CTRL
#define BLEIOT_UART_SCB__EZ_DATA0 CYREG_SCB3_EZ_DATA0
#define BLEIOT_UART_SCB__EZ_DATA1 CYREG_SCB3_EZ_DATA1
#define BLEIOT_UART_SCB__EZ_DATA10 CYREG_SCB3_EZ_DATA10
#define BLEIOT_UART_SCB__EZ_DATA11 CYREG_SCB3_EZ_DATA11
#define BLEIOT_UART_SCB__EZ_DATA12 CYREG_SCB3_EZ_DATA12
#define BLEIOT_UART_SCB__EZ_DATA13 CYREG_SCB3_EZ_DATA13
#define BLEIOT_UART_SCB__EZ_DATA14 CYREG_SCB3_EZ_DATA14
#define BLEIOT_UART_SCB__EZ_DATA15 CYREG_SCB3_EZ_DATA15
#define BLEIOT_UART_SCB__EZ_DATA16 CYREG_SCB3_EZ_DATA16
#define BLEIOT_UART_SCB__EZ_DATA17 CYREG_SCB3_EZ_DATA17
#define BLEIOT_UART_SCB__EZ_DATA18 CYREG_SCB3_EZ_DATA18
#define BLEIOT_UART_SCB__EZ_DATA19 CYREG_SCB3_EZ_DATA19
#define BLEIOT_UART_SCB__EZ_DATA2 CYREG_SCB3_EZ_DATA2
#define BLEIOT_UART_SCB__EZ_DATA20 CYREG_SCB3_EZ_DATA20
#define BLEIOT_UART_SCB__EZ_DATA21 CYREG_SCB3_EZ_DATA21
#define BLEIOT_UART_SCB__EZ_DATA22 CYREG_SCB3_EZ_DATA22
#define BLEIOT_UART_SCB__EZ_DATA23 CYREG_SCB3_EZ_DATA23
#define BLEIOT_UART_SCB__EZ_DATA24 CYREG_SCB3_EZ_DATA24
#define BLEIOT_UART_SCB__EZ_DATA25 CYREG_SCB3_EZ_DATA25
#define BLEIOT_UART_SCB__EZ_DATA26 CYREG_SCB3_EZ_DATA26
#define BLEIOT_UART_SCB__EZ_DATA27 CYREG_SCB3_EZ_DATA27
#define BLEIOT_UART_SCB__EZ_DATA28 CYREG_SCB3_EZ_DATA28
#define BLEIOT_UART_SCB__EZ_DATA29 CYREG_SCB3_EZ_DATA29
#define BLEIOT_UART_SCB__EZ_DATA3 CYREG_SCB3_EZ_DATA3
#define BLEIOT_UART_SCB__EZ_DATA30 CYREG_SCB3_EZ_DATA30
#define BLEIOT_UART_SCB__EZ_DATA31 CYREG_SCB3_EZ_DATA31
#define BLEIOT_UART_SCB__EZ_DATA4 CYREG_SCB3_EZ_DATA4
#define BLEIOT_UART_SCB__EZ_DATA5 CYREG_SCB3_EZ_DATA5
#define BLEIOT_UART_SCB__EZ_DATA6 CYREG_SCB3_EZ_DATA6
#define BLEIOT_UART_SCB__EZ_DATA7 CYREG_SCB3_EZ_DATA7
#define BLEIOT_UART_SCB__EZ_DATA8 CYREG_SCB3_EZ_DATA8
#define BLEIOT_UART_SCB__EZ_DATA9 CYREG_SCB3_EZ_DATA9
#define BLEIOT_UART_SCB__I2C_CFG CYREG_SCB3_I2C_CFG
#define BLEIOT_UART_SCB__I2C_CTRL CYREG_SCB3_I2C_CTRL
#define BLEIOT_UART_SCB__I2C_M_CMD CYREG_SCB3_I2C_M_CMD
#define BLEIOT_UART_SCB__I2C_S_CMD CYREG_SCB3_I2C_S_CMD
#define BLEIOT_UART_SCB__I2C_STATUS CYREG_SCB3_I2C_STATUS
#define BLEIOT_UART_SCB__INTR_CAUSE CYREG_SCB3_INTR_CAUSE
#define BLEIOT_UART_SCB__INTR_I2C_EC CYREG_SCB3_INTR_I2C_EC
#define BLEIOT_UART_SCB__INTR_I2C_EC_MASK CYREG_SCB3_INTR_I2C_EC_MASK
#define BLEIOT_UART_SCB__INTR_I2C_EC_MASKED CYREG_SCB3_INTR_I2C_EC_MASKED
#define BLEIOT_UART_SCB__INTR_M CYREG_SCB3_INTR_M
#define BLEIOT_UART_SCB__INTR_M_MASK CYREG_SCB3_INTR_M_MASK
#define BLEIOT_UART_SCB__INTR_M_MASKED CYREG_SCB3_INTR_M_MASKED
#define BLEIOT_UART_SCB__INTR_M_SET CYREG_SCB3_INTR_M_SET
#define BLEIOT_UART_SCB__INTR_RX CYREG_SCB3_INTR_RX
#define BLEIOT_UART_SCB__INTR_RX_MASK CYREG_SCB3_INTR_RX_MASK
#define BLEIOT_UART_SCB__INTR_RX_MASKED CYREG_SCB3_INTR_RX_MASKED
#define BLEIOT_UART_SCB__INTR_RX_SET CYREG_SCB3_INTR_RX_SET
#define BLEIOT_UART_SCB__INTR_S CYREG_SCB3_INTR_S
#define BLEIOT_UART_SCB__INTR_S_MASK CYREG_SCB3_INTR_S_MASK
#define BLEIOT_UART_SCB__INTR_S_MASKED CYREG_SCB3_INTR_S_MASKED
#define BLEIOT_UART_SCB__INTR_S_SET CYREG_SCB3_INTR_S_SET
#define BLEIOT_UART_SCB__INTR_SPI_EC CYREG_SCB3_INTR_SPI_EC
#define BLEIOT_UART_SCB__INTR_SPI_EC_MASK CYREG_SCB3_INTR_SPI_EC_MASK
#define BLEIOT_UART_SCB__INTR_SPI_EC_MASKED CYREG_SCB3_INTR_SPI_EC_MASKED
#define BLEIOT_UART_SCB__INTR_TX CYREG_SCB3_INTR_TX
#define BLEIOT_UART_SCB__INTR_TX_MASK CYREG_SCB3_INTR_TX_MASK
#define BLEIOT_UART_SCB__INTR_TX_MASKED CYREG_SCB3_INTR_TX_MASKED
#define BLEIOT_UART_SCB__INTR_TX_SET CYREG_SCB3_INTR_TX_SET
#define BLEIOT_UART_SCB__RX_CTRL CYREG_SCB3_RX_CTRL
#define BLEIOT_UART_SCB__RX_FIFO_CTRL CYREG_SCB3_RX_FIFO_CTRL
#define BLEIOT_UART_SCB__RX_FIFO_RD CYREG_SCB3_RX_FIFO_RD
#define BLEIOT_UART_SCB__RX_FIFO_RD_SILENT CYREG_SCB3_RX_FIFO_RD_SILENT
#define BLEIOT_UART_SCB__RX_FIFO_STATUS CYREG_SCB3_RX_FIFO_STATUS
#define BLEIOT_UART_SCB__RX_MATCH CYREG_SCB3_RX_MATCH
#define BLEIOT_UART_SCB__SPI_CTRL CYREG_SCB3_SPI_CTRL
#define BLEIOT_UART_SCB__SPI_STATUS CYREG_SCB3_SPI_STATUS
#define BLEIOT_UART_SCB__SS0_POSISTION 0u
#define BLEIOT_UART_SCB__SS1_POSISTION 1u
#define BLEIOT_UART_SCB__SS2_POSISTION 2u
#define BLEIOT_UART_SCB__SS3_POSISTION 3u
#define BLEIOT_UART_SCB__STATUS CYREG_SCB3_STATUS
#define BLEIOT_UART_SCB__TX_CTRL CYREG_SCB3_TX_CTRL
#define BLEIOT_UART_SCB__TX_FIFO_CTRL CYREG_SCB3_TX_FIFO_CTRL
#define BLEIOT_UART_SCB__TX_FIFO_STATUS CYREG_SCB3_TX_FIFO_STATUS
#define BLEIOT_UART_SCB__TX_FIFO_WR CYREG_SCB3_TX_FIFO_WR
#define BLEIOT_UART_SCB__UART_CTRL CYREG_SCB3_UART_CTRL
#define BLEIOT_UART_SCB__UART_FLOW_CTRL CYREG_SCB3_UART_FLOW_CTRL
#define BLEIOT_UART_SCB__UART_RX_CTRL CYREG_SCB3_UART_RX_CTRL
#define BLEIOT_UART_SCB__UART_RX_STATUS CYREG_SCB3_UART_RX_STATUS
#define BLEIOT_UART_SCB__UART_TX_CTRL CYREG_SCB3_UART_TX_CTRL

/* BLEIOT_UART_SCB_IRQ */
#define BLEIOT_UART_SCB_IRQ__INTC_CLR_EN_REG CYREG_CM0_ICER
#define BLEIOT_UART_SCB_IRQ__INTC_CLR_PD_REG CYREG_CM0_ICPR
#define BLEIOT_UART_SCB_IRQ__INTC_MASK 0x800u
#define BLEIOT_UART_SCB_IRQ__INTC_NUMBER 11u
#define BLEIOT_UART_SCB_IRQ__INTC_PRIOR_MASK 0xC0000000u
#define BLEIOT_UART_SCB_IRQ__INTC_PRIOR_NUM 3u
#define BLEIOT_UART_SCB_IRQ__INTC_PRIOR_REG CYREG_CM0_IPR2
#define BLEIOT_UART_SCB_IRQ__INTC_SET_EN_REG CYREG_CM0_ISER
#define BLEIOT_UART_SCB_IRQ__INTC_SET_PD_REG CYREG_CM0_ISPR

/* BLEIOT_UART_SCBCLK */
#define BLEIOT_UART_SCBCLK__CTRL_REGISTER CYREG_PERI_PCLK_CTL5
#define BLEIOT_UART_SCBCLK__DIV_ID 0x00000042u
#define BLEIOT_UART_SCBCLK__DIV_REGISTER CYREG_PERI_DIV_16_CTL2
#define BLEIOT_UART_SCBCLK__PA_DIV_ID 0x000000FFu

/* BLEIOT_UART_tx */
#define BLEIOT_UART_tx__0__DR CYREG_GPIO_PRT6_DR
#define BLEIOT_UART_tx__0__DR_CLR CYREG_GPIO_PRT6_DR_CLR
#define BLEIOT_UART_tx__0__DR_INV CYREG_GPIO_PRT6_DR_INV
#define BLEIOT_UART_tx__0__DR_SET CYREG_GPIO_PRT6_DR_SET
#define BLEIOT_UART_tx__0__HSIOM CYREG_HSIOM_PORT_SEL6
#define BLEIOT_UART_tx__0__HSIOM_GPIO 0u
#define BLEIOT_UART_tx__0__HSIOM_I2C 14u
#define BLEIOT_UART_tx__0__HSIOM_I2C_SDA 14u
#define BLEIOT_UART_tx__0__HSIOM_MASK 0x000000F0u
#define BLEIOT_UART_tx__0__HSIOM_SHIFT 4u
#define BLEIOT_UART_tx__0__HSIOM_SPI 15u
#define BLEIOT_UART_tx__0__HSIOM_SPI_MISO 15u
#define BLEIOT_UART_tx__0__HSIOM_UART 9u
#define BLEIOT_UART_tx__0__HSIOM_UART_TX 9u
#define BLEIOT_UART_tx__0__INTCFG CYREG_GPIO_PRT6_INTR_CFG
#define BLEIOT_UART_tx__0__INTR CYREG_GPIO_PRT6_INTR
#define BLEIOT_UART_tx__0__INTR_CFG CYREG_GPIO_PRT6_INTR_CFG
#define BLEIOT_UART_tx__0__INTSTAT CYREG_GPIO_PRT6_INTR
#define BLEIOT_UART_tx__0__MASK 0x02u
#define BLEIOT_UART_tx__0__PC CYREG_GPIO_PRT6_PC
#define BLEIOT_UART_tx__0__PC2 CYREG_GPIO_PRT6_PC2
#define BLEIOT_UART_tx__0__PORT 6u
#define BLEIOT_UART_tx__0__PS CYREG_GPIO_PRT6_PS
#define BLEIOT_UART_tx__0__SHIFT 1u
#define BLEIOT_UART_tx__DR CYREG_GPIO_PRT6_DR
#define BLEIOT_UART_tx__DR_CLR CYREG_GPIO_PRT6_DR_CLR
#define BLEIOT_UART_tx__DR_INV CYREG_GPIO_PRT6_DR_INV
#define BLEIOT_UART_tx__DR_SET CYREG_GPIO_PRT6_DR_SET
#define BLEIOT_UART_tx__INTCFG CYREG_GPIO_PRT6_INTR_CFG
#define BLEIOT_UART_tx__INTR CYREG_GPIO_PRT6_INTR
#define BLEIOT_UART_tx__INTR_CFG CYREG_GPIO_PRT6_INTR_CFG
#define BLEIOT_UART_tx__INTSTAT CYREG_GPIO_PRT6_INTR
#define BLEIOT_UART_tx__MASK 0x02u
#define BLEIOT_UART_tx__PC CYREG_GPIO_PRT6_PC
#define BLEIOT_UART_tx__PC2 CYREG_GPIO_PRT6_PC2
#define BLEIOT_UART_tx__PORT 6u
#define BLEIOT_UART_tx__PS CYREG_GPIO_PRT6_PS
#define BLEIOT_UART_tx__SHIFT 1u

/* CapSense_Cmod */
#define CapSense_Cmod__0__DR CYREG_GPIO_PRT4_DR
#define CapSense_Cmod__0__DR_CLR CYREG_GPIO_PRT4_DR_CLR
#define CapSense_Cmod__0__DR_INV CYREG_GPIO_PRT4_DR_INV
#define CapSense_Cmod__0__DR_SET CYREG_GPIO_PRT4_DR_SET
#define CapSense_Cmod__0__HSIOM CYREG_HSIOM_PORT_SEL4
#define CapSense_Cmod__0__HSIOM_MASK 0x00000F00u
#define CapSense_Cmod__0__HSIOM_SHIFT 8u
#define CapSense_Cmod__0__INTCFG CYREG_GPIO_PRT4_INTR_CFG
#define CapSense_Cmod__0__INTR CYREG_GPIO_PRT4_INTR
#define CapSense_Cmod__0__INTR_CFG CYREG_GPIO_PRT4_INTR_CFG
#define CapSense_Cmod__0__INTSTAT CYREG_GPIO_PRT4_INTR
#define CapSense_Cmod__0__MASK 0x04u
#define CapSense_Cmod__0__PC CYREG_GPIO_PRT4_PC
#define CapSense_Cmod__0__PC2 CYREG_GPIO_PRT4_PC2
#define CapSense_Cmod__0__PORT 4u
#define CapSense_Cmod__0__PS CYREG_GPIO_PRT4_PS
#define CapSense_Cmod__0__SHIFT 2u
#define CapSense_Cmod__Cmod__DR CYREG_GPIO_PRT4_DR
#define CapSense_Cmod__Cmod__DR_CLR CYREG_GPIO_PRT4_DR_CLR
#define CapSense_Cmod__Cmod__DR_INV CYREG_GPIO_PRT4_DR_INV
#define CapSense_Cmod__Cmod__DR_SET CYREG_GPIO_PRT4_DR_SET
#define CapSense_Cmod__Cmod__INTCFG CYREG_GPIO_PRT4_INTR_CFG
#define CapSense_Cmod__Cmod__INTR CYREG_GPIO_PRT4_INTR
#define CapSense_Cmod__Cmod__INTR_CFG CYREG_GPIO_PRT4_INTR_CFG
#define CapSense_Cmod__Cmod__INTSTAT CYREG_GPIO_PRT4_INTR
#define CapSense_Cmod__Cmod__MASK 0x04u
#define CapSense_Cmod__Cmod__PC CYREG_GPIO_PRT4_PC
#define CapSense_Cmod__Cmod__PC2 CYREG_GPIO_PRT4_PC2
#define CapSense_Cmod__Cmod__PORT 4u
#define CapSense_Cmod__Cmod__PS CYREG_GPIO_PRT4_PS
#define CapSense_Cmod__Cmod__SHIFT 2u
#define CapSense_Cmod__DR CYREG_GPIO_PRT4_DR
#define CapSense_Cmod__DR_CLR CYREG_GPIO_PRT4_DR_CLR
#define CapSense_Cmod__DR_INV CYREG_GPIO_PRT4_DR_INV
#define CapSense_Cmod__DR_SET CYREG_GPIO_PRT4_DR_SET
#define CapSense_Cmod__INTCFG CYREG_GPIO_PRT4_INTR_CFG
#define CapSense_Cmod__INTR CYREG_GPIO_PRT4_INTR
#define CapSense_Cmod__INTR_CFG CYREG_GPIO_PRT4_INTR_CFG
#define CapSense_Cmod__INTSTAT CYREG_GPIO_PRT4_INTR
#define CapSense_Cmod__MASK 0x04u
#define CapSense_Cmod__PC CYREG_GPIO_PRT4_PC
#define CapSense_Cmod__PC2 CYREG_GPIO_PRT4_PC2
#define CapSense_Cmod__PORT 4u
#define CapSense_Cmod__PS CYREG_GPIO_PRT4_PS
#define CapSense_Cmod__SHIFT 2u

/* CapSense_CSD_FFB */
#define CapSense_CSD_FFB__CSD_CONFIG CYREG_CSD0_CONFIG
#define CapSense_CSD_FFB__CSD_COUNTER CYREG_CSD0_COUNTER
#define CapSense_CSD_FFB__CSD_ID CYREG_CSD0_ID
#define CapSense_CSD_FFB__CSD_INTR CYREG_CSD0_INTR
#define CapSense_CSD_FFB__CSD_INTR_SET CYREG_CSD0_INTR_SET
#define CapSense_CSD_FFB__CSD_NUMBER 0u
#define CapSense_CSD_FFB__CSD_PWM CYREG_CSD0_PWM
#define CapSense_CSD_FFB__CSD_STATUS CYREG_CSD0_STATUS

/* CapSense_IDAC1_cy_psoc4_idac */
#define CapSense_IDAC1_cy_psoc4_idac__CONTROL CYREG_CSD0_CONFIG
#define CapSense_IDAC1_cy_psoc4_idac__CSD_IDAC CYREG_CSD0_IDAC
#define CapSense_IDAC1_cy_psoc4_idac__CSD_IDAC_SHIFT 0u
#define CapSense_IDAC1_cy_psoc4_idac__CSD_TRIM1 CYREG_CSD0_TRIM1
#define CapSense_IDAC1_cy_psoc4_idac__CSD_TRIM1_SHIFT 0u
#define CapSense_IDAC1_cy_psoc4_idac__CSD_TRIM2 CYREG_CSD0_TRIM2
#define CapSense_IDAC1_cy_psoc4_idac__CSD_TRIM2_SHIFT 0u
#define CapSense_IDAC1_cy_psoc4_idac__IDAC_NUMBER 1u
#define CapSense_IDAC1_cy_psoc4_idac__POLARITY CYREG_CSD0_CONFIG
#define CapSense_IDAC1_cy_psoc4_idac__POLARITY_SHIFT 16u

/* CapSense_IDAC2_cy_psoc4_idac */
#define CapSense_IDAC2_cy_psoc4_idac__CONTROL CYREG_CSD0_CONFIG
#define CapSense_IDAC2_cy_psoc4_idac__CSD_IDAC CYREG_CSD0_IDAC
#define CapSense_IDAC2_cy_psoc4_idac__CSD_IDAC_SHIFT 16u
#define CapSense_IDAC2_cy_psoc4_idac__CSD_TRIM1 CYREG_CSD0_TRIM1
#define CapSense_IDAC2_cy_psoc4_idac__CSD_TRIM1_SHIFT 4u
#define CapSense_IDAC2_cy_psoc4_idac__CSD_TRIM2 CYREG_CSD0_TRIM2
#define CapSense_IDAC2_cy_psoc4_idac__CSD_TRIM2_SHIFT 4u
#define CapSense_IDAC2_cy_psoc4_idac__IDAC_NUMBER 2u
#define CapSense_IDAC2_cy_psoc4_idac__POLARITY CYREG_CSD0_CONFIG
#define CapSense_IDAC2_cy_psoc4_idac__POLARITY_SHIFT 17u

/* CapSense_ISR */
#define CapSense_ISR__INTC_CLR_EN_REG CYREG_CM0_ICER
#define CapSense_ISR__INTC_CLR_PD_REG CYREG_CM0_ICPR
#define CapSense_ISR__INTC_MASK 0x20000u
#define CapSense_ISR__INTC_NUMBER 17u
#define CapSense_ISR__INTC_PRIOR_MASK 0xC000u
#define CapSense_ISR__INTC_PRIOR_NUM 3u
#define CapSense_ISR__INTC_PRIOR_REG CYREG_CM0_IPR4
#define CapSense_ISR__INTC_SET_EN_REG CYREG_CM0_ISER
#define CapSense_ISR__INTC_SET_PD_REG CYREG_CM0_ISPR

/* CapSense_SampleClk */
#define CapSense_SampleClk__CTRL_REGISTER CYREG_PERI_PCLK_CTL7
#define CapSense_SampleClk__DIV_ID 0x00000040u
#define CapSense_SampleClk__DIV_REGISTER CYREG_PERI_DIV_16_CTL0
#define CapSense_SampleClk__PA_DIV_ID 0x000000FFu

/* CapSense_SenseClk */
#define CapSense_SenseClk__CTRL_REGISTER CYREG_PERI_PCLK_CTL6
#define CapSense_SenseClk__DIV_ID 0x00000041u
#define CapSense_SenseClk__DIV_REGISTER CYREG_PERI_DIV_16_CTL1
#define CapSense_SenseClk__PA_DIV_ID 0x000000FFu

/* CapSense_Sns */
#define CapSense_Sns__0__DR CYREG_GPIO_PRT1_DR
#define CapSense_Sns__0__DR_CLR CYREG_GPIO_PRT1_DR_CLR
#define CapSense_Sns__0__DR_INV CYREG_GPIO_PRT1_DR_INV
#define CapSense_Sns__0__DR_SET CYREG_GPIO_PRT1_DR_SET
#define CapSense_Sns__0__HSIOM CYREG_HSIOM_PORT_SEL1
#define CapSense_Sns__0__HSIOM_MASK 0x0000000Fu
#define CapSense_Sns__0__HSIOM_SHIFT 0u
#define CapSense_Sns__0__INTCFG CYREG_GPIO_PRT1_INTR_CFG
#define CapSense_Sns__0__INTR CYREG_GPIO_PRT1_INTR
#define CapSense_Sns__0__INTR_CFG CYREG_GPIO_PRT1_INTR_CFG
#define CapSense_Sns__0__INTSTAT CYREG_GPIO_PRT1_INTR
#define CapSense_Sns__0__MASK 0x01u
#define CapSense_Sns__0__PA__CFG0 CYREG_UDB_PA1_CFG0
#define CapSense_Sns__0__PA__CFG1 CYREG_UDB_PA1_CFG1
#define CapSense_Sns__0__PA__CFG10 CYREG_UDB_PA1_CFG10
#define CapSense_Sns__0__PA__CFG11 CYREG_UDB_PA1_CFG11
#define CapSense_Sns__0__PA__CFG12 CYREG_UDB_PA1_CFG12
#define CapSense_Sns__0__PA__CFG13 CYREG_UDB_PA1_CFG13
#define CapSense_Sns__0__PA__CFG14 CYREG_UDB_PA1_CFG14
#define CapSense_Sns__0__PA__CFG2 CYREG_UDB_PA1_CFG2
#define CapSense_Sns__0__PA__CFG3 CYREG_UDB_PA1_CFG3
#define CapSense_Sns__0__PA__CFG4 CYREG_UDB_PA1_CFG4
#define CapSense_Sns__0__PA__CFG5 CYREG_UDB_PA1_CFG5
#define CapSense_Sns__0__PA__CFG6 CYREG_UDB_PA1_CFG6
#define CapSense_Sns__0__PA__CFG7 CYREG_UDB_PA1_CFG7
#define CapSense_Sns__0__PA__CFG8 CYREG_UDB_PA1_CFG8
#define CapSense_Sns__0__PA__CFG9 CYREG_UDB_PA1_CFG9
#define CapSense_Sns__0__PC CYREG_GPIO_PRT1_PC
#define CapSense_Sns__0__PC2 CYREG_GPIO_PRT1_PC2
#define CapSense_Sns__0__PORT 1u
#define CapSense_Sns__0__PS CYREG_GPIO_PRT1_PS
#define CapSense_Sns__0__SHIFT 0u
#define CapSense_Sns__Button0__BTN__DR CYREG_GPIO_PRT1_DR
#define CapSense_Sns__Button0__BTN__DR_CLR CYREG_GPIO_PRT1_DR_CLR
#define CapSense_Sns__Button0__BTN__DR_INV CYREG_GPIO_PRT1_DR_INV
#define CapSense_Sns__Button0__BTN__DR_SET CYREG_GPIO_PRT1_DR_SET
#define CapSense_Sns__Button0__BTN__INTCFG CYREG_GPIO_PRT1_INTR_CFG
#define CapSense_Sns__Button0__BTN__INTR CYREG_GPIO_PRT1_INTR
#define CapSense_Sns__Button0__BTN__INTR_CFG CYREG_GPIO_PRT1_INTR_CFG
#define CapSense_Sns__Button0__BTN__INTSTAT CYREG_GPIO_PRT1_INTR
#define CapSense_Sns__Button0__BTN__MASK 0x01u
#define CapSense_Sns__Button0__BTN__PA__CFG0 CYREG_UDB_PA1_CFG0
#define CapSense_Sns__Button0__BTN__PA__CFG1 CYREG_UDB_PA1_CFG1
#define CapSense_Sns__Button0__BTN__PA__CFG10 CYREG_UDB_PA1_CFG10
#define CapSense_Sns__Button0__BTN__PA__CFG11 CYREG_UDB_PA1_CFG11
#define CapSense_Sns__Button0__BTN__PA__CFG12 CYREG_UDB_PA1_CFG12
#define CapSense_Sns__Button0__BTN__PA__CFG13 CYREG_UDB_PA1_CFG13
#define CapSense_Sns__Button0__BTN__PA__CFG14 CYREG_UDB_PA1_CFG14
#define CapSense_Sns__Button0__BTN__PA__CFG2 CYREG_UDB_PA1_CFG2
#define CapSense_Sns__Button0__BTN__PA__CFG3 CYREG_UDB_PA1_CFG3
#define CapSense_Sns__Button0__BTN__PA__CFG4 CYREG_UDB_PA1_CFG4
#define CapSense_Sns__Button0__BTN__PA__CFG5 CYREG_UDB_PA1_CFG5
#define CapSense_Sns__Button0__BTN__PA__CFG6 CYREG_UDB_PA1_CFG6
#define CapSense_Sns__Button0__BTN__PA__CFG7 CYREG_UDB_PA1_CFG7
#define CapSense_Sns__Button0__BTN__PA__CFG8 CYREG_UDB_PA1_CFG8
#define CapSense_Sns__Button0__BTN__PA__CFG9 CYREG_UDB_PA1_CFG9
#define CapSense_Sns__Button0__BTN__PC CYREG_GPIO_PRT1_PC
#define CapSense_Sns__Button0__BTN__PC2 CYREG_GPIO_PRT1_PC2
#define CapSense_Sns__Button0__BTN__PORT 1u
#define CapSense_Sns__Button0__BTN__PS CYREG_GPIO_PRT1_PS
#define CapSense_Sns__Button0__BTN__SHIFT 0u
#define CapSense_Sns__DR CYREG_GPIO_PRT1_DR
#define CapSense_Sns__DR_CLR CYREG_GPIO_PRT1_DR_CLR
#define CapSense_Sns__DR_INV CYREG_GPIO_PRT1_DR_INV
#define CapSense_Sns__DR_SET CYREG_GPIO_PRT1_DR_SET
#define CapSense_Sns__INTCFG CYREG_GPIO_PRT1_INTR_CFG
#define CapSense_Sns__INTR CYREG_GPIO_PRT1_INTR
#define CapSense_Sns__INTR_CFG CYREG_GPIO_PRT1_INTR_CFG
#define CapSense_Sns__INTSTAT CYREG_GPIO_PRT1_INTR
#define CapSense_Sns__MASK 0x01u
#define CapSense_Sns__PA__CFG0 CYREG_UDB_PA1_CFG0
#define CapSense_Sns__PA__CFG1 CYREG_UDB_PA1_CFG1
#define CapSense_Sns__PA__CFG10 CYREG_UDB_PA1_CFG10
#define CapSense_Sns__PA__CFG11 CYREG_UDB_PA1_CFG11
#define CapSense_Sns__PA__CFG12 CYREG_UDB_PA1_CFG12
#define CapSense_Sns__PA__CFG13 CYREG_UDB_PA1_CFG13
#define CapSense_Sns__PA__CFG14 CYREG_UDB_PA1_CFG14
#define CapSense_Sns__PA__CFG2 CYREG_UDB_PA1_CFG2
#define CapSense_Sns__PA__CFG3 CYREG_UDB_PA1_CFG3
#define CapSense_Sns__PA__CFG4 CYREG_UDB_PA1_CFG4
#define CapSense_Sns__PA__CFG5 CYREG_UDB_PA1_CFG5
#define CapSense_Sns__PA__CFG6 CYREG_UDB_PA1_CFG6
#define CapSense_Sns__PA__CFG7 CYREG_UDB_PA1_CFG7
#define CapSense_Sns__PA__CFG8 CYREG_UDB_PA1_CFG8
#define CapSense_Sns__PA__CFG9 CYREG_UDB_PA1_CFG9
#define CapSense_Sns__PC CYREG_GPIO_PRT1_PC
#define CapSense_Sns__PC2 CYREG_GPIO_PRT1_PC2
#define CapSense_Sns__PORT 1u
#define CapSense_Sns__PS CYREG_GPIO_PRT1_PS
#define CapSense_Sns__SHIFT 0u

/* Miscellaneous */
#define CY_PROJECT_NAME "Example10b-PSoC"
#define CY_VERSION "PSoC Creator  3.3 SP2"
#define CYDEV_BANDGAP_VOLTAGE 1.024
#define CYDEV_BCLK__HFCLK__HZ 48000000U
#define CYDEV_BCLK__HFCLK__KHZ 48000U
#define CYDEV_BCLK__HFCLK__MHZ 48U
#define CYDEV_BCLK__SYSCLK__HZ 48000000U
#define CYDEV_BCLK__SYSCLK__KHZ 48000U
#define CYDEV_BCLK__SYSCLK__MHZ 48U
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PANTHER 19u
#define CYDEV_CHIP_DIE_PSOC4A 11u
#define CYDEV_CHIP_DIE_PSOC5LP 18u
#define CYDEV_CHIP_DIE_TMA4 2u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC4
#define CYDEV_CHIP_JTAG_ID 0x112D11A1u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 11u
#define CYDEV_CHIP_MEMBER_4C 16u
#define CYDEV_CHIP_MEMBER_4D 7u
#define CYDEV_CHIP_MEMBER_4E 4u
#define CYDEV_CHIP_MEMBER_4F 12u
#define CYDEV_CHIP_MEMBER_4G 2u
#define CYDEV_CHIP_MEMBER_4H 10u
#define CYDEV_CHIP_MEMBER_4I 15u
#define CYDEV_CHIP_MEMBER_4J 8u
#define CYDEV_CHIP_MEMBER_4K 9u
#define CYDEV_CHIP_MEMBER_4L 14u
#define CYDEV_CHIP_MEMBER_4M 13u
#define CYDEV_CHIP_MEMBER_4N 6u
#define CYDEV_CHIP_MEMBER_4O 5u
#define CYDEV_CHIP_MEMBER_4U 3u
#define CYDEV_CHIP_MEMBER_5A 18u
#define CYDEV_CHIP_MEMBER_5B 17u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_4M
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_MEMBER_USED
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REV_TMA4_ES 17u
#define CYDEV_CHIP_REV_TMA4_ES2 33u
#define CYDEV_CHIP_REV_TMA4_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4C_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4D_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4E_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0u
#define CYDEV_CHIP_REVISION_4G_ES 17u
#define CYDEV_CHIP_REVISION_4G_ES2 33u
#define CYDEV_CHIP_REVISION_4G_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4H_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4I_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4J_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4K_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4L_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4M_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4N_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4O_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4U_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_4M_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REVISION_USED
#define CYDEV_CONFIG_READ_ACCELERATOR 1
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_DEBUG_PROTECT_KILL 4
#define CYDEV_DEBUG_PROTECT_OPEN 1
#define CYDEV_DEBUG_PROTECT CYDEV_DEBUG_PROTECT_OPEN
#define CYDEV_DEBUG_PROTECT_PROTECTED 2
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DFT_SELECT_CLK0 10u
#define CYDEV_DFT_SELECT_CLK1 11u
#define CYDEV_DMA_CHANNELS_AVAILABLE 8
#define CYDEV_HEAP_SIZE 0x80
#define CYDEV_IMO_TRIMMED_BY_USB 0u
#define CYDEV_IMO_TRIMMED_BY_WCO 0u
#define CYDEV_INTR_NUMBER_DMA 13u
#define CYDEV_IS_EXPORTING_CODE 0
#define CYDEV_IS_IMPORTING_CODE 0
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LAUNCHER 5
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER 4
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_STACK_SIZE 0x0800
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 1
#define CYDEV_VDDA 3.3
#define CYDEV_VDDA_MV 3300
#define CYDEV_VDDD 3.3
#define CYDEV_VDDD_MV 3300
#define CYDEV_VDDIO 3.3
#define CYDEV_VDDIO_MV 3300
#define CYDEV_WDT_GENERATE_ISR 1u
#define CYIPBLOCK_m0s8can_VERSION 1
#define CYIPBLOCK_m0s8cpussv2_VERSION 1
#define CYIPBLOCK_m0s8csd_VERSION 1
#define CYIPBLOCK_m0s8ioss_VERSION 1
#define CYIPBLOCK_m0s8lcd_VERSION 2
#define CYIPBLOCK_m0s8lpcomp_VERSION 2
#define CYIPBLOCK_m0s8peri_VERSION 1
#define CYIPBLOCK_m0s8scb_VERSION 2
#define CYIPBLOCK_m0s8srssv2_VERSION 1
#define CYIPBLOCK_m0s8tcpwm_VERSION 2
#define CYIPBLOCK_m0s8udbif_VERSION 1
#define CYIPBLOCK_m0s8wco_VERSION 1
#define CYIPBLOCK_s8pass4al_VERSION 1
#define DMA_CHANNELS_USED__MASK 0u
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */