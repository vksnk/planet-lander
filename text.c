//http://www.dafont.com/hyperspace.font


#include <stdio.h>
#include <math.h>
#include <string.h>

#ifdef __APPLE__
    #include <OpenGL/glu.h>
    #include <OpenGL/glext.h>
#else
    #include <GL/glu.h>
    #include <GL/glext.h>
    #include <GL/glx.h>
    #include <GL/glxext.h>
    #define glXGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)x)
#endif

const float A_coords[] = {	0, 1, 0, 0.3,
							0, 0.3, 0.5, 0,
							0.5, 0, 1, 0.3,
							1, 0.3, 1, 1,
							0, 0.6, 1, 0.6};

const float B_coords[] = {	0, 1, 0, 0,
							0, 0, 0.7, 0,
							0.7, 0, 1, 0.2,
							1, 0.2, 1, 0.36,
							1, 0.36, 0.7, 0.5,
							0.7, 0.5, 1, 0.65,
							1, 0.65, 1, 0.8,
							1, 0.8, 0.7, 1,
							0.7, 1, 0, 1,
							0, 0.5, 0.7, 0.5
							};

const float C_coords[] = {	1, 1, 0, 1,
							0, 1, 0, 0,
							0, 0, 1, 0
							};

const float D_coords[] = {	0, 1, 0, 0,
							0, 0, 0.5, 0,
							0.5, 0, 1, 0.33,
							1, 0.33, 1, 0.7,
							1, 0.7, 0.5, 1,
							0.5, 1, 0, 1
							};

const float E_coords[] = {	0, 1, 0, 0,
							0, 0, 1, 0,
							0, 1, 1, 1,
							0, 0.5, 0.7, 0.5,
							};

const float F_coords[] = {	0, 1, 0, 0,
							0, 0, 1, 0,
							0, 0.5, 0.7, 0.5,
							};

const float G_coords[] = {	1, 0.33, 1, 0,
							1, 0, 0, 0,
							0, 0, 0, 1,
							0, 1, 1, 1,
							1, 1, 1, 0.66,
							1, 0.66, 0.5, 0.66
							};


const float H_coords[] = {	0,	1,	0,	0,
							1,	0,	1,	1,
							0,	0.5,1,	0.5,
							};


const float I_coords[] = {	0.2, 0, 0.8, 0,
							0.5, 0, 0.5, 1,
							0.2, 1, 0.8, 1
							};


const float J_coords[] = {	1, 0, 1, 1,
							1, 1, 0.5, 1,
							0.5, 1, 0, 0.6
							};


const float K_coords[] = {	0, 0, 0, 1,
							0, 0.5, 1, 0,
							0, 0.5, 1, 1
							};

const float L_coords[] = {	0, 0, 0, 1,
							0, 1, 1, 1
							};

const float M_coords[] = {	0, 0, 0, 1,
							0, 0, 0.5, 0.3,
							0.5, 0.3, 1, 0,
							1, 0, 1, 1
							};


const float N_coords[] = {	0, 1, 0, 0,
							0, 0, 1, 1,
							1, 1, 1, 0,
							};

const float O_coords[] = {	0, 1, 0, 0,
							0, 0, 1, 0,
							1, 0, 1, 1,
							1, 1, 0, 1
							};

const float P_coords[] = {	0, 1, 0, 0,
							0, 0, 1, 0,
							1, 0, 1, 0.5,
							1, 0.5, 0, 0.5
							};


const float Q_coords[] = {	0, 1, 0, 0,
							0, 0, 1, 0,
							1, 0, 1, 0.7,
							1, 0.7, 0.7, 1,
							0.7, 1, 0, 1,
							1, 1, 0.5, 0.7
							};


const float R_coords[] = {	0, 1, 0, 0,
							0, 0, 1, 0,
							1, 0, 1, 0.5,
							1, 0.5, 0, 0.5,
							0, 0.5, 1, 1
							};


const float S_coords[] = {	1, 0, 0, 0,
							0, 0, 0, 0.5,
							0, 0.5, 1, 0.5,
							1, 0.5, 1, 1,
							1, 1, 0, 1
							};


const float T_coords[] = {	1, 0, 0, 0,
							0.5, 0, 0.5, 1
							};


const float U_coords[] = {	0, 0, 0, 1,
							0, 1, 1, 1,
							1, 1, 1, 0
							};

const float V_coords[] = {	0, 0, 0.5, 1,
							1, 0, 0.5, 1
							};


const float W_coords[] = {	0, 0, 0, 1,
							0, 1, 0.5, 0.66,
							0.5, 0.66, 1, 1,
							1, 1, 1, 0
							};


const float X_coords[] = {	0, 0, 1, 1,
							1, 0, 0, 1
							};


const float Y_coords[] = {	0, 0, 0.5, 0.33,
							1, 0, 0.5, 0.33,
							0.5, 0.33, 0.5, 1
							};


const float Z_coords[] = {	0, 0, 1, 0,
							1, 0, 0, 1,
							0, 1, 1, 1
							};
//0
const float s048_coords[] = {0, 1, 0, 0,
							0, 0, 1, 0,
							1, 0, 1, 1,
							1, 1, 0, 1,
							1, 0, 0, 1
							};
//1
const float s049_coords[] = {0.33, 1, 0.33, 0
							};

//2
const float s050_coords[] = {0, 0, 1, 0,
							1, 0, 1, 0.5,
							1, 0.5, 0, 0.5,
							0, 0.5, 0, 1,
							0, 1, 1, 1
							};
//3
const float s051_coords[] = {0, 0, 1, 0,
							0, 0.5, 1, 0.5,
							0, 1, 1, 1,
							1, 0, 1, 1
							};
//4
const float s052_coords[] = {0, 0, 0, 0.5,
							0, 0.5, 1, 0.5,
							1, 0, 1, 1
							};
//5
const float s053_coords[] = {1, 0, 0, 0,
							0, 0, 0, 0.5,
							0, 0.5, 1, 0.5,
							1, 0.5, 1, 1,
							1, 1, 0, 1
							};
//6
const float s054_coords[] = {0, 0, 0, 1,
							0, 1, 1, 1,
							1, 1, 1, 0.5,
							1, 0.5, 0, 0.5
							};
//7
const float s055_coords[] = {0, 0, 1, 0,
							1, 0, 1, 1
							};
//8
const float s056_coords[] = {0, 0, 1, 0,
							1, 0, 1, 1,
							1, 1, 0, 1,
							0, 1, 0, 0,
							0, 0.5, 1, 0.5
							};
//9
const float s057_coords[] = {0, 0, 1, 0,
							1, 0, 1, 1,
							0, 0, 0, 0.5,
							0, 0.5, 1, 0.5
							};

const char char_lines[126-32] = {
	0, //space
	0, //!
	0, //"
	0, //#
	0, //$
	0, //%
	0, //&
	0, //'
	0, //(
	0, //)
	0, //*
	0, //+
	0, //,
	0, //-
	0, //.
	0, ///
	4, //0
	1, //1
	5, //2
	4, //3
	3, //4
	5, //5
	4, //6
	2, //7
	5, //8
	4, //9
	0, //:
	0, //;
	0, //<
	0, //=
	0, //>
	0, //?
	0, //@
	5, //A
	10, //B
	3, //C
	6, //D
	4, //E
	3, //F
	6, //G
	3, //H
	3, //I
	3, //J
	3, //K
	2, //L
	4, //M
	3, //N
	4, //O
	4, //P
	6, //Q
	5, //R
	5, //S
	2, //T
	3, //U
	2, //V
	4, //W
	2, //X
	3, //Y
	4, //Z
	0, //[
	0, //\
	0, //]
	0, //^
	0, //_
	0, //`
	0, //fucking hack
	5, //a
	10, //b
	3, //c
	6, //d
	4, //e
	3, //f
	6, //g
	3, //h
	3, //i
	3, //j
	3, //k
	2, //l
	4, //m
	3, //n
	4, //o
	4, //p
	6, //q
	5, //r
	5, //s
	2, //t
	3, //u
	2, //v
	4, //w
	2, //x
	3, //y
	4, //z
	0, //{
	0, //}
	0 //~
};

const float* chars_coords[126-32] = {
	0, //space
	0, //!
	0, //"
	0, //#
	0, //$
	0, //%
	0, //&
	0, //'
	0, //(
	0, //)
	0, //*
	0, //+
	0, //,
	0, //-
	0, //.
	0, ///
	s048_coords, //0
	s049_coords, //1
	s050_coords, //2
	s051_coords, //3
	s052_coords, //4
	s053_coords, //5
	s054_coords, //6
	s055_coords, //7
	s056_coords, //8
	s057_coords, //9
	0, //:
	0, //;
	0, //<
	0, //=
	0, //>
	0, //?
	0, //@
	A_coords, //A
	B_coords, //B
	C_coords, //C
	D_coords, //D
	E_coords, //E
	F_coords, //F
	G_coords, //G
	H_coords, //H
	I_coords, //I
	J_coords, //J
	K_coords, //K
	L_coords, //L
	M_coords, //M
	N_coords, //N
	O_coords, //O
	P_coords, //P
	Q_coords, //Q
	R_coords, //R
	S_coords, //S
	T_coords, //T
	U_coords, //U
	V_coords, //V
	W_coords, //W
	X_coords, //X
	Y_coords, //Y
	Z_coords, //Z
	0, //[
	0, //\
	0, //]
	0, //^
	0, //_
	0, //`
	0, //fucking hack
	A_coords, //a
	B_coords, //b
	C_coords, //c
	D_coords, //d
	E_coords, //e
	F_coords, //f
	G_coords, //g
	H_coords, //h
	I_coords, //i
	J_coords, //j
	K_coords, //k
	L_coords, //l
	M_coords, //m
	N_coords, //n
	O_coords, //o
	P_coords, //p
	Q_coords, //q
	R_coords, //r
	S_coords, //s
	T_coords, //t
	U_coords, //u
	V_coords, //v
	W_coords, //w
	X_coords, //x
	Y_coords, //y
	Z_coords, //z
	0, //{
	0, //}
	0 //~
};

const float SPASING = 1.4;
const float HEIGHT_WIDTH_RATIO = 1.5;
void draw_vector_text(const char* text, int x, int y, float font_scale)
{
	for (int i=0; i<strlen(text); i++)
	{
		float char_x = x + SPASING * font_scale * i;
		float char_y = y;
		char current_char = text[i];

		if (current_char < 32)
			return;

		const float* current_char_coords = chars_coords[current_char-32];

		glBegin(GL_LINES);
		for (int l = 0; l < char_lines[current_char-32]; l++) {
			glVertex2f(char_x + current_char_coords[4*l] * font_scale, char_y + current_char_coords[4*l+1] * HEIGHT_WIDTH_RATIO * font_scale);
			glVertex2f(char_x + current_char_coords[4*l+2] * font_scale, char_y + current_char_coords[4*l+3] * HEIGHT_WIDTH_RATIO * font_scale);
		}
		glEnd();
	}
}