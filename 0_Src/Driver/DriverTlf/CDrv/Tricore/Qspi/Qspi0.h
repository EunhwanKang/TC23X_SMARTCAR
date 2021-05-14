/**
 * \file 
 * \brief QSPI0 include file
 *
 * This Driver manage the global initialisation of QSPI0.
 */
#ifndef _QSPI0_H
#define _QSPI0_H
/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include <Cpu/Std/Ifx_Types.h>
#include <Qspi/SpiMaster/IfxQspi_SpiMaster.h>

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/
/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

IfxQspi_SpiMaster *qspi0_init (void);

#endif /* _QSPI0_H */