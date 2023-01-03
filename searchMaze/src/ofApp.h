#pragma once

#include "ofMain.h"
#include <iostream>
#include <string.h>
#include <stack>
#include <queue>

#define LENGTH 20

class ofApp : public ofBaseApp{

    struct vertex{
        int row_number;
        int column_number;
        struct vertex* adjacent_vertex;
    };
    struct vertex** miro;
    
    struct vertex_dot{
        int x;
        int y;
        //0이면 visit x
        //1이면 red dot
        //2이면 blue dot
        int visited;
    };
    struct vertex_dot** dot_miro;
    
    
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
    int row;
    int column;
    int read_flag;
    int current_row;
    int current_column;
    int x_pos;
    int y_pos;
    int x_init_pos;
    int draw_miro_flag;
    int dfs_flag;
    int bfs_flag;
    int dfs_end_flag;
    int bfs_end_flag;
    int** visited_miro;
    int draw_clear_flag;
    vector <string> input;
    stack<struct vertex> stack;
    void readFile(void);
    void add_edge(int i, int j, int a, int b);
    void FreeMemory(void);
    void visit_init(void);
    void DFS(int i, int j);
    void BFS(int i, int j);
    void drawMiro(void);
    void drawRoot(void);
    void draw_clear(void);
};
