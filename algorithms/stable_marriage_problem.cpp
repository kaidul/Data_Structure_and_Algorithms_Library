/* Ignore the dirty comments */
#define MAX 100001

int prefM[MAX][MAX], rankW[MAX][MAX], options[MAX], marriedTo[MAX];
queue <int> bachelor;
int N;

void stableMarriage() {
    memset(marriedTo, -1, sizeof marriedTo);
    
    int man, woman, husband;
    
    // while there is a free man m who still has a woman to propose to
    while(!bachelor.empty()) {
        man = bachelor.front();
        bachelor.pop();
        bool friendZoned = true;
        for(int j = options[man] - 1; j >= 0; --j) {
            // man's highest ranked such woman to whom he has not yet proposed
            woman = prefM[man][j];
            // man won't propose this woman again
            options[man]--;
            
            // if this woman is free
            if(marriedTo[woman] == -1) {
                // man and woman become engaged
                marriedTo[woman] = man;
                // man is no longer friend, so stop
                friendZoned = false;
                break;
            } else { // if woman is already engaged
                husband = marriedTo[woman];
                // if woman prefers man to husband (bitch)
                if(rankW[woman][man] > rankW[woman][husband]) {
                    // woman divorces her husband and man-woman get engaged
                    marriedTo[woman] = man;
                    
                    // welcome to friendzone, you miserable bastard! :3)
                    bachelor.push(husband);
                    
                    // man is no longer friend, so stop
                    friendZoned = false;
                    break;
                }
            }
        }
        // if man got his dick still dry, push the loser into frinedzone again
        if(friendZoned) bachelor.push(man);
    }
}

/*
 Problem: http://www.codechef.com/problems/STABLEMP (Classical Stable Marriage problem)
 */

int main(void) {
    int tcase;
    scanf("%d", &tcase);
    int man, woman;
    while(tcase--) {
        scanf("%d", &N);
        for(int i = 1; i <= N; i++) {
            scanf("%d", &woman);
            for(int j = N - 1; j >= 0; j--) {
                scanf("%d", &man);
                rankW[woman][man] = j;
            }
        }
        for(int i = 1; i <= N; i++) {
            scanf("%d", &man);
            bachelor.push(man);
            options[man] = N;
            for(int j = N - 1; j >= 0; j--) {
                scanf("%d", &prefM[man][j]);
            }
        }
        stableMarriage();
        for(int i = 1; i <= N; i++) {
            printf("%d %d\n", marriedTo[i], i);
        }
    }
    return EXIT_SUCCESS;
}
