#define maxN 250005
#define maxState (maxN << 1)
#define ASCII 128

// Necessary to calculate longest common substring in linear time where suffix array yields TLE

struct State {
    State *next[ASCII]; // //Links to next transition state in the DAWG (Directed acyclic word graph)
    State *suffix; // //Link to previous transition state in the DAWG
    int depth, id;
    //    long long cnt;
};
State pool[maxState]; // pool of states, from where you can pick a raw state to include in the DAWG
State *point, *root, *sink;
int size; // number of states present in the DAWG.

State *newState(int dep) {
    point->id = size++;
    point->depth = dep;
    return point++;
}

void init() {
    point = pool;
    size = 0;
    root = sink = newState(0);
}

void extend(int a) {
    State *p = newState(sink->depth + 1);
    State *cur = sink, *sufState;
    while (cur and !cur->next[a]) {
        cur->next[a] = p;
        cur = cur->suffix;
    }
    if (!cur)
        sufState = root;
    else {
        State *q = cur->next[a];
        if (q->depth == cur->depth + 1)
            sufState = q;
        else {
            State *r = newState(cur->depth+1);
            memcpy(r->next, q->next, sizeof(q->next));
            r->suffix = q->suffix;
            q->suffix = r;
            sufState = r;
            while (cur and cur->next[a] == q) {
                cur->next[a] = r;
                cur = cur->suffix;
            }
        }
    }
    p->suffix = sufState;
    sink = p;
}


int LCSubstr(string const& S1, string const& S2) {
    init();
    int len = (int)S1.length();
    for (int i = 0; i < len; i++)
        extend(S1[i]-'a');
    
    len = (int)S2.length();
    int indx = 0, length = 0, Max = 0;
    State *cur = root;
    for (int i = 0; i < len; i++) {
        if (cur->next[S2[i] - 'a']) {
            length++;
            cur = cur->next[S2[i] - 'a'];
        } else {
            while (cur and !cur->next[S2[i] - 'a'])
                cur = cur->suffix;
            
            if (!cur) {
                cur = root;
                length = 0;
            } else {
                length = cur->depth + 1;
                cur = cur->next[S2[i] - 'a'];
            }
        }
        if(length > Max) {
            Max = length;
            indx = i - length + 1;
        }
    }
    
    if(Max > 0)
        pf("%s\n", S2.substr(indx, Max).c_str());
    
    return Max; // len
}