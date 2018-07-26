/*******************************************************************/
/*                                                                 */
/*                      ADOBE CONFIDENTIAL                         */
/*                   _ _ _ _ _ _ _ _ _ _ _ _ _                     */
/*                                                                 */
/* Copyright 2007 Adobe Systems Incorporated                       */
/* All Rights Reserved.                                            */
/*                                                                 */
/* NOTICE:  All information contained herein is, and remains the   */
/* property of Adobe Systems Incorporated and its suppliers, if    */
/* any.  The intellectual and technical concepts contained         */
/* herein are proprietary to Adobe Systems Incorporated and its    */
/* suppliers and may be covered by U.S. and Foreign Patents,       */
/* patents in process, and are protected by trade secret or        */
/* copyright law.  Dissemination of this information or            */
/* reproduction of this material is strictly forbidden unless      */
/* prior written permission is obtained from Adobe Systems         */
/* Incorporated.                                                   */
/*                                                                 */
/*******************************************************************/

/*
	Skeleton.h
*/

#pragma once

#ifndef SKELETON_H
#define SKELETON_H

typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned short		u_int16;
typedef unsigned long		u_long;
typedef short int			int16;
#define PF_TABLE_BITS	12
#define PF_TABLE_SZ_16	4096

#define PF_DEEP_COLOR_AWARE 1	// make sure we get 16bpc pixels; 
								// AE_Effect.h checks for this.

#include "AEConfig.h"

#ifdef AE_OS_WIN
	typedef unsigned short PixelType;
	#include <Windows.h>
#endif

#include "entry.h"
#include "AE_Effect.h"
#include "AE_EffectCB.h"
#include "AE_Macros.h"
#include "Param_Utils.h"
#include "AE_EffectCBSuites.h"
#include "String_Utils.h"
#include "AE_GeneralPlug.h"
#include "AEFX_ChannelDepthTpl.h"
#include "AEGP_SuiteHandler.h"

#include "Skeleton_Strings.h"

/* Versioning information */

#define	MAJOR_VERSION	1
#define	MINOR_VERSION	0
#define	BUG_VERSION		0
#define	STAGE_VERSION	PF_Stage_DEVELOP
#define	BUILD_VERSION	1


/* Parameter defaults */

#define	SKELETON_SEG_MIN		0
#define	SKELETON_SEG_MAX		25000
#define	SKELETON_SEG_DFLT		100

#define	SKELETON_LEN_MIN		1
#define	SKELETON_LEN_MAX		20
#define	SKELETON_LEN_DFLT		5

#define	SKELETON_RANG_MIN		0
#define	SKELETON_RANG_MAX		100
#define	SKELETON_RANG_DFLT		20

#define	SKELETON_STRAIT_MIN		5
#define	SKELETON_STRAIT_MAX		360
#define	SKELETON_STRAIT_DFLT	180

#define	SKELETON_DETECT_MIN		1
#define	SKELETON_DETECT_MAX		255
#define	SKELETON_DETECT_DFLT	100

#define	SKELETON_SPREAD_MIN		1
#define	SKELETON_SPREAD_MAX		100
#define	SKELETON_SPREAD_DFLT	20

#define	SKELETON_RAND_MIN		0
#define	SKELETON_RAND_MAX		1000
#define	SKELETON_RAND_DFLT		100

enum {
	SKELETON_INPUT = 0,
	SKELETON_SEG,
	SKELETON_TOPIC_GENERATOR_START,
	SKELETON_LEN,
	SKELETON_RANG,
	SKELETON_STRAIT,
	SKELETON_MODE,
	SKELETON_COLOR,
	SKELETON_TOPIC_GENERATOR_END,
	SKELETON_TOPIC_DETECTOR_START,
	SKELETON_SEARCH,
	SKELETON_DETECT,
	SKELETON_SPREAD,
	SKELETON_GRID,
	SKELETON_RAND,
	SKELETON_CHECK,
	SKELETON_TOPIC_DETECTOR_END,
	SKELETON_NUM_PARAMS
};

enum {
	SEG_DISK_ID = 1,
	LEN_DISK_ID,
	SKELETON_GENERATOR_START_ID,
	RANG_DISK_ID,
	STRAIT_DISK_ID,
	MODE_DISK_ID,
	COLOR_DISK_ID,
	SKELETON_GENERATOR_END_ID,
	SKELETON_DETECTOR_START_ID,
	SEARCH_DISK_ID,
	DETECT_DISK_ID,
	SPREAD_DISK_ID,
	GRID_DISK_ID,
	RAND_DISK_ID,
	CHECK_DISK_ID,
	SKELETON_DETECTOR_END_ID
};

typedef enum {
	MODE_LINES = 1,
	MODE_LINESLOOP,
	MODE_POLYGONS,
	MODE_LINES_POLYGONS,
	MODE_POINTS,
	MODE_SIZE = MODE_POINTS
} current_mode;

typedef struct GainInfo{
	PF_FpLong	gainF;
	PF_FpLong	randF;
} GainInfo, *GainInfoP, **GainInfoH;


extern "C" {

	DllExport
	PF_Err
	EffectMain(
		PF_Cmd			cmd,
		PF_InData		*in_data,
		PF_OutData		*out_data,
		PF_ParamDef		*params[],
		PF_LayerDef		*output,
		void			*extra);

}

#endif // SKELETON_H
