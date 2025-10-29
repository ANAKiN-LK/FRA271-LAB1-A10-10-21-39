/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Encoder_reader_simulink.c
 *
 * Code generated for Simulink model 'Encoder_reader_simulink'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Fri Oct 24 20:17:56 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Encoder_reader_simulink.h"
#include "Encoder_reader_simulink_types.h"
#include "rtwtypes.h"
#include "stm_timer_ll.h"
#include "Encoder_reader_simulink_private.h"

/* Block signals (default storage) */
B_Encoder_reader_simulink_T Encoder_reader_simulink_B;

/* Block states (default storage) */
DW_Encoder_reader_simulink_T Encoder_reader_simulink_DW;

/* Real-time model */
static RT_MODEL_Encoder_reader_simul_T Encoder_reader_simulink_M_;
RT_MODEL_Encoder_reader_simul_T *const Encoder_reader_simulink_M =
  &Encoder_reader_simulink_M_;

/* Forward declaration for local functions */
static void Encoder_reader_SystemCore_setup(stm32cube_blocks_EncoderBlock_T *obj);
static void Encoder_reader_SystemCore_setup(stm32cube_blocks_EncoderBlock_T *obj)
{
  uint8_T ChannelInfo;
  TIM_Type_T b;
  boolean_T isSlaveModeTriggerEnabled;

  /* Start for MATLABSystem: '<Root>/TIM3_Encoder' */
  obj->isInitialized = 1;
  b.PeripheralPtr = TIM3;
  b.isCenterAlignedMode = false;

  /* Start for MATLABSystem: '<Root>/TIM3_Encoder' */
  b.repetitionCounter = 0U;
  obj->TimerHandle = Timer_Handle_Init(&b);
  enableTimerInterrupts(obj->TimerHandle, 0);
  ChannelInfo = ENABLE_CH;

  /* Start for MATLABSystem: '<Root>/TIM3_Encoder' */
  enableTimerChannel1(obj->TimerHandle, ChannelInfo);
  enableTimerChannel2(obj->TimerHandle, ChannelInfo);
  isSlaveModeTriggerEnabled = isSlaveTriggerModeEnabled(obj->TimerHandle);
  if (!isSlaveModeTriggerEnabled) {
    /* Start for MATLABSystem: '<Root>/TIM3_Encoder' */
    enableCounter(obj->TimerHandle, false);
  }

  obj->isSetupComplete = true;
}

/* Model step function */
void Encoder_reader_simulink_step(void)
{
  {
    real_T diff;
    real_T lastTime;
    real_T *lastU;
    uint32_T timerCounts;

    /* MATLABSystem: '<Root>/TIM3_Encoder' */
    timerCounts = getTimerCounterValueForG4
      (Encoder_reader_simulink_DW.obj.TimerHandle, false, NULL);

    /* MATLAB Function: '<Root>/WrapAround' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion1'
     *  MATLABSystem: '<Root>/TIM3_Encoder'
     */
    if (!Encoder_reader_simulink_DW.prev_not_empty) {
      Encoder_reader_simulink_DW.prev = timerCounts;
      Encoder_reader_simulink_DW.prev_not_empty = true;
    }

    diff = (real_T)timerCounts - Encoder_reader_simulink_DW.prev;
    if (diff > 30720.0) {
      diff -= 61440.0;
    } else if (diff < -30720.0) {
      diff += 61440.0;
    }

    Encoder_reader_simulink_DW.prev += diff;

    /* End of MATLAB Function: '<Root>/WrapAround' */

    /* Gain: '<Root>/Count2Rad' */
    Encoder_reader_simulink_B.Count2Rad = 0.00010226538585904274 *
      Encoder_reader_simulink_DW.prev;

    /* Derivative: '<Root>/A' incorporates:
     *  Derivative: '<Root>/B'
     *  Derivative: '<Root>/F'
     *  Derivative: '<Root>/T'
     */
    diff = Encoder_reader_simulink_M->Timing.t[0];
    if ((Encoder_reader_simulink_DW.TimeStampA >= diff) &&
        (Encoder_reader_simulink_DW.TimeStampB >= diff)) {
      /* Derivative: '<Root>/A' */
      Encoder_reader_simulink_B.A = 0.0;
    } else {
      lastTime = Encoder_reader_simulink_DW.TimeStampA;
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA;
      if (Encoder_reader_simulink_DW.TimeStampA <
          Encoder_reader_simulink_DW.TimeStampB) {
        if (Encoder_reader_simulink_DW.TimeStampB < diff) {
          lastTime = Encoder_reader_simulink_DW.TimeStampB;
          lastU = &Encoder_reader_simulink_DW.LastUAtTimeB;
        }
      } else if (Encoder_reader_simulink_DW.TimeStampA >= diff) {
        lastTime = Encoder_reader_simulink_DW.TimeStampB;
        lastU = &Encoder_reader_simulink_DW.LastUAtTimeB;
      }

      /* Derivative: '<Root>/A' */
      Encoder_reader_simulink_B.A = (Encoder_reader_simulink_B.Count2Rad -
        *lastU) / (diff - lastTime);
    }

    /* End of Derivative: '<Root>/A' */
    /* Derivative: '<Root>/F' */
    if ((Encoder_reader_simulink_DW.TimeStampA_p >= diff) &&
        (Encoder_reader_simulink_DW.TimeStampB_n >= diff)) {
      /* Derivative: '<Root>/F' */
      Encoder_reader_simulink_B.F = 0.0;
    } else {
      lastTime = Encoder_reader_simulink_DW.TimeStampA_p;
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA_g;
      if (Encoder_reader_simulink_DW.TimeStampA_p <
          Encoder_reader_simulink_DW.TimeStampB_n) {
        if (Encoder_reader_simulink_DW.TimeStampB_n < diff) {
          lastTime = Encoder_reader_simulink_DW.TimeStampB_n;
          lastU = &Encoder_reader_simulink_DW.LastUAtTimeB_c;
        }
      } else if (Encoder_reader_simulink_DW.TimeStampA_p >= diff) {
        lastTime = Encoder_reader_simulink_DW.TimeStampB_n;
        lastU = &Encoder_reader_simulink_DW.LastUAtTimeB_c;
      }

      /* Derivative: '<Root>/F' */
      Encoder_reader_simulink_B.F = (Encoder_reader_simulink_B.A - *lastU) /
        (diff - lastTime);
    }

    /* Gain: '<Root>/Count2Deg' */
    Encoder_reader_simulink_B.Count2Deg = 0.005859375 *
      Encoder_reader_simulink_DW.prev;

    /* Derivative: '<Root>/B' */
    if ((Encoder_reader_simulink_DW.TimeStampA_h >= diff) &&
        (Encoder_reader_simulink_DW.TimeStampB_b >= diff)) {
      /* Derivative: '<Root>/B' */
      Encoder_reader_simulink_B.B = 0.0;
    } else {
      lastTime = Encoder_reader_simulink_DW.TimeStampA_h;
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA_b;
      if (Encoder_reader_simulink_DW.TimeStampA_h <
          Encoder_reader_simulink_DW.TimeStampB_b) {
        if (Encoder_reader_simulink_DW.TimeStampB_b < diff) {
          lastTime = Encoder_reader_simulink_DW.TimeStampB_b;
          lastU = &Encoder_reader_simulink_DW.LastUAtTimeB_d;
        }
      } else if (Encoder_reader_simulink_DW.TimeStampA_h >= diff) {
        lastTime = Encoder_reader_simulink_DW.TimeStampB_b;
        lastU = &Encoder_reader_simulink_DW.LastUAtTimeB_d;
      }

      /* Derivative: '<Root>/B' */
      Encoder_reader_simulink_B.B = (Encoder_reader_simulink_B.Count2Deg -
        *lastU) / (diff - lastTime);
    }

    /* Derivative: '<Root>/T' */
    if ((Encoder_reader_simulink_DW.TimeStampA_b >= diff) &&
        (Encoder_reader_simulink_DW.TimeStampB_bt >= diff)) {
      /* Derivative: '<Root>/T' */
      Encoder_reader_simulink_B.T = 0.0;
    } else {
      lastTime = Encoder_reader_simulink_DW.TimeStampA_b;
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA_d;
      if (Encoder_reader_simulink_DW.TimeStampA_b <
          Encoder_reader_simulink_DW.TimeStampB_bt) {
        if (Encoder_reader_simulink_DW.TimeStampB_bt < diff) {
          lastTime = Encoder_reader_simulink_DW.TimeStampB_bt;
          lastU = &Encoder_reader_simulink_DW.LastUAtTimeB_l;
        }
      } else if (Encoder_reader_simulink_DW.TimeStampA_b >= diff) {
        lastTime = Encoder_reader_simulink_DW.TimeStampB_bt;
        lastU = &Encoder_reader_simulink_DW.LastUAtTimeB_l;
      }

      /* Derivative: '<Root>/T' */
      Encoder_reader_simulink_B.T = (Encoder_reader_simulink_B.B - *lastU) /
        (diff - lastTime);
    }
  }

  {
    real_T *lastU;

    /* Update for Derivative: '<Root>/A' */
    if (Encoder_reader_simulink_DW.TimeStampA == (rtInf)) {
      Encoder_reader_simulink_DW.TimeStampA =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA;
    } else if (Encoder_reader_simulink_DW.TimeStampB == (rtInf)) {
      Encoder_reader_simulink_DW.TimeStampB =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeB;
    } else if (Encoder_reader_simulink_DW.TimeStampA <
               Encoder_reader_simulink_DW.TimeStampB) {
      Encoder_reader_simulink_DW.TimeStampA =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA;
    } else {
      Encoder_reader_simulink_DW.TimeStampB =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeB;
    }

    *lastU = Encoder_reader_simulink_B.Count2Rad;

    /* End of Update for Derivative: '<Root>/A' */

    /* Update for Derivative: '<Root>/F' */
    if (Encoder_reader_simulink_DW.TimeStampA_p == (rtInf)) {
      Encoder_reader_simulink_DW.TimeStampA_p =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA_g;
    } else if (Encoder_reader_simulink_DW.TimeStampB_n == (rtInf)) {
      Encoder_reader_simulink_DW.TimeStampB_n =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeB_c;
    } else if (Encoder_reader_simulink_DW.TimeStampA_p <
               Encoder_reader_simulink_DW.TimeStampB_n) {
      Encoder_reader_simulink_DW.TimeStampA_p =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA_g;
    } else {
      Encoder_reader_simulink_DW.TimeStampB_n =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeB_c;
    }

    *lastU = Encoder_reader_simulink_B.A;

    /* End of Update for Derivative: '<Root>/F' */

    /* Update for Derivative: '<Root>/B' */
    if (Encoder_reader_simulink_DW.TimeStampA_h == (rtInf)) {
      Encoder_reader_simulink_DW.TimeStampA_h =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA_b;
    } else if (Encoder_reader_simulink_DW.TimeStampB_b == (rtInf)) {
      Encoder_reader_simulink_DW.TimeStampB_b =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeB_d;
    } else if (Encoder_reader_simulink_DW.TimeStampA_h <
               Encoder_reader_simulink_DW.TimeStampB_b) {
      Encoder_reader_simulink_DW.TimeStampA_h =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA_b;
    } else {
      Encoder_reader_simulink_DW.TimeStampB_b =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeB_d;
    }

    *lastU = Encoder_reader_simulink_B.Count2Deg;

    /* End of Update for Derivative: '<Root>/B' */

    /* Update for Derivative: '<Root>/T' */
    if (Encoder_reader_simulink_DW.TimeStampA_b == (rtInf)) {
      Encoder_reader_simulink_DW.TimeStampA_b =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA_d;
    } else if (Encoder_reader_simulink_DW.TimeStampB_bt == (rtInf)) {
      Encoder_reader_simulink_DW.TimeStampB_bt =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeB_l;
    } else if (Encoder_reader_simulink_DW.TimeStampA_b <
               Encoder_reader_simulink_DW.TimeStampB_bt) {
      Encoder_reader_simulink_DW.TimeStampA_b =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA_d;
    } else {
      Encoder_reader_simulink_DW.TimeStampB_bt =
        Encoder_reader_simulink_M->Timing.t[0];
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeB_l;
    }

    *lastU = Encoder_reader_simulink_B.B;

    /* End of Update for Derivative: '<Root>/T' */
  }

  {                                    /* Sample time: [0.001s, 0.0s] */
    extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
    extmodeSimulationTime_T extmodeTime = (extmodeSimulationTime_T)
      ((Encoder_reader_simulink_M->Timing.clockTick1) * 0.001);

    /* Trigger External Mode event */
    errorCode = extmodeEvent(1, extmodeTime);
    if (errorCode != EXTMODE_SUCCESS) {
      /* Code to handle External Mode event errors
         may be added here */
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  Encoder_reader_simulink_M->Timing.t[0] =
    ((time_T)(++Encoder_reader_simulink_M->Timing.clockTick0)) *
    Encoder_reader_simulink_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    Encoder_reader_simulink_M->Timing.clockTick1++;
  }
}

/* Model initialize function */
void Encoder_reader_simulink_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Encoder_reader_simulink_M->solverInfo,
                          &Encoder_reader_simulink_M->Timing.simTimeStep);
    rtsiSetTPtr(&Encoder_reader_simulink_M->solverInfo, &rtmGetTPtr
                (Encoder_reader_simulink_M));
    rtsiSetStepSizePtr(&Encoder_reader_simulink_M->solverInfo,
                       &Encoder_reader_simulink_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&Encoder_reader_simulink_M->solverInfo,
                          (&rtmGetErrorStatus(Encoder_reader_simulink_M)));
    rtsiSetRTModelPtr(&Encoder_reader_simulink_M->solverInfo,
                      Encoder_reader_simulink_M);
  }

  rtsiSetSimTimeStep(&Encoder_reader_simulink_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&Encoder_reader_simulink_M->solverInfo,
    false);
  rtsiSetIsContModeFrozen(&Encoder_reader_simulink_M->solverInfo, false);
  rtsiSetSolverName(&Encoder_reader_simulink_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(Encoder_reader_simulink_M,
             &Encoder_reader_simulink_M->Timing.tArray[0]);
  rtmSetTFinal(Encoder_reader_simulink_M, -1);
  Encoder_reader_simulink_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  Encoder_reader_simulink_M->Sizes.checksums[0] = (2332799726U);
  Encoder_reader_simulink_M->Sizes.checksums[1] = (1867321275U);
  Encoder_reader_simulink_M->Sizes.checksums[2] = (260333997U);
  Encoder_reader_simulink_M->Sizes.checksums[3] = (4241757102U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[3];
    Encoder_reader_simulink_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Encoder_reader_simulink_M->extModeInfo,
      &Encoder_reader_simulink_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Encoder_reader_simulink_M->extModeInfo,
                        Encoder_reader_simulink_M->Sizes.checksums);
    rteiSetTPtr(Encoder_reader_simulink_M->extModeInfo, rtmGetTPtr
                (Encoder_reader_simulink_M));
  }

  /* InitializeConditions for Derivative: '<Root>/A' */
  Encoder_reader_simulink_DW.TimeStampA = (rtInf);
  Encoder_reader_simulink_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Derivative: '<Root>/F' */
  Encoder_reader_simulink_DW.TimeStampA_p = (rtInf);
  Encoder_reader_simulink_DW.TimeStampB_n = (rtInf);

  /* InitializeConditions for Derivative: '<Root>/B' */
  Encoder_reader_simulink_DW.TimeStampA_h = (rtInf);
  Encoder_reader_simulink_DW.TimeStampB_b = (rtInf);

  /* InitializeConditions for Derivative: '<Root>/T' */
  Encoder_reader_simulink_DW.TimeStampA_b = (rtInf);
  Encoder_reader_simulink_DW.TimeStampB_bt = (rtInf);

  /* Start for MATLABSystem: '<Root>/TIM3_Encoder' */
  Encoder_reader_simulink_DW.obj.isInitialized = 0;
  Encoder_reader_simulink_DW.obj.matlabCodegenIsDeleted = false;
  Encoder_reader_SystemCore_setup(&Encoder_reader_simulink_DW.obj);
}

/* Model terminate function */
void Encoder_reader_simulink_terminate(void)
{
  uint8_T ChannelInfo;

  /* Terminate for MATLABSystem: '<Root>/TIM3_Encoder' */
  if (!Encoder_reader_simulink_DW.obj.matlabCodegenIsDeleted) {
    Encoder_reader_simulink_DW.obj.matlabCodegenIsDeleted = true;
    if ((Encoder_reader_simulink_DW.obj.isInitialized == 1) &&
        Encoder_reader_simulink_DW.obj.isSetupComplete) {
      disableCounter(Encoder_reader_simulink_DW.obj.TimerHandle);
      disableTimerInterrupts(Encoder_reader_simulink_DW.obj.TimerHandle, 0);
      ChannelInfo = ENABLE_CH;
      disableTimerChannel1(Encoder_reader_simulink_DW.obj.TimerHandle,
                           ChannelInfo);
      disableTimerChannel2(Encoder_reader_simulink_DW.obj.TimerHandle,
                           ChannelInfo);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/TIM3_Encoder' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
