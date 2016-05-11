/*******************************************************************************
* File Name: PWW.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the PWW
*  component
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

uint8 PWW_initVar = 0u;


/*******************************************************************************
* Function Name: PWW_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default PWW configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWW_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (PWW__QUAD == PWW_CONFIG)
        PWW_CONTROL_REG = PWW_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        PWW_TRIG_CONTROL1_REG  = PWW_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        PWW_SetInterruptMode(PWW_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        PWW_SetCounterMode(PWW_COUNT_DOWN);
        PWW_WritePeriod(PWW_QUAD_PERIOD_INIT_VALUE);
        PWW_WriteCounter(PWW_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (PWW__QUAD == PWW_CONFIG) */

    #if (PWW__TIMER == PWW_CONFIG)
        PWW_CONTROL_REG = PWW_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        PWW_TRIG_CONTROL1_REG  = PWW_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        PWW_SetInterruptMode(PWW_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        PWW_WritePeriod(PWW_TC_PERIOD_VALUE );

        #if (PWW__COMPARE == PWW_TC_COMP_CAP_MODE)
            PWW_WriteCompare(PWW_TC_COMPARE_VALUE);

            #if (1u == PWW_TC_COMPARE_SWAP)
                PWW_SetCompareSwap(1u);
                PWW_WriteCompareBuf(PWW_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == PWW_TC_COMPARE_SWAP) */
        #endif  /* (PWW__COMPARE == PWW_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (PWW_CY_TCPWM_V2 && PWW_TIMER_UPDOWN_CNT_USED && !PWW_CY_TCPWM_4000)
            PWW_WriteCounter(1u);
        #elif(PWW__COUNT_DOWN == PWW_TC_COUNTER_MODE)
            PWW_WriteCounter(PWW_TC_PERIOD_VALUE);
        #else
            PWW_WriteCounter(0u);
        #endif /* (PWW_CY_TCPWM_V2 && PWW_TIMER_UPDOWN_CNT_USED && !PWW_CY_TCPWM_4000) */
    #endif  /* (PWW__TIMER == PWW_CONFIG) */

    #if (PWW__PWM_SEL == PWW_CONFIG)
        PWW_CONTROL_REG = PWW_CTRL_PWM_BASE_CONFIG;

        #if (PWW__PWM_PR == PWW_PWM_MODE)
            PWW_CONTROL_REG |= PWW_CTRL_PWM_RUN_MODE;
            PWW_WriteCounter(PWW_PWM_PR_INIT_VALUE);
        #else
            PWW_CONTROL_REG |= PWW_CTRL_PWM_ALIGN | PWW_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (PWW_CY_TCPWM_V2 && PWW_PWM_UPDOWN_CNT_USED && !PWW_CY_TCPWM_4000)
                PWW_WriteCounter(1u);
            #elif (PWW__RIGHT == PWW_PWM_ALIGN)
                PWW_WriteCounter(PWW_PWM_PERIOD_VALUE);
            #else 
                PWW_WriteCounter(0u);
            #endif  /* (PWW_CY_TCPWM_V2 && PWW_PWM_UPDOWN_CNT_USED && !PWW_CY_TCPWM_4000) */
        #endif  /* (PWW__PWM_PR == PWW_PWM_MODE) */

        #if (PWW__PWM_DT == PWW_PWM_MODE)
            PWW_CONTROL_REG |= PWW_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (PWW__PWM_DT == PWW_PWM_MODE) */

        #if (PWW__PWM == PWW_PWM_MODE)
            PWW_CONTROL_REG |= PWW_CTRL_PWM_PRESCALER;
        #endif  /* (PWW__PWM == PWW_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        PWW_TRIG_CONTROL1_REG  = PWW_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        PWW_SetInterruptMode(PWW_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (PWW__PWM_PR == PWW_PWM_MODE)
            PWW_TRIG_CONTROL2_REG =
                    (PWW_CC_MATCH_NO_CHANGE    |
                    PWW_OVERLOW_NO_CHANGE      |
                    PWW_UNDERFLOW_NO_CHANGE);
        #else
            #if (PWW__LEFT == PWW_PWM_ALIGN)
                PWW_TRIG_CONTROL2_REG = PWW_PWM_MODE_LEFT;
            #endif  /* ( PWW_PWM_LEFT == PWW_PWM_ALIGN) */

            #if (PWW__RIGHT == PWW_PWM_ALIGN)
                PWW_TRIG_CONTROL2_REG = PWW_PWM_MODE_RIGHT;
            #endif  /* ( PWW_PWM_RIGHT == PWW_PWM_ALIGN) */

            #if (PWW__CENTER == PWW_PWM_ALIGN)
                PWW_TRIG_CONTROL2_REG = PWW_PWM_MODE_CENTER;
            #endif  /* ( PWW_PWM_CENTER == PWW_PWM_ALIGN) */

            #if (PWW__ASYMMETRIC == PWW_PWM_ALIGN)
                PWW_TRIG_CONTROL2_REG = PWW_PWM_MODE_ASYM;
            #endif  /* (PWW__ASYMMETRIC == PWW_PWM_ALIGN) */
        #endif  /* (PWW__PWM_PR == PWW_PWM_MODE) */

        /* Set other values from customizer */
        PWW_WritePeriod(PWW_PWM_PERIOD_VALUE );
        PWW_WriteCompare(PWW_PWM_COMPARE_VALUE);

        #if (1u == PWW_PWM_COMPARE_SWAP)
            PWW_SetCompareSwap(1u);
            PWW_WriteCompareBuf(PWW_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == PWW_PWM_COMPARE_SWAP) */

        #if (1u == PWW_PWM_PERIOD_SWAP)
            PWW_SetPeriodSwap(1u);
            PWW_WritePeriodBuf(PWW_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == PWW_PWM_PERIOD_SWAP) */
    #endif  /* (PWW__PWM_SEL == PWW_CONFIG) */
    
}


/*******************************************************************************
* Function Name: PWW_Enable
********************************************************************************
*
* Summary:
*  Enables the PWW.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWW_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    PWW_BLOCK_CONTROL_REG |= PWW_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (PWW__PWM_SEL == PWW_CONFIG)
        #if (0u == PWW_PWM_START_SIGNAL_PRESENT)
            PWW_TriggerCommand(PWW_MASK, PWW_CMD_START);
        #endif /* (0u == PWW_PWM_START_SIGNAL_PRESENT) */
    #endif /* (PWW__PWM_SEL == PWW_CONFIG) */

    #if (PWW__TIMER == PWW_CONFIG)
        #if (0u == PWW_TC_START_SIGNAL_PRESENT)
            PWW_TriggerCommand(PWW_MASK, PWW_CMD_START);
        #endif /* (0u == PWW_TC_START_SIGNAL_PRESENT) */
    #endif /* (PWW__TIMER == PWW_CONFIG) */
    
    #if (PWW__QUAD == PWW_CONFIG)
        #if (0u != PWW_QUAD_AUTO_START)
            PWW_TriggerCommand(PWW_MASK, PWW_CMD_RELOAD);
        #endif /* (0u != PWW_QUAD_AUTO_START) */
    #endif  /* (PWW__QUAD == PWW_CONFIG) */
}


/*******************************************************************************
* Function Name: PWW_Start
********************************************************************************
*
* Summary:
*  Initializes the PWW with default customizer
*  values when called the first time and enables the PWW.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWW_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time PWW_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the PWW_Start() routine.
*
*******************************************************************************/
void PWW_Start(void)
{
    if (0u == PWW_initVar)
    {
        PWW_Init();
        PWW_initVar = 1u;
    }

    PWW_Enable();
}


/*******************************************************************************
* Function Name: PWW_Stop
********************************************************************************
*
* Summary:
*  Disables the PWW.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWW_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_BLOCK_CONTROL_REG &= (uint32)~PWW_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the PWW. This function is used when
*  configured as a generic PWW and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the PWW to operate in
*   Values:
*   - PWW_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - PWW_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - PWW_MODE_QUAD - Quadrature decoder
*         - PWW_MODE_PWM - PWM
*         - PWW_MODE_PWM_DT - PWM with dead time
*         - PWW_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_CONTROL_REG &= (uint32)~PWW_MODE_MASK;
    PWW_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - PWW_MODE_X1 - Counts on phi 1 rising
*         - PWW_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - PWW_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_CONTROL_REG &= (uint32)~PWW_QUAD_MODE_MASK;
    PWW_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - PWW_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - PWW_PRESCALE_DIVBY2    - Divide by 2
*         - PWW_PRESCALE_DIVBY4    - Divide by 4
*         - PWW_PRESCALE_DIVBY8    - Divide by 8
*         - PWW_PRESCALE_DIVBY16   - Divide by 16
*         - PWW_PRESCALE_DIVBY32   - Divide by 32
*         - PWW_PRESCALE_DIVBY64   - Divide by 64
*         - PWW_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_CONTROL_REG &= (uint32)~PWW_PRESCALER_MASK;
    PWW_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWW runs
*  continuously or stops when terminal count is reached.  By default the
*  PWW operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_CONTROL_REG &= (uint32)~PWW_ONESHOT_MASK;
    PWW_CONTROL_REG |= ((uint32)((oneShotEnable & PWW_1BIT_MASK) <<
                                                               PWW_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetPWMMode(uint32 modeMask)
{
    PWW_TRIG_CONTROL2_REG = (modeMask & PWW_6BIT_MASK);
}



/*******************************************************************************
* Function Name: PWW_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_CONTROL_REG &= (uint32)~PWW_PWM_SYNC_KILL_MASK;
    PWW_CONTROL_REG |= ((uint32)((syncKillEnable & PWW_1BIT_MASK)  <<
                                               PWW_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_CONTROL_REG &= (uint32)~PWW_PWM_STOP_KILL_MASK;
    PWW_CONTROL_REG |= ((uint32)((stopOnKillEnable & PWW_1BIT_MASK)  <<
                                                         PWW_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_CONTROL_REG &= (uint32)~PWW_PRESCALER_MASK;
    PWW_CONTROL_REG |= ((uint32)((deadTime & PWW_8BIT_MASK) <<
                                                          PWW_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - PWW_INVERT_LINE   - Inverts the line output
*         - PWW_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_CONTROL_REG &= (uint32)~PWW_INV_OUT_MASK;
    PWW_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: PWW_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void PWW_WriteCounter(uint32 count)
{
    PWW_COUNTER_REG = (count & PWW_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWW_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 PWW_ReadCounter(void)
{
    return (PWW_COUNTER_REG & PWW_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWW_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - PWW_COUNT_UP       - Counts up
*     - PWW_COUNT_DOWN     - Counts down
*     - PWW_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - PWW_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_CONTROL_REG &= (uint32)~PWW_UPDOWN_MASK;
    PWW_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void PWW_WritePeriod(uint32 period)
{
    PWW_PERIOD_REG = (period & PWW_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWW_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 PWW_ReadPeriod(void)
{
    return (PWW_PERIOD_REG & PWW_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWW_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_CONTROL_REG &= (uint32)~PWW_RELOAD_CC_MASK;
    PWW_CONTROL_REG |= (swapEnable & PWW_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void PWW_WritePeriodBuf(uint32 periodBuf)
{
    PWW_PERIOD_BUF_REG = (periodBuf & PWW_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWW_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 PWW_ReadPeriodBuf(void)
{
    return (PWW_PERIOD_BUF_REG & PWW_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWW_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_CONTROL_REG &= (uint32)~PWW_RELOAD_PERIOD_MASK;
    PWW_CONTROL_REG |= ((uint32)((swapEnable & PWW_1BIT_MASK) <<
                                                            PWW_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void PWW_WriteCompare(uint32 compare)
{
    #if (PWW_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (PWW_CY_TCPWM_4000) */

    #if (PWW_CY_TCPWM_4000)
        currentMode = ((PWW_CONTROL_REG & PWW_UPDOWN_MASK) >> PWW_UPDOWN_SHIFT);

        if (((uint32)PWW__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)PWW__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (PWW_CY_TCPWM_4000) */
    
    PWW_COMP_CAP_REG = (compare & PWW_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWW_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 PWW_ReadCompare(void)
{
    #if (PWW_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (PWW_CY_TCPWM_4000) */

    #if (PWW_CY_TCPWM_4000)
        currentMode = ((PWW_CONTROL_REG & PWW_UPDOWN_MASK) >> PWW_UPDOWN_SHIFT);
        
        regVal = PWW_COMP_CAP_REG;
        
        if (((uint32)PWW__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)PWW__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & PWW_16BIT_MASK);
    #else
        return (PWW_COMP_CAP_REG & PWW_16BIT_MASK);
    #endif /* (PWW_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: PWW_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void PWW_WriteCompareBuf(uint32 compareBuf)
{
    #if (PWW_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (PWW_CY_TCPWM_4000) */

    #if (PWW_CY_TCPWM_4000)
        currentMode = ((PWW_CONTROL_REG & PWW_UPDOWN_MASK) >> PWW_UPDOWN_SHIFT);

        if (((uint32)PWW__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)PWW__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (PWW_CY_TCPWM_4000) */
    
    PWW_COMP_CAP_BUF_REG = (compareBuf & PWW_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWW_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 PWW_ReadCompareBuf(void)
{
    #if (PWW_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (PWW_CY_TCPWM_4000) */

    #if (PWW_CY_TCPWM_4000)
        currentMode = ((PWW_CONTROL_REG & PWW_UPDOWN_MASK) >> PWW_UPDOWN_SHIFT);

        regVal = PWW_COMP_CAP_BUF_REG;
        
        if (((uint32)PWW__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)PWW__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & PWW_16BIT_MASK);
    #else
        return (PWW_COMP_CAP_BUF_REG & PWW_16BIT_MASK);
    #endif /* (PWW_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: PWW_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 PWW_ReadCapture(void)
{
    return (PWW_COMP_CAP_REG & PWW_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWW_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 PWW_ReadCaptureBuf(void)
{
    return (PWW_COMP_CAP_BUF_REG & PWW_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWW_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWW_TRIG_LEVEL     - Level
*     - PWW_TRIG_RISING    - Rising edge
*     - PWW_TRIG_FALLING   - Falling edge
*     - PWW_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_TRIG_CONTROL1_REG &= (uint32)~PWW_CAPTURE_MASK;
    PWW_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWW_TRIG_LEVEL     - Level
*     - PWW_TRIG_RISING    - Rising edge
*     - PWW_TRIG_FALLING   - Falling edge
*     - PWW_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_TRIG_CONTROL1_REG &= (uint32)~PWW_RELOAD_MASK;
    PWW_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWW_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWW_TRIG_LEVEL     - Level
*     - PWW_TRIG_RISING    - Rising edge
*     - PWW_TRIG_FALLING   - Falling edge
*     - PWW_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_TRIG_CONTROL1_REG &= (uint32)~PWW_START_MASK;
    PWW_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWW_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWW_TRIG_LEVEL     - Level
*     - PWW_TRIG_RISING    - Rising edge
*     - PWW_TRIG_FALLING   - Falling edge
*     - PWW_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_TRIG_CONTROL1_REG &= (uint32)~PWW_STOP_MASK;
    PWW_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWW_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWW_TRIG_LEVEL     - Level
*     - PWW_TRIG_RISING    - Rising edge
*     - PWW_TRIG_FALLING   - Falling edge
*     - PWW_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_TRIG_CONTROL1_REG &= (uint32)~PWW_COUNT_MASK;
    PWW_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWW_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - PWW_CMD_CAPTURE    - Trigger Capture/Switch command
*     - PWW_CMD_RELOAD     - Trigger Reload/Index command
*     - PWW_CMD_STOP       - Trigger Stop/Kill command
*     - PWW_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void PWW_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWW_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWW_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the PWW.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - PWW_STATUS_DOWN    - Set if counting down
*     - PWW_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 PWW_ReadStatus(void)
{
    return ((PWW_STATUS_REG >> PWW_RUNNING_STATUS_SHIFT) |
            (PWW_STATUS_REG & PWW_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: PWW_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - PWW_INTR_MASK_TC       - Terminal count mask
*     - PWW_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetInterruptMode(uint32 interruptMask)
{
    PWW_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: PWW_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - PWW_INTR_MASK_TC       - Terminal count mask
*     - PWW_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PWW_GetInterruptSourceMasked(void)
{
    return (PWW_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: PWW_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - PWW_INTR_MASK_TC       - Terminal count mask
*     - PWW_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PWW_GetInterruptSource(void)
{
    return (PWW_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: PWW_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - PWW_INTR_MASK_TC       - Terminal count mask
*     - PWW_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWW_ClearInterrupt(uint32 interruptMask)
{
    PWW_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: PWW_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - PWW_INTR_MASK_TC       - Terminal count mask
*     - PWW_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWW_SetInterrupt(uint32 interruptMask)
{
    PWW_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
