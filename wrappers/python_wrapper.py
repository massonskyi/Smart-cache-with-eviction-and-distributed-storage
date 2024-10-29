# example.py
from lcache import Cache, LRUEvictionPolicy

# Create a cache with LRU eviction policy
cache = Cache(3)

# Add items to the cache
cache.put("key1", "value1", 10)
cache.put("key2", "value2", 20)
cache.put("key3", "value3", 30)

# Retrieve items from the cache
print(cache.get("key1"))  # Output: value1
print(cache.get("key2"))  # Output: value2

# Add another item to trigger eviction
cache.put("key4", "value4", 40)

# Check the state of the cache after eviction
print(cache.get("key3"))  # Output: None (evicted)
print(cache.get("key4"))  # Output: value4