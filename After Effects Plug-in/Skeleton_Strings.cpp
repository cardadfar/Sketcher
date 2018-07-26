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

#include "Skeleton.h"

typedef struct {
	A_u_long	index;
	A_char		str[256];
} TableString;



TableString		g_strs[StrID_NUMTYPES] = {
	StrID_NONE,						"",
	StrID_Name,						"Sketcher",
	StrID_Description,				"A graphics rendering overlay\r that matches the source layer.",
    StrID_Topic_Generator,          "Generator",
    StrID_Topic_Detector,           "Detector",
	StrID_Seg_Param_Name,			"Segments",
    StrID_Len_Param_Name,           "Length",
    StrID_Rang_Param_Name,          "Range",
    StrID_Strait_Param_Name,        "Straightness",
    StrID_Mode_Param_Name,          "Drawing Mode",


    StrID_ModeChoices,              "Lines|"
                                    "Lines Loop|"
                                    "Polygons|"
                                    "Lines & Polygons|"
                                    "Points",

    StrID_Color_Param_Name,         "Line Color",
    StrID_Search_Param_Name,        "Color Detector",
    StrID_Detect_Param_Name,        "Detector Range",
    StrID_Spread_Param_Name,        "Spread",
    StrID_Grid_Param_Name,          "Gap Selection",
    StrID_Rand_Param_Name,          "Random Seed",
    StrID_Check_Param_Name,         "Subject Layer",
};


char	*GetStringPtr(int strNum)
{
	return g_strs[strNum].str;
}
	
