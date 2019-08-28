#include <iostream>
int RE, Q[20];
int queen(int r) {
    if(r == 8) { RE ++; return 0; }
    for(int i = 0, j; i < 8; i ++) {
        Q[r] = i;// 此处r表示行，Q[r]的值也就是i表示列，即第r行第i列有皇后
        for(j = 0; j < r; j ++)
            if(Q[j] == i || i-r == Q[j]-j || i+r == Q[j]+j) break;
        if(j == r) queen(r+1);
    }
    return RE;
}
int main() {
    std::cout << queen(0) << std::endl;
    return 0;
}
