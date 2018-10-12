
# include "my_viewer.h"

# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sigogl/ui_slider.h>

# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>

# include <sigogl/ws_run.h>

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

MyViewer::MyViewer(int x, int y, int w, int h, const char* l) : WsViewer(x, y, w, h, l)
{
	state = 10;
	nstate = 0;
	cstate = 0;
	bstate = 0;
	smoothing = 0;
	_nbut = 0;
	//_nbut->value(1);
	_animating = false;
	add_ui();
	build_scene(nstate,state,cstate,bstate,smoothing, SliderX->value(), SliderY->value(),SliderZ->value());
	gsout << "You can change the number of triangles by clicking [q] or [w]." << gsnl;
	gsout << "[q] Decrease the number of triangles" << gsnl;
	gsout << "[w] Increase the number of triangles" << gsnl;
}

void MyViewer::add_ui()
{
	UiPanel *p, *sp; 
	UiPanel *ssp;//
	UiManager* uim = WsWindow::uim();
	

	p = uim->add_panel("", UiPanel::HorizLeft);
	p->add(new UiButton("Triangles", sp = new UiPanel()));
	{	UiPanel* p = sp;
	p->add(new UiButton("64(1)", EvTr1));
	p->add(new UiButton("256(2)", EvTr2)); p->top()->separate();
	p->add(new UiButton("576(3)", EvTr3)); p->top()->separate();
	p->add(new UiButton("1,024(4)", EvTr4)); p->top()->separate();
	p->add(new UiButton("1,600(5)", EvTr5)); p->top()->separate();
	p->add(new UiButton("2,304(6)", EvTr6)); p->top()->separate();
	p->add(new UiButton("3,136(7)", EvTr7)); p->top()->separate();
	p->add(new UiButton("4,096(8)", EvTr8)); p->top()->separate();
	p->add(new UiButton("5,184(9)", EvTr9)); p->top()->separate();
	p->add(new UiButton("5,400(10)", EvTr10)); p->top()->separate();
	p->add(new UiButton("160,000(50)", EvTr11)); p->top()->separate();
	p->add(new UiButton("640,000(100)", EvTr12)); p->top()->separate();
	}
	p->add(new UiCheckButton("Cage Rendering 1", EvCage1)); p->top()->separate();
	p->add(new UiCheckButton("Cage Rendering 2", EvCage2)); p->top()->separate();
	p->add(new UiCheckButton("Normal", EvNormals)); p->top()->separate();
	p->add(new UiCheckButton("Shadow", EvShadow)); p->top()->separate();
	/**/
	p->add(new UiButton("Light Control", ssp = new UiPanel()));
	{	UiPanel* p = ssp;
	p->add(SliderX=new UiSlider("X:", EvLight));
	SliderX->range(-100, 100);
	p->add(SliderY=new UiSlider("Y:", EvLight));
	SliderY->range(-100, 100);
	p->add(SliderZ=new UiSlider("Z:", EvLight));
	SliderZ->range(0, 200);
	SliderZ->value(100);
	}
	p->add(new UiCheckButton("Smooth", EvSmooth)); p->top()->separate();
	p->add(new UiButton("Exit", EvExit)); p->top()->separate();
}

void MyViewer::add_model(SnShape* s, GsVec p)
{
	SnManipulator* manip = new SnManipulator;
	GsMat m;
	m.translation(p);
	manip->initial_mat(m);

	SnGroup* g = new SnGroup;
	SnLines* l = new SnLines;
	l->color(GsColor::orange);
	g->add(s);
	g->add(l);
	manip->child(g);

	rootg()->add(manip);
}


void MyViewer::build_scene(int check, int div, int put, int button, int change, float lightx, float lighty, float lightz)
{

	// Loading a File
	ifstream ifs("teapotCGA.txt");
	string str;
	/*
	if (ifs.fail()) {
		gsout << "File do not exist.\n";
	}
	else {
		gsout << "Success!!!\n";
	}
	*/

	//Initialization
	SnModel* _model;
	_model = new SnModel;
	GsModel* m;
	m = _model->model();
	int numgroup = 32;
	int sizenum = 16 * numgroup + (3 + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (3 + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32;
	int sizenumA = 16 * numgroup;
	int sizenumB = 16 * numgroup + (3 + 1)*(div + 1) * 32;
	int sizenumC = 16 * numgroup + (3 + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32;
	int sizenumD = 16 * numgroup + (3 + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (3 + 1)*(div + 1) * 32;
	int sizenumE = 16 * numgroup + (3 + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (3 + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32;
	int sizenumF = 16 * numgroup + (3 + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (3 + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32;
	int sizenumG = 16 * numgroup + (3 + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (3 + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32;
	int sizenumH = 16 * numgroup + (3 + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (3 + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32 + (div + 1)*(div + 1) * 32;
	m->V.size(sizenum);

	//Control Point Coordinates
	int a = 0, b = 0;
	float c = 0.0, d = 0.0, e = 0.0;
	getline(ifs, str);
	sscanf(str.data(), "%d", &a);
	getline(ifs, str);
	sscanf(str.data(), "%d %d", &a, &b);
	for (int i = 0; i <= 15; i++) {
		getline(ifs, str);
		sscanf(str.data(), "%f %f %f", &c, &d, &e);
		m->V[i].set(c, d, e);
	}
	for (int j = 16; j <= 16 * (numgroup - 1); j = j + 16) {

		getline(ifs, str);
		sscanf(str.data(), "%d %d", &a, &b);
		for (int i = j; i <= j + 15; i++) {
			getline(ifs, str);
			sscanf(str.data(), "%f %f %f", &c, &d, &e);
			m->V[i].set(c, d, e);
		}
	}

	//Bezier Curve 1-1
	for (int pnum = 0; pnum <= 31; pnum++) {
		for (int cnum = 0; cnum <= 3; cnum++) {
			for (int tnum = 0; tnum <= div; tnum++) {
				double t = (double)tnum / div;
				double A = (1 - 3 * t + 3 * t*t - t*t*t);
				double B = (3 * t - 6 * t*t + 3 * t*t*t);
				double C = (3 * t*t - 3 * t*t*t);
				double D = (t*t*t);
				double x = A*(m->V[0 + (cnum * 4) + (16 * pnum)].x) + B*(m->V[1 + (cnum * 4) + (16 * pnum)].x) + C*(m->V[2 + (cnum * 4) + (16 * pnum)].x) + D*(m->V[3 + (cnum * 4) + (16 * pnum)].x);
				double y = A*(m->V[0 + (cnum * 4) + (16 * pnum)].y) + B*(m->V[1 + (cnum * 4) + (16 * pnum)].y) + C*(m->V[2 + (cnum * 4) + (16 * pnum)].y) + D*(m->V[3 + (cnum * 4) + (16 * pnum)].y);
				double z = A*(m->V[0 + (cnum * 4) + (16 * pnum)].z) + B*(m->V[1 + (cnum * 4) + (16 * pnum)].z) + C*(m->V[2 + (cnum * 4) + (16 * pnum)].z) + D*(m->V[3 + (cnum * 4) + (16 * pnum)].z);
				m->V[511 + (tnum + 1) + (cnum * (div + 1)) + (pnum*(3 + 1)*(div + 1))].set(x, y, z);
			}
		}
	}

	//Bezier Curve 1-2
	for (int pnum = 0; pnum <= 31; pnum++) {
		for (int rnum = 0; rnum <= div; rnum++) {
			for (int tnum = 0; tnum <= div; tnum++) {
				double t = (double)tnum / div;
				double A = (1 - 3 * t + 3 * t*t - t*t*t);
				double B = (3 * t - 6 * t*t + 3 * t*t*t);
				double C = (3 * t*t - 3 * t*t*t);
				double D = (t*t*t);
				double x = A*(m->V[512 + (rnum)+((3 + 1)*(div + 1) * pnum)].x) + B*(m->V[(512 + div + 1) + (rnum)+((3 + 1)*(div + 1) * pnum)].x) + C*(m->V[(512 + (div + 1) * 2) + (rnum)+((3 + 1)*(div + 1) * pnum)].x) + D*(m->V[(512 + (div + 1) * 3) + (rnum)+((3 + 1)*(div + 1) * pnum)].x);
				double y = A*(m->V[512 + (rnum)+((3 + 1)*(div + 1) * pnum)].y) + B*(m->V[(512 + div + 1) + (rnum)+((3 + 1)*(div + 1) * pnum)].y) + C*(m->V[(512 + (div + 1) * 2) + (rnum)+((3 + 1)*(div + 1) * pnum)].y) + D*(m->V[(512 + (div + 1) * 3) + (rnum)+((3 + 1)*(div + 1) * pnum)].y);
				double z = A*(m->V[512 + (rnum)+((3 + 1)*(div + 1) * pnum)].z) + B*(m->V[(512 + div + 1) + (rnum)+((3 + 1)*(div + 1) * pnum)].z) + C*(m->V[(512 + (div + 1) * 2) + (rnum)+((3 + 1)*(div + 1) * pnum)].z) + D*(m->V[(512 + (div + 1) * 3) + (rnum)+((3 + 1)*(div + 1) * pnum)].z);
				m->V[(sizenumB - 1) + (tnum + 1) + (rnum * (div + 1)) + (pnum * (div + 1)*(div + 1))].set(x, y, z);
			}
		}
	}

	//Bezier Curve 2-1
	for (int pnum = 0; pnum <= 31; pnum++) {
		for (int cnum = 0; cnum <= 3; cnum++) {
			for (int tnum = 0; tnum <= div; tnum++) {
				double t = (double)tnum / div;
				double A = (1 - 3 * t + 3 * t*t - t*t*t);
				double B = (3 * t - 6 * t*t + 3 * t*t*t);
				double C = (3 * t*t - 3 * t*t*t);
				double D = (t*t*t);
				double x = A*(m->V[0 + (cnum)+(16 * pnum)].x) + B*(m->V[4 + (cnum)+(16 * pnum)].x) + C*(m->V[8 + (cnum)+(16 * pnum)].x) + D*(m->V[12 + (cnum)+(16 * pnum)].x);
				double y = A*(m->V[0 + (cnum)+(16 * pnum)].y) + B*(m->V[4 + (cnum)+(16 * pnum)].y) + C*(m->V[8 + (cnum)+(16 * pnum)].y) + D*(m->V[12 + (cnum)+(16 * pnum)].y);
				double z = A*(m->V[0 + (cnum)+(16 * pnum)].z) + B*(m->V[4 + (cnum)+(16 * pnum)].z) + C*(m->V[8 + (cnum)+(16 * pnum)].z) + D*(m->V[12 + (cnum)+(16 * pnum)].z);
				m->V[(sizenumC - 1) + (tnum + 1) + (cnum * (div + 1)) + (pnum*(3 + 1)*(div + 1))].set(x, y, z);
			}
		}
	}

	//Bezier Curve 2-2
	for (int pnum = 0; pnum <= 31; pnum++) {
		for (int rnum = 0; rnum <= div; rnum++) {
			for (int tnum = 0; tnum <= div; tnum++) {
				double t = (double)tnum / div;
				double A = (1 - 3 * t + 3 * t*t - t*t*t);
				double B = (3 * t - 6 * t*t + 3 * t*t*t);
				double C = (3 * t*t - 3 * t*t*t);
				double D = (t*t*t);
				double x = A*(m->V[sizenumC + (rnum)+((3 + 1)*(div + 1) * pnum)].x) + B*(m->V[(sizenumC + div + 1) + (rnum)+((3 + 1)*(div + 1) * pnum)].x) + C*(m->V[(sizenumC + (div + 1) * 2) + (rnum)+((3 + 1)*(div + 1) * pnum)].x) + D*(m->V[(sizenumC + (div + 1) * 3) + (rnum)+((3 + 1)*(div + 1) * pnum)].x);
				double y = A*(m->V[sizenumC + (rnum)+((3 + 1)*(div + 1) * pnum)].y) + B*(m->V[(sizenumC + div + 1) + (rnum)+((3 + 1)*(div + 1) * pnum)].y) + C*(m->V[(sizenumC + (div + 1) * 2) + (rnum)+((3 + 1)*(div + 1) * pnum)].y) + D*(m->V[(sizenumC + (div + 1) * 3) + (rnum)+((3 + 1)*(div + 1) * pnum)].y);
				double z = A*(m->V[sizenumC + (rnum)+((3 + 1)*(div + 1) * pnum)].z) + B*(m->V[(sizenumC + div + 1) + (rnum)+((3 + 1)*(div + 1) * pnum)].z) + C*(m->V[(sizenumC + (div + 1) * 2) + (rnum)+((3 + 1)*(div + 1) * pnum)].z) + D*(m->V[(sizenumC + (div + 1) * 3) + (rnum)+((3 + 1)*(div + 1) * pnum)].z);
				m->V[(sizenumD - 1) + (tnum + 1) + (rnum * (div + 1)) + (pnum * (div + 1)*(div + 1))].set(x, y, z);
			}
		}
	}
	
	//Bezier Curve derivative 1
	GsVec d0;
	GsVec d1;
	GsVec d2;

	for (int pnum = 0; pnum <= 31; pnum++) {
		for (int cnum = 0; cnum <= div; cnum++) {
			d0 = 3 * (m->V[(sizenumA + (div + 1)) + cnum + pnum*(3 + 1)*(div + 1)] - m->V[(sizenumA)+cnum + pnum*(3 + 1)*(div + 1)]);
			d1 = 3 * (m->V[(sizenumA + 2 * (div + 1)) + cnum + pnum*(3 + 1)*(div + 1)] - m->V[(sizenumA + (div + 1)) + cnum + pnum*(3 + 1)*(div + 1)]);
			d2 = 3 * (m->V[(sizenumA + 3 * (div + 1)) + cnum + pnum*(3 + 1)*(div + 1)] - m->V[(sizenumA + 2 * (div + 1)) + cnum + pnum*(3 + 1)*(div + 1)]);
			for (int tnum = 0; tnum <= div; tnum++) {
				double t = (double)tnum / div;
				double A = (1 - 2 * t + t*t);
				double B = (2 * t - 2 * t*t);
				double C = (t*t);
				double x = A*(d0.x) + B*(d1.x) + C*(d2.x);
				double y = A*(d0.y) + B*(d1.y) + C*(d2.y);
				double z = A*(d0.z) + B*(d1.z) + C*(d2.z);
				m->V[sizenumE + (tnum)+(cnum)*(div + 1) + (pnum)*(div + 1)*(div + 1)].set(x, y, z);
			}
		}
	}


	//Bezier Curve derivative 2
	for (int pnum = 0; pnum <= 31; pnum++) {
		for (int rnum = 0; rnum <= div; rnum++) {
			d0 = 3 * (m->V[(sizenumC + (div + 1)) + (rnum)+(pnum)*(3 + 1)*(div + 1)] - m->V[(sizenumC)+(rnum)+(pnum)*(3 + 1)*(div + 1)]);
			d1 = 3 * (m->V[(sizenumC + 2 * (div + 1)) + (rnum)+(pnum)*(3 + 1)*(div + 1)] - m->V[(sizenumC + (div + 1)) + (rnum)+(pnum)*(3 + 1)*(div + 1)]);
			d2 = 3 * (m->V[(sizenumC + 3 * (div + 1)) + (rnum)+(pnum)*(3 + 1)*(div + 1)] - m->V[(sizenumC + 2 * (div + 1)) + (rnum)+(pnum)*(3 + 1)*(div + 1)]);
			for (int tnum = 0; tnum <= div; tnum++) {
				double t = (double)tnum / div;
				double A = (1 - 2 * t + t*t);
				double B = (2 * t - 2 * t*t);
				double C = (t*t);
				double x = A*(d0.x) + B*(d1.x) + C*(d2.x);
				double y = A*(d0.y) + B*(d1.y) + C*(d2.y);
				double z = A*(d0.z) + B*(d1.z) + C*(d2.z);
				m->V[sizenumF + (tnum)+(rnum)*(div + 1) + (pnum)*(div + 1)*(div + 1)].set(x, y, z);
			}
		}
	}

	//Normal Vectors
	for (int pnum = 0; pnum <= 31; pnum++) {
		for (int j = 0; j <= div; j++) {
			for (int i = 0; i <= div; i++) {
				GsVec null;
				GsVec center = null;
				GsVec u = m->V[sizenumE + i + ((div + 1) * j) + ((div + 1)*(div + 1) * pnum)];
				GsVec v = m->V[sizenumF + ((div + 1) * i) + j + ((div + 1)*(div + 1) * pnum)];
				GsVec n;
				n = cross(v, u);
				n.normalize();
				n = n / 2;
				m->V[sizenumG + i + (j * (div + 1)) + ((div + 1)*(div + 1) * pnum)].set(n.x, n.y, n.z);
			}
		}
	}
	
	//Rendering Cage 1
	SnLines* cage = new SnLines;
	cage->color(GsColor::cyan);
	for (int pnum = 0; pnum <= 31; pnum++) {
		for (int i = 0; i <= 12; i = i + 4) {
			cage->push(m->V[i + 16 * pnum], m->V[i + 1 + 16 * pnum]);
			cage->push(m->V[i + 1 + 16 * pnum], m->V[i + 2 + 16 * pnum]);
			cage->push(m->V[i + 2 + 16 * pnum], m->V[i + 3 + 16 * pnum]);
		}
		for (int i = 0; i <= 3; i = i + 1) {
			cage->push(m->V[i + 16 * pnum], m->V[i + 4 + 16 * pnum]);
			cage->push(m->V[i + 4 + 16 * pnum], m->V[i + 8 + 16 * pnum]);
			cage->push(m->V[i + 8 + 16 * pnum], m->V[i + 12 + 16 * pnum]);
		}
	}
	if (put == 1) {
		rootg()->add(cage);
	}

	//Rendering Cage 2
	SnLines* cage2 = new SnLines;
	cage2->color(GsColor::green);
	for (int pnum = 0; pnum <= 31; pnum++) {
		for (int i = 0; i <= 12; i = i + 4) {
			cage2->push(m->V[i + 16 * pnum], m->V[i + 1 + 16 * pnum]);
			cage2->push(m->V[i + 1 + 16 * pnum], m->V[i + 2 + 16 * pnum]);
			cage2->push(m->V[i + 2 + 16 * pnum], m->V[i + 3 + 16 * pnum]);
		}
		for (int i = 0; i <= 3; i = i + 1) {
			cage2->push(m->V[i + 16 * pnum], m->V[i + 4 + 16 * pnum]);
			cage2->push(m->V[i + 4 + 16 * pnum], m->V[i + 8 + 16 * pnum]);
			cage2->push(m->V[i + 8 + 16 * pnum], m->V[i + 12 + 16 * pnum]);
		}
	}
	cage2->visible(0);
	cagehead = cage2;
	rootg()->add(cage2);

	//Teapot
	SnModel* realmodel;
	realmodel = new SnModel;
	GsModel* real;
	real = realmodel->model();
	real->V.size((div + 1)*(div + 1) * 32);
	real->N.size((div + 1)*(div + 1) * 32);
	for (int pnum = 0; pnum <= 31; pnum++) {
		for (int num = 0; num <= (div + 1)*(div + 1) - 1; num++) {
			m->V[sizenumH + num + (pnum*(div + 1)*(div + 1))].set(m->V[sizenumB + num + (pnum * (div + 1)*(div + 1))].x + m->V[sizenumG + num + (pnum * (div + 1)*(div + 1))].x, m->V[sizenumB + num + (pnum * (div + 1)*(div + 1))].y + m->V[sizenumG + num + (pnum * (div + 1)*(div + 1))].y, m->V[sizenumB + num + (pnum * (div + 1)*(div + 1))].z + m->V[sizenumG + num + (pnum * (div + 1)*(div + 1))].z);
			real->V[num + pnum*((div + 1)*(div + 1))] = m->V[sizenumB + num + (pnum * (div + 1)*(div + 1))];
			real->N[num + pnum*((div + 1)*(div + 1))] = m->V[sizenumG + num + (pnum * (div + 1)*(div + 1))];
		}
	}

	//Shadow
	SnModel* shadowmodel;
	shadowmodel = new SnModel;
	shadowmodel->color(GsColor::gray);
	GsModel* shadow;
	shadow = shadowmodel->model();
	shadow->V.size((div + 1)*(div + 1) * 32);
	GsVec light;
	light.set(lightx, lighty, lightz);
	double height = 0;
	GsVec lightvec;
	GsVec newpoint;
	for (int i = 0; i <= ((div + 1)*(div + 1) * 32 - 1); i++) {
		lightvec.set((real->V[i].x - light.x), (real->V[i].y - light.y),  (real->V[i].z - light.z));
		newpoint.set(((-1)*(real->V[i].z - height) / (lightvec.z / lightvec.x)+ real->V[i].x), ((-1)*(real->V[i].z - height) / (lightvec.z / lightvec.y)+ real->V[i].y), height);
		shadow->V[i] = newpoint;
	}
	
	//Rendering Shadow
	for (int pnum = 0; pnum <= 31; pnum++){
		for (int i = 0; i <= (div-1)*(div+1); i = i + (div+1)) {
			for (int j = 0; j <= (div-1); j++) {
				shadow->F.push().set(i+j+pnum*(div+1)*(div+1), i + 1+j + pnum*(div + 1)*(div + 1), i + (div+2)+j + pnum*(div + 1)*(div + 1));
				shadow->F.push().set(i + (div+2)+j + pnum*(div + 1)*(div + 1), i + (div+1)+j + pnum*(div + 1)*(div + 1), i+j + pnum*(div + 1)*(div + 1));
			}
		}
     }
	if (button == 1) {
		rootg()->add(shadowmodel);
	}
	 
	//Rendering Normal Vectors
	SnLines* s = new SnLines;
	s->color(GsColor::lightblue);
	for (int pnum = 0; pnum <= 31; pnum++) {
		for (int num = 0; num <= (div + 1)*(div + 1)-1; num++) {
			GsVec u;
			u = m->V[sizenumB + num + (pnum * (div + 1)*(div + 1))];
			GsVec v;
			v = m->V[sizenumH + num + (pnum * (div + 1)*(div + 1))];
			s->push(u, v);
		}
	}
	if (check == 1) {
		rootg()->add(s);
	}

	//Rendering Teapot
	for (int pnum = 0; pnum <= 31; pnum++) {
		for (int i = (pnum * (div + 1)*(div + 1)); i <= (div - 1)*(div + 1) + (pnum * (div + 1)*(div + 1)); i = i + (div + 1)) {
			for (int j = 0; j <= (div - 1); j++) {
				real->F.push().set(i + j, i + (div + 1) + j, i + 1 + j);
				real->F.push().set(i + (div + 1) + j, i + (div + 1) + 1 + j, i + 1 + j);
			}
		}
		for (int i = (pnum * (div + 1)*(div + 1)); i <= (div - 1)*(div + 1) + (pnum * (div + 1)*(div + 1)); i = i + (div + 1)) {
			for (int j = 0; j <= (div - 1); j++) {
				real->F.push().set(i + j, i + 1 + j, i + (div + 1) + j);
				real->F.push().set(i + (div + 1) + j, i + 1 + j, i + (div + 1) + 1 + j);
			}
		}
	}
	rootg()->add(realmodel);

	//Change the Mode of Teapot
	/*
	cout << real->geomode() << endl;
	cout << real->mtlmode() << endl;
	*/
	if (change == 1) {
		real->set_mode(real->Smooth, real->NoMtl);
	}
	/*
	cout << real->geomode() << endl;
	cout << real->mtlmode() << endl;
	*/
	
}

// Below is an example of how to control the main loop of an animation:
void MyViewer::run_animation()
{
	/*
	if (_animating) return; // avoid recursive calls
	_animating = true;

	int ind = gs_random(0, rootg()->size() - 1); // pick one child
	SnManipulator* manip = rootg()->get<SnManipulator>(ind); // access one of the manipulators
	GsMat m = manip->mat();

	double frdt = 1.0 / 30.0; // delta time to reach given number of frames per second
	double v = 4; // target velocity is 1 unit per second
	double t = 0, lt = 0, t0 = gs_time();
	do // run for a while:
	{
		while (t - lt<frdt) t = gs_time() - t0; // wait until it is time for next frame
		double yinc = (t - lt)*v;
		if (t>2) yinc = -yinc; // after 2 secs: go down
		lt = t;
		m.e24 += (float)yinc;
		if (m.e24<0) m.e24 = 0; // make sure it does not go below 0
		manip->initial_mat(m);
		render(); // notify it needs redraw
		ws_check(); // redraw now
	} while (m.e24>0);
	_animating = false;
	*/
}

void MyViewer::show_normals(bool b)
{
	// Note that primitives are only converted to meshes in GsModel
	// at the first draw call.

	/*
	GsArray<GsVec> fn;
	SnGroup* r = (SnGroup*)root();
	for ( int k=0; k<r->size(); k++ )
	{	SnManipulator* manip = r->get<SnManipulator>(k);
	SnShape* s = manip->child<SnGroup>()->get<SnShape>(0);
	SnLines* l = manip->child<SnGroup>()->get<SnLines>(1);
	if ( !b ) { l->visible(false); continue; }
	l->visible ( true );
	if ( !l->empty() ) continue; // build only once
	l->init();
	if ( s->instance_name()==SnPrimitive::class_name )
	{	GsModel& m = *((SnModel*)s)->model();
	m.get_normals_per_face ( fn );
	const GsVec* n = fn.pt();
	float f = 0.33f;
	for ( int i=0; i<m.F.size(); i++ )
	{	const GsVec& a=m.V[m.F[i].a]; l->push ( a, a+(*n++)*f );
	const GsVec& b=m.V[m.F[i].b]; l->push ( b, b+(*n++)*f );
	const GsVec& c=m.V[m.F[i].c]; l->push ( c, c+(*n++)*f );
	}
	}
	}
	*/
}

int MyViewer::handle_keyboard(const GsEvent &e)
{
	int ret = WsViewer::handle_keyboard(e); // 1st let system check events
	if (ret) return ret;

	switch (e.key)
	{
	case GsEvent::KeyEsc: gs_exit();
		return 1;
	case 'q': {
		if (state >= 1) {
			rootg()->init();
			state = state - 1;
			build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
			gsout << "Change the number of triangles to " << state*state * 2 * 32 << "." << gsnl;
			redraw();
		}
		else {
			gsout << "0 is the Minimum Number of Triangles!!! " << gsnl;
		}
		return 1;
	}
	case 'w': {
		if (state <= 100) {
			rootg()->init();
			state = state + 1;
			build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
			gsout << "Change the number of triangles to " << state*state * 2 * 32 << "." << gsnl;
			redraw();
		}
		else {
			gsout << "640,000 is the Maximum Number of Triangles!!! " << gsnl;
		}
		return 1;
	}
	default: gsout << "Key pressed: " << e.key << gsnl;
	}

	return 0;
}

int MyViewer::uievent(int e)
{
	switch (e)
	{
	case EvLight:
		rootg()->init();
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvTr1:
		rootg()->init();
		state = 1;
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvTr2:
		rootg()->init();
		state = 2;
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvTr3:
		rootg()->init();
		state = 3;
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvTr4:
		rootg()->init();
		state = 4;
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvTr5:
		rootg()->init();
		state = 5;
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvTr6:
		rootg()->init();
		state = 6;
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvTr7:
		rootg()->init();
		state = 7;
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvTr8:
		rootg()->init();
		state = 8;
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvTr9:
		rootg()->init();
		state = 9;
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvTr10:
		rootg()->init();
		state = 10;
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvTr11:
		rootg()->init();
		state = 50;
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvTr12:
		rootg()->init();
		state = 100;
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;

	case EvNormals:
		rootg()->init();
		if (nstate == 0) {
			nstate = 1;
		}
		else {
			nstate = 0;
		}
		build_scene(nstate, state, cstate,bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvShadow: 
		rootg()->init();
		if (bstate == 0) {
			bstate = 1;
		}
		else {
			bstate = 0;
		}
		build_scene(nstate, state, cstate,bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvCage1:
		on_off= cagehead->visible();
		st1 = gs_time();
		rootg()->init();
		if (cstate == 0) {
			cstate = 1;
		}
		else {
			cstate = 0;
		}
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		fi1 = gs_time();
		if (cstate == 0) {
			gsout << "Cage Rendering Time 1 (OFF) : ";
		}
		else {
			gsout << "Cage Rendering Time 1 (ON) : ";
		}
		gsout << fi1 - st1 << gsnl;
		cagehead->visible(on_off);
		redraw();
		return 1;
	case EvCage2:
		st2 = gs_time();
		cagehead->visible(!cagehead->visible());
		redraw();
		fi2 = gs_time();
		if (cagehead->visible() == 0) {
			gsout << "Cage Rendering Time 2 (OFF) : " ;
		}
		else {
			gsout << "Cage Rendering Time 2 (ON) : ";
		}
		gsout << fi2 - st2 << gsnl;
		return 1;
	case EvSmooth:
		rootg()->init();
		if (smoothing == 0) {
			smoothing = 1;
		}
		else {
			smoothing = 0;
		}
		build_scene(nstate, state, cstate, bstate, smoothing, SliderX->value(), SliderY->value(), SliderZ->value());
		redraw();
		return 1;
	case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}
