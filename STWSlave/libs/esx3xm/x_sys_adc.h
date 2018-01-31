//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_sys_adc.h
   \brief      defines for ESX3XM ADC channels

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     08.09.2009  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_SYS_ADC_H
#define _X_SYS_ADC_H


#ifdef __cplusplus
extern "C" {
#endif

//MISRA 2217: Allow more than 120 characters for better readability
//MISRA  857: Allow more than 1024 macro definitions
//PRQA S 2217, 857 ++

/* -- Defines ------------------------------------------------------------- */

#define X_ADC_CH_MAX             (113U)            // max. number of external ADC channels


// analog channels for ESX3XM:

// ADC0 group A: ADC0_0..ADC0_7, ADC0_24..ADC0_31 MUX position 0
#define X_ADC_I_PWM1             (0U)              // analog input channel current PWM_MUT1
#define X_ADC_I_PWM2             (1U)              // analog input channel current PWM_MUT2
#define X_ADC_I_PWM3             (2U)              // analog input channel current PWM_MUT3
#define X_ADC_I_PWM4             (3U)              // analog input channel current PWM_MUT4
#define X_ADC_I_PWM5             (4U)              // analog input channel current PWM_MUT5
#define X_ADC_I_PWM6             (5U)              // analog input channel current PWM_MUT6
#define X_ADC_I_PWM7             (6U)              // analog input channel current PWM_MUT7
#define X_ADC_I_PWM8             (7U)              // analog input channel current PWM_MUT8
#define X_ADC_EXPBOARD_A_AN4     (8U)              // analog input channel exp. board A analog 4
#define X_ADC_EXPBOARD_A_AN5     (9U)              // analog input channel exp. board A analog 5
#define X_ADC_EXPBOARD_A_AN6     (10U)             // analog input channel exp. board A analog 6
#define X_ADC_EXPBOARD_A_AN7     (11U)             // analog input channel exp. board A analog 7
#define X_ADC_EXPBOARD_A_AN8     (12U)             // analog input channel exp. board A analog 8
#define X_ADC_EXPBOARD_A_AN9     (13U)             // analog input channel exp. board A analog 9
#define X_ADC_2V56               (14U)             // analog input channel test voltage 2.56V
#define X_ADC_3V02_A             (15U)             // analog input channel test voltage 3.02V

// ADC0 group B: ADC0_16..ADC0_23, ADC0_24..ADC0_31 MUX position 1
#define X_ADC_I_DOUT9            (16U)             // analog input channel current feedback OUT9
#define X_ADC_I_DOUT10           (17U)             // analog input channel current feedback OUT10
#define X_ADC_I_DOUT11           (18U)             // analog input channel current feedback OUT11
#define X_ADC_I_DOUT12           (19U)             // analog input channel current feedback OUT12
#define X_ADC_U_DOUT9            (20U)             // analog input channel voltage feedback OUT9
#define X_ADC_U_DOUT10           (21U)             // analog input channel voltage feedback OUT10
#define X_ADC_U_DOUT11           (22U)             // analog input channel voltage feedback OUT11
#define X_ADC_U_DOUT12           (23U)             // analog input channel voltage feedback OUT12
#define X_ADC_EXPBOARD_B_AN4     (24U)             // analog input channel exp. board B analog 4
#define X_ADC_EXPBOARD_B_AN5     (25U)             // analog input channel exp. board B analog 5
#define X_ADC_EXPBOARD_B_AN6     (26U)             // analog input channel exp. board B analog 6
#define X_ADC_EXPBOARD_B_AN7     (27U)             // analog input channel exp. board B analog 7
#define X_ADC_1V50_A             (28U)             // analog input channel test voltage 1.50V
#define X_ADC_0V97_A             (29U)             // analog input channel test voltage 0.97V
#define X_ADC_EXPBOARD_A_AN10    (30U)             // analog input channel exp. board A analog 10
#define X_ADC_EXPBOARD_A_AN11    (31U)             // analog input channel exp. board A analog 11

// ADC0 group A: ADC0_0..ADC0_7, ADC0_24..ADC0_31 MUX position 2
#define X_ADC_I_PWM1_B           (32U)             // analog input channel current PWM_MUT1
#define X_ADC_I_PWM2_B           (33U)             // analog input channel current PWM_MUT2
#define X_ADC_I_PWM3_B           (34U)             // analog input channel current PWM_MUT3
#define X_ADC_I_PWM4_B           (35U)             // analog input channel current PWM_MUT4
#define X_ADC_I_PWM5_B           (36U)             // analog input channel current PWM_MUT5
#define X_ADC_I_PWM6_B           (37U)             // analog input channel current PWM_MUT6
#define X_ADC_I_PWM7_B           (38U)             // analog input channel current PWM_MUT7
#define X_ADC_I_PWM8_B           (39U)             // analog input channel current PWM_MUT8
#define X_ADC_EXPBOARD_C_AN4     (40U)             // analog input channel exp. board C analog 4
#define X_ADC_EXPBOARD_C_AN5     (41U)             // analog input channel exp. board C analog 5
#define X_ADC_1V65_A             (42U)             // analog input channel test voltage 1.65V
#define X_ADC_2V14_A             (43U)             // analog input channel test voltage 2.14V
#define X_ADC_EXPBOARD_B_AN8     (44U)             // analog input channel exp. board B analog 8
#define X_ADC_EXPBOARD_B_AN9     (45U)             // analog input channel exp. board B analog 9
#define X_ADC_EXPBOARD_B_AN10    (46U)             // analog input channel exp. board B analog 10
#define X_ADC_EXPBOARD_B_AN11    (47U)             // analog input channel exp. board B analog 11

// ADC0 group B: ADC0_16..ADC0_23, ADC0_24..ADC0_31 MUX position 3
#define X_ADC_I_DOUT9_B          (48U)             // analog input channel current feedback OUT9
#define X_ADC_I_DOUT10_B         (49U)             // analog input channel current feedback OUT10
#define X_ADC_I_DOUT11_B         (50U)             // analog input channel current feedback OUT11
#define X_ADC_I_DOUT12_B         (51U)             // analog input channel current feedback OUT12
#define X_ADC_U_DOUT9_B          (52U)             // analog input channel voltage feedback OUT9
#define X_ADC_U_DOUT10_B         (53U)             // analog input channel voltage feedback OUT10
#define X_ADC_U_DOUT11_B         (54U)             // analog input channel voltage feedback OUT11
#define X_ADC_U_DOUT12_B         (55U)             // analog input channel voltage feedback OUT12
#define X_ADC_2V05               (56U)             // analog input channel test voltage 2.05V (4.1Vref option)
#define X_ADC_MIN                (57U)             // analog input channel test voltage 0.00V
#define X_ADC_EXPBOARD_C_AN6     (58U)             // analog input channel exp. board C analog 6
#define X_ADC_EXPBOARD_C_AN7     (59U)             // analog input channel exp. board C analog 7
#define X_ADC_EXPBOARD_C_AN8     (60U)             // analog input channel exp. board C analog 8
#define X_ADC_EXPBOARD_C_AN9     (61U)             // analog input channel exp. board C analog 9
#define X_ADC_EXPBOARD_C_AN10    (62U)             // analog input channel exp. board C analog 10
#define X_ADC_EXPBOARD_C_AN11    (63U)             // analog input channel exp. board C analog 11

// ADC1 group A: ADC1_4..ADC1_15 MUX position 0
#define X_ADC_0V97_B             (64U)             // analog input channel test voltage 0.97V
#define X_ADC_AIN5               (65U)             // analog input channel AIN5
#define X_ADC_AIN4               (66U)             // analog input channel AIN4
#define X_ADC_AIN9               (67U)             // analog input channel AIN9
#define X_ADC_EXPBOARD_A_AN0     (68U)             // analog input channel exp. board A analog 0
#define X_ADC_AIN8               (69U)             // analog input channel AIN8
#define X_ADC_EXPBOARD_A_AN2     (70U)             // analog input channel exp. board A analog 2
#define X_ADC_EXPBOARD_A_AN1     (71U)             // analog input channel exp. board A analog 1
#define X_ADC_1V90               (72U)             // analog input channel test voltage 1.90V
#define X_ADC_AIN13              (73U)             // analog input channel AIN13
#define X_ADC_AIN12              (74U)             // analog input channel AIN12
#define X_ADC_1V25               (75U)             // analog input channel test voltage 1.25V

// ADC1 group A: ADC1_4..ADC1_15 MUX position 1
#define X_ADC_AIN1               (76U)             // analog input channel AIN1
#define X_ADC_0V55               (77U)             // analog input channel test voltage 0.55V
#define X_ADC_UE                 (78U)             // analog input channel power supply +UE
#define X_ADC_AIN10              (79U)             // analog input channel AIN10
#define X_ADC_EXPBOARD_B_AN0     (80U)             // analog input channel exp. board B analog 0
#define X_ADC_I_UB1              (81U)             // analog input channel current on UB1 pin
#define X_ADC_2V14_B             (82U)             // analog input channel test voltage 2.14V
#define X_ADC_EXPBOARD_B_AN1     (83U)             // analog input channel exp. board B analog 1
#define X_ADC_EXPBOARD_A_AN3     (84U)             // analog input channel exp. board A analog 3
#define X_ADC_AIN14              (85U)             // analog input channel AIN14
#define X_ADC_1V65_B             (86U)             // analog input channel test voltage 1.65V
#define X_ADC_TEMP_BOARD         (87U)             // analog input channel board temperature

// ADC1 group A: ADC1_4..ADC1_15 MUX position 2
#define X_ADC_AIN2               (88U)             // analog input channel AIN2
#define X_ADC_AIN6               (89U)             // analog input channel AIN6
#define X_ADC_U_EXT1             (90U)             // analog input channel voltage ext1
#define X_ADC_1V50_B             (91U)             // analog input channel test voltage 1.50V
#define X_ADC_EXPBOARD_C_AN0     (92U)             // analog input channel exp. board C analog 0
#define X_ADC_0V25               (93U)             // analog input channel test voltage 0.25V
#define X_ADC_EXPBOARD_B_AN2     (94U)             // analog input channel exp. board B analog 2
#define X_ADC_2V50               (95U)             // analog input channel test voltage 2.50V
#define X_ADC_EXPBOARD_B_AN3     (96U)             // analog input channel exp. board B analog 3
#define X_ADC_AIN15              (97U)             // analog input channel AIN15
#define X_ADC_U_UB1              (98U)             // analog input channel voltage on UB1 pin
#define X_ADC_U_UC1              (99U)             // analog input channel voltage on UB1 power stage (after safety switch)

// ADC1 group A: ADC1_4..ADC1_15 MUX position 3
#define X_ADC_AIN3               (100U)            // analog input channel AIN3
#define X_ADC_AIN7               (101U)            // analog input channel AIN7
#define X_ADC_0V82               (102U)            // analog input channel test voltage 0.82V
#define X_ADC_AIN11              (103U)            // analog input channel AIN11
#define X_ADC_3V02_B             (104U)            // analog input channel test voltage 3.02V
#define X_ADC_EXPBOARD_A_AN12    (105U)            // analog input channel exp. board B analog 12
#define X_ADC_EXPBOARD_C_AN2     (106U)            // analog input channel exp. board C analog 2
#define X_ADC_EXPBOARD_C_AN1     (107U)            // analog input channel exp. board C analog 1
#define X_ADC_EXPBOARD_C_AN3     (108U)            // analog input channel exp. board C analog 3
#define X_ADC_0V06               (109U)            // analog input channel test voltage 0.06V
#define X_ADC_EXPBOARD_B_AN12    (110U)            // analog input channel exp. board A analog 12
#define X_ADC_EXPBOARD_C_AN12    (111U)            // analog input channel exp. board C analog 12

#define X_ADC_TEMP_CPU           (112U)            // analog input channel CPU temperature


// system voltage ADC channels
#define X_ADC_12V                X_ADC_1V90        // analog channel for 12Vana system voltage
#define X_ADC_6V0_A              X_ADC_3V02_A      // analog channel for 6Vlim system voltage
#define X_ADC_6V0_B              X_ADC_3V02_B      // analog channel for 6Vlim system voltage
#define X_ADC_5V0                X_ADC_2V50        // analog channel for 5V system voltage
#define X_ADC_5VANA_A            X_ADC_2V14_A      // analog channel for 5.0Vana system voltage
#define X_ADC_5VANA_B            X_ADC_2V14_B      // analog channel for 5.0Vana system voltage
#define X_ADC_3V5                X_ADC_0V55        // analog channel for 3.5Vana system voltage
#define X_ADC_UEBU               X_ADC_1V65_A      // analog channel for 3.3V EBU supply voltage
#define X_ADC_3V3                X_ADC_1V65_B      // analog channel for 3.3V supply voltage
#define X_ADC_USSV_A             X_ADC_0V97_A      // analog channel for 3.3Vssv supply voltage
#define X_ADC_USSV_B             X_ADC_0V97_B      // analog channel for 3.3Vssv supply voltage
#define X_ADC_UAREF              X_ADC_0V25        // analog channel for 3.3Varef system voltage
#define X_ADC_UDREF              X_ADC_0V82        // analog channel for 3.3Vdref system voltage


#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_SYS_ADC_H */
