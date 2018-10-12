
# include "my_viewer.h"

# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>

# include <sigogl/ws_run.h>

# include <vector>
#include <math.h>

MyViewer::MyViewer ( int x, int y, int w, int h, const char* l ) : WsViewer(x,y,w,h,l)
{
	limit_num = 0;
	_nbut=0;
	_animating=false;
	add_ui ();
	build_scene (limit_num);
}

void MyViewer::add_ui ()
{
	UiPanel *p, *sp;
	UiManager* uim = WsWindow::uim();
	p = uim->add_panel ( "", UiPanel::HorizLeft );
	p->add ( new UiButton ( "View", sp=new UiPanel() ) );
	{	UiPanel* p=sp;
		p->add ( _nbut=new UiCheckButton ( "Normals", EvNormals ) ); 
	}
	p->add ( new UiButton ( "Animate", EvAnimate ) );
	p->add ( new UiButton ( "Exit", EvExit ) ); p->top()->separate();
}

void MyViewer::add_model ( SnShape* s, GsVec p )
{
	SnManipulator* manip = new SnManipulator;
	GsMat m;
	m.translation ( p );
	manip->initial_mat ( m );

	SnGroup* g = new SnGroup;
	SnLines* l = new SnLines;
	l->color(GsColor::orange);
	g->add(s);
	g->add(l);
	manip->child(g);

	rootg()->add(manip);
}

void MyViewer::build_scene(int NUM)
{
	//Initialization

	SnModel* original_model;
	GsModel* original;
	original_model = new SnModel;
	original = original_model->model();
	int limit = NUM;

	//Loading Object
	const char* file = "sphere.obj";
	original->load(file);
	//gsout << "V:" << original->V.size() << gsnl;
	//gsout << "F:" << original->F.size() << gsnl;
	original_model->color(GsColor::gray);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	if (limit <= 0) {

		//Original Model Rendering
		rootg()->add(original_model);

	}
	else {

		//Data of Each Objects

		//**sphere.obj**
		
		const int ver_num = 62;
		const int face_num = 120;
		

		//**cow.obj**
		/*
		const int ver_num = 2903;
		const int face_num = 5804;
		*/

		std::vector<int> edges[ver_num];
		std::vector<int> faces[ver_num];

		int edge_size;

		//////////////////////////////////////////////////////////////////////////////////////////////////////

		//Construct Edge Array
		for (int i = 0; i < face_num; i++) {
			int V_indexA = original->F[i].a;
			int V_indexB = original->F[i].b;
			int V_indexC = original->F[i].c;
			edges[V_indexA].push_back(V_indexB);
			edges[V_indexA].push_back(V_indexC);
			edges[V_indexB].push_back(V_indexA);
			edges[V_indexB].push_back(V_indexC);
			edges[V_indexC].push_back(V_indexA);
			edges[V_indexC].push_back(V_indexB);
			faces[V_indexA].push_back(i);
			faces[V_indexB].push_back(i);
			faces[V_indexC].push_back(i);
		}

		//''CHECK''
		/*
		edge_size = edges[28].size();
		for (int i = 0; i < edge_size; i++) {
			gsout <<"edge[28]["<<i<<"]:"<< edges[28][i] << gsnl;
		}
		*/

		//Detect the Duplicates (edge)

		for (int i = 0; i < ver_num; i++) {
			edge_size = edges[i].size();
			for (int j = 0; j < edge_size; j++) {
				for (int k = j + 1; k < edge_size; k++) {
					if (edges[i][j] == edges[i][k]) {
						edges[i][k] = 99999;
					}
				}
			}
		}

		//''CHECK''
		/*
		edge_size = edges[28].size();
		for (int i = 0; i < edge_size; i++) {
		gsout <<"Detected-edge[28]["<<i<<"]:"<< edges[28][i] << gsnl;
		}
		*/

		//Sort Edge Array

		for (int k = 0; k < ver_num; k++) {
			edge_size = edges[k].size();
			for (int j = 1; j < edge_size; j++) {
				int key = edges[k][j];
				int i = j - 1;
				while (i >= 0 && edges[k][i] > key) {
					edges[k][i + 1] = edges[k][i];
					i = i - 1;
				}
				edges[k][i + 1] = key;
			}
		}

		//''CHECK''
		/*
		int count = 0;
		for (int j = 0; j < ver_num; j++) {
			edge_size = edges[j].size();
			for (int i = 0; i < edge_size; i++) {
				if (edges[j][i] != 99999) {
					//gsout << "Sorted-edge["<<j<<"][" << i << "]:" << edges[j][i] << gsnl;
					count = count + 1;
				}
			}
		}
		gsout << "Sum Edge:" << count << gsnl;//ans. 360
		*/

		/////////////////////////////////////////////////////////////////////////////////////////////////////

		//Error Calculation (Vertex-Vertex Distance)
		
		GsArray<float> error_array;
		GsArray<float> sort_error_array;
		GsArray<int> order;
		GsArray<int> sort_order;
		GsArray<int> gone;
		float error;
		float max_error;
		
		for (int j = 0; j < ver_num; j++) {
			edge_size = edges[j].size();
			max_error = 0;
			for (int i = 0; i < edge_size; i++) {
				if (edges[j][i] != 99999) {
					error = dist((original->V[j]), (original->V[edges[j][i]]));
					if (error > max_error) {
						max_error = error;
					}
				}
			}
			error_array.push() = max_error;
			sort_error_array.push() = max_error;
		}
		
		//''Check''
		/*
		for (int i = 0; i < ver_num; i++) {
			gsout<< "error_array["<<i<<"]: "<< error_array[i] << gsnl;
		}
		*/
		
		//Construct Order Array

		for (int i = 0; i < ver_num; i++) {
			order.push() = i;
			sort_order.push() = i;
		}

		//Sorting Error Array

		int order_local;
		for (int j = 1; j < ver_num; j++) {
			float key = sort_error_array[j];
			order_local = order[j];
			int i = j - 1;
			while (i >= 0 && sort_error_array[i] > key) {
				sort_error_array[i + 1] = sort_error_array[i];
				order[i + 1] = order[i];
				i = i - 1;
			}
			sort_error_array[i + 1] = key;
			order[i + 1] = order_local;
		}
		for (int i = 0; i < ver_num; i++) {
			for (int j = 0; j < ver_num; j++) {
				if (sort_error_array[i] == error_array[j] && sort_order[j] != 99999) {
					order[j] = i;
					sort_order[j] = 99999;
					break;
				}
			}

		}
		
		//''Check''
		/*
		for (int i = 0; i < ver_num; i++) {
		gsout<< "sort_error_array["<<i<<"]: "<< sort_error_array[i] << gsnl;
		}
		*/
		/*
		for (int i = 0; i < ver_num; i++) {
			gsout << "error_array[" << i << "]: " << error_array[i] <<" : "<<order[i]<< gsnl;
		}
		*/

		/////////////////////////////////////////////////////////////////////////////////////////////////////

		//Pushing Triangles with No Change

		int ind;

		//Getting the Faces that will be disappeared
		GsArray<int> out_array;
		int sum_out_face = 0;
		for (int j = 0; j < limit; j++) {
			for (int k = 0; k < ver_num; k++) {
				if (order[k] == j) {
					ind = k;
					break;
				}
			}
			int face_size = faces[ind].size();
			for (int i = 0; i < face_size; i++) {
				out_array.push() = faces[ind][i];
			}
			sum_out_face = sum_out_face + face_size;
		}

		//''Check''
		/*
		for (int i = 0; i < sum_out_face; i++) {
			gsout << "out_array[" << i << "]:" << out_array[i] << gsnl;
		}
		*/

		//Detect Duplicate Face Index
		int F_index;
		for (int i = 0; i < sum_out_face; i++) {
			F_index = out_array[i];
			for (int j = i + 1; j < sum_out_face; j++) {
				if (out_array[j] == F_index) {
					out_array[j] = 99999;
				}
			}
		}

		//''Check''
		/*
		for (int i = 0; i < sum_out_face; i++) {
		gsout << "out_array[" << i << "]:" << out_array[i] << gsnl;
		}
		*/

		//Sort Out_Array
		int key;
		for (int j = 1; j < sum_out_face; j++) {
			key = out_array[j];
			int i = j - 1;
			while (i >= 0 && out_array[i] > key) {
				out_array[i + 1] = out_array[i];
				i = i - 1;
			}
			out_array[i + 1] = key;
		}

		//''Check''
		/*
		for (int i = 0; i < sum_out_face; i++) {
		gsout << "out_array[" << i << "]:" << out_array[i] << gsnl;
		}
		*/
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////

		//Modification Process
		
		SnModel* modify_model;
		GsModel* modify;
		modify_model = new SnModel;
		modify = modify_model->model();
		modify->V.size(ver_num);
		modify->V = original->V;

		//Getting the Verticies that will be disappeared
		GsArray<int> vanish_array;
		for (int j = 0; j < limit; j++) {
			for (int k = 0; k < ver_num; k++) {
				if (order[k] == j) {
					ind = k;
					break;
				}
			}
			vanish_array.push() = ind;
		}


		//''Check''
		/*
		for (int i = 0; i < limit; i++) {
		gsout << "vanish_array[" << i << "]:" << vanish_array[i] << gsnl;
		}
		*/

		GsArray<int> id_array;
		GsArray<int> change_array;
		for (int i = 0; i < ver_num;i++) {
			id_array.push() = i;
			change_array.push() = i;
		}

		//Computing the nearest Verticies
		float min_len;
		float len;
		int min_ind;
		int count = 0;
		for (int k = 0; k < limit; k++) {
			min_len = 99999;
			edge_size = edges[vanish_array[k]].size();
			for (int i = 0; i < edge_size; i++) {
				if (edges[vanish_array[k]][i] != 99999 && change_array[edges[vanish_array[k]][i]] != 99999) {
					len = dist(modify->V[vanish_array[k]], modify->V[edges[vanish_array[k]][i]]);
					if (min_len > len) {
						min_len = len;
						min_ind = edges[vanish_array[k]][i];
					}
				}
			}
			//gsout<<"id: "<< vanish_array[k]<<" ¨ "<< "id: " << min_ind << gsnl;
			change_array[vanish_array[k]] = 99999;
			//gsout << "cod: " << modify->V[vanish_array[k]] << " ¨ " << "cod: " << modify->V[min_ind] << gsnl;
			modify->V[vanish_array[k]] = modify->V[min_ind];
			//gsout << "cod: " << modify->V[vanish_array[k]] << gsnl;
			
			//for (int h = 0; h < ver_num; h++) {
				for (int e = 0; e < ver_num; e++) {
					if (id_array[e] == vanish_array[k]) {
						id_array[e] = min_ind;
					}
				}
			//}
			
			count = count + 1;
		}


		//''Check''
		
		
		/*
		for (int i = 0; i < ver_num; i++) {
		gsout << "id_array[" << i << "]:" << id_array[i] << gsnl;
		}
		for (int i = 0; i < ver_num; i++) {
			gsout << "change_array[" << i << "]:" << change_array[i] << gsnl;
		}
		gsout << "count: " << count << gsnl;
		*/

		//////////////////////////////////////////////////////////////////////////////////////////////////////

		//Hole Object
		SnModel* next_model;
		GsModel* next;
		next_model = new SnModel;
		next = next_model->model();
		next->V.size(ver_num);
		next->V = original->V;

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		/*
		//Pushing Triangle Data
		int check = 0;
		for (int i = 0; i < face_num; i++) {
			if (out_array[check] == 99999) {
				break;
			}
			if (i == out_array[check]) {
				check = check + 1;
				modify->F.push().set(original->F[i].a, original->F[i].b, original->F[i].c);
			}
			else {
				next->F.push().set(original->F[i].a, original->F[i].b, original->F[i].c);
			}
		}
		*/
		//Pushing Triangle Data
		int check = 0;
		for (int i = 0; i < face_num; i++) {
			if (out_array[check] == 99999) {
				break;
			}
			if (i == out_array[check]) {
				check = check + 1;
				modify->F.push().set(id_array[original->F[i].a], id_array[original->F[i].b], id_array[original->F[i].c]);
			}
			else {
				next->F.push().set(original->F[i].a, original->F[i].b, original->F[i].c);
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////

		//''Check''
		/*
		for (int i = 0; i < ver_num; i++) {
		gsout << "V[" << i << "]:" << modify->V[i] << gsnl;
		}
		*/

		//Hole Object Rendering
		rootg()->add(next_model);

		//Modify Object Rendering
		rootg()->add(modify_model);

	}
	
}

// Below is an example of how to control the main loop of an animation:
void MyViewer::run_animation ()
{
	if ( _animating ) return; // avoid recursive calls
	_animating = true;
	
	int ind = gs_random ( 0, rootg()->size()-1 ); // pick one child
	SnManipulator* manip = rootg()->get<SnManipulator>(ind); // access one of the manipulators
	GsMat m = manip->mat();

	double frdt = 1.0/30.0; // delta time to reach given number of frames per second
	double v = 4; // target velocity is 1 unit per second
	double t=0, lt=0, t0=gs_time();
	do // run for a while:
	{	while ( t-lt<frdt ) t = gs_time()-t0; // wait until it is time for next frame
		double yinc = (t-lt)*v;
		if ( t>2 ) yinc=-yinc; // after 2 secs: go down
		lt = t;
		m.e24 += (float)yinc;
		if ( m.e24<0 ) m.e24=0; // make sure it does not go below 0
		manip->initial_mat ( m );
		render(); // notify it needs redraw
		ws_check(); // redraw now
	}	while ( m.e24>0 );
	_animating = false;
}

void MyViewer::show_normals ( bool b )
{
	// Note that primitives are only converted to meshes in GsModel
	// at the first draw call.
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
}

int MyViewer::handle_keyboard ( const GsEvent &e )
{
	int ret = WsViewer::handle_keyboard ( e ); // 1st let system check events
	if ( ret ) return ret;

	switch ( e.key ){	
	case GsEvent::KeyEsc : gs_exit(); return 1;

	case 'a': {
		rootg()->init();
		limit_num = limit_num - 1;
		if (limit_num < 0) {
			limit_num = 0;
		}
		build_scene(limit_num);
		gsout << "Change the number of verticies to " << 62-limit_num << "." << gsnl;
		redraw();
		return 1;
	}

	case 's': {
		rootg()->init();
		limit_num = limit_num + 1;
		build_scene(limit_num);
		gsout << "Change the number of verticies to " << 62 - limit_num << "." << gsnl;
		redraw();
		return 1;
	}

	case 'n' : { 
		//bool b=!_nbut->value(); _nbut->value(b); show_normals(b); return 1; 
	}
	default: gsout<<"Key pressed: "<<e.key<<gsnl;
	}

	return 0;
}

int MyViewer::uievent ( int e )
{
	switch ( e )
	{	case EvNormals: show_normals(_nbut->value()); return 1;
		case EvAnimate: run_animation(); return 1;
		case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}
