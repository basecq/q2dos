/*
 * This file is automatically generated from the Mesa internal type
 * definitions.  Do not edit directly.
 */

#ifndef __ASM_TYPES_H__
#define __ASM_TYPES_H__

#include "assyntax.h"


/* =============================================================
 * Offsets for GLcontext
 */

#define CTX_DRIVER_CTX              	680

#define CTX_LIGHT_ENABLED           	37136
#define CTX_LIGHT_SHADE_MODEL       	37140
#define CTX_LIGHT_COLOR_MAT_FACE    	37144
#define CTX_LIGHT_COLOR_MAT_MODE    	37148
#define CTX_LIGHT_COLOR_MAT_MASK    	37152
#define CTX_LIGHT_COLOR_MAT_ENABLED 	37156
#define CTX_LIGHT_ENABLED_LIST      	37160
#define CTX_LIGHT_NEED_VERTS        	41516
#define CTX_LIGHT_FLAGS             	41520
#define CTX_LIGHT_BASE_COLOR        	41524


/* =============================================================
 * Offsets for struct vertex_buffer
 */

#define VB_SIZE                	0
#define VB_COUNT               	4

#define VB_FIRST_CLIPPED       	8
#define VB_FIRST_PRIMITIVE     	12

#define VB_ELTS                	16
#define VB_OBJ_PTR             	20
#define VB_EYE_PTR             	24
#define VB_CLIP_PTR            	28
#define VB_PROJ_CLIP_PTR       	32
#define VB_CLIP_OR_MASK        	36
#define VB_CLIP_MASK           	40
#define VB_NORMAL_PTR          	44
#define VB_EDGE_FLAG           	52
#define VB_TEX0_COORD_PTR      	56
#define VB_TEX1_COORD_PTR      	60
#define VB_TEX2_COORD_PTR      	64
#define VB_TEX3_COORD_PTR      	68
#define VB_INDEX_PTR           	88
#define VB_COLOR_PTR           	96
#define VB_SECONDARY_COLOR_PTR 	104
#define VB_FOG_COORD_PTR       	116
#define VB_POINT_SIZE_PTR      	112
#define VB_MATERIAL            	120
#define VB_MATERIAL_MASK       	124
#define VB_FLAG                	128
#define VB_PRIMITIVE           	132
#define VB_PRIMITIVE_LENGTH    	136

#define VB_IMPORTABLE_DATA     	204

#define VB_LAST_CLIPPED        	216

/*
 * Flags for struct vertex_buffer
 */

#define VERT_BIT_OBJ           	0x1
#define VERT_BIT_NORM          	0x4
#define VERT_BIT_RGBA          	0x8
#define VERT_BIT_SPEC_RGB      	0x10
#define VERT_BIT_FOG_COORD     	0x20
#define VERT_BIT_INDEX         	0x40
#define VERT_BIT_EDGE          	0x80
#define VERT_BIT_TEX0          	0x100
#define VERT_BIT_TEX1          	0x200
#define VERT_BIT_TEX2          	0x400
#define VERT_BIT_TEX3          	0x800
#define VERT_BIT_EVAL_C1       	0x10000
#define VERT_BIT_EVAL_C2       	0x20000
#define VERT_BIT_EVAL_P1       	0x40000
#define VERT_BIT_EVAL_P2       	0x80000
#define VERT_BIT_OBJ_3         	0x100000
#define VERT_BIT_OBJ_4         	0x200000
#define VERT_BIT_MATERIAL      	0x400000
#define VERT_BIT_ELT           	0x800000
#define VERT_BIT_BEGIN         	0x1000000
#define VERT_BIT_END           	0x2000000
#define VERT_BIT_END_VB        	0x4000000
#define VERT_BIT_POINT_SIZE    	0x8000000
#define VERT_BIT_EYE           	0x1000000
#define VERT_BIT_CLIP          	0x2000000

#define VERT_BIT_OBJ_23        	0x100000
#define VERT_BIT_OBJ_234       	0x200000


/* =============================================================
 * Offsets for GLvector3f
 */

#define V3F_DATA          	0
#define V3F_START         	4
#define V3F_COUNT         	8
#define V3F_STRIDE        	12
#define V3F_FLAGS         	16


/* =============================================================
 * Offsets for GLvector4f
 */

#define V4F_DATA          	0
#define V4F_START         	4
#define V4F_COUNT         	8
#define V4F_STRIDE        	12
#define V4F_SIZE          	16
#define V4F_FLAGS         	20

/*
 * Flags for GLvector4f
 */

#define VEC_MALLOC        	0x10
#define VEC_NOT_WRITEABLE 	0x40
#define VEC_BAD_STRIDE    	0x100

#define VEC_SIZE_1        	0x1
#define VEC_SIZE_2        	0x3
#define VEC_SIZE_3        	0x7
#define VEC_SIZE_4        	0xf


/* =============================================================
 * Offsets for GLmatrix
 */

#define MATRIX_DATA   	0
#define MATRIX_INV    	4
#define MATRIX_FLAGS  	8
#define MATRIX_TYPE   	12


/* =============================================================
 * Offsets for struct gl_light
 */

#define LIGHT_NEXT              	0
#define LIGHT_PREV              	4

#define LIGHT_AMBIENT           	8
#define LIGHT_DIFFUSE           	24
#define LIGHT_SPECULAR          	40
#define LIGHT_EYE_POSITION      	56
#define LIGHT_EYE_DIRECTION     	72
#define LIGHT_SPOT_EXPONENT     	88
#define LIGHT_SPOT_CUTOFF       	92
#define LIGHT_COS_CUTOFF        	96
#define LIGHT_CONST_ATTEN       	100
#define LIGHT_LINEAR_ATTEN      	104
#define LIGHT_QUADRATIC_ATTEN   	108
#define LIGHT_ENABLED           	112

#define LIGHT_FLAGS             	116

#define LIGHT_POSITION          	120
#define LIGHT_VP_INF_NORM       	136
#define LIGHT_H_INF_NORM        	148
#define LIGHT_NORM_DIRECTION    	160
#define LIGHT_VP_INF_SPOT_ATTEN 	176

#define LIGHT_SPOT_EXP_TABLE    	180
#define LIGHT_MAT_AMBIENT       	4276
#define LIGHT_MAT_DIFFUSE       	4300
#define LIGHT_MAT_SPECULAR      	4324

#define SIZEOF_GL_LIGHT         	4356

/*
 * Flags for struct gl_light
 */

#define LIGHT_SPOT              	0x1
#define LIGHT_LOCAL_VIEWER      	0x2
#define LIGHT_POSITIONAL        	0x4

#define LIGHT_NEED_VERTICES     	0x6


/* =============================================================
 * Offsets for struct gl_lightmodel
 */

#define LIGHT_MODEL_AMBIENT       	0
#define LIGHT_MODEL_LOCAL_VIEWER  	16
#define LIGHT_MODEL_TWO_SIDE      	17
#define LIGHT_MODEL_COLOR_CONTROL 	20


#endif /* __ASM_TYPES_H__ */