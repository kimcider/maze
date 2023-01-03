# maze
미로 생성 및 찾기

서강대학교 컴퓨터공학 설계 및 실험과목의 프로젝트 중 미로찾기의 제출물.

### 1. makeMaze
미로를 제작하는 프로그램  
- makeMaze파일을 실행한 후, 만들고자 하는 미로의 높이와 너비를 입력해주면 완전미로파일인 miro.maze파일을 만든다.
- 좌측 상단을 시작점으로, 우측 하단을 탈출구로 한다.
<img width="558" alt="image" src="https://user-images.githubusercontent.com/105146508/210338461-6a620fb5-b5d7-4980-8d81-3ab2fb764b32.png">

### 2. searchMaze
미로를 탐색하는 프로그램
- OpenFrameWorks상에서 동작하는 프로그램이다.
- OpenFrameWorks의 새 프로젝트를 만든 후, src파일을 searchMaze/src로 변경하면 실행이 가능하다. 
- 프로젝트 내의 bin/data폴더 안에 makeMaze에서 생성한 .maz확장자를 가지는 파일을 넣어줘야 길을 찾을 미로의 선택이 가능하다.  
  searchMaze/bin/data에 몇 개의 미로 샘플을 넣어두었다. 이 미로들을 그대로 활용해도 무방하다.
  
- 사용방법
  실행하기 전 키보드가 영문/소문자인 상태에서 실행할 것
  - 실행 후, 길을 찾을 미로를 선택한다.
  - 'd': DFS를 이용한 미로탐색
  - 'b': BFS를 이용한 미로탐색
  - 'r': 새로운 미로 선택
  - 'q': 프로그램 종료

- 길을 찾는 과정에서 지나간 길은 빨간색 선으로, 최단경로는 파란색 선으로 표시된다.  
![image](https://user-images.githubusercontent.com/105146508/210338369-edaf3d61-75de-475a-b4c1-787729687bb7.png)
