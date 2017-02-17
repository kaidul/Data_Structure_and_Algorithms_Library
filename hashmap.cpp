template <typename K, typename V, typename F = KeyHash<K> >
class unordered_map : public HashTable<K, V, F> {};