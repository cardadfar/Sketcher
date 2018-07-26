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

#pragma once

typedef enum {
	StrID_NONE, 
	StrID_Name,
	StrID_Description,
    StrID_Topic_Generator,
    StrID_Topic_Detector,
	StrID_Seg_Param_Name,
	StrID_Len_Param_Name,
    StrID_Rang_Param_Name,
    StrID_Strait_Param_Name,
    StrID_Mode_Param_Name,

    StrID_ModeChoices,

    StrID_Color_Param_Name,
    StrID_Search_Param_Name,
    StrID_Detect_Param_Name,
    StrID_Spread_Param_Name,
    StrID_Grid_Param_Name,
    StrID_Rand_Param_Name,
    StrID_Check_Param_Name,
	StrID_NUMTYPES
} StrIDType;
