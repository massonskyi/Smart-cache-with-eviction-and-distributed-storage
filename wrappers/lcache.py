# wrappers/local_cache.py
import ctypes
import os

# Load the shared library
lib_path = os.path.join(os.path.dirname(__file__), '../cmake-build-debug/lib/liblocal_cache.so')
local_cache_lib = ctypes.CDLL(lib_path)
# Define the Cache class
class Cache:
    def __init__(self, max_size):
        """Initialize the Cache with a maximum size."""
        try:
            self.obj = local_cache_lib.Cache_new(max_size)
        except AttributeError as e:
            raise RuntimeError(f"Failed to initialize Cache: {e}")

    def put(self, key, value, ttl):
        """Put a key-value pair into the cache with a time-to-live (ttl)."""
        try:
            local_cache_lib.Cache_put(self.obj, key.encode('utf-8'), value.encode('utf-8'), ttl)
        except AttributeError as e:
            raise RuntimeError(f"Failed to put item into Cache: {e}")

    def get(self, key):
        """Get the value associated with a key from the cache."""
        try:
            local_cache_lib.Cache_get.restype = ctypes.c_char_p
            result = local_cache_lib.Cache_get(self.obj, key.encode('utf-8'))
            return result.decode('utf-8') if result else None
        except AttributeError as e:
            raise RuntimeError(f"Failed to get item from Cache: {e}")

    def remove(self, key):
        """Remove a key-value pair from the cache."""
        try:
            local_cache_lib.Cache_remove(self.obj, key.encode('utf-8'))
        except AttributeError as e:
            raise RuntimeError(f"Failed to remove item from Cache: {e}")

    def clear(self):
        """Clear all items from the cache."""
        try:
            local_cache_lib.Cache_clear(self.obj)
        except AttributeError as e:
            raise RuntimeError(f"Failed to clear Cache: {e}")

# Define the eviction policies
class LRUEvictionPolicy:
    def __init__(self):
        """Initialize the LRU Eviction Policy."""
        try:
            self.obj = local_cache_lib.LRUEvictionPolicy_new()
        except AttributeError as e:
            raise RuntimeError(f"Failed to initialize LRUEvictionPolicy: {e}")

class LFUEvictionPolicy:
    def __init__(self):
        """Initialize the LFU Eviction Policy."""
        try:
            self.obj = local_cache_lib.LFUEvictionPolicy_new()
        except AttributeError as e:
            raise RuntimeError(f"Failed to initialize LFUEvictionPolicy: {e}")

class FIFOEvictionPolicy:
    def __init__(self):
        """Initialize the FIFO Eviction Policy."""
        try:
            self.obj = local_cache_lib.FIFOEvictionPolicy_new()
        except AttributeError as e:
            raise RuntimeError(f"Failed to initialize FIFOEvictionPolicy: {e}")