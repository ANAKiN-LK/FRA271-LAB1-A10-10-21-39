/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Encoder_reader_simulink.c
 *
 * Code generated for Simulink model 'Encoder_reader_simulink'.
 *
 * Model version                  : 2.6
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Thu Oct 30 02:16:29 2025
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
    real_T pos_out;
    real_T *lastU;
    uint32_T pinReadLoc;
    uint32_T timerCounts;

    /* MATLABSystem: '<Root>/TIM3_Encoder' */
    timerCounts = getTimerCounterValueForG4
      (Encoder_reader_simulink_DW.obj_p.TimerHandle, false, NULL);

    /* MATLABSystem: '<S5>/Digital Port Read' */
    pinReadLoc = LL_GPIO_ReadInputPort(GPIOC);

    /* MATLAB Function: '<Root>/WrapAround1' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion1'
     *  MATLABSystem: '<Root>/TIM3_Encoder'
     *  MATLABSystem: '<S5>/Digital Port Read'
     * */
    if ((pinReadLoc & 8192U) != 0U) {
      Encoder_reader_simulink_DW.offset = timerCounts;
    }

    pos_out = (real_T)timerCounts - Encoder_reader_simulink_DW.offset;

    /* End of MATLAB Function: '<Root>/WrapAround1' */

    /* MATLAB Function: '<Root>/WrapAround' */
    if (!Encoder_reader_simulink_DW.prev_not_empty) {
      Encoder_reader_simulink_DW.prev = pos_out;
      Encoder_reader_simulink_DW.prev_not_empty = true;
      Encoder_reader_simulink_DW.acc = pos_out;
    }

    diff = pos_out - Encoder_reader_simulink_DW.prev;
    if (diff > 30720.0) {
      diff -= 61440.0;
    } else if (diff < -30720.0) {
      diff += 61440.0;
    }

    Encoder_reader_simulink_DW.acc += diff;
    Encoder_reader_simulink_B.y = Encoder_reader_simulink_DW.acc;
    Encoder_reader_simulink_DW.prev = pos_out;

    /* End of MATLAB Function: '<Root>/WrapAround' */

    /* Gain: '<Root>/Gain' incorporates:
     *  Gain: '<Root>/Gain1'
     */
    Encoder_reader_simulink_B.RAd = 0.26179938779914941 *
      Encoder_reader_simulink_B.y;

    /* Derivative: '<Root>/Derivative1' */
    pos_out = Encoder_reader_simulink_M->Timing.t[0];
    if ((Encoder_reader_simulink_DW.TimeStampA >= pos_out) &&
        (Encoder_reader_simulink_DW.TimeStampB >= pos_out)) {
      /* Derivative: '<Root>/Derivative1' */
      Encoder_reader_simulink_B.AngularVelocityrads = 0.0;
    } else {
      diff = Encoder_reader_simulink_DW.TimeStampA;
      lastU = &Encoder_reader_simulink_DW.LastUAtTimeA;
      if (Encoder_reader_simulink_DW.TimeStampA <
          Encoder_reader_simulink_DW.TimeStampB) {
        if (Encoder_reader_simulink_DW.TimeStampB < pos_out) {
          diff = Encoder_reader_simulink_DW.TimeStampB;
          lastU = &Encoder_reader_simulink_DW.LastUAtTimeB;
        }
      } else if (Encoder_reader_simulink_DW.TimeStampA >= pos_out) {
        diff = Encoder_reader_simulink_DW.TimeStampB;
        lastU = &Encoder_reader_simulink_DW.LastUAtTimeB;
      }

      /* Derivative: '<Root>/Derivative1' */
      Encoder_reader_simulink_B.AngularVelocityrads =
        (Encoder_reader_simulink_B.RAd - *lastU) / (pos_out - diff);
    }

    /* End of Derivative: '<Root>/Derivative1' */
    /* Gain: '<Root>/Gain1' */
    Encoder_reader_simulink_B.AngularPositionRadians =
      Encoder_reader_simulink_B.RAd;
  }

  {
    real_T *lastU;

    /* Update for Derivative: '<Root>/Derivative1' */
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

    *lastU = Encoder_reader_simulink_B.RAd;

    /* End of Update for Derivative: '<Root>/Derivative1' */
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
  Encoder_reader_simulink_M->Sizes.checksums[0] = (1156101041U);
  Encoder_reader_simulink_M->Sizes.checksums[1] = (975767780U);
  Encoder_reader_simulink_M->Sizes.checksums[2] = (509850451U);
  Encoder_reader_simulink_M->Sizes.checksums[3] = (780605551U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[5];
    Encoder_reader_simulink_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Encoder_reader_simulink_M->extModeInfo,
      &Encoder_reader_simulink_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Encoder_reader_simulink_M->extModeInfo,
                        Encoder_reader_simulink_M->Sizes.checksums);
    rteiSetTPtr(Encoder_reader_simulink_M->extModeInfo, rtmGetTPtr
                (Encoder_reader_simulink_M));
  }

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  Encoder_reader_simulink_DW.TimeStampA = (rtInf);
  Encoder_reader_simulink_DW.TimeStampB = (rtInf);

  /* Start for MATLABSystem: '<Root>/TIM3_Encoder' */
  Encoder_reader_simulink_DW.obj_p.isInitialized = 0;
  Encoder_reader_simulink_DW.obj_p.matlabCodegenIsDeleted = false;
  Encoder_reader_SystemCore_setup(&Encoder_reader_simulink_DW.obj_p);

  /* Start for MATLABSystem: '<S5>/Digital Port Read' */
  Encoder_reader_simulink_DW.obj.matlabCodegenIsDeleted = false;
  Encoder_reader_simulink_DW.obj.isInitialized = 1;
  Encoder_reader_simulink_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void Encoder_reader_simulink_terminate(void)
{
  uint8_T ChannelInfo;

  /* Terminate for MATLABSystem: '<Root>/TIM3_Encoder' */
  if (!Encoder_reader_simulink_DW.obj_p.matlabCodegenIsDeleted) {
    Encoder_reader_simulink_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((Encoder_reader_simulink_DW.obj_p.isInitialized == 1) &&
        Encoder_reader_simulink_DW.obj_p.isSetupComplete) {
      disableCounter(Encoder_reader_simulink_DW.obj_p.TimerHandle);
      disableTimerInterrupts(Encoder_reader_simulink_DW.obj_p.TimerHandle, 0);
      ChannelInfo = ENABLE_CH;
      disableTimerChannel1(Encoder_reader_simulink_DW.obj_p.TimerHandle,
                           ChannelInfo);
      disableTimerChannel2(Encoder_reader_simulink_DW.obj_p.TimerHandle,
                           ChannelInfo);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/TIM3_Encoder' */

  /* Terminate for MATLABSystem: '<S5>/Digital Port Read' */
  if (!Encoder_reader_simulink_DW.obj.matlabCodegenIsDeleted) {
    Encoder_reader_simulink_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S5>/Digital Port Read' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
