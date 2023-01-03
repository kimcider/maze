#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    miro = NULL;
    ofSetFrameRate(30);
    ofSetBackgroundAuto(false);
    ofBackground(0,0,0);
    read_flag = 0;
    current_row = 0;
    current_column = 0;
    x_init_pos = 20;
    x_pos = x_init_pos;
    y_pos = x_init_pos;
    draw_miro_flag=0;
    dfs_flag=0;
    bfs_flag=0;
    dfs_end_flag=0;
    bfs_end_flag=0;
    row=0;
    column=0;
    readFile();
}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::drawMiro(void){
    //miro 그리기
    y_pos=0;
    int cnt = 0;
    for(int i=0;i<input.size();i++){
        if(i % 2 == 0){
            y_pos += LENGTH;
        }
        x_pos=x_init_pos;
        for(int j=0;input[i][j];j++){
            if(input[i][j]=='+')continue;
            cnt++;
            if(input[i][j] == '-'){
                ofDrawLine(x_pos,y_pos,x_pos+LENGTH,y_pos);
                x_pos += LENGTH;
            }
            else if(input[i][j] == '|'){
                ofDrawLine(x_pos, y_pos, x_pos, y_pos+LENGTH);
            }
            else if(input[i][j] == ' '){
                if(j % 2 == 1 ) {
                    x_pos += LENGTH;
                }
            }
        }
    }
    draw_miro_flag ++;
}
//--------------------------------------------------------------
int ff=0;
void ofApp::draw(){
    ofSetLineWidth(5);
    if(read_flag) {
        drawMiro();
    }
    if(dfs_flag){
        drawRoot();
    }
    if(bfs_flag){
        drawRoot();
    }
}
 
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'd'){
        bfs_flag = 0;
        dfs_flag = 0;
        visit_init();
        dfs_end_flag = 0;
        DFS(0,0);
        dfs_flag = 1;
    }
    if(key == 'b'){
        dfs_flag = 0;
        bfs_flag = 0;
        visit_init();
        bfs_end_flag = 0;
        BFS(0,0);
        bfs_flag = 1;
        
    }
    if(key == 'r'){
        ofSetBackgroundAuto(true);
        FreeMemory();
        
        setup();
    }
    if(key == 'q'){
        FreeMemory();
        _Exit(0);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::readFile(void){
    ofFileDialogResult openFileResult = ofSystemLoadDialog("Select .maz file");
    string filePath;
    size_t pos;
    // Check whether the user opened a file
    if (openFileResult.bSuccess) {
        ofLogVerbose("User selected a file");

        //We have a file, check it and process it
        string fileName = openFileResult.getName();
        filePath = openFileResult.getPath();
        printf("Open\n");
        pos = filePath.find_last_of(".");
        if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "maz") {

            ofFile file(fileName);

            if (!file.exists()) {
                cout << "Target file does not exists." << endl;
            }
            else {
                cout << "We found the target file." << endl;
            }

            ofBuffer buffer(file);
            
            int input_flag = 0;

            // Idx is a variable for index of array.
            int idx = 0;

            // Read file line by line
            int cnt = 0;
            
            
            // TO DO
            for (auto line : buffer.getLines()) {
                input.push_back(line);
            }
            row = ((int)input.size() - 1 ) / 2;
            int column_counter = 0;
            while(true){
                if(input[0][column_counter]){
                    column_counter++;
                }
                else break;
            }
            column = ( column_counter - 1 ) / 2;
  
            //vertex 초기화
            miro=(struct vertex**)malloc(sizeof(vertex*) * row);
            for(int i = 0; i < row ; i++ ){
                miro[i] = (struct vertex*)malloc(sizeof(vertex) * column);
                for(int j = 0; j < column; j++){
                    miro[i][j].row_number=i;
                    miro[i][j].column_number=j;
                    miro[i][j].adjacent_vertex=NULL;
                }
            }
            
            
            //edge 초기화
            for(int i = 1; i < input.size() ;i+=2 ){
                int j=1;
                while(input[i][j]){
                    int a=((i-1)/2);
                    int b=((j-1)/2);
                    if(input[i-1][j] == ' '){
                        add_edge(a,b,a-1,b);
                    }
                    if(input[i+1][j] == ' '){
                        add_edge(a,b, a+1, b);
                    }
                    if(input[i][j+1] == ' '){
                        add_edge(a, b, a, b+1);
                    }
                    if(input[i][j-1] == ' '){
                        add_edge(a, b, a, b-1);
                    }
                    j += 2;
                }
            }
            
            
            //visit을 위한 visited_miro초기화
            visited_miro=(int**)malloc(sizeof(int*)*row);
            for(int i = 0; i < row; i++){
                visited_miro[i]=(int*)malloc(sizeof(int)*column);
                for(int j = 0; j < column; j++){
                    visited_miro[i][j]=0;
                }
            }
            //drawLine()를위한 dot_miro초기화
            dot_miro = (struct vertex_dot**)malloc(sizeof(vertex_dot*)* row);
            for(int i = 0; i< row; i++){
                dot_miro[i] = (struct vertex_dot*)malloc(sizeof(vertex_dot) * column);
                for(int j = 0; j < column; j++){
                    //        dot_list[exist_dot_number]->x=20 * ( j + 2 ) - 12;
                    //        dot_list[exist_dot_number]->y=20 * ( i + 2 ) - 12;
                    
                    dot_miro[i][j].x = 20 * ( j + 2 ) - 12;
                    dot_miro[i][j].y = 20 * ( i + 2 ) - 12;
                    dot_miro[i][j].visited = 0;
                }
            }
            
            read_flag = 1;
        }
        else {
            printf("  Needs a '.maz' extension\n");
        }
    }
}

void ofApp::add_edge(int i, int j, int a, int b){
    struct vertex* temp = (struct vertex *) malloc(sizeof(struct vertex));
    temp->row_number = a;
    temp->column_number = b;
    temp->adjacent_vertex = NULL;
    
    if(miro[i][j].adjacent_vertex){
        temp->adjacent_vertex = miro[i][j].adjacent_vertex;
    }
    miro[i][j].adjacent_vertex = temp;
}

void ofApp::FreeMemory(void){
    for(int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            struct vertex* temp = miro[i][j].adjacent_vertex;
            if(temp){
                struct vertex* pre = NULL;
                while(temp -> adjacent_vertex){
                    pre = temp;
                    temp = temp -> adjacent_vertex;
                    free(pre);
                }
            }
        }
        free(miro[i]);
        free(dot_miro[i]);
    }
    free(miro);
    free(dot_miro);
    input.clear();
}


void ofApp::DFS(int i, int j){
    visited_miro[i][j] = 1;
    dot_miro[i][j].visited=1;
    int stay=1;
    
    //도착지 도착
    if(i == row - 1 && j == column - 1){
        dfs_end_flag=1;
        dot_miro[i][j].visited = 2;
        return;
    }
    
    struct vertex* temp = miro[i][j].adjacent_vertex;
    while(temp){
        if(visited_miro[temp->row_number][temp->column_number] == 0 && dfs_end_flag==0){
            DFS(temp->row_number, temp->column_number);
        }
        
        if(dfs_end_flag){
            break;
        }
        else {
            temp = temp->adjacent_vertex;
        }
    }
    
    if(dfs_end_flag==0){
        stay=0;
    }
    if(stay == 1){
        dot_miro[i][j].visited = 2;
    }
}

void ofApp::BFS(int i, int j){
    int memory[row][column][2];
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            memory[i][j][0] = -99;  //before_row
            memory[i][j][1] = -99;  //before_col
        }
    }
    
    struct vertex *temp = &miro[i][j];
    queue<struct vertex*> que;
    printf("%d %d\n",temp->row_number,temp->column_number);
    visited_miro[i][j] = 1;
    dot_miro[i][j].visited = 1;
    que.push(temp);
    while(que.size() != 0){
        temp = que.front();
        que.pop();
        int before_row = temp->row_number;
        int before_col = temp->column_number;
        
        temp=miro[temp->row_number][temp->column_number].adjacent_vertex;
        
        while(temp){
            if(!visited_miro[temp->row_number][temp->column_number]){
                memory[temp->row_number][temp->column_number][0] = before_row;
                memory[temp->row_number][temp->column_number][1] = before_col;
                
                printf("%d %d\n",temp->row_number,temp->column_number);
                que.push(temp);
                visited_miro[temp->row_number][temp->column_number] = 1;
                dot_miro[temp->row_number][temp->column_number].visited = 1;
                if(temp->row_number == row - 1 && temp->column_number == column - 1){
                    bfs_end_flag = 1;
                    break;
                }
            }
            temp = temp -> adjacent_vertex;
        }
        if(bfs_end_flag){
            break;
        }
    }
    int temp_row = row - 1;
    int temp_col = column - 1;
    dot_miro[temp_row][temp_col].visited = 2;
    while(true){
        int before_row = memory[temp_row][temp_col][0];
        int before_col = memory[temp_row][temp_col][1];
        if(before_col < 0 || before_row < 0) break;
        dot_miro[before_row][before_col].visited = 2;
        temp_row = before_row;
        temp_col = before_col;
        
        
    }
}

void ofApp::drawRoot(void){
    for (int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if(dot_miro[i][j].visited != 0){
                struct vertex* temp=miro[i][j].adjacent_vertex;
                while(temp){
                    int a = temp -> row_number;
                    int b = temp -> column_number;
                    if(dot_miro[a][b].visited == 0){
                        temp = temp -> adjacent_vertex;
                        continue;
                    }
                    
                    ofSetColor(255, 0, 0);
                    if(dot_miro[i][j].visited == 2 && dot_miro[a][b].visited == 2){//인접이 파란색
                        ofSetColor(0, 0, 255);
                    }
                    ofDrawLine(dot_miro[i][j].x, dot_miro[i][j].y, dot_miro[a][b].x, dot_miro[a][b].y);
                    
                    
                    temp = temp -> adjacent_vertex;
                }
            }
        }
    }
    ofSetColor(255, 255, 255);
}

void ofApp::visit_init(void){
    ofBackground(0, 0, 0);
    for(int i = 0; i< row; i++){
        for(int j = 0; j < column; j++){
            visited_miro[i][j]=0;
            dot_miro[i][j].x = 20 * ( j + 2 ) - 12;
            dot_miro[i][j].y = 20 * ( i + 2 ) - 12;
            dot_miro[i][j].visited = 0;
        }
    }
}
