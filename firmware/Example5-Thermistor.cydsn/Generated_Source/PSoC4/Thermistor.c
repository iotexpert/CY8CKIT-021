/*******************************************************************************
* File Name: Thermistor.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the ThermistorCalc
*  Component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Thermistor.h"


/*******************************************************************************
* Function Name: Thermistor_GetResistance
********************************************************************************
*
* Summary:
*  The digital values of the voltages across the reference resistor and the
*  thermistor are passed to this function as parameters. The function returns
*  the resistance, based on the voltage values.
*
* Parameters:
*  vReference: the voltage across the reference resistor;
*  vThermistor: the voltage across the thermistor.
*  The ratio of these two voltages is used by this function. Therefore, the
*  units for both parameters must be the same.
*
* Return:
*  The return value is the resistance across the thermistor. The value returned
*  is the resistance in Ohms.
*
*******************************************************************************/
uint32 Thermistor_GetResistance(int16 vReference, int16 vThermistor)
                                      
{
    int32 resT;
    int16 temp;

    /* Calculate thermistor resistance from the voltages */
    resT = Thermistor_REF_RESISTOR * ((int32)vThermistor);
    if (vReference < 0)
    {
        temp = -vReference;
        temp = (int16)((uint16)((uint16)temp >> 1u));
        temp = -temp;
    }
    else
    {
        temp = (int16)((uint16)((uint16)vReference >> 1u));
    }
    resT += temp;
    resT /= vReference;

    /* The ordering of Reference resistor value is specifically designed to keep the result from overflowing */
    return ((uint32)((uint32)resT << Thermistor_REF_RES_SHIFT));
}


/*******************************************************************************
* Function Name: Thermistor_GetTemperature
********************************************************************************
*
* Summary:
*  The value of the thermistor resistance is passed to this function as a
*  parameter. The function returns the temperature, based on the resistance
*  value. The method used to calculate the temperature is dependent on whether
*  Equation or LUT was selected in the Customizer.
*
* Parameters:
*  resT: the resistance across the thermistor in Ohms.
*
* Return:
*  The return value is the temperature in 1/100ths of degrees C. For example,
*  the return value is 2345, when the actual temperature is 23.45 degrees C.
*
*******************************************************************************/
int16 Thermistor_GetTemperature(uint32 resT) 
{
    int16 tempTR;
    static const uint32 CYCODE Thermistor_LUT[] = { 27219u, 27103u, 26987u, 26871u, 26757u, 26643u, 26529u, 26416u, 26303u,
 26191u, 26080u, 25969u, 25859u, 25749u, 25639u, 25531u, 25422u, 25315u, 25207u, 25101u, 24994u, 24889u, 24783u, 24679u,
 24575u, 24471u, 24368u, 24265u, 24163u, 24061u, 23960u, 23859u, 23759u, 23659u, 23559u, 23461u, 23362u, 23264u, 23167u,
 23070u, 22973u, 22877u, 22782u, 22686u, 22592u, 22497u, 22403u, 22310u, 22217u, 22125u, 22033u, 21941u, 21850u, 21759u,
 21669u, 21579u, 21489u, 21400u, 21311u, 21223u, 21135u, 21048u, 20961u, 20874u, 20788u, 20702u, 20617u, 20532u, 20447u,
 20363u, 20279u, 20196u, 20113u, 20030u, 19948u, 19866u, 19784u, 19703u, 19623u, 19542u, 19462u, 19383u, 19303u, 19224u,
 19146u, 19068u, 18990u, 18912u, 18835u, 18759u, 18682u, 18606u, 18531u, 18455u, 18380u, 18306u, 18231u, 18157u, 18084u,
 18011u, 17938u, 17865u, 17793u, 17721u, 17649u, 17578u, 17507u, 17437u, 17366u, 17296u, 17227u, 17157u, 17088u, 17020u,
 16951u, 16883u, 16815u, 16748u, 16681u, 16614u, 16547u, 16481u, 16415u, 16350u, 16284u, 16219u, 16154u, 16090u, 16026u,
 15962u, 15898u, 15835u, 15772u, 15709u, 15647u, 15585u, 15523u, 15461u, 15400u, 15339u, 15278u, 15218u, 15157u, 15097u,
 15038u, 14978u, 14919u, 14860u, 14802u, 14743u, 14685u, 14627u, 14570u, 14513u, 14456u, 14399u, 14342u, 14286u, 14230u,
 14174u, 14118u, 14063u, 14008u, 13953u, 13899u, 13844u, 13790u, 13737u, 13683u, 13630u, 13576u, 13524u, 13471u, 13418u,
 13366u, 13314u, 13263u, 13211u, 13160u, 13109u, 13058u, 13007u, 12957u, 12907u, 12857u, 12807u, 12758u, 12708u, 12659u,
 12610u, 12562u, 12513u, 12465u, 12417u, 12369u, 12322u, 12275u, 12227u, 12180u, 12134u, 12087u, 12041u, 11995u, 11949u,
 11903u, 11857u, 11812u, 11767u, 11722u, 11677u, 11633u, 11588u, 11544u, 11500u, 11456u, 11413u, 11369u, 11326u, 11283u,
 11240u, 11198u, 11155u, 11113u, 11071u, 11029u, 10987u, 10946u, 10904u, 10863u, 10822u, 10781u, 10741u, 10700u, 10660u,
 10620u, 10580u, 10540u, 10500u, 10461u, 10421u, 10382u, 10343u, 10304u, 10266u, 10227u, 10189u, 10151u, 10113u, 10075u,
 10037u, 10000u, 9963u, 9926u, 9888u, 9852u, 9815u, 9778u, 9742u, 9706u, 9670u, 9634u, 9598u, 9562u, 9527u, 9492u,
 9456u, 9421u, 9387u, 9352u, 9317u, 9283u, 9249u, 9214u, 9180u, 9147u, 9113u, 9079u, 9046u, 9013u, 8979u, 8946u, 8913u,
 8881u, 8848u, 8816u, 8783u, 8751u, 8719u, 8687u, 8655u, 8624u, 8592u, 8561u, 8530u, 8498u, 8467u, 8437u, 8406u, 8375u,
 8345u, 8314u, 8284u, 8254u, 8224u, 8194u, 8165u, 8135u, 8105u, 8076u, 8047u, 8018u, 7989u, 7960u, 7931u, 7902u, 7874u,
 7845u, 7817u, 7789u, 7761u, 7733u, 7705u, 7678u, 7650u, 7622u, 7595u, 7568u, 7541u, 7514u, 7487u, 7460u, 7433u, 7407u,
 7380u, 7354u, 7327u, 7301u, 7275u, 7249u, 7223u, 7198u, 7172u, 7147u, 7121u, 7096u, 7071u, 7046u, 7021u, 6996u, 6971u,
 6946u, 6921u, 6897u, 6873u, 6848u, 6824u, 6800u, 6776u, 6752u, 6728u, 6704u, 6681u, 6657u, 6634u, 6611u, 6587u, 6564u,
 6541u, 6518u, 6495u, 6472u, 6450u, 6427u, 6405u, 6382u, 6360u, 6338u, 6316u, 6293u, 6271u, 6250u, 6228u, 6206u, 6184u,
 6163u, 6141u, 6120u, 6099u, 6078u, 6057u, 6035u, 6015u, 5994u, 5973u, 5952u, 5932u, 5911u, 5891u, 5870u, 5850u, 5830u,
 5810u, 5790u, 5770u, 5750u, 5730u, 5710u, 5691u, 5671u, 5651u, 5632u, 5613u, 5593u, 5574u, 5555u, 5536u, 5517u, 5498u,
 5479u, 5461u, 5442u, 5423u, 5405u, 5386u, 5368u, 5350u, 5332u, 5313u, 5295u, 5277u, 5259u, 5241u, 5224u, 5206u, 5188u,
 5171u, 5153u, 5136u, 5118u, 5101u, 5084u, 5066u, 5049u, 5032u, 5015u, 4998u, 4981u, 4965u, 4948u, 4931u, 4915u, 4898u,
 4882u, 4865u, 4849u, 4833u, 4816u, 4800u, 4784u, 4768u, 4752u, 4736u, 4720u, 4705u, 4689u, 4673u, 4658u, 4642u, 4627u,
 4611u, 4596u, 4580u, 4565u, 4550u, 4535u, 4520u, 4505u, 4490u, 4475u, 4460u, 4445u, 4431u, 4416u, 4401u, 4387u, 4372u,
 4358u, 4343u, 4329u, 4315u, 4300u, 4286u, 4272u, 4258u, 4244u, 4230u, 4216u, 4202u, 4188u, 4175u, 4161u };


    #if (Thermistor_IMPLEMENTATION == Thermistor_EQUATION_METHOD)

        float32 stEqn;
        float32 logrT;

        /* Calculate thermistor resistance from the voltages */
        #if(!CY_PSOC3)
            logrT = (float32)log((float64)resT);
        #else
            logrT = log((float32)resT);
        #endif  /* (!CY_PSOC3) */

        /* Calculate temperature from the resistance of thermistor using Steinhart-Hart Equation */
        #if(!CY_PSOC3)
            stEqn = (float32)(Thermistor_THA + (Thermistor_THB * logrT) + 
                             (Thermistor_THC * pow((float64)logrT, (float32)3)));
        #else
            stEqn = (float32)(Thermistor_THA + (Thermistor_THB * logrT) + 
                             (Thermistor_THC * pow(logrT, (float32)3)));
        #endif  /* (!CY_PSOC3) */

        tempTR = (int16)((float32)((((1.0 / stEqn) - Thermistor_K2C) * (float32)Thermistor_SCALE) + 0.5));

    #else /* Thermistor_IMPLEMENTATION == Thermistor_LUT_METHOD */

        uint16 mid;
        uint16 first = 0u;
        uint16 last = Thermistor_LUT_SIZE - 1u;

        /* Calculate temperature from the resistance of thermistor by using the LUT */
        while (first < last)
        {
            mid = (first + last) >> 1u;

            if ((0u == mid) || ((Thermistor_LUT_SIZE - 1u) == mid) || (resT == Thermistor_LUT[mid]))
            {
                last = mid;
                break;
            }
            else if (Thermistor_LUT[mid] > resT)
            {
                first = mid + 1u;
            }
            else /* (Thermistor_LUT[mid] < resT) */
            {
                last = mid - 1u;
            }
        }

        /* Calculation the closest entry in the LUT */
        if ((Thermistor_LUT[last] > resT) && (last < (Thermistor_LUT_SIZE - 1u)) &&
           ((Thermistor_LUT[last] - resT) > (resT - Thermistor_LUT[last + 1u])))
        {
            last++;
        }
        else if ((Thermistor_LUT[last] < resT) && (last > 0u) &&
                ((Thermistor_LUT[last - 1u] - resT) < (resT - Thermistor_LUT[last])))
        {
            last--;
        }
        else
        {
            /* Closest entry in the LUT already found */
        }

        tempTR = Thermistor_MIN_TEMP + (int16)((uint16)(last * Thermistor_ACCURACY));

    #endif /* (Thermistor_IMPLEMENTATION == Thermistor_EQUATION_METHOD) */

    return (tempTR);
}


/* [] END OF FILE */
