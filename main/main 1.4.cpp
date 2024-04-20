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
    if(x < l || x > r) puts("ֵ���Ϸ���"), exit(1);
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

LL st[N][M];  //0��δ֪��1���ҿ���2�����
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

LL cnt = 0;
void open_block(LL x, LL y){
    auto it = open(x, y);
    if(!it){
        h--;
        if(h == 0){
            system("cls");
            puts("��Ϸʧ�ܣ�");
            pnt(x, y);
            system("pause");
            return;
        }else{
            puts("��ȵ����ˣ�");
            st[x][y] = 2, cnt++;
            sleep(1);
            return;
        }
    }
}

string replay;

void solve(){
    system("cls");
    
    printf("������������8~40����");
    rdlim(n, 8, 40);
    
    printf("������������8~40����");
    rdlim(m, 8, 40);
    
    LL l = n * m * 0.1, r = n * m * 0.55;
    printf("�������������%lld~%lld����", l, r);
    rdlim(k, l, r);
    
    printf("����������ֵ��1~100����");
    rdlim(h, 1, 100);
    LL th = h;
    
    gen();
    
    string tmp; getline(cin, tmp);
    LL stc = INF;
    while(true){
        system("cls");
        
        if(stc != INF){
            LL edc = clock();
            LL len = edc - stc;
            printf("��ǰ��ʱ��%02lld��%02lld��%03lld����\n", len / 1000 / 60, len / 1000 % 60, len % 1000);
        }else{
            puts("��ʱ��δ��ʼ");
        }
        puts("");
        
        printf("��ͼ����%lld/%lld������ֵ%lld��\n", cnt, k, h);
        pnt();
        puts("");
        puts("ָ�");
        puts("1. WASD");
        puts("2. Enter/Backspace");
        puts("3. T");
        char ch = getch();
        LL tst = stc;
        stc = min(stc, (LL)clock());
        
        if(ch == 'w'){
            if(cx > 1) cx--;
            replay += 'w';
        }else if(ch == 's'){
            if(cx < n) cx++;
            replay += 's';
        }else if(ch == 'a'){
            if(cy > 1) cy--;
            replay += 'a';
        }else if(ch == 'd'){
            if(cy < m) cy++;
            replay += 'd';
        }else if(ch == '\r'){
            LL x = cx, y = cy;
            if(st[x][y] == 1 && subget(x, y) == subtrue(x, y)){
                rep(i, 1, 8){
                    LL tx = x + fx2[i], ty = y + fy2[i];
                    if(tx < 1 || tx > n) continue;
                    if(ty < 1 || ty > n) continue;
                    if(st[tx][ty]) continue;
                    open_block(tx, ty);
                }
                replay += 'E';
                continue;
            }
            if(st[x][y]){
                puts("���Ϸ�����");
                sleep(1);
                continue;
            }
            open_block(x, y);
            replay += 'E';
        }else if(ch == '\b'){
            LL x = cx, y = cy;
            if(st[x][y] == 1){
                puts("���Ϸ�����");
                sleep(1);
                continue;
            }
            if(st[x][y] == 0) st[x][y] = 2, cnt++;
            else st[x][y] = 0, cnt--;
            replay += 'M';
        }else if(ch == 't'){
            puts("������Ҫ�ս����ķ���");
            LL x, y; rd(x), rd(y);
            if(x < 1 || x > n || y < 1 || y > m){
                puts("���Ϸ�����");
                sleep(1);
                continue;
            }
            cx = x, cy = y;
            replay += 't' + to_string(x) + ',' + to_string(y);
        }else stc = tst;
        
        if(iswin()){
            system("cls");
            puts("��Ϸʤ����");
            pnt();
            LL edc = clock();
            LL len = edc - stc;
            printf("�������ʱ��%02lld��%02lld��%03lld����\n", len / 1000 / 60, len / 1000 % 60, len % 1000);
            system("pause");
            
            ofstream fout("replay.txt");
            fout << n << ' ' << m << ' ' << k << ' ' << th <<endl;
            rep(i, 1, n){
                rep(j, 1, m) fout << a[i][j] << ' ';
                fout <<endl;
            }
            fout << replay <<endl;
            fout << len <<endl;
            fout.close();
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