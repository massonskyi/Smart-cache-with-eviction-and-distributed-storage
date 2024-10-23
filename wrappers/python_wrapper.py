import requests

class CacheClient:
    def __init__(self, base_url):
        self.base_url = base_url

    def put(self, key, value):
        response = requests.post(self.base_url, json={"key": key, "value": value})
        return response.json()

    def get(self, key):
        response = requests.get(f"{self.base_url}/{key}")
        return response.json()

    def remove(self, key):
        response = requests.delete(f"{self.base_url}/{key}")
        return response.json()
