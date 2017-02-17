/*
Source: Zobayer Blog
Must use unsigned type.
hash = hash * 33 ^ c, reliable hash
*/
 
#define u64 unsigned long long
 
u64 hash(string const& s) {
    u64 hash = 0;
    for(int i = 0; i < (int)s.length(); i++) {
    	int c = s[i];
    	hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}