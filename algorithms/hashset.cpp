template <typename K, typename F = KeyHash<K> >
class unordered_set : public HashTable<K, K, F> {};