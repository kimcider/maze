//
//  main.c
//  miro
//
//  Created by 김병천 on 2022/11/28.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define INF 999

typedef struct{
    int right_wall;
    int down_wall;
    int num;
}space;
space ** miro;

int width;
int height;
FILE*fp;
void init_miro(void);
void create_miro_by_binary_algorithm(void);
void create_miro_by_eller_algorithm(void);
void print_miro_to_file(void);
void print_miro_in_xcode(void);
int main(int argc, const char * argv[]) {
    srand(time(NULL));

    printf("width: ");
    scanf("%d",&width);
    printf("height: ");
    scanf("%d",&height);
    
    init_miro();
    //create_miro_in_binary_algorithm();
    create_miro_by_eller_algorithm();
    print_miro_in_xcode();
    print_miro_to_file();
    
    for(int i=0;i<height;i++){
        free(miro[i]);
    }
    free(miro);
}
void init_miro(void){
    miro=(space**)malloc(sizeof(space*)*height);
    for(int i=0;i<height;i++){
        miro[i]=(space*)malloc(sizeof(space)*width);
    }
    int counter=0;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            miro[i][j].down_wall=1;
            miro[i][j].right_wall=1;
            miro[i][j].num=counter++;
        }
    }
    
}
void create_miro_by_binary_algorithm(void){
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int n=rand()%2;
            if(n==0) miro[i][j].right_wall=0;
            else miro[i][j].down_wall=0;
        }
    }
    for(int i=0;i<height;i++){
        miro[i][width-1].right_wall=1;
        miro[i][width-1].down_wall=0;
    }
    for(int i=0;i<width;i++){
        miro[height-1][i].right_wall=0;
        miro[height-1][i].down_wall=1;
        
    }
    miro[height-1][width-1].down_wall=1;
    miro[height-1][width-1].right_wall=1;
    
}
void print_miro_to_file(void){
    fp=fopen("miro.maz","w");
    
    for(int i=0;i<width;i++) {
        if(i==0)fprintf(fp,"+-+");
        else fprintf(fp,"-+");
    }
    fprintf(fp,"\n");
    for(int i=0;i<height;i++){
        fprintf(fp,"|");
        for(int j=0;j<width;j++){
            fprintf(fp," ");
            if(miro[i][j].right_wall==1)fprintf(fp,"|");
            else fprintf(fp," ");
        }
        fprintf(fp,"\n+");
        for(int j=0;j<width;j++){
            if(i==height-1){
                fprintf(fp,"-+");
            }else{
                if(miro[i][j].down_wall==1)fprintf(fp,"-+");
                else fprintf(fp," +");
            }
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}
void print_miro_in_xcode(void){
    for(int i=0;i<width;i++) {
        if(i==0)printf("+-+");
        else printf("-+");
    }
    printf("\n");
    for(int i=0;i<height;i++){
        printf("|");
        for(int j=0;j<width;j++){
            printf(" ");
            if(miro[i][j].right_wall==1)printf("|");
            else printf(" ");
        }
        printf("\n+");
        
        for(int j=0;j<width;j++){
            if(i==height-1){
                printf("-+");
            }else{
                if(miro[i][j].down_wall==1)printf("-+");
                else printf(" +");
            }
            
        }
        printf("\n");
    }
}
//방을 뚫을떄 눈으로 봤을 때 규칙성이 보이면 잘못 만들었을 가능성이 높음
void create_miro_by_eller_algorithm(void){
    for(int h=0;h<height;h++){
        for(int w=0; w < width-1; w++){
            if(miro[h][w].num != miro[h][w+1].num){
                int ran = rand() % 2;
                if(ran==0) continue;
                else{
                    miro[h][w].right_wall=0;
                    int small_num=9999;
                    int big_num=9999;
                    if(miro[h][w].num<miro[h][w+1].num){
                        small_num=miro[h][w].num;
                        big_num=miro[h][w+1].num;
                    }
                    else{
                        small_num=miro[h][w+1].num;
                        big_num=miro[h][w].num;
                    }
                    for(int h=0;h<height;h++){
                        for(int w=0;w<width;w++){
                            if(miro[h][w].num==big_num)miro[h][w].num=small_num;
                        }
                    }
                }
            }
        }
        int first = 0;
        int last=0;
        while(first<width){
            for(int j = first; j < width; j++){
                if(miro[h][first].num == miro[h][j].num) last = j;
                else break;
            }
            
            int flag=0;
            for (int j = first; j <= last; j++) {
                if (j < width && miro[h][j].down_wall == 1 && miro[h][j + 1].down_wall == 1) {
                    int ran = rand() % 2;
                    if (ran == 0) {
                        flag=1;
                        miro[h][j].down_wall = 0;
                        if(h+1<height){
                            miro[h + 1][j].num = miro[h][j].num;
                        }
                    }
                }
            }
            if(flag==0){
                int rand_num = rand() % (last - first + 1);
                int break_num=first + rand_num;
                miro[h][break_num].down_wall=0;
                if(h + 1 < height) miro[h + 1][break_num].num=miro[h][break_num].num;
            }
            
            first = last + 1;
        }
    }
    for(int w = 0; w < width - 1; w++){
        if(miro[height - 1][w].num!=miro[height-1][w+1].num){
            miro[height - 1][w].right_wall=0;
            int small_num=9999;
            int big_num=9999;
            if(miro[height-1][w].num<miro[height-1][w+1].num){
                small_num=miro[height-1][w].num;
                big_num=miro[height-1][w+1].num;
            }
            else{
                small_num=miro[height-1][w+1].num;
                big_num=miro[height-1][w].num;
            }
            for(int i=0;i<height;i++){
                for(int j=0;j<width;j++){
                    if(miro[i][j].num==big_num)miro[i][j].num=small_num;
                }
            }
        }
    }
}
