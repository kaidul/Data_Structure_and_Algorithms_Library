/*
hash() takes the string and next free index as parameter.
if string is found in map, it returns its index.
else, it inserts in current free index and updates the free index.
*/
 
map<string, int> Map;
 
inline int hashString(string const& s, int &n) {
    int ret; 
    auto it = Map.find(s);
    if(it == Map.end()) Map.insert(pair< string, int > (s, ret = n++));
    else ret = it->second;
    return ret;
}