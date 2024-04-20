#include <bits/stdc++.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
using namespace std;

#define fir first
#define sec second
#define pb push_back
#define bs basic_string
#define sz(v) (LL)(v).size()
#define cir(x) rep(__tmp, 1, x)
#define rd(x) scanf("%lld", &(x))
#define all(v) (v).begin(), (v).end()
#define erg(i, pre, x) for(LL i = (pre)[x];i;i = a[i].next)
#define rep(i, l, r) for(LL i = (l), _tmp = (r);i <= _tmp;i++)
#define per(i, l, r) for(LL i = (l), _tmp = (r);i >= _tmp;i--)
typedef long long LL;
typedef pair<LL, LL> PII;
const LL INF = 0x3f3f3f3f3f3f3f3f, INF_BIT = 0x3f;

const LL N = 1010, M = 1010;

mt19937_64 _rand(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
#define random(l, r) (_rand() % ((LL)(r) - (LL)(l) + 1) + (LL)(l))
#define random_db(l, r) (random((l) * 1e5, (r) * 1e5) / 1e5)
LL cmp(double a, double b){
    if(fabs(a - b) < 1e-6) return 0;
    else if(a < b) return -1;
    else return 1;
}
#define random_gl(p) (cmp(random_db(0, 1), p) <= 0)
#define random_fracgl(a, b) (random_gl(1.0 * (a) / (b)))
template<typename Val>
Val random_arr(set<Val> s){
    bs<LL> v;
    for(auto x : s) v += x;
    return v[random(0, sz(v) - 1)];
}

void color_text(LL x){  //0:default(white) 1:red 2:dark-red 3/4:blue 5:green 6:dark-green 7/8:yelow 9/10:pink 11/12:blue-green 13/14:gray
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
         if(x == 0 ) SetConsoleTextAttribute(hConsole, (                       FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE));
    else if(x == 1 ) SetConsoleTextAttribute(hConsole, (FOREGROUND_INTENSITY | FOREGROUND_RED));
    else if(x == 2 ) SetConsoleTextAttribute(hConsole, (                       FOREGROUND_RED));
    else if(x == 3 ) SetConsoleTextAttribute(hConsole, (FOREGROUND_INTENSITY | FOREGROUND_BLUE));
    else if(x == 4 ) SetConsoleTextAttribute(hConsole, (                       FOREGROUND_BLUE));
    else if(x == 5 ) SetConsoleTextAttribute(hConsole, (FOREGROUND_INTENSITY | FOREGROUND_GREEN));
    else if(x == 6 ) SetConsoleTextAttribute(hConsole, (                       FOREGROUND_GREEN));
    else if(x == 7 ) SetConsoleTextAttribute(hConsole, (FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN));
    else if(x == 8 ) SetConsoleTextAttribute(hConsole, (                       FOREGROUND_RED | FOREGROUND_GREEN));
    else if(x == 9 ) SetConsoleTextAttribute(hConsole, (FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE));
    else if(x == 10) SetConsoleTextAttribute(hConsole, (                       FOREGROUND_RED | FOREGROUND_BLUE));
    else if(x == 11) SetConsoleTextAttribute(hConsole, (FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN));
    else if(x == 12) SetConsoleTextAttribute(hConsole, (                       FOREGROUND_BLUE | FOREGROUND_GREEN));
    else if(x == 13) SetConsoleTextAttribute(hConsole, (FOREGROUND_INTENSITY));
    else if(x == 14) SetConsoleTextAttribute(hConsole, 0);
}

LL n, m, k, h;
bool a[N][M];

void rdlim(LL &x, LL l, LL r){
    rd(x);
    if(x < l || x > r) puts("值不合法！"), exit(1);
}

set<PII> s;
void gen(){
    cir(k){
        LL tx, ty;
        while(true){
            LL x = random(1, n), y = random(1, m);
            if(s.count({x, y})) continue;
            tx = x, ty = y;
            break;
        }
        s.insert({tx, ty});
        a[tx][ty] = true;
    }
    
    ofstream fout("mine.txt");
    for(auto it : s) fout << it.fir << ' ' << it.sec <<endl;
    rep(i, 1, n){
        rep(j, 1, m) fout << (char)(a[i][j] ? 'x' : ' ') << ' ';
        fout <<endl;
    }
    fout.close();
}

PII jie(string s){
    PII ret;
    LL p = 0;
    for(;p < sz(s) && isdigit(s[p]);p++) ret.fir = ret.fir * 10 + s[p] - '0';
    p++;
    for(;p < sz(s) && isdigit(s[p]);p++) ret.sec = ret.sec * 10 + s[p] - '0';
    if(p != sz(s)) return {-1, -1};
    else return ret;
}

LL cx = 1, cy = 1;

LL st[N][M];  //0：未知，1：揭开，2：标记
const LL fx2[9] = {0, -1, -1, -1, 0, 1, 1, 1, 0}, fy2[9] = {0, -1, 0, 1, 1, 1, 0, -1, -1};
LL subget(LL x, LL y){
    LL ret = 0;
    rep(i, 1, 8){
        LL tx = x + fx2[i], ty = y + fy2[i];
        if(tx < 1 || tx > n) continue;
        if(ty < 1 || ty > n) continue;
        ret += a[tx][ty];
    }
    return ret;
}
LL subtrue(LL x, LL y){
    LL ret = 0;
    rep(i, 1, 8){
        LL tx = x + fx2[i], ty = y + fy2[i];
        if(tx < 1 || tx > n) continue;
        if(ty < 1 || ty > n) continue;
        ret += st[tx][ty] == 2;
    }
    return ret;
}
LL submark(LL x, LL y){
    LL ret = 0;
    rep(i, 1, 8){
        LL tx = x + fx2[i], ty = y + fy2[i];
        if(tx < 1 || tx > n) continue;
        if(ty < 1 || ty > n) continue;
        ret += st[tx][ty] != 1;
    }
    return ret;
}
bool subblank(LL x, LL y){
    rep(i, 1, 8){
        LL tx = x + fx2[i], ty = y + fy2[i];
        if(tx < 1 || tx > n) continue;
        if(ty < 1 || ty > n) continue;
        if(st[tx][ty] == 0) return true;
    }
    return false;
}
void subpnt(LL x, LL y, bool flag = false){
    LL ret = subget(x, y);
         if(ret == 0) color_text(0);
    else if(ret == 1) color_text(6);
    else if(ret == 2) color_text(5);
    else if(ret == 3) color_text(11);
    else if(ret == 4) color_text(3);
    else if(ret == 5) color_text(9);
    else if(ret == 6) color_text(1);
    else if(ret == 7) color_text(2);
    else if(ret == 8) color_text(2);
    if(ret == 0){
        if(x == cx && y == cy) color_text(7), printf("o");
        else printf(" ");
    }else{
        if(flag && ret == subtrue(x, y)) color_text(13);
        if(x == cx && y == cy) color_text(7);
        printf("%lld", ret);
    }
}
void pnt(LL x = 0, LL y = 0){
    if(x == 0 && y == 0){
        printf("     ");
        rep(j, 1, m) printf("%02lld ", j);
        puts("");
        printf("     ");
        rep(j, 1, m) printf("---");
        puts("");
        rep(i, 1, n){
            printf("%02lld | ", i);
            rep(j, 1, m){
                if(st[i][j] == 0) color_text(i == cx && j == cy ? 7 : 13), printf(".");
                else if(st[i][j] == 1) subpnt(i, j, true);
                else if(st[i][j] == 2) color_text(i == cx && j == cy ? 7 : 1), printf("M");
                printf("  ");
                color_text(0);
            }
            puts("");
        }
    }else{
        printf("     ");
        rep(j, 1, m) printf("%02lld ", j);
        puts("");
        printf("     ");
        rep(j, 1, m) printf("---");
        puts("");
        rep(i, 1, n){
            printf("%02lld | ", i);
            rep(j, 1, m){
                if((i == x && j == y) || a[i][j]){
                    color_text(1), printf("x");
                    goto end;
                }
                if(st[i][j] == 1) subpnt(i, j);
                else color_text(13), printf(".");
                end : ;
                printf("  ");
                color_text(0);
            }
            puts("");
        }
    }
}
bool vis[N][N];
queue<PII> q;
const LL fx[5] = {0, 0, 1, 0, -1}, fy[5] = {0, 1, 0, -1, 0};
bool open(LL x, LL y){
    if(a[x][y]) return false;
    rep(i, 1, n) rep(j, 1, m) vis[i][j] = false;
    q.push({x, y});
    while(sz(q)){
        auto it = q.front();
        q.pop();
        LL x = it.fir, y = it.sec;
        st[x][y] = 1;
        rep(i, 1, 4){
            LL tx = x + fx[i], ty = y + fy[i];
            if(tx < 1 || tx > n) continue;
            if(ty < 1 || ty > n) continue;
            if(vis[tx][ty]) continue;
            if(a[tx][ty]) continue;
            if(subget(tx, ty)){ st[tx][ty] = 1; continue; }
            if(st[tx][ty]) continue;
            vis[tx][ty] = true;
            q.push({tx, ty});
        }
    }
    return true;
}
bool iswin(){
    rep(i, 1, n) rep(j, 1, m) if(st[i][j] == 0) return false;
    return true;
}

LL ran = 0;

LL cnt = 0;
void open_block(LL x, LL y){
    auto it = open(x, y);
    if(!it){
        h--;
        if(h == 0){
            system("cls");
            puts("游戏失败！");
            pnt(x, y);
            system("pause");
            exit(0);
        }else{
            st[x][y] = 2, cnt++;
            ran = 2;
            return;
        }
    }
}
void mark_block(LL x, LL y){
    if(st[x][y] == 0) st[x][y] = 2, cnt++;
    else st[x][y] = 0, cnt--;
}

bool can_ent(){
    LL x = cx, y = cy;
    if(st[x][y] == 1 && subblank(x, y)){
        if(subget(x, y) == subtrue(x, y)) return true;
        else if(subget(x, y) == submark(x, y)) return true;
    }
    if(st[x][y]) return false;
    return true;
}
void pnt_cmd(){
    if(cx > 1) color_text(0); else color_text(13);
    printf("W");
    color_text(0);
    printf(",");
    
    if(cy > 1) color_text(0); else color_text(13);
    printf("A");
    color_text(0);
    printf(",");
    
    if(cx < n) color_text(0); else color_text(13);
    printf("S");
    color_text(0);
    printf(",");
    
    if(cy < m) color_text(0); else color_text(13);
    printf("D");
    color_text(0);
    printf(",");
    
    if(can_ent()) color_text(0); else color_text(13);
    printf("Enter");
    color_text(0);
    printf(",");
    
    if(st[cx][cy] != 1) color_text(0); else color_text(13);
    printf("Backspace");
    color_text(0);
    printf(",");
    
    color_text(0);
    printf("T");
    color_text(0);
    printf(",");
    
    if(h > k - cnt) color_text(0); else color_text(13);
    printf("O");
    color_text(0);
    puts("");
}
LL get_tp(char ch){
    if(ch == 'w'){
        if(cx > 1) return 1;
        else return 0;
    }else if(ch == 's'){
        if(cx < n) return 2;
        else return 0;
    }else if(ch == 'a'){
        if(cy > 1) return 3;
        else return 0;
    }else if(ch == 'd'){
        if(cy < m) return 4;
        else return 0;
    }else if(ch == '\r'){
        if(can_ent()) return 5;
        else return 0;
    }else if(ch == '\b'){
        if(st[cx][cy] != 1) return 6;
        else return 0;
    }else if(ch == 't'){
        return 7;
    }else if(ch == 'o'){
        if(h <= k - cnt) return 0;
        else return 8;
    }else return 0;
}

string replay;

bool challenge_mode;
bool display_max;
LL mi[5];
void import_settings(){
    if(system("dir settings.config > NUL 2> NUL")) return;
    ifstream fin("settings.config");
    fin >> challenge_mode;
    fin >> display_max;
    rep(i, 1, 4) fin >> mi[i];
    fin.close();
}
void export_settings(){
    ofstream fout("settings.config");
    fout << challenge_mode <<endl;
    fout << display_max <<endl;
    rep(i, 1, 4) fout << mi[i] << ' ';
    fout <<endl;
    fout.close();
}
void settings(){
    while(true){
        system("cls");
        puts("请输入你要更改的设置编号，输入0返回：");
        printf("- 1：挑战者模式：%s\n", challenge_mode ? "开" : "关");
        printf("- 2：显示最高记录：%s\n", display_max ? "开" : "关");
        LL opt; rd(opt);
        if(opt == 0) break;
        else if(opt == 1) challenge_mode = !challenge_mode;
        else if(opt == 2) display_max = !display_max;
    }
    export_settings();
}

void pnt_time(LL len){
    if(len == INF) printf("还未记录");
    else printf("%02lld分%02lld秒%03lld毫秒", len / 1000 / 60, len / 1000 % 60, len % 1000);
}

void solve(){
    rep(i, 1, 4) mi[i] = INF;
    
    start : ;
    
    system("cls");
    import_settings();
    puts("请输入操作：");
    puts("- 0：打开系统设置");
    printf("- 1：【简单模式】10*10，10个雷");
    if(display_max) printf("  | 最高记录："), pnt_time(mi[1]);
    puts("");
    printf("- 2：【中等模式】20*20，45个雷");
    if(display_max) printf("  | 最高记录："), pnt_time(mi[2]);
    puts("");
    printf("- 3：【均衡模式】25*25，70个雷");
    if(display_max) printf("  | 最高记录："), pnt_time(mi[3]);
    puts("");
    printf("- 4：【困难模式】30*30，120个雷");
    if(display_max) printf(" | 最高记录："), pnt_time(mi[4]);
    puts("");
    puts("- 5：【自定义】自定义地图");
    LL opt; rd(opt);
    if(opt == 0){ settings(); goto start; }
    else if(opt == 1) n = 10, m = 10, k = 10;
    else if(opt == 2) n = 20, m = 20, k = 45;
    else if(opt == 3) n = 25, m = 25, k = 70;
    else if(opt == 4) n = 30, m = 30, k = 120;
    else{
        printf("请输入行数（8~40）：");
        rdlim(n, 8, 40);
        printf("请输入列数（8~40）：");
        rdlim(m, 8, 40);
        LL l = n * m * 0.1, r = n * m * 0.55;
        printf("请输入地雷数（%lld~%lld）：", l, r);
        rdlim(k, l, r);
    }
    if(!challenge_mode){
        printf("请输入生命值（1~100）：");
        rdlim(h, 1, 100);
    }else h = 1;
    LL th = h;
    
    gen();
    
    while(true){
        cx = random(1, n), cy = random(1, m);
        if(a[cx][cy]) continue;
        break;
    }
    LL tcx = cx, tcy = cy;
    
    string tmp; getline(cin, tmp);
    LL stc = INF;
    while(true){
        system("cls");
        
        if(stc != INF){
            LL edc = clock();
            LL len = edc - stc;
            printf("当前用时："), pnt_time(len), puts("");
        }else{
            puts("计时还未开始");
        }
        puts("");
        
        printf("地图：（%lld/%lld，生命值", cnt, k);
        if(ran > 0) ran--, color_text(1);
        printf("%lld", h);
        color_text(0);
        puts("）");
        pnt();
        puts("");
        puts("指令：");
        pnt_cmd();
        
        char ch = getch();
        LL it;
        while((it = get_tp(ch)) == 0) ch = getch();
        stc = min(stc, (LL)clock());
        
        if(it == 1){
            if(cx > 1) cx--;
            replay += 'w';
        }else if(it == 2){
            if(cx < n) cx++;
            replay += 's';
        }else if(it == 3){
            if(cy > 1) cy--;
            replay += 'a';
        }else if(it == 4){
            if(cy < m) cy++;
            replay += 'd';
        }else if(it == 5){
            LL x = cx, y = cy;
            if(st[x][y] == 1){
                if(subget(x, y) == subtrue(x, y)){
                    rep(i, 1, 8){
                        LL tx = x + fx2[i], ty = y + fy2[i];
                        if(tx < 1 || tx > n) continue;
                        if(ty < 1 || ty > n) continue;
                        if(st[tx][ty]) continue;
                        open_block(tx, ty);
                    }
                    replay += 'E';
                    goto end;
                }else if(subget(x, y) == submark(x, y)){
                    rep(i, 1, 8){
                        LL tx = x + fx2[i], ty = y + fy2[i];
                        if(tx < 1 || tx > n) continue;
                        if(ty < 1 || ty > n) continue;
                        if(st[tx][ty]) continue;
                        mark_block(tx, ty);
                    }
                    replay += 'E';
                    goto end;
                }
            }
            open_block(x, y);
            replay += 'E';
        }else if(it == 6){
            LL x = cx, y = cy;
            mark_block(x, y);
            replay += 'M';
        }else if(it == 7){
            LL x, y;
            start2 : ;
            puts("请输入要空降到的方格：");
            rd(x), rd(y);
            if(x < 1 || x > n || y < 1 || y > m){
                puts("不合法方格！");
                goto start2;
            }
            cx = x, cy = y;
            replay += 't' + to_string(x) + ',' + to_string(y);
        }else if(it == 8){
            rep(i, 1, n) rep(j, 1, m){
                if(st[i][j]) continue;
                open_block(i, j);
            }
            replay += 'o';
        }
        
        end : ;
        
        if(iswin()){
            system("cls");
            puts("游戏胜利！");
            pnt();
            LL edc = clock();
            LL len = edc - stc;
            printf("解决总用时："), pnt_time(len), puts("");
            
            if((1 <= opt && opt <= 4) && (challenge_mode)){
                mi[opt] = min(mi[opt], len);
                export_settings();
            }
            
            ofstream fout("replay.txt");
            fout << n << ' ' << m << ' ' << k << ' ' << th << ' ' << tcx << ' ' << tcy <<endl;
            rep(i, 1, n){
                rep(j, 1, m) fout << a[i][j] << ' ';
                fout <<endl;
            }
            fout << replay <<endl;
            fout << len <<endl;
            fout.close();
            
            system("pause");
            return;
        }
    }
}

int main(){
    // freopen("1.in", "r", stdin);  //std=
    // freopen("1.out", "w", stdout);
    // freopen("problem.in", "r", stdin);
    // freopen("problem.out", "w", stdout);
    
    solve();
    return 0;
}