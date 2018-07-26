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

/*	Skeleton.cpp	

	This is a compiling husk of a project. Fill it in with interesting
	pixel processing code.
	
	Revision History

	Version		Change													Engineer	Date
	=======		======													========	======
	1.0			(seemed like a good idea at the time)					bbb			6/1/2002

	1.0			Okay, I'm leaving the version at 1.0,					bbb			2/15/2006
				for obvious reasons; you're going to 
				copy these files directly! This is the
				first XCode version, though.

	1.0			Let's simplify this barebones sample					zal			11/11/2010

	1.0			Added new entry point									zal			9/18/2017

*/

#include "Skeleton.h"
#include <assert.h>
#include <windows.h>
#include <glew.h>
#include <glut.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "Skeleton_Helper.h"
#include "Skeleton_Helper.cpp"






class Vertex
{
public:
  // Construction
  Vertex() : x_(0), y_(0) {}
  Vertex(float x,float y) : x_(x), y_(y) {}

  // Getters
  float getX() const {return x_;}
  float getY() const {return y_;}

  float Xcord(float wth) {return ( (x_ / (wth/2)) - 1.0f);}
  float Ycord(float hgt) {return ( (y_ / (hgt/2)) - 1.0f);}

  // Setters
  void setX(float val) {x_ = val;}
  void setY(float val) {y_ = val;}
private:
  float x_;
  float y_;
};




static PF_Err 
About (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	
	suites.ANSICallbacksSuite1()->sprintf(	out_data->return_msg,
											"%s v%d.%d\r%s",
											STR(StrID_Name), 
											MAJOR_VERSION, 
											MINOR_VERSION, 
											STR(StrID_Description));
	return PF_Err_NONE;
}

static PF_Err 
GlobalSetup (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	out_data->my_version = PF_VERSION(	MAJOR_VERSION, 
										MINOR_VERSION,
										BUG_VERSION, 
										STAGE_VERSION, 
										BUILD_VERSION);

	out_data->out_flags =  PF_OutFlag_DEEP_COLOR_AWARE;	// just 16bpc, not 32bpc
	
	return PF_Err_NONE;
}

static PF_Err 
ParamsSetup (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err		err		= PF_Err_NONE;
	PF_ParamDef	def;	

	AEFX_CLR_STRUCT(def);

	PF_ADD_FLOAT_SLIDERX(	STR(StrID_Seg_Param_Name), 
							SKELETON_SEG_MIN, 
							SKELETON_SEG_MAX, 
							SKELETON_SEG_MIN, 
							SKELETON_SEG_MAX, 
							SKELETON_SEG_DFLT,
							PF_Precision_INTEGER,
							0,
							0,
							LEN_DISK_ID);


	PF_ADD_TOPIC(STR(StrID_Topic_Generator), SKELETON_GENERATOR_START_ID);


	PF_ADD_FLOAT_SLIDERX(	STR(StrID_Len_Param_Name), 
							SKELETON_LEN_MIN, 
							SKELETON_LEN_MAX, 
							SKELETON_LEN_MIN, 
							SKELETON_LEN_MAX, 
							SKELETON_LEN_DFLT,
							PF_Precision_INTEGER,
							0,
							0,
							LEN_DISK_ID);


	PF_ADD_FLOAT_SLIDERX(	STR(StrID_Rang_Param_Name), 
							SKELETON_RANG_MIN, 
							SKELETON_RANG_MAX, 
							SKELETON_RANG_MIN, 
							SKELETON_RANG_MAX, 
							SKELETON_RANG_DFLT,
							PF_Precision_HUNDREDTHS,
							0,
							0,
							RANG_DISK_ID);


	PF_ADD_FLOAT_SLIDERX(	STR(StrID_Strait_Param_Name), 
							SKELETON_STRAIT_MIN, 
							SKELETON_STRAIT_MAX, 
							SKELETON_STRAIT_MIN, 
							SKELETON_STRAIT_MAX, 
							SKELETON_STRAIT_DFLT,
							PF_Precision_INTEGER,
							0,
							0,
							STRAIT_DISK_ID);


	PF_ADD_POPUP(		STR(StrID_Mode_Param_Name), 
						MODE_SIZE,
						MODE_LINES,
						STR(StrID_ModeChoices),
						MODE_DISK_ID);


	PF_ADD_COLOR(	STR(StrID_Color_Param_Name),
					PF_MAX_CHAN8,
					0,
					PF_MAX_CHAN8,
					COLOR_DISK_ID);



	PF_END_TOPIC(SKELETON_GENERATOR_END_ID);


	PF_ADD_TOPIC(STR(StrID_Topic_Detector), SKELETON_DETECTOR_START_ID);


	PF_ADD_COLOR(	STR(StrID_Search_Param_Name),
					0,
					0,
					0,
					SEARCH_DISK_ID);


	PF_ADD_FLOAT_SLIDERX(	STR(StrID_Detect_Param_Name), 
							SKELETON_DETECT_MIN, 
							SKELETON_DETECT_MAX, 
							SKELETON_DETECT_MIN, 
							SKELETON_DETECT_MAX, 
							SKELETON_DETECT_DFLT,
							PF_Precision_INTEGER,
							0,
							0,
							DETECT_DISK_ID);

	PF_ADD_FLOAT_SLIDERX(	STR(StrID_Spread_Param_Name), 
							SKELETON_SPREAD_MIN, 
							SKELETON_SPREAD_MAX, 
							SKELETON_SPREAD_MIN, 
							SKELETON_SPREAD_MAX, 
							SKELETON_SPREAD_DFLT,
							PF_Precision_INTEGER,
							0,
							0,
							SPREAD_DISK_ID);


	PF_ADD_CHECKBOXX(	STR(StrID_Grid_Param_Name),
						FALSE,
						0,
						GRID_DISK_ID);


	PF_ADD_FLOAT_SLIDERX(	STR(StrID_Rand_Param_Name), 
							SKELETON_RAND_MIN, 
							SKELETON_RAND_MAX, 
							SKELETON_RAND_MIN, 
							SKELETON_RAND_MAX, 
							SKELETON_RAND_DFLT,
							PF_Precision_HUNDREDTHS,
							0,
							0,
							RAND_DISK_ID);


	PF_ADD_LAYER(	STR(StrID_Check_Param_Name), 
					PF_LayerDefault_MYSELF, 
					CHECK_DISK_ID);


	PF_END_TOPIC(SKELETON_DETECTOR_END_ID);
	
	out_data->num_params = SKELETON_NUM_PARAMS;

	return err;
}


static PF_Err 
Render (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{

	PF_Err		err		= PF_Err_NONE;

	AEGP_SuiteHandler	l_suites(in_data->pica_basicP);

	PF_Pixel color;
	AEFX_CLR_STRUCT(color);
	color = params[SKELETON_COLOR]->u.cd.value;
 
	int size = 0;
	int capacity = 10;
	std::vector<Vertex> blackPts(capacity);

	PF_EffectWorld l_world;

    AEFX_CLR_STRUCT(l_world);

    A_long l_width = output->width;

    A_long l_height = output->height;

    A_long l_size = l_width * l_height;


	PF_ParamDef			checkout;

	AEFX_CLR_STRUCT(checkout);


	PF_CHECKOUT_PARAM(	in_data, 
						SKELETON_CHECK,
						in_data->current_time, 
						in_data->time_step,
						in_data->time_scale, 
						&checkout);


	PF_Pixel inputColor;
	AEFX_CLR_STRUCT(inputColor);
	inputColor = params[SKELETON_SEARCH]->u.cd.value;

	float rangeC = params[SKELETON_DETECT]->u.fs_d.value / 10.0;
	float spread = params[SKELETON_SPREAD]->u.fs_d.value;

	for(int y = 0; y < l_height; y++) {

		for(int x = 0; x < l_width; x++) {

    		PF_Pixel *p = getPixelXY(checkout, x, y);
    		float random = rand() % 100;

    		if(   (abs( (p->red)   -  (inputColor.red)   )  <  rangeC)
			   && (abs( (p->green) -  (inputColor.green) )  <  rangeC)
			   && (abs( (p->blue)  -  (inputColor.blue)  )  <  rangeC) 
			   && random <= spread) {

			    blackPts[size] = Vertex(x, y);
				size++;
				if(size >= capacity) { 

					capacity *= 2;
					blackPts.resize( capacity, Vertex() ); 

				}

			}

		}

	}


	PF_CHECKIN_PARAM(in_data, &checkout);


	GLFWwindow* offscreen_context;

	AEFX_CLR_STRUCT(offscreen_context);

	offscreen_context = glewSetup(l_width, l_height);



	if(glewInit() == GLEW_OK)
	{

		ERR(l_suites.WorldSuite1()->new_world(in_data->effect_ref,
											  l_width, 
											  l_height, 
											  PF_NewWorldFlag_CLEAR_PIXELS, 
											  &l_world));

   		PF_Pixel8 *l_data;

   		AEFX_CLR_STRUCT(l_data);

   		in_data->utils->get_pixel_data8(&l_world, NULL, &l_data);

		if (size > 0) {

			int count   =  params[SKELETON_SEG]->u.fs_d.value;
			int ps      =  0;
			int pd      =  params[SKELETON_LEN]->u.fs_d.value;
			int strait  =  params[SKELETON_STRAIT]->u.fs_d.value;
			int k       =  (2 * rand()) % size;

			float points[1000000];


			for(int p = 0; p < count; p++) {


				k = (2 * rand()) % size;
				
				points[2*ps]      =  blackPts[k].Xcord(l_width);
				points[2*ps + 1]  =  blackPts[k].Ycord(l_height);
				ps++;

				int pk = 1;
				int tries = 0;
				int triesMax = 20;

				float range = params[SKELETON_RANG]->u.fs_d.value / 500.0 + 0.01;

				while( (pk < pd) ) {

					k = (2 * rand()) % size;
					float x  =  blackPts[k].Xcord(l_width);
					float y  =  blackPts[k].Ycord(l_height);


					tries++;

					float d  =  dist( points[2*ps - 2], points[2*ps - 1], x, y );

					if( (d < range) && 
						(gap( points[2*ps - 2],
							 points[2*ps - 1],
							 x, y,
							 l_width,
							 l_height,
							 inputColor,
							 checkout ) || ( params[SKELETON_GRID]->u.bd.value ) ) ) {

						if( pk == 1 ) {

							points[2*ps]      =  x;
							points[2*ps + 1]  =  y;
							ps++;
							pk++;
							tries = 0;

						}

						else if ( dir( points[2*ps - 4],
									   points[2*ps - 3],
									   points[2*ps - 2],
									   points[2*ps - 1],
									   x, y,
									   params[SKELETON_STRAIT]->u.fs_d.value ) ) {

							points[2*ps]      =  x;
							points[2*ps + 1]  =  y;
							ps++;
							pk++;
							tries = 0;

						}

					}


					if(tries > triesMax) {

						points[2*ps]      =  points[2*ps - 2];
						points[2*ps + 1]  =  points[2*ps - 1];
						ps++;
						pk++;
						tries = 0;

					}

				}

			}

	   		generateCanvas(points, 
	   					   l_width, 
	   					   l_height, 
	   					   l_world, 
	   					   l_data,
	   					   color, 
	   					   offscreen_context,
	   					   count,
	   					   pd,
	   					   params[SKELETON_MODE]->u.pd.value);

	   	}

   		ERR(l_suites.WorldTransformSuite1()->copy_hq(in_data->effect_ref, &l_world, output, NULL, NULL));

		ERR(l_suites.WorldSuite1()->dispose_world(in_data->effect_ref, &l_world));

	}

    return err;
}


extern "C" DllExport
PF_Err PluginDataEntryFunction(
	PF_PluginDataPtr inPtr,
	PF_PluginDataCB inPluginDataCallBackPtr,
	SPBasicSuite* inSPBasicSuitePtr,
	const char* inHostName,
	const char* inHostVersion)
{
	PF_Err result = PF_Err_INVALID_CALLBACK;

	result = PF_REGISTER_EFFECT(
		inPtr,
		inPluginDataCallBackPtr,
		"Skeleton", // Name
		"ADBE Skeleton", // Match Name
		"Sample Plug-ins", // Category
		AE_RESERVED_INFO); // Reserved Info

	return result;
}


PF_Err
EffectMain(
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extra)
{
	PF_Err		err = PF_Err_NONE;
	
	try {
		switch (cmd) {
			case PF_Cmd_ABOUT:

				err = About(in_data,
							out_data,
							params,
							output);
				break;
				
			case PF_Cmd_GLOBAL_SETUP:

				err = GlobalSetup(	in_data,
									out_data,
									params,
									output);
				break;
				
			case PF_Cmd_PARAMS_SETUP:

				err = ParamsSetup(	in_data,
									out_data,
									params,
									output);
				break;
				
			case PF_Cmd_RENDER:

				err = Render(	in_data,
								out_data,
								params,
								output);
				break;
		}
	}
	catch(PF_Err &thrown_err){
		err = thrown_err;
	}
	return err;
}

